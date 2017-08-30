#!/usr/bin/env python
# pylint: disable=C0103,C0326,R0903,W0702
"""Native Python"""

import sqlite3
import sys

REP_COUNT            = 1000
COMMAND_TABLE_CREATE = 'CREATE TABLE COMPANY(ID INT PRIMARY KEY NOT NULL, NAME TEXT NOT NULL);'

class Action(object):
    """Action enum"""

    INSERT = 0
    SELECT = 1
    BOTH   = 2

def main():
    """Main function"""

    # get rep count
    try:
        count = int(sys.argv[1])
    except:
        count = REP_COUNT

    # get action
    try:
        action = int(sys.argv[2])
    except:
        action = 0

    # connect db
    conn = sqlite3.connect('native-py.db')
    c = conn.cursor()

    if action == Action.INSERT or action == Action.BOTH:
        # create table
        c.execute(COMMAND_TABLE_CREATE)

        # inserts
        for i in range(0, count):
            c.execute('INSERT INTO COMPANY VALUES (%d, %d);' % (i, i))

        # commit inserts
        conn.commit()

    if action == Action.SELECT or action == Action.BOTH:
        # selects
        for i in range(0, count):
            c.execute('SELECT * FROM COMPANY WHERE ID=%d;' % (i))

    # close db
    c.close()
    conn.close()

if __name__ == '__main__':
    main()
