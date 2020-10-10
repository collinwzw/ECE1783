#ifndef _RGBVideo_h_
#define _RGBVideo_h_
#include "RGBFrame.h"
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class RGBVideo{
	private:
		std::vector<RGBFrame> frames;
	public:
		int frameNumber;
		RGBVideo(){}
		
		void LoadRBGFile(char* filename, int resolutionRow, int resolutionColumn ){
			long filesize = GetFileSize(filename);
			
			frameNumber = getFrameNumber(resolutionRow,resolutionColumn,filesize);
			createEmptyVideo(frameNumber, resolutionRow, resolutionColumn);
			loadDataFromFile(filename,filesize);
		}

		// function need to be update with throw exception
		RGBFrame getFrame(int index){
			if (index >=0 && index < frameNumber){
				return frames[index];
			}
			else{
            	throw std::invalid_argument( "received invalid frametype value" );
				return frames[0];
			}
		}

		void createEmptyVideo(int framenumber, int resolutionRow, int resolutionColumn ){
			frameNumber = framenumber;
			if (frameNumber > 0) {
				for(int i = 0; i < frameNumber; i++) frames.push_back(RGBFrame(i, resolutionRow, resolutionColumn)); 
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
		int getFrameNumber(int resolutionRow, int resolutionColumn,long filesize){
			int bytesPerFrame;
			long frame_number;

			bytesPerFrame = resolutionRow * resolutionColumn * 4;//16 + 16 + 16 =48
			frame_number = ( filesize / bytesPerFrame );

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
				uint8_t *RGB = (uint8_t *)malloc(size);

				size_t result = fread(RGB,1,size,file);
				uint8_t *byte = RGB;
				int iVal;
				
				for (int i = 0; i < frameNumber; i++){
					//read data for Y plane
					for (int row =0; row < frames[i].R.numberOfRow; row++){
						for (int col =0; col < frames[i].R.numberOfColumn; col++){
							frames[i].R.setData(row,col,*byte);
							byte++;
						}
					}
				
					//read data for U plane
					for (int row =0; row < frames[i].G.numberOfRow; row++){
						for (int col =0; col < frames[i].G.numberOfColumn; col ++){
							frames[i].G.setData(row,col,*byte);
							byte++;

						}
					}
				
					//read data for V plane
					for (int row =0; row < frames[i].B.numberOfRow; row++){
						for (int col =0; col < frames[i].B.numberOfColumn; col ++){
							frames[i].B.setData(row,col,*byte);
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
#endif