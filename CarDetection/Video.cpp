#include "Video.h"

Video * Video::instance;

Video::Video(QWidget *parent) :Observer() {
		SVM_Algorithm *SVMinstance = SVM_Algorithm::getInstance();
		OpticalFlow_Algorithm *OFinstance = OpticalFlow_Algorithm::getInstance();
		NoneAlg *NAinstance = NoneAlg::getInstance();
		Video::algorithms["SVM"] = SVMinstance;
		Video::algorithms["Optical Flow"] = OFinstance;
		Video::algorithms["None"] = NAinstance;
		video = cv::VideoCapture();
		openOk = false;
		qDebug() << "setting up map: " << Video::algorithms["SVM"];
		//Video::algorithms["Optical Flow"] = OFinstance;
		//this->hog = hog;
}

Video::Video(const Video& Tocopy) {
	this->video = Tocopy.video;

}

Video* Video::getInstance() {
	// Singleton
	if (instance == 0) {
		instance = new Video();
	}
	return instance;
}

void Video::startVideo() {

}

QImage Video::updateFrame() {
	qDebug() << "strange";
	cv::Mat cvImage, outputIm;
	video.read(cvImage);
	if (cvImage.empty()) {
		qDebug() << "Empty! ImAGE";
		QImage empty;
		return empty;
	}
	else {

		if (this->Frame.empty()) {
			Frame = cvImage;
		}
		else {
			prevFrame = Frame;
			Frame = cvImage;
		}

		cv::resize(cvImage, cvImage, cv::Size(480, 320));
		if (Ialgorithm != OpticalFlow_Algorithm::getInstance()) {
			OpticalFlow_Algorithm::getInstance()->setPrevFrame(cvImage);
		}
		int detectcounts;
		Ialgorithm->FrameAnalisys(&cvImage, &detectcounts);
		checkcars(detectcounts);

		if (!cvImage.empty()) {
			cv::resize(cvImage, cvImage, cv::Size(320, 240));
			QImage myImage = Mat2QImage(cvImage);
			return myImage;
		}
		else {
			qDebug() << "Empty Image!";
		}
		QImage myImage = Mat2QImage(cvImage);
		return myImage;
	}
}

void Video::checkcars(int cars) {
	numbofcars = cars;
}

int Video::retcars() {
	return numbofcars;
}
void Video::close() {
	if (flagopened == 1) {
		//video.release();
	}

}

bool Video::isOpened() {
	if (video.isOpened()) {
		return true;
	}
	else {
		return false;
	}
}

void Video::Setalgorithm(Algorithm *Newalgorithm) {
	Ialgorithm = Newalgorithm;
}

//void Video::SetWindow(MainWindow *wm) {

//	this->mw = wm;
//}

void Video::update(QString name) {

	//QString name = this->mw->returnComboBoxState();
	//qDebug() << "algorithm: " << Video::algorithms[name];
	Setalgorithm(Video::algorithms[name]);

}

QImage Mat2QImage(cv::Mat &src) {
	std::cout << "Mat2QImage cols: " << src.cols << std::endl;
	std::cout << "Mat2QImage rows: " << src.rows << std::endl;
	QImage dest(src.cols, src.rows, QImage::Format_ARGB32);
	QRgb value;
	for (int x = 0; x < src.cols; x++) {
		for (int y = 0; y < src.rows; y++) {
			value = qRgba(src.at<cv::Vec3b>(y, x)[2], src.at<cv::Vec3b>(y, x)[1], src.at<cv::Vec3b>(y, x)[0], 255); // this is weird y x are fliped
			dest.setPixel(x, y, value);
		}
	}
	return dest;
}

Video::~Video()
{
}

void Video::LoadVideo(std::string folder) {
	//cv::String folder_cv = folder.c_str();
	//std::vector<cv::String> files;
	//glob(folder_cv, files);
	int flagopened = 1;
	video.open(folder);
}