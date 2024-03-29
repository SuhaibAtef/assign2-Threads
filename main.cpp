#include "bits/stdc++.h"
#include <pthread.h>

using namespace std;

/*
How to use the file::
- Build using "g++ main.cpp" command
- Run by ""./a.out T" command
*/

pthread_mutex_t plock;

struct threadInp
{
    int numOfThreads, r0, r1;
    bool needed;
};

// Global Variables
int numOfPrimes = 0, totalNums = 0;
vector<int> primeList; // Vector to hold prime numbers.

// A function that appends the text(s) to the out.txt file.
void write(string s)
{

    fstream file;
    file.open("out.txt", ios_base::app);
    file << s << endl;
    file.close();
}

// Worker Thread that takes a range of numbers that consists of (range 1 - range 0) and tests if the numbers are prime or not.
void *Worker(void *tInput)
{

    threadInp *n = (threadInp *)tInput;

    // int range0 = n->r0;
    // int range1 = n->r1;
    if (!(n->needed))
    {
        pthread_exit(NULL);
    }
    for (int j = n->r0; j < n->r1; j++)
    {

        // if the number is prime increase the total prime numbers and push the number to the list.
        bool isPrime = true;
        for (int i = 2; i < j; i++)
        {
            if (j % i == 0)
                isPrime = false;
        }
        pthread_mutex_lock(&plock);
        if (isPrime)
        {
            numOfPrimes++;
            primeList.push_back(j);
        }
        totalNums++;
        pthread_mutex_unlock(&plock);
    }
    // cout << "Exited thread " << n->numOfThreads << "   ID:" << pthread_self() << endl;
    // cout << "EXIT" << pthread_self() << endl;
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    // variables
    int range0, range1, T;

    // Files
    fstream file;
    file.open("out.txt", ios::out);
    file.close();
    file.open("in.txt");

    // Arguments
    if (argv[1] != NULL)
    {
        // takes the argument as the number of threads.
        T = atoi(argv[1]);
        // Case:: number is negative or Zero.
        if (T <= 0)
        {
            T = 1;
            cout << "WRONG INPUT : Default Thread value (T=1) is used." << endl;
        }
    }

    else
    // Case:: No arguments were provided.
    {
        T = 1;
        cout << "NO ARGUMENTS WERE PROVIDED : Default Thread value (T=1) is used." << endl;
    }
    cout << "Number of choosen Threads: " << T << endl;

    // Case:: No input file in the directory.
    if (!file)
        cout << "no file with this name" << endl;
    else
    {
        file >> range0 >> range1;
    }
    file.close();
    primeList.reserve(range1 - range0);
    // Threads array to hold the threads.
    pthread_t *threads = new pthread_t[T];

    // StepSize = (floor(range/T));
    int stepSize = floor((range1 - range0 + 1) / T);

    // RemainingSteps = range mod T ;
    int remainingSteps = (range1 - range0 + 1) % T;

    /*
    Algorithm:  There are two pointers (startRange,endRange) that points to the start and end of the thread range
                the two pointers increase with amount that is equal to the stepSize.
    */

    int startRange = range0;
    int endRange = startRange + stepSize;
    threadInp tInput[T];
    // tInput = (struct threadInp *)malloc(T * sizeof(struct threadInp));
    if (T > (range1 - range0 + 1))
    {
        cout << "You Just Saved : " << T - (range1 - range0 + 1) << endl;
        // T = range1 - range0 + 1;
    }
    for (int i = 0; i < T; i++)
    {

        if (i >= (range1 - range0 + 1))
        {
            tInput[i].needed = false;
        }
        else
        {
            tInput[i].needed = true;
        }
        if (remainingSteps)
        {
            endRange++;
            remainingSteps--;
        }
        // Creating thread number i
        // 1) we declare the inputs for the thread.
        tInput[i].numOfThreads = i;
        tInput[i].r0 = startRange;
        tInput[i].r1 = endRange;
        // 2) we create the thread.
        int rc = pthread_create(&threads[i], NULL, Worker, (void *)(&tInput[i]));
        // Case:: no thread was created.
        if (rc)
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
        else
        {
            //
            if ((tInput[i].needed))
                cout << "ThreadID=" << tInput[i].numOfThreads << ", startNum=" << ((!(T > (range1 - range0 + 1)) && (i != 0)) ? tInput[i].r0 - 1 : tInput[i].r0) << ", endNum=" << tInput[i].r1 - 1 << endl;
            else
                cout << "ThreadID=" << tInput[i].numOfThreads << " Not needed" << endl;
        }
        // 3) we increase the pointers for the next thread.
        startRange = endRange;
        endRange = endRange + stepSize;
    }

    // (Joining Threads): all threads are done.
    for (int i = 0; i < T; i++)
    {
        // cout << "JOIN " << threads[i] << endl;
        pthread_join(threads[i], NULL);
    }

    // Printing the total number of prime numbers found (STDOUT)
    cout << "numOfPrime=" << numOfPrimes << ", totalNums=" << totalNums << endl;

    // Printing all these numbers. (out.txt)
    write("The prime numbers are:");
    for (auto i = primeList.begin(); i != primeList.end(); i++)
    {
        write(to_string(*i));
    }

    return 0;
}
