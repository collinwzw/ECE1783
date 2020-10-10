#include "YUVScaler.cpp"
#include "Converter.cpp"
#include "YUVVideo.h"
#include "RGBVideo.h"

#include <string>
#include <iostream>

using namespace std;

int main()
{	
	YUVVideo v1,v2;
	v1.LoadYUVFile("akiyo_Y.yuv",176,144,400);
	//v1.writeYOnlyVideoToFile("test.yuv", true);
	//v1.LoadYUVFile("akiyo_qcif.yuv",176, 144, 420);
	//v2.createEmptyVideo(300,176,144,444);

	// //v1.LoadYUVFile("debug.yuv",4,4 , 420);
	// //v2.createEmptyVideo(1,4,4,444);
	// //YUVVideo v1("C:\\Users\\Zhiying\\c++workspace\\ECE1783A1\\akiyo_qcif.yuv",176, 144, 420);
	// //v1.writeOneFrameToFile("test.yuv",100,true);
	

	//RGBVideo r1;
	//r1.createEmptyVideo(300,176,144);

	//YUVScaler vs;
	//vs.yuvScaler420to444(v1,v2);
	// //cout << "the number is " << v2.getFrame(0).U.getData(0,1) << '\n';
	
	//Converter c;
	//c.YUV444ToRGB(v2,r1);


	//v1.writeYOnlyVideoToFile("akiyo_Y.yuv",true);
	//v1.writeVideoToFile("fristframe420.yuv",true);
	//v2.getFrame(0).writeOneFrameToFile("fristframe444.yuv",true);
	//r1.getFrame(0).writeOneFrameToFile("img.bmp",true);
	return 0;
}