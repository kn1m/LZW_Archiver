//
// Created by m3sc4 on 27.09.15.
//

#ifndef LZW_ARCHIVER_CORE_H
#define LZW_ARCHIVER_CORE_H

#include <vector>
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <ios>
#include <iostream>
#include <istream>
#include <limits>
#include <map>
#include <ostream>
#include <stdexcept>
#include <string>


using CodeType = std::uint16_t;

namespace globals {

    const CodeType dms {std::numeric_limits<CodeType>::max()};
}

void check_file(std::istream &is);

void check_code(CodeType k, std::vector<std::vector<char>> &dictionary);

void check_dictionary_decompress_size(std::vector<std::vector<char>> &dictionary);

void check_dictionary_compress_size(std::map<std::vector<char>, CodeType> &dictionary);

void decompress_key(CodeType k, std::vector<std::vector<char>> &dictionary, std::vector<char> &s);

void write_dictionary(CodeType k, std::vector<std::vector<char>> &dictionary, std::vector<char> &s);

void compress_key(std::ostream &os, std::vector<char> &s, std::map<std::vector<char>, CodeType> &dictionary, char &c);

std::vector<char> operator + (std::vector<char> vc, char c);

void decompress(std::istream &is, std::ostream &os);

void compress(std::istream &is, std::ostream &os);

void reset_compress_dictionary(std::map<std::vector<char>, CodeType> &dictionary);

void reset_decompress_dictionary(std::vector<std::vector<char>> &dictionary);

#endif //LZW_ARCHIVER_CORE_H
