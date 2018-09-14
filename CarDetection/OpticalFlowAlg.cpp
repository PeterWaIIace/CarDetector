#include "OpticalFlowAlg.h"
#include "QDebug"


double length_of_line(cv::Point2f p1, cv::Point2f p2) {

	return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));

}

void findRects(const vector<cv::Point2f> &point, vector<TrackedRectangle> &rectangles, int threshold, int overlaping) {
	int rect_num = 0;
	bool detected = false;

	for (int n = 0; n < point.size(); n++) {
		if (n == 0) {
			//qDebug() << n << "point.size: " << point.size();
			TrackedRectangle new_rect(point[n].x - 20, point[n].y - 20, threshold, threshold);
			rectangles.push_back(new_rect);
			rect_num += 1;
		}
		else {
			//qDebug() << n << "point.size: " << point.size();
			for (int j = 0; j < rect_num; j++) {
				detected = rectangles[j].ifWillBeOverlaping(point[n], overlaping);
				if (detected) {
					rectangles[j].points.push_back(point[n]);
					rectangles[j].increase_points();
					break;
				}
			}
			if (!detected) {
				rect_num++;
				TrackedRectangle new_rect(point[n].x - threshold / 2, point[n].y - threshold / 2, threshold, threshold, cv::Scalar(0, 0, rect_num * 15));
				new_rect.points.push_back(point[n]);
				rectangles.push_back(new_rect);
			}
			else {}
		}
	}
	for (int j = 0; j < rectangles.size(); j++) {
		//qDebug() << j << "rectangles.size(): " << rectangles.size();
		if (rectangles[j].getContainingP() < 25) {
			j = distance(rectangles.begin(), rectangles.erase(rectangles.begin() + j));
			j--;
		}
	}
	for (int j = 0; j < rectangles.size(); j++) { rectangles[j].optymalize(); }
	qDebug() << "after optymalize ";
	if (0 < rectangles.size()) {
		//qDebug() << rectangles.size() << " = rectangles.size()";
		for (int j = 0; j < rectangles.size() - 1; j++) {
			//qDebug() << j << "j rectangles.size(): " << rectangles.size();
			for (int n = 1; n < rectangles.size(); n++) {
				//qDebug() << n << "n rectangles.size(): " << rectangles.size();
				if (mergeRectanglesWithSmallArea(rectangles[j], rectangles[n])) {
					rectangles[j].optymalize();
					n = distance(rectangles.begin(), rectangles.erase(rectangles.begin() + n));
					n--;
				}
			}
		}
	}
	qDebug() << "find rect finish";
}

bool TrackedRectangle::ifWillBeOverlaping(cv::Point2f pForRect, int threshold) {
	cv::Rect new_rect(pForRect.x - threshold / 2, pForRect.y - threshold / 2, threshold, threshold);
	cv::Rect overlaping = (sRectangle & new_rect);
	if (overlaping.area() == 0) {
		return false;
	}
	else {
		return true;
	}
}

void TrackedRectangle::optymalize() {
	std::vector<cv::Point2f>::iterator result;
	int at;
	double minx = 0, miny = 0, maxx = 0, maxy = 0, x = 0, y = 0;
	double h = sRectangle.height;
	double w = sRectangle.height;

	double area = h * w;

	double density = containing_points / area;
	result = max_element(points.begin(), points.end(), compare_for_y);
	at = distance(points.begin(), result);
	if (points.size() > 0) {
		maxy = points[at].y;
	}
	result = min_element(points.begin(), points.end(), compare_for_y);
	at = distance(points.begin(), result);
	if (points.size() > 0) {
		miny = points[at].y;
	}
	result = max_element(points.begin(), points.end(), compare_for_x);
	at = distance(points.begin(), result);
	if (points.size() > 0) {
		maxx = points[at].x;
	}
	result = min_element(points.begin(), points.end(), compare_for_x);
	at = distance(points.begin(), result);
	if (points.size() > 0) {
		minx = points[at].x;
	}
	w = maxx - minx; h = maxy - miny;
	if (density * 1000 > 50) {
		sRectangle.x = minx;
		sRectangle.y = miny;
		sRectangle.width = w;
		sRectangle.height = h;
	}
	else {
		sRectangle.x = 0;
		sRectangle.y = 0;
		sRectangle.width = 0;
		sRectangle.height = 0;
	}
}
void TrackedRectangle::merge(TrackedRectangle rect) {
	containing_points += rect.getContainingP();
	sRectangle |= rect.getRect();
}

bool mergeRectanglesWithSmallArea(TrackedRectangle rect1, TrackedRectangle rect2) {
	if (rect2.getRect().area() > 0)
		//cout << rect2.getRect().area() << " " << rect2.getDensity() << endl;
		if ((rect2.getRect().area() < 1500) && (rect2.getDensity() < 100)) {
			if (rect1.ifWillBeOverlaping(cv::Point(rect2.getRect().x, rect2.getRect().y), 60)) {
				rect1.merge(rect2);
				return true;
			}
			//else if((rect2.getRect().area() > 1600) &&(rect2.getDensity()<50)){
			//    rect1.merge(rect2);
			//    return true;
			//}
			else {
				return false;
			}
		} return false;
}

bool compare_for_y(const cv::Point2f &p1, const cv::Point2f &p2) {
	if (p1.y < p2.y) {
		return true;
	}
	else {
		return false;
	}
}
bool compare_for_x(const cv::Point2f &p1, const cv::Point2f &p2) {
	if (p1.x < p2.x) {
		return true;
	}
	else {
		return false;
	}
}