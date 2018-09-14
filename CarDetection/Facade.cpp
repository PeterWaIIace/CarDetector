#include "Facade.h"

Facade::Facade() {
	this->initVideo();
};

Facade* Facade::instanceF;

Facade* Facade::getInstance(){

	if (instanceF == 0) {
		instanceF = new Facade();
	}
	return instanceF;
}
/////////// for playing video ///////////////
void Facade::initVideo() {
	video = Video::getInstance();
}
void Facade::loadVideo(QString file) {
	std::string strfile = file.toStdString();
	video->LoadVideo(strfile);
}
void Facade::startVideo(){
	video->startVideo();
}

void Facade::updateFrame(QImage &img) {
	img = video->updateFrame();
}
void Facade::closeVideo() {
	video->close();
}
int Facade::retNumbCars(){
	return video->retcars();
}

bool Facade::isOpened() {
		return video->isOpened();
}
/*void Facade::addWatched(MainWindow *mw) {

    mw->addObserver(video);

}*/
