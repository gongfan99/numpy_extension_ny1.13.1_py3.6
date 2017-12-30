import numpy as np
import mylib

mul = 3
aaa = np.random.rand(3, 2)
bbb = mylib.example(aaa, multiplier=mul)

print("\ntest.py: ", aaa)
print("\ntest.py: ", bbb)

np.testing.assert_array_equal(aaa * mul, bbb)