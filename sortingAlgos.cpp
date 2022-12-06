#include "hospitalList.h"
#include <cmath>
#include <iostream>

using namespace std;

void insertionSort(vector<hospital> &list, int sortBy, int start, int end) {
	for (int i = start + 1; i <= end; i++) {
		int j = i - 1;
		int key = 0;
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
	int lengthLeft = middle - left + 1;
	int lengthRight = right - middle;
	vector<hospital> leftList(lengthLeft);
	vector<hospital> rightList(lengthRight);
	//Initialize the left and right sublists
	for (int i = 0; i < lengthLeft; i++) {
		leftList[i] = list[left + i];
	}
	for (int i = 0; i < lengthRight; i++) {
		rightList[i] = list[middle + 1 + i];
	}

	int l = 0;
	int r = 0;
	int main = left;

	//Merge by average cost
	if (sortBy == 1) {
		while (l < lengthLeft && r < lengthRight) {
			if (leftList[l].returnAverage() <= rightList[r].returnAverage()) {
				list[main] = leftList[l];
				l++;
			}
			else {
				list[main] = rightList[r];
				r++;
			}
			main++;
		}
	}
	//Merge by patient ratings
	else if (sortBy == 2) {
		while (l < lengthLeft && r < lengthRight) {
			if (leftList[l].returnInt("overallrating") < rightList[r].returnInt("overallrating")) {
				list[main] = leftList[l];
				l++;
			}
			else {
				list[main] = rightList[r];
				r++;
			}
			main++;
		}
	}
	//Merge by timeliness
	else if (sortBy == 3) {
		while (l < lengthLeft && r < lengthRight) {
			if (leftList[l].returnInt("timeliness") < rightList[r].returnInt("timeliness")) {
				list[main] = leftList[l];
				l++;
			}
			else {
				list[main] = rightList[r];
				r++;
			}
			main++;
		}
	}
	//Merge by safety
	else if (sortBy == 4) {
		while (l < lengthLeft && r < lengthRight) {
			if (leftList[l].returnInt("safety") < rightList[r].returnInt("safety")) {
				list[main] = leftList[l];
				l++;
			}
			else {
				list[main] = rightList[r];
				r++;
			}
			main++;
		}
	}
	//Merge remaining elements
	while (l < lengthLeft) {
		list[main] = leftList[l];
		l++;
		main++;
	}
	while (r < lengthRight) {
		list[main] = rightList[r];
		r++;
		main++;
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

void heapify(vector<hospital>& list, int sortBy, int size, int i) {
	int maxVal = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	//If sorting by average cost
	if (sortBy == 1) {
		//If left child is larger than the root
		if (left < size && list[left].returnAverage() > list[maxVal].returnAverage()) {
			maxVal = left;
		}

		//If right child is larger than root
		if (right < size && list[right].returnAverage() > list[maxVal].returnAverage()) {
			maxVal = right;
		}

		//If the root isn't the largest
		if (maxVal != i) {
			swap(list[i], list[maxVal]);
			heapify(list, sortBy, size, maxVal);
		}
	}
	//If sorting by patient ranking
	else if (sortBy == 2) {
		//If left child is larger than the root
		if (left < size && list[left].returnInt("overallrating") > list[maxVal].returnInt("overallrating")) {
			maxVal = left;
		}

		//If right child is larger than root
		if (right < size && list[right].returnInt("overallrating") > list[maxVal].returnInt("overallrating")) {
			maxVal = right;
		}

		//If the root isn't the largest
		if (maxVal != i) {
			swap(list[i], list[maxVal]);
			heapify(list, sortBy, size, maxVal);
		}
	}
	//If sorting by timeliness
	if (sortBy == 3) {
		//If left child is larger than the root
		if (left < size && list[left].returnInt("timeliness") > list[maxVal].returnInt("timeliness")) {
			maxVal = left;
		}

		//If right child is larger than root
		if (right < size && list[right].returnInt("timeliness") > list[maxVal].returnInt("timeliness")) {
			maxVal = right;
		}

		//If the root isn't the largest
		if (maxVal != i) {
			swap(list[i], list[maxVal]);
			heapify(list, sortBy, size, maxVal);
		}
	}
	//If sorting by safety
	if (sortBy == 4) {
		//If left child is larger than the root
		if (left < size && list[left].returnInt("safety") > list[maxVal].returnInt("safety")) {
			maxVal = left;
		}

		//If right child is larger than root
		if (right < size && list[right].returnInt("safety") > list[maxVal].returnInt("safety")) {
			maxVal = right;
		}

		//If the root isn't the largest
		if (maxVal != i) {
			swap(list[i], list[maxVal]);
			heapify(list, sortBy, size, maxVal);
		}
	}
}

void heapSort(vector<hospital>& list, int sortBy, int start, int end) {
	//Build heap in place
	for (int i = (end - start) / 2 - 1; i >= 0; i--) {
		heapify(list, sortBy, end - start, i);
	}

	for (int i = end - start - 1; i >= 0; i--) {
		swap(list[start], list[i]);
		heapify(list, sortBy, i, 0);
	}
}

int partition(vector<hospital>& list, int sortBy, int start, int end) {
	//If sorting by cost
	if (sortBy == 1) {
		int pivot = list[end].returnAverage();
		int i = start - 1;
		for (int j = start; j < end; j++) {
			if (list[j].returnAverage() <= pivot) {
				j++;
				swap(list[i], list[j]);
			}
		}
		swap(list[i + 1], list[end]);
		return i + 1;
	}
	//If sorting by patient rating
	if (sortBy == 2) {
		int pivot = list[start].returnInt("overallrating");
		int count = 0;
		for (int i = start + 1; i <= end; i++) {
			if (list[i].returnInt("overallrating") <= pivot) {
				count++;
			}
		}

		int pivotIndex = start + count;
		swap(list[pivotIndex], list[start]);

		int i = start;
		int j = end;

		while (i < pivotIndex && j > pivotIndex) {
			while (list[i].returnInt("overallrating") <= pivot) {
				i++;
			}

			while (list[j].returnInt("overallrating") > pivot) {
				j--;
			}

			if (i < pivotIndex && j > pivotIndex) {
				swap(list[i], list[j]);
				i++;
				j--;
			}
		}

		return pivotIndex;
	}
	//If sorting by timliness
	if (sortBy == 3) {
		int pivot = list[start].returnInt("timeliness");
		int count = 0;
		for (int i = start + 1; i <= end; i++) {
			if (list[i].returnInt("timeliness") <= pivot) {
				count++;
			}
		}

		int pivotIndex = start + count;
		swap(list[pivotIndex], list[start]);

		int i = start;
		int j = end;

		while (i < pivotIndex && j > pivotIndex) {
			while (list[i].returnInt("timeliness") <= pivot) {
				i++;
			}

			while (list[j].returnInt("timeliness") > pivot) {
				j--;
			}

			if (i < pivotIndex && j > pivotIndex) {
				swap(list[i], list[j]);
				i++;
				j--;
			}
		}

		return pivotIndex;
	}
	//Sorting by safety
	if (sortBy == 4) {
		int pivot = list[start].returnInt("safety");
		int count = 0;
		for (int i = start + 1; i <= end; i++) {
			if (list[i].returnInt("safety") <= pivot) {
				count++;
			}
		}

		int pivotIndex = start + count;
		swap(list[pivotIndex], list[start]);

		int i = start;
		int j = end;

		while (i < pivotIndex && j > pivotIndex) {
			while (list[i].returnInt("safety") <= pivot) {
				i++;
			}

			while (list[j].returnInt("safety") > pivot) {
				j--;
			}

			if (i < pivotIndex && j > pivotIndex) {
				swap(list[i], list[j]);
				i++;
				j--;
			}
		}

		return pivotIndex;
	}
}

void introsortHelp(vector<hospital>& list, int sortBy, int maxDepth, int start, int end) {
	int size = end - start;

	//If the list is small, do insertion sort
	if (size < 32) {
		insertionSort(list, sortBy, start, end);
		return;
	}

	//If max depth is reached, do heap sort
	if (maxDepth == 0) {
		heapSort(list, sortBy, start, end);
		return;
	}

	//All else fails, use quicksort
	int partitionIndex = partition(list, sortBy, start, end);
	introsortHelp(list, sortBy, maxDepth - 1, start, partitionIndex - 1);
	introsortHelp(list, sortBy, maxDepth - 1, partitionIndex + 1, end);
}

void introSort(vector<hospital>& list, int sortBy) {
	int maxDepth = 2 * log2(list.size());
	introsortHelp(list, sortBy, maxDepth, 0, list.size() - 1);
}

void quicksort(vector<hospital>& list, int sortBy, int start, int end) {
	if (start >= end) {
		return;
	}

	int pivotIndex = partition(list, sortBy, start, end);
	quicksort(list, sortBy, start, pivotIndex - 1);
	quicksort(list, sortBy, pivotIndex + 1, end);
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
