#include "ControlWindow.h"
#include "ui_ControlWindow.h"
#include "Game.h"
#include <QIntValidator>
#include <QDoubleValidator>

ControlWindow::ControlWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ControlWindow)
{
    ui->setupUi(this);
    ui->runButton->setText("Run Simulation");                        //Sets control window objects to default values
    ui->playerNumEdit->setText("2");
    ui->playerNumEdit->setValidator(new QIntValidator(1,30,this));   //Stops text being entered
    ui->speedEdit->setText("5");
    ui->speedEdit->setValidator(new QDoubleValidator(0.1,30,3,this));
    ui->defSpeedEdit->setText("0.90");
    ui->defSpeedEdit->setValidator(new QDoubleValidator(0.1,2,3,this));
    ui->lengthEdit->setText("50");
    ui->lengthEdit->setValidator(new QIntValidator(30,100,this));
    ui->widthEdit->setText("100");
    ui->widthEdit->setValidator(new QIntValidator(40,200,this));

    oPlayGame = new Game();
    oField = new Field();
    oDisplay = new DisplayWindow(oPlayGame);

    this->setGeometry(40, 40, 332, 221);                            //Sets position and geometry of the control window

    oTimer = new QTimer(this);                                      //Calls timer to run ControlWindow::Simulate()
    connect(oTimer, SIGNAL(timeout()), this, SLOT(Simulate()));
}

ControlWindow::~ControlWindow()
{
    delete oTimer;
    delete oDisplay;
    delete oPlayGame;
    delete ui;
    delete oError;
}

void ControlWindow::on_runButton_clicked(){
    oError = new QErrorMessage();                                   //Calls error message window

    if(oDisplay->isVisible()){
        oDisplay->hide();
    }

    int number = ui->playerNumEdit->text().toInt();                 //Converts values in lineEdits to variables to be used in the simulation
    double speed = ui->speedEdit->text().toDouble();
    double dSpeed = ui->defSpeedEdit->text().toDouble();
    int length = ui->lengthEdit->text().toInt();
    int width = ui->widthEdit->text().toInt();

    if ((number < 2) || (number > 10)){                             //If incorrect values entered, show error message
        oError->showMessage("Players per team must be between 2 and 10.");
        ui->playerNumEdit->setText("2");
    }
    else if((speed < 0.1) || (speed > 15.0)){
        oError->showMessage("Player speed must be between 0.1 and 15.");
        ui->speedEdit->setText("5");
    }
    else if((dSpeed < 0.01) || (dSpeed > 2.0)){
        oError->showMessage("Defender speed coefficient must be between 0.01 and 2.0.");
        ui->defSpeedEdit->setText("0.90");
    }
    else if((length < 30) || (length > 100 )){
        oError->showMessage("Length must be between 30 and 100.");
        ui->lengthEdit->setText("50");
    }
    else if((width < 40) || (width > 200 )){
        oError->showMessage("Width must be between 40 and 200.");
        ui->widthEdit->setText("100");
    }
    else{                                                           //Otherwise set field arguments
        oPlayGame->SetPlayerNum(number);
        oPlayGame->SetSize(width, length);
        oPlayGame->SetSpeed(speed, dSpeed);

        oPlayGame->CreatePlayers(number, oField);                          //Create players

        oDisplay = new DisplayWindow(oPlayGame);                   //Create and show display window

        oDisplay->show();

        oTimer->start(10);                                          //Start timer to run simulate

         ui->runButton->setText("Restart Sim");
    }
}


void ControlWindow::Simulate(){
    if(oPlayGame->GetRun() == true){                               //Runs Simulation
        oPlayGame->Simulate();
    }
}

void ControlWindow::on_pauseButton_clicked()                        //Pauses simulation
{
    if(oPlayGame->GetRun() == true){
        oPlayGame->SetRun(false);
    }
    else{
        oPlayGame->SetRun(true);
    }
}

