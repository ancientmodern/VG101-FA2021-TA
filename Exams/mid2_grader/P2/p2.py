import random

ins = []
outs = []

for i in range(10):
    chs = ""
    out = 0
    for j in range(int(254 / 10 * (i + 1))):
        ch = random.randint(0, 61)
        if 0 <= ch <= 9:
            chs += chr(ch + ord('0'))
            out += ch
        elif 10 <= ch <= 35:
            chs += chr(ch - 10 + ord('a'))
        else:
            chs += chr(ch - 36 + ord('A'))
    ins.append(chs)
    outs.append(out)

for i in range(10):
    with open('pretest/case%d.in' % i, 'w', newline='\n') as fin:
        fin.write(ins[i] + '\n')

    with open('pretest/case%d.out' % i, 'w', newline='\n') as fout:
        fout.write('%d\n' % outs[i])
