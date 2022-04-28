#include "bits/stdc++.h"

using namespace std;
// numOfPrimes&&TotalNums&&PrimeList
/*

When any of the threads starts executing, it will print its number (0 to T-1), and then the range of
    numbers that it is operating on. 
    
*/
void write(string s) {
        fstream file;
        file.open("out.txt", ios::out);
        file << s << endl;
        cout<<"s2"<<endl;
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
        cout<<range0<<endl;
    }
    file.close();

    /*

    */

    
    //all threads are done,(join) 
    
    //print the total number of prime numbers found (STDOUT)

    //print all these numbers. (out.txt)

    return 0;
}
