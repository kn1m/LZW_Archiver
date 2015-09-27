//
// Created by m3sc4 on 28.09.15.
//

#define BOOST_TEST_MAIN
#if !defined(WIN32)
    #define BOOST_TEST_DYN_LINK
#endif

#include <boost/test/unit_test.hpp>
#include "core.h"

BOOST_AUTO_TEST_CASE(Compress) {

    std::string input_data = "hello from lzw!";
    std::string output_data = "";
    std::string line;

    std::ifstream input_file_c("test.txt", std::ios_base::binary);
    std::ofstream output_file_c("new.lzw", std::ios_base::binary);
    compress(input_file_c, output_file_c);
    output_file_c.close();

    std::ifstream input_file_d("new.lzw", std::ios_base::binary);
    std::ofstream output_file_d("new.txt", std::ios_base::binary);
    decompress(input_file_d, output_file_d);
    output_file_d.close();

    std::ifstream test_file("new.txt");
    if (test_file.is_open())
    {
        while (getline (test_file,line))
        {
           output_data += line;
        }
        test_file.close();
    }

    BOOST_CHECK_EQUAL(input_data, output_data);
}


