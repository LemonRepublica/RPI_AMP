/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDial>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QDial *dial;
    QDial *dial_4;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QDial *dial_5;
    QDial *dial_6;
    QDial *dial_7;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QDial *dial_2;
    QDial *dial_3;
    QLabel *label;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(500, 300);
        MainWindow->setMinimumSize(QSize(500, 300));
        MainWindow->setMaximumSize(QSize(500, 300));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setMinimumSize(QSize(500, 300));
        centralWidget->setMaximumSize(QSize(500, 300));
        verticalLayoutWidget_2 = new QWidget(centralWidget);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(20, 30, 111, 271));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(verticalLayoutWidget_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout_2->addWidget(pushButton);

        pushButton_2 = new QPushButton(verticalLayoutWidget_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        verticalLayout_2->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(verticalLayoutWidget_2);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        verticalLayout_2->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(verticalLayoutWidget_2);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        verticalLayout_2->addWidget(pushButton_4);

        pushButton_5 = new QPushButton(verticalLayoutWidget_2);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        verticalLayout_2->addWidget(pushButton_5);

        dial = new QDial(centralWidget);
        dial->setObjectName(QStringLiteral("dial"));
        dial->setGeometry(QRect(330, 10, 77, 69));
        dial_4 = new QDial(centralWidget);
        dial_4->setObjectName(QStringLiteral("dial_4"));
        dial_4->setGeometry(QRect(330, 130, 77, 69));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(230, 210, 261, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        dial_5 = new QDial(horizontalLayoutWidget);
        dial_5->setObjectName(QStringLiteral("dial_5"));

        horizontalLayout->addWidget(dial_5);

        dial_6 = new QDial(horizontalLayoutWidget);
        dial_6->setObjectName(QStringLiteral("dial_6"));

        horizontalLayout->addWidget(dial_6);

        dial_7 = new QDial(horizontalLayoutWidget);
        dial_7->setObjectName(QStringLiteral("dial_7"));

        horizontalLayout->addWidget(dial_7);

        horizontalLayoutWidget_2 = new QWidget(centralWidget);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(240, 70, 251, 71));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        dial_2 = new QDial(horizontalLayoutWidget_2);
        dial_2->setObjectName(QStringLiteral("dial_2"));

        horizontalLayout_2->addWidget(dial_2);

        dial_3 = new QDial(horizontalLayoutWidget_2);
        dial_3->setObjectName(QStringLiteral("dial_3"));

        horizontalLayout_2->addWidget(dial_3);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(190, 20, 121, 31));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Run", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "Distortion", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindow", "Delay", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("MainWindow", "Reverb", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("MainWindow", "EQ", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "NAME", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
