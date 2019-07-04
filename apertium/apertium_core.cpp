#include <apertium/string_utils.h>
#include <apertium/tagger.h>
#include <apertium/file_tagger.h>
#include <iostream>

class apertium: public Apertium::apertium_tagger
{
public:
  /**
   * Imitates functionality of apertium-core binaries using file path
   */
  
  apertium(int &argc, char **&argv): apertium_tagger(argc, argv){}
};


int main()
{
  int argc;
  char **argv;
  argc = 3;
  argv = (char**)malloc(sizeof(char*)*argc);
  argv[0] = "apertium-tagger";
  argv[1] = "-g";
  argv[2] = "/usr/share/apertium/apertium-eng-spa/eng-spa.prob";
  apertium ap(argc, argv);
}
