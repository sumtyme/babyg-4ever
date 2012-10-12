/*
 * HoughLine.cpp
 *
 *  Created on: Oct 9, 2012
 *      Author: troy
 */

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <sys/time.h>

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
 double sleepTimeDbl=1000/fps;
 int key;
 vector<Vec4i> lines;

 while (true) {
	 struct timeval  startTime, endTime;
	 gettimeofday(&startTime, NULL);

	 double startTimeMillis =
	          (startTime.tv_sec) * 1000 + (startTime.tv_usec) / 1000 ;
	 cap>>src;

	 int width=src.cols/2;
	 int height= src.rows/2;
	 //pyrDown( src, src, Size( width, height) );
	 original=src.clone();

	 GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );
	 erode(src, src, Mat(), Point (-1,-1), 5);
	 Canny(src, dst, 130, 200, 3);
	 //cvtColor(dst, cdst, CV_GRAY2BGR);

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

	  HoughLinesP( dst, lines, 1, CV_PI/180, 40, 70, 14 );
	  for( size_t i = 0; i < lines.size(); i++ )
	  {
		Vec4i l = lines[i];
		line( original, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
	  }
	 #endif


	 gettimeofday(&endTime, NULL);

	 double endTimeMillis =
			  (endTime.tv_sec) * 1000 + (endTime.tv_usec) / 1000 ;
	 double totalTime = endTimeMillis-startTimeMillis;

	 //cout<<"sleepTimeDbl: "<<sleepTimeDbl<< " total time: "<<totalTime<<endl;

	 double calcWait = sleepTimeDbl-totalTime;
	 if (calcWait<1)
		 calcWait=1;

	 double calcFPS=1000;
	 if (totalTime>0)
		 calcFPS = 1000/totalTime;
	 ostringstream os;
	 os<<"FPS: "<<calcFPS<<" loop: "<<totalTime <<" w: "<<width<<" h: "<<height;
	 String fpsStr = os.str();

	 putText(original, fpsStr, cvPoint(30,30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(250,10,10), 1, CV_AA);
	 imshow("source", original);

	 key=cvWaitKey(calcWait);

// waitKey();
 }

 return 0;
}



