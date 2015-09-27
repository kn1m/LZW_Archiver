//
// Created by m3sc4 on 27.09.15.
//

#include "core.h"

std::vector<char> operator + (std::vector<char> vc, char c)
{
    vc.push_back(c);
    return vc;
}

void reset_compress_dictionary(std::map<std::vector<char>, CodeType> &dictionary)
{
    dictionary.clear();
    const long int minc = std::numeric_limits<char>::min();
    const long int maxc = std::numeric_limits<char>::max();
    for (long int c = minc; c <= maxc; ++c)
    {
        const CodeType dictionary_size = dictionary.size();
        dictionary[{static_cast<char> (c)}] = dictionary_size;
    }
}

void check_dictionary_compress_size(std::map<std::vector<char>, CodeType> &dictionary)
{
    if (dictionary.size() == globals::dms)
        reset_compress_dictionary(dictionary);
}

void compress_key(std::ostream &os, std::vector<char> &s, std::map<std::vector<char>, CodeType> &dictionary, char &c)
{
    check_dictionary_compress_size(dictionary);
    s.push_back(c);
    if (dictionary.count(s) == 0)
    {
        const CodeType dictionary_size = dictionary.size();
        dictionary[s] = dictionary_size;
        s.pop_back();
        os.write(reinterpret_cast<const char *> (&dictionary.at(s)), sizeof (CodeType));
        s = {c};
    }
}

void compress(std::istream &is, std::ostream &os)
{
    std::map<std::vector<char>, CodeType> dictionary;
    reset_compress_dictionary(dictionary);
    std::vector<char> s;
    char c;
    while (is.get(c))
    {
        compress_key(os, s, dictionary, c);
    }
    if (!s.empty())
        os.write(reinterpret_cast<const char *> (&dictionary.at(s)), sizeof (CodeType));
}

void reset_decompress_dictionary(std::vector<std::vector<char>> &dictionary)
{
    dictionary.clear();
    dictionary.reserve(globals::dms);
    const long int minc = std::numeric_limits<char>::min();
    const long int maxc = std::numeric_limits<char>::max();
    for (long int c = minc; c <= maxc; ++c)
        dictionary.push_back({static_cast<char> (c)});
}

void check_file(std::istream &is)
{
    if (!is.eof() || is.gcount() != 0)
        throw std::runtime_error("corrupted compressed file");
}

void check_code(CodeType k, std::vector<std::vector<char>> &dictionary)
{
    if (k > dictionary.size())
        throw std::runtime_error("invalid compressed code");
}


void check_dictionary_decompress_size(std::vector<std::vector<char>> &dictionary)
{
    if (dictionary.size() == globals::dms)
        reset_decompress_dictionary(dictionary);
}

void write_dictionary(CodeType k, std::vector<std::vector<char>> &dictionary, std::vector<char> &s)
{
    if (k == dictionary.size())
        dictionary.push_back(s + s.front());
    else if (!s.empty())
        dictionary.push_back(s + dictionary.at(k).front());
}

void decompress_key(CodeType k, std::vector<std::vector<char>> &dictionary, std::vector<char> &s)
{
    check_dictionary_decompress_size(dictionary);
    check_code(k, dictionary);
    write_dictionary(k, dictionary, s);
}

void decompress(std::istream &is, std::ostream &os)
{
    std::vector<std::vector<char>> dictionary;
    reset_decompress_dictionary(dictionary);
    std::vector<char> s;
    CodeType k;
    while (is.read(reinterpret_cast<char *> (&k), sizeof (CodeType)))
    {
        decompress_key(k, dictionary, s);
        os.write(&dictionary.at(k).front(), dictionary.at(k).size());
        s = dictionary.at(k);
    }
    check_file(is);
}


