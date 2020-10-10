#ifndef _RGBFrame_h_
#define _RGBFrame_h_
#include<iostream>
#include "Plane.h"
#include <string>
#include <stdexcept> 
using namespace std;


class RGBFrame{
	public:
		int frameIndex;
		Plane R;
		Plane G;
		Plane B;
		int FrameType;
		RGBFrame(int frameIndex, int resolutionRow, int resolutionColumn)
			:R(resolutionRow, resolutionColumn), G(resolutionRow, resolutionColumn), B(resolutionRow, resolutionColumn)
		{}

		void writeOneFrameToFile(const char* file_name, bool overwrite){

			int filesize = 54 + 3*R.numberOfRow*R.numberOfColumn;
			unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
			unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
			unsigned char bmppad[3] = {0,0,0};

			bmpfileheader[ 2] = (unsigned char)(filesize    );
			bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
			bmpfileheader[ 4] = (unsigned char)(filesize>>16);
			bmpfileheader[ 5] = (unsigned char)(filesize>>24);

			bmpinfoheader[ 4] = (unsigned char)(       R.numberOfColumn    );
			bmpinfoheader[ 5] = (unsigned char)(       R.numberOfColumn>> 8);
			bmpinfoheader[ 6] = (unsigned char)(       R.numberOfColumn>>16);
			bmpinfoheader[ 7] = (unsigned char)(       R.numberOfColumn>>24);
			bmpinfoheader[ 8] = (unsigned char)(       R.numberOfRow    );
			bmpinfoheader[ 9] = (unsigned char)(       R.numberOfRow>> 8);
			bmpinfoheader[10] = (unsigned char)(       R.numberOfRow>>16);
			bmpinfoheader[11] = (unsigned char)(       R.numberOfRow>>24);
			FILE *f;
			f = fopen("img.bmp","wb");
			fwrite(bmpfileheader,1,14,f);
			fwrite(bmpinfoheader,1,40,f);
			overwrite = false;
			R.writePlaneToFile(file_name,overwrite);
			
			G.writePlaneToFile(file_name,overwrite);
			B.writePlaneToFile(file_name,overwrite);			
		}
};
#endif
