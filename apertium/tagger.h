// Copyright (C) 2005 Universitat d'Alacant / Universidad de Alicante
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 2 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.

#ifndef TAGGER_H
#define TAGGER_H


#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <locale>
#include <sstream>
#include <string>
#include <unistd.h>

#include "constructor_eq_delete.h"
#include "optional.h"

#include "getopt_long.h"
#include <string>

#include "apertium_config.h"

#include "align.h"
#include "basic_exception_type.h"
#include "basic_stream_tagger.h"
#include "basic_stream_tagger_trainer.h"
#include "basic_tagger.h"
#include "err_exception.h"
#include "exception.h"
#include "file_tagger.h"
#include "linebreak.h"
#include "stream_5_3_1_tagger.h"
#include "stream_5_3_1_tagger_trainer.h"
#include "stream_5_3_2_tagger.h"
#include "stream_5_3_2_tagger_trainer.h"
#include "stream_5_3_3_tagger.h"
#include "stream_5_3_3_tagger_trainer.h"
#include <apertium/perceptron_tagger.h>
#include <apertium/file_morpho_stream.h>
#include <apertium/hmm.h>
#include <apertium/lswpost.h>
#include <apertium/tagger_word.h>
#include <apertium/shell_utils.h>

#include <lttoolbox/lt_locale.h>

namespace Apertium {
class apertium_tagger : private constructor_eq_delete {
public:
  apertium_tagger(int &argc, char **&argv);

protected:
  enum FunctionType { Tagger, Retrain, Supervised, Train };
  void functionTypeOptionCase(const FunctionType &FunctionType_);
  Apertium::Optional<FunctionType> TheFunctionType;
  enum FunctionTypeType { Unigram, SlidingWindow, Perceptron };
  void functionTypeTypeOptionCase(const FunctionTypeType &FunctionTypeType_);
  void g_FILE_Tagger(Apertium::FILE_Tagger &FILE_Tagger_);
  Apertium::Optional<FunctionTypeType> TheFunctionTypeType;
  basic_Tagger::Flags TheFlags;

private:
  enum UnigramType { Stream_5_3_1, Stream_5_3_2, Stream_5_3_3 };
  static void help();
  static const struct option longopts[];

  static std::string option_string(const int &indexptr_);
  static std::string option_string(const struct option &option_);
  static void locale_global_();
  void set_indexptr();
  void flagOptionCase(bool (basic_Tagger::Flags::*GetFlag)() const,
                      void (basic_Tagger::Flags::*SetFlag)(const bool &));
  std::string option_string();
  void getCgAugmentedModeArgument();
  void getIterationsArgument();
  unsigned long optarg_unsigned_long(const char *metavar);
  void get_file_arguments(
    bool get_crp_fn,
    char **DicFn, char **CrpFn,
    char **TaggedFn, char **UntaggedFn,
    char **TsxFn, char **ProbFn);
  void init_FILE_Tagger(FILE_Tagger &FILE_Tagger_, string const &TsxFn);

  MorphoStream* setup_untagged_morpho_stream(
    FILE_Tagger &FILE_Tagger_,
    char *DicFn, char *UntaggedFn,
    FILE **Dictionary, FILE **UntaggedCorpus);
  void close_untagged_files(
    char *DicFn, char *UntaggedFn,
    FILE *Dictionary, FILE *UntaggedCorpus);

  void g_StreamTagger(StreamTagger &StreamTagger_);
  void s_StreamTaggerTrainer(StreamTaggerTrainer &StreamTaggerTrainer_);
  void r_FILE_Tagger(FILE_Tagger &FILE_Tagger_);
  void s_FILE_Tagger(FILE_Tagger &FILE_Tagger_);
  void t_FILE_Tagger(FILE_Tagger &FILE_Tagger_);
  void c_FILE_Tagger(FILE_Tagger &FILE_Tagger_);
  int &argc;
  char **&argv;
  int The_val;
  int nonoptarg;


  int The_indexptr;
  Apertium::Optional<int> FunctionTypeTypeOption_indexptr;
  Apertium::Optional<int> FunctionTypeOption_indexptr;
  Apertium::Optional<UnigramType> TheUnigramType;
  unsigned long TheFunctionTypeOptionArgument;
  unsigned long CgAugmentedMode;
};
}

#endif // TAGGER_H
