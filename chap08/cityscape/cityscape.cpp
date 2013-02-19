#include <QtWidgets>

#include "annotation.h"
#include "cityblock.h"
#include "cityscape.h"
#include "cityview.h"

Cityscape::Cityscape()
{
    scene = new QGraphicsScene(-22.25, -22.25, 1980, 1980);
    scene->setBackgroundBrush(QColor(255, 255, 238));
    generateCityBlocks();

    view = new CityView;
    view->setScene(scene);
    setCentralWidget(view);

    setWindowTitle(tr("Cityscape"));
}

void Cityscape::generateCityBlocks()
{
    QSet<QString> names;
    names << "Adams" << "Agnew" << "Arthur" << "Breckinridge"
          << "Buchanan" << "Burr" << "Bush" << "Calhoun" << "Carter"
          << "Cheney" << "Cleveland" << "Clinton" << "Colfax"
          << "Coolidge" << "Curtis" << "Dallas" << "Dawes"
          << "Eisenhower" << "Fairbanks" << "Fillmore" << "Ford"
          << "Garfield" << "Garner" << "Gerry" << "Gore" << "Grant"
          << "Hamlin" << "Harding" << "Harrison" << "Hayes"
          << "Hendricks" << "Hobart" << "Hoover" << "Humphrey"
          << "Jackson" << "Jefferson" << "Johnson" << "Kennedy"
          << "King" << "Lincoln" << "Madison" << "Marshall"
          << "McKinley" << "Mondale" << "Monroe" << "Morton"
          << "Nixon" << "Pierce" << "Polk" << "Quayle" << "Reagan"
          << "Rockefeller" << "Roosevelt" << "Sherman" << "Stevenson"
          << "Taft" << "Taylor" << "Tompkins" << "Truman" << "Tyler"
          << "Van Buren" << "Wallace" << "Washington" << "Wheeler"
          << "Wilson";

    QSetIterator<QString> i(names);
    for (int y = 0; y < 44; ++y) {
        for (int x = 0; x < 44; ++x) {
            int percentile;
            if (x > 20 && x < 24 && y > 20 && y < 24) {
                percentile = std::rand() % (std::rand() % 2 != 0
                                            ? 10 : 100);
            } else if (x > 18 && x < 26 && y > 18 && y < 26) {
                percentile = std::rand() % (rand() % 3 != 0
                                            ? 10 : 100);
            } else if (x > 15 && x < 29 && y > 15 && y < 29) {
                percentile = std::rand() % (std::rand() % 5 != 0
                                            ? 10 : 100);
            } else {
                percentile = std::rand() % 100;
            }

            CityBlock::Kind kind;
            QString name;

            if (percentile == 0) {
                kind = CityBlock::Park;
                name = tr("%1 Park");
            } else if (percentile <= 2) {
                kind = CityBlock::SmallBuilding;
            } else if (percentile <= 4) {
                kind = CityBlock::Hospital;
                name = tr("%1 Hospital");
            } else if (percentile == 5) {
                kind = CityBlock::Hall;
                name = tr("%1 Hall");
            } else if (percentile <= 7) {
                kind = CityBlock::Building;
                name = tr("%1 Bldg");
            } else if (percentile <= 9) {
                kind = CityBlock::Tower;
                name = tr("%1 Tower");
            } else if (percentile <= 15) {
                kind = CityBlock::LShapedBlock;
            } else if (percentile <= 30) {
                kind = CityBlock::LShapedBlockPlusSmallBlock;
            } else if (percentile <= 70) {
                kind = CityBlock::TwoBlocks;
            } else {
                kind = CityBlock::BlockPlusTwoSmallBlocks;
            }

            CityBlock *block = new CityBlock(kind);
            block->setPos(QPointF(x * 44.5, y * 44.5));
            scene->addItem(block);

            if (!name.isEmpty()) {
                if (!i.hasNext())
                    i.toFront();

                bool major = (std::rand() % 10 == 0);
                Annotation *annotation =
                        new Annotation(name.arg(i.next()), major);
                annotation->setPos(block->pos());
                scene->addItem(annotation);
            }
        }
    }
}
