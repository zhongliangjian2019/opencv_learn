/* 图像读取与保存
 * cv::imread()读取
 * cv::imwrite()保存
 * cv::namedWindow()创建显示窗口
 * cv::imshow()显示图像
 * cv::waitKey()显示等待
 */

#include <opencv2/core/core.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
int display_image(void)
{
	char *imageName = "../Image/lena.jpg";
	Mat image;
	image = imread(imageName, 1);
	if (image.empty()){
		cout << "image is empty, please checkout image path" << endl;
		system("pause");
		return 0;
	}
	Mat gray;
	cvtColor(image, gray, COLOR_BGR2GRAY);
	namedWindow(imageName, WINDOW_AUTOSIZE);
	namedWindow("gray image", WINDOW_AUTOSIZE);
	imshow(imageName, image);
	imshow("gray image", gray);
	waitKey(0);
	return 0;
}