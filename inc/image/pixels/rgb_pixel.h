#pragma once


template<typename T>
struct RGBPixel {
    T red;
    T green;
    T blue;

    RGBPixel<T> operator-(const RGBPixel<T>& other) {
        return RGBPixel<T> {
                static_cast<T>(red - other.red),
                static_cast<T>(green - other.green),
                static_cast<T>(blue - other.blue)
        };
    }

    RGBPixel<T> operator+(const RGBPixel<T>& other) {
        return RGBPixel<T> {
                static_cast<T>(red + other.red),
                static_cast<T>(green + other.green),
                static_cast<T>(blue + other.blue)
        };
    }

    RGBPixel<T> operator*(const double& d) {
        return RGBPixel<T> {
                static_cast<T>(red * d),
                static_cast<T>(green * d),
                static_cast<T>(blue * d)
        };
    }
};
