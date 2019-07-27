#!/usr/bin/env python3

'''
Setup for SWIG Python bindings for apertium
'''
from os import path
from distutils.core import Extension, setup
from distutils.command.build import build


class CustomBuild(build):
    sub_commands = [
        ('build_ext', build.has_ext_modules),
        ('build_py', build.has_pure_modules),
        ('build_clib', build.has_c_libraries),
        ('build_scripts', build.has_scripts),
    ]


def get_sources():
    sources = ['apertium_core.i']
    cc_sources = [
                  # interchunk.cc postchunk.cc transfer.cc
                  'apertium_re.cc', 'interchunk.cc', 'interchunk_word.cc', 'postchunk.cc', 'string_utils.cc', 'transfer.cc',
                  'transfer_data.cc', 'transfer_instr.cc', 'transfer_mult.cc', 'transfer_token.cc', 'transfer_word.cc',
                  'transfer_word_list.cc', 'trx_reader.cc', 'utf_converter.cc', 'xml_reader.cc',
                  # 'pretransfer.cc'
                  'pretransfer.cc',
                  # tagger.cc
                  'a.cc', 'align.cc', 'analysis.cc', 'basic_5_3_1_tagger.cc', 'basic_5_3_2_tagger.cc', 'basic_exception_type.cc',
                  'basic_stream_tagger.cc', 'basic_stream_tagger_trainer.cc', 'basic_tagger.cc', 'collection.cc',
                  'constant_manager.cc', 'endian_double_util.cc', 'exception_type.cc', 'feature_vec.cc',
                  'feature_vec_averager.cc', 'file_morpho_stream.cc', 'file_tagger.cc', 'hmm.cc', 'i.cc', 'lemma.cc',
                  'linebreak.cc', 'lswpost.cc', 'morpheme.cc', 'morpho_stream.cc', 'mtx_reader.cc', 'perceptron_spec.cc',
                  'perceptron_tagger.cc', 'sentence_stream.cc', 'shell_utils.cc', 'stream.cc', 'stream_5_3_1_tagger.cc',
                  'stream_5_3_1_tagger_trainer.cc', 'stream_5_3_2_tagger.cc', 'stream_5_3_2_tagger_trainer.cc',
                  'stream_5_3_3_tagger.cc', 'stream_5_3_3_tagger_trainer.cc', 'stream_tagger.cc', 'stream_tagger_trainer.cc',
                  'tag.cc', 'tagger.cc', 'tagger_data.cc', 'tagger_data_hmm.cc', 'tagger_data_lsw.cc',
                  'tagger_data_percep_coarse_tags.cc', 'tagger_utils.cc', 'tagger_word.cc', 'tsx_reader.cc',
                  'wchar_t_exception_type.cc']
    rel_path = '../apertium'
    sources.extend(path.join(rel_path, f) for f in cc_sources)
    return sources

def get_include_dirs():
    # Remove '-I' from Flags, as python add '-I' on its own
    dirs = '-I/usr/local/include/lttoolbox-3.5 -I/usr/local/lib/lttoolbox-3.5/include -I/usr/include/libxml2 '.replace('-I', '').split()
    return dirs + ['..']


apertium_core_module = Extension(
    name='_apertium_core',
    sources=get_sources(),
    swig_opts=['-c++', '-I..', '-I../apertium', '-Wall']+'-I/usr/local/include/lttoolbox-3.5 -I/usr/local/lib/lttoolbox-3.5/include -I/usr/include/libxml2 '.split(),
    include_dirs=get_include_dirs(),
    library_dirs=['/usr/include/libxml2', '/usr/local/lib'],
    extra_compile_args=' -I/usr/local/include/lttoolbox-3.5 -I/usr/local/lib/lttoolbox-3.5/include -I/usr/include/libxml2 '.split()+'-Wall -Wextra -g -O2 -std=c++2a'.split(),
    extra_link_args=' -lpcreposix -lpcre -lpcrecpp -L/usr/local/lib -llttoolbox3 -lxml2 -lpcre '.split(),
)

setup(
    name='apertium',
    version='3.5.2',
    description='SWIG interface to apertium',
    long_description='SWIG interface to apertium for use in apertium-python',
    # TODO: author, maintainer, url
    author_email='sortiz@users.sourceforge.net',
    license='GPL-3.0+',
    maintainer_email='sortiz@users.sourceforge.net',
    cmdclass={'build': CustomBuild},
    ext_modules=[apertium_core_module],
    py_modules=['apertium_core'],
)
