//* Stack : This is a last in first out (LIFO) datastructure. It can be
//implemented using array, vector, linked list
// This is also a part of C++ STL (Majorly we will use this STL while solving
// interview questions)

//* Stack using Array/Vector :

#include <bits/stdc++.h>
using namespace std;

class stackV {
  vector<int> v;

public:
  void push(int val) { // O(1)
    v.push_back(val);
  }

  void pop() { // O(1)
    v.pop_back();
  }

  int top() { // O(1)
    return v[v.size() - 1];
  }

  bool empty() { return v.size() == 0; }
};

//* Stack using Linked List :

class stackLL {
  list<int> ll;

public:
  void push(int val) { // O(1)
    ll.push_front(val);
  }

  void pop() { // O(1)
    ll.pop_front();
  }

  int top() { // O(1)
    return ll.front();
  }

  bool empty() { return ll.size() == 0; }
};

//* Stack using STL :

//(header #include<stack>)

int main() {
  stackV s1;

  s1.push(10);
  s1.push(20);
  s1.push(30);
  s1.push(40);

  while (!s1.empty()) {
    cout << s1.top() << " ";
    s1.pop();
  }

  cout << endl;

  stackLL s2;

  s2.push(50);
  s2.push(60);
  s2.push(70);
  s2.push(80);

  while (!s2.empty()) {
    cout << s2.top() << " ";
    s2.pop();
  }

  cout << endl;

  stack<int> s3;

  s3.push(1);
  s3.push(2);
  s3.push(3);
  s3.push(4);

  while (!s3.empty()) {
    cout << s3.top() << " ";
    s3.pop();
  }

  return 0;
}
