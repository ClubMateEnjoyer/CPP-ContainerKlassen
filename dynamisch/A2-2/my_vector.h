#pragma once
#include <cstddef>
#include <stdexcept>
#include <cstdlib>
#include <new>
#include <utility>

namespace my {

    template <typename ValueT>
    class vector {
    private:
        size_t size_;
        size_t capacity_;
        ValueT* data_;

    public:

        bool empty() const {
            return size_ == 0;
        }

        size_t size() const {
            return size_;
        }

        size_t capacity() const {
            return capacity_;
        }

        /**
         * n = 0 als standard wert
         * ValueT als standard wert (zb. 0 bei int)
         * anders als bei 2.1: hier alles auf null setzen 
         */
        vector(size_t n = 0, const ValueT& val = ValueT{}) : size_(0), capacity_(0), data_(nullptr) {
            
            // malloc von 0 unsicher, deswegen prüfen
            if(n > 0) {
                // speicher holen, in bytes
                auto memory = std::malloc(n * sizeof(ValueT));
                if(!memory) {
                    throw std::bad_alloc();
                }

                data_ = static_cast<ValueT*>(memory);
                capacity_ = n;
                
                // mit placement new den speicher belegen
                for (size_t i = 0; i < n; ++i) {
                    new (data_ + i) ValueT(val);
                }
                size_ = n;
            }
        }

        void clear() {
            // alle existierenden objecte destructen
            for (size_t i = 0; i < size_; ++i) {
                data_[i].~ValueT();
            }
            // size ist jetzt 0, capacity bleibt aber gleich
            size_ = 0;
        }

        ~vector() {
            clear();
            std::free(data_);
        };

        void reserve(size_t new_capacity) {
            if(new_capacity <= capacity_) {
                return;
            }

            //neuen speicher holen
            auto memory = std::malloc(new_capacity * sizeof(ValueT));
            if(!memory) {
                throw std::bad_alloc();
            }

            ValueT* new_data = static_cast<ValueT*>(memory);

            // alte elemente mitnehmen
            for (size_t i = 0; i < size_; ++i) {
                new (new_data + i) ValueT(std::move(data_[i]));
                data_[i].~ValueT();
            }

            // alten speicher freigeben
            std::free(data_);

            data_ = new_data;
            capacity_ = new_capacity;
        }

        void push_back(const ValueT& val) {
            
            if(size_ == capacity_) {
                size_t new_capacity;
                if(capacity_ == 0) {
                    new_capacity = 1;
                } else {
                    new_capacity = capacity_ * 2;
                }
                reserve(new_capacity);
            }

            new(data_ + size_) ValueT(val);

            ++size_;
        }


        ValueT pop_back() {

            if(size_ == 0) {
                throw std::out_of_range("Vector ist leer...");
            }

            ValueT returnVal = std::move(data_[size_ - 1]);

            data_[size_ - 1].~ValueT();

            --size_;

            return returnVal;
        }

        void shrink_to_fit() {
            if(capacity_ == size_) {
                return;
            }

            if(size_ == 0) {
                std::free(data_);
                data_ = nullptr;
                capacity_ = 0;
                return;
            }

            auto memory = std::malloc(size_ * sizeof(ValueT));
            if(!memory) {
                throw std::bad_alloc();
            }

            ValueT* new_data = static_cast<ValueT*>(memory);

            for (size_t i = 0; i < size_; ++i) {
                new (new_data + i) ValueT(std::move(data_[i]));
                data_[i].~ValueT();
            }

            std::free(data_);
            data_ = new_data;
            capacity_ = size_;
        }

        ValueT& operator[](size_t i) {
            return data_[i];
        }

        const ValueT& operator[](size_t i) const{
            return data_[i];
        }

        ValueT& at(size_t i) {
            if(i >= size_) {
                throw std::out_of_range("Index out of range...");
            }
            return data_[i];
        }

        const ValueT& at(size_t i) const {
            if(i >= size_) {
                throw std::out_of_range("Index out of range...");
            }
            return data_[i];
        }

        // rule of 5

        vector(const vector& rhs) : size_(0), capacity_(0), data_(nullptr) {
            reserve(rhs.capacity_); 
            for (size_t i = 0; i < rhs.size_; ++i) {
                new (data_ + i) ValueT(rhs.data_[i]);
            }
            size_ = rhs.size_;            
        }

        vector(vector&& rhs) : size_(0), capacity_(0), data_(nullptr) {
            swap(*this, rhs);
        }

        vector& operator=(vector rhs) {
            swap(*this, rhs);
            return *this;
        }

        friend void swap(vector& lhs, vector& rhs) {
            std::swap(lhs.size_, rhs.size_);
            std::swap(lhs.capacity_, rhs.capacity_);
            std::swap(lhs.data_, rhs.data_);
        }
    };
}