// Name:

// CPSC 1160, Assignment #8
// started by Gladys Monagan
// Do not post anywhere
// Fill in the missing code and submit with Brightspace
// These functions are not for makes: complete in the lab

#include <cassert>
#include <string>
#include <iostream>
#include <limits> // for declaration of 'numeric_limits' for cin
#include <ios>    // for declaration of 'streamsize' for cin
#include "llist_utils.h"

int car(Node* p) { 
   assert(p != nullptr);
   return(p->value); 
}

Node* cdr(Node* p) { 
   assert(p != nullptr); 
   return(p->link); 
}

void setcar(Node* p, int x) { 
   assert(p != nullptr); 
   p->value = x; 
}

void setcdr(Node* p, Node* q) { 
   assert(p != nullptr); 
   p->link = q; 
}

Node * cons( int x, Node* p) {
   Node* q = new Node;
   setcar(q, x);
   setcdr(q, p);
   return q;
}



// "{ " followed by the value followed by a " " closed with "}"
std::ostream& operator << (std::ostream& out, Node* p) {
   out << "{ ";
   while(p != nullptr){
      out << car(p) << " ";
      p = cdr(p);
   }
   out << "}";
   return out;
}

// the nodes of the copyList are in the same order as in p
Node* copyList(Node* p) {
   Node* q = nullptr;
   if(p == nullptr) return q;
   while(p != nullptr) {
      q = cons(car(p), q);
      p = cdr(p);
   }
   return reverse(q);
}

// CPSC 1160 class notes
// reverse the list p doing a "destructive" reverse 
// i.e. the pointers are rearranged, a new list is NOT created
// postcondition: 
//   return a pointer to the beginning of the reversed list
Node * reverse(Node *p) {
   if(p == nullptr) return p;
   Node* prev = nullptr;
   Node* rest = cdr(p);
   while(p != nullptr) {
      setcdr(p, prev);
      prev = p;
      p = rest;
      if(p) rest = cdr(p);
   }
   return prev;
}

// read integers until the input stream in enters a fail state due
// to a non-digit character or end-of-file
// consume the character typed and reset the input stream
std::istream& operator >> (std::istream& in, Node* &p) {
   int x;
   p = nullptr;
   while(in >> x) {
      p = cons(x, p);
   }
   p = reverse(p);

   // reset the input stream state out of fail 
   in.clear();
   // consume characters encountered to the end of the line
   in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
   return in;
}
