// Name:

#ifndef BAG_H
#define BAG_H

#include <iostream>
#include <string>

class Bag {
   public:
      // construct an empty Bag
      Bag(); 
      // return the number of items in the Bag
      // 1160: use the overloaded defined below
      int size() const; 
      // add x into the right place of the Bag (in ascending order)
      // 1160: use the overloaded function defined below
      void add(int x); 
      // remove an item matching x
      // if x is not in the Bag, remove does nothing
      // 1160: use the overloaded function defined below
      void remove(int x);       
      // return true if x is in the Bag 
      // 1160: use the static function "in" defined below
      // 1160: note that the operator < is not a member function of Bag
      friend bool operator < (int x, const Bag & b); 
      // return true if every item of a is the same as every item of b
      // duplicates in both a and b are possible
      friend bool operator == (const Bag & a, const Bag & b); 
      // for output: the bag starts with START is separated by SEP ends with END
      static const std::string START;
      static const std::string END;
      static const std::string SEP;
      // output a bag in the form 
      // Bag::START item0 Bag::SEP item1  BAG::SEP ... BAG::END
      // a bag has NO order but in this implementation of Bag, the values
      // are output in ascending order with duplicates next to each other
      friend std::ostream& operator << (std::ostream&, const Bag&);
      // reads integers into the Bag until a non-integer or the input stream fails
      // resets the input stream out of the fail state
      // 1160: note how the private variable list stores the values
      friend std::istream& operator >> (std::istream& in, Bag&);
      // return a new Bag that contains all the items of both a and b
      friend const Bag operator + (const Bag & a, const Bag & b);
      // copy constructor
      Bag(const Bag&); 
      // overloaded assignment operator so that rtSide can be assigned to the 
      // calling object
      Bag& operator = (const Bag& rtSide); 
      // destructor 
      // CPSC 1160: deallocate every node
      ~Bag(); 


      // BONUS question
      // return a new Bag that contains all the UNIQUE items of both a and b
      // so, the resulting Bag does not have any duplicates
      friend const Bag operator * (const Bag & a, const Bag & b); 
 
   private:
      struct Node {
         int value;
         Node * next;
      };
      // CPSC 1160: list is ALWAYS sorted in ascending order
      Node * list;
      
      // make a new node with x and linked to p
      // return a pointer to the new node
      // we want to access cons in friend functions so make it static
      static Node * cons( int x, Node * p );

      // return the length of the linked list pointed to by p
      // CPSC 1160: called by the function size
      // CPSC 1160: make this function RECURSIVE
      static int size(Node * p);
   
      // determine if x is in p
      // precondition:
      //    p is sorted in ascending order
      // 1160: called by the operator <
      static bool in(int x, Node * p);
      
      // add x if x is not in p already
      // precondition:
      //    p is in ascending order
      // CPSC 1160: make this function RECURSIVE
      static Node* add(int x, Node* p);

      // remove from p the node with x in it
      // CPSC 1160: make this function RECURSIVE
      static Node* remove(int x, Node* p);

      // copy original list and return a new list (in the same order)
      // must be used by the overloaded =, copy constructor and/or destructor
      static Node * copyList(Node *); 

      // delete every node of the list (return memory to the heap)
      // return nullptr
      // must be used by the overloaded =, copy constructor and/or destructor
      static Node * deleteList(Node *);

      // return true if every element of p is equal to q and false otherwise
      static bool equalLists(Node *p, Node *q);
};

#endif

// copyright 2023 Gladys Monagan

