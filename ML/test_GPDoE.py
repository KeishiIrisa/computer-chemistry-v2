import sys
import numpy as np
import itertools
import pandas as pd
from mylib.regression.GPDoE import GPDoE

if __name__ == "__main__":
    filename = sys.argv[1]

    data = pd.read_csv(filename, header=None)

    x_train = data.iloc[:, :-1]
    y_train = data.iloc[:, -1:]

    x_test = pd.DataFrame(itertools.product(np.arange(10), repeat=4))

    pd.set_option("display.max_columns", 5)
    GPDoE(x_train, y_train, x_test)
