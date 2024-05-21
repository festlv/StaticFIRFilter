from scipy.signal import lfilter
import numpy as np


if __name__ == "__main__":
    coef = np.array([0.5, 1.0, 0.5])
    samples = np.array([1.0, 0.0, 0])
    print(lfilter(coef, [1.0], samples))
