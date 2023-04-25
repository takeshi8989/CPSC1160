// CPSC 1160
// developed by Gladys Monagan
// do not post anywhere, do not modify
#ifndef LLIST_H
#define LLIST_H

#include <iostream>
// includes the definition of Node
#include "llist_utils.h" 

// create a new node with x in it and appends this node to the end of the list p
// precondition: 
//    the linear linked list p has been properly constructed
// postcondition: 
//    return a pointer to the beginning of the list
// 1160: do not use reverse
Node* append(int x, Node *p);

// 1160: iterative version of append
Node* append_it(int x, Node *p);

// determine if x is in the list p
// precondition: 
//    the linear linked list p is in sorted in ascending order
// postcondition: 
//    return true if x is in p, false otherwise
bool searchInOrder(int x, Node *p);

// 1160: iterative version of searchInOrder
bool searchInOrder_it(int x, Node *p);

// determine if the first list p is longer than the second list q 
// return true if p is longer than q, false otherwise
// 1160: do not call the function length
bool isLonger(Node *p, Node *q);

// return true if all the elements of p and q are equal and false otherwise
// equal means the same values in the lists in the same order
// 1160: p, q or both could be empty
bool equal( Node *p, Node *q);

// return a new list with every element appearing twice in the same order as p
// p is not modified
// postcondition: 
//    return a list that is independent of the original list p
// 1160: the returned list is independent of p
Node* makeDuplicates(Node *p);

// delete every node of the list p returning memory to the heap (or freestore)
// postcondition: 
//    returns the nullptr pointer
Node * removeList(Node *p);

// return a list with all the elements of A
// the first node of the returned list should have as value A[0], 
// the second node A[1], and so on and the last node of the list will be A[n-1]
// precondition: 
//    A has been allocated memory for at least n integers
//    n >= 0
// postcondition: 
//    return a pointer to the beginning of the list
Node * array2List(int A[], int n);

// return a new list with the values of p and q merged
// precondition:
//    p and q are sorted in ascending order
// postcondition:
//    return a merged list with all the elements sorted in ascending order
// 1160: the returned list is independent of p and q
Node* mergeTwoOrderedLists(Node* p, Node* q);

// remove from p the node at position i
// if the list p is not empty, the very first node is the 0th node
// if the ith node does not exist, do nothing, i.e. return the original p
// postcondition:
//    return a list without the ith node (if the ith node existed)
// 1160: return to the heap the memory no longer needed
Node* removeIth(int i, Node* p);
Node* removeIth(int i, Node* p, int curr);

// remove every occurrence of x in p
// removing is based on the value x and NOT on position in the list
// postcondition:
//    return a list without any x’s
// 1160: return to the heap the memory no longer needed
Node* removeOccurrences(int x, Node* p);

// BONUS
// returns a new list with the odd-positioned values of p (where possible)
// the first node is odd, the third node is odd, and so on
// Example
// if p = { 11 22 33 44 55 }, odds(p) returns { 11 33 55 }
// 1160: implement recursively (yes, you can overload the function)
Node* odds(Node* p);

// returns a new list with the even-positioned values of p (where possible)
// the second node is even, the fourth node is even, and so on
// Example
// if p = { 11 22 33 44 55 66 77 }, evens(p) returns { 22 44 66 }
// 1160: implement iteratively
Node* evens(Node* p);

#endif

// copyright 2023 Gladys Monagan

