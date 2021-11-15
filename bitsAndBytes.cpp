// Program: Bits and Bytes
// This: bitsAndBytes.cpp
// Author: N. Honold
// Professor: Dr. Lucas Vespa
// Date: 8/30/2021
// Purpose:To take user input of IP address and allow bitwise manipulation
//         of it. 



#include <iostream>
#include <string>
using namespace std;

//============================ int main() =========================
int main(){

//====================== Structures and Unions =====================
struct components  {
    unsigned int right: 8 ;
    unsigned int rightMiddle: 8 ;
    unsigned int leftMiddle: 8 ;
    unsigned int left: 8 ;
};

union ipAddress {
 components parts;
 unsigned int entireAddress: 32;
};


ipAddress userIP; //creates the union and subordinate structure

//Getting IP address from user in 4 consecutive parts. 
    int userInput;
 
    cout<< "Input you IP address as 4 seperate lines"<<endl;

    cout <<  "First part:";
    cin>>userInput;
    userIP.parts.left = userInput;

    cout<<"Second part:";
    cin>>userInput;
    userIP.parts.leftMiddle = userInput;

    cout<<"Third part:";
    cin>>userInput;
    userIP.parts.rightMiddle = userInput;

    cout<<"Final part:";
    cin>>userInput;
    userIP.parts.right = userInput;

//getting the user choice for the IP address output
    cout<< "How would you like to see your IP address?"<<endl<< 
            "\t(1) Single value"<<
            "\n\t(2) Four Values"<<
            "\n\t(3) Two Values"<<
            "\n\t(4) A Single Bit Value" <<
            "\n\t(5) QUIT";

    int selection;
// main do while loop that allows for multiple manipulations of the same IP address
    do{
        
        cout<< endl<<"\nInput selection here: ";
        cin>> selection;
        switch (selection)
        {
        case 1:
            cout<< "As a single value: " << userIP.entireAddress;
            break;

        case 2:
            cout<< "As four values: "<< userIP.parts.left << "." 
            << userIP.parts.leftMiddle << "." 
            << userIP.parts.rightMiddle << "." 
            << userIP.parts.right;
            break;

        case 3:
            int addressBits;
            cout<< endl<<"How many bits in the network address:";
            cin>> addressBits; //inputting the number of bits

            int move; // intitializing the amount of bits to shift to shave off
            move = 32 - addressBits;

            int original;
            original = userIP.entireAddress; // capturing original 32bit integer for restoration later

            userIP.entireAddress = userIP.entireAddress << move;//shift left to shave off bits on left
            userIP.entireAddress = userIP.entireAddress >>move; // shift right to return to original position in memory

            int host;
            host = userIP.entireAddress;//assign the found value to variable right 

            userIP.entireAddress = original;//restoring original value
            userIP.entireAddress = userIP.entireAddress >> move;//shaving off value to right 
            
            int network;//assign found
            network = userIP.entireAddress;

            userIP.entireAddress = original;// restoring original value a final time
            cout<< endl<< "Two values with "<<  addressBits<< " network address bits: "
                << " Network: "<< network<< ", Host:"<< host; 
            break;

        case 4:
            int addressBit;
            cout<< endl<<"Which bit would you like to see: ";
            cin>> addressBit; //inputting the index of the bit 
            original = userIP.entireAddress;// capturing original value to restore later

            int moveRight;
            moveRight = addressBit;//this is the size of the shift to the right to clear those bits
            int moveLeft;
            moveLeft = 31 - addressBit;// size of shift to left to clear bits to the left

            userIP.entireAddress = userIP.entireAddress << moveLeft;//shaving bits on left
            userIP.entireAddress = userIP.entireAddress >> moveLeft;//returning to original position
            userIP.entireAddress = userIP.entireAddress >> moveRight;//shaving off bits to right 
           
            int bitValue;
            bitValue = userIP.entireAddress;//getting bit value
            userIP.entireAddress = original;//restoring IP address to original 32 bit integer
            cout << "\nThe bit at index " << addressBit << " is: " << bitValue;
            break;
            
        case 5:
            cout << "======== Goodbye! ========";
            break;
        
        default:
            break;
        }

    }while(selection != 5);









}