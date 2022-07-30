#pragma once

#include <cmath>

template<typename T>
struct RGBPixel {
    T red;
    T green;
    T blue;

    RGBPixel<T> operator-(const RGBPixel<T>& other) const {
        return RGBPixel<T> {
            static_cast<T>(red - other.red),
            static_cast<T>(green - other.green),
            static_cast<T>(blue - other.blue)
        };
    }

    RGBPixel<T> operator+(const RGBPixel<T>& other) const {
        return RGBPixel<T> {
            static_cast<T>(red + other.red),
            static_cast<T>(green + other.green),
            static_cast<T>(blue + other.blue)
        };
    }

    RGBPixel<T> operator*(const double& d) const {
        return RGBPixel<T> {
            static_cast<T>(red * d),
            static_cast<T>(green * d),
            static_cast<T>(blue * d)
        };
    }

    explicit operator RGBPixel<int>() const {
        return RGBPixel<int> {
            static_cast<int>(red),
            static_cast<int>(green),
            static_cast<int>(blue)
        };
    }

};

template<typename T>
static RGBPixel<T> pow(const RGBPixel<T>& base, const double& exp) {
    return RGBPixel<T> {
        static_cast<T>(std::pow(base.red, exp)),
        static_cast<T>(std::pow(base.green, exp)),
        static_cast<T>(std::pow(base.blue, exp))
    };
}
