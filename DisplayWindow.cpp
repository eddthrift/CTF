#include "DisplayWindow.h"
#include "ui_DisplayWindow.h"
#include "Game.h"

#include <QPainter>
#include <QTimer>
#include <QPixmap>
#include <iostream>

DisplayWindow::DisplayWindow(Game *game, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayWindow)
{

    ui->setupUi(this);
    oDisplayGame = game;                                                                          //Sets the field from the arguement as a private data member

    this->setGeometry(382, 40, oDisplayGame->GetWidth()*10, oDisplayGame->GetLength()*10);            //Sets position and size of window

    oTimer = new QTimer(this);                                                                          //Creates and starts timer to update display window
    connect(oTimer, SIGNAL(timeout()), this, SLOT(update()));
    oTimer->start(10);
}

DisplayWindow::~DisplayWindow()
{
    delete ui;
}

void DisplayWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);                                                                             //Creates painter and draws field
    painter.fillRect(QRect(0,0,oDisplayGame->GetWidth()*10, oDisplayGame->GetLength()*10), Qt::green);
    painter.drawLine(oDisplayGame->GetWidth()*5, 0, oDisplayGame->GetWidth()*5, oDisplayGame->GetLength()*10);

    QPixmap redAtt(":/images/RedAtt.png");                                                              //Loads images used as QPixmaps
    QPixmap redDef(":/images/RedDef.png");
    QPixmap redTag(":/images/RedTag.png");
    QPixmap redFlag(":/images/RedFlag.png");
    QPixmap blueAtt(":/images/BlueAtt.png");
    QPixmap blueDef(":/images/BlueDef.png");
    QPixmap blueTag(":/images/BlueTag.png");
    QPixmap blueFlag(":/images/BlueFlag.png");

    QPixmap flagRed(":/images/FlagRed.png");
    QPixmap flagBlue(":/images/FlagBlue.png");
    QPixmap redBase(":/images/RedBase.png");
    QPixmap blueBase(":/images/BlueBase.png");

    painter.drawPixmap(oDisplayGame->GetBlueFlagPos().GetX()*10 - 20, oDisplayGame->GetBlueFlagPos().GetY()*10 - 20, 40, 40, blueBase); //Draws bases
    painter.drawPixmap(oDisplayGame->GetRedFlagPos().GetX()*10 - 20, oDisplayGame->GetRedFlagPos().GetY()*10 - 20, 40, 40, redBase);

    for(int i = 0; i < oDisplayGame->GetPlayerNum()*2; i++){//DRAW PLAYER ICONS
        Player drawPlayer = oDisplayGame->GetPlayer(i);
        if(drawPlayer.GetTeam() == false){                 //if RED team
            if(drawPlayer.GetAttacker() == true){
                if(drawPlayer.GetIsTagged() == true){      //if tagged player
                    painter.drawPixmap(drawPlayer.GetPosition().GetX()*10 - 8, drawPlayer.GetPosition().GetY()*10 - 8, 16, 16, redTag);
                }
                else if(drawPlayer.GetHasFlag() == true){  //if has flag
                    painter.drawPixmap(drawPlayer.GetPosition().GetX()*10 - 8, drawPlayer.GetPosition().GetY()*10 - 8, 16, 16, redFlag);
                }
                else{                                      //active player
                    painter.drawPixmap(drawPlayer.GetPosition().GetX()*10 - 8, drawPlayer.GetPosition().GetY()*10 - 8, 16, 16, redAtt);
                }
            }
            else{                                          //defender
                painter.drawPixmap(drawPlayer.GetPosition().GetX()*10 - 8, drawPlayer.GetPosition().GetY()*10 - 8, 16, 16, redDef);
            }
        }
        else{                                              //if BLUE team
            if(drawPlayer.GetAttacker() == true){
                if(drawPlayer.GetIsTagged() == true){      //if tagged player
                    painter.drawPixmap(drawPlayer.GetPosition().GetX()*10 - 8, drawPlayer.GetPosition().GetY()*10 - 8, 16, 16, blueTag);
                }
                else if(drawPlayer.GetHasFlag() == true){  //if has flag
                    painter.drawPixmap(drawPlayer.GetPosition().GetX()*10 - 8, drawPlayer.GetPosition().GetY()*10 - 8, 16, 16, blueFlag);
                }
                else{                                      //active player
                    painter.drawPixmap(drawPlayer.GetPosition().GetX()*10 - 8, drawPlayer.GetPosition().GetY()*10 - 8, 16, 16, blueAtt);
                }
            }
            else{                                          //defender
                painter.drawPixmap(drawPlayer.GetPosition().GetX()*10 - 8, drawPlayer.GetPosition().GetY()*10 - 8, 16, 16, blueDef);
            }
        }
    }

    if(oDisplayGame->GetBlueFlagHeld() == false){  //Shows flags if not held
        painter.drawPixmap(oDisplayGame->GetBlueFlagPos().GetX()*10 - 15, oDisplayGame->GetBlueFlagPos().GetY()*10 - 15, 30, 30, flagBlue);
    }
    if(oDisplayGame->GetRedFlagHeld() == false){
        painter.drawPixmap(oDisplayGame->GetRedFlagPos().GetX()*10 - 15, oDisplayGame->GetRedFlagPos().GetY()*10 - 15, 30, 30, flagRed);
    }

    QFont winFont = painter.font();  //Creates and writes text, showing the winner.
    winFont.setPointSize(30);
    painter.setFont(winFont);

    if((oDisplayGame->GetBlueWin() == true) && (oDisplayGame->GetRedWin() == false)){
        painter.setPen(Qt::blue);
        painter.drawText(30, 60, "Blue Team Wins!");
    }
    if((oDisplayGame->GetRedWin() == true) && (oDisplayGame->GetBlueWin() == false)){
        painter.setPen(Qt::red);
        painter.drawText(30, 60, "Red Team Wins!");
    }
    if((oDisplayGame->GetBlueWin() == true) && (oDisplayGame->GetRedWin() == true)){
        painter.setPen(Qt::magenta);
        painter.drawText(30,60, "Draw!");
    }
}




