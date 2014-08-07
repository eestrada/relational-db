#!/usr/bin/env python
import sys

def main(args=sys.argv):
    import subprocess as sp
    import os

    try: min = int(args[1])
    except IndexError: raise
    except: min = 8
    else: args.pop(1)

    stdout = sp.check_output(['pmccabe']+args[1:],
                             stderr=open(os.devnull, mode='w'))
    import io

    outbytes = io.BytesIO(stdout)

    for line in outbytes:
        lnlist = line.split()
        if lnlist[0].isdigit() and int(lnlist[0]) > min:
            sys.stdout.write(line)

if __name__ == '__main__':
    main()
