#include <iostream> 
#include <string>
#include <stdlib.h>
using namespace std;



void printMenu(){// Function to print menu for user
    cout<< "\n" << "============= Main Menu ============"<< endl;
    cout<< "Select from the choices below:\n" <<
    "\t1) Select memory address to cache" <<
    "\n\t2) View data that is in main memory" <<
    "\n\t3) View data in cache"<<
    "\n\t4) View number of cache misses"<<
    "\n\t0) Quit"<<endl;

}
void printMem(int *array){// will print all the data in memory for reference
    cout<< "========================= Main Memory =========================" << endl;
    cout<<"[";
    for( int i = 0; i < 256;i++){
        
        cout<< array[i];
        if(i != 255){
            cout<< ", ";
        }
        if(((i + 1) % 16) == 0 && i != 255){
            cout << "\n";
        }
    }
    cout<<"]";
}


int main(int argc, char const *argv[])
{

    int index; 
    int cacheIndices;

    int mainMem[256];
    int cacheValues[8];
    int indicesInCache[8];

    for(int i = 0; i < 256; i++){//creating data in main memory
        mainMem[i] = rand() % 255;
    }

    for (int i = 0; i < 8; i++)//setting up cache 
    {
        cacheValues[i] = -1;
        indicesInCache[i] = -1;
    }
    
    int cacheMisses = 0;
    int selection;
    
    do
    {
        printMenu();
        cout<< "Please enter your choice here: ";
        cin>>selection;
        switch (selection)
        {
        case 1/*Select main memory index to cache*/:
            int index;
            cout<< "Choose an address between 0 and 255: ";
            cin>> index; //get desired memory address from user
            if(index < 0 || index > 255){
                cout<< "You must pick an appropriate index."<< endl;
                break;
            }
            int cacheIndex;
            cacheIndex = index % 8;
            //cacheIndex = getCacheIndex(index);
            int compare;
            compare = indicesInCache[cacheIndex];
            if(compare != index){
                cacheMisses++;
            }
            cacheValues[cacheIndex] = mainMem[index];
            indicesInCache[cacheIndex] = index;
            cout<< "\nYou have assigned the data("<< mainMem[index] << ") at memory address " << index <<
            "\nto the cache at cache index: "<< cacheIndex<< endl;
            break;

        case 2/* view main memory */:
            printMem(mainMem);
            break;
        case 3/* view cache status */:
            cout<< "Data in the Cache:"<< endl;
            cout<< "==================="<< endl;
            for(int i = 0; i < 8;i++){
                cout<< "Cache Index: " << i << "---Memory Address Cached: " 
                << indicesInCache[i]
                << " ---Data Cached: "
                << cacheValues[i]
                << endl;
            }
            break;
        case 4/* view cache misses */:
        cout<< "=========== Cache Misses ============"<< endl;
            cout<< "The number of cache misses is currently: " << cacheMisses <<endl;
            cout<<"===================================="<<endl;
            break;
        case 0/* quit */:

            cout << "\n===== Final Cache Miss Count ======"<<
            "\n\t * " << cacheMisses<<" *"<<endl;
            cout<< "============ Goodbye! ============"<< endl;
            break;
        
        default:
        cout<< "\n******That is not a choice. Try again.******"<<endl;

            break;
        }
        /* code */
    } while (selection != 0);
    

   
   
}
