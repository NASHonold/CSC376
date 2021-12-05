#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <locale>
using namespace std;


struct regAccInd
{ //Accumulator and Index register
    union
    {
        struct
        {
            unsigned int right8 : 8;
            unsigned int left8 : 8;
        };
        unsigned int full : 16;
    };
};

typedef union
{ // This holds the structs to divide the 8bit instructions
    struct
    {
        unsigned int r1 : 1;
        unsigned int instr7 : 7;
    } unary; //Unary instructions (0000 000r)

    struct
    {
        unsigned int aaa3 : 3;
        unsigned int instr5 : 5;
    } ioTrap; //I/O instructions (0000 0aaa)

    struct
    {
        unsigned int aaa3 : 3;
        unsigned int r1 : 1;
        unsigned int instr4 : 4;
    } arith; //Arithmetic instructions (0000 raaa)

    unsigned int full : 8;
} instructions;

typedef union
{
    struct
    {
        unsigned int right8 : 8;
        unsigned int left8 : 8;
    };
    unsigned int full : 16;
} bit16Struct;

//opSpec, operand, tempValue, tempAddress

struct Registers
{

    unsigned int programCounter : 16;
    regAccInd accumulator;
    regAccInd iRegister;
    instructions instruct;
    bit16Struct oSpec;
    bit16Struct operand;
    bit16Struct tempAddress;
    bit16Struct tempVal;
};

bool printDetails(Registers cpu, int mainMem[]){
    cout << "==================== DETAILS =================="<< endl;
    cout << "Instruction nibble: " << dec << cpu.instruct.arith.instr4 << " Instruction Register: " << cpu.instruct.arith.r1 <<
    " Instruction addressing mode: " << cpu.instruct.arith.aaa3 << endl;
    cout << "oSpec left:" << hex << cpu.oSpec.left8 << endl;
    cout << "oSpec right:" << cpu.oSpec.right8 << endl;
    cout << "Temp address left:" << cpu.tempAddress.left8 << endl;
    cout << "Temp address right:" << cpu.tempAddress.right8 << endl;
    cout << "Value at Left temp address:" << mainMem[cpu.tempAddress.full] << endl;
    cout << "Value at right temp address:" << mainMem[cpu.tempAddress.full + 1] << endl;
    int value = mainMem[cpu.tempAddress.full] + mainMem[cpu.tempAddress.full + 1];
    cout << "Value at full temp address:" << (mainMem[cpu.tempAddress.full] + mainMem[cpu.tempAddress.full + 1]) << endl;
    cout << "Current operand: " << cpu.operand.full << endl;
    cout << "Current accumulator: " << cpu.accumulator.full << endl;
    cout << "Current Index Register: " << cpu.iRegister.full << endl;
    return true;
    
}


bool printCpu(Registers cpu){
    cout << "================== Registers =================="<< endl;
    cout << "Program Counter: " << dec << cpu.programCounter << endl;
    cout << "Accumulator: " << hex << cpu.accumulator.full << endl;
    cout << "Index Register: " << hex << cpu.iRegister.full << endl;
    cout << "Instruction Byte: " << hex << cpu.instruct.full << endl;
    cout << "Operand Specifier: " << hex << cpu.oSpec.full << endl;
    cout << "Operand: " << hex << cpu.operand.full << endl;

    return true;

}

