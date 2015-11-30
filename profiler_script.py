#!/usr/bin/python3.4

import glob
import os
import argparse
import filecmp

parser = argparse.ArgumentParser()

parser.add_argument("-r", "--remove_old", action='store_true',
                    help="cleanes old profiler reports")
parser.add_argument("-e", "--executable", type=str,
                    help="executable to profile")
parser.add_argument("-g", "--graph", type=str,
                    help="profiler graph file")
parser.add_argument("-c", "--compress", action='store_true',
                    help="use executable to compress")
parser.add_argument("-d", "--decompress", action='store_true',
                    help="use executable to decompress")
parser.add_argument("-i", "--input", type=str,
                    help="input file name for executable")
parser.add_argument("-o", "--output", type=str,
                    help="output file name for executable")
parser.add_argument("-s", "--speed", action='store_true',
                    help="searching for best optimiztion modes")
args = parser.parse_args()


def check_file(test_filename, filename, output=None):
    if not filecmp.cmp(test_filename, filename):
        #if files are not equal then do =>
        if output:
            output.write(opt + "\n")
        diff_run = ["diff", test_filename, filename, ">", filename + ".diff"]
        os.system(" ".join(diff_run))
    else:
        #remove uninteresting file
        rm_run = ["rm", "-f", filename]
        os.system(" ".join(rm_run))

if args.speed:
    default_flags = "-std=c++11 -S -O"
    run_gcc_base = ["g++", default_flags]
    src = ["core.cpp"]
    all_flags = 0
    used_flags = 0

    if not os.path.exists("opt/"):
        os.makedirs("opt/")

    output = open("opt/uoptions", "w+")

    test_filename = "opt/core_uo.o"
    compile_test_run = run_gcc_base + src + ["-o", test_filename]
    os.system(" ".join(compile_test_run))

    with open("avaible_optimization_options", "r+") as f:
        for line in f:
                opt = line.replace('\n', '').strip()
                if len(opt) > 0:
                    all_flags += 1
                    filename = "opt/" + opt[2:] + ".o"
                    print("Checking: " + filename)

                    compile_opt_run = run_gcc_base + [opt] + src +  ["-o", filename]
                    os.system(" ".join(compile_opt_run))

                    check_file(test_filename, filename, output)
        output.close()

        options = []
        with open("opt/uoptions", 'r+') as f:
            for line in f:
                options.append(line.replace('\n', '').strip())

        used_flags = len(options)

        print("{0} of {1} flags were useful.".format(used_flags, all_flags))

        print("Object file with best flags compiled.")

        final_filename = "opt/core_bo.o"
        final_complile_run = run_gcc_base + options + src + ["-o", final_filename]
        os.system(" ".join(final_complile_run))
        check_file(test_filename, final_filename)
        
if args.remove_old:
    [os.system("rm " + x) for x in glob.glob('callgrind.out.*')]
    [os.system("rm " + x) for x in glob.glob('*.svg')]
    print("Old profiler files cleaned.")

def profile(mode, executable, input, output, graph):
    if executable and input and output:
        os.system("valgrind --tool=callgrind ./" + executable + mode + input + " " + output)
        if graph:
            logs = [x for x in glob.glob('callgrind.out.*')]
            os.system("gprof2dot -f callgrind " + logs[0] +" | dot -Tsvg -o "+ graph +".svg")
    elif not executable or not input or not output:
        print("Not all parameters was specified.")

if args.compress or args.decompress:
    if args.compress:
        command = " -c "
        profile(command, args.executable, args.input, args.output, args.graph)
    else:
        command = " -d "
        profile(command, args.executable, args.input, args.output, args.graph)
