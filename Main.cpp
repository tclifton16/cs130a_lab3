#include <string>
#include <iostream>

using namespace std;

int main(){
  bool q = false;
  int input;

  cout << "Welcome!\n";
  while(!q){
    cout << "What operation would you like to perform?\n\t1: Input from file\n\t2: Add user\n\t3: Find user\n\t4: Find user's details\n\t5: Recommend friends\n\t6: Quit";
    if(cin >> input){
      switch (input){
      case 1:
	//input from file
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
