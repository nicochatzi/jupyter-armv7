#pragma once

#include <cstdint>
#include <cmath>

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
    float advance() { return (value *= mult).imag; }
    void set_freq(float f, float sample_rate) {
        auto const phase = 2.f * M_PI * f * (1.f / sample_rate);
        mult.real = std::cos(phase);
        mult.imag = std::sin(phase);
    }
};
