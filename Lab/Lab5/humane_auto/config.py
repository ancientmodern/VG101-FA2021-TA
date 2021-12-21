with open('config.yaml', 'a') as f:
    for i in range(10):
        f.write('- <<: *default\n')
        f.write('  input: pretest/case%d.in\n' % i)
        f.write('  output: pretest/case%d.out\n' % i)
        f.write('  category: pretest\n')
