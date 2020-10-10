#include<iostream>
#include <cstring>
using namespace std;

class Plane{
	private:
		uint8_t ** matrix;
	public:
	  
		int numberOfRow;
		int numberOfColumn;
		int block_x;
		int block_y;
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
	    	if (row < numberOfRow || col < numberOfColumn){
				matrix[row][col] = data;
			}
			else{
				cout << "the value could not be set" <<"\n";
			}
	  	} 

		//reset the size of the plan and update corresponding attribute
		void resetSizeEmptyData(int newRow, int newCol){
			delete(matrix);
			numberOfRow = newRow;
			numberOfColumn = newCol;
			matrix = new uint8_t*[numberOfRow];
			for(int i = 0; i < numberOfRow; i++)
			matrix[i] = new uint8_t[numberOfColumn]; 
		}

		void  resetSizePadding(int newRow, int newCol, uint8_t padding_value){
			uint8_t ** newMatrix = new uint8_t*[newRow];
			for(int i = 0; i < newRow; i++) newMatrix[i] = new uint8_t[newCol];

			for (int row =0; row < newRow; row++){
				for (int col =0; col < newCol; col ++){
					if (row >= numberOfRow || col >= numberOfColumn){
						newMatrix[row][col] = (uint8_t) padding_value;
					}
					else{
						newMatrix[row][col] = matrix[row][col];
					}
				}
			}
			delete(matrix);
			matrix = newMatrix;
			// matrix =  new uint8_t*[newRow];
			// for(int i = 0; i < newRow; i++) matrix[i] = new uint8_t[newCol];
			// memcpy(matrix, newMatrix,newRow*newCol);
			// delete(newMatrix);

		}

		void blockTruncation(int block_width, int block_height,uint8_t paddingValue){
			this->block_x = block_width;
			this->block_y = block_height;
			int xPadding = 0, yPadding = 0;
			if (numberOfColumn % block_width != 0){
				xPadding = block_height - numberOfColumn % block_height;
			} 
			if (numberOfRow % block_height != 0){
				yPadding = block_width - numberOfRow % block_width;
			}
				resetSizePadding(numberOfRow + yPadding,numberOfColumn + xPadding, paddingValue);
				this->numberOfRow = numberOfRow + yPadding;
				this->numberOfColumn = numberOfColumn + xPadding;
			
		}
		
};



