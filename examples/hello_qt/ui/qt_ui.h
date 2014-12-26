#ifndef HELLO_QT_H
#define HELLO_QT_H

#include <QtGui/QWidget>
#include "ui_qt_ui.h"

class hello_qt : public QWidget
{
    Q_OBJECT

public:
    hello_qt(QWidget *parent = 0);
    ~hello_qt();

    Ui::hello_qtClass ui;
};

#endif // HELLO_QT_H
