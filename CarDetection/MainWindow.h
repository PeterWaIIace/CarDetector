#pragma once
//#include "mainwindow.h"
#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include <qfiledialog.h>
#include <QString>
#include <qtimer.h>
#include <opencv2/core.hpp>
#include <opencv2/video.hpp>
#include <qmessagebox.h>
#include <vector>
#include "Facade.h"
#include "qthread.h"
#include "QCustomPlot.h"
//#include "Observer.h"
//#include <Video.h>

class MainWindow : public QMainWindow, public Watched
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	void setImageInLabel(QImage *image);
	void plot(QCustomPlot *plot);
	QString returnComboBoxState();

private slots:
	//void on_comboBox_activated(const QString &arg1);
	void update();
	void on_actionOpen_2_triggered();
	void on_play_pressed();
	void on_stop_clicked();
	void on_clearvideo_clicked();
	void on_comboBox_currentIndexChanged(const QString &arg1);
	void NotifyObserver();

private:
	std::vector<int> cars; // 
	int flagplay = 0;
	QTimer *timer;
	QString file; 
	QCustomPlot Customplot;
	Ui::MainWindowClass ui;
	Facade* player;
};

//void LoadVideo(cv::VideoCapture* video, QString folder);
