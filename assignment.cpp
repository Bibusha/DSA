#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>

using namespace std;

// Function to generate random numbers between 1 and 1000
void generateRandomArray(int arr[], int N)
{
    for (int i = 0; i < N; i++)
    {
        arr[i] = rand() % 1000 + 1;
    }

    // Display the generated array
    cout << "Generated array: ";
    for (int i = 0; i < N; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Function to print an array (useful for verifying sorted arrays)
void printArray(int arr[], int N)
{
    for (int i = 0; i < N; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Selection Sort Algorithm
void selectionSort(int arr[], int N)
{
    for (int i = 0; i < N - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < N; j++)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

// Merge Sort Helper Function
void merge(int arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = new int[n1];
    int *R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
    delete[] L;
    delete[] R;
}

// Merge Sort Algorithm
void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Binary Search Algorithm
int binarySearch(int arr[], int left, int right, int target)
{
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target)
            return mid;
        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

// Interpolation Search Algorithm
int interpolationSearch(int arr[], int N, int target)
{
    int low = 0, high = N - 1;
    while (low <= high && target >= arr[low] && target <= arr[high])
    {
        if (low == high)
        {
            if (arr[low] == target)
                return low;
            return -1;
        }
        int pos = low + (((double)(high - low) / (arr[high] - arr[low])) * (target - arr[low]));
        if (arr[pos] == target)
            return pos;
        if (arr[pos] < target)
            low = pos + 1;
        else
            high = pos - 1;
    }
    return -1;
}

// Function to display time in minutes and seconds format
void displayTimeInMinutesAndSeconds(double seconds)
{
    int minutes = static_cast<int>(seconds) / 60;
    seconds = seconds - (minutes * 60);
    cout << "Time: " << minutes << " minutes and " << seconds << " seconds\n";
}

int main()
{
    srand(time(0)); // Seed for random number generation

    int N;
    cout << "Enter number of elements (N): ";
    cin >> N;

    // Generate and copy arrays
    int *original = new int[N];
    generateRandomArray(original, N);

    int *sortArr = new int[N];
    copy(original, original + N, sortArr);

    // User choice for sorting method
    int sortChoice;
    cout << "For sorting algorithm:\n1. Selection Sort\n2. Merge Sort\n";
    cout << "Choose Number to sort:";
    cin >> sortChoice;

    // Sorting with selected algorithm and timing
    auto start = chrono::high_resolution_clock::now();
    if (sortChoice == 1)
    {
        selectionSort(sortArr, N);
    }
    else if (sortChoice == 2)
    {
        mergeSort(sortArr, 0, N - 1);
    }
    else
    {
        cout << "Invalid choice. Exiting.\n";
        delete[] original;
        delete[] sortArr;
        return 0;
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    cout << "Sorting Time: ";
    displayTimeInMinutesAndSeconds(elapsed.count()); // Display time in minutes and seconds
    cout << "Sorted Array: ";
    printArray(sortArr, N);

    // User choice for search method
    int searchChoice;
    cout << "Choose search algorithm:\n1. Binary Search\n2. Interpolation Search\n";
    cout << "Choose Number to search:";
    cin >> searchChoice;

    // Get the target number to search for
    int target;
    cout << "Enter a number to search: ";
    cin >> target;

    // Perform search based on user's choice
    int result = -1;
    start = chrono::high_resolution_clock::now();

    if (searchChoice == 1)
    {
        result = binarySearch(sortArr, 0, N - 1, target);
    }
    else if (searchChoice == 2)
    {
        result = interpolationSearch(sortArr, N, target);
    }
    else
    {
        cout << "Invalid choice. Exiting.\n";
        delete[] original;
        delete[] sortArr;
        return 0;
    }

    end = chrono::high_resolution_clock::now();
    elapsed = end - start;

    // Display search result and time taken
    if (result != -1)
    {
        cout << "Search Found at index " << result;
    }
    else
    {
        cout << "Search: Not found";
    }
    cout << "  ";
    displayTimeInMinutesAndSeconds(elapsed.count());

    // Cleanup
    delete[] original;
    delete[] sortArr;

    return 0;
}
