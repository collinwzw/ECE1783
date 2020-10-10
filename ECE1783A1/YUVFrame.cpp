#include<iostream>
#include "Plane.h"
#include <string>
#include <stdexcept> 
using namespace std;


class YUVFrame{
	public:
		int frameIndex;
		Plane Y;
		Plane U;
		Plane V;
		int FrameType;
		YUVFrame(int frameIndex, int resolutionRow, int resolutionColumn, int frametype)
			:Y(resolutionRow, resolutionColumn), U(resolutionRow, resolutionColumn), V(resolutionRow, resolutionColumn)
		{
			FrameType = frametype;
			switch(frametype){
				case(444):
					break;
				case(422):
					U.resetSize(resolutionRow, resolutionColumn/2);
					V.resetSize(resolutionRow, resolutionColumn/2);
					break;
				case(420):
					U.resetSize(resolutionRow/2, resolutionColumn/2);
					V.resetSize(resolutionRow/2, resolutionColumn/2);
					break;
				case(400):
					U.resetSize(0, 0);
					V.resetSize(0, 0);
					break;
				default:
            		throw std::invalid_argument( "received invalid frametype value" );
			
			}

		}

		void writeOneFrameToFile(const char* file_name, bool overwrite){

			Y.writePlaneToFile(file_name,overwrite);
			overwrite = false;
			U.writePlaneToFile(file_name,overwrite);
			V.writePlaneToFile(file_name,overwrite);			
		}
};

