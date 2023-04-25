// Student Name: Takeshi Hashimoto
// Student Number: 100398623

// code for CPSC 1160 Assignment #5
// copyright Gladys Monagan
// do not post anywhere

/*
g++ -pedantic -Wall -Wextra -std=c++17 timings.cpp -o timings
*/


//==============================================================================
// sort the first n elements of A in ascending order using insertion sort 
// precondition:
//    A has been declared to have at least n elements
// postcondition:
//    the first n elements of A are sorted in ascending order
void insertionSort(int A[], int n);

// sort the first n elements of A in ascending order using quicksort
// precondition:
//    A has been declared to have at least n elements
// postcondition:
//    the first n elements of A are sorted in ascending order
void quickSort(int A[], int n);

// sort the values A[low] up to and including A[high] using quicksort
// postcondition:
//    A[low] <= A[low+1] <= ... <= A[high-1] <= A[high]
void quickSort(int A[], int low, int high);

// partition is used for quicksort
// find a pivot and guarantee that all the elements 
// before the pivot are <= the pivot 
// and all the elements  after the pivot are >= the pivot
// explanation given in class 
// choose the first element as pivot like in the textbook by Liang, Listing 19.8
// postcondition:
//    the value returned is the index of the pivot
//    the pivot is stored at A[value returned]
int partition(int A[], int low, int high);

// sort the first n elements of A in ascending order using mergesort
// precondition:
//    A and W have been declared to have at least n elements
// postcondition:
//    the first n elements of A are sorted in ascending order
void mergeSort(int A[], int W[], int n);

// sort A[low], A[low-1], ... , A[high-1], A[high] using mergesort
// precondition:
//    A and W have been declared to have at least (high - low + 1) elements
// postcondition:
//    A[low] <= A[low+1] <= ... <= A[high-1] <= A[high]
void mergeSort(int A[], int low, int high, int W[]);

// merge A[lStart],...,A[lEnd] with A[rStart],....,A[rEnd] into W 
// and copy W into A
// precondition:
//    array A and array W have declared to have at least rEnd - lStart + 1 elements
// postcondition:
//    A[lStart] <= .. <= A[lEnd] <= A[rStart] <= A[rStart+1] <= ... <= A[rEnd]
void merge(int A[], int lStart, int lEnd, int rStart, int rEnd, int W[]);


// ----------------------------------insertion sort  -------------------------
void insertionSort(int A[], int n) {
   for (int i = 1; i < n; i++) {
      int j;
      int t = A[i]; // new value
      for (j = i-1; j >= 0 && A[j] > t; j--)
         A[j+1] = A[j];
      A[j+1] = t;
   }
}

// ----------------------------------quick sort  -------------------------
// choose the first element as pivot like in the textbook by Liang, Listing 19.8
int partition(int A[], int low, int high) { 
   int pivot = A[low];
   while (low < high) {
      // gap is now at A[low]
      while (low < high && A[high] >= pivot) {
         high--;
      }
      A[low] = A[high];
      // gap is now at A[high]
      while (low < high && A[low] <= pivot) { 
         low++;
      }
      A[high] = A[low];
   }
   A[low] = pivot; 
   // return index of the pivot
   return low;
}
void quickSort(int A[], int low, int high) {
   if (low >= high) {  // correct, fixed from class notes
      return;
   }
   if (low + 1 == high) {
      if (A[low] > A[high]) {
         int tmp = A[low];
         A[low] = A[high];
         A[high] = tmp;
      }
      return;
   }
   int pivotIndex = partition(A, low, high);
   quickSort(A, low, pivotIndex - 1);
   quickSort(A, pivotIndex + 1, high);
}

void quickSort(int A[], int n) {
   quickSort(A, 0, n-1);
}

// ----------------------------------merge sort  -------------------------
void mergeSort(int A[], int W[], int n) {
   mergeSort(A, 0, n-1, W);
}
void mergeSort(int A[], int low, int high, int W[] ) {
   if (high == low) {
      return;
   }
   // split the array in two and recursively do mergeSort
   int mid = (low + high)/2;
   mergeSort(A, low, mid, W);
   mergeSort(A, mid+1, high, W);
   merge(A, low, mid, mid+1, high, W);
}

