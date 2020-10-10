
#include "YUVVideo.h"
#include <string>
#include <iostream>
using namespace std;

class YUVScaler{
	public:
		YUVScaler(){};
		void yuvScaler420to444 (YUVVideo yuv420Video, YUVVideo yuv444Video ){
			for (int i = 0; i < yuv420Video.frameNumber; i++){
				//read data for Y plane
				for (int row =0; row < yuv420Video.getFrame(i).Y.numberOfRow; row++){
					for (int col =0; col < yuv420Video.getFrame(i).Y.numberOfColumn; col++){
						yuv444Video.getFrame(i).Y.setData(row,col,yuv420Video.getFrame(i).Y.getData(row,col));
					}
				}
			
				//read data for U plane
				for (int row =0; row < yuv420Video.getFrame(i).U.numberOfRow; row++){
					for (int col =0; col < yuv420Video.getFrame(i).U.numberOfColumn; col ++){
						yuv444Video.getFrame(i).U.setData(row*2,col*2,yuv420Video.getFrame(i).U.getData(row,col));
						yuv444Video.getFrame(i).U.setData(row*2 + 1,col*2,yuv420Video.getFrame(i).U.getData(row,col));
						yuv444Video.getFrame(i).U.setData(row*2,col*2 + 1,yuv420Video.getFrame(i).U.getData(row,col));
						yuv444Video.getFrame(i).U.setData(row*2 + 1,col*2 + 1,yuv420Video.getFrame(i).U.getData(row,col));

					}
				}
			
				//read data for V plane
				for (int row =0; row < yuv420Video.getFrame(i).V.numberOfRow; row++){
					for (int col =0; col < yuv420Video.getFrame(i).V.numberOfColumn; col ++){
						yuv444Video.getFrame(i).V.setData(row*2,col*2,yuv420Video.getFrame(i).V.getData(row,col));
						yuv444Video.getFrame(i).V.setData(row*2 + 1,col*2,yuv420Video.getFrame(i).V.getData(row,col));
						yuv444Video.getFrame(i).V.setData(row*2,col*2 + 1,yuv420Video.getFrame(i).V.getData(row,col));
						yuv444Video.getFrame(i).V.setData(row*2 + 1,col*2 + 1,yuv420Video.getFrame(i).V.getData(row,col));

					}
				}
						
			}
	}

};


