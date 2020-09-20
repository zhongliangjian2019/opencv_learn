// ͼ�����ر���
// Opencv����ֵ�洢
// �㷨���ܲ���
// ���ұ�ʹ��

#include <iostream>
#include <opencv2/opencv.hpp>
#include <cstddef>

using namespace std;
using namespace cv;

void create_table(uchar *const table, const uchar gap = 10, const size_t n = 256){
	for (int i = 0; i < n; i++){
		table[i] = (uchar)((i / gap) * gap);
	}
		
}
// ָ����ʷ�ʽ
Mat &scan_image_and_reduce_color_ptr(Mat &image, const uchar *const table){
	// ���ͼ������Ƿ�Ϊuchar
	CV_Assert(image.depth() == CV_8U);

	int n_channel = image.channels(); // ��ȡͼ��ͨ����
	int n_row = image.rows; // ��ȡ����
	int n_col = image.cols * n_channel; // ��ȡ����

	// ���洢�Ƿ�����
	if (image.isContinuous()){
		uchar *p = image.data;  // ��ȡ��һ�е�һ�ж�Ӧ��Ԫ��ָ��
		for (uint i = 0; i < n_row*n_col; i++)
			*p++ = table[*p];
	}
	else{
		uchar *p;
		for (int i = 0; i < n_row; i++){
			p = image.ptr<uchar>(i);
			for (int j = 0; j < n_col; j++){
				*(p + j) = table[*(p + j)];
			}
		}
	}

	
	return image;
}
// ���������ʷ�ʽ
Mat &scan_image_and_reduce_color_iterator(Mat &image, const uchar *const table){
	CV_Assert(image.depth() == CV_8U);
	const int n_channel = image.channels();
	switch (n_channel){
		case 1:
		{
			MatIterator_<uchar> iter, end;  // ��������������
			for (iter = image.begin<uchar>(), end = image.end<uchar>(); iter != end; iter++){
				*iter = table[*iter];
			}
			break;
		}
		case 3:
		{
			MatIterator_<Vec3b> iter, end;
			for (iter = image.begin<Vec3b>(), end = image.end<Vec3b>(); iter != end; iter++){
				(*iter)[0] = table[(*iter)[0]];
				(*iter)[1] = table[(*iter)[1]];
				(*iter)[2] = table[(*iter)[2]];
			}
			break;
		}
	}
	return image;
}
// ������ʷ�ʽ
Mat &scan_image_and_reduce_color_random(Mat &image, const uchar *const table){
	CV_Assert(image.depth() == CV_8U);
	const int n_channel = image.channels();
	switch (n_channel){
	case 1:
		{
			for (int i = 0; i < image.rows; i++){
				for (int j = 0; j < image.cols; j++){
					image.at<uchar>(i, j) = table[image.at<uchar>(i, j)];
				}
			}
			break;
		}
	case 3:
		{
			//  Mat_<Vec3b> _image = image;
			//  for (int i = 0; i < image.rows; i++){
			//	  for (int j = 0; j < image.cols; j++){
			//		  _image(i, j)[0] = table[_image(i, j)[0]];
			//		  _image(i, j)[1] = table[_image(i, j)[1]];
			//		  _image(i, j)[2] = table[_image(i, j)[2]];
			//	  }
			//  }
			// image = _image;
			  for (int i = 0; i < image.rows; i++){
				  for (int j = 0; j < image.cols; j++){
					  Vec3b &_img = image.at<Vec3b>(i, j);
					  _img[0] = table[_img[0]];
					  _img[1] = table[_img[1]];
					  _img[2] = table[_img[2]];
				  }
			  }
			  break;

		}
	}
	return image;
}

int scan_image(void){
	const char *path = "../Image/lena.jpg";
	Mat image;
	image = imread(path, IMREAD_COLOR);
	uchar table[256] = { 0 };
	create_table(table, 50, 256);
	for (auto num : table)
		cout << int(num) << " ";
	cout << endl;
	Mat result;
	Mat lookUpTable(1, 256, CV_8U);
	uchar *p = lookUpTable.ptr();
	for (int i = 0; i < 256; i++)
		p[i] = table[i];

	// ʱ�����
	double time = (double)getTickCount();

	LUT(image, lookUpTable, result); // cv::LUT() ���ұ�
	// result = scan_image_and_reduce_color_ptr(image, table); // 0.0027s
	// result = scan_image_and_reduce_color_iterator(image, table); // 0.0417s
	// result = scan_image_and_reduce_color_random(image, table); // 0.0835s

	time = ((double)getTickCount() - time) / getTickFrequency();
	cout << "cost time: " << time << endl;

	namedWindow("source", WINDOW_AUTOSIZE);
	namedWindow("result", WINDOW_AUTOSIZE);
	imshow("source", image);
	imshow("result", result);
	waitKey(0);
	destroyAllWindows();

	return 0;
}