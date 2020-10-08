#include "Frame.cpp"
#include "YUVVideo.h"
#include "YUVScaler.cpp"
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

		YUVVideo(char* filename, int resolutionRow, int resolutionColumn, int frametype ){
			long filesize = yuvOpenInputFile(filename);
			frameNumber = getFrameNumber(resolutionRow,resolutionColumn,frametype,filesize);
			
			for(int i = 0; i < frameNumber; i++) frames.push_back(YUVFrame(i, resolutionRow, resolutionColumn, frametype)); 
			initData(filename,filesize);
			
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

		//file writer, update function to throw exception when failed to read.
		void writeFrameToFile(const char* file_name, int frameindex){
			FILE *file = fopen(file_name, "wb");
			uint8_t byte;
			if(file!=NULL){
				for (int row =0; row < frames[frameindex].Y.numberOfRow; row++)
				{
					for (int col =0; col < frames[frameindex].Y.numberOfColumn; col++){
						byte = frames[frameindex].Y.getData(row,col);
						fwrite(&byte, 1, 1, file);
					}
					
				}
				cout << "writing done" <<"\n";
			
				//read data for U plane
				for (int row =0; row < frames[frameindex].U.numberOfRow; row++){
					for (int col =0; col < frames[frameindex].U.numberOfColumn; col ++){
						byte = frames[frameindex].U.getData(row,col);
						fwrite(&byte, 1, 1, file);
					}
				}
		
				//read data for V plane
				for (int row =0; row < frames[frameindex].V.numberOfRow; row++){
					for (int col =0; col < frames[frameindex].V.numberOfColumn; col ++){
						byte = frames[frameindex].V.getData(row,col);
						fwrite(&byte, 1, 1, file);
					}
				}
				
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

		long yuvOpenInputFile(const char* file_name ) {
			long size;
			ifstream file;
			file.open(file_name);
			if (file.is_open()){
				file.seekg(0, ios::end);
				size= file.tellg();
				
				cout << "successfully opened file " << '\n'; 
				cout << " tellg() returns " <<size << '\n'; 

				file.close();
				return size;
			}
			else{
				cout << "unable to open file "  << '\n'; 
			}
			return -1;
		}
	  	void initData(const char* file_name,long filesize){
			
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
	
// 	YUVVideo v1("akiyo_qcif.yuv",176, 144, 420);

// 	//YUVVideo v1("C:\\Users\\Zhiying\\c++workspace\\ECE1783A1\\akiyo_qcif.yuv",176, 144, 420);
// 	v1.writeFrameToFile("test.yuv",0);
// 	return 0;
// }

