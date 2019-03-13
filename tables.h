#include <map>

#include "pack_types.h"


using std::map;
using std::pair;

class Table{
  map<tcode, char> tbl;

  void set_decode_tbl();
  char* decode(char * buffer, int size);
  pair<char*, int> encode(char * buffer);
};
