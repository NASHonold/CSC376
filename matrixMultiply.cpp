// Program: Matrix Multiplier
// This: matrixMultiply.cpp
// Author: N. Honold
// Professor: Dr. Lucas Vespa
// Date: 8/23/2021
// Purpose:To multiply two 5x5 matrices and output a resulting 5x5 matrix 


#include <iostream>
using namespace std;

//================================ void printMatrix() ================================
//function to take a 5x5 matrix and print its values in a grid
void printMatrix(int matrix[][5]){
    int col;
    int row;

    for(row = 0; row<5; row++){
        if(row > 0)
            cout<<endl;
        for(col = 0; col<5;col++)
        cout<<matrix[row][col]<<" ";
    }
    cout<<endl<< "-------------------------------";


}

int main(){
    int matrixA[5][5] = {1,1,1,1,1,2,2,2,2,2,3,3,3,3,3,4,4,4,4,4,5,5,5,5,5};

    int matrixB[5][5] ={1,2,3,4,5,1,2,3,4,5,1,2,3,4,5,1,2,3,4,5,1,2,3,4,5};

    int result[5][5];

    //this is to capture the length of the rows and columns to be used
    //in the nested for loops when doing calculations
    int rows = sizeof(matrixA)/ sizeof(matrixA[0]);
    int columns = sizeof(matrixA[0]) / sizeof(int);

    
    //this is the outside loop to accomodate for the number or columns 
    //in the matrix
    for (int col = 0; col < columns; col++ ){
        //this loop accomodates for the number of rows
        for(int row = 0;row < rows; row++){
            int sum = 0;
            int count;
            
            //this loop does the calculation for each index for the 
            //result[][] matrix 
            for(count = 0;count < rows; count++){
                sum += matrixA[col][count] * matrixB[count][row];
                //condition if all of the products have been calculated and summed: 
                if(count == rows - 1){
                result[col][row] = sum;
                
                }
            }
        }
    }

    cout<< "====== Matrix Multiplier ======"<<endl;
    cout<< "The first 2d array is:"<<endl;
    printMatrix(matrixA);
    

    cout<<endl<< "The second 2d array is:"<<endl;
    printMatrix(matrixB);

    cout<<endl<< "The resulting array after multiplication:"<<endl;
    printMatrix(result);
    return 0;

}

    



