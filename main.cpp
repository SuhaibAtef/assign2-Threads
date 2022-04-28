#include "bits/stdc++.h"

using namespace std;
int numOfPrimes=0,totalNums=0;
vector <int> primeList;
/*

When any of the threads starts executing, it will print its number (0 to T-1), and then the range of
    numbers that it is operating on. 
    
*/
bool isPrime(int num){
    for(int i=2;i<num;i++){
        if(num%i==0)return false;
    }
    return true;
}

void write(string s) {
        fstream file;
        file.open("out.txt", ios_base::app);
        file << s << endl;
        file.close();
}

int main() {
    int range0,range1;
    fstream file;
    file.open("in.txt");
    if (!file)
        cout << "no file with this name" << endl;
    else
    {
        file >> range0 >>range1;
    }
    file.close();

    for (int i=range0;i<range1;i++){
        totalNums++;
        if(isPrime(i)){
            numOfPrimes++;
            primeList.push_back(i);
        }
    }  
    /*
    // floor((range 1 - range 0 )/T) 
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
