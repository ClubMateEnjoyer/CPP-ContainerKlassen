#pragma once

#include <iostream>
#include <concepts>
#include <array>
#include <type_traits>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <string>

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

        auto begin() { return values_.begin(); }
        auto begin() const { return values_.begin(); }
        auto end() { return values_.end(); }
        auto end() const { return values_.end(); }
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

        T length() const;

        int size() const { return N; }

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
        
        auto add = [](T a, T b){ return a + b; };
        std::transform(
            this->values_.begin(), 
            this->values_.end(), 
            rhs.values_.begin(), 
            this->values_.begin(),
            add
        );
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

        auto negate = [](T a){ return -a; };
        std::transform(
            this->values_.begin(), 
            this->values_.end(), 
            result.values_.begin(), 
            negate
        );
        return result;
    }

    template<typename T, int N>
    requires std::is_arithmetic_v<T>
    T dot(const Vec<T,N>& lhs, const Vec<T,N>& rhs) {

        T result = std::inner_product(
            lhs.begin(),
            lhs.end(),
            rhs.begin(),
            T{}
        );
        
        return result;
    }

    template<typename T, int N>
    requires std::is_arithmetic_v<T>
    T Vec<T,N>::length() const{
        return std::sqrt(dot(*this, *this));
    }

    // size() methode benötigt
    template<typename Container>
    void printVec(const Container& container) {

        for(const auto& vec : container) {
            std::cout << "(";
            for (int i = 0; i < vec.size(); ++i)
            {
                std::cout << vec[i];
                if(i == vec.size()-1) {
                    break;
                }
                std::cout << ", ";
            }
            std::cout << ")";

            std::cout << ", Length: " << vec.length() << std::endl;
        }
    }

}