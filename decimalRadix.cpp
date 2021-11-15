// Program: Decimal Radix
// This: decimalRadix.cpp
// Author: N. Honold
// Professor: Dr. Lucas Vespa
// Date: 9/17/2021
// Purpose:To take a user input of a decimal number and desired base and express that 
// (dec)integer in the given base 


#include <iostream>
#include <string>
using namespace std;

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
string toRadix(int decimal, int radix){
    int original = decimal;
    int remainder;
    string storage;
    while(decimal != 0){
        remainder = decimal % radix;
        decimal = decimal / radix;
        storage += to_string(remainder);
    }
    return flipString(storage);
}
//======================== int main() =========================
int main(){
    cout<< "===== Decimal to Radix Value ====="<<endl<<endl;
    int quotient;
    int base;

    cout<< "Please enter an integer here: ";
    cin>>quotient;
    cout<<endl;
    cout<< "Now enter the base value you would like to " << 
            "\nconvert to between 2 and 16: ";
    cin>>base; 
    string answer = toRadix(quotient, base);
    int original = quotient;
    int remainder;
    string storage;
    cout<<endl;

    cout<< "The radix expression of "
    << original << " with base "<< base << " is: " <<answer<<endl;
return 0;
    
}