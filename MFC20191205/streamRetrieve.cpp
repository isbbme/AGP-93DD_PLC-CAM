#include "pch.h"
#include "StreamRetrieve.h"
#include "GenICam/Frame.h"
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string> 
#include <ctime>


#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace cv;
using namespace std;

stringstream ss; 


StreamRetrieve::StreamRetrieve(IStreamSourcePtr& streamSptr)
	: CThread("streamRetrieve")
	, m_isLoop(false)
	, m_streamSptr(streamSptr)
{
	
}

bool StreamRetrieve::start(DWORD c, DWORD vx, DWORD vz, DWORD vz1, DWORD vpltz)
{
	
	coordinatee = c;
	coordinatee1 = vx;
	coordinatee2 = vz;
	coordinatee3 = vz1;
	coordinatee4 = vpltz;
	m_isLoop = true;
	return createThread();
}
 
void StreamRetrieve::stop()
{
	m_isLoop = false;
	m_streamSptr.reset();
}

void StreamRetrieve::threadProc()
{

	int j = 0;

	//cv::namedWindow("src1", cv::WINDOW_AUTOSIZE);
	//cv::resizeWindow("camera", 1920 * 0.9 * 0.4, 1024 * 0.9 * 0.4);
	//cv::namedWindow("camera", WINDOW_AUTOSIZE);//CV_WINDOW_NORMAL´N¬O0
	while (m_isLoop)
	{
		Mat mat;
		string name = "ID_";
		string type = ".jpg";
		CFrame frame;
		uint32_t* JPEG;
		if (!m_streamSptr)
		{
			return;
		}
		bool isSuccess = m_streamSptr->getFrame(frame, 100);

		if (!isSuccess)
		{
			continue;
		}

		bool isValid = frame.valid();
		if (!isValid)
		{
			continue;
		}

		////////////////////////////////////////////////////

		///////////////////frame.getImage();

		JPEG = (uint32_t*)malloc(sizeof(uint32_t) * frame.getImageSize());
		if (JPEG) {
			memcpy(JPEG, frame.getImage(), frame.getImageSize());
		}
		mat = cv::Mat(frame.getImageHeight(), frame.getImageWidth(), CV_8UC1, JPEG);
		
		ss << name << coordinatee<<"_" << coordinatee1 << "_" << coordinatee2 << "_" << coordinatee3 << "_" << coordinatee4 << type;
		string filename = ss.str();
		ss.str("");
		imwrite("C:/Users/³¯¸t¿Î/Desktop/crop/" + filename, mat);
		
		//cam flow
		//Size dsize = Size(3072 * 0.625 * 0.9 * 0.4, 2048 * 0.5 * 0.9 * 0.4);
		//Mat image2;
		//image2 = Mat(dsize, CV_8U);
		//resize(mat, image2, dsize);

		//cv::imshow("camera", image2);
		//cv::waitKey(30);

		//j++;
		sleep(30);
		free(JPEG);
	}

}
