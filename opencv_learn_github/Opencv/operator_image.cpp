#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

using namespace std;
using namespace cv;

int operator_image(int argc,char *argv[]){
	const string path = "../Image/lena.jpg";
	Mat src = imread(path, IMREAD_COLOR);
	Mat gray;
	cvtColor(src, gray, CV_BGR2GRAY);
	Scalar intensity1 = gray.at<uchar>(10, 10);
	cout << intensity1 << endl;
	Scalar intensity2 = gray.at<uchar>(Point(10, 10));
	cout << intensity2 << endl;

	Vec3b intensity3 = src.at<Vec3b>(10, 10);
	uchar blue = intensity3.val[0];
	uchar green = intensity3.val[1];
	uchar red = intensity3.val[2];
	cout << int(blue) << "," << int(green) << "," << int(red) << endl;
	cout << intensity3 << endl;

	vector<Point3f> points;
	points.push_back(Point3f(10, 20, 30));
	points.push_back(Point3f(20, 30, 40));
	Mat point_mat = Mat(points);
	Mat point_matr = Mat(points).reshape(1);
	cout << point_matr << endl;
	cout << point_mat << endl;

	Mat background,rand_rgb;
	background.create(gray.size(), gray.type());
	rand_rgb.create(src.size(), src.type());
	rand_rgb = Scalar(127, 38, 79);
	background = Scalar(127);
	imshow("background", background);
	imshow("rand_rgb", rand_rgb);
	
	// roi区域提取, 是对原对象的引用，操作会相互影响
	Rect rect(10, 10, 100, 100);
	Mat roi = src(rect);
	roi = Scalar(0, 127, 0);
	imshow("src", src);
	imshow("roi", roi);  


	Mat sobel,result;
	Sobel(gray, sobel, CV_32F, 1, 0);
	double min, max;
	minMaxLoc(sobel, &min, &max);

	// 数据类型转换
	sobel.convertTo(result, CV_8U, 255 / (max - min), -min * 255 / (max - min));
	
	Mat dst;
	addWeighted(gray, 0.7, result, 0.3, 0.0, dst);
	// 只能显示uchar类型数据 CV_8U	
	imshow("dst", dst);
	waitKey(0);
	destroyAllWindows();
	system("pause");
	return 0;
}