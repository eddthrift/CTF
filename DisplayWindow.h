#ifndef DISPLAYWINDOW_H
#define DISPLAYWINDOW_H

#include <QWidget>
#include "Field.h"
#include <QTimer>

namespace Ui {
class DisplayWindow;
}

class DisplayWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DisplayWindow(Field *oPlayfield, QWidget *parent = 0);
    ~DisplayWindow();

private slots:
    void paintEvent(QPaintEvent *);

    private:
    Ui::DisplayWindow *ui;
    Field *oDisplayField;
    QTimer *oTimer;



};

#endif // DISPLAYWINDOW_H
