// Name: 


// CPSC 1160, Assignment #10
// initial code written by Gladys Monagan, CPSC 1160

#include "sparse.h"
#include <iostream>

// 1160 complexity: there are n terms in this->list

// changes this->variable to w
void Sparse:: setPrintVariable(char w) {
   this->variable = w;
}
      
// returns the variable used in outputting the polynomial
char Sparse::getPrintVariable() const {
   return this->variable;
}

// the zero polynomial i.e. the constant zero
Sparse::Sparse() : variable(DEFAULT_VARIABLE) {
   list = nullptr;
}

// creates the term  c*x^d and sets the list to this term
// 1160 complexity: 
Sparse::Sparse(int c, int d) : variable(DEFAULT_VARIABLE){ 
   list = new Node{ new Term{c, d}, nullptr};
}

// basically, checks the representation of the zero polynomial 
// 1160 complexity: O(1)
bool Sparse::isZeroPolynomial() const { 
   return list == nullptr;
}


// 1160 complexity: O(n)
int Sparse::degree() const {
   Node* p = list;
   if(p == nullptr) return -1;
   while(p->link != nullptr) {
      p = p->link;
   }
   return p->term->degree;
}

// 1160 complexity: 
int Sparse::coefficient(int d) const{
   Node* p = list;
   while(p != nullptr) {
      if(p->term->degree == d) {
         return p->term->coeff;
      }
      p = p->link;
   }
   return 0;
}  


// outputs the polynomial and then terminates with a "\n"
// it uses the linked list and the instance variable this->variable
// do not output  "+ -" when outputting negative coefficients
// outputting is O(n) where n is the number of terms of the polynomial f
std::ostream& operator << (std::ostream& out, const Sparse& f) {
   // 1160 make a special case for the list that has no terms i.e. the zero polynomial
   if(f.isZeroPolynomial()) return (out << "0");

   // 1160 get the private list from f below
   Sparse::Node* p = f.list;

   // variable is a private member of f
   char x = f.variable; 
   bool first_term = true;
   // 1160 fix the while loop CHANGE from while (false) !!!!!!!!!!!!!!!!!
   while ( p != nullptr ) {
       // 1160 fix 
      int c = p->term->coeff;
      int d = p->term->degree;
      if (d == 0) { // do not output "x^0"
         out << c;
      }
      else { 
         // the degree d  > 0
         if (c > 0) {
            if (!first_term) out << " + ";
            if (c != 1) {
               out << c <<  "*" ;
            }
         }
         else {
            // c < 0, could not be c == 0
            out << " - ";
            if (c != -1) {
               out << -c <<  "*" ;
            }
         }
         out << x << "^" << d;
      }
      // 1160 get the next Node below
      p = p->link;
      first_term = false;
   } // while
   return out;
}


Sparse Sparse::operator *(int c) const {
   Sparse s;
   if(this->isZeroPolynomial() || c == 0) return s;
   
   Node* p = copyList(this->list);
   Node* head = p;
   
   while(p != nullptr) {
      p->term->coeff *= c;
      p = p->link;
   }
   s.list = head;
   return s;
}


// 1160 complexity: 
void Sparse::insert(Term *t) { 
   Sparse::insert(t, list);
}

// 1160 complexity: O(n)
Sparse::Node* Sparse::insert(Term *t, Node *p) { 
   Node* head = p;
   if(p == nullptr) return new Node{t, nullptr};
   if(t->degree < p->term->degree) return new Node{t, p};
   if(t->degree == p->term->degree) {
      p->term->coeff += t->coeff;
      return p;
   }

   while(p->link != nullptr) {
      
      Sparse::Node* next = p->link;
      if(next->term->degree < t->degree) {
         p = p->link;
      } else if(next->term->degree > t->degree) {
         p->link = new Node{t, next};
         return head;
      } else {
         next->term->coeff += t->coeff;
         return head;
      }
   }
   p->link = new Node{t, nullptr};

   return head;
}

