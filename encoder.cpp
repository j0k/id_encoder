#include "huffman.h"

int main(int argc, char * argv[]){
  if (argc < 4)
    std::cout << "example: " << argv[0] << " file.txt dict.tbl file.out";

  ifstream textf;
  ofstream tablef;
  ofstream endcodedf;

  textf.open (argv[1]);
  tablef.open(argv[2], ios::out | ios::trunc | ios::binary);
  endcodedf.open(argv[3], ios::out | ios::trunc | ios::binary);

  Huffman huff;

  string line;
  while ( getline (textf, line) ){
    huff.calc_weight(line.c_str());
  }

  huff.create_dict();
  huff.table2file(tablef);

  textf.clear();
  textf.seekg(0);
  huff.encode(textf, endcodedf);

  textf.close();
  tablef.close();
  return 0;
}
