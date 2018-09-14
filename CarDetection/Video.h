#pragma once
#include "Observer.h"
#include "Algorithm.h"
//#include "MainWindow.h"
#include "opticalflowalg.h"
#include <opencv2/core.hpp>
#include <opencv2/video.hpp>
#include <qdebug.h>
#include <qthread.h>
#include <map>
#include <QPainter>


class Video :  public Observer
{
	//Q_OBJECT
private: 

	static Video * instance;
	Algorithm *Ialgorithm;

	explicit Video(QWidget *parent = 0);
	explicit Video(const Video&);
	~Video();
	int flagopened = 0;
public:
	std::map<QString, Algorithm*> algorithms;
	static Video* getInstance(); // Singleton

	void aboutObject() { qDebug() << "object singleton" << this; }
	void startVideo();
	void close();
	//void SetWindow(MainWindow *wm);
	void Setalgorithm(Algorithm *Newalgorithm);
	void update(QString name);
	void LoadVideo(std::string folder);
	bool isOpened();
	bool openOk;
	int retcars();
	void checkcars(int cars);

	int numbofcars;
	cv::Mat prevFrame;
	cv::Mat Frame;
	cv::VideoCapture video;
	//MainWindow *mw;
public slots:
	QImage updateFrame();

};


QImage Mat2QImage(cv::Mat &src);

