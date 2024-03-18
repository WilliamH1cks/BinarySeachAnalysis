// BinarySeachAnalysis.cpp : This file contains the 'main' function. Program execution begins and ends there
//

#pragma comment(linker, "/STACK:8000000")


#include <iostream>
#include <vector>
#include <random>
#include <chrono>
using namespace std;

int N = 5000;
double SumRBS = 0;
double SumIBS = 0;
double SumSeqS = 0;

//Precondition: The target value of the vector/list and its location is given (Location is -1 if the value doesn't appear in said array)
//Postcondition: Prints whether the list/vector/array has the target value, and at what location.
void doesExist(int location, int target)
{
    if (location < 0)
        cout << "Element " << target << " not found in array" << endl;
    else
        cout << "Element " << target << " found at index " << location << endl;
}


//Randomly generates integers from 1 to 100
int ranNumGen()
{
    int rangeMax = 100;

    mt19937 rng(random_device{}());

    uniform_int_distribution<int> distribution(1, rangeMax);

    int randomNumber = distribution(rng);
    //cout << "Random Number: " << randomNumber << endl;

    return randomNumber;
}

//Precond: An integer to search for in a vector is given
//Postcond: Returns the location (-1 if nonexistant) of the value through recursively dividing up the vector into smaller chunks.
int recursiveBiSearch(const vector<int>& vec, int target, int low, int high)
{
    
    if (low <= high)
    {
        int mid = high + low / 2;

        if (vec[mid] == target)
            return mid;
        else if (vec[mid] < target)
            return recursiveBiSearch(vec, target, mid + 1, high);
        else
            return recursiveBiSearch(vec, target, low, mid - 1);
    }
    else
        return -1;
}

//Precond: An integer to search for in a vector is given
//Postcond: Returns the location (-1 if nonexistant) of the value through iterating the vector into smaller chunks.
int iterativeBiSearch(const vector<int>& vec, int target)
{
    int low = 0;
    int high = vec.size() - 1;

    while (low <= high)
    {
        int mid = high + low / 2;

        if (vec[mid] == target)
            return mid;
        else if (vec[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

//Precond: An integer to search for in a vector is given
//Postcond: Returns the location (-1 if nonexistant) of the value through manually searching each entry, from start to finish.
int seqSearch(const vector<int>& vec, int target)
{
    for (int i = 0; i < vec.size(); i++)
        if (vec[i] == target)
            return i;

    return -1;
}

//Sorts the randomly-generated list for use of binary searches.
//  NOTE: While not the most efficient available, an insertion sort was used because otherwise my head would implode.
//        It's not that i do not understand the more complex sorts' functions or general behavior, but it is the constant errors
//        on vector overflowing and out-of-bounds that I did get tired of.
void sort(vector<int>& vec, int start, int end)
{
    for (int i = 1; i < vec.size(); i++)
    {
        if (vec[i] < vec[i - 1])
        {
            int temp = vec[i];
            int loc = i;

            while (loc > 0 && vec[loc - 1] > temp)
            {
                vec[loc] = vec[loc - 1];
                loc--;
            }

            vec[loc] = temp;
        }
    }
}

//A main program is a main program. This one happens to be for randomly generating a list,
//      sorting said list, searching for a random valuye, and seeing which of the three search methods is the quickest.
int main()
{
    for (int i = 0; i < 10; i++)
    {
        vector<int> vec(N);
        for (int i = 0; i < vec.size(); i++)
        {
            int num = ranNumGen();
            vec[i] = num;
        }

        sort(vec, 0, vec.size());

        //cout << "\nVector done, now for the target value..." << endl;
        int target1 = ranNumGen();

        auto start = chrono::high_resolution_clock::now();
        int RBSresult1 = recursiveBiSearch(vec, target1, 0, vec.size() - 1);
        auto end = chrono::high_resolution_clock::now();
        //doesExist(RBSresult1, target1);
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
        SumRBS += duration;


        start = chrono::high_resolution_clock::now();
        int IBSresult1 = iterativeBiSearch(vec, target1);
        end = chrono::high_resolution_clock::now();
        //doesExist(IBSresult1, target1);
        duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
        SumIBS += duration;
        

        start = chrono::high_resolution_clock::now();
        int seqResult1 = seqSearch(vec, target1);
        end = chrono::high_resolution_clock::now();
        //doesExist(seqResult1, target1);
        duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
        SumSeqS += duration;
    }

    cout << "Avg Running Time for Recursive Binary Search: " << SumRBS / 10 << " microseconds" << endl;
    cout << "Avg Running Time for Iterative Binary Search: " << SumIBS / 10 << " microseconds" << endl;
    cout << "Avg Running Time for Sequential Search:       " << SumSeqS / 10 << " microseconds" << endl;

    return 0;
}