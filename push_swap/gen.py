#!/usr/bin/env python3

import sys
import random

INT32_MAX = 2**31 - 1
INT32_MIN = -2**31


def gen_to(count: int, f):
    random.seed()
    data = random.sample(range(INT32_MIN, INT32_MAX + 1), k=count)
    f.write(' '.join(map(str, data)))


if __name__ == '__main__':
    gen_to(int(sys.argv[1]), sys.stdout)
