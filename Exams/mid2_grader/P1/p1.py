import math

base = [0, 0, 1, 1, 3, 2, 1234, 44182, 2147483647, 2147483647]
exp = [0, 10000, 0, 10000, 2, int(math.log(2147483647, 2)), int(math.log(2147483647, 1234)),
       int(math.log(2147483647, 44182)), 0, 1]

for i in range(10):
    with open('pretest/case%d.in' % i, 'w', newline='\n') as fin:
        fin.write('%d %d\n' % (base[i], exp[i]))

    with open('pretest/case%d.out' % i, 'w', newline='\n') as fout:
        fout.write('%d\n' % base[i] ** exp[i])
