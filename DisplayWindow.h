#ifndef DISPLAYWINDOW_H
#define DISPLAYWINDOW_H

#include <QWidget>
#include "Game.h"
#include <QTimer>

namespace Ui {
class DisplayWindow;
}

class DisplayWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DisplayWindow(Game *oPlayfield, QWidget *parent = 0);
    ~DisplayWindow();

private slots:
    void paintEvent(QPaintEvent *);

    private:
    Ui::DisplayWindow *ui;
    Game *oDisplayGame;
    Field *oDisplayField;
    QTimer *oTimer;



};

#endif // DISPLAYWINDOW_H
