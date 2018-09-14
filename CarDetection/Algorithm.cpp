#include "Algorithm.h"
#include <qDebug.h>
#include <opencv2/core/cuda_types.hpp>

SVM_Algorithm * SVM_Algorithm::instance;

SVM_Algorithm * SVM_Algorithm::getInstance() {

	if (instance == 0) {
		instance = new SVM_Algorithm();
	}
	return instance;
}

SVM_Algorithm::SVM_Algorithm() {

	myhog.winSize = cv::Size(40, 40);
	myhog.free_coef = 0;

	std::vector <float> hog_detector;
	mysvm = cv::ml::StatModel::load<cv::ml::SVM>("C:\\projects\\Car_Detection\\QTpart\\CarDetection\\trainedclassifier.yml");
	this->getSVMDetector(mysvm, hog_detector); // get
	//printHOGParams(myhog);

	myhog.setSVMDetector(hog_detector);
}

void SVM_Algorithm::getSVMDetector(const cv::Ptr<cv::ml::SVM> &svm, std::vector<float>&hog_detector) {
	cv::Mat sv = svm->getSupportVectors(); // segmentation fault

	cv::Mat alpha, svidx;
	double rho = svm->getDecisionFunction(0, alpha, svidx);

	hog_detector.clear();

	hog_detector.resize(sv.cols + 1);
	memcpy(&hog_detector[0], sv.ptr(), sv.cols * sizeof(hog_detector[0]));
	hog_detector[sv.cols] = (float)-rho;

}

void SVM_Algorithm::FrameAnalisys(cv::Mat *img, int* detectcounts) {
	//myhog.detectROI(,,);
	cv::cvtColor(*img, *img, CV_RGB2GRAY);

	std::vector<cv::Rect>  cars;

	this->myhog.detectMultiScale(*img, cars);
	*detectcounts = (int)cars.size();
	for(uint i = 0; i < cars.size(); i++) {
		cv::rectangle(*img, cars[i], cv::Scalar(150, 100, 100));
		//Car new_car(cars[i],img);
		//obj_cars.push_back(new_car);
	}
	cv::cvtColor(*img, *img, CV_GRAY2RGB);
}

// add optical flow instance
OpticalFlow_Algorithm* OpticalFlow_Algorithm::OFinstance;

OpticalFlow_Algorithm* OpticalFlow_Algorithm::getInstance() {
	if (OFinstance == 0) {
		OFinstance = new OpticalFlow_Algorithm();
	}
	return OFinstance;
}

OpticalFlow_Algorithm::OpticalFlow_Algorithm() : firstTime(true), showOutput(true),
min_features(50), max_features(500), quality_level(0.01), min_distance(3) {}

OpticalFlow_Algorithm::~OpticalFlow_Algorithm() {}

void OpticalFlow_Algorithm::FrameAnalisys(cv::Mat *img, int* detectcounts) {
	cv::Mat output;
	cv::cvtColor(*img, *img, CV_RGB2GRAY);

	process(img, output,detectcounts);
	qDebug() << "after processing";

	*img = output;
	//cv::cvtColor(*img, *img, CV_RGB2GRAY);
	if (!img->empty()) {

	}
}

void OpticalFlow_Algorithm::setPrevFrame(cv::Mat img_input) {
	cv::cvtColor(img_input,img_input,CV_RGB2GRAY);
	img_input.copyTo(this->img_input_prev);
	if (this->img_input_prev.empty()) {
		qDebug() << "observation is not working";
	}
}

void OpticalFlow_Algorithm::process(cv::Mat *img_input, cv::Mat &img_output, int *detectcounts) {
	//imshow("test1",*img_input);
	vector<TrackedRectangle> rectangles;
	qDebug() << "start process " << img_input;
	qDebug() << "cols input: " << img_input->cols << "rows input: " << img_input->rows;

	if (img_input->empty()) {
		return;
		qDebug() << "return";
	}
	if (this->img_input_prev.empty())
	{
		img_input->copyTo(this->img_input_prev);
		qDebug() << "prev";
		return;
	}
	else {
		cv::goodFeaturesToTrack(
			*img_input,     // The input 8-bit or floating-point 32-bit, single-channel image
			features,      // the output detected features
			max_features,  // the maximum number of features
			quality_level, // quality level
			min_distance   // The minimum possible Euclidean distance between the returned corners
		);

		//imshow("test1",*img_input);
		//qDebug() << "after goodFeaturesToTrack";
		points[0].insert(points[0].end(), features.begin(), features.end());
		initial.insert(initial.end(), features.begin(), features.end());


		cv::calcOpticalFlowPyrLK(
			img_input_prev, // prevImg � The first 8-bit single-channel or 3-channel input image.
			*img_input,      // nextImg � The second input image of the same size and the same type as prevImg.
			points[0],      // prevPts � Vector of points for which the flow needs to be found.
			points[1],      // nextPts � The output vector of points containing the calculated new positions of the input features in the second image.
			status,         // status  � The output status vector. Each element of the vector is set to 1 if the flow for the corresponding features has been found, 0 otherwise.
			err
		);
		//imshow("test1",*img_input);
		qDebug() << "after calcOpticalFlowPyrLK";
		int k = 0;
		for (uint i = 0; i < points[1].size(); i++)
		{
			//qDebug() << "i: " << i << "points.size:" <<points[1].size();
			// do we keep this point?
			if (status[i] && (abs(points[0][i].x - points[1][i].x) + (abs(points[0][i].y - points[1][i].y)) > 2))
			{
				// keep this point in vector
				initial[k] = initial[i];
				points[1][k++] = points[1][i];
			}
		}
		//qDebug() << "after point in vector";
		//imshow("test1",*img_input);
		points[1].resize(k);
		initial.resize(k);
		cv::Mat img_good_features;
		img_input->convertTo(*img_input, CV_8UC3);
		cv::cvtColor(*img_input, img_good_features, CV_GRAY2RGB);

		qDebug() << "after cvtColor";

		for (uint i = 0; i < points[1].size(); i++) {
			////qDebug() << i <<"points[1].size(): "<< points[1].size();
			cv::Point2f p1 = points[1][i];
			// cv::Point2f p2 = points[0][i];
			// cv::Point2f p3 = points[3][i];
			cv::circle(img_good_features, p1, 1, cv::Scalar(i), 1, 8);

		}
		//imshow("test1",*img_input);
		////qDebug() << "after circles";

		findRects(points[1], rectangles, 40, 20);
		////qDebug() << "after findRects";
		*detectcounts = (int)rectangles.size();
		for (int n = 0; n < rectangles.size(); n++) {
			cv::rectangle(img_good_features, rectangles[n].getRect(), rectangles[n].getColor());

		}

		qDebug() << "after for with rects";

		//cv::cvtColor(*img_input, img_good_features, CV_RGB2GRAY);
		std::swap(points[1], points[0]);
		img_input->copyTo(img_input_prev);
		img_good_features.copyTo(img_output);
		// imshow("img_output",img_output);
	}
}

NoneAlg * NoneAlg::NAinstance;

NoneAlg::NoneAlg() {};
NoneAlg::~NoneAlg() {};

NoneAlg * NoneAlg::getInstance() {
	if (NAinstance == 0) {
		NAinstance=new NoneAlg();
	}
	return NAinstance;
}

void NoneAlg::FrameAnalisys(cv::Mat * img, int* detectcounts) { detectcounts = 0; }
