#include <QtWidgets>

#include "imagewindow.h"
#include "ui_resizedialog.h"

ImageWindow::ImageWindow()
{
    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Dark);
    imageLabel->setAutoFillBackground(true);
    imageLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    setCentralWidget(imageLabel);

    createActions();
    createMenus();

    statusBar()->showMessage(tr("Ready"), 2000);

    connect(&thread, SIGNAL(transactionStarted(const QString &)),
            statusBar(), SLOT(showMessage(const QString &)));
    connect(&thread, SIGNAL(allTransactionsDone()),
            this, SLOT(allTransactionsDone()));

    setCurrentFile("");
}

void ImageWindow::closeEvent(QCloseEvent *event)
{
    if (okToContinue()) {
        event->accept();
    } else {
        event->ignore();
    }
}

void ImageWindow::open()
{
    if (okToContinue()) {
        QString fileName = QFileDialog::getOpenFileName(this);
        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}

bool ImageWindow::save()
{
    if (curFile.isEmpty()) {
        return saveAs();
    } else {
        saveFile(curFile);
        return true;
    }
}

bool ImageWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this);
    if (QFile::exists(fileName)) {
        int r = QMessageBox::warning(this, tr("Image Pro"),
                        tr("File %1 already exists.\n"
                           "Do you want to overwrite it?")
                        .arg(QDir::toNativeSeparators(fileName)),
                        QMessageBox::Yes | QMessageBox::No);
        if (r == QMessageBox::No)
            return true;
    }
    if (!fileName.isEmpty())
        saveFile(fileName);
    return true;
}

void ImageWindow::flipHorizontally()
{
    addTransaction(new FlipTransaction(Qt::Horizontal));
}

void ImageWindow::flipVertically()
{
    addTransaction(new FlipTransaction(Qt::Vertical));
}

void ImageWindow::resizeImage()
{
    QDialog dialog;
    Ui::ResizeDialog ui;
    ui.setupUi(&dialog);

    ui.widthSpinBox->setValue(imageLabel->pixmap()->width());
    ui.heightSpinBox->setValue(imageLabel->pixmap()->height());

    if (dialog.exec()) {
        QSize newSize(ui.widthSpinBox->value(),
                      ui.heightSpinBox->value());
        addTransaction(new ResizeTransaction(newSize));
    }
}

void ImageWindow::convertTo32Bit()
{
    addTransaction(new ConvertDepthTransaction(32));
}

void ImageWindow::convertTo8Bit()
{
    addTransaction(new ConvertDepthTransaction(8));
}

void ImageWindow::convertTo1Bit()
{
    addTransaction(new ConvertDepthTransaction(1));
}

void ImageWindow::addTransaction(Transaction *transact)
{
    thread.addTransaction(transact);
    openAction->setEnabled(false);
    saveAction->setEnabled(false);
    saveAsAction->setEnabled(false);
}

void ImageWindow::about()
{
    QMessageBox::about(this, tr("About Image Pro"),
            tr("<h2>Image Pro 1.1</h2>"
               "<p>Copyright &copy; 2008 Software Inc."
               "<p>Image Pro is a small application that demonstrates "
               "signal-slot connections across threads."));
}

void ImageWindow::allTransactionsDone()
{
    openAction->setEnabled(true);
    saveAction->setEnabled(true);
    saveAsAction->setEnabled(true);
    imageLabel->setPixmap(QPixmap::fromImage(thread.image()));
    setWindowModified(true);
    statusBar()->showMessage(tr("Ready"), 2000);
}

