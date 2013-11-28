#if !defined(UTILS_HPP)
#define UTILS_HPP

#include <stdexcept>

namespace cg
{

namespace utils
{
    template <typename T>
    T clamp(T value, T max, T min)
    {
        if(value > max) return max;
        else if(value < min) return min;
        else return value;
    }

    template <typename T>
    T mix(T a, T b, T bias)
    {
        T complement = 1 - bias;

        a = a * bias;
        b = b * complement;

        return a + b;
    }

    template <typename T>
    T fit(T value, T oldmin, T oldmax, T newmin, T newmax)
    {
        T bias;

        bias = clamp((value - oldmin)/(oldmax - oldmin), 0.0, 1.0);
        return mix(newmin, newmax, bias);
    }
} // end namespace utils

} // end namespace cg

#endif // end include guard
