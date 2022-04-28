#include "bits/stdc++.h"
#include <pthread.h>
using namespace std;

/*
How to use the file::
- Build using "g++ main.cpp" command 
- Run by ""./a.out T" command 
*/

// Global Variables 
int numOfPrimes=0,totalNums=0;
vector <int> primeList;

// isPrime function that tests if the number(num) is prime or not.
bool isPrime(int num){
    for(int i=2;i<num;i++){
        if(num%i==0)return false;
    }
    return true;
}

// write function that appends the text(s) to the out.txt file. 
void write(string s) {
        fstream file;
        file.open("out.txt", ios_base::app);
        file << s << endl;
        file.close();
}

/*
// worker function (numberoftheThread,range 0 ,range 1){
    // print its number (0 to T-1)(numberoftheThread) and the range of numbers that it is operating on. 
    format=="ThreadID=0, startNum=1000, endNum=1050"

    // check is prime for all the numbers in range  (check for Basic isPrime Test implementation)


    //v2 note : add thread-safe code
}
    
*/


int main(int argc, char *argv[]) {
    //variables 
    int range0,range1,T;

    //Files 
    fstream file;
    file.open("out.txt",ios::out);
    file.close();
    file.open("in.txt");

    //Arguments 
    if(argv[1] !=NULL)
        T= atoi(argv[1]) ;
    else T=1;
        cout<<T<<endl;


    //Inputs:: Range 0 and Range 1 
    if (!file)
        cout << "no file with this name" << endl;
    else
    {
        file >> range0 >>range1;
    }
    file.close();

    /*Basic isPrime Test*/
    for (int i=range0;i<range1;i++){
        totalNums++;
        if(isPrime(i)){
            numOfPrimes++;
            primeList.push_back(i);
        }
    } 

     
    /*
    // create threads array 

    // find true range range 1 - range 0

    // find stepSize = (floor(range/T));

    // find remainingSteps = range mod T ; 

    // this is psuedo code for the dividing range for threads 

    pointer = startRange
    pointer2 = endRange = startRange + stepSize;  
    for(each thread){
        if(remainingSteps){
            endRange++;
            remaining--;
        }
        // create thread number i ; 
        startrange = endrange;
        endRange = endrange + stepSize;
    }
    */

    //all threads are done,(join) 
    
    //print the total number of prime numbers found (STDOUT)
    cout<<"numOfPrime="<<numOfPrimes<<", totalNums="<<totalNums<<endl;

    //print all these numbers. (out.txt)
    write("The prime numbers are:");
    for(auto i=primeList.begin();i!=primeList.end();i++){
        write(to_string(*i));
    }

    return 0;
}
