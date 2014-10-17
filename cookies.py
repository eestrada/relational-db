#!/usr/bin/env python 

import sqlite3
import io
import sys

def main(argv=sys.argv):
    """Converts cookies stored in a sqlite3 database to the old netscape cookies.txt format.
    
    usually the google chrome cookie database lives at '/users/animation/eestrada/.config/google-chrome/Default/Cookies'
    """
    
    if len(argv) != 3:
        sys.stderr.write('requires exactly 3 arguments')
        sys.exit(2)

    cookie_file = argv[1]
    output_file = argv[2]



    conn = sqlite3.connect(cookie_file)
    cur = conn.cursor()
    cur.execute('SELECT host_key, path, secure, expires_utc, name, value FROM cookies')
    with io.open(output_file, 'w') as f:
        i = 0
        for row in cur.fetchall():
          f.write("%s\tTRUE\t%s\t%s\t%d\t%s\t%s\n" % (row[0], row[1], str(bool(row[2])).upper(), row[3], str(row[4]), str(row[5])))
          i += 1
        print("%d rows written" % i)
    # f.close()
    conn.close()

if __name__ == '__main__':
    main()
