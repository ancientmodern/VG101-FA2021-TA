import random
import time

COURSE = 15
NAME = 3
TOTAL = COURSE * NAME

for nt in range(10):
    timestamp = random.sample(range(1, int(time.time())), TOTAL * 3)
    diff = random.sample(range(int(-2 ** 29), int(2 ** 29)), TOTAL * 3)
    with open('driver/table%d.txt' % nt, 'w', newline='\n') as tfile:
        tfile.write('test%d\n' % nt)
        for i in range(COURSE):
            for j in range(NAME):
                ddl = int(time.strftime('%Y%m%d', time.localtime(timestamp[NAME * i + j])))
                tfile.write('course_name%d assign_name%d %d %d\n' % (i, j, ddl, diff[NAME * i + j]))

    with open('pretest/case%d.in' % nt, 'w', newline='\n') as cfile:
        for i in range(10):
            cfile.write('LOAD table%d.txt\n' % (9 - i))
        cfile.write('LIST\n')
        for i in range(COURSE, COURSE * 2):
            for j in range(NAME):
                ddl = int(time.strftime('%Y%m%d', time.localtime(timestamp[NAME * i + j])))
                cfile.write(
                    'INSERT ( course_name%d assign_name%d %d %d ) test%d\n' % (i, j, ddl, diff[NAME * i + j], nt))
        for i in range(COURSE * 2):
            cfile.write('UPDATE ( course course%d ) test%d ( course_name%d * )\n' % (i, nt, i))
        for i in range(NAME):
            cfile.write('UPDATE ( name name%d ) test%d ( * assign_name%d )\n' % (i, nt, i))
        for i in range(COURSE * 2):
            for j in range(NAME):
                ddl = int(time.strftime('%Y%m%d', time.localtime(timestamp[NAME * i + j + 5])))
                cfile.write('UPDATE ( deadline %d ) test%d ( course%d name%d )\n' % (ddl, nt, i, j))
                cfile.write(
                    'UPDATE ( difficulty %d ) test%d ( course%d name%d )\n' % (diff[NAME * i + j + 4], nt, i, j))
        cfile.write('DELETE test%d ( * name%d )\n' % (nt, 0))
        for i in range(COURSE, COURSE * 2):
            cfile.write('DELETE test%d ( course%d * )\n' % (nt, i))
        cfile.write('SELECT test%d ( * * ) SORT difficulty LIMIT 5\n' % nt)
        cfile.write('SELECT test%d ( * name1 ) SORT deadline LIMIT 6\n' % nt)
        cfile.write('SELECT test%d ( * name2 ) SORT difficulty LIMIT 7\n' % nt)
        cfile.write('SELECT test%d ( course2 * ) SORT difficulty LIMIT 100\n' % nt)
        cfile.write('PRINT test%d\n' % nt)
        cfile.write('EXIT\n')
