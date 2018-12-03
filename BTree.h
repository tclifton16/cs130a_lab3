#include "Node.h"

#ifndef BTREE_H
#define BTREE_H

class BTree{
 public:
  void insert();
  void search(int perm);
  void searchAndReturn(int perm);
  void recommend(int perm);
 private:
  Node root;
  int height;
  int n;
}

#endif
