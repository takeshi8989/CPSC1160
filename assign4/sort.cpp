#include<iostream>
using namespace std;

void createRandomArr(int[], int);
void sort(int[], int);

void sortR(int[], int);
void sortR(int[], int, int);

void placeLargest(int[], int, int);
void placeSmallest(int[], int, int);
void printArr(int[], int);

const int ARRAY_SIZE = 19;
int comparisons = 0;
int main(){
    srand(time(0));
    int A[ARRAY_SIZE];
    // createRandomArr(A, ARRAY_SIZE);
    // printArr(A, ARRAY_SIZE);
    // sort(A, ARRAY_SIZE);
    // printArr(A, ARRAY_SIZE);
    // cout << "Comparisons: " << comparisons << "\n\n";

    comparisons = 0;
    createRandomArr(A, ARRAY_SIZE);
    printArr(A, ARRAY_SIZE);
    sortR(A, ARRAY_SIZE);
    printArr(A, ARRAY_SIZE);
    cout << "Comparisons: " << comparisons << "\n\n";
    return 1;
}

void createRandomArr(int A[], int n){
    for (int i = 0; i < n; i++){
        A[i] = rand() % 1000;
    }
}

void printArr(int A[], int n){
    const int perLine = 5;
    cout << "[";
    for (int i = 0; i < n; i++) {
        if(i != 0 && i % 5 == 0) cout << endl;
        cout << A[i];
        if(i != n-1) cout << ", ";
    }
    cout << "]\n\n";
}

// precondition:
//      n > 5, no duplicates
void sort(int A[], int n){
    int i = 0;
    int j = n-1;
    while(j > i){
        placeLargest(A, i, j);
        j--;
        placeSmallest(A, i, j);
        i++;
    }
}

// precondition:
//     n > 5, no duplicates
void sortR(int A[], int n){
    sortR(A, 0, n-1);
}

void sortR(int A[], int start, int end){
    if(start >= end) return;
    placeLargest(A, start, end);
    placeSmallest(A, start, end-1);
    sortR(A, start+1, end-1);
}

void placeLargest(int A[], int start, int end){
    if(start >= end) return;
    int i = start;
    while(i < end){
        comparisons++;
        if(A[i] > A[i+1]){
            int tmp = A[i];
            A[i] = A[i+1];
            A[i+1] = tmp;
        }
        i++;
    }
}

void placeSmallest(int A[], int start, int end){
    if(start >= end) return;
    int i = end;
    while(i > start){
        comparisons++;
        if(A[i] < A[i-1]){
            int tmp = A[i];
            A[i] = A[i-1];
            A[i-1] = tmp;
        }
        i--;
    }
}
