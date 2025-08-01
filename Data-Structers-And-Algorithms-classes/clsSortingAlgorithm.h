#pragma once

#include <iostream>
#include <cmath>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

class clsSortingAlgorithm
{
public:


    // ==================== Simple Sorting Algorithms ====================

// Bubble Sort: Repeatedly swaps adjacent elements if they are in the wrong order
    static void BubbleSort(int arr[], int n) {
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }

    // Template version of Bubble Sort
    template<typename T>
    static void BubbleSort_T(T arr[], int n) {
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }

    // Selection Sort: Repeatedly selects the minimum element and puts it at the beginning
    static void SelectionSort(int arr[], int n) {
        for (int i = 0; i < n - 1; i++) {
            int min_idx = i;
            for (int j = i + 1; j < n; j++) {
                if (arr[j] < arr[min_idx])
                    min_idx = j;
            }
            swap(arr[i], arr[min_idx]);
        }
    }

    // Template version of Selection Sort
    template<typename T>
    static void SelectionSort_T(T arr[], int n) {
        for (int i = 0; i < n - 1; i++) {
            int min_idx = i;
            for (int j = i + 1; j < n; j++) {
                if (arr[j] < arr[min_idx])
                    min_idx = j;
            }
            swap(arr[i], arr[min_idx]);
        }
    }

    // Insertion Sort: Builds the final sorted array one item at a time
    static void InsertionSort(int arr[], int n) {
        for (int i = 1; i < n; i++) {
            int key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }

    // Template version of Insertion Sort
    template<typename T>
    static void InsertionSort_T(T arr[], int n) {
        for (int i = 1; i < n; i++) {
            T key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }

    // Merge Sort: Divide and conquer algorithm that splits, sorts and merges arrays
    static void Merge(int arr[], int l, int m, int r) {
        int n1 = m - l + 1;
        int n2 = r - m;
        int* L = new int[n1];
        int* R = new int[n2];

        for (int i = 0; i < n1; i++) L[i] = arr[l + i];
        for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

        int i = 0, j = 0, k = l;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) arr[k++] = L[i++];
            else arr[k++] = R[j++];
        }
        while (i < n1) arr[k++] = L[i++];
        while (j < n2) arr[k++] = R[j++];

        delete[] L;
        delete[] R;
    }

    static void MergeSort(int arr[], int l, int r) {
        if (l < r) {
            int m = l + (r - l) / 2;
            MergeSort(arr, l, m);
            MergeSort(arr, m + 1, r);
            Merge(arr, l, m, r);
        }
    }

