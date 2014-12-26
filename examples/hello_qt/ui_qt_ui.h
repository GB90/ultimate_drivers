/********************************************************************************
** Form generated from reading UI file 'qt_ui.ui'
**
** Created: Fri Dec 26 11:46:48 2014
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QT_UI_H
#define UI_QT_UI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_hello_qtClass
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_6;
    QLineEdit *lineEdit;

    void setupUi(QWidget *hello_qtClass)
    {
        if (hello_qtClass->objectName().isEmpty())
            hello_qtClass->setObjectName(QString::fromUtf8("hello_qtClass"));
        hello_qtClass->resize(160, 160);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(hello_qtClass->sizePolicy().hasHeightForWidth());
        hello_qtClass->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("\346\226\207\346\263\211\351\251\277\347\202\271\351\230\265\346\255\243\351\273\221"));
        font.setPointSize(12);
        hello_qtClass->setFont(font);
        hello_qtClass->setWindowTitle(QString::fromUtf8("hello_qt"));
        pushButton = new QPushButton(hello_qtClass);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(10, 60, 41, 30));
        pushButton->setFocusPolicy(Qt::NoFocus);
        pushButton->setCheckable(false);
        pushButton_4 = new QPushButton(hello_qtClass);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(10, 90, 41, 30));
        pushButton_5 = new QPushButton(hello_qtClass);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(10, 120, 41, 30));
        pushButton_7 = new QPushButton(hello_qtClass);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(110, 60, 41, 30));
        pushButton_8 = new QPushButton(hello_qtClass);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(110, 90, 41, 30));
        pushButton_9 = new QPushButton(hello_qtClass);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setGeometry(QRect(110, 120, 41, 30));
        pushButton_2 = new QPushButton(hello_qtClass);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(60, 60, 41, 30));
        pushButton_3 = new QPushButton(hello_qtClass);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(60, 90, 41, 30));
        pushButton_6 = new QPushButton(hello_qtClass);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(60, 120, 41, 30));
        lineEdit = new QLineEdit(hello_qtClass);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(10, 10, 141, 41));

        retranslateUi(hello_qtClass);

        QMetaObject::connectSlotsByName(hello_qtClass);
    } // setupUi

    void retranslateUi(QWidget *hello_qtClass)
    {
        pushButton->setText(QApplication::translate("hello_qtClass", "1", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("hello_qtClass", "4", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("hello_qtClass", "7", 0, QApplication::UnicodeUTF8));
        pushButton_7->setText(QApplication::translate("hello_qtClass", "3", 0, QApplication::UnicodeUTF8));
        pushButton_8->setText(QApplication::translate("hello_qtClass", "6", 0, QApplication::UnicodeUTF8));
        pushButton_9->setText(QApplication::translate("hello_qtClass", "9", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("hello_qtClass", "2", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("hello_qtClass", "5", 0, QApplication::UnicodeUTF8));
        pushButton_6->setText(QApplication::translate("hello_qtClass", "8", 0, QApplication::UnicodeUTF8));
        lineEdit->setInputMask(QString());
        lineEdit->setText(QApplication::translate("hello_qtClass", "0", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(hello_qtClass);
    } // retranslateUi

};

namespace Ui {
    class hello_qtClass: public Ui_hello_qtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT_UI_H
