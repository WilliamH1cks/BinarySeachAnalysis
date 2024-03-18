// BinarySeachAnalysis.cpp : This file contains the 'main' function. Program execution begins and ends there
//

#include <iostream>
#include <vector>
#include <random>
using namespace std;

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
//      sorting said list, searching for a random valuye, and eventually seeing which of the three search methods is the quickest.
int main()
{
    //vector<int> arr = { 1, 2, 3, 4, 5, 10, 20, 30, 40, 50 };
    int size = 20;
    vector<int> vec(size);
    //cout << vec.size() << endl;
    for (int i = 0; i < vec.size(); i++)
    {
        int num = ranNumGen();
        vec[i] = num;
    }

    //Printing vector BEFORE sort
    cout << "Unsorted: ";
    for (int i = 0; i < vec.size(); i++)
        cout << vec[i] << " ";
    cout << endl;

    //THIS IS WHERE THE SORT LIES ONCE I HAVE IT WORKING
    sort(vec, 0, vec.size());

    cout << "Sorted:   ";
    //Printing vector AFTER sort
    for (int i = 0; i < vec.size(); i++)
        cout << vec[i] << " ";
    cout << endl;

    cout << "\nVector done, now for the target value..." << endl;
    int target1 = ranNumGen();

    int RBSresult1 = recursiveBiSearch(vec, target1, 0, vec.size() - 1);
    doesExist(RBSresult1, target1);
    //int RBSresult2 = recursiveBiSearch(vec, target2, 0, arr.size() - 1);
    //doesExist(RBSresult2, target2);

    int IBSresult1 = iterativeBiSearch(vec, target1);
    doesExist(IBSresult1, target1);
    //int IBSresult2 = iterativeBiSearch(vec, target2);
    //doesExist(IBSresult2, target2);

    int seqResult1 = seqSearch(vec, target1);
    doesExist(seqResult1, target1);
    //int seqResult2 = seqSearch(vec, target2);
    //doesExist(seqResult2, target2);
}