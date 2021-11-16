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

//==================== string flipString() ====================
//takes a given string and returns the reverse
string flipString(string toFlip){
    int length = toFlip.size();
    string flipped;
    for (length; length >= 0 ;length--){
        flipped += toFlip[length];
    }
    return flipped;

}
//==================== string toBinary() =======================
string toBinary(int decimal){
    int original = decimal;
    int remainder;
    string storage;
    while(decimal != 0){
        remainder = decimal % 2;
        decimal = decimal / 2;
        storage += to_string(remainder);
    }
    return flipString(storage);
}


struct regAccInd {     //Accumulator and Index registers
    union {
        struct {
            unsigned int right8 : 8;
            unsigned int left8 : 8;
        };
        unsigned int full : 16;
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
    } bit16Struct;

//opSpec, operand, tempValue, tempAddress

struct Registers{

unsigned int programCounter : 16;
regAccInd accumulator;
regAccInd index;
instructions instruct;
bit16Struct oSpec;
bit16Struct operand;
bit16Struct tempAddress;
bit16Struct tempVal;



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
    cout << "\n\n***********************************\n"<<
    "That is not a valid file name or\n" <<  
    "the file you input is not found!\n" <<
    "Try again...\n"<<
    "***********************************" << endl;
}
};

cout << "Instructions have been loaded..." << 
"\nPerforming operations...\n\n"<< endl;

int mainMem[10000];//setting up memory 
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

//create the cpu 
Registers cpu;
cpu.programCounter = 0;
cpu.accumulator.full = 0;
cpu.index.full = 0;
cpu.instruct.full = 0;
cpu.oSpec.full = 0;
cpu.operand.full = 0;
cpu.tempAddress.full = 0;
cpu.tempVal.full = 0;

/*
testing code------
*/

int testValue = 232;
cout << "THis is the testValue of 232 in hex: " << hex << testValue << endl;
cpu.accumulator.full = 49155;
cout << "Binary of the accumulator: " << toBinary(cpu.accumulator.full) << endl;
cout << "Current value in accumulator in hex: " << hex << cpu.accumulator.full << endl;

mainMem[0] = 30;

cout << "This is the first index of mem in hex:" << hex << mainMem[0]<< endl;

char testChar = 'A';
int charInt = testChar;
cout<< dec << charInt << endl;

/*
testing code------
*/



//read in the first byte into cpu
cpu.instruct.full = mainMem[cpu.programCounter++];

while(cpu.instruct.full != 0){

    if(cpu.instruct.arith.instr4 == 1){// this checks for unary operator
        cpu.operand.full = 0;
        bool toIndex = cpu.instruct.unary.r1;// boolean check for where the unary operator is pointing to

        if(cpu.instruct.unary.instr7 == 12){//bitwise invert r
            if(toIndex){
                cpu.index.full = ~cpu.index.full;
            }else{
                cpu.accumulator.full = ~cpu.accumulator.full;
            }

        }else if(cpu.instruct.unary.instr7 == 14){//shift left r
            if(toIndex){
                cpu.index.full = cpu.index.full << 1;
            }else{
                cpu.accumulator.full = cpu.accumulator.full << 1;
            }

        }else{//shift right r
            cout << "Shifting right-->" << endl;
            if(toIndex){
                cpu.index.full = cpu.index.full >> 1; 
            }else{
                cpu.accumulator.full = cpu.accumulator.full >> 1;
            }
        }
    }

    if(cpu.instruct.arith.instr4 == 2){
        cpu.operand.full = 0;
        bool toIndex = cpu.instruct.unary.r1;// boolean check for where the unary operator is pointing to
        if(cpu.instruct.unary.instr7 == 16){// rotation to left
            if(toIndex){
                cpu.index.full = (cpu.index.full << 1) + (cpu.index.full >> 15);
            }else{
                cpu.accumulator.full = (cpu.accumulator.full << 1) + (cpu.accumulator.full >> 15);
            }
        }else if( cpu.instruct.unary.instr7 == 17){// rotation to right
            if(toIndex){// points to index
                cpu.index.full = (cpu.index.full >> 1) + (cpu.index.full << 15);
            }else{// points to accumulator
                cpu.accumulator.full = (cpu.accumulator.full >> 1) + (cpu.accumulator.full << 15);
            }
        }
     // now we need to do the 2 traps

     // character i/o


    }
    cpu.instruct.full = mainMem[cpu.programCounter++];

}
cout <<"This is accumulator after inversion in hex: "<< hex << cpu.accumulator.full<< endl;
cout <<"This is accumulator after inversion in dec: "<< dec << cpu.accumulator.full<< endl;
cout << "Binary of the accumulator: " << toBinary(cpu.accumulator.full) << endl;

// I have taken in the instructions and assigned them to memory 
// need to have a way to print out the register values 
// need to actully process data










return 1;
}