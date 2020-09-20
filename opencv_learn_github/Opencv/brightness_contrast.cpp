// 对比度与亮度调节
// 公式：alpha * src_point + beta
// alpha(1.0-3.0) 调节对比度，越大对比度越高
// beta(0-100) 调节亮度，越大亮度越高

#include "image_process.h"
#include <iostream>

using namespace std;

void change_brightness_contrast(const Mat &src, Mat &res, double alpha, int beta){
	CV_Assert(src.depth() == CV_8U);
	
	int n_row = src.rows;
	int n_col = src.cols;
	int n_channel = src.channels();
	res.create(src.size(), src.type());
	
	/*for (int i = 0; i < n_row; ++i){
		for (int j = 0; j < n_col; ++j){
			switch (n_channel){
			case 1:
				res.at<uchar>(i, j) = saturate_cast<uchar>(alpha*src.at<uchar>(i, j) + beta);
				break;
			case 3:
				for (int c = 0; c < 3; ++c){
					res.at<Vec3b>(i, j)[c] = saturate_cast<uchar>(alpha*src.at<Vec3b>(i, j)[c] + beta);
				}
				break;
			}
		}
	}*/
	const uchar *p_src = nullptr;
	uchar *p_res = nullptr;
	for (int i = 0; i < n_row; ++i){
		p_src = src.ptr<uchar>(i);
		p_res = res.ptr<uchar>(i);
		for (int j = 0; j < n_col*n_channel; ++j){
			*(p_res++) = saturate_cast<uchar>(alpha * *(p_src++) + beta);
		}
	}
	
}

int brightness_contrast(int argc, char *argv[]){
	const string path = "../Image/lena.jpg";
	double alpha;
	int beta;
	cout << "alpha:1.0-3.0" << endl;
	cout << "beta:1-100" << endl;
	cout << "please input alpha and beta:" << endl;
	Mat src = imread(path, IMREAD_GRAYSCALE);

	Mat res;
	namedWindow("src", WINDOW_AUTOSIZE);
	namedWindow("res", WINDOW_AUTOSIZE);

	while (cin >> alpha >> beta){
		double time = (double)getTickCount();
		change_brightness_contrast(src, res, alpha, beta);
		time = ((double)getTickCount() - time) / getTickFrequency();
		cout << "time: " << time << "second" << endl;
		imshow("src", src);
		imshow("res", res);
		waitKey(30);
	}
	destroyAllWindows();
	return 0;
}