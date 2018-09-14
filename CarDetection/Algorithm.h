#pragma once

#include <opencv2/ml.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <vector>
#include <QString>
#include "opticalflowalg.h"
#include <opencv2/core/cuda.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#define TRAINEDSVM "trainedclassifier.yml"

class Algorithm
{
public:
	virtual void FrameAnalisys(cv::Mat *img, int *detectcounts) = 0;
};

class SVM_Algorithm : public Algorithm
{
public:
	QString name = "SVM";

	static SVM_Algorithm* getInstance();
	void FrameAnalisys(cv::Mat *img, int *detectcounts)override;

private:
	static SVM_Algorithm * instance;
	cv::HOGDescriptor myhog;
	cv::Ptr<cv::ml::SVM> mysvm;

	SVM_Algorithm();
	SVM_Algorithm(SVM_Algorithm&) {}
	void getSVMDetector(const cv::Ptr<cv::ml::SVM> &svm, std::vector<float>&hog_detector);
};
using namespace std;

class OpticalFlow_Algorithm : public Algorithm
{
private:
	static OpticalFlow_Algorithm * OFinstance;
	bool firstTime, showOutput;
	int min_features, max_features, min_distance;
	double quality_level;

	vector<cv::Point2f> corners;
	vector<cv::Point2f> points[2]; // tracked features from 0->1
	vector<cv::Point2f> initial;   // initial position of tracked points
	vector<cv::Point2f> features;
	std::vector<uchar> status; // status of tracked features
	std::vector<float> err;    // error in tracking
	cv::Mat img_input_prev;
	OpticalFlow_Algorithm();
	~OpticalFlow_Algorithm();
public:

	static OpticalFlow_Algorithm * getInstance();
	void FrameAnalisys(cv::Mat *img, int *detectcounts)override;
	void process(cv::Mat *img_input, cv::Mat &img_output, int *detectcounts);
	void setPrevFrame(cv::Mat img_input);
};

class NoneAlg : public Algorithm {
	private:
		NoneAlg();
		~NoneAlg();
		static NoneAlg *NAinstance;

	public:
		static NoneAlg *getInstance();
		void FrameAnalisys(cv::Mat *img, int *detectcounts)override;

};