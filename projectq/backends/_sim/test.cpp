#include "./_cppkernels/simulator.hpp"
using c_type = std::complex<double>;
using ArrayType = std::vector<c_type, aligned_allocator<c_type, 64>>;
using MatrixType = std::vector<ArrayType>;
using QuRegs = std::vector<std::vector<unsigned>>;
using Indexs = std::vector<unsigned>;
int main()
{
    unsigned n = 2;
    Simulator s = Simulator(1, n);
    MatrixType m = {{{0, 0}, {1, 0}}, {{1, 0}, {0, 0}}};
    Indexs ids = {0};
    Indexs ctrl = {};

    // s.test(0, m, 0, 1 << 2);
    s.apply_controlled_gate(m, ids, ctrl);
    s.run();
    s.print_info();
}
// g++ -fopenmp -std = c++ 17 -DINTRIN -march=native test.cpp