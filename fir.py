from scipy.signal import lfilter
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


if __name__ == "__main__":

    taps = np.array([-7.905163e-04, -8.125758e-04, -8.442258e-04, -8.857786e-04, -9.373221e-04, -9.987087e-04, -1.069547e-03, -1.149197e-03, -1.236770e-03, -1.331128e-03, -1.430892e-03, -1.534453e-03, -1.639982e-03, -1.745447e-03, -1.848635e-03, -1.947175e-03, -2.038563e-03, -2.120191e-03, -2.189378e-03, -2.243403e-03, -2.279541e-03, -2.295096e-03, -2.287440e-03, -2.254048e-03, -2.192535e-03, -2.100690e-03, -1.976514e-03, -1.818251e-03, -1.624415e-03, -1.393826e-03, -1.125630e-03, -8.193195e-04, -4.747582e-04, -9.218992e-05, 3.277487e-04, 7.840226e-04, 1.275197e-03, 1.799440e-03, 2.354531e-03, 2.937873e-03, 3.546509e-03, 4.177145e-03, 4.826172e-03, 5.489700e-03, 6.163587e-03, 6.843479e-03, 7.524847e-03, 8.203030e-03, 8.873280e-03, 9.530804e-03, 1.017082e-02, 1.078858e-02, 1.137945e-02, 1.193895e-02, 1.246276e-02, 1.294682e-02, 1.338734e-02, 1.378083e-02, 1.412417e-02, 1.441462e-02, 1.464984e-02, 1.482794e-02, 1.494749e-02, 1.500750e-02, 1.500750e-02, 1.494749e-02, 1.482794e-02, 1.464984e-02, 1.441462e-02, 1.412417e-02, 1.378083e-02, 1.338734e-02, 1.294682e-02, 1.246276e-02, 1.193895e-02, 1.137945e-02, 1.078858e-02, 1.017082e-02, 9.530804e-03, 8.873280e-03, 8.203030e-03, 7.524847e-03, 6.843479e-03, 6.163587e-03, 5.489700e-03, 4.826172e-03, 4.177145e-03, 3.546509e-03, 2.937873e-03, 2.354531e-03, 1.799440e-03, 1.275197e-03, 7.840226e-04, 3.277487e-04, -9.218992e-05, -4.747582e-04, -8.193195e-04, -1.125630e-03, -1.393826e-03, -1.624415e-03, -1.818251e-03, -1.976514e-03, -2.100690e-03, -2.192535e-03, -2.254048e-03, -2.287440e-03, -2.295096e-03, -2.279541e-03, -2.243403e-03, -2.189378e-03, -2.120191e-03, -2.038563e-03, -1.947175e-03, -1.848635e-03, -1.745447e-03, -1.639982e-03, -1.534453e-03, -1.430892e-03, -1.331128e-03, -1.236770e-03, -1.149197e-03, -1.069547e-03, -9.987087e-04, -9.373221e-04, -8.857786e-04, -8.442258e-04, -8.125758e-04, -7.905163e-04])


    data = pd.read_csv("test.csv")
    print("Read data: ", data)



    ts = data["timestamp_us"] * 1e-6
    x = data["mean_amp"]
    x_filt = lfilter(taps, [1.0], x)

    plt.figure("Raw and filtered data")
    plt.subplot(311)
    plt.plot(ts[len(taps):], x[len(taps):])
    plt.ylabel("raw data")

    plt.subplot(312)
    plt.plot(ts[len(taps):], x_filt[len(taps):])
    plt.ylabel("filtered data")

    with open("testdata.h", "wb") as f:
        f.write(("StaticFIRFilter<float, %d> testFilter({%s});\n" % (
            len(taps), ", ".join(["%e" % c for c in taps])
        )).encode("utf-8"))

        f.write(
            ("const float test_samples[] = {%s};\n" % ",".join(["%e" % s for s in data["mean_amp"]])).encode("utf-8")
        )

        f.write(
            ("const float test_output[] = {%s};" % ",".join(["%e" % s for s in x_filt[len(taps):]])).encode("utf-8")
        )


# process data using the same algorithm as C++ code

    x_filt2 = np.zeros(shape=(len(x)))
    for si in range(len(taps), len(x)):
        tmp = 0
        for ti in range(0, len(taps)):
            tap = taps[ti]
            tmp += x[si - ti] * taps[ti]
        x_filt2[si] = tmp

    plt.subplot(313)
    plt.plot(ts[len(taps):], x_filt2[len(taps):])
    plt.ylabel("filtered data2")
    plt.xlabel("timestamp(s)")
    plt.show()


