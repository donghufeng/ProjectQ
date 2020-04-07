// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/complex.h>
#include <pybind11/stl.h>
#include <pybind11/pytypes.h>
#include <vector>
#include <complex>
#include <iostream>
#if defined(_OPENMP)
#include <omp.h>
#endif
#include "_cppkernels/simulator.hpp"

namespace py = pybind11;

using c_type = std::complex<double>;
using ArrayType = std::vector<c_type, aligned_allocator<c_type, 64>>;
using MatrixType = std::vector<ArrayType>;
using QuRegs = std::vector<std::vector<unsigned>>;

// template <class QR>
// void emulate_math_wrapper(Simulator &sim, py::function const &pyfunc, QR const &qr, std::vector<unsigned> const &ctrls)
// {
//     auto f = [&](std::vector<int> &x) {
//         pybind11::gil_scoped_acquire acquire;
//         x = std::move(pyfunc(x).cast<std::vector<int>>());
//     };
//     pybind11::gil_scoped_release release;
//     sim.emulate_math(f, qr, ctrls);
// }

PYBIND11_PLUGIN(_cppsim)
{
    py::module m("_cppsim", "_cppsim");
    py::class_<Simulator>(m, "Simulator")
        .def(py::init<unsigned, unsigned>())
        .def("test", &Simulator::test)
        .def("print_info", &Simulator::print_info)
        // .def("allocate_qubit", &Simulator::allocate_qubit)
        // .def("deallocate_qubit", &Simulator::deallocate_qubit)
        // .def("get_classical_value", &Simulator::get_classical_value)
        // .def("is_classical", &Simulator::is_classical)
        // .def("measure_qubits", &Simulator::measure_qubits_return)
        .def("apply_controlled_gate", &Simulator::apply_controlled_gate<MatrixType>)
        // .def("emulate_math", &emulate_math_wrapper<QuRegs>)
        // .def("emulate_math_addConstant", &Simulator::emulate_math_addConstant<QuRegs>)
        // .def("emulate_math_addConstantModN", &Simulator::emulate_math_addConstantModN<QuRegs>)
        // .def("emulate_math_multiplyByConstantModN", &Simulator::emulate_math_multiplyByConstantModN<QuRegs>)
        // .def("get_expectation_value", &Simulator::get_expectation_value)
        // .def("apply_qubit_operator", &Simulator::apply_qubit_operator)
        // .def("emulate_time_evolution", &Simulator::emulate_time_evolution)
        // .def("get_probability", &Simulator::get_probability)
        // .def("get_amplitude", &Simulator::get_amplitude)
        // .def("set_wavefunction", &Simulator::set_wavefunction)
        // .def("collapse_wavefunction", &Simulator::collapse_wavefunction)
        .def("run", &Simulator::run)
        // .def("cheat", &Simulator::cheat)
        // .def("test_speed", &Simulator::test_speed)
        ;
    return m.ptr();
}

// x86_64-linux-gnu-gcc -pthread -DNDEBUG -g -fwrapv -O2  -g -fstack-protector-strong -Wformat -Werror=format-security -Wdate-time -D_FORTIFY_SOURCE=2 -fPIC -I/usr/local/include/python3.6 -I/home/thuxuxs/.local/include/python3.6m -I/usr/include/python3.6m -c _cppsim.cpp -o _cppsim.o -fopenmp -DINTRIN -march=native -ffast-math -std=c++17 -fvisibility=hidden -DVERSION_INFO="0.5.0"

// x86_64-linux-gnu-g++ -pthread -shared -Wl,-O1 -Wl,-Bsymbolic-functions -Wl,-Bsymbolic-functions -Wl,-z,relro -Wl,-Bsymbolic-functions -Wl,-z,relro -g -fstack-protector-strong -Wformat -Werror=format-security -Wdate-time -D_FORTIFY_SOURCE=2 _cppsim.o -o _cppsim.cpython-36m-x86_64-linux-gnu.so -fopenmp

// g++ -O3 -fopenmp -shared -std=c++11 -fPIC `python3 -m pybind11 --include` _cppsim.cpp -o _cppsim`python3-config --extension-suffix`