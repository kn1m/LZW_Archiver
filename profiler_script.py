#!/usr/bin/python3.4

import glob
import os
import argparse

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
args = parser.parse_args()

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