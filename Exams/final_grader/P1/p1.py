import random

lhs = random.sample(range(-20000, 20000), 9)
rhs = random.sample(range(-20000, 20000), 9)

lhs.append(100)
rhs.append(100)

for i in range(10):
    with open('case%d.in' % i, 'w', newline='\n') as fin:
        fin.write('%d %d\n' % (lhs[i], rhs[i]))

    with open('case%d.out' % i, 'w', newline='\n') as fout:
        result = 0
        for j in range(min(lhs[i], rhs[i]), max(lhs[i], rhs[i]) + 1):
            result += j
        fout.write('%d\n' % result)
