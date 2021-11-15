#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <locale>
using namespace std;


/**
 * @brief Things I need to figure out
 * 
 */

//the registers: how will I store all of them and get them unioned up the right way?


//how do I parse that file line by line?
//I may be able to take 6 characters at a time and convert each into binary?
//then maybe I assign that to each struct?


//how do I convert this hex value to a binary value to be stored in registers and memory

//that should get me started


struct regAccInd {     //Accumulator and Index registers
    union {
        struct {
            unsigned int right8 : 4;
            unsigned int left8 : 4;
        };
        unsigned int full : 8;
    };
};

typedef union { // This holds the structs to divide the 8bit instructions
        struct {
            unsigned int r1 : 1;
            unsigned int instr7 : 7;
        } unary;    //Unary instructions (0000 000r)
        
        struct {
            unsigned int aaa3 : 3;
            unsigned int instr5 : 5;
        } ioTrap;    //I/O instructions (0000 0aaa)
        
        struct {
            unsigned int aaa3 : 3;
            unsigned int r1 : 1;
            unsigned int instr4 : 4;
        } arith;    //Arithmetic instructions (0000 raaa)
        
        unsigned int full : 8; 
    }instructions;

typedef union {
        struct {
            unsigned int right8 : 8;
            unsigned int left8 : 8;
        };
        unsigned int full : 16;
    } oSpec, operand, tempValue, tempAddress;



struct Registers{
unsigned int programCounter : 16;
regAccInd accumulator;
regAccInd index;
instructions instruct;





};

int main(int argc, char const *argv[])
{


//Intro and directions
cout<< "======================= PEP/8 Simulator =======================\n"<<
"This will allow you to input a set of hexadecimal instructions\n" <<
"through the use of a .txt file and will show registers for every\n"<<
"set of instructions and the output in the end "<< endl;
bool selection = false;
ifstream inputFile;
string fileName;

while(!selection){//takes file name from user until 
cout<< "\nPlease type in the file name located\n" << 
"in the same directory as this .exe file. \nEx. \"filename.txt\"\n" << 
"File name: ";
cin >> fileName;
inputFile.open(fileName);
if(inputFile.is_open()){
    selection = true;
}else{
    cout << "\n***********************************\n"<<
    "That is not a valid file name or\n" <<  
    "the file you input is not found!\n" <<
    "Try again...\n"<<
    "***********************************" << endl;
}
};

cout << "Instructions have been loaded..." << 
"\nPerforming operations...\n\n"<< endl;

int mainMem[10000];
int x;
int mainMemIndex = 0;

if(!inputFile.is_open()){
    cout << "This is not a valid file. Please try again.";
}else{
    while(inputFile >> hex >>  x){
        mainMem[mainMemIndex] = x;
        mainMemIndex++;
    }
}


// I have taken in the instructions and assigned them to memory 
// need to have a way to print out the register values 
// need to actully process data










return 1;
}