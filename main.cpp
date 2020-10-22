#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QApplication>
#include <QKeyEvent>
#include <QtDebug>

#include <QLabel>
#include "board.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Board * b = new Board();
    /*ListenerRect * rect = new ListenerRect();
    rect->setFlag(QGraphicsItem::ItemIsFocusable);
    rect->setFocus();*/
    return a.exec();
}


