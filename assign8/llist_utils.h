// CPSC 1160, Assignment #8
// started by Gladys Monagan
// Do not post anywhere
// Fill in the missing code and submit with Brightspace
// These functions are not for makes: complete in the lab

#ifndef LLIST_UTILS_H
#define LLIST_UTILS_H

#include <iostream>

// main data structure
struct Node {
   int value; 
   Node *link; 
};

// returns the value field of the Node
// if p is the nullptr, we cannot dereference p so ...exit abruptly
int car(Node* p); 

// returns the link field of the Node
// if p is the nullptr, we cannot dereference p so ...exit abruptly
Node* cdr(Node* p);

// change the value field (the car) of the Node pointed to by p
void setcar(Node* p, int x);

// change the link field (the cdr) of the Node pointed to by p
void setcdr(Node* p, Node* q);

// construct a new node: allocate dynamic memory for a Node
// set x to be the field of the value and p to be the field of link
Node * cons( int x, Node* p);

// output p so that it starts with curly left brace followed by a blank
// then a number followed by a blank and closed off with a curly right brace
// or "{ " followed by the value followed by a " " closed with "}"
// Examples
//   { 7 10 9 } 
//   "{ }" for the empty list
std::ostream& operator << (std::ostream& out, Node* p);

// return a new list that is independent of p and has the values of the
// nodes in the same order as those from p
Node* copyList(Node* p);

// reverse the list p doing a "destructive" reverse 
// i.e. the pointers are rearranged, a new list is NOT created
// postcondition: 
//   return a pointer to the beginning of the reversed list
Node* reverse(Node *p);

// read integers until the input stream in enters a fail state due
// to a non-digit character or end-of-file
// consume the character typed and reset the input stream
std::istream& operator >> (std::istream& in, Node* & p);

#endif

// copyright 2023 Gladys Monagan

