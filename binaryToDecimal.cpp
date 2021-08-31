// Program: Binary To Decimal
// This: binaryToDecimal.cpp
// Author: N. Honold
// Professor: Dr. Lucas Vespa
// Date: 8/23/2021
// Purpose:Take a binary number and output the decimal value of that number 

#include <iostream>
#include <string>
using namespace std;

//========================== int exp() =========================
// to do basic exponential calculations 
int exp(int x, int y){
    int exponent = x;
    if ( y == 0)
        return 1;
    else if ( y ==1)
        return exponent;

    for(int count = 0; count < (y-1);count++){
        exponent = exponent * x;
    }
    return exponent;
}

//======================= string processBinary() ============================
// To take a string object that is in the form of binary and output 
// an integer that is in base 10
int processBinary(string binary){

    int length = binary.size();
    string output;
    int sum = 0;//tracks the running total of the base 10 value as while loop iterates
    int count = 0;//tracks place value 

    while(length >= 0){
        
        string character;
        character= binary[length - 1];
        int digit = atoi(character.c_str());
        sum += digit * exp(2,count);
        count++;
        length--;
    }
    return sum;
}

//========================= int main() ==========================
int main(){

    cout << "===== Binary to Decimal ====="<< endl << endl;
        
    string original;
    cout<< "Please enter a binary number here: ";
    cin>>original;
    cout<<endl;
    cout<< "The decimal representation of "<< original<< " is: "
        << processBinary(original)<<endl;

    return 0;
}