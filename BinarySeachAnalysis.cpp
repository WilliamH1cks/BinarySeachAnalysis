// BinarySeachAnalysis.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;

void doesExist(int, int);

int recursiveBiSearch(const vector<int>& arr, int target, int low, int high)
{
    if (low <= high)
    {
        int mid = low + ((high - low) / 2);

        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            return recursiveBiSearch(arr, target, mid + 1, high);
        else
            return recursiveBiSearch(arr, target, low, mid - 1);
    }
    else
        return -1;
}

int iterativeBiSearch(const vector<int>& arr, int target)
{
    int low = 0;
    int high = arr.size() - 1;

    while (low <= high)
    {
        int mid = low + ((high - low) / 2);

        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

int seqSearch(const vector<int>& arr, int target)
{
    for (int i = 0; i < arr.size(); i++)
        if (arr[1] == target)
            return i;

    return -1;
}

int main()
{
    vector<int> arr = { 1, 2, 3, 4, 5, 10, 20, 30, 40, 50 };
    int target1 = 5;
    int target2 = 12;

    int RBSresult1 = recursiveBiSearch(arr, target1, 0, arr.size() - 1);
    doesExist(RBSresult1, target1);
    int RBSresult2 = recursiveBiSearch(arr, target2, 0, arr.size() - 1);
    doesExist(RBSresult2, target2);

    int IBSresult1 = iterativeBiSearch(arr, target1);
    doesExist(IBSresult1, target1);
    int IBSresult2 = iterativeBiSearch(arr, target2);
    doesExist(IBSresult2, target2);

    int seqResult1 = seqSearch(arr, target1);
    doesExist(seqResult1, target1);
    int seqResult2 = seqSearch(arr, target2);
    doesExist(seqResult2, target2);
}

void doesExist(int location, int target)
{
    if (location == -1)
        cout << "Element " << target << " not found in array" << endl;
    else
        cout << "Element " << target << " found at index " << location << endl;
}