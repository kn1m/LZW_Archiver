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


std::vector<char> operator + (std::vector<char> vc, char c);

void decompress(std::istream &is, std::ostream &os);

void compress(std::istream &is, std::ostream &os);


#endif //LZW_ARCHIVER_CORE_H
