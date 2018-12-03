

#ifndef NODE_H
#define NODE_H

class Node{
 public:
  Node(int m);
  int getM();
 private:
  int m;
  Entry[] children;
};
