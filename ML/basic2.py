import sys
import os.path
import pandas as pd

if __name__ == "__main__":
    input_filename = sys.argv[1]

    data = pd.read_csv(input_filename, sep='\t')

    base_name, ext = os.path.splitext(input_filename)
    ii = 0
    while (os.path.exists('{}_{}'.format(base_name, ii))):
        ii += 1
    dirname = '{}_{}'.format(base_name, ii)
    os.mkdir(dirname)

    data.describe().to_csv('{}/statistics.csv'.format(dirname))
