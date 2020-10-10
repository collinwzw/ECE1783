#ifndef _Plane_h_
#define _Plane_h_
#include<iostream>
using namespace std;

class Plane{
	private:
		uint8_t ** matrix;
	public:
	  
		int numberOfRow;
		int numberOfColumn;

		//constructor for the Plane Object
		Plane(int resolutionRow, int resolutionColumn){
			numberOfRow = resolutionRow;
			numberOfColumn = resolutionColumn;
			matrix = new uint8_t*[numberOfRow];
			
			for(int i = 0; i < numberOfRow; i++) matrix[i] = new uint8_t[numberOfColumn]; 
		}

		//get Data according to the input argument row and col
	    // function need to improved with exception 
	  	uint8_t getData(int row, int col){
			if (row < numberOfRow && col < numberOfColumn){
				return matrix[row][col];
			}
			else{
				cout << "the value could not be set" <<"\n";
				return 0;
			}
	  	} 

		  
		//set Data according to the input argument row and col
	    // function need to improved with exception 
	  	void setData(int row, int col, uint8_t data){
	    	if (row < numberOfRow && col < numberOfColumn){
				matrix[row][col] = data;
			}
			else{
				cout << "the value could not be set" <<"\n";
			}
	  	} 

		//reset the size of the plan and update corresponding attribute
		void resetSize(int newRow, int newCol){
			delete(matrix);
			numberOfRow = newRow;
			numberOfColumn = newCol;
			matrix = new uint8_t*[numberOfRow];
			for(int i = 0; i < numberOfRow; i++)
			matrix[i] = new uint8_t[numberOfColumn]; 
		}

		//writing specific frame to file, update function to throw exception when failed to read.
		void writePlaneToFile(const char* file_name, bool overwrite){
			FILE *file;
			if (overwrite) 	file = fopen(file_name, "wb");
			else file = fopen(file_name, "ab");
			uint8_t byte;
			if(file!=NULL){
				for (int row =0; row < numberOfRow; row++){
					for (int col =0; col < numberOfColumn; col++){
						byte = getData(row,col);
						fwrite(&byte, 1, 1, file);
					}
					
				}
			}
			fclose(file);
		}
		
};



#endif