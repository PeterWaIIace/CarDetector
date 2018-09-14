#ifndef FACADE
#define FACADE

#include "Video.h"
#include "qstring.h"
//#include "MainWindow.h"
//#include "Observer.h"

class Facade 
{
public:
	static Facade *instanceF;
	static Facade* getInstance();
	/////////// for playing video ///////////////
	void initVideo();

	void loadVideo(QString file);
	bool isOpened();
	void startVideo();
	void updateFrame(QImage &img);
	void closeVideo();
	int retNumbCars();

private:

	//void addWatched(MainWindow *mw);
	Video *video;
	Facade();
	~Facade();
};

#endif