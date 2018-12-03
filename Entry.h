

#ifndef ENTRY_H
#define ENTRY_H

class Entry{
 public:
  int compareTo(Entry one, Entry two);
 private:
  Node* next;
  User user;
};
