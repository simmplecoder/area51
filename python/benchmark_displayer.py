#!/usr/bin/env python3

import matplotlib.pyplot as plt
from collections import OrderedDict
import sys
import os


def read_metadata(filename):
    file = open(filename)
    xlabel = file.readline().strip()
    ylabel = file.readline().strip()
    benchmark_files = []
    for line in file.readlines():
        if line == '\n':
            continue
        benchmark_files.append(line.strip())

    return xlabel, ylabel, benchmark_files


def read_benchmark(file):
    benchmark_name = file.readline().strip()
    if benchmark_name == '\n':
        benchmark_name = None

    readings = []
    for line in file.readlines():
        a, b = line.split()
        readings.append((int(a), int(b)))

    return benchmark_name, readings

inputdirectory = 'benchmarks/'
outputdirectory = 'benchmarks/out/'

commandcount = len(sys.argv)
if commandcount == 1:
    print('No input directory and output directory specified. Defaulting to "benchmarks" and "benchmarks/out"')
elif commandcount == 2:
    print('Only one parameter specified. Assuming it is input directory, '
          'defaulting output directory to "benchmarks/out"')
    inputdirectory = sys.argv[1]
elif commandcount == 3:
    inputdirectory = sys.argv[1]
    outputdirectory = sys.argv[2]
else:
    print('usage: <input-directory> <output-directory>')
    exit()

if not inputdirectory.endswith('/'):
    inputdirectory += '/'
if not outputdirectory.endswith('/'):
    outputdirectory += '/'

metadata = read_metadata(inputdirectory + 'benchmarks.txt')
for file in metadata[2]:
    benchmark_name, readings = read_benchmark(open(inputdirectory + file))
    x, y = zip(*readings)
    plt.plot(x, y, label=benchmark_name)

handles, labels = plt.gca().get_legend_handles_labels()
by_label = OrderedDict(zip(labels, handles))
plt.xlabel(metadata[0])
plt.ylabel(metadata[1])
plt.legend(by_label.values(), by_label.keys(), loc='upper left')

os.makedirs(outputdirectory, exist_ok=True)
plt.savefig(outputdirectory + 'plot.pdf')
print('successfully plotted the graphs and saved in ' + outputdirectory)