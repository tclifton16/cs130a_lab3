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
Node * search(int perm, Node *p);
void insertBTree(User *x);
bool isFull(Node *n);
void split(Node *n);
int getMin(Node *n);
void recommend(int perm);
void dfs(int perm, string one, string two);
void dfsutil(int p, bool *visited);
vector<int> dfshelper(int perm, Node *leafNode, bool *visited);

Node *root = NULL, *newNode = NULL, *tempNode = NULL;
vector<vector<int> > graph;
Entry tempEntry;
bool found = false;

Node * createNewNode(){
	newNode = new Node;
	newNode->c=0;
	newNode->leaf = true;
	for(int i=0; i<3; i++)
		newNode->k[i] = 10000;
	newNode->usr1 = NULL;
	newNode->usr2 = NULL;
	newNode->c1 = NULL;
	newNode->c2 = NULL;
	newNode->c3 = NULL;
	newNode->c4 = NULL;
	newNode->parent = NULL;

	return newNode;
}

void recommend(int perm){
  string one, two;
  Node *temp = search(perm, root);
  if(temp != NULL){
    if(perm < temp->k[0]){
      temp = temp->c1;
    }
    else if(perm >= temp->k[0] && perm < temp->k[1]){
      temp = temp->c2;
    }
    else if(perm >= temp->k[1] && perm < temp->k[2]){
      temp = temp->c3;
    }
    else{
      temp = temp->c4;
    }
    if(temp->usr1->perm == perm){
      one = temp->usr1->genre1;
      two = temp->usr1->genre2;
    }
    else if(temp->usr2->perm == perm){
      one = temp->usr2->genre1;
      two = temp->usr2->genre2;
    }
    dfs(perm,one,two);
  }
}

void dfs(int perm, string one, string two){
  bool *visited = new bool[graph.size()];
  for(int i = 0; i < graph.size(); i++){
    visited[i] = false;
  }
  dfsutil(graph.size(),visited);
}

void dfsutil(int p, bool *visited){
  visited[p] = true;
  vector<int> temp = dfshelper(p,root,visited);
  for(int i = 0; i < p; i++){
    if(!visited[i]){
      dfsutil(i,visited);
      vector<int> temp = dfshelper(p,root,visited);
    }
  }
  for(int i = 0; i < temp.size(); i++){
    for(int x = 0; x < graph[p].size();x++){
      if(temp[i] != graph[p][x]){
	cout << "Perms of recommended friends: ";
	cout << temp[i];
      }
    }
  }
}

vector<int> dfshelper(int perm, Node *leafNode, bool *visited){
  vector<int> temp;
  if(leafNode->usr1 != NULL && leafNode->usr1->perm == perm){
    for(int i = 0; i < graph[perm].size(); i++){
      find(perm, leafNode);
      temp.push_back(graph[perm][i]);
    }
    return temp;
  }
  else if(leafNode->usr2 != NULL && leafNode->usr2->perm == perm){
    for(int i = 0; i < graph[perm].size();i++){
      find(perm,leafNode);
      temp.push_back(graph[perm][i]);
    }
    return temp;
  }
  return temp;
}

void insertion(string fullstr){
	
	User *user = new User;

	int index, numFriends, count=4;
	string temp = "";
	vector<string> vec;
	vector<int> numvec;
	stringstream ss(fullstr);

	while(ss.good()){
		string substr;
		getline(ss,substr,';');
		vec.push_back(substr);
	}

	string tempa = vec[0];
	int tempb = stoi(tempa);
	user->perm = tempb;
	user->name=vec[1];
	user->genre1=vec[2];
	user->genre2=vec[3];

	index = graph.size();
	numvec.push_back(tempb);
	while(count < vec.size()){
		numvec.push_back(stoi(vec[count]));
		count ++;
	}
	graph.push_back(numvec);
	insertBTree(user);
}

void find(int perm, Node *p){//node is root on first iteration
	if(root == NULL)
	{
		cout<<"There are no users"<<endl;
		return;
	}
	if(p == NULL)
	{
		found = false;
		return;
	}

	if(p->leaf)
	{
		if(p->usr1->perm == perm)
		{
			cout<<"User found!"<<endl;
			found = true;
			return;
		}
		else if(p->usr2 != NULL && p->usr2-> perm == perm)
		{
			cout<<"User found!"<<endl;
			found = true;
			return;
		}
		else
			return;

	}
	if(perm < p->k[0])
		find(perm, p->c1);

	if(perm >= p->k[0])
	{
		if(p->k[1] > 9999)
			find(perm, p->c2);
		
		else 
		{
			if(perm < p->k[1])
				find (perm, p->c2);

			if(perm >= p->k[1])
			{
				if(p->k[2] > 9999)
					find(perm, p->c3);
				
				else
				{
					if(perm < p->k[2])
						find(perm, p->c3);
					else
						find(perm, p->c4);
				}
			}
		}
	}



	
}



