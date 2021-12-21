import random

ins = []

for i in range(10):
    chs = ""
    for j in range(int(254 / 10 * (i + 1))):
        ch = random.randint(97, 122)
        chs += chr(ch)
    ins.append(chs)

for i in range(10):
    with open('pretest/case%d.in' % i, 'w', newline='\n') as fin:
        fin.write(ins[i] + '\n')

    with open('pretest/case%d.out' % i, 'w', newline='\n') as fout:
        for j in range(97, 123):
            count = ins[i].count(chr(j))
            if count != 0:
                fout.write(chr(j) + ': ' + str(count) + '\n')
