/**************************************************/
/*                                                */
/*  Lab 6				                          */
/*                                                */
/*  Name:  Ashwin Anand                           */
/*  Student number:  152042206                    */
/*                                                */
/**************************************************/

#include <cstdlib>
#include <iostream>
#include <fstream>


using namespace std;

void heapify(int arr[], int size, int currIdx)
{
    int currentRootIdx = currIdx;
    int leftChildIdx = currIdx * 2 + 1;
    int rightChildIdx = currIdx * 2 + 2;

    if (leftChildIdx < size && arr[currentRootIdx] > arr[leftChildIdx])
    {
        int temp = arr[currentRootIdx];
        arr[currentRootIdx] = arr[leftChildIdx];
        arr[leftChildIdx] = temp;
        currentRootIdx = leftChildIdx;
    }

    if (rightChildIdx < size && arr[currentRootIdx] > arr[rightChildIdx])
    {
        int temp = arr[currentRootIdx];
        arr[currentRootIdx] = arr[rightChildIdx];
        arr[rightChildIdx] = temp;
        currentRootIdx = rightChildIdx;
    }

    if (currentRootIdx != currIdx)
        heapify(arr, size, currentRootIdx);
}

void makeHeap(int arr[], int size)
{
    for (int i = (size - 2) / 2; i >= 0; i--)
    {
        heapify(arr, size, i);
    }
}


/*Only modify this function*/
void insertionSortModified(int arr[], int size)
{
    makeHeap(arr, size);
    int curr;
    int i, j;
    for (i = 1; i < size; i++)
    {
        curr = arr[i];
        for (j = i; arr[j - 1] > curr; j--)
        {
            arr[j] = arr[j - 1];
        }
        arr[j] = curr;
    }
}


/*performs the insertion sort algorithm on array from index
left to index right inclusive.  You don't need to change this function*/
void insertionSortStandard(int arr[], int size)
{
    int curr;
    int i, j;
    for (i = 1; i < size; i++)
    {
        curr = arr[i];
        for (j = i; j > 0 && arr[j - 1] > curr; j--)
        {
            arr[j] = arr[j - 1];
        }
        arr[j] = curr;
    }
}

