#include "vec3f.h"

namespace my {

    Vec3f::Vec3f(float a, float b, float c) : values_{a, b, c} {};

    const float& Vec3f::operator[] (int index) const {
        return values_[index];
    }

    float& Vec3f::operator[] (int index) {
        return values_[index];
    }

    bool Vec3f::operator== (const Vec3f& rhs) const{
        return this->values_ == rhs.values_;
    }

    bool Vec3f::operator!= (const Vec3f& rhs) const{
        return this->values_ != rhs.values_;
    }

    Vec3f& Vec3f::operator+= (const Vec3f& rhs) {
        this->values_[0] += rhs.values_[0];
        this->values_[1] += rhs.values_[1];
        this->values_[2] += rhs.values_[2];
        return *this;
    }

    Vec3f operator+ (Vec3f lhs, const Vec3f& rhs) {
        return lhs += rhs;
    }

    Vec3f Vec3f::operator- () const {
        return Vec3f(-values_[0], -values_[1], -values_[2]);
    }

    float dot(const Vec3f& lhs, const Vec3f& rhs) {
        return lhs[0]*rhs[0] +lhs[1]*rhs[1] +lhs[2]*rhs[2];
    }
}