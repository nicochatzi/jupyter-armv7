#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <arm_neon.h>
#include <array>
#include <cstdint>
#include <cmath>

namespace py = pybind11;

// std::array<int32_t, 4> add_quad(const std::array<int32_t, 4>& a, const std::array<int32_t, 4>& b) {
//     int32x4_t const qa = vld1q_s32(a.data());
//     int32x4_t const qb = vld1q_s32(b.data());
//     int32x4_t const r  = vaddq_s32(qa, qb);
//     return { r[0], r[1], r[2], r[3] };
// }

struct Complex {
    float real = 0.f, imag = 0.f;

    Complex operator*=(const Complex& rhs) {
        return (*this = {
            .real = real * rhs.real - imag * rhs.imag,
            .imag = real * rhs.imag + imag * rhs.real,
        });
    }
};

struct MagicCircle {
    Complex value = {1.f, 0.f}, mult = {0.f, 0.f};

    void reset()    { *this = MagicCircle{}; }
    void set_freq(float f, float sample_rate) {
        auto const phase = 2.f * M_PI * f * (1.f / sample_rate);
        mult.real = std::cos(phase);
        mult.imag = std::sin(phase);
    }

    float advance() { return (value *= mult).imag; }
};

struct Distortion {
    float gain = 0.5;

    void set_gain(float gain) { this->gain = gain; }

    float process(float x) {
        x *= gain;
        auto const x_2 = x * x;
        auto const y   = x * (27 + x_2) / (27 + 9 * x_2);
        return y > 1. ? 1. : y < -1. ? -1 : y;
    }
};

PYBIND11_MODULE(_core, m) {
    m.doc() = "pybind11 example plugin";

    m.def("add", [](int i, int j) { return i + j; }, "A function that adds two numbers");
    // m.def("add_quad", &add_quad, "A function that adds two arrays of 4 numbers");

    py::class_<MagicCircle>(m, "MagicCircle")
        .def(py::init<>())
        .def("reset", &MagicCircle::reset)
        .def("set_freq", &MagicCircle::set_freq,
             py::arg("f") = 440.f, py::arg("sample_rate") = 48'000.f)
        .def("advance", &MagicCircle::advance);

    py::class_<Distortion>(m, "Distortion")
        .def(py::init<>())
        .def("set_gain", &Distortion::set_gain, py::arg("gain") = 1.f)
        .def("process", &Distortion::process);
}