#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

const int NUMBER = 10;
const int DELAY = 30;
const int WIDTH = 700;

static Scalar random_color(RNG &rng){
	unsigned int color = static_cast<unsigned int>(rng);
	return Scalar(color & 255, (color >> 8) & 255, (color >> 16) & 255);
}

int draw_line(Mat &image,const string &line_window, RNG rng){
	Point pt1, pt2;
	Mat res;
	res = image.clone();
	for (int i = 0; i < NUMBER; ++i){
		pt1.x = rng.uniform(0, image.cols);
		pt1.y = rng.uniform(0, image.rows);
		pt2.x = rng.uniform(0, image.cols);
		pt2.y = rng.uniform(0, image.rows);

		line(res, pt1, pt2, random_color(rng), 2);
		imshow(line_window, res);
		int sign = waitKey(DELAY);
		if (sign >= 0)
			return -1;
	}
	return 0;
}

int draw_rectangle(Mat &image, const string &rectangle_window, RNG rng){
	Mat res;
	res = image.clone();
	Point pt1, pt2;
	for (int i = 0; i < NUMBER; ++i){
		pt1.x = rng.uniform(0, image.cols);
		pt1.y = rng.uniform(0, image.rows);
		pt2.x = rng.uniform(0, image.cols);
		pt2.y = rng.uniform(0, image.rows);

		rectangle(res, pt1, pt2, random_color(rng), 2);
		imshow(rectangle_window, res);
		if (waitKey(DELAY) >= 0)
			return -1;
	}
	return 0;
}

int draw_ellipse(Mat &image, const string &ellipse_window, RNG rng){
	Mat res = image.clone();
	Point center;
	for (int i = 0; i < NUMBER; ++i){
		center.x = rng.uniform(0, image.cols);
		center.y = rng.uniform(0, image.rows);
		ellipse(res, center, Size(rng.uniform(10, 500), rng.uniform(10, 500)),
			rng.uniform(0, 360), 0, 360, random_color(rng), 2);
		imshow(ellipse_window, res);
		if (waitKey(DELAY) >= 0)
			return -1;
	}
	return 0;
}

int draw_text(Mat &image, const string &text_window, RNG rng){
	Mat res = image.clone();
	Point org;

	for (int i = 0; i < NUMBER; ++i){
		org.x = rng.uniform(0, image.cols);
		org.y = rng.uniform(0, image.rows);

		putText(res, "Opencv Learning", org, rng.uniform(0, 8), rng.uniform(0, 100)*0.05 + 0.1,
			random_color(rng), rng.uniform(1, 10));
		imshow(text_window, res);
		if (waitKey(DELAY) >= 0)
			return -1;
	}
	return 0;
}

int displaying_big_end(Mat &image, const string &window_name, RNG rng)
{
	Size textsize = getTextSize("OpenCV forever!", FONT_HERSHEY_COMPLEX, 2, 5, 0);
	Point org((image.cols - textsize.width) / 2, (image.rows - textsize.height) / 2);
	int lineType = 8;
	Mat image2;
	for (int i = 0; i < 255; ++i)
	{
		image2 = image - Scalar::all(i);
		putText(image2, "Opencv Learning", org, FONT_HERSHEY_COMPLEX, 2,
			random_color(rng), rng.uniform(1, 10));
		imshow(window_name, image2);
		if (waitKey(DELAY) >= 0)
		{
			return -1;
		}
	}
	return 0;
}
int rng_main(int argc, const char *argv[]){
	RNG rng(0xffffffff);
	Mat image = Mat::zeros(WIDTH, WIDTH, CV_8UC3);
	
	/*if (draw_line(image, "random_line", rng) != 0)
		return 0;
	if (draw_rectangle(image, "random_rectangle", rng) != 0)
		return 0;
	if (draw_ellipse(image, "random_ellipse", rng) != 0)
		return 0;
	if (draw_text(image, "random_text", rng) != 0)
		return 0;*/
	if (displaying_big_end(image, "big_end", rng) != 0)
		return 0;
	system("pause");
	destroyAllWindows();
	return 0;
}