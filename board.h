#ifndef BOARD_H
#define BOARD_H
#include <QMouseEvent>
#include <QGraphicsView>
#include <QPixmap>


class Board:public QGraphicsView
{
public:
    int Field = 70;
    int A;
    int B;
    int Figures[8][8];
    int Motion;
    int isGoing;
    int OldA;
    int OldB;

    bool WhiteCanGo[8][8];
    bool BlackCanGo[8][8];

    int WhiteKingPosition[2];
    int BlackKingPosition[2];

    QGraphicsScene *scene;

    QGraphicsPixmapItem * figures[8][8];
    QGraphicsPixmapItem * rect[8][8];

    const QPixmap White_Field = QPixmap("D:/Qt/projects/1/Chess_2/img/0_0_2.png");
    const QPixmap Black_Field = QPixmap("D:/Qt/projects/1/Chess_2/img/0_1_3.png");
    const QPixmap Yellow_Field = QPixmap("D:/Qt/projects/1/Chess_2/img/0_2_2.png");

    const QPixmap Hollow_Field = QPixmap();

    const QPixmap White_Pawn = QPixmap("D:/Qt/projects/1/Chess_2/img/1_0_5.png");
    const QPixmap White_Horse = QPixmap("D:/Qt/projects/1/Chess_2/img/2_2.png");
    const QPixmap White_Rook = QPixmap("D:/Qt/projects/1/Chess_2/img/3_2.png");
    const QPixmap White_Officer = QPixmap("D:/Qt/projects/1/Chess_2/img/4_2.png");
    const QPixmap White_Queen = QPixmap("D:/Qt/projects/1/Chess_2/img/5_2.png");
    const QPixmap White_King = QPixmap("D:/Qt/projects/1/Chess_2/img/6_2.png");

    const QPixmap Black_Pawn = QPixmap("D:/Qt/projects/1/Chess_2/img/11_2.png");
    const QPixmap Black_Horse = QPixmap("D:/Qt/projects/1/Chess_2/img/12_2.png");
    const QPixmap Black_Rook = QPixmap("D:/Qt/projects/1/Chess_2/img/13_2.png");
    const QPixmap Black_Officer = QPixmap("D:/Qt/projects/1/Chess_2/img/14_2.png");
    const QPixmap Black_Queen = QPixmap("D:/Qt/projects/1/Chess_2/img/15_2.png");
    const QPixmap Black_King = QPixmap("D:/Qt/projects/1/Chess_2/img/16_2.png");
    Board();

    void mousePressEvent(QMouseEvent * e);


    void WhitePawnMooving(int A, int B);
    void WhiteHorseMooving(int A, int B);
    void WhiteRookMooving(int A, int B);
    void WhiteOfficerMooving(int A, int B);
    void WhiteQueenMooving(int A, int B);
    void WhiteKingMooving(int A, int B);

    void BlackPawnMooving(int A, int B);
    void BlackHorseMooving(int A, int B);
    void BlackRookMooving(int A, int B);
    void BlackOfficerMooving(int A, int B);
    void BlackQueenMooving(int A, int B);
    void BlackKingMooving(int A, int B);

    void cleanField(int A, int B);
    void drawFiguresOnPositions(int A, int B);

    void WhiteCanGoTo();
    void BlackCanGoTo();

    bool WhiteKingIsInDanger();
    bool BlackKingIsInDanger();
};

#endif // BOARD_H