    // Template version of Merge Sort merge function
    template<typename T>
    static void Merge_T(T arr[], int l, int m, int r) {
        int n1 = m - l + 1;
        int n2 = r - m;
        T* L = new T[n1];
        T* R = new T[n2];

        for (int i = 0; i < n1; i++) L[i] = arr[l + i];
        for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

        int i = 0, j = 0, k = l;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) arr[k++] = L[i++];
            else arr[k++] = R[j++];
        }
        while (i < n1) arr[k++] = L[i++];
        while (j < n2) arr[k++] = R[j++];

        delete[] L;
        delete[] R;
    }

    // Template version of Merge Sort
    template<typename T>
    static void MergeSort_T(T arr[], int l, int r) {
        if (l < r) {
            int m = l + (r - l) / 2;
            MergeSort_T(arr, l, m);
            MergeSort_T(arr, m + 1, r);
            Merge_T(arr, l, m, r);
        }
    }

    // Quick Sort: Picks a pivot and partitions the array
    static int Partition(int arr[], int low, int high) {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }

    static void QuickSort(int arr[], int low, int high) {
        if (low < high) {
            int pi = Partition(arr, low, high);
            QuickSort(arr, low, pi - 1);
            QuickSort(arr, pi + 1, high);
        }
    }

    // Template version of Quick Sort partition function
    template<typename T>
    static int Partition_T(T arr[], int low, int high) {
        T pivot = arr[high];
        int i = low - 1;
        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }

    // Template version of Quick Sort
    template<typename T>
    static void QuickSort_T(T arr[], int low, int high) {
        if (low < high) {
            int pi = Partition_T(arr, low, high);
            QuickSort_T(arr, low, pi - 1);
            QuickSort_T(arr, pi + 1, high);
        }
    }

    // Heapify function for Heap Sort
    static void Heapify(int arr[], int n, int i) {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < n && arr[l] > arr[largest]) largest = l;
        if (r < n && arr[r] > arr[largest]) largest = r;
        if (largest != i) {
            swap(arr[i], arr[largest]);
            Heapify(arr, n, largest);
        }
    }

    // Heap Sort: Uses a binary heap data structure
    static void HeapSort(int arr[], int n) {
        for (int i = n / 2 - 1; i >= 0; i--)
            Heapify(arr, n, i);
        for (int i = n - 1; i > 0; i--) {
            swap(arr[0], arr[i]);
            Heapify(arr, i, 0);
        }
    }

    // Radix Sort: Sorts by individual digits (non-comparison sort)
    static int getMax(int arr[], int n) {
        int mx = arr[0];
        for (int i = 1; i < n; i++)
            if (arr[i] > mx)
                mx = arr[i];
        return mx;
    }

    static void CountSort(int arr[], int n, int exp) {
        int* output = new int[n];
        int count[10] = { 0 };
        for (int i = 0; i < n; i++) count[(arr[i] / exp) % 10]++;
        for (int i = 1; i < 10; i++) count[i] += count[i - 1];
        for (int i = n - 1; i >= 0; i--) {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }
        for (int i = 0; i < n; i++) arr[i] = output[i];
        delete[] output;
    }

    static void RadixSort(int arr[], int n) {
        int m = getMax(arr, n);
        for (int exp = 1; m / exp > 0; exp *= 10)
            CountSort(arr, n, exp);
    }

    // Bucket Sort: Distributes elements into buckets and sorts them individually
    static void BucketSort(float arr[], int n) {
        vector<vector<float>> buckets(n);
        for (int i = 0; i < n; i++) {
            int idx = n * arr[i];
            buckets[idx].push_back(arr[i]);
        }
        for (int i = 0; i < n; i++)
            sort(buckets[i].begin(), buckets[i].end());
        int index = 0;
        for (int i = 0; i < n; i++) {
            for (float value : buckets[i]) {
                arr[index++] = value;
            }
        }
    }

    // Shell Sort: Generalization of insertion sort that allows exchange of far elements
    static void ShellSort(int arr[], int n) {
        for (int gap = n / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < n; i++) {
                int temp = arr[i];
                int j;
                for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                    arr[j] = arr[j - gap];
                arr[j] = temp;
            }
        }
    }

    // Template version of Shell Sort
    template<typename T>
    static void ShellSort_T(T arr[], int n) {
        for (int gap = n / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < n; i++) {
                T temp = arr[i];
                int j;
                for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                    arr[j] = arr[j - gap];
                arr[j] = temp;
            }
        }
    }
    static void bubbleSortRec(int arr[], int n)
    {
        if (n == 1)//base case
            return;

        for (int i = 0; i < n - 1; i++)
            if (arr[i] > arr[i + 1])
                swap(arr[i], arr[i + 1]);

        bubbleSortRec(arr, n - 1);
    }
    static void insertionSortRec(int arr[], int n)
    {
        // base case 
        if (n <= 1)
            return;

        insertionSortRec(arr, n - 1);
        int last = arr[n - 1];
        int j = n - 2;

        while (j >= 0 && arr[j] > last)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = last;
    }
    static void merge(int array[], int const left, int const mid, int const right)
    {
        int const subArrayOne = mid - left + 1;
        int const subArrayTwo = right - mid;

        // Create temp arrays
        auto* leftArray = new int[subArrayOne],
            * rightArray = new int[subArrayTwo];

        // Copy data to temp arrays leftArray[] and rightArray[]
        for (auto i = 0; i < subArrayOne; i++)
            leftArray[i] = array[left + i];
        for (auto j = 0; j < subArrayTwo; j++)
            rightArray[j] = array[mid + 1 + j];

        auto indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
        int indexOfMergedArray = left;

        // Merge the temp arrays back into array[left..right]
        while (indexOfSubArrayOne < subArrayOne
            && indexOfSubArrayTwo < subArrayTwo) {
            if (leftArray[indexOfSubArrayOne]
                <= rightArray[indexOfSubArrayTwo]) {
                array[indexOfMergedArray]
                    = leftArray[indexOfSubArrayOne];
                indexOfSubArrayOne++;
            }
            else {
                array[indexOfMergedArray]
                    = rightArray[indexOfSubArrayTwo];
                indexOfSubArrayTwo++;
            }
            indexOfMergedArray++;
        }

        // Copy the remaining elements of
        // left[], if there are any
        while (indexOfSubArrayOne < subArrayOne) {
            array[indexOfMergedArray]
                = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
            indexOfMergedArray++;
        }

        // Copy the remaining elements of
        // right[], if there are any
        while (indexOfSubArrayTwo < subArrayTwo) {
            array[indexOfMergedArray]
                = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
            indexOfMergedArray++;
        }
        delete[] leftArray;
        delete[] rightArray;
    }

    static void mergeSort(int array[], int const begin, int const end)
    {

        if (begin >= end)
            return;

        int mid = begin + (end - begin) / 2;
        mergeSort(array, begin, mid);
        mergeSort(array, mid + 1, end);
        merge(array, begin, mid, end);
    }
    static int partition(int arr[], int low, int high)
    {
        // Choosing the pivot
        int pivot = arr[high];

        // Index of smaller element and indicates
        // the right position of pivot found so far
        int i = (low - 1);

        for (int j = low; j <= high - 1; j++) {

            // If current element is smaller than the pivot
            if (arr[j] < pivot) {

                // Increment index of smaller element
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return (i + 1);

        // The main function that implements QuickSort
        // arr[] --> Array to be sorted,
        // low --> Starting index,
        // high --> Ending index

    }

    static void quickSort(int arr[], int low, int high)
    {
        if (low < high) {

            // pi is partitioning index, arr[p]
            // is now at right place
            int pi = partition(arr, low, high);

            // Separately sort elements before
            // partition and after partition
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

    static void heapify(int arr[], int N, int i)
    {

        // To heapify a subtree rooted with node i
        // which is an index in arr[].
        // n is size of heap

            // Initialize largest as root
        int largest = i;

        // left = 2*i + 1
        int l = 2 * i + 1;

        // right = 2*i + 2
        int r = 2 * i + 2;

        // If left child is larger than root
        if (l < N && arr[l] > arr[largest])
            largest = l;

        // If right child is larger than largest
        // so far
        if (r < N && arr[r] > arr[largest])
            largest = r;

        // If largest is not root
        if (largest != i) {
            swap(arr[i], arr[largest]);

            // Recursively heapify the affected
            // sub-tree
            heapify(arr, N, largest);
        }
    }

    static void heapSort(int arr[], int N)
    {

        // Build heap (rearrange array)
        for (int i = N / 2 - 1; i >= 0; i--)
            heapify(arr, N, i);

        // One by one extract an element
        // from heap
        for (int i = N - 1; i > 0; i--) {

            // Move current root to end
            swap(arr[0], arr[i]);

            // call max heapify on the reduced heap
            heapify(arr, i, 0);
        }
    }
};