void findDetails(int perm, Node *p){
	if(root == NULL)
         {
                 cout<<"There are no users"<<endl;
                 return;
         }
         if(p == NULL)
         {
                 found = false;
                 return;
         }

         if(p->leaf)
         {
                 if(p->usr1->perm == perm)
                 {
                         cout<<"User found!"<<endl;
			 cout<<"Perm Number: "<<perm<<"\nUser Name: "<<p->usr1->name<<"\nGenre 1: "<<p->usr1->genre1<<"\nGenre 2: "<<p->usr1->genre2<<"\nPerm Numbers of Friends:\n";
			 for(int i = 0; i<graph.size(); i++)
			 {
				 if(graph[i][0] == perm)
				 {
					 for( int j=1; j<graph[i].size(); j++)
						 cout<<graph[i][j]<<"\n";
				}
			 }
                         found = true;
                         return;
                 }
                 else if(p->usr2 != NULL && p->usr2-> perm == perm)
                 {
                         cout<<"User found!"<<endl;
			 cout<<"Perm Number: "<<perm<<"\nUser Name: "<<p->usr2->name<<"\nGenre 1: "<<p->usr2->genre1<<"\nGenre 2: "<<p->usr2->genre2<<"\nPerm Numbers of Friends:\n";
                          for(int i = 0; i<graph.size(); i++)
                          {
                                  if(graph[i][0] == perm)
                                  {
                                          for( int j=1; j<graph[i].size(); j++)
                                                  cout<<graph[i][j]<<endl;
                                  }
                          }

                         found = true;
                         return;
		 }
                 else
			 found = false;
                         return;

         }
         if(perm < p->k[0])
                 findDetails(perm, p->c1);

         if(perm >= p->k[0])
         {
                 if(p->k[1] > 9999)
                         findDetails(perm, p->c2);

                 else
                 {
                         if(perm < p->k[1])
                                 findDetails(perm, p->c2);

                         if(perm >= p->k[1])
                         {
                                 if(p->k[2] > 9999)
                                         findDetails(perm, p->c3);

                                 else
                                 {
                                         if(perm < p->k[2])
                                                 findDetails(perm, p->c3);
                                         else
                                                 findDetails(perm, p->c4);
                                 }
                         }
                 }
         }


}

int getMin(Node *n){
  if(n == NULL){
    return 10000;
  }
  if(n->leaf){
    return n->usr1->perm;
  }
  else{
    return getMin(n->c1);
  }
}

Node * search(int perm, Node *p){

	if(p == NULL){
	  return NULL;
	}
	if(p->leaf==true && p->parent != NULL){
		if(p->usr1->perm == perm || (p->usr2 != NULL && p->usr2->perm == perm){
			 return p->parent;
		}
	}
	if (p->leaf == true)
	{
		if(p->usr1->perm == perm || (p->usr2 != NULL && p->usr2->perm == perm)
			return root;
	}
	else if(p->leaf == false){
	  if(perm < p->k[0]){
	    return search(perm, p->c1);
	  }
	  else if(perm >= p->k[0] && perm < p->k[1]){
	    return search(perm, p->c2);
	  }
	  else if(perm >= p->k[1] && perm < p->k[2]){
	    return search(perm, p->c3);
	  }
	  else{
	    return search(perm, p->c4);
	  }
	}
	
}

void insertBTree(User *x)
{
	if (root == NULL)//first insert
	{
		Node *t = createNewNode();
		t->usr1 = x;
		t->c =1;
		root = t;
		return;
	}

	Node *temp = search(x->perm, root);


	
}

bool isFull(Node * n)
{
	if(n == NULL)
		return false;
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
	if(n->parent == NULL)//is root
	{
		Node *c = createNewNode();
		c->leaf = false;
		c->c = 2;
		n->parent = c;
		a->parent = c;
		c->parent = NULL;
		c->c1 = n;
		c->c2 = a;
		root = c;

		a->k[0] = getMin(a->c2);
		a->k[1] = 10000;
		a->k[2] = 10000;

		n->k[0] = getMin(n->c2);
		n->k[1] = 10000;
		n->k[2] = 10000;

		c->k[0] = getMin(c->c2);
		c->k[1] = 10000;
		c->k[2] = 10000;

		return;
	}
	Node *b = n->parent;
	a->k[0] = getMin(a->c2);

	a->k[1] = 10000;
	a->k[2] = 10000;

	n->k[0] = getMin(n->c2);
	n->k[1] = 10000;
	n->k[2] = 10000;

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
		cout << "What operation would you like to perform?\n\t1: Input from file\n\t2: Add user\n\t3: Find user\n\t4: Find user's details\n\t5: Recommend friends\n\t6: Quit\n\tOption (1,2,3,4,5,6): ";
		if(cin >> input){
			switch (input){
				case 1:
					{
					//input from file
					cout << "Please enter filename: ";
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
					string perm1 = to_string(perm);
					fullstr = perm1;
					fullstr += ";";
						cout << "Enter name: ";
					cin >> name;
					fullstr += name;
					fullstr += ";";
					cout << "Enter genre 1: ";
					name = "";
					cin >> name;
					fullstr += name;
					fullstr += ";";
					cout << "Enter genre 2: ";
					name = "";
					cin >> name;
					fullstr += name;
					fullstr += ";";
					do{
						cout << "Enter friend perm (-1 to stop): ";
						cin>>perm;
						if(perm>=0){
						string perm2 = to_string(perm);
						fullstr+=perm2;
						fullstr+=";";
						}

					}
					while(perm>=0);
					fullstr.pop_back();
					insertion(fullstr);
					break;
					}
				case 3:
					{
					//find user
					cout << "Enter the perm number you would like to find: ";
					cin >> perm;
					find(perm,root);
					if(!found){
					  cout << "Perm not found\n";
					}
					break;
					}
				case 4:
					{
					//find details
					cout << "Enter the perm number you would like to find: ";
					cin >> perm;
					findDetails(perm,root);
					if(!found)
						cout<<"Perm not found\n";
					break;
					}
				case 5:
					{
					//recommend
					  cout<<"Enter the perm for recommendations: ";
					  cin>>perm;
					  recommend(perm);
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
