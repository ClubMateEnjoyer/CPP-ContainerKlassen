#pragma once
#include <cstddef>
#include <stdexcept>

namespace my {

    template <typename ValueT>
    class vector {
    private:
        size_t size_;
        ValueT* data_;

    public:

        bool empty() const {
            return size_ == 0;
        }

        size_t size() const {
            return size_;
        }

        /**
         * n = 0 als standard wert
         * ValueT als standard wert (zb. 0 bei int)
         */
        vector(size_t n = 0, const ValueT& val = ValueT{}) : size_(n), data_(nullptr) {
            
            if(size_ > 0) {
                // speicher auf dem heap reservieren
                data_ = new ValueT[size_];

                // speicher mit val füllen
                for(size_t i = 0; i < size_; ++i) {
                    data_[i] = val;
                }
            }
        }

        void clear() {
            delete[] data_;
            data_ = nullptr;
            size_ = 0;
        }

        ~vector() {
            clear();
        };

        void push_back(const ValueT& val) {
            //alte daten sichern
            ValueT* old_data = data_;
          
            // neuen platz reservieren
            data_ = new ValueT[size_ + 1];

            //alten stand kopieren
            for(size_t i = 0; i < size_; ++i) {
                data_[i] = old_data[i];
            }

            //neues element anheften
            data_[size_] = val;

            //größe erhöhen
            ++size_;

            // altes array löschen
            delete[] old_data;
        }


        ValueT pop_back() {

            // letzten wert sichern
            ValueT returnVal = data_[size_ - 1];

            // falls vector jetzt leer, aufräumen
            if(size_ == 1) {
                clear();
                return returnVal;
            }

            // alte daten sichern
            ValueT* old_data = data_;

            // array um 1 verkleinern
            data_ = new ValueT[size_ - 1];


            for(size_t i = 0; i < size_ - 1; ++i) {
                data_[i] = old_data[i];
            }

            delete[] old_data;
            --size_;

            return returnVal;
        }

        ValueT& operator[](size_t i) {
            return data_[i];
        }

        const ValueT& operator[](size_t i) const {
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

        vector(vector<ValueT> const &) = delete;
        vector<ValueT>& operator=(vector<ValueT> const &) = delete;

    };
}