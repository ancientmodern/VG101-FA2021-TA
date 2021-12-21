import random
import numpy as np

nums = [1, 5, 10, 20, 50, 100, 200, 1000, 10000, 1000000]

for i in range(10):
    arr = random.sample(range(-1000000000, 1000000000), k=nums[i])
    arr = [num / 10000 for num in arr]
    with open('case%d/P5.txt' % i, 'w', newline='\n') as fin:
        for j in range(nums[i] - 1):
            fin.write('%f\n' % arr[j])
        fin.write('%f' % arr[nums[i] - 1])

    with open('case%d/P5.out' % i, 'w', newline='\n') as fout:
        fout.write('mean = %f\tmedian = %f\n' % (np.mean(arr), np.median(arr)))
