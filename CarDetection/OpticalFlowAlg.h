#pragma once

#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iterator>
#include <vector>
#include <cmath>

using namespace std;

class TrackedRectangle {
	cv::Rect sRectangle;
	cv::Scalar color;
	int containing_points = 0;
	double density;

public:

	vector<cv::Point2f> points;
	TrackedRectangle(cv::Rect sRectangle, cv::Scalar color = cv::Scalar(0, 0, 0))
		: sRectangle(sRectangle), color(color) {};

	TrackedRectangle(int x, int y, int width, int height, cv::Scalar color = cv::Scalar(0, 0, 0))
		: sRectangle(cv::Rect(x, y, width, height)), color(color) {};

	bool ifWillBeOverlaping(cv::Point2f pForRect, int threshold);
	void increase_points() { containing_points++; };
	void optymalize();
	void merge(TrackedRectangle rect);

	cv::Rect getRect() { return sRectangle; }
	cv::Scalar getColor() { return color; }
	double getDensity() {
		double h = sRectangle.height; double w = sRectangle.height;
		double area = h * w; density = containing_points / area; return density * 1000;
	}
	int getContainingP() { return containing_points; };
};

double length_of_line(cv::Point2f p1, cv::Point2f p2);
void findRects(const vector<cv::Point2f> &point, vector<TrackedRectangle> &rectangles, int threshold, int overlaping);
bool compare_for_y(const cv::Point2f &p1, const cv::Point2f &p2);
bool compare_for_x(const cv::Point2f &p1, const cv::Point2f &p2);
bool mergeRectanglesWithSmallArea(TrackedRectangle rect1, TrackedRectangle rect2);




