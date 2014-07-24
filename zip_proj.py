#!/usr/bin/env python2
import os, sys, zipfile, glob

def main(args):
    paths = glob.glob('./src/*.cpp')
    paths += glob.glob('./inc/*.h')
    with zipfile.ZipFile(args[1], mode='w', compression=zipfile.ZIP_DEFLATED) as zf:
        for p in paths:
            name = p.split('/')[-1]
            zf.write(p, name)

if __name__ == '__main__':
    ret = main(sys.argv)
    sys.exit(ret)
