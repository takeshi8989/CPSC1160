// Name:

#include <iostream>
#include <string>
#include "Bag.h"
using std::string;

#include <cassert>
#include <limits> // for declaration of 'numeric_limits' for cin
#include <ios>    // for declaration of 'streamsize' for cin

// static constants initialized only once
// 1160: done for you
const string Bag::START = string("< ");
const string Bag::END   = string(">");
const string Bag::SEP   = string(" ");

Bag::Node * Bag::copyList(Node* p) {
   Node* q = cons(p->value, nullptr);
   Node* head = q;
   p = p->next;
   while(p != nullptr){
      q->next = cons(p->value, nullptr);
      p = p->next;
      q = q->next;
   }
   return head;
}

Bag::Node * Bag::deleteList(Node* p) {
   while(p != nullptr) {
      Node* q = p;
      p = p->next;
      delete q;
   }
   return nullptr;
}

bool Bag::equalLists(Node *p, Node *q) {
   while(p != nullptr && q != nullptr) {
      if(p->value != q->value) return false;
      p = p->next;
      q = q->next;
   }
   return p == nullptr && q == nullptr;
}

// function was declared static in the class definition
// postcondition:
//   a pointer to the newly created Node is returned
Bag::Node* Bag::cons( int x, Node * p ) {
   Node * q;
   q = new Node;
   q->value = x;
   q->next = p;
   return q;
}

// constructor 
Bag::Bag()  {
   list = nullptr;
}

// -- added --
Bag::Bag(const Bag& b) {
   list = copyList(b.list);
}

Bag::~Bag() {
   list = deleteList(list);
}

int Bag::size() const { 
   return size(list);
}

// 1160: must be recursive
int Bag::size(Node * p) {
   if(p == nullptr) return 0;
   return 1 + size(p->next);
}

void Bag::add(int x) { 
   list = Bag::add(x, list);
}

// recursive 
// precondition:
//    p is sorted in ascending order 
// postcondition:
//    the linked list returned is in ascending order with a node with x
Bag::Node* Bag::add(int x, Node* p) {
   if(p == nullptr) return cons(x, nullptr);
   if(p->value >= x) return cons(x, p);
   
   p->next = add(x, p->next);
   return p;
}

void Bag::remove(int x) {  
   list = remove(x, list);
}

// --- added ---
Bag::Node* Bag::remove(int x, Node* p) {
   if(p == nullptr) return p;
   if(p->value == x) {
      Node* skip = p->next;
      delete p;
      return skip;
   }
   p->next = remove(x, p->next);
   return p;
}


// return true if x is in the Bag b, false otherwise
// operator < is a friend of Bag, operator < is a "stand alone" function
bool operator < (int x, const Bag & b) {
   return Bag::in(x, b.list);
}

// --- added ---
bool Bag::in(int x, Node* p) {
   if(p == nullptr) return false;
   if(p->value == x) return true;
   return in(x, p->next);
}

// --- added --
bool operator == (const Bag & a, const Bag & b) {
   return Bag::equalLists(a.list, b.list);
}

// output b in the form Bag::START item0 Bag::SEP item1  BAG::SEP ... BAG::END
std::ostream& operator << (std::ostream& out, const Bag& b) {
   out << Bag::START;
   Bag::Node* listB = b.list;
   while(listB != nullptr) {
      out << listB->value << Bag::SEP;
      listB = listB->next;
   }
   out << Bag::END;
   return out;
}

std::istream& operator >> (std::istream& in, Bag& b) {
   Bag::deleteList(b.list);
   int x;
   Bag::Node* items = nullptr;
   while(in >> x){
      items = b.add(x, items);
   }
   in.clear();

   in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
   b.list = items;
   return in;
}


// copyright 2023 Gladys Monagan


/* can be improved... O(n^2)
const Bag operator + (const Bag & a, const Bag & b) {
   Bag bag;
   Bag::Node* p = bag.list;
   Bag::Node* listA = a.list;
   Bag::Node* listB = b.list;

   while(listA != nullptr) {
      p = bag.add(listA->value, p);
      listA = listA->next;
   }
   while(listB != nullptr) {
      p = bag.add(listB->value, p);
      listB = listB->next;
   }
   bag.list = p;
   return bag;
}
*/

// Assume a and b are sorted O(n)
const Bag operator + (const Bag & a, const Bag & b) {
   Bag::Node* listA = a.list;
   Bag::Node* listB = b.list;

   Bag bag;
   Bag::Node* p = Bag::cons(0, nullptr); // dummy head
   Bag::Node* head = p;

   while(listA != nullptr && listB != nullptr) {
      if(listA->value <= listB->value) {
         p->next = Bag::cons(listA->value, nullptr);
         listA = listA->next;
      } else {
         p->next = Bag::cons(listB->value, nullptr);
         listB = listB->next;
      }
      p = p->next;
   }
   while(listA != nullptr) {
      p->next = Bag::cons(listA->value, nullptr);
      listA = listA->next;
      p = p->next;
   }
   while(listB != nullptr) {
      p->next = Bag::cons(listB->value, nullptr);
      listB = listB->next;
      p = p->next;
   }
   bag.list = head->next;

   return bag;
}




Bag& Bag::operator = (const Bag& rtSide) {
   list = copyList(rtSide.list);
   return *this;
}

// add (a+b) and remove duplicates O(n). simple
const Bag operator * (const Bag & a, const Bag & b) {
   Bag bag = (a + b);
   Bag::Node* p = bag.list;
   while(p != nullptr && p->next != nullptr) {
      if(p->value == p->next->value) {
         Bag::Node* next = p->next;
         p->next = next->next;
         delete next;
      } else {
         p = p->next;
      }
   }
   return bag;
}