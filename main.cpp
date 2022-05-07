#include "bits/stdc++.h"
#include <pthread.h>
using namespace std;

/*
How to use the file::
- Build using "g++ main.cpp" command 
- Run by ""./a.out T" command 
*/

struct threadInp
{
int numOfThreads,r0,r1;
} ;

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

void *Worker(void * tInput){
    threadInp * n = (threadInp *) tInput;
    int range0 = n->r0;
    int range1 = n->r1;
    cout<<"ThreadID="<<n->numOfThreads<<", startNum="<<range0<<", endNum="<<range1<<endl;
    for (int i=range0;i<range1;i++){
        totalNums++;
        if(isPrime(i)){
            numOfPrimes++;
            primeList.push_back(i);
            
        } 
     } 
       
      pthread_exit(NULL);   
}



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
    // create threads array
    pthread_t threads[T]; 

    // find true range range 1 - range 0
    // find stepSize = (floor(range/T));

    int stepSize = floor((range1 - range0)/T); 
    // find remainingSteps = range mod T ; 
    int remainingSteps = (range1 - range0) % T; 

    // this is psuedo code for the dividing range for threads 
    
    int startRange = range0;
    int endRange = startRange + stepSize;
    threadInp tInput[T];
    for(int i=0;i<T;i++){
        if(T>(range1-range0)){
            cout<<"You Just Saved : "<<T-(range1-range0)<<endl;
            T=range1-range0;
        }
        if(remainingSteps){
            endRange++;
            remainingSteps--;
        }
        // create thread number i ;
        
        tInput[i].numOfThreads = i;
        tInput[i].r0 = startRange;
        tInput[i].r1 = endRange;
        int rc = pthread_create(&threads[i], NULL,Worker,&tInput[i]);  
        if (rc)
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
        startRange = endRange;
        endRange = endRange + stepSize;

    }
    

    //all threads are done,(join)
    for (int i = 0; i <T; i++)
    {
        pthread_join(threads[i],NULL);
    }
     
    

    //print the total number of prime numbers found (STDOUT)
   // cout<<"numOfPrime="<<numOfPrimes<<", totalNums="<<totalNums<<endl;

    //print all these numbers. (out.txt)
    write("The prime numbers are:");
    for(auto i=primeList.begin();i!=primeList.end();i++){
        write(to_string(*i));
    }

    return 0;
}
