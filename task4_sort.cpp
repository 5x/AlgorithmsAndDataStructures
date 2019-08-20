#include <iostream>
#include <ctime>

const unsigned int MAX_VALUE = 100;

void bubbleSort(int arr[], const int size) {
    bool unsorted = true;
    int j = 0;

    while (unsorted) {
        unsorted = false;
        j++;

        for (int i = 0; i < size - j; i++) {
            if (arr[i] > arr[i + 1]) {
                const int tmp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = tmp;

                unsorted = true;
            }
        }
    }
}

void selectionSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int min_index = i;

        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }

        if (min_index != i) {
            const int tmp = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = tmp;
        }
    }
}

void quickSort(int* arr, int start, int end) {
    const int x = arr[(start + end) / 2];
    int i = start, j = end;

    do {
        while (arr[i] < x) {
            ++i;
        }

        while (arr[j] > x) {
            --j;
        }

        if (i <= j) {
            if (i != j) {
                arr[j] ^= (arr[i] ^= (arr[j] ^= arr[i]));
            }

            i++;
            j--;
        }
    } while (i < j);

    if (start < j) {
        quickSort(arr, start, j);
    }

    if (i < end) {
        quickSort(arr, i, end);
    }
}

void bucketSort(int* mas, int n, int max) {
    int* arr = new int[max], p = 0, i, j;

    for (i = 0; i < max; i++) {
        arr[i] = 0;
    }

    for (i = 0; i < n; i++) {
        arr[mas[i]] += 1;
    }

    for (i = 0; i < max; i++) {
        for (j = 0; j < arr[i]; j++) {
            mas[j + p] = i;
        }

        p += arr[i];
    }

    delete[]arr;
}

int binarySearch(int arr[], int value, int left, int right) {
    while (left <= right) {
        const int middle = (left + right) / 2;

        if (arr[middle] == value) {
            return middle;
        }

        if (arr[middle] > value) {
            right = middle - 1;
        } else {
            left = middle + 1;
        }
    }

    return -1;
}

int lineSearch(int arr[], int size, int value) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == value) {
            return i;
        }
    }

    return -1;
}

void randomizeArray(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % MAX_VALUE;
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << ", ";
    }
}


int main() {
    srand(time(0));
    const int size = 10;
    int* arr = new int[size];

    randomizeArray(arr, size);
    std::cout << "Array:" << std::endl;
    printArray(arr, size);
    std::cout << std::endl << "Bubble Sort:" << std::endl;
    bubbleSort(arr, size);
    printArray(arr, size);

    randomizeArray(arr, size);
    std::cout << std::endl << std::endl << "Array:" << std::endl;
    printArray(arr, size);
    selectionSort(arr, size);
    std::cout << std::endl << "Selection Sort:" << std::endl;
    selectionSort(arr, size);
    printArray(arr, size);

    randomizeArray(arr, size);
    std::cout << std::endl << std::endl << "Array:" << std::endl;
    printArray(arr, size);
    selectionSort(arr, size);
    std::cout << std::endl << "Quick Sort:" << std::endl;
    quickSort(arr, 0, size - 1);
    printArray(arr, size);

    randomizeArray(arr, size);
    std::cout << std::endl << std::endl << "Array:" << std::endl;
    printArray(arr, size);
    selectionSort(arr, size);
    std::cout << std::endl << "Bucket Sort:" << std::endl;
    bucketSort(arr, size, MAX_VALUE);
    printArray(arr, size);

    std::cout << std::endl << std::endl << "Array:" << std::endl;
    printArray(arr, size);
    int index = binarySearch(arr, 8, 0, size);
    std::cout << std::endl << "Binary Search: index with value 8: " << index << std::endl;

    std::cout << std::endl << std::endl << "Array:" << std::endl;
    printArray(arr, size);
    index = lineSearch(arr, size, 9);
    std::cout << std::endl << "Line Search: index with value 9: " << index << std::endl;

    std::cout << std::endl;

    system("pause");

    return 0;
}