// merge A[rStart],...,A[lEnd] with A[rStart],....,A[rEnd] into 
// W  which is indexed by k
void merge(int A[], int lStart, int lEnd, int rStart, int rEnd, int W[]) {
   int i = lStart;  // index of the left half of A
   int j = rStart;  // index of the right half of A
   int k = lStart;  // index of the W working array
   while (i <= lEnd && j <= rEnd) {
      if (A[i] < A[j]) {
         W[k++] = A[i++];
      }
      else if (A[i] > A[j]) {
         W[k++] = A[j++];
      }
      else { 
         W[k++] = A[i++]; 
         W[k++] = A[j++]; 
      }
   }
   // copy the "left tail" if it is not empty
   while (i <= lEnd) {
      W[k++] = A[i++];
   }
   // copy the "right tail" if it is not empty
   while (j <= rEnd) {
      W[k++] = A[j++];
   }
   // copy working W back into the resulting A 
   for (i = lStart; i <= rEnd; i++) {
      A[i] = W[i];  
   }  
}
//==============================================================================

#include <time.h>
#include <iostream>
using namespace std;

void printArr(const int A[], int n){
   for (int i = 0; i < n; i++){
      cout << A[i] << " ";
   }
}

void createRandomArr(int A[], int n){
   for (int i = 0; i < n; i++){
      A[i] = rand();
   }
}

void createAscendingArr(int A[], int n){
   for (int i = 0; i < n; i++){
      A[i] = i;
   }
}

void createDesceindgArr(int A[], int n){
   for (int i = 0; i < n; i++){
      A[i] = n - i;
   }
}

void testAlgorithms(int A[], int W[], int size, int m){
   cout << "Array SIZE: " << size << endl << endl;

   // random - insertion sort
   clock_t t = clock();
   for (int i = 0; i < m; i++){
      createRandomArr(A, size);
      insertionSort(A, size);
   }
   t = clock() - t;
   cout << "Insertion sort (Random Array): " << t / static_cast<double>(m) << endl;

   // ascending - insertion sort
   t = clock();
   for (int i = 0; i < m; i++){
      createAscendingArr(A, size);
      insertionSort(A, size);
   }
   t = clock() - t;
   cout << "Insertion sort (Ascending Array): " << t / static_cast<double>(m) << endl;

   // descending - insertion sort
   t = clock();
   for (int i = 0; i < m; i++){
      createDesceindgArr(A, size);
      insertionSort(A, size);
   }
   t = clock() - t;
   cout << "Insertion sort (Descending Array): " << t / static_cast<double>(m) << endl;


   cout << endl;

   // random - quick sort
   t = clock();
   for (int i = 0; i < m; i++){
      createRandomArr(A, size);
      quickSort(A, size);
   }
   t = clock() - t;
   cout << "Quick sort (Random Array): " << t / static_cast<double>(m) << endl;

   // ascending - quick sort
   t = clock();
   for (int i = 0; i < m; i++){
      createAscendingArr(A, size);
      quickSort(A, size);
   }
   t = clock() - t;
   cout << "Quick sort (Ascending Array): " << t / static_cast<double>(m) << endl;

   // descending - quick sort
   t = clock();
   for (int i = 0; i < m; i++){
      createDesceindgArr(A, size);
      quickSort(A, size);
   }
   t = clock() - t;
   cout << "Quick sort (Descending Array): " << t / static_cast<double>(m) << endl;

   
   cout << endl;


   // random - merge sort
   t = clock();
   for (int i = 0; i < m; i++){
      createRandomArr(A, size);
      mergeSort(A, W, size);
   }
   t = clock() - t;
   cout << "Merge sort (Random Array): " << t / static_cast<double>(m) << endl;

   // ascending - merge sort
   t = clock();
   for (int i = 0; i < m; i++){
      createAscendingArr(A, size);
      mergeSort(A, W, size);
   }
   t = clock() - t;
   cout << "Merge sort (Ascending Array): " << t / static_cast<double>(m) << endl;

   // descending - merge sort
   t = clock();
   for (int i = 0; i < m; i++){
      createDesceindgArr(A, size);
      mergeSort(A, W, size);
   }
   t = clock() - t;
   cout << "Merge sort (Descending Array): " << t / static_cast<double>(m) << endl;
}

int main() {
   srand(time(0));
   int TRIAL = 4;
   int size = 1000;
   const int M = 1000;
   for (int i = 0; i < TRIAL; i++){
      int A[size];
      int W[size];
      testAlgorithms(A, W, size, M);
      size *= 2;
      cout << endl;
   }
   
 
   return 0;
}

