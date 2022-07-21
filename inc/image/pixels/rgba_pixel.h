#pragma once

template<typename T>
struct RGBAPixel {
    T red;
    T green;
    T blue;
    T alpha;

    RGBAPixel<T> operator-(const RGBAPixel<T>& other) {
        return RGBAPixel<T> {
                static_cast<T>(red - other.red),
                static_cast<T>(green - other.green),
                static_cast<T>(blue - other.blue)},
                static_cast<T>(alpha - other.alpha)
    }
};