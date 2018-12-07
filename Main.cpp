#include <string>
#include<sstream>
#include<fstream>
#include <iostream>
#include <stdio.h>
#include <vector>

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
        User *usr1, *usr2;
        Node *c1, *c2, *c3, *c4, *parent;
        int c;//number of children
        bool leaf;
};

Node * createNewNode();
void insertion(string fullstr);
void find(int perm, Node *p);
void findDetails(int perm, Node *p);
Node * search(int perm);
void insertBTree(User *x);
bool isFull(Node *n);
void split(Node *n);
int getMin(Node *n);


Node *root = NULL, *newNode = NULL, *tempNode = NULL;
vector<vector<int> > graph;
Entry tempEntry;

Node * createNewNode(){
	newNode = new Node;
	newNode->c=0;
	newNode->leaf = true;
	for(int i=0; i<3; i++)
		newNode->k[i] = -1;
	newNode->usr1 = NULL;
	newNode->usr2 = NULL;
	newNode->c1 = NULL;
	newNode->c2 = NULL;
	newNode->c3 = NULL;
	newNode->c4 = NULL;
	newNode->parent = NULL;

	return newNode;
}

void insertion(string fullstr){
	User *user;
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

	user->perm=stoi(vec[0]);
	user->name=vec[1];
	user->genre1=vec[2];
	user->genre2=vec[3];

	index = graph.size();
	while(count < vec.size()){
		numvec.push_back(stoi(vec[count]));
	}
	graph.push_back(numvec);
	insertBTree(user);
}