// the number of terms read must be positive
// read each term and build the polynomial by inserting each term in order 
// into the list
// Note that internally there are no nodes with a zero coefficient so the
// zero polynomial is a special case 
// Hint: if the coefficient of the term is 0, do not insert it into 
// the sparse polynomial
// 1160 complexity: O(n)
std::istream& operator >> (std::istream& in, Sparse& p) {
   int numTerms;
   in >> numTerms;
   if (in && numTerms >= 0) {
      for(int i = 0; i < numTerms; i++) {
         int c, d;
         in >> c >> d;
         p.list = p.insert(new Sparse::Term{c, d}, p.list);
      }
   }
  return in;
}
  
// the length of "f" is n plus the length of "g" is m
// 1160 complexity: O(n+m)
Sparse operator +(const Sparse & f, const Sparse & g) {
   return Sparse::calculation(1, f, g);
}

// the length of "f" is n plus the length of "g" is m
// 1160 complexity: O(n+m)
Sparse operator -(const Sparse & f, const Sparse & g) {
   return Sparse::calculation(-1, f, g);
}

// return new sparse which has derivative of the original one
Sparse Sparse::derivative() const {
   Sparse s = Sparse();
   Node* original = this->list;
   Node* p = new Node{new Term{0, 0}, nullptr}; //dummy
   Node* head = p;
   while(original != nullptr) {
      if(original->term->degree > 0) {
         int c = original->term->coeff * original->term->degree;
         int d = original->term->degree - 1;
         Term* t = new Term{c, d};
         p->link = new Node{t, nullptr};
         p = p->link;
      }
      original = original->link;
   }
   s.list = head->link;
   Sparse::deleteNode(head);
   return s;
}

// copy constructor using copylist function
Sparse::Sparse(const Sparse& other) : variable(other.variable) {
   list = copyList(other.list);
}

// assginment operator
Sparse& Sparse::operator = (const Sparse& rhs) {
   deleteList(list);
   list = copyList(rhs.list);
   variable = rhs.variable;
   return *this;
}

// deconstructor
Sparse::~Sparse() {
   deleteList(list);
}



// other methods

// delete node and its term
void Sparse::deleteNode(Node* &p) {
   delete p->term;
   delete p;
}

// delete list of sparse
void Sparse::deleteList(Node* &head) {
   while(head != nullptr) {
      Node* l = head;
      head = head->link;
      deleteNode(l);
   }
}

// copy the entire list and term
Sparse::Node* Sparse::copyList(Node* p) {
   Node* newList = new Node{new Term{0,0}, nullptr}; // dummy
   Node* head = newList;
   while(p != nullptr) {
      Term* t = new Term{p->term->coeff, p->term->degree};
      newList->link = new Node{t, nullptr};
      newList = newList->link;
      p = p->link;
   }
   Node* h = head->link;
   delete head;
   return h;
}


// add or subtract (f-g) and return new sparse
Sparse Sparse::calculation(int sign, const Sparse & f, const Sparse & g) {
   Sparse::Node* fList = f.list;
   Sparse::Node *gList = g.list;
   Sparse s = Sparse();
   Sparse::Node* sList = new Sparse::Node{new Sparse::Term{0,0}, nullptr}; // dummy head
   Sparse::Node* head = sList;

   while(fList != nullptr && gList != nullptr) {
      Sparse::Term* t;
      if(fList->term->degree < gList->term->degree) {
         t = new Sparse::Term{fList->term->coeff, fList->term->degree};
         fList = fList->link;
      } else if(gList->term->degree < fList->term->degree) {
         t = new Sparse::Term{sign * gList->term->coeff, gList->term->degree};
         gList = gList->link;
      } else {
         if(fList->term->coeff + sign * gList->term->coeff != 0){
            t = new Sparse::Term{ fList->term->coeff + sign * gList->term->coeff, fList->term->degree};
            fList = fList->link;
            gList = gList->link;
         }
         else{
            fList = fList->link;
            gList = gList->link;
            continue;
         }
      }
      sList->link = new Sparse::Node{t, nullptr};
      sList = sList->link;
   }

   if(fList != nullptr) {
      sList->link = copyList(fList);
   }

   while(gList != nullptr) {
      Sparse::Term* t = new Sparse::Term{sign * gList->term->coeff, gList->term->degree};
      sList->link = new Sparse::Node{t, nullptr};
      sList = sList->link;
      gList = gList->link;
   }
   
   s.list = head->link;
   Sparse::deleteNode(head);
   return s;
}

// copyright 2023 Gladys Monagan