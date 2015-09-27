//
// Created by m3sc4 on 27.09.15.
//

#include "core.h"

void print_usage(const std::string &s = "", bool su = true)
{
    if (!s.empty())
        std::cerr << "\nERROR: " << s << '\n';

    if (su)
    {
        std::cerr << "\nUsage:\n";
        std::cerr << "\tprogram -flag input_file output_file\n\n";
        std::cerr << "Where `flag' is either `c' for compressing, or `d' for decompressing, and\n";
        std::cerr << "`input_file' and `output_file' are distinct files.\n\n";
        std::cerr << "Examples:\n";
        std::cerr << "\tlzw_v1.exe -c license.txt license.lzw\n";
        std::cerr << "\tlzw_v1.exe -d license.lzw new_license.txt\n";
    }

    std::cerr << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        print_usage("Wrong number of arguments.");
        return EXIT_FAILURE;
    }

    enum class Mode {
        Compress,
        Decompress
    };

    Mode m;

    if (std::string(argv[1]) == "-c")
        m = Mode::Compress;
    else
    if (std::string(argv[1]) == "-d")
        m = Mode::Decompress;
    else
    {
        print_usage(std::string("flag `") + argv[1] + "' is not recognized.");
        return EXIT_FAILURE;
    }

    std::ifstream input_file(argv[2], std::ios_base::binary);

    if (!input_file.is_open())
    {
        print_usage(std::string("input_file `") + argv[2] + "' could not be opened.");
        return EXIT_FAILURE;
    }

    std::ofstream output_file(argv[3], std::ios_base::binary);

    if (!output_file.is_open())
    {
        print_usage(std::string("output_file `") + argv[3] + "' could not be opened.");
        return EXIT_FAILURE;
    }

    try
    {
        input_file.exceptions(std::ios_base::badbit);
        output_file.exceptions(std::ios_base::badbit | std::ios_base::failbit);

        if (m == Mode::Compress)
            compress(input_file, output_file);
        else
        if (m == Mode::Decompress)
            decompress(input_file, output_file);
    }
    catch (const std::ios_base::failure &f)
    {
        print_usage(std::string("File input/output failure: ") + f.what() + '.', false);
        return EXIT_FAILURE;
    }
    catch (const std::exception &e)
    {
        print_usage(std::string("Caught exception: ") + e.what() + '.', false);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}