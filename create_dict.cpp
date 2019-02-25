#include "huffman.h"

int main(int argc, char * argv[]){
  if (argc < 3)
    std::cout << "example: " << argv[0] << " file.txt table.tbl";

  ifstream textf;
  ofstream tablef;

  textf.open (argv[1]);
  tablef.open(argv[2], ios::out | ios::trunc | ios::binary);

  Huffman huff;

  string line;
  while ( getline (textf, line) ){
    huff.calc_weight(line.c_str());
  }

  huff.print_weights();
  huff.create_dict();
  huff.print_codes();
  huff.table2file(tablef);

  textf.clear();
  textf.seekg(0);
  huff.encode(textf);

  textf.close();
  tablef.close();
  return 0;
}
