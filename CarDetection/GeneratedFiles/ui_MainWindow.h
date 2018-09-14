/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QAction *actionabout_CarDetector;
    QAction *actionExit;
    QAction *actionsomething;
    QAction *OpenFile;
    QAction *actionExit_2;
    QAction *actionOpen;
    QAction *actionOpen_2;
    QWidget *centralWidget;
    QLabel *mylabel;
    QComboBox *comboBox;
    QPushButton *play;
    QPushButton *stop;
    QPushButton *clearvideo;
    QCustomPlot *graph;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuhelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QStringLiteral("MainWindowClass"));
        MainWindowClass->resize(480, 563);
        actionabout_CarDetector = new QAction(MainWindowClass);
        actionabout_CarDetector->setObjectName(QStringLiteral("actionabout_CarDetector"));
        actionabout_CarDetector->setCheckable(true);
        actionExit = new QAction(MainWindowClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionExit->setCheckable(true);
        QIcon icon;
        icon.addFile(QStringLiteral("../../../../Pictures/AGH.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon);
        actionsomething = new QAction(MainWindowClass);
        actionsomething->setObjectName(QStringLiteral("actionsomething"));
        OpenFile = new QAction(MainWindowClass);
        OpenFile->setObjectName(QStringLiteral("OpenFile"));
        OpenFile->setCheckable(true);
        actionExit_2 = new QAction(MainWindowClass);
        actionExit_2->setObjectName(QStringLiteral("actionExit_2"));
        actionOpen = new QAction(MainWindowClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionOpen_2 = new QAction(MainWindowClass);
        actionOpen_2->setObjectName(QStringLiteral("actionOpen_2"));
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        mylabel = new QLabel(centralWidget);
        mylabel->setObjectName(QStringLiteral("mylabel"));
        mylabel->setGeometry(QRect(20, 50, 320, 240));
        mylabel->setFrameShape(QFrame::StyledPanel);
        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(20, 10, 131, 22));
        play = new QPushButton(centralWidget);
        play->setObjectName(QStringLiteral("play"));
        play->setGeometry(QRect(360, 50, 101, 31));
        stop = new QPushButton(centralWidget);
        stop->setObjectName(QStringLiteral("stop"));
        stop->setGeometry(QRect(360, 90, 101, 31));
        clearvideo = new QPushButton(centralWidget);
        clearvideo->setObjectName(QStringLiteral("clearvideo"));
        clearvideo->setGeometry(QRect(360, 130, 101, 31));
        graph = new QCustomPlot(centralWidget);
        graph->setObjectName(QStringLiteral("graph"));
        graph->setGeometry(QRect(10, 300, 451, 201));
        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 480, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuhelp = new QMenu(menuBar);
        menuhelp->setObjectName(QStringLiteral("menuhelp"));
        MainWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindowClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindowClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuhelp->menuAction());
        menuFile->addAction(actionOpen_2);
        menuhelp->addAction(actionabout_CarDetector);

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "MainWindow", Q_NULLPTR));
        actionabout_CarDetector->setText(QApplication::translate("MainWindowClass", "about CarDetector", Q_NULLPTR));
        actionExit->setText(QApplication::translate("MainWindowClass", "Exit", Q_NULLPTR));
        actionsomething->setText(QApplication::translate("MainWindowClass", "something", Q_NULLPTR));
        OpenFile->setText(QApplication::translate("MainWindowClass", "Open File", Q_NULLPTR));
        actionExit_2->setText(QApplication::translate("MainWindowClass", "Exit", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("MainWindowClass", "Open", Q_NULLPTR));
        actionOpen_2->setText(QApplication::translate("MainWindowClass", "Open", Q_NULLPTR));
        mylabel->setText(QString());
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindowClass", "None", Q_NULLPTR)
         << QApplication::translate("MainWindowClass", "SVM", Q_NULLPTR)
         << QApplication::translate("MainWindowClass", "Optical Flow", Q_NULLPTR)
        );
        play->setText(QApplication::translate("MainWindowClass", "Play", Q_NULLPTR));
        stop->setText(QApplication::translate("MainWindowClass", "Stop", Q_NULLPTR));
        clearvideo->setText(QApplication::translate("MainWindowClass", "Clear Video", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindowClass", "File", Q_NULLPTR));
        menuhelp->setTitle(QApplication::translate("MainWindowClass", "help", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
