#!/usr/bin/python

# Generate sine table
# 
# Mikael Forsberg 2015
# AGPLv3
# 
# usage gensine.py size
# 
import math
import sys

def gensine(size):
    print("float sines[" + str(size) + "] = {")
    
    n = 0
    
    for i in range(0, size):
        sys.stdout.write("{0:.9f}f".format(math.sin((float(i) / float(size)) * 2.0 * math.pi)))
        n += 13
        
        if i + 1 != size:
            sys.stdout.write(", ")
            n += 2
        
        if n > 80:
            n = 0
            print("")
    
    print("};")

gensine(256)
