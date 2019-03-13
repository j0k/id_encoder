#include "bitpacker.h"



using std::ifstream;

int main(int argc, char * argv[]){
  if (argc == 1){
    cout << "example:" << endl;
    cout << argv[0] << " file.source" << " tobits" << endl;
    cout << argv[0] << " file.source" << " frombits" << endl;
  }

  uint8_t buf[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
  memstream s(buf, 5);

  char b;
  int readed;

  int b_size = 74;
  if (argc == 3){
    ifstream fin(argv[1]);
    fin.seekg(0, fin.end);
    size_t f_length = fin.tellg();
    fin.seekg(0, fin.beg);

    while(!fin.eof()){
      char buffer[b_size];
      if (f_length > sizeof (buffer))
      {
          f_length = sizeof (buffer);
      }
      fin.read(buffer, f_length);
      readed += f_length

      //if (!fin.eof())
      cout << "hep:" << buffer << endl;
    }
    // cout << buffer;

    while (! s.eof() ){
      s.read(&b, 1);
      //if (! s.eof() )
      std::cout << "read: " << (int)b << std::endl;
      s.read(&b, 1);
      std::cout << "read: " << (int)b << std::endl;
      s.read(&b, 1);
      //if (! s.eof() )
      std::cout << "read: " << (int)b << std::endl;
      s.read(&b, 1);
      std::cout << "read: " << (int)b << std::endl;
    }
  }



}
