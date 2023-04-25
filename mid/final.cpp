#include <iostream>
using namespace std;

void printArr(int A[], int n) {
    for(int i = 0; i < n; i++) {
        cout << A[i] << ", ";
    }
    cout << endl;
}

void writeBackwardForward (unsigned int n, std::ostream& out = std::cout);
int maximum(const int A[] , int n);
bool isStrictlyDescending(const int A[], int n); 
void swapPairsLeftToRight(int A[], int n);
void outputAsOctal(unsigned int n, std::ostream& out = std::cout);


template <typename T>
class Stack{
    public:
        Stack();
        void push(T);
        T pop();
        T peek();
       
    private:
        struct Node{
            T value;
            Node* next;
        };
        Node* head;
};

template <typename T>
Stack<T>::Stack(){
    head = nullptr;
}
template <typename T>
void Stack<T>::push(T val) {
    if(head == nullptr) {
        head = new Node{val, nullptr};
    } else {
        head = new Node{val, head};
    }
}
template <typename T>
T Stack<T>::pop() {
    if(head == nullptr) {
        cerr << "empty";
        exit(1);
    }
    Node* discard = head;
    head = head->next;
    T val = discard->value;
    delete discard;
    return val;
}
template <typename T>
T Stack<T>::peek() {
    if(head == nullptr) {
        cerr << "empty";
        exit(1);
    }
    return head->value;
}



int main() {
    Stack<int> s = Stack<int>();
    s.push(1);
    s.push(2);
    cout << s.pop() << endl;
    cout << s.pop() << endl;
    cout << s.peek() << endl;
    return 0;
}




// -- implementations --

void writeBackwardForward(unsigned int n, std::ostream& out) {
    if(n == 0) {
        out << endl;
        return;
    }
    out << n % 10;
    writeBackwardForward(n / 10, out);
    out << n % 10;
}


int maximum(const int A[] , int n) {
    if(n <= 0) return 0;
    int prevMax = maximum(A, n-1);
    int num = A[n-1];
    return num > prevMax ? num : prevMax;
}


bool isStrictlyDescending(const int A[], int n) {
    if(n <= 1) return true;
    if(A[n-1] >= A[n-2]) return false;
    return isStrictlyDescending(A, n-1);
}

void swapPairsLeftToRight(int A[], int n, int i) {
    if(i + 1 >= n) return;
    int temp = A[i];
    A[i] = A[i+1];
    A[i+1] = temp;
    swapPairsLeftToRight(A, n, i+2);
}

void swapPairsLeftToRight(int A[], int n) {
    swapPairsLeftToRight(A, n, 0);
}

void outputAsOctal(unsigned int n, std::ostream& out) {
    if(n <= 0) return;
    outputAsOctal(n >> 1, out);
    out << (n & 1);
}