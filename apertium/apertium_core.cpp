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


int main(int argc, char *argv[])
{
  apertium ap(argc, argv);
}
