#pragma once

#include <concepts>
#include <array>
#include <type_traits>

namespace my {

    template<typename T, int N>
    requires std::is_arithmetic_v<T>
    class Vec {

    public:

        // konstruktor mit 0 als automatischen wert ("Default Constructor")
        Vec() : values_{} {};

        // konstruktor
        template<typename... Ts>
        Vec(Ts... args) : values_{static_cast<T>(args) ...} {
            static_assert(sizeof...(args) == N, "Falsche Anzahl an uebergebenen Werten...");
        };

        // nur lesen (kopie)
        const T& operator[] (int index) const;

        // schreiben (referenz)
        T& operator[] (int index);

        // gleich
        bool operator== (const Vec& rhs) const;

        // ungleich
        bool operator!= (const Vec& rhs) const;

        // inline +=
        Vec& operator+= (const Vec& rhs);

        Vec operator- () const;

    private:
        std::array<T, N> values_;

    };

    /*
     *   Implentierungen
    */

    template<typename T, int N>
    requires std::is_arithmetic_v<T>
    const T& Vec<T,N>::operator[] (int index) const {
        return values_[index];
    }

    template<typename T, int N>
    requires std::is_arithmetic_v<T>
    T& Vec<T,N>::operator[] (int index) {
        return values_[index];
    }

    template<typename T, int N>
    requires std::is_arithmetic_v<T>
    bool Vec<T,N>::operator== (const Vec& rhs) const{
        return this->values_ == rhs.values_;
    }

    template<typename T, int N>
    requires std::is_arithmetic_v<T>
    bool Vec<T,N>::operator!= (const Vec& rhs) const{
        return this->values_ != rhs.values_;
    }

    template<typename T, int N>
    requires std::is_arithmetic_v<T>
    Vec<T,N>& Vec<T,N>::operator+= (const Vec& rhs) {
        for (int i = 0; i < N; ++i)
        {
            this->values_[i] += rhs.values_[i];
        }
        
        return *this;
    }

    template<typename T, int N>
    requires std::is_arithmetic_v<T>
    Vec<T,N> operator+ (Vec<T,N> lhs, const Vec<T,N>& rhs) {
        return lhs += rhs;
    }

    template<typename T, int N>
    requires std::is_arithmetic_v<T>
    Vec<T,N> Vec<T,N>::operator- () const {
        Vec<T,N> result{};
        for (int i = 0; i < N; ++i)
        {
            result.values_[i] = -(this->values_[i]);
        }
        return result;
    }

    template<typename T, int N>
    requires std::is_arithmetic_v<T>
    T dot(const Vec<T,N>& lhs, const Vec<T,N>& rhs) {

        T result{};
        for (int i = 0; i < N; ++i)
        {
            result += (lhs[i]*rhs[i]);
        }
        
        return result;
    }

}