void ImageWindow::createActions()
{
    openAction = new QAction(tr("&Open..."), this);
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing image file"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save the image to disk"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAction = new QAction(tr("Save &As..."), this);
    saveAsAction->setStatusTip(tr("Save the image under a new name"));
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    flipHorizontallyAction = new QAction(tr("Flip &Horizontally"),
                                         this);
    flipHorizontallyAction->setShortcut(tr("Ctrl+H"));
    flipHorizontallyAction->setStatusTip(tr("Flip the image "
                                            "horizontally"));
    connect(flipHorizontallyAction, SIGNAL(triggered()),
            this, SLOT(flipHorizontally()));

    flipVerticallyAction = new QAction(tr("Flip &Vertically"), this);
    flipVerticallyAction->setShortcut(tr("Ctrl+V"));
    flipVerticallyAction->setStatusTip(tr("Flip the image vertically"));
    connect(flipVerticallyAction, SIGNAL(triggered()),
            this, SLOT(flipVertically()));

    resizeAction = new QAction(tr("&Resize..."), this);
    resizeAction->setShortcut(tr("Ctrl+R"));
    resizeAction->setStatusTip(tr("Resize the image"));
    connect(resizeAction, SIGNAL(triggered()),
            this, SLOT(resizeImage()));

    convertTo32BitAction = new QAction(tr("32 Bit"), this);
    convertTo32BitAction->setStatusTip(tr("Convert to 32-bit image"));
    connect(convertTo32BitAction, SIGNAL(triggered()),
            this, SLOT(convertTo32Bit()));

    convertTo8BitAction = new QAction(tr("8 Bit"), this);
    convertTo8BitAction->setStatusTip(tr("Convert to 8-bit image"));
    connect(convertTo8BitAction, SIGNAL(triggered()),
            this, SLOT(convertTo8Bit()));

    convertTo1BitAction = new QAction(tr("1 Bit"), this);
    convertTo1BitAction->setStatusTip(tr("Convert to 1-bit image"));
    connect(convertTo1BitAction, SIGNAL(triggered()),
            this, SLOT(convertTo1Bit()));

    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("Show the application's About box"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAction = new QAction(tr("About &Qt"), this);
    aboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void ImageWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(flipHorizontallyAction);
    editMenu->addAction(flipVerticallyAction);
    editMenu->addAction(resizeAction);
    editMenu->addSeparator();

    convertToSubMenu = editMenu->addMenu(tr("&Convert to"));
    convertToSubMenu->addAction(convertTo32BitAction);
    convertToSubMenu->addAction(convertTo8BitAction);
    convertToSubMenu->addAction(convertTo1BitAction);

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
}

bool ImageWindow::okToContinue()
{
    if (isWindowModified()) {
        int r = QMessageBox::warning(this, tr("Image Pro"),
                        tr("The image has been modified.\n"
                           "Do you want to save your changes?"),
                        QMessageBox::Yes | QMessageBox::No
                        | QMessageBox::Cancel);
        if (r == QMessageBox::Yes) {
            return save();
        } else if (r == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

void ImageWindow::loadFile(const QString &fileName)
{
    QImage newImage;

    QApplication::setOverrideCursor(Qt::WaitCursor);
    bool loaded = newImage.load(fileName);
    QApplication::restoreOverrideCursor();

    if (loaded) {
        thread.setImage(newImage);
        imageFormat = QImageReader::imageFormat(fileName);
        imageLabel->setPixmap(QPixmap::fromImage(newImage));
        setCurrentFile(fileName);
        statusBar()->showMessage(tr("File loaded"), 2000);
    } else {
        QMessageBox::warning(this, tr("Image Pro"),
                             tr("Error when loading image."));
        statusBar()->showMessage(tr("Loading canceled"), 2000);
    }
}

void ImageWindow::saveFile(const QString &fileName)
{
    QImage image = thread.image();

    QApplication::setOverrideCursor(Qt::WaitCursor);
    bool saved = image.save(fileName, imageFormat);
    QApplication::restoreOverrideCursor();

    if (saved) {
        setCurrentFile(fileName);
        statusBar()->showMessage(tr("File saved"), 2000);
    } else {
        QMessageBox::warning(this, tr("Image Pro"),
                             tr("Error when saving image."));
        statusBar()->showMessage(tr("Saving canceled"), 2000);
    }
}

void ImageWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    setWindowModified(false);

    bool hasImage = !curFile.isEmpty();

    if (hasImage) {
        setWindowTitle(tr("%1[*] - %2").arg(strippedName(curFile))
                                       .arg(tr("Image Pro")));
    } else {
        setWindowTitle(tr("Image Pro"));
    }

    saveAction->setEnabled(hasImage);
    saveAsAction->setEnabled(hasImage);
    flipHorizontallyAction->setEnabled(hasImage);
    flipVerticallyAction->setEnabled(hasImage);
    resizeAction->setEnabled(hasImage);
    convertTo32BitAction->setEnabled(hasImage);
    convertTo8BitAction->setEnabled(hasImage);
    convertTo1BitAction->setEnabled(hasImage);
}

QString ImageWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}
