#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int mat_create(void){
	const string path("../Image/lena.jpg");
	// ǳ����,ֻ��������ͷ���������������ݱ����ڴ�������
	Mat A, C;
	A = imread(path, IMREAD_COLOR);
	C = A;
	Mat B(A);
	Mat D(A,Rect(10,10,100,100));
	Mat E = A(Range::all(), Range(1, 50));
	Mat S(A.size[0],A.size[1],CV_8UC3,Scalar(127,127,127));
	// ����������������ݱ����ڴ����Ĵ�
	Mat F = A.clone();
	Mat G;
	A.copyTo(G);

	B = A - S;
	/*imshow("A", A);
	imshow("B", B);
	imshow("C", C);
	imshow("D", D);
	imshow("E", E);
	imshow("F", F);
	imshow("G", G);*/
	Mat R(500, 500, CV_8UC3);
	randu(R, Scalar::all(0), Scalar::all(255)); //�����ֵ������
	Mat M;
	M.create(4, 4, CV_8UC3);
	cout << "M" << M << endl;
	//imshow("M", M);
	imshow("R", R);
	waitKey(0);
	return 0;
}