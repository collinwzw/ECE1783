#include "Frame.cpp"
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class YUVVideo{
	private:
		std::vector<YUVFrame> frames;
	public:
		int frameNumber;
		YUVVideo(){}
		
		void LoadYUVFile(char* filename, int resolutionRow, int resolutionColumn, int frametype ){
			long filesize = GetFileSize(filename);
			
			frameNumber = getFrameNumber(resolutionRow,resolutionColumn,frametype,filesize);
			createEmptyVideo(frameNumber, resolutionRow, resolutionColumn, frametype);
			loadDataFromFile(filename,filesize);
		}

		// function need to be update with throw exception
		YUVFrame getFrame(int index){
			if (index >=0 && index < frameNumber){
				return frames[index];
			}
			else{
            	throw std::invalid_argument( "received invalid frametype value" );
			}
		}

		void createEmptyVideo(int framenumber, int resolutionRow, int resolutionColumn, int frametype ){
			frameNumber = framenumber;
			if (frameNumber > 0) {
				for(int i = 0; i < frameNumber; i++) frames.push_back(YUVFrame(i, resolutionRow, resolutionColumn, frametype)); 
			}
			else{
				cout << "the file has wrong size comparing to the input size and type" <<"\n";
			}

		}

		void writeVideoToFile(const char* file_name, bool overwrite){
			for (int i = 0; i < frameNumber; i++){
				if (i==0 && overwrite) frames[i].writeOneFrameToFile(file_name,overwrite);
				else frames[i].writeOneFrameToFile(file_name,false );
			}
		}
	private:
		int getFrameNumber(int resolutionRow, int resolutionColumn,int frametype, long filesize){
			int bytesPerFrame;
			long frame_number;
			switch(frametype){
				case(444):
					bytesPerFrame = resolutionRow * resolutionColumn * 4;//16 + 16 + 16 =48
					frame_number = ( filesize / bytesPerFrame );
					break;
				case(422):
					bytesPerFrame = resolutionRow * resolutionColumn * 2;//16 + 8 + 8 = 32
					frame_number = ( filesize / bytesPerFrame );
					break;
				case(420):
					bytesPerFrame = resolutionRow * resolutionColumn * 1.5;// 16 + 4 + 4 = 24
					frame_number = ( filesize / bytesPerFrame );
					break;
				default:
            		throw std::invalid_argument( "received invalid frametype value" );
			
			}
			if (is_integer(frame_number)){
				return frame_number;
			}
			else{
				cout << "the file has wrong size" <<"\n";
			}
			return -1;
		}

		bool is_integer(long k)
		{
			return std::floor(k) == k;
		}

		long GetFileSize(const char* file_name ) {
			long size;
			ifstream file;
			file.open(file_name);
			if (file.is_open()){
				file.seekg(0, ios::end);
				size= file.tellg();
				cout << "successfully opened file " << '\n'; 
				file.close();
				return size;
			}
			else{
				cout << "unable to open file "  << '\n'; 
			}
			return -1;
		}
	  	
		void loadDataFromFile(const char* file_name,long filesize){
			
			FILE *file = fopen(file_name, "rb");


			//file.open(file_name);
			if (file != NULL){
				fseek(file, 0, SEEK_END);
				uint32_t size = ftell(file);
				fseek(file, 0, SEEK_SET);
				uint8_t *YUV = (uint8_t *)malloc(size);

				size_t result = fread(YUV,1,size,file);
				uint8_t *byte = YUV;
				int iVal;
				
				for (int i = 0; i < frameNumber; i++){
					//read data for Y plane
					for (int row =0; row < frames[i].Y.numberOfRow; row++){
						for (int col =0; col < frames[i].Y.numberOfColumn; col++){
							frames[i].Y.setData(row,col,*byte);
							byte++;
						}
					}
				
					//read data for U plane
					for (int row =0; row < frames[i].U.numberOfRow; row++){
						for (int col =0; col < frames[i].U.numberOfColumn; col ++){
							frames[i].U.setData(row,col,*byte);
							byte++;

						}
					}
				
					//read data for V plane
					for (int row =0; row < frames[i].V.numberOfRow; row++){
						for (int col =0; col < frames[i].V.numberOfColumn; col ++){
							frames[i].V.setData(row,col,*byte);
							byte++;

						}
					}
					
				}
				
				//file.close();
				fclose(file);
			}
			else{
				cout << "unable to open file "  << '\n'; 
			}
		}
};

// int main()
// {	
	
// 	YUVVideo v1, v2;
// 	v1.LoadYUVFile("akiyo_qcif.yuv",176, 144, 420);

// 	//YUVVideo v1("C:\\Users\\Zhiying\\c++workspace\\ECE1783A1\\akiyo_qcif.yuv",176, 144, 420);
// 	//v1.writeOneFrameToFile("test.yuv",100,true);
// 	v2.createEmptyVideo(300,30,30,420);
// 	cout << "the number is " << v2.getFrame(0).U.getData(0,0) << '\n';
// 	v2.writeVideoToFile("test.yuv",0,true);
// 	return 0;
// }

