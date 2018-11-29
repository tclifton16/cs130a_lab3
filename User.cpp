#incude <string>

#include "User.h"

using namespace std;

User::User(){
  perm_number = 0;
  name = "";
  genre1 = "";
  genre2 = "";
}

User::User(int perm, string name, string genre1, string genre2){
  this->perm_number = perm;
  this->name = name;
  this->genre1 = genre1;
  this->genre2 = genre2;
}

void User::setPerm(int perm){
  this->perm_number = perm;
}

int User::getPerm(){
  return perm;
}

void User::setName(string name){
  this->name = name;
}

string User::getName(){
  return name;
}

void User::setGenre1(string genre1){
  this->genre1 = genre1;
}

string User::getGenre1(){
  return genre1;
}

void User::setGenre2(string genre2){
  this->genre2 = genre2;
}

string User::getGenre2(){
  return genre2;
}
