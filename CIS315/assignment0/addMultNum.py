import math
import sys

def add_mult(x, y):
    add = int(x) + int(y)
    mult = int(x) * int(y)
    return add, mult

def main():
    for line in sys.stdin:
        line = line.split()
        if len(line)  > 1:
            x = line[0]
            y = line[1]
            add,mult = add_mult(x,y)
            print add,mult

    return


if __name__ == "__main__":
    main()