void find(int perm, Node *p){
	bool found = false;
	if(p == NULL){
		return;
	}
	if(p->leaf==true){
		if(perm == p->usr1->perm || perm == p->usr2->perm){
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
		cout << "Perm not found\n";
}



void findDetails(int perm, Node *p){
	bool found = false;
	if(p == NULL){
		return;
	}
	if(p->leaf == true){

	}
	else if(p->leaf == false){

	}

	for(int i=0;i<p->c;i++){
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

int getMin(Node *n){
  if(n == NULL){
    return -1;
  }
  if(n->leaf){
    return n->usr1->perm;
  }
  else{
    return getMin(n->c1);
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

void insertBTree(User *x)
{
	Node *temp = search(x->perm);
	if(isFull(temp))
	{
		split(temp);
		insertBTree(x);
	}
	if(temp->c4 != NULL)
	{
		split(temp);
		insertBTree(x);
	}
	if(root == NULL)//x is first user entered
	{
		Node *t = createNewNode();
		t->usr1 = x;
		root = t;
		


		return;
	}
	if(root->leaf)
	{
		if(root->usr2 == NULL)
		{
			if(x->perm > root->usr1->perm)
			{
				root->usr2 = x;
			}
			else
			{
				root->usr2 = root->usr1;
				root->usr1 = x;
			}
		}
		else
		{
			Node *t2 = createNewNode();
			t2->leaf = false;
			t2->c = 2;
			Node *t3 = createNewNode();

			if(x->perm < root->usr1->perm)
			{
				t3->usr1 = x;
				t3->parent = t2;
				t2->c1 = t3;
				root->parent = t2;
				t2->c2 = root;
				root = t2;

				t2->k[0] = getMin(t2->c2);
				t2->k[1] = -1;
				t2->k[2] = -1;
			
				return;
			}
			if(x->perm > root->usr2->perm)
			{
				t3->usr1 = x;
				t3->parent = t2;
				root->parent = t2;
				t2->c1 = root;
				t2->c2 = t3;
				root = t2;

				t2->k[0] = x->perm;
				t2->k[1] = -1;
				t2->k[2] = -1;

				return;
			}
			else
			{
				t3->usr1 = root->usr2;
				root->usr2 = x;
				t3->parent = t2;
				root->parent = t2;
				t2->c1 = root;
				t2->c2 = t3;
				root = t2;

				t2->k[0] = t3->usr1->perm;
				t2->k[1] = -1;
				t2->k[2] = -1;
				
				return;
			}
		}
	}
	else//if root is not a leaf
	{
		if(x->perm < temp->k[0])//x belongs in leaf no1
		{
			if(temp->c1->usr2 == NULL)//leafno1 has space
			{
				if(x->perm <temp->c1->usr1->perm)
				{
					temp->c1->usr2 = temp->c1->usr1;
					temp->c1->usr1 = x;
					return;
				}
				else
				{
					temp->c1->usr2 = x;
					return;
				}
			}
			else//leafno1 has no space
			{
				if(x->perm < temp->c1->usr1->perm)//perm<A
				{
					Node *r = createNewNode();
					r->usr1 = x;
					r->parent = temp;
					temp->c ++;
					temp->c4 = temp->c3;
					temp->c3 = temp->c2;
					temp->c2 = temp->c1;
					temp->c1 = r;

				}
				else if(x->perm > temp->c1->usr2->perm)//Perm>B
				{
					Node *r = createNewNode();
					r->usr1 = x;
					r->parent = temp;
					temp->c ++;
					temp->c4 = temp->c3;
					temp->c3 = temp->c2;
					temp->c2 = r;
				}
				else
				{
					Node *r = createNewNode();
					r->usr1 = temp->c1->usr2;
					temp->c1->usr2 = x;
					r->parent = temp;
					temp->c++;
					temp->c4 = temp->c3;
					temp->c3 = temp->c2;
					temp->c2 = r;
				}

				temp->k[0] = getMin(temp->c2);
				temp->k[1] = getMin(temp->c3);
				temp->k[2] = getMin(temp->c4);

				return;
			}
		}
		else if(x->perm < temp->k[1])//x belongs in leafno2
		{
			if(temp->c2->usr2 == NULL)//if leafno2 has space
			{
				if(x->perm < temp->c2->usr1->perm)
				{
					temp->c2->usr2 = temp->c2->usr1;
					temp->c2->usr1 = x;
					temp->k[0] = x->perm;
				}
				else
					temp->c2->usr2 = x;
			}
			else//leaf no space
			{
				if(x->perm < temp->c2->usr1->perm)
				{
					Node *r = createNewNode();
					r->usr1 = x;
					r->parent = temp;
					temp->c++;
					temp->c4 = temp->c3;
					temp->c3 = temp->c2;
					temp->c2 = r;
				}
				else if(x->perm > temp->c2->usr2->perm)
				{
					Node *r = createNewNode();
					r->usr1 = x;
					r->parent = temp;
					temp->c++;
					temp->c4 = temp->c3;
					temp->c3 = r;
				}
				else
				{
					Node *r = createNewNode();
					r->usr1 = temp->c2->usr2;
					temp->c2->usr2 =x;
					r->parent = temp;
					temp->c ++;
					temp->c4 = temp->c3;
					temp->c3 = r;
				}
				temp->k[0] = getMin(temp->c2);
				temp->k[1] = getMin(temp->c3);
				temp->k[2] = getMin(temp->c4);

				return;
			}
		}
		else if(x->perm < temp->k[2])//x belongs in leafno3
		{
			if(temp->c3->usr2 == NULL)
			{
				if(x->perm < temp->c3->usr1->perm)
				{
					temp->c3->usr2 = temp->c3->usr1;
					temp->c3->usr1 = x;
					temp->k[1] = x->perm;
				}
				else
				{
					temp->c3->usr2 = x;
				}
			}
			else//leafno3 has no space
			{
				if(x->perm < temp->c3->usr1->perm)
				{
					Node *r = createNewNode();
					r->usr1 = x;
					r->parent = temp;
					temp->c ++;
					temp->c4 = temp->c3;
					temp->c3 = r;
				}
				else if (x->perm > temp->c3->usr1->perm)
				{
					Node *r = createNewNode();
					r->usr1 = x;
					r->parent = temp;
					temp->c ++;
					temp->c4 = r;
				}
				else
				{
					Node *r = createNewNode();
					r->usr1 = temp->c3->usr2;
					temp->c3->usr2 = x;
					r->parent = temp;
					temp->c ++;
					temp->c4 = r;
				}
				temp->k[0] = getMin(temp->c2);
				temp->k[1] = getMin(temp->c3);
				temp->k[2] = getMin(temp->c4);
				return;
			}
		}	
		else 
		{
			temp->c4->usr1 = x;
			temp->k[2] = getMin(temp->c4);
		}
	}
}

bool isFull(Node * n)
{
	if(n->leaf)
	{
		if(n->usr2 == NULL)
		{
			return false;
		}

		return true;
	}
	if(n->c1 == NULL || n->c2 == NULL || n->c3 == NULL || n->c4 == NULL)
	{
		return false;
	}
	return (isFull(n->c1) && isFull(n->c2) && isFull(n->c3) && isFull(n->c4));
}

void split(Node * n)
{
	Node *a = createNewNode();
	a->leaf = false;
	a->c = 2;
	a->c1 = n->c3;
	a->c2 = n->c4;
	n->c3 = NULL;
	n->c4 = NULL;
	if(n->parent = NULL)//is root
	{
		Node *c = createNewNode();
		c->leaf = false;
		c->c = 2;
		n->parent = c;
		a->parent = c;
		c->parent = NULL;
		c->c1 = n;
		c->c2 = a;

		a->k[0] = getMin(a->c2);
		a->k[1] = -1;
		a->k[2] = -1;

		n->k[0] = getMin(n->c2);
		n->k[1] = -1;
		n->k[2] = -1;

		c->k[0] = getMin(c->c2);
		c->k[1] = -1;
		c->k[2] = -1;

		return;
	}
	Node *b = n->parent;
	a->k[0] = getMin(a->c2);

	a->k[1] = -1;
	a->k[2] = -1;

	n->k[0] = getMin(n->c2);
	n->k[1] = -1;
	n->k[2] = -1;

	if(b->c1 == n)//N is first child of its parent
	{
		if(b->c2 == NULL)
		{
			b->c2 = a;
			b->k[0] = getMin(b->c2);

			return;
		}
		if(b->c3 == NULL)
		{
			b->c3 = b->c2;
			b->c2 = a;
			b->k[0] = getMin(b->c2);
			b->k[1] = getMin(b->c3);

			return;
		}
		if(b->c4 == NULL)
		{
			b->c4 = b->c3;
			b->c3 = b->c2;
			b->c2 = a;
			b->k[0] = getMin(b->c2);
			b->k[1] = getMin(b->c3);
			b->k[2] = getMin(b->c4);
			return;
		}
	}
	else if (b->c2 == n)//N is its parents second child
	{
		if(b->c3 == NULL)
		{
			b->c3 = a;
			b->k[0] = getMin(b->c2);
			b->k[1] = getMin(b->c3);
			return;
		}
		if(b->c4 == NULL)
		{
			b->c4 = b->c3;
			b->c3 = a;
			b->k[0] = getMin(b->c2);
			b->k[1] = getMin(b->c3);
			b->k[2] = getMin(b->c4);
			return;
		}
	}
	else if (b->c3 == n)//N is its parents third child
	{
		b->c4 = a;
		b->k[0] = getMin(b->c2);
		b->k[1] = getMin(b->c3);
		b->k[2] = getMin(b->c4);
		return;
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
					{
					//input from file
					cout << "Please enter filname: ";
					cin >> name;
					ifstream infile(name);
					while(getline(infile, name)){
						insertion(name);
					}
					break;
					}
				case 2:
					{
					//add user
					cout << "Enter perm: ";
					cin >> perm;
					fullstr += perm;
					fullstr += ";";
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
					}
				case 3:
					{
					//find user
					cout << "Enter the perm number you would like to find: ";
					cin >> perm;
					find(perm,root);
					break;
					}
				case 4:
					{
					//find details
					cout << "Enter the perm number you would like to find: ";
					cin >> perm;
					findDetails(perm,root);
					break;
					}
				case 5:
					{
					//recommend

					break;
					}
				case 6:
					{
					q = true;
					break;
					}
				default:
					{
					cout << "Please enter a valid operation (1,2,3,4,5)\n";
					break;
					}
			}
		}
		else{
			cout << "Please enter a valid operation (1,2,3,4,5)\n";
		}
	}
	return 0;
}
