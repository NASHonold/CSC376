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
    for(int i = 0;i <8;i++){
        remainder = decimal % 2;
        decimal = decimal / 2;
        storage += to_string(remainder);
    }
    //cout << sizeof(storage) << endl;
    return flipString(storage);
}


//==================== bool isError() ========================
bool isError(string value){
    int count = 0;
    for (int i = 0; i <= 8; i++)
    {
        if(value[i] == '1'){
            count++;
        }
    }
    if( count % 2 == 0 /*&& value[8] == '1'*/){
        return false;
    }else{
        return true;
    }
}


//========================== main() ========================
int main(int argc, char const *argv[])
{
  int givenNumber;

  cout<< "What is your integer value between 0 and 255?"<< endl;
  cin >> givenNumber;
  
  string newString = toBinary(givenNumber);
  cout<< "Your number in binary is: " << newString<<endl;
  //cout << newString<< endl;
  if(isError(newString)){
      cout<< "There is a 1 bit error.";
  }else{
      cout<< "There is no error present.";
  }





}
