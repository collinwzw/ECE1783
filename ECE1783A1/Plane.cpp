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
			if (row < numberOfRow || col < numberOfColumn){
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
		void resetSize(int newRow, int newCol){
			delete(matrix);
			numberOfRow = newRow;
			numberOfColumn = newCol;
			matrix = new uint8_t*[numberOfRow];
			for(int i = 0; i < numberOfRow; i++)
			matrix[i] = new uint8_t[numberOfColumn]; 
		}
};



