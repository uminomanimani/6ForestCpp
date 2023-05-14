baseline = 0
experiment = 0

with(open('./Baseline.txt', 'r')) as f:
    line = f.readline()
    while line:
        baseline += (int(line))
        line = f.readline()


with(open('./Experiment.txt', 'r')) as f:
    line = f.readline()
    while line:
        experiment += (int(line))
        line = f.readline()


print(f'baseline : {baseline}, experiment : {experiment}, baseline - experiment : {baseline-experiment}')