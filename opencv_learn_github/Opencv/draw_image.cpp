// ����Բ
// ������Բ
// ���ƾ���
// �����������
// ����ֱ��

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

const int w = 500;

// ������Բ
void my_ellipse(Mat &src, const double angle){
	ellipse(src, 
		Point(w / 2, w / 2), // ����
		Size(w/4,w/16), // �������ο��С
		angle, // �Ƕ�
		0, // �Ƕȷ�Χ���
		360, // �Ƕȷ�Χ�յ�
		Scalar(255, 0, 0), 2);
}
// ��������Բ
void my_filled_circle(Mat &src,const Point &center){
	circle(src, 
		center, // Բ��
		w / 32, // �뾶
		Scalar(0, 0, 255), -1);
}

// ���ƶ����
void my_polygon(Mat &src){
	Point rook_points[2][20];
	rook_points[0][0] = Point(10+w / 4.0, 7 * w / 8.0);
	rook_points[0][1] = Point(10+3 * w / 4.0, 7 * w / 8.0);
	rook_points[0][2] = Point(10+3 * w / 4.0, 13 * w / 16.0);
	rook_points[0][3] = Point(10+11 * w / 16.0, 13 * w / 16.0);
	rook_points[0][4] = Point(10+19 * w / 32.0, 3 * w / 8.0);
	rook_points[0][5] = Point(10+3 * w / 4.0, 3 * w / 8.0);
	rook_points[0][6] = Point(10+3 * w / 4.0, w / 8.0);
	rook_points[0][7] = Point(10+26 * w / 40.0, w / 8.0);
	rook_points[0][8] = Point(10+26 * w / 40.0, w / 4.0);
	rook_points[0][9] = Point(10+22 * w / 40.0, w / 4.0);
	rook_points[0][10] = Point(10+22 * w / 40.0, w / 8.0);
	rook_points[0][11] = Point(10+18 * w / 40.0, w / 8.0);
	rook_points[0][12] = Point(10+18 * w / 40.0, w / 4.0);
	rook_points[0][13] = Point(10+14 * w / 40.0, w / 4.0);
	rook_points[0][14] = Point(10+14 * w / 40.0, w / 8.0);
	rook_points[0][15] = Point(10+w / 4.0, w / 8.0);
	rook_points[0][16] = Point(10+w / 4.0, 3 * w / 8.0);
	rook_points[0][17] = Point(10+13 * w / 32.0, 3 * w / 8.0);
	rook_points[0][18] = Point(10+5 * w / 16.0, 13 * w / 16.0);
	rook_points[0][19] = Point(10+w / 4.0, 13 * w / 16.0);

	rook_points[1][0] = Point(w / 4.0, 7 * w / 8.0);
	rook_points[1][1] = Point(3 * w / 4.0, 7 * w / 8.0);
	rook_points[1][2] = Point(3 * w / 4.0, 13 * w / 16.0);
	rook_points[1][3] = Point(11 * w / 16.0, 13 * w / 16.0);
	rook_points[1][4] = Point(19 * w / 32.0, 3 * w / 8.0);
	rook_points[1][5] = Point(3 * w / 4.0, 3 * w / 8.0);
	rook_points[1][6] = Point(3 * w / 4.0, w / 8.0);
	rook_points[1][7] = Point(26 * w / 40.0, w / 8.0);
	rook_points[1][8] = Point(26 * w / 40.0, w / 4.0);
	rook_points[1][9] = Point(22 * w / 40.0, w / 4.0);
	rook_points[1][10] = Point(22 * w / 40.0, w / 8.0);
	rook_points[1][11] = Point(18 * w / 40.0, w / 8.0);
	rook_points[1][12] = Point(18 * w / 40.0, w / 4.0);
	rook_points[1][13] = Point(14 * w / 40.0, w / 4.0);
	rook_points[1][14] = Point(14 * w / 40.0, w / 8.0);
	rook_points[1][15] = Point(w / 4.0, w / 8.0);
	rook_points[1][16] = Point(w / 4.0, 3 * w / 8.0);
	rook_points[1][17] = Point(13 * w / 32.0, 3 * w / 8.0);
	rook_points[1][18] = Point(5 * w / 16.0, 13 * w / 16.0);
	rook_points[1][19] = Point(w / 4.0, 13 * w / 16.0);

	const Point* ppt[2] = { rook_points[0],rook_points[1] };
	int npt[] = { 20 ,20};
	// �������
	fillPoly(src,  // ����ͼ��
		ppt,		// ���㼯��
		npt,		// �������
		2,          // ���������
		Scalar(255, 255, 255)); // ��ɫ
}

// ����ֱ��
void my_line(Mat &src, const Point &start, const Point &end){
	line(src, start, end, Scalar(0, 255, 0), 2);
}

int draw_image(int argc, const char *argv[]){
	const char *atom_window = "Drawing 1: atom";
	const char *rook_window = "Drawing 2: rook";

	Mat atom_image = Mat::zeros(Size(w, w), CV_8UC3);
	Mat rook_image = Mat::zeros(Size(w, w), CV_8UC3);

	// ����ԭ��
	const double angle_arr[4] = { 0, 45, 90, -45};
	for (auto angle : angle_arr)
		my_ellipse(atom_image, angle);
	my_filled_circle(atom_image, Point(w / 2, w / 2));

	// ���ƶ�̨
	my_polygon(rook_image);
	rectangle(rook_image,
		Point(0, 7 * w / 8.0), //���㣬���Ͻ�
		Point(w, w),			//���㣬���½�
		Scalar(0, 255, 255),
		-1, 8);
	my_line(rook_image, Point(0, 15 * w / 16), Point(w, 15 * w / 16));
	my_line(rook_image, Point(w / 4, 7 * w / 8), Point(w / 4, w));
	my_line(rook_image, Point(w / 2, 7 * w / 8), Point(w / 2, w));
	my_line(rook_image, Point(3 * w / 4, 7 * w / 8), Point(3 * w / 4, w));

	imshow(atom_window, atom_image);
	imshow(rook_window, rook_image);
	waitKey(0);
	destroyAllWindows();
	return 0;
}
