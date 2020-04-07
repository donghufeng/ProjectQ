import _cppsim
import numpy as np
import time

x = np.array([[0, 1], [1, 0]])
h = np.array([[1, 1], [1, -1]]) / np.sqrt(2)

n = 26
t0 = time.time()
s = _cppsim.Simulator(3, n)
# s.print_info()
# s.test(0, x, 0, 1 << n)
# for i in range(n):
#     s.allocate_qubit(i)

t1 = time.time()
s.apply_controlled_gate(x, [0], [])
for i in range(n):
    s.apply_controlled_gate(h, [i], [])
s.apply_controlled_gate(x, [n - 1], [])
s.run()
# # s.test_speed()

t2 = time.time()
print(t1-t0, t2-t1)
# print(s.cheat()[1][:8])
s.print_info()
