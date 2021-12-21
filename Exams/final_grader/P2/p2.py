import random
import math

num = [random.randint(1, 5) for _ in range(10)]
ins = list()
for i in num:
    l = [chr(random.randint(0, 25) + ord('a')) for j in range(i)]
    ins.append("".join(l))

for i in range(10):
    with open('case%d.in' % i, 'w', newline='\n') as fin:
        fin.write(ins[i] + '\n')

    with open('case%d.out' % i, 'w', newline='\n') as fout:
        result = 0
        for j in range(len(ins[i])):
            result += (ord(ins[i][j]) - ord('a') + 1) * \
                pow(10, len(ins[i]) - j - 1)
        fout.write('%d\n' % result)
