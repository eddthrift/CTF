#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H

#include <QMainWindow>
#include "DisplayWindow.h"
#include <QErrorMessage>
#include <QTimer>
#include "Game.h"

namespace Ui {
class ControlWindow;
}

class ControlWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ControlWindow(QWidget *parent = 0);
    ~ControlWindow();

private slots:
    void on_runButton_clicked();
    void Simulate(); 

    void on_pauseButton_clicked();

private:
    Ui::ControlWindow *ui;
    QErrorMessage *oError;
    DisplayWindow *oDisplay;
    QTimer *oTimer;
    Game *oPlayGame;
    Field *oField;

};

#endif // CONTROLWINDOW_H
