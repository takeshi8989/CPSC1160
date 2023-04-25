
#include <iostream>
using namespace std;


struct Node {
    int value;
    Node* next;
};

Node* cons(int x, Node* p);
int car(Node* p);
Node* cdr(Node* p);
void setCar(int x, Node* p);
void setCdr(Node* p, Node* q);

Node* cons(int x, Node* p) {
    Node* q = new Node;
    q->value = x;
    q->next = p;
    return q;
}

int car(Node* p) {
    return p->value;
}

Node* cdr(Node* p) {
    return p->next;
}

void setCar(int x, Node* p) {
    p->value = x;
}

void setCdr(Node* p, Node* q) {
    p->next = q;
}


Node* append(int x, Node* p);
Node* append_it(int x, Node* p);

Node* insert(int x, int i, Node* p);
Node* insert_it(int x, int i, Node* p);

Node* reverse(Node* p);
Node* reverse_it(Node* p);

int length(Node* p);
int length_it(Node* p);

Node* remove(int i, Node* p);
Node* remove_it(int i, Node* p);
Node* remove_val(int x, Node* p);
Node* remove_val_it(int x, Node* p);

Node* append(int x, Node* p) {
    if(p == nullptr) {
        return cons(x, nullptr);
    }
    setCdr(p, append(x, cdr(p)));
    return p;
}

Node* append_it(int x, Node* p) {
    if(p == nullptr) {
        return cons(x, nullptr);
    }
    Node* q = p;
    while(cdr(q) != nullptr) q = cdr(q);
    setCdr(q, cons(x, nullptr));
    return p;
}

Node* insert(int x, int i, Node* p, int current) {
    if(i == current) {
        Node* q = cons(x, p);
        return q;
    }
    if(p == nullptr) return cons(x, nullptr);
    setCdr(p, insert(x, i, cdr(p), current+1));
    return p;
}

Node* insert(int x, int i, Node* p) {
    return insert(x, i, p, 0);
}
Node* insert_it(int x, int i, Node* p) {
    if(i == 0) {
        return cons(x, p);
    }
    Node* prev = p;
    int current = 1;
    while(prev != nullptr && current < i) {
        prev = cdr(prev);
        current++;
    }
    if(prev != nullptr) setCdr(prev, cons(x, cdr(prev)));
    return p;
}

Node* reverse(Node* p) {
    if(cdr(p) == nullptr) {
        return p;
    }
    Node* head = reverse(cdr(p));
    setCdr(cdr(p), p);
    setCdr(p, nullptr);
    return head;
}

Node* reverse_it(Node* p) {
    Node* prev = nullptr;
    Node* next;
    while(p != nullptr) {
        next = cdr(p);
        setCdr(p, prev);
        prev = p;
        p = next;
    }
    return prev;
}

int length(Node* p) {
    if(p == nullptr) return 0;
    return 1 + length(cdr(p));
}

int length_it(Node* p) {
    int len = 0;
    while(p != nullptr) {
        p = cdr(p);
        len++;
    }
    return len;
}

Node* remove(int i, Node* p, int current) {
    if(p == nullptr) return p;
    if(i == current) {
        Node* next = cdr(p);
        delete p;
        return next;
    }
    setCdr(p, remove(i, cdr(p), current+1));
    return p;
}

Node* remove(int i, Node* p) {
    return remove(i, p, 0);
}

Node* remove_it(int i, Node* p) {
    if(i == 0) {
        Node* next = cdr(p);
        delete p;
        return next;
    }
    Node* q = p;
    int current = 1;
    while(q != nullptr && i > current) {
        q = cdr(q);
        current++;
    }
    if(q != nullptr && cdr(q) != nullptr) {
        Node* next = cdr(cdr(q));
        delete cdr(q);
        setCdr(q, next);
    }
    return p;
}

Node* remove_val(int x, Node* p) {
    if(p == nullptr) return p;
    if(car(p) == x) {
        Node* next = cdr(p);
        delete p;
        return next;
    }
    setCdr(p, remove_val(x, cdr(p)));
    return p;
}

Node* remove_val_it(int x, Node* p) {
    if(car(p) == x) {
        Node* next = cdr(p);
        delete p;
        return next;
    }
    Node* q = p;
    while(q != nullptr && cdr(q) != nullptr) {
        if(car(cdr(q)) == x) {
            Node* next = cdr(cdr(q));
            delete cdr(q);
            setCdr(q, next);
            break;
        }
        q = cdr(q);
    }
    return p;
}

int main() {

    Node* head = cons(1, nullptr);
    Node* p = head;
    setCdr(p, cons(2, nullptr));
    p = cdr(head);
    setCdr(p, cons(3, nullptr));
    p = cdr(head);


    p = head;
    while(p != nullptr) {
        cout << car(p);
        p = cdr(p);
    }

    cout << endl;

    head = remove_val_it(4, head);

    while(head != nullptr) {
        cout << car(head);
        head = cdr(head);
    }

    cout << endl;
    


    return 0;
}