#include <string>

#ifndef USER_H
#define USER_H

using namespace std;

class User{
 public:
  User();
  User(int perm, string name, string genre1, string genre2);
  void setPerm(int perm);
  int getPerm();
  void setName(string name);
  string getName();
  void setGenre1(string genre1);
  string getGenre1();
  void setGenre2(string genre2);
  string getGenre2();
 private:
  int perm_number;
  string name;
  string genre1;
  string genre2;
}

#endif
