#!/usr/bin/env python

import os
import random
import subprocess
import sys
import time

def run_benchmark(iter_cnt, exec):
    subprocess.call([exec, str(iter_cnt), '0', '1239129.123'], stdout=sys.stdout)
    sys.stdout.flush()

def scatter_one_plot(plt, x, data):
    import numpy as np
    overloads = [d[0] for d in data]
    timings = [float(d[x+2])/1000.0 for d in data]
    marker, color, label = {
        (0, 'gcc'): ('o', '#ff7f0e', f'{data[0][1]}, raw loop'),
        (1, 'gcc'): ('o', '#2ca02c', f'{data[0][1]}, find_if'),
        (2, 'gcc'): ('o', '#d62728', f'{data[0][1]}, ranges'),
        (3, 'gcc'): ('o', '#1f77b4', f'{data[0][1]}, ranges w/ anon lambda'),
        (0, 'clang'): ('x', '#bf0f0a', f'{data[0][1]}, raw loop'),
        (1, 'clang'): ('x', '#2ca01c', f'{data[0][1]}, find_if'),
        (2, 'clang'): ('x', '#df27b8', f'{data[0][1]}, ranges'),
        (3, 'clang'): ('x', '#1f97e1', f'{data[0][1]}, ranges w/ anon lambda'),
    }[(x, data[0][1])]
    plt.scatter(overloads, timings, marker=marker, color=color, label=label, s=10)

    a, b, c, d, e = np.polyfit(overloads, timings, 4)
    xs = list(range(overloads[0], overloads[-1]))
    plt.plot(xs, [a*x*x*x*x + b*x*x*x + c*x*x + d*x + e for x in xs], color=color, linewidth=1)


if sys.argv[1] == '--graph':
    import matplotlib.pyplot as plt

    field_arr = []
    if len(sys.argv) > 2:
        for file in sys.argv[2:]:
            with open(file, "r") as f:
                fields = list([line.split(' ') for line in f.readlines()])
                field_arr.append(fields)
    else:
        fields = [line.split(' ') for line in sys.stdin.readlines()]
        field_arr = [fields]
    for fields in field_arr:
        data = [(int(f[0]), str(f[1]), str(f[2]).split('ns')[0], str(f[3]).split('ns')[0], str(f[4]).split('ns')[0], str(f[5]).split('ns')[0]) for f in fields]
        for method in [0, 1, 2, 3]:
            scatter_one_plot(plt, method, data)
    plt.xlabel("Iteration count")
    plt.ylabel("Execution time (us)")
    # plt.yscale('log')
    plt.legend()

    plt.savefig('ranges_performance.svg')

    plt.show()
    
    # sys.path.append('./tikzplotlib/src/')
    # import tikzplotlib
    # tikzplotlib.save("test.tex")
elif sys.argv[1] == '--time':
    start_size = 1000
    step_size = 5000
    final_size = 1000000
    for i in range(start_size, final_size + step_size, step_size):
        run_benchmark(i, sys.argv[2])
else:
    print('Usage: ./x.py --time <exec> | ./x.py --graph')
