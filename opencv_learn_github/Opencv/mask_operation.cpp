// �Զ������˾��
// filter2D() ʵ��
// �ֶ�ʵ��

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// �ֶ�ʵ��
void sharpen(Mat &src, Mat &res){
	CV_Assert(src.depth() == CV_8U); // ���ͼ���Ƿ�Ϊ uchar ���ݸ�ʽ�洢
	res.create(src.size(), src.type()); // ����һ����Դͼ��ͬ����С�͸�ʽ��ͼ��
	const int n_channel = src.channels();

	// �������ʵ��
	//switch (n_channel){
	//case 1:
	//	for (int i = 1; i < src.rows - 1; i++){
	//		for (int j = 1; j < src.cols - 1; j++){
	//			res.at<uchar>(i, j) = 
	//				saturate_cast<uchar>(	- src.at<uchar>(i - 1, j - 1) + 0 + src.at<uchar>(i - 1, j + 1)
	//										- src.at<uchar>(i, j - 1)     + 0 + src.at<uchar>(i, j + 1)
	//										- src.at<uchar>(i + 1, j - 1) + 0 + src.at<uchar>(i + 1, j + 1));
	//		}
	//	}
	//	break;
	//case 3:
	//	for (int i = 1; i < src.rows - 1; i++){
	//		for (int j = 1; j < src.cols - 1; j++){
	//			int count = 0;
	//			while (count < n_channel){
	//				res.at<Vec3b>(i, j)[count] = 
	//					saturate_cast<uchar>(
	//					- src.at<Vec3b>(i - 1, j - 1)[count] + 0 + src.at<Vec3b>(i - 1, j + 1)[count]
	//					- src.at<Vec3b>(i, j - 1)[count]     + 0 + src.at<Vec3b>(i, j + 1)[count]
	//					- src.at<Vec3b>(i + 1, j - 1)[count] + 0 + src.at<Vec3b>(i + 1, j + 1)[count]);
	//				count++;
	//			}
	//			
	//		}
	//	}
	//	break;
	//}
	
	// ָ��ʵ��
	for (int j = 1; j < src.rows - 1; j++){
		const uchar *previous = src.ptr<uchar>(j - 1); // ǰһ��
		const uchar *current  = src.ptr<uchar>(j    ); // ��ǰ��
		const uchar *next     = src.ptr<uchar>(j + 1); // ��һ��
		
		uchar *output = res.ptr<uchar>(j);  // �����->��ǰ��
		// �ӵ�һ�п�ʼ
		for (int i = n_channel; i < n_channel*(src.cols - 1); i++){
			*output++ = saturate_cast<uchar>(- previous[i - n_channel]  + 0 + previous[i + n_channel]
											 - current[i - n_channel]   + 0 + current[i + n_channel]
											 - next[i - n_channel]      + 0 + next[i + n_channel]);
											//  -1  0  1
											//  -1  0  1
											//  -1  0  1
		}
	}
		res.row(0).setTo(Scalar(0)); // ���õ�һ��Ϊ0
		res.row(res.rows - 1).setTo(Scalar(0)); // �������һ��Ϊ0
		res.col(0).setTo(Scalar(0)); // ���õ�һ��Ϊ0
		res.col(res.cols - 1).setTo(Scalar(0)); // �������һ��Ϊ0
	
}

// filter2Dʵ�־��
void sharpen_filter2d(Mat &src, Mat &res){
	Mat kernel = (Mat_<char>(3, 3) << - 1, 0, 1,
									  - 1, 0, 1,
									  - 1, 0, 1);
	filter2D(src, res, src.depth(), kernel);
}

int mask_operation(void){
	const string s_path("../Image/lena.jpg");
	Mat src, res;
	src = imread(s_path, IMREAD_COLOR);
	//cvtColor(src, src, CV_BGR2GRAY);
	sharpen(src, res);
	namedWindow("src", WINDOW_AUTOSIZE);
	namedWindow("res", WINDOW_AUTOSIZE);
	imshow("src", src);
	imshow("res", res);
	waitKey(0);
	destroyAllWindows();
	return 0;
}