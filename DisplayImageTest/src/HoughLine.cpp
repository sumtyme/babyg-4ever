/*
 * HoughLine.cpp
 *
 *  Created on: Oct 9, 2012
 *      Author: troy
 */

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>

using namespace cv;
using namespace std;

void help()
{
 cout << "\nThis program demonstrates line finding with the Hough transform.\n"
         "Usage:\n"
         "./houghlines <image_name>, Default is pic1.jpg\n" << endl;
}

int main(int argc, char** argv)
{
 const char* filename = argc >= 2 ? argv[1] : "pic1.jpg";

 //Mat original = imread(filename, -1);
 //Mat src = imread(filename, 0);

 VideoCapture cap(filename);


// if (!cap.isOpened()) {
//	 return -1;
// }

// if(src.empty())
// {
//     help();
//     cout << "can not open " << filename << endl;
//     return -1;
// }

 Mat src, original;
 Mat dst, cdst;

 double fps = cap.get(CV_CAP_PROP_FPS);
 cout<<"Frames per second "<<fps<<endl;
 double sleepTimeDbl=1/fps*1000;
 int sleepTime=(int)sleepTimeDbl;
 int key;

 while (true) {
	 Mat src;
	 cap>>src;
//	 imshow("video", src);

////	 cout<<"sleep for: "<<sleepTime<<endl;
////	 usleep(sleepTime);
//
//	 continue;

	 original=src.clone();

	 GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );
	 erode(src, src, Mat(), Point (-1,-1), 4);
	 Canny(src, dst, 50, 200, 3);
	 cvtColor(dst, cdst, CV_GRAY2BGR);

	 #if 0
	  vector<Vec2f> lines;
	  HoughLines(dst, lines, 1, CV_PI/180, 100, 0, 0 );

	  for( size_t i = 0; i < lines.size(); i++ )
	  {
		 float rho = lines[i][0], theta = lines[i][1];
		 Point pt1, pt2;
		 double a = cos(theta), b = sin(theta);
		 double x0 = a*rho, y0 = b*rho;
		 pt1.x = cvRound(x0 + 1000*(-b));
		 pt1.y = cvRound(y0 + 1000*(a));
		 pt2.x = cvRound(x0 - 1000*(-b));
		 pt2.y = cvRound(y0 - 1000*(a));
		 line( cdst, pt1, pt2, Scalar(0,0,255), 3, CV_AA);
	  }
	 #else
	  vector<Vec4i> lines;
	  HoughLinesP( dst, lines, 1, CV_PI/180, 40, 70, 14 );
	  for( size_t i = 0; i < lines.size(); i++ )
	  {
		Vec4i l = lines[i];
		line( original, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
	  }
	 #endif
	 imshow("source", original);

	 key=cvWaitKey(1/fps*1000);

// waitKey();
 }

 return 0;
}



