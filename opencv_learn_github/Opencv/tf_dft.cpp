#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, const char *argv[]){

	const string path = argc >= 2 ? argv[1] : "../Image/lena.jpg";
	Mat image = imread(path, 0);
	if (image.empty()){
		cout << "image load fail" << endl;
		return -1;
	}
	int m = getOptimalDFTSize(image.rows);
	int n = getOptimalDFTSize(image.cols);
	cout << "optimal(" << m << "," << n << ")" << endl;
	cout << image.size() << endl;
	Mat pad;
	copyMakeBorder(image, pad, 0, m - image.rows, 0, n - image.cols, BORDER_CONSTANT, Scalar::all(0));

	Mat planes[] = { Mat_<float>(pad), Mat::zeros(pad.size(), CV_32F) };
	Mat complex_image;
	merge(planes, 2, complex_image);  // 合并两个矩阵面到一张图像

	dft(complex_image, complex_image);

	split(complex_image, planes); // 拆分图像到两个矩阵面

	magnitude(planes[0], planes[1], planes[0]);

	Mat mag_image = planes[0];
	mag_image += Scalar::all(1);
	log(mag_image, mag_image);

	mag_image = mag_image(Rect(0, 0, mag_image.cols & -2, mag_image.rows & -2));
	int cx = mag_image.cols / 2;
	int cy = mag_image.rows / 2;

	Mat q0(mag_image, Rect(0, 0, cx, cy)); // Rect(x,y,width,height)
	Mat q1(mag_image, Rect(cx, 0, cx, cy));
	Mat q2(mag_image, Rect(0, cy, cx, cy));
	Mat q3(mag_image, Rect(cx, cy, cx, cy));

	/*Mat tmp;
	tmp = q0.clone();
	q0 = q2.clone();
	q2 = tmp.clone();

	tmp = q1.clone();
	q1 = q3.clone();
	q3 = tmp.clone();*/

	Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
	q2.copyTo(q1);
	tmp.copyTo(q2);


	normalize(mag_image, mag_image, 0, 1, NORM_MINMAX);

	imshow("src", image);
	imshow("mag_image", mag_image);
	waitKey(0);
	destroyAllWindows();

	return 0;
}