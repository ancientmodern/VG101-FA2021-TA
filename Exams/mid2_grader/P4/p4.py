import random

ins = []

for i in range(9):
    chs = ""
    for j in range(i + 1):
        ch = random.randint(49, 57)
        chs += chr(ch)
    ins.append(chs)

ins.append('1111111112')

for i in range(10):
    with open('pretest/case%d.in' % i, 'w', newline='\n') as fin:
        fin.write(ins[i] + '\n')

    with open('pretest/case%d.out' % i, 'w', newline='\n') as fout:
        arr = sorted(ins[i], reverse=True)
        fout.write("".join(arr) + '\n')
