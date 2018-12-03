#include "Entry.h"

using namespace std;

int Entry::compareTo(Entry one, Entry two){
  if(one < two){
    return -1;
  }
  else if(one == two){
    return 0;
  }
  else{
    return 1;
  }
}
