#include "board.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QDebug>
#include <QLabel>
#include <QMessageBox>

Board::Board()
{

    scene = new QGraphicsScene();
    setFocus();
    setFixedSize(8*Field+3, 8*Field+5);
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++){
            if(j == 1)
                Figures[i][j] = 11;
            else if(j == 6)
                Figures[i][j] = 1;
            else
            Figures[i][j] = 0;

        }
    Figures[1][7] = 2;
    Figures[6][7] = 2;
    Figures[0][7] = 3;
    Figures[7][7] = 3;
    Figures[2][7] = 4;
    Figures[5][7] = 4;
    Figures[3][7] = 5;
    BlackKingPosition[0] = 5;
    BlackKingPosition[1] = 3;
    Figures[5][3] = 16;
    WhiteKingPosition[0] = 3;
    WhiteKingPosition[1] = 7;
    Figures[4][7] = 6;

    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++){
            rect[i][j] = new QGraphicsPixmapItem();
            rect[i][j]->setPos(i*Field,j*Field);
            cleanField(i,j);
            rect[i][j]->setVisible(true);
            scene->addItem(rect[i][j]);

            figures[i][j] = new QGraphicsPixmapItem();
            figures[i][j]->setPos(i*Field,j*Field);

            drawFiguresOnPositions(i,j);
            //figures[i][j]->setPixmap(Hollow_Field);
            figures[i][j]->setVisible(true);
            scene->addItem(figures[i][j]);

        }


    setScene(scene);
    show();
}



void Board::mousePressEvent(QMouseEvent * e){
    A = e->x()/Field;
    B = e->y()/Field;

    if(Motion == 0){

    if(Figures[A][B] == 1){
        WhitePawnMooving(A,B);
        isGoing = 1;
    }

    if(Figures[A][B] == 2){
        WhiteHorseMooving(A,B);
        isGoing = 2;
    }
    if(Figures[A][B] == 3){
        WhiteRookMooving(A,B);
        isGoing = 3;
    }
    if(Figures[A][B] == 4){
        WhiteOfficerMooving(A,B);
        isGoing = 4;
    }
    if(Figures[A][B] == 5){
        WhiteQueenMooving(A, B);
        isGoing = 5;
    }
    OldA = A;
    OldB = B;
    Motion = 1;
    WhiteCanGoTo();
    if(WhiteCanGo[BlackKingPosition[0]][BlackKingPosition[1]])
        qDebug() << "aaaaaa";
    }


    else
        if(Motion == 1){
        if(rect[A][B]->pixmap() == Yellow_Field){
            for(int i = 0; i < 8; i++)
                for(int j = 0; j < 8; j++){
                    cleanField(i,j);
                }
            Motion = 0;

            Figures[OldA][OldB] = 0;
            figures[OldA][OldB]->setPixmap(Hollow_Field);

            Figures[A][B] = isGoing;
            if(isGoing == 1){
                figures[A][B]->setPixmap(White_Pawn);
            }
            if(isGoing == 2){
                figures[A][B]->setPixmap(White_Horse);
            }
            if(isGoing == 3){
                figures[A][B]->setPixmap(White_Rook);
            }
            if(isGoing == 4){
                figures[A][B]->setPixmap(White_Officer);
            }
            if(isGoing == 5){
                figures[A][B]->setPixmap(White_Queen);
            }
            isGoing = 0;
        }
        else {
            for(int i = 0; i < 8; i++)
                for(int j = 0; j < 8; j++){
                    cleanField(i,j);
                }
            Motion = 2;
        }
        }
    else
        if(Motion == 2){
        if(Figures[A][B] == 11){
            BlackPawnMooving(A,B);
            isGoing = 11;
        }

        if(Figures[A][B] == 12){
            WhiteHorseMooving(A,B);
            isGoing = 12;
        }
        if(Figures[A][B] == 13){
            WhiteRookMooving(A,B);
            isGoing = 13;
        }
        if(Figures[A][B] == 14){
            WhiteOfficerMooving(A,B);
            isGoing = 14;
        }
        if(Figures[A][B] == 15){
            WhiteQueenMooving(A, B);
            isGoing = 15;
        }
        OldA = A;
        OldB = B;
        Motion = 3;
        BlackCanGoTo();
        if(BlackCanGo[WhiteKingPosition[0]][WhiteKingPosition[1]])
            qDebug() << "aaaaaa";
        }




}

