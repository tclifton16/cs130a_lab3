#include <string>
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <vector>

#include "User.h"

using namespace std;

struct User{
  int perm;
  string name;
  string genre1;
  string genre2;
}

struct Entry{
  int index;
  User user;
}

struct Node{
  Entry *data;
  Node **children;
  bool leaf;
  int n;
  int degree;
};

Node *root = NULL, *np = NULL, *x = NULL;

Node * createNewNode(){
  tempNode = new Node;
  tempNode->data = new Entry[3];
  tempNode->children = new Node *[4];
  tempNode->isLeaf = true;
  tempNode->degree = 0;
  for(int i=0;i<4;i++){
    tempNode->children[i] = NULL;
  }
  return tempNode;
}

void insertion(string fullstr){
  User user;
  int index,numFriends,count=4;
  string temp;
  vector<string> vec;
  vector<int> numvec;
  stringstream ss(fullstr);

  while(ss.good()){
    string substr;
    getline(ss,substr,';');
    vec.push_back(substr);
  }

  user.perm=atoi(vec[0]);
  user.name=vec[1];
  user.genre1=vec[2];
  user.genre2=vec[3];

  index = graph.size();
  while(count < vec.size()){
    numvec.push_back(atoi(vec[count]));
  }
  graph.push_back(numvec);
  insertBTree(user.perm, user, index);
}

void insertBTree(int perm, User user, int index){
  
}

int main(){
  vector<vector<int> > graph;
  bool q = false;
  int input;
  string *parsestr;
  string name;

  BTree tree;

  cout << "Welcome!\n";
  while(!q){
    cout << "What operation would you like to perform?\n\t1: Input from file\n\t2: Add user\n\t3: Find user\n\t4: Find user's details\n\t5: Recommend friends\n\t6: Quit";
    if(cin >> input){
      switch (input){
      case 1:
	//input from file
	cout << "Please enter filname: ";
	cin >> name;
	break;
      case 2:
	//add user
	
	break;
      case 3:
	//find user
	break;
      case 4:
	//find details
	break;
      case 5:
	//recommend
	break;
      case 6:
	q = true;
	break;
      default:
	cout << "Please enter a valid operation (1,2,3,4,5)\n";
	break;
      }
    }
    else{
      cout << "Please enter a valid operation (1,2,3,4,5)\n";
    }
  }
}
