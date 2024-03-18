// BinarySeachAnalysis.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <random>
using namespace std;

void doesExist(int location, int target)
{
    if (location < 0)
        cout << "Element " << target << " not found in array" << endl;
    else
        cout << "Element " << target << " found at index " << location << endl;
}

int ranNumGen()
{
    int rangeMax = 10;

    mt19937 rng(random_device{}());

    uniform_int_distribution<int> distribution(1, rangeMax);

    int randomNumber = distribution(rng);
    //cout << "Random Number: " << randomNumber << endl;

    return randomNumber;
}

void merge(vector<int> vec, int low, int high, int mid)
{
    int const leftSize = mid - low;
    int const rightSize = high - mid + 1;

    vector<int> left(leftSize);
    vector<int> right(rightSize);

    //for (int i = 0; i < leftSize; i++)
        //left[i] = vec[low + i];
    //for (int i = 0; i < rightSize; i++)
        //right[i] = vec[mid + 1 + i];

    //int leftIndex = 0;
    //int rightIndex = 0;
    size_t leftIndex = 0;
    size_t rightIndex = 0;
    //int mergedIndex = low;

    while (leftIndex < leftSize && rightIndex < rightSize)
    {
        
        if (left[leftIndex] >= right[rightIndex])
        {
            vec.push_back(left[leftIndex]);
            //leftIndex++;
        }
        else
        {
            vec.push_back(right[rightIndex]);
            //rightIndex++;
        }
        //mergedIndex++;
    }

    while (leftIndex < leftSize)
    {
        //vec[mergedIndex] = left[leftIndex];
        vec.push_back(left[leftIndex]);
        //leftIndex++;
        //mergedIndex++;
    }

    while (rightIndex < rightSize)
    {
        //vec[mergedIndex] = right[rightIndex];
        vec.push_back(right[rightIndex]);
        //rightIndex++;
        //mergedIndex++;
    }

    return;
    //This comment is added toensure the latest version is committed to github
}

void mergeSort(vector<int> vec, int const begin, int const end)
{
    if (begin >= end)
        return;

    int mid = vec.size() / 2;
    mergeSort(vec, 0, mid);
    mergeSort(vec, mid + 1, vec.size());
    merge(vec, 0, mid, vec.size());

    cout << "Test:     ";
    for (int i = 0; i < vec.size(); i++)
        cout << vec[i] << " ";
    cout << endl;
}

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

int seqSearch(const vector<int>& vec, int target)
{
    for (int i = 0; i < vec.size(); i++)
        if (vec[i] == target)
            return i;

    return -1;
}

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

    mergeSort(vec, 0, vec.size() - 1);

    cout << "Sorted: ";
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