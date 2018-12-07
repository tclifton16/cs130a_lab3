#include <string>
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <vector>
#include <fstream>

#include "User.h"

using namespace std;

struct User{
  int perm;
  string name;
  string genre1;
  string genre2;
};

struct Entry{
  int index;
  User user;
};

struct Node{
  int k[3];
  user *usr1, *usr2;
  Node *c1, *c2, *c3, *c4, *parent;
  int c;//number of children
  bool leaf;
};

Node *root = NULL, *newNode = NULL, *tempNode = NULL;
vector<vector<int> > graph;
Entry tempEntry;

Node * createNewNode(){
  newNode = new Node;
  newNode->n=0;
  newNode->leaf = true;
  return newNode;
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

void find(int perm, Node *p){
  bool found = false;
  if(p == NULL){
    return 0;
  }
  if(p->leaf==true){
    if(perm == p->usr1.perm || perm == p->usr2.perm){
      cout << "Perm: " << perm << " exists in B Tree\n";
      found = true;
    }
  }
  else if(p->leaf == false){
    find(perm, p->c1);
    find(perm, p->c2);
    find(perm, p->c3);
    find(perm, p->c4);
  }
  
  if(found == false)
    cout << "Perm not found\n");
}



void findDetails(int perm, Node *p){
  bool found = false;
  if(p == NULL){
    return 0;
  }
  if(p->leaf == true){
    
  }
  else if(p->leaf == false){
    
  }
  
  for(int i=0;i<p->n;i++){
    if(p->leaf==true){
      if(perm == p->data[i].user.perm){
        cout << "Perm: " << perm << " Name: " << p->data[i].user.name << " Genre1: " << p->data[i].user.perm << " Genre2: " << p->data[i].user.perm << " Friends perm:";
	for(int x = 0; x < graph[p->data[i].index].size(); x++){
	  cout << " " << graph[p->data[i].index][x];
	}
	cout << endl;
      }
    }
    else if(p->leaf == false){
      find(p->children[i]);
    }
  }
  if(found == false){
    cout << "Perm not found\n";
  }
}

Node * search(int perm){
  if(p == NULL){
    return;
  }
  for(int i=0;i<p->n;i++){
    if(p->leaf==true){
      if(perm == p->usr1->perm || perm == p->usr2->perm){
	return p->parent;
      }
    }
    else if(p->leaf == false){
      return find(p->children[i]);
    }
  }
}

void insertBTree(int perm, User user, int index){
  int temp;
  tempEntry->user = user;
  tempEntry->index = index;
  tempNode = root;
  if(tempNode == NULL){
    root = createNewNode();
    tempNode = root;
  }
  else{
    //if tempNode is leaf & full
    if(tempNode->leaf == 1 && tempNode->n == 2){
      split_leaf(tempNode);
      tempNode = root;
      for(int i=0; i<tempNode->n; i++){
        temp = split_child(tempNode);
	tempNode = root;
      }
    }
    else{
      while(tempNode->leaf != 1){
	for(int i=0;i<tempNode->n;i++){
	  if((perm > tempNode->keys[i])&&(perm < tempNode->keys[i+1])){
	    i++;
	    break;
	  }
	  else if(perm < tempNode->keys[0]){
	    break;
	  }
	  else{
	    continue;
	  }
	}
	if((tempNode->children[i])->n==3){
	  temp = split_child(tempNode);
	  tempNode->keys[tempNode->n] = temp;
	  tempNode->n++;
	  continue;
	}
	else{
	  tempNode = tempNode->children[i];
	}
      }
    }
  }
}

int main(){
  bool q = false;
  int input;
  int perm;
  string *parsestr;
  string name;
  string fullstr = "";

  cout << "Welcome!\n";
  while(!q){
    cout << "What operation would you like to perform?\n\t1: Input from file\n\t2: Add user\n\t3: Find user\n\t4: Find user's details\n\t5: Recommend friends\n\t6: Quit";
    if(cin >> input){
      switch (input){
      case 1:
	//input from file
	cout << "Please enter filname: ";
	cin >> name;
	ifstream infile(name);
	while(getline(infile, name)){
	  insertion(name);
	}
	break;
      case 2:
	//add user
	cout << "Enter perm: ";
	cin >> perm;
	fullstr += perm;
	fullstr += ";"
	cout << "Enter name: ";
	cin >> name;
	fullstr += name;
	fullstr += ";";
	cout << "Enter genre 1: ";
	cin >> name;
	fullstr += name;
	fullstr += ";";
	cout << "Enter genre 2: ";
	cin >> name;
	fullstr += name;
	fullstr += ";";
	do{
	  cout << "Enter friend perm (stop to stop): ";
	  cin >> name;
	  if(name!="stop"){
	    fullstr+=name;
	    fullstr+=";";
	  }
	}while(name != "stop");
	break;
      case 3:
	//find user
	cout << "Enter the perm number you would like to find: ";
	cin >> perm;
	find(perm,root);
	break;
      case 4:
	//find details
	cout << "Enter the perm number you would like to find: ";
	cin >> perm;
	findDetails(perm,root);
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
