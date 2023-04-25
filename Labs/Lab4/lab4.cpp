#include<iostream>
#include<cstdlib>
using namespace std;

void insertionSort(int[], int);

void printArr(int[], int);

void createRandomArr(int[], int);

void printComparisons();

int comparisons = 0;
const int ARRAY_SIZE = 6;
int main(){
    int A[ARRAY_SIZE] = {1,2,3,4,5,6};
    int B[ARRAY_SIZE] = {6,5,4,3,2,1};
    int C[ARRAY_SIZE];
    srand( time(0) );
    createRandomArr(C, ARRAY_SIZE);
    printArr(A, ARRAY_SIZE);
    printArr(B, ARRAY_SIZE);
    printArr(C, ARRAY_SIZE);

    cout << endl;

    insertionSort(A, ARRAY_SIZE);
    printArr(A, ARRAY_SIZE);
    printComparisons();

    insertionSort(B, ARRAY_SIZE);
    printArr(B, ARRAY_SIZE);
    printComparisons();

    insertionSort(C, ARRAY_SIZE);
    printArr(C, ARRAY_SIZE);
    printComparisons();
    
    return 1;
}


void insertionSort(int A[], int n){
    if (n <= 1) return;
    insertionSort(A, n-1);
    int i = n-1;
    while (i > 0 && A[i] < A[i-1]){
        comparisons++;
        int tmp = A[i];
        A[i] = A[i-1];
        A[i-1] = tmp;
        i--;
    }
}

void createRandomArr(int A[], int n){
    const int RANDOM_RANGE = 6;
    for (int i = 0; i < n; i++){
        A[i] = rand() % RANDOM_RANGE + 1;
    }
}

void printArr(int A[], int n){
    for (int i = 0; i < n; i++){
        cout << A[i] << " ";
    }
    cout << endl;
}

void printComparisons(){
    cout << "Comparisons: " << comparisons << endl;
    comparisons = 0;
}