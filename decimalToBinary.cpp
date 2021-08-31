// Program: Decimal to Binary
// This: decimaToBinary.cpp
// Author: N. Honold
// Professor: Dr. Lucas Vespa
// Date: 8/23/2021
// Purpose:To take a user input of a decimal number and output that
//         value in binary


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
//======================== int main() =========================
int main(){
    cout<< "===== Decimal to Binary ====="<<endl<<endl;
    int quotient;

    cout<< "Please enter an integer here: ";
    cin>>quotient;
    cout<<endl;
    cout<< "The binary representation of " << quotient << " is: "<<
    toBinary(quotient);

    cout<< endl<<"Break-----------------"<< endl;
    cout<< endl;

    int original = quotient;
    int remainder;
    string storage;

    while(quotient != 0){
        remainder = quotient % 2;
        quotient = quotient / 2;
        storage += to_string(remainder);
    }

    cout<< "The binary representation of "
    << original << " is: " <<flipString(storage)<<endl;
return 0;
    
}