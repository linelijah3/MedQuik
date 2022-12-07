#include "hospitalList.h"
#include <cmath>
#include <iostream>

using namespace std;

//TimSort algorithm referenced from GeeksforGeeks (https://www.geeksforgeeks.org/timsort/)
//Merge sort algorithm referenced from GeeksforGeeks (https://www.geeksforgeeks.org/merge-sort/)

void insertionSort(vector<hospital> &list, int sortBy, int start, int end) {
    for (int i = start + 1; i <= end; i++) {
        int key = 0;
        int j = i - 1;
        hospital keyHospital = list[i];
        //Sort average cost of care
        if (sortBy == 1) {
            key = list[i].returnAverage();
            while (j >= start && list[j].returnAverage() > key) {
                list[j + 1] = list[j];
                j--;
            }
        }
            //Sort by patient ratings
        else if (sortBy == 2) {
            key = list[i].returnInt("overallrating");
            while (j >= start && list[j].returnInt("overallrating") > key) {
                list[j + 1] = list[j];
                j--;
            }
        }
            //Sort by timeliness
        else if (sortBy == 3) {
            key = list[i].returnInt("timeliness");
            while (j >= start && list[j].returnInt("timeliness") > key) {
                list[j + 1] = list[j];
                j--;
            }
        }
            //Sort by safety
        else if (sortBy == 4) {
            key = list[i].returnInt("safety");
            while (j >= start && list[j].returnInt("safety") > key) {
                list[j + 1] = list[j];
                j--;
            }
        }
        list[j + 1] = keyHospital;
    }
}

//Called by timsort and merge sort
void merge(vector<hospital>& list, int left, int middle, int right, int sortBy) {
    int lengthRight = right - middle;
    int lengthLeft = middle - left + 1;
    vector<hospital> rightList(lengthRight);
    vector<hospital> leftList(lengthLeft);
    //Initialize the left and right sublists
    for (int i = 0; i < lengthRight; i++) {
        rightList[i] = list[middle + 1 + i];
    }
    for (int i = 0; i < lengthLeft; i++) {
        leftList[i] = list[left + i];
    }

    int main = left;
    int r = 0;
    int l = 0;

    //Merge by average cost
    if (sortBy == 1) {
        while (r < lengthRight && l < lengthLeft) {
            if (leftList[l].returnAverage() <= rightList[r].returnAverage()) {
                list[main] = leftList[l];
                main++;
                l++;
            }
            else {
                list[main] = rightList[r];
                main++;
                r++;
            }
        }
    }
        //Merge by patient ratings
    else if (sortBy == 2) {
        while (r < lengthRight && l < lengthLeft) {
            if (leftList[l].returnInt("overallrating") < rightList[r].returnInt("overallrating")) {
                list[main] = leftList[l];
                main++;
                l++;
            }
            else {
                list[main] = rightList[r];
                main++;
                r++;
            }
        }
    }
        //Merge by timeliness
    else if (sortBy == 3) {
        while (r < lengthRight && l < lengthLeft) {
            if (leftList[l].returnInt("timeliness") < rightList[r].returnInt("timeliness")) {
                list[main] = leftList[l];
                main++;
                l++;
            }
            else {
                list[main] = rightList[r];
                main++;
                r++;
            }
        }
    }
        //Merge by safety
    else if (sortBy == 4) {
        while (r < lengthRight && l < lengthLeft) {
            if (leftList[l].returnInt("safety") < rightList[r].returnInt("safety")) {
                list[main] = leftList[l];
                main++;
                l++;
            }
            else {
                list[main] = rightList[r];
                main++;
                r++;
            }
        }
    }
    //Merge remaining elements
    while (l < lengthLeft) {
        list[main] = leftList[l];
        main++;
        l++;
    }
    while (r < lengthRight) {
        list[main] = rightList[r];
        main++;
        r++;
    }
}

void timsort(vector<hospital>& list, int sortBy) {

    //Perform insertion sort on subarrays of length 32
    for (int i = 0; i < list.size(); i += 32) {
        insertionSort(list, sortBy, i, min(i + 32 - 1, int(list.size() - 1)));
    }

    //Merge sorted subarrays
    for (int i = 32; i < list.size(); i *= 2) {
        for (int left = 0; left < list.size(); left += i * 2) {
            int middle = left + i - 1;
            int right = min((left + 2 * i - 1), int(list.size() - 1));
            if (middle < right) {
                merge(list, left, middle, right, sortBy);
            }
        }
    }
}

void mergesort(vector<hospital>& list, int sortBy, int start, int end) {
    if (start >= end) {
        return;
    }
    int middle = start + (end - start) / 2;
    mergesort(list, sortBy, start, middle);
    mergesort(list, sortBy, middle + 1, end);
    merge(list, start, middle, end, sortBy);
}
