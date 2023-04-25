// Name:


#include "llist.h"
#include "llist_utils.h"
#include <iostream>
#include <limits> // for declaration of 'numeric_limits' for cin
#include <ios>    // for declaration of 'streamsize' for cin

Node* append(int x, Node *p) {
    if(p == nullptr) return cons(x, nullptr);
    if(cdr(p) == nullptr) {
        setcdr(p, cons(x, nullptr));
        return p;
    }
    append(x, cdr(p));
    return p;
}

Node * append_it(int x, Node * p) {
    if(p == nullptr) return cons(x, nullptr);
    Node* head = p;
    while(cdr(p) != nullptr){
        p = cdr(p);
    }
    setcdr(p, cons(x, nullptr));
    return head;
}


bool searchInOrder(int x, Node *p) {
    if(p == nullptr || car(p) > x) return false;
    return car(p) == x || searchInOrder(x, cdr(p));
}

bool searchInOrder_it(int x, Node *p) {
    while(p != nullptr && car(p) <= x) {
        if(car(p) == x) return true;
        p = cdr(p);
    }
    return false;
}

bool isLonger(Node *p, Node *q) {
    while(p != nullptr && q != nullptr) {
        p = cdr(p);
        q = cdr(q);
    }
    return p != nullptr && q == nullptr;
}

bool equal(Node *p, Node *q) {
    while(p != nullptr && q != nullptr) {
        if(car(p) != car(q)) return false;
        p = cdr(p);
        q = cdr(q);
    }
    return p == nullptr && q == nullptr;
}

Node* makeDuplicates(Node *p) {
    if(p == nullptr) return nullptr;
    Node *second = cons(car(p), nullptr);
    Node *first = cons(car(p), second);
    setcdr(second, makeDuplicates(cdr(p)));
    return first;
}

Node* removeList(Node *p) {
    if(p == nullptr) return nullptr;
    removeList(cdr(p));
    delete p;
    p = nullptr;
    return p;
}

Node* array2List(int A[], int n) {
    Node* p = nullptr;
    for(int i = n-1; i >= 0; i--) {
        p = cons(A[i], p);
    }
    return p;
}

Node* mergeTwoOrderedLists(Node *p, Node *q) {
    if(p == nullptr && q == nullptr) return nullptr;
    Node* merged;
    if(q == nullptr || (p != nullptr && car(p) < car(q))) {
        merged = cons(car(p), mergeTwoOrderedLists(cdr(p), q));
    } else {
        merged = cons(car(q), mergeTwoOrderedLists(p, cdr(q)));
    }
    
    return merged;
}

Node* removeIth(int i, Node *p) {
    return removeIth(i, p, 0);
}

Node* removeIth(int i, Node *p, int curr) {
    if(p == nullptr) return p;
    if(i == curr) {
        Node* next = cdr(p);
        delete p;
        return next;
    }
    
    setcdr(p, removeIth(i, cdr(p), curr+1));
    return p;
}

Node* removeOccurrences(int x, Node *p) {
    if(p == nullptr) return p;
    if(x == car(p)) {
        Node* next = cdr(p);
        delete p;
        return removeOccurrences(x, next);
    }

    setcdr(p, removeOccurrences(x, cdr(p)));
    return p;
}


// BONUS

Node* odds(Node *p) {
    if(p == nullptr || cdr(p) == nullptr) return p;
    setcdr(p, odds(cdr(cdr(p))));
    return p;
}


Node* evens(Node *p) {
    if(p == nullptr) return p;
    p = cdr(p);
    Node* head = p;
    while(p != nullptr && cdr(p) != nullptr) {
        setcdr(p, cdr(cdr(p)));
        p = cdr(p);
    }
    return head;
}