/*
Figures:
0 = no Figure;
1 = white pawn
2 = white horse
3 = white rook
4 = white officer
5 = white queen
6 = white king

11 = black pawn
12 = black horse
13 = black rook
14 = black officer
15 = black queen
16 = black king

motions:
0 - white is movung, figure is not taken;
1 - white is movung, figure is taken;
3 - black is movung, figure is not taken;
4 - black is movung, figure is taken;
*/

void Board::WhitePawnMooving(int A, int B){
    if(B > 0 ) {
        if(Figures[A][B-1] == 0){
            rect[A][B-1]->setPixmap(Yellow_Field);
        }
    }

    if(B == 6){
        if(Figures[A][B-2] == 0)
            rect[A][B-2]->setPixmap(Yellow_Field);
    }

    if(B > 0 && A < 7){
        if(Figures[A+1][B-1] > 10){
            rect[A+1][B-1]->setPixmap(Yellow_Field);
       }
    }

    if(A > 0 && B > 0){
        if(Figures[A-1][B-1] > 10){
            rect[A-1][B-1]->setPixmap(Yellow_Field);
        }
   }

}

void Board::WhiteHorseMooving(int A, int B){
    if(A < 7 && B > 1)
        if(Figures[A+1][B-2] > 10 || Figures[A+1][B-2] == 0){
            rect[A+1][B-2]->setPixmap(Yellow_Field);
        }
    if(A < 6 && B > 0)
        if(Figures[A+2][B-1] > 10 || Figures[A+2][B-1] == 0){
            rect[A+2][B-1]->setPixmap(Yellow_Field);
        }
    if(A < 6 && B < 7)
        if(Figures[A+2][B+1] > 10 || Figures[A+2][B+1] == 0){
            rect[A+2][B+1]->setPixmap(Yellow_Field);
        }
    if(A < 7 && B < 6)
        if(Figures[A+1][B+2] > 10 || Figures[A+1][B+2] == 0){
            rect[A+1][B+2]->setPixmap(Yellow_Field);
        }
    if(A > 0 && B < 6)
         if(Figures[A-1][B+2] > 10 || Figures[A-1][B+2] == 0){
             rect[A-1][B+2]->setPixmap(Yellow_Field);
         }
    if(A > 1 && B < 7)
         if(Figures[A-2][B+1] > 10 || Figures[A-2][B+1] == 0){
             rect[A-2][B+1]->setPixmap(Yellow_Field);
         }
    if(A > 1 && B > 0)
         if(Figures[A-2][B-1] > 10 || Figures[A-2][B-1] == 0){
             rect[A-2][B-1]->setPixmap(Yellow_Field);
         }
    if(A>0 && B > 1)
         if(Figures[A-1][B-2] > 10 || Figures[A-1][B-2] == 0){
             rect[A-1][B-2]->setPixmap(Yellow_Field);
         }

}

void Board::WhiteRookMooving(int A, int B){
    int A2 = A + 1, B2 = B;
    bool L = true;
    while (A2 <= 7 && L) {
        if(Figures[A2][B] == 0 || Figures[A2][B] > 10){
            rect[A2][B]->setPixmap(Yellow_Field);
        }
        if(Figures[A2][B] != 0)
            L = false;        
        A2++;
    }

    A2 = A - 1;
    L = true;
    while (A2 >= 0 && L) {
        if(Figures[A2][B] == 0 || Figures[A2][B] > 10){
            rect[A2][B]->setPixmap(Yellow_Field);
        }
        if(Figures[A2][B] != 0)
            L = false;
        A2--;
    }

    B2 = B - 1;
    L = true;
    while (B2 >= 0 && L) {
        if(Figures[A][B2] == 0 || Figures[A][B2] > 10){
            rect[A][B2]->setPixmap(Yellow_Field);
        }
        if(Figures[A][B2] != 0)
            L = false;
        B2--;
    }

    B2 = B + 1;
    L  = true;
    while (B2 <= 7 && L) {
        if(Figures[A][B2] == 0 || Figures[A][B2] > 10){
            rect[A][B2]->setPixmap(Yellow_Field);
        }
        if(Figures[A][B2] != 0)
                L = false;
        B2++;
    }

}

