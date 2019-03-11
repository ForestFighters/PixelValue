////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <pthread.h>
#include <fstream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


using namespace cv;
using namespace std;

enum Colours { Red, Green, Blue, Yellow, None };

int Hue = 0;
int Saturation = 0;
int Value = 0;
 

int main( int argc, char** argv )
{
	bool visible = false;
	int camNumber = 0;
	
	if( argc > 1 )
		visible = true;
		
	VideoCapture cap(camNumber); //capture the video from web cam

	if ( !cap.isOpened() )  // if not success, exit program
	{
		 cout << "Cannot open the web cam" << endl;
		 return -1;
	}


	Mat imgOriginal;
    
	Mat imgROI;
    
	Mat imgHSV;
	
	int Hue = 0;
	int Saturation = 0;
	int Value = 0;


	for( int i = 1; i< 10; i++ )
	{
		bool bSuccess = cap.read(imgOriginal); // read a new frame from video

		if (!bSuccess) //if not success, break loop
		{
			 cout << "Cannot read a frame from video stream" << endl;
			 break;
		}
		//Extract a region of interest from the grey scale frame
		Rect roi(0,0,640,80);  
		imgOriginal(roi).copyTo(imgROI);
		
		cvtColor(imgROI, imgHSV, COLOR_BGR2YUV);

		if( visible ) 
		{
			imshow("Colour Space", imgHSV);
			imshow("Original", imgROI); //show the original image
		}

		if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break; 
		}
										
		int x = 320;
		int y = 40;
		Vec3b val = imgHSV.at<Vec3b>(y,x); // opencv is row-major! 
		
		Hue += val[0];
        Saturation += val[1];        
        Value += val[2];
        
		//cout << Hue << ", " << Saturation << ", " << Value << endl;				
	}	
	Hue = Hue / 10;
    Saturation = Saturation / 10;        
    Value = Value / 10;
    
    cout << Hue << ", " << Saturation << ", " << Value << ", " << endl;				
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
