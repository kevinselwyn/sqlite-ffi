#!/usr/bin/env python
# pylint: disable=C0326,R0903,W0702
"""Hybrid C/Python"""

import ctypes
import sys

INSERT_COUNT         = 1000
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
        count = INSERT_COUNT

    # get action
    try:
        action = int(sys.argv[2])
    except:
        action = 0

    # load library
    hybrid_so = ctypes.cdll.LoadLibrary('./hybrid.so')
    hybrid_so.connect.restype = ctypes.c_void_p

    # connect db
    conn = hybrid_so.connect('hybrid.db')

    if action == Action.INSERT or action == Action.BOTH:
        # start transaction
        hybrid_so.begin(conn)

        # create table
        hybrid_so.execute(conn, COMMAND_TABLE_CREATE)

        # inserts
        for i in range(0, count):
            hybrid_so.execute(conn, 'INSERT INTO COMPANY VALUES (%d, %d);' % (i, i))

        # commit inserts
        hybrid_so.commit(conn)

    if action == Action.SELECT or action == Action.BOTH:
        # selects
        for i in range(0, count):
            hybrid_so.execute(conn, 'SELECT * FROM COMPANY WHERE ID=%d;' % (i))

    # close db
    hybrid_so.close(conn)

if __name__ == '__main__':
    main()
