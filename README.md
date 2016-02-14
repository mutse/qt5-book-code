Qt5 Book Code
=============

**Description**:

Porting the source code of the book C++ GUI Programming with Qt 4 (second edition) from Qt4 to Qt5 by Mutse Young.

The examples for all chapters with Qt 5.0 will be built on Ubuntu 12.04, and you can install qt5.0 with [ppa](http://developer.ubuntu.com/get-started/gomobile/).

## Contents

1. Getting Started

        chap01/age
        chap01/hello
        chap01/quit

2. Creating Dialogs

        chap02/find
        chap02/gotocell1
        chap02/gotocell2
        chap02/gotocell3
        chap02/sort

3. Creating Main Windows

        chap03/spreadsheet

4. Implementing Application Functionality

        chap04/spreadsheet

5. Creating Custom Widgets

        chap05/hexspinbox
        chap05/iconeditor
        chap05/iconeditorplugin
        chap05/plotter

6. Layout Management

        chap06/findfile1
        chap06/findfile2
        chap06/findfile3
        chap06/mailclient
        chap06/mdieditor
        chap06/preferences
        chap06/splitter

7. Event Processing

        chap07/ticker

8. 2D Graphics

        chap08/cityscape
        chap08/diagram
        chap08/oventimer

9. Drag and Drop

        chap09/projectchooser

10. Item View Classes

        chap10/booleanparser
        chap10/cities
        chap10/colornames
        chap10/coordinatesetter
        chap10/currencies
        chap10/directoryviewer
        chap10/flowchartsymbolpicker
        chap10/settingsviewer
        chap10/teamleaders
        chap10/trackeditor

12. Input/Output

        chap12/imageconverter
        chap12/imagespace
        chap12/tidy

13. Databases

        chap13/scooters
        chap13/staffmanager

14. Multithreading

        chap14/imagepro
        chap14/semaphores
        chap14/threads
        chap14/waitconditions

15. Networking

        chap15/ftpget
        chap15/httpget
        chap15/spider
        chap15/tripplanner
        chap15/tripserver
        chap15/weatherballoon
        chap15/weatherstation

16. XML

        chap16/domparser
        chap16/saxhandler
        chap16/xmlstreamreader
        chap16/xmlstreamwriter

19. Look and Feel Customization

        chap19/bronze
        chap19/candy

20. 3D Graphics

        chap20/teapots
        chap20/tetrahedron
        chap20/vowelcube

21. Creating Plugins

        chap21/basiceffectsplugin
        chap21/bronze
        chap21/bronzestyleplugin
        chap21/cursorplugin
        chap21/extraeffectsplugin
        chap21/textart

22. Application Scripting

        chap22/calculator
        chap22/gaspump
        chap22/htmleditor

23. Platform-Specific Features

        chap23/addressbook
        chap23/bouncer
        chap23/mediaplayer
        chap23/tictactoe

24. Embedded Programming

        chap24/expenses
        chap24/unitconverter

## Note

The chap15 Networking needs QtFtp module before compiling because it is removed in Qt5. You can download QtFtp from its [repo](git://gitorious.org/qt/qtftp.git) by git command:

> git clone git://gitorious.org/qt/qtftp.git

All examples are compiled on Ubuntu 12.04.2 LTE with Qt5, except the chap23,
which is only compiled on Windows platform with axserver module.

## Thanks

Ersin Özkan <ersin.ozkan@windowslive.com> 

reported pixmap.fill(this, 0, 0) in the chap05/plotter/plotter.cpp is deprecated with QT5.0.2, and suggested to use fill(QColor &) instead it.

Adriano Martinez <uberkael@gmail.com>

found the bug pixmap.fill(palette().dark().color()) not work in Qt5.5, and suggested to use
 fill(QWidget::palette().color(QWidget::backgroundRole())) instead it.

## TODO

> <input type="checkbox" disabled checked> <s>Test with Qt5.0.1</s>

> <input type="checkbox" disabled checked> <s>Test with Qt5.0.2</s>

> <input type="checkbox" disabled> Test with Qt5.1.0

> <input type="checkbox" disabled> Test with Qt5.1.1

> <input type="checkbox" disabled> Test with Qt5.2.0

> <input type="checkbox" disabled> Test with Qt5.3.0

> <input type="checkbox" disabled> Test with Qt5.4.0

> <input type="checkbox" disabled> Test with Qt5.5.0

## Getting involved

Any questions or suggestions are welcome. You can contact me with <a href="mailto:yyhoo2.young@gmail.com">yyhoo2.young@gmail.com<a>

