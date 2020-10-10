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

			R.writePlaneToFile(file_name,overwrite);
			overwrite = false;
			G.writePlaneToFile(file_name,overwrite);
			B.writePlaneToFile(file_name,overwrite);			
		}
};

