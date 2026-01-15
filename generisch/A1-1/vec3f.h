#pragma once

#include <array>

namespace my {

    class Vec3f {

    public:
        
        // konstruktor (0 als standardwert)
        Vec3f(float a = 0, float b = 0, float c = 0);

        // nur lesen (kopie)
        const float& operator[] (int index) const;

        // schreiben (referenz)
        float& operator[] (int index);

        // gleich
        bool operator== (const Vec3f& rhs) const;

        // ungleich
        bool operator!= (const Vec3f& rhs) const;

        // inline +=
        Vec3f& operator+= (const Vec3f& rhs);

        Vec3f operator- () const;

    private:
        std::array<float, 3> values_;

    };

    // 2 vektoren, einer als kopie den ich auch wieder zurückgebe
    // ein vektor, der nur gelesen wird und deswegen als referenz
    Vec3f operator+ (Vec3f lhs, const Vec3f& rhs);

    // skalarprodukt
    float dot(const Vec3f& lhs, const Vec3f& rhs);
}