int main(int argc, char const *argv[])
{

    //Intro and directions
    cout << "======================= PEP/8 Simulator =======================\n"
         << "This will allow you to input a set of hexadecimal instructions\n"
         << "through the use of a .txt file and will show registers for every\n"
         << "set of instructions and the output in the end " << endl;
    bool selection = false;
    ifstream inputFile;
    string fileName;

    while (!selection)
    { //takes file name from user until
        cout << "\nPlease type in the file name located\n"
             << "in the same directory as this .exe file. \nEx. \"filename.txt\"\n"
             << "File name: ";
        cin >> fileName;
        inputFile.open(fileName);
        if (inputFile.is_open())
        {
            selection = true;
        }
        else
        {
            cout << "\n\n***********************************\n"
                 << "That is not a valid file name or\n"
                 << "the file you input is not found!\n"
                 << "Try again...\n"
                 << "***********************************" << endl;
        }
    };

    cout << "Instructions have been loaded..."
         << "\nPerforming operations...\n\n"
         << endl;

    int mainMem[10000]; //setting up memory
    int x;
    int mainMemIndex = 0;

    if (!inputFile.is_open())
    {
        cout << "This is not a valid file. Please try again.";
    }
    else
    {
        while (inputFile >> hex >> x)
        {
            mainMem[mainMemIndex] = x;
            mainMemIndex++;
        }
    }

    //create the cpu
    Registers cpu;
    cpu.programCounter = 0;
    cpu.accumulator.full = 0;
    cpu.iRegister.full = 0;
    cpu.instruct.full = 0;
    cpu.oSpec.full = 0;
    cpu.operand.full = 0;
    cpu.tempAddress.full = 0;
    cpu.tempVal.full = 0;


    //read in the first byte into cpu
    cpu.instruct.full = mainMem[cpu.programCounter++];

    while (cpu.instruct.full != 0)
    {
   
        bool directAddress;
        bool regSelect;

        if (cpu.instruct.arith.instr4 == 1)
        { // this checks for unary operator
            cpu.operand.full = 0;
            bool toIndex = cpu.instruct.unary.r1; // boolean check for where the unary operator is pointing to

            if (cpu.instruct.unary.instr7 == 12)
            { //bitwise invert r
                if (toIndex)
                {
                    cpu.iRegister.full = ~cpu.iRegister.full;
                }
                else
                {
                    cpu.accumulator.full = ~cpu.accumulator.full;
                }
            }
            else if (cpu.instruct.unary.instr7 == 14)
            { //shift left r
                if (toIndex)
                {
                    cpu.iRegister.full = cpu.iRegister.full << 1;
                }
                else
                {
                    cpu.accumulator.full = cpu.accumulator.full << 1;
                }
            }
            else
            { //shift right r
                if (toIndex)
                {
                    cpu.iRegister.full = cpu.iRegister.full >> 1;
                }
                else
                {
                    cpu.accumulator.full = cpu.accumulator.full >> 1;
                }
            }
            printDetails(cpu, mainMem);
        }

        if (cpu.instruct.arith.instr4 == 2)
        {
            cpu.operand.full = 0;
            bool toIndex = cpu.instruct.unary.r1; // boolean check for where the unary operator is pointing to
            if (cpu.instruct.unary.instr7 == 16)
            { // rotation to left
                if (toIndex)
                {
                    cpu.iRegister.full = (cpu.iRegister.full << 1) + (cpu.iRegister.full >> 15);
                }
                else
                {
                    cpu.accumulator.full = (cpu.accumulator.full << 1) + (cpu.accumulator.full >> 15);
                }
            }
            else if (cpu.instruct.unary.instr7 == 17)
            { // rotation to right
                if (toIndex)
                { // points to index
                    cpu.iRegister.full = (cpu.iRegister.full >> 1) + (cpu.iRegister.full << 15);
                }
                else
                { // points to accumulator
                    cpu.accumulator.full = (cpu.accumulator.full >> 1) + (cpu.accumulator.full << 15);
                }
            }
            printDetails(cpu, mainMem);
        }
        // this grabs the next instructions and places them in ospec with the left and right bytes respectively ******

        if (cpu.instruct.ioTrap.aaa3 == 1) //
        {                                  //captures a boolean value to use later for addressing mode and register
            directAddress = true;
        }
        else
        {
            directAddress = false;
        }
        //==============================================================================

        if (cpu.instruct.arith.instr4 > 2)

        { //load the next instructions
            regSelect = cpu.instruct.arith.r1;
            cpu.oSpec.left8 = mainMem[cpu.programCounter++];
            cpu.oSpec.right8 = mainMem[cpu.programCounter++];

            if (!directAddress)
            {
                cpu.operand.full = cpu.oSpec.full;
            }
            else
            {
                cpu.tempAddress.left8 = cpu.oSpec.left8;
                cpu.tempAddress.right8 = cpu.oSpec.right8;

            }
        }
        //=============================================================================== ********

        if (cpu.instruct.arith.instr4 == 3) // this is decimal input trap
        {

            if (cpu.instruct.ioTrap.instr5 == 6)
            { // only direct addressing
                int input;
                cin >> input;
                cout << endl;

                cpu.tempVal.full = input; // capture decimal

                mainMem[cpu.tempAddress.full] = cpu.tempVal.left8;      //assign the left 8 bits to the address in mem
                mainMem[cpu.tempAddress.full + 1] = cpu.tempVal.right8; //assign the right 8 bits in next position in array

            }
            else if (cpu.instruct.ioTrap.instr5 == 7)
            { //decimal out trap with direct and immediate addressing
                // get user decimal input
                unsigned int decimalOut;

                if (directAddress)
                { // True means address mode is direct

                    cpu.operand.left8 = mainMem[cpu.tempAddress.full];
                    cpu.operand.right8 = mainMem[cpu.tempAddress.full + 1];

                    cpu.tempVal.full = cpu.operand.full;

                }
                else
                { // immediate addressing
                
                    cpu.tempVal.full = cpu.operand.full;
                }

                cout << "Decimal Output: " << cpu.tempVal.full << endl;
            }
            printDetails(cpu, mainMem);
        }

        if (cpu.instruct.arith.instr4 == 4)//char input
        { 
            char input;
            cout << "Input: ";
            cin >> input;
            cout << endl;
            int charInt = input;
            cpu.operand.full = charInt;
            mainMem[cpu.tempAddress.full] = charInt;
            printDetails(cpu, mainMem);
        }

        if (cpu.instruct.arith.instr4 == 5)// char output with direct and immediate addressing

        { 
            char charOut;

            if (directAddress)// direct addressing
            { 

                cpu.operand.full = mainMem[cpu.tempAddress.full];
                charOut = (char)cpu.operand.full;
            }
            else// immediate addressing
            { 
                cpu.operand.full = cpu.oSpec.full;
                charOut = (char)cpu.operand.full;
            }

            cout << "Character Output: " << charOut << endl;
            printDetails(cpu, mainMem);
        }

        if (cpu.instruct.arith.instr4 == 7)// Add to R
        {

            if (regSelect)// add to Index Register
            {
                if (!directAddress) // immediate addressing mode
                {
                    cpu.iRegister.full += cpu.operand.full;
                }
                else// direct addressing 
                {

                    cpu.operand.left8 = mainMem[cpu.tempAddress.full];
                    cpu.operand.right8 = mainMem[cpu.tempAddress.full + 1];
                    cpu.iRegister.full += cpu.operand.full;
                    //this is direct addressing to index register
                }
            }
            else// add to Accumulator regiseter
            { 
                if (!directAddress) // immediate addressing mode
                {
                    cpu.accumulator.full += cpu.operand.full;
                }
                else// direct addressing
                {
                    cpu.operand.left8 = mainMem[cpu.tempAddress.full];
                    cpu.operand.right8 = mainMem[cpu.tempAddress.full + 1];
                    cpu.accumulator.full += cpu.operand.full;
                }
            }
            printDetails(cpu, mainMem);
        }

        if (cpu.instruct.arith.instr4 == 8)
        {
            if (regSelect)// Index register selected
            {
                if (!directAddress)//
                {
                    cpu.iRegister.full -= cpu.operand.full;
                }
                else
                {
                    cpu.operand.left8 = mainMem[cpu.tempAddress.full];
                    cpu.operand.right8 = mainMem[cpu.tempAddress.full + 1];
                    cpu.iRegister.full -= cpu.operand.full;
                    //this is direct addressing to index register
                }
            }
            else
            { // Accumulator selected
                if (!directAddress)
                {
                    cpu.accumulator.full -= cpu.operand.full;
                }
                else
                {
                    cpu.operand.left8 = mainMem[cpu.tempAddress.full];
                    cpu.operand.right8 = mainMem[cpu.tempAddress.full + 1];
                    cpu.accumulator.full -= cpu.operand.full;
                    //this is direct addressing to accumulator
                }
            }
            printDetails(cpu, mainMem);
        }

        if(cpu.instruct.arith.instr4 == 9){
            if (regSelect)
            {
                if (!directAddress)
                {
                    cpu.iRegister.full &= cpu.operand.full;
                }
                else
                {

                    cpu.operand.left8 = mainMem[cpu.tempAddress.full];
                    cpu.operand.right8 = mainMem[cpu.tempAddress.full + 1];
                    cpu.iRegister.full &= cpu.operand.full;
                    //this is direct addressing to index register
                }
            }
            else
            { //accumulator selected
                if (!directAddress)
                {
                    cpu.accumulator.full &= cpu.operand.full;
                }
                else
                {
                    cpu.operand.left8 = mainMem[cpu.tempAddress.full];
                    cpu.operand.right8 = mainMem[cpu.tempAddress.full + 1];
                    cpu.accumulator.full &= cpu.operand.full;
                    //this is direct addressing to accumulator
                }
            }
           printDetails(cpu, mainMem); 

        }
        if(cpu.instruct.arith.instr4 == 10){
            if (regSelect)
            {
                if (!directAddress)
                {
                    cpu.iRegister.full |= cpu.operand.full;
                }
                else
                {

                    cpu.operand.left8 = mainMem[cpu.tempAddress.full];
                    cpu.operand.right8 = mainMem[cpu.tempAddress.full + 1];
                    cpu.iRegister.full |= cpu.operand.full;
                    //this is direct addressing to index register
                }
            }
            else
            { //accumulator selected
                if (!directAddress)
                {   // immediate addressing
                    cpu.accumulator.full |= cpu.operand.full;
                }
                else
                {
                    //this is direct addressing to accumulator
                    cpu.operand.left8 = mainMem[cpu.tempAddress.full];
                    cpu.operand.right8 = mainMem[cpu.tempAddress.full + 1];
                    cpu.accumulator.full |= cpu.operand.full;
                    
                }
            }
            printDetails(cpu, mainMem);
            
        }
        if(cpu.instruct.arith.instr4 == 12){
            if (regSelect)
            {
                if (!directAddress)
                {
                    cpu.iRegister.full = cpu.operand.full;
                }
                else
                {

                    cpu.operand.left8 = mainMem[cpu.tempAddress.full];
                    cpu.operand.right8 = mainMem[cpu.tempAddress.full + 1];
                    cpu.iRegister.full = cpu.operand.full;
                    //this is direct addressing to index register
                }
            }
            else
            { //accumulator selected
                if (!directAddress)
                {
                    cpu.accumulator.full = cpu.operand.full;
                }
                else
                {
                    cpu.operand.left8 = mainMem[cpu.tempAddress.full];
                    cpu.operand.right8 = mainMem[cpu.tempAddress.full + 1];
                    cpu.accumulator.full = cpu.operand.full;
                    //this is direct addressing to accumulator
                }
            }
            printDetails(cpu, mainMem);
              
        }
        if(cpu.instruct.arith.instr4 == 13){
            if (regSelect)
            {
                if (!directAddress)
                {
                    cpu.iRegister.full = cpu.operand.full;
                }
                else
                {

                    cpu.operand.full = mainMem[cpu.tempAddress.full];
                    cpu.iRegister.full = cpu.operand.full;
                    //this is direct addressing to index register
                }
            }
            else
            { //accumulator selected
                if (!directAddress)
                {
                    cpu.accumulator.full = cpu.operand.full;
                }
                else
                {
                    cpu.operand.full = mainMem[cpu.tempAddress.full];
                    cpu.accumulator.full = cpu.operand.full;
                    //this is direct addressing to accumulator
                }
            }
            printDetails(cpu, mainMem);
        }
        if(cpu.instruct.arith.instr4 == 14){
            if (regSelect)
            {
                
                    cpu.operand.full = cpu.iRegister.full;
                    mainMem[cpu.tempAddress.full] = cpu.operand.left8;
                    mainMem[cpu.tempAddress.full + 1] = cpu.operand.right8;
                    //this is direct addressing to index register
                
            }
            else
            { //accumulator selected
                cpu.operand.full = cpu.accumulator.full;
                    mainMem[cpu.tempAddress.full] = cpu.operand.left8;
                    mainMem[cpu.tempAddress.full + 1] = cpu.operand.right8;
            }
            printDetails(cpu, mainMem);
        }
        if(cpu.instruct.arith.instr4 == 15){
            if (regSelect)
            {
                
                    cpu.operand.full = cpu.iRegister.full;
                    mainMem[cpu.tempAddress.full] = cpu.operand.full;
                    //this is direct addressing to index register
                
            }
            else
            { //accumulator selected
                cpu.operand.full = cpu.accumulator.full;
                mainMem[cpu.tempAddress.full] = cpu.operand.full;
            }
            printDetails(cpu, mainMem);

        }

        printCpu(cpu);

        cpu.tempVal.full = 0;
        cpu.tempAddress.full = 0;
        cpu.instruct.full = mainMem[cpu.programCounter++];
    }
    

    return 1;
}