void Board::WhiteOfficerMooving(int A, int B){
    int A2 = A + 1, B2 = B + 1;
    bool L = true;
    while(A2 <= 7 && B2 <= 7 && L){
        if(Figures[A2][B2] == 0 || Figures[A2][B2] > 10){
            rect[A2][B2]->setPixmap(Yellow_Field);
        }
        if(Figures[A2][B2] != 0)
                L = false;
        A2++;
        B2++;
    }
    A2 = A - 1;
    B2 = B - 1;
    L  = true;
    while(A2 >= 0 && B2 >= 0 && L){
        if(Figures[A2][B2] == 0 || Figures[A2][B2] > 10){
            rect[A2][B2]->setPixmap(Yellow_Field);
        }
        if(Figures[A2][B2] != 0)
                L = false;
        A2--;
        B2--;
    }
    A2 = A - 1;
    B2 = B + 1;
    L  = true;
    while(A2 >= 0 && B2 <= 7 && L){
        if(Figures[A2][B2] == 0 || Figures[A2][B2] > 10){
            rect[A2][B2]->setPixmap(Yellow_Field);
        }
        if(Figures[A2][B2] != 0)
                L = false;
        A2--;
        B2++;
    }
    A2 = A + 1;
    B2 = B - 1;
    L  = true;
    while(A2 <= 7 && B2 >= 0 && L){
        if(Figures[A2][B2] == 0 || Figures[A2][B2] > 10){
            rect[A2][B2]->setPixmap(Yellow_Field);
        }
        if(Figures[A2][B2] != 0)
                L = false;
        A2++;
        B2--;
    }

}

void Board::WhiteQueenMooving(int A, int B){
    WhiteRookMooving(A, B);
    WhiteOfficerMooving(A, B);
}

void Board::WhiteKingMooving(int A, int B){

}

void Board::WhiteCanGoTo(){
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            WhiteCanGo[i][j] = false;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            int A = i; int B = j;
            if(Figures[i][j] == 1){


                if(B > 0 && A < 7){
                    if(Figures[A+1][B-1] > 10){
                        WhiteCanGo[A+1][B-1] = true;
                   }
                }

                if(A > 0 && B > 0){
                    if(Figures[A-1][B-1] > 10){
                        WhiteCanGo[A-1][B-1] = true;
                    }
               }

            }
            if(Figures[i][j] == 2){
                if(A < 7 && B > 1)
                    if(Figures[A+1][B-2] > 10 || Figures[A+1][B-2] == 0){
                        WhiteCanGo[A+1][B-2] = true;
                    }
                if(A < 6 && B > 0)
                    if(Figures[A+2][B-1] > 10 || Figures[A+2][B-1] == 0){
                        WhiteCanGo[A+2][B-1] = true;
                    }
                if(A < 6 && B < 7)
                    if(Figures[A+2][B+1] > 10 || Figures[A+2][B+1] == 0){
                        WhiteCanGo[A+2][B+1] = true;
                    }
                if(A < 7 && B < 6)
                    if(Figures[A+1][B+2] > 10 || Figures[A+1][B+2] == 0){
                        WhiteCanGo[A+1][B+2] = true;
                    }
                if(A > 0 && B < 6)
                     if(Figures[A-1][B+2] > 10 || Figures[A-1][B+2] == 0){
                         WhiteCanGo[A-1][B+2] = true;
                     }
                if(A > 1 && B < 7)
                     if(Figures[A-2][B+1] > 10 || Figures[A-2][B+1] == 0){
                         WhiteCanGo[A-2][B+1] = true;
                     }
                if(A > 1 && B > 0)
                     if(Figures[A-2][B-1] > 10 || Figures[A-2][B-1] == 0){
                         WhiteCanGo[A-2][B-1] = true;
                     }
                if(A>0 && B > 1)
                     if(Figures[A-1][B-2] > 10 || Figures[A-1][B-2] == 0){
                         WhiteCanGo[A-1][B-2] = true;
                     }

            }
            if(Figures[i][j] == 3 || Figures[i][j] == 5){
                int A2 = A + 1, B2 = B;
                bool L = true;
                while (A2 <= 7 && L) {
                    if(Figures[A2][B] == 0 || Figures[A2][B] > 10){
                        WhiteCanGo[A2][B] = true;
                    }
                    if(Figures[A2][B] != 0)
                        L = false;
                    A2++;
                }

                A2 = A - 1;
                L = true;
                while (A2 >= 0 && L) {
                    if(Figures[A2][B] == 0 || Figures[A2][B] > 10){
                        WhiteCanGo[A2][B] = true;
                    }
                    if(Figures[A2][B] != 0)
                        L = false;
                    A2--;
                }

                B2 = B - 1;
                L = true;
                while (B2 >= 0 && L) {
                    if(Figures[A][B2] == 0 || Figures[A][B2] > 10){
                        WhiteCanGo[A][B2] = true;
                    }
                    if(Figures[A][B2] != 0)
                        L = false;
                    B2--;
                }

                B2 = B + 1;
                L  = true;
                while (B2 <= 7 && L) {
                    if(Figures[A][B2] == 0 || Figures[A][B2] > 10){
                        WhiteCanGo[A][B2] = true;
                    }
                    if(Figures[A][B2] != 0)
                            L = false;
                    B2++;
                }

            }
            if(Figures[i][j] == 4 || Figures[i][j] == 5){
                int A2 = A + 1, B2 = B + 1;
                bool L = true;
                while(A2 <= 7 && B2 <= 7 && L){
                    if(Figures[A2][B2] == 0 || Figures[A2][B2] > 10){
                        WhiteCanGo[A2][B2] = true;
                    }
                    if(Figures[A2][B2] != 0)
                            L = false;
                    A2++;
                    B2++;
                }
                A2 = A - 1;
                B2 = B - 1;
                L  = true;
                while(A2 >= 0 && B2 >= 0 && L){
                    if(Figures[A2][B2] == 0 || Figures[A2][B2] > 10){
                        WhiteCanGo[A2][B2] = true;
                    }
                    if(Figures[A2][B2] != 0)
                            L = false;
                    A2--;
                    B2--;
                }
                A2 = A - 1;
                B2 = B + 1;
                L  = true;
                while(A2 >= 0 && B2 <= 7 && L){
                    if(Figures[A2][B2] == 0 || Figures[A2][B2] > 10){
                        WhiteCanGo[A2][B2] = true;
                    }
                    if(Figures[A2][B2] != 0)
                            L = false;
                    A2--;
                    B2++;
                }
                A2 = A + 1;
                B2 = B - 1;
                L  = true;
                while(A2 <= 7 && B2 >= 0 && L){
                    if(Figures[A2][B2] == 0 || Figures[A2][B2] > 10){
                        WhiteCanGo[A2][B2] = true;
                    }
                    if(Figures[A2][B2] != 0)
                            L = false;
                    A2++;
                    B2--;
                }

            }
            /*if(Figures[i][j] == 5){
                int A2 = A + 1, B2 = B;
                bool L = true;
                while (A2 <= 7 && L) {
                    if(Figures[A2][B] == 0 || Figures[A2][B] > 10){
                        WhiteCanGo[A2][B] = true;
                    }
                    if(Figures[A2][B] != 0)
                        L = false;
                    A2++;
                }

                A2 = A - 1;
                L = true;
                while (A2 >= 0 && L) {
                    if(Figures[A2][B] == 0 || Figures[A2][B] > 10){
                        WhiteCanGo[A2][B] = true;
                    }
                    if(Figures[A2][B] != 0)
                        L = false;
                    A2--;
                }

                B2 = B - 1;
                L = true;
                while (B2 >= 0 && L) {
                    if(Figures[A][B2] == 0 || Figures[A][B2] > 10){
                        WhiteCanGo[A][B2] = true;
                    }
                    if(Figures[A][B2] != 0)
                        L = false;
                    B2--;
                }

                B2 = B + 1;
                L  = true;
                while (B2 <= 7 && L) {
                    if(Figures[A][B2] == 0 || Figures[A][B2] > 10){
                        WhiteCanGo[A][B2] = true;
                    }
                    if(Figures[A][B2] != 0)
                            L = false;
                    B2++;
                }
                A2 = A + 1;
                B2 = B + 1;
                L = true;
                while(A2 <= 7 && B2 <= 7 && L){
                    if(Figures[A2][B2] == 0 || Figures[A2][B2] > 10){
                        WhiteCanGo[A2][B2] = true;
                    }
                    if(Figures[A2][B2] != 0)
                            L = false;
                    A2++;
                    B2++;
                }
                A2 = A - 1;
                B2 = B - 1;
                L  = true;
                while(A2 >= 0 && B2 >= 0 && L){
                    if(Figures[A2][B2] == 0 || Figures[A2][B2] > 10){
                        WhiteCanGo[A2][B2] = true;
                    }
                    if(Figures[A2][B2] != 0)
                            L = false;
                    A2--;
                    B2--;
                }
                A2 = A - 1;
                B2 = B + 1;
                L  = true;
                while(A2 >= 0 && B2 <= 7 && L){
                    if(Figures[A2][B2] == 0 || Figures[A2][B2] > 10){
                        WhiteCanGo[A2][B2] = true;
                    }
                    if(Figures[A2][B2] != 0)
                            L = false;
                    A2--;
                    B2++;
                }
                A2 = A + 1;
                B2 = B - 1;
                L  = true;
                while(A2 <= 7 && B2 >= 0 && L){
                    if(Figures[A2][B2] == 0 || Figures[A2][B2] > 10){
                        WhiteCanGo[A2][B2] = true;
                    }
                    if(Figures[A2][B2] != 0)
                            L = false;
                    A2++;
                    B2--;
                }

            }*/
        }
    }
}

void Board::BlackPawnMooving(int A, int B){
    if(B < 7) {
        if(Figures[A][B+1] == 0){
            rect[A][B+1]->setPixmap(Yellow_Field);
        }
    }

    if(B == 1){
        if(Figures[A][B+2] == 0)
            rect[A][B+2]->setPixmap(Yellow_Field);
    }

    if(B < 7 && A < 7){
        if(Figures[A+1][B+1] > 10){
            rect[A+1][B+1]->setPixmap(Yellow_Field);
       }
    }

    if(A > 0 && B < 7){
        if(Figures[A-1][B+1] > 10){
            rect[A-1][B+1]->setPixmap(Yellow_Field);
        }
   }

}

void Board::cleanField(int i, int j){
    if(i % 2 == 0){
        if(j % 2 == 0){
            rect[i][j]->setPixmap(White_Field);
        }
        else
            rect[i][j]->setPixmap(Black_Field);
    }
    else
    {
        if (j % 2 == 0)
            rect[i][j]->setPixmap(Black_Field);
            else
            rect[i][j]->setPixmap(White_Field);
    }

}

void Board::drawFiguresOnPositions(int i, int j){
    if(Figures[i][j] == 0)
        figures[i][j]->setPixmap(Hollow_Field);
    if(Figures[i][j] == 1)
         figures[i][j]->setPixmap(White_Pawn);
    if(Figures[i][j] == 2)
        figures[i][j]->setPixmap(White_Horse);
    if(Figures[i][j] == 3)
        figures[i][j]->setPixmap(White_Rook);
    if(Figures[i][j] == 4)
        figures[i][j]->setPixmap(White_Officer);
    if(Figures[i][j] == 5)
        figures[i][j]->setPixmap(White_Queen);
    if(Figures[i][j] == 6)
        figures[i][j]->setPixmap(White_King);

    if(Figures[i][j] == 11)
         figures[i][j]->setPixmap(Black_Pawn);
    if(Figures[i][j] == 12)
        figures[i][j]->setPixmap(Black_Horse);
    if(Figures[i][j] == 13)
        figures[i][j]->setPixmap(Black_Rook);
    if(Figures[i][j] == 14)
        figures[i][j]->setPixmap(Black_Officer);
    if(Figures[i][j] == 15)
        figures[i][j]->setPixmap(Black_Queen);
    if(Figures[i][j] == 16)
        figures[i][j]->setPixmap(Black_King);
}


