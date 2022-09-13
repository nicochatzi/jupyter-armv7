#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <arm_neon.h>
#include <array>
#include <cstdint>
#include <MagicCircle.h>

namespace py = pybind11;

// std::array<int32_t, 4> add_quad(const std::array<int32_t, 4>& a, const std::array<int32_t, 4>& b) {
//     int32x4_t const qa = vld1q_s32(a.data());
//     int32x4_t const qb = vld1q_s32(b.data());
//     int32x4_t const r  = vaddq_s32(qa, qb);
//     return { r[0], r[1], r[2], r[3] };
// }

PYBIND11_MODULE(_core, m) {
    m.doc() = "pybind11 example plugin";

    m.def("add", [](int i, int j) { return i + j; }, "A function that adds two numbers");
    // m.def("add_quad", &add_quad, "A function that adds two arrays of 4 numbers");

    py::class_<MagicCircle>(m, "MagicCircle")
        .def(py::init<>())
        .def("reset", &MagicCircle::reset)
        .def("set_freq", &MagicCircle::set_freq)
        .def("advance", &MagicCircle::advance);
}