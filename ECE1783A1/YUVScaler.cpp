#include "YUVVideo.cpp"
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

int main()
{	
	
	YUVVideo v1, v2;
	v1.LoadYUVFile("akiyo_qcif.yuv",176, 144, 420);
	//v1.LoadYUVFile("debug.yuv",4,4 , 420);
	//v2.createEmptyVideo(1,4,4,444);
	//YUVVideo v1("C:\\Users\\Zhiying\\c++workspace\\ECE1783A1\\akiyo_qcif.yuv",176, 144, 420);
	//v1.writeOneFrameToFile("test.yuv",100,true);
	
	v2.createEmptyVideo(300,176,144,444);
	YUVScaler vs;
	vs.yuvScaler420to444(v1,v2);
	//cout << "the number is " << v2.getFrame(0).U.getData(0,1) << '\n';
	//v2.writeVideoToFile("test.yuv",true);
	v1.writeVideoToFile("fristframe420.yuv",true);
	v2.getFrame(0).writeOneFrameToFile("fristframe444.yuv",true);
	return 0;
}
