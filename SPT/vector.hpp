//
// Created by karl on 28.02.21.
//

#ifndef __SPT_VECTOR_HPP__
#define __SPT_VECTOR_HPP__

#include <cstdint>
#include <memory>
#include <cstring>
//Debugging macro
//#define VEC_DEBUG

namespace spt {

    template<class T>
    class vector {
    public:
        using memorySize = uint64_t;
        using iterator = T *;
        using const_iterator = const T *;
        using reverse_iterator = std::reverse_iterator<iterator>;

    public:
        vector();

        explicit vector(uint32_t size);

        vector(uint32_t size, T data);

        vector(vector &&v) noexcept;

        vector(std::initializer_list<T> l);

        //Add element at the back
        void push_back(T data);

        //Remove element at the back
        void pop_back();

        void insert(memorySize index, T data);

        void resize(memorySize size);

        //Reverse memory
        void reserve(memorySize size);

        [[nodiscard]] memorySize capacity() const;

        [[nodiscard]] memorySize size() const;

        [[nodiscard]] memorySize max_size() const;

        iterator begin();

        iterator end();

        const_iterator cbegin() const;

        const_iterator cend() const;

        reverse_iterator rbegin();

        reverse_iterator rend();

        T *data() const;

        void clear();

        void shrink_to_fit();

        void erase(memorySize index);

        void erase(T *index);

        void erase(T *first, T *last);

        T &at(memorySize index) const;

        T &front() const;

        T &back() const;

        T &operator[](memorySize index) const;

        vector<T> &operator=(const vector &lhs);

        vector<T> &operator=(vector &&lhs) noexcept;

        bool operator==(const vector &rhs);

        bool operator!=(const vector &rhs) const;

        bool operator>(const vector &rhs) const;

        bool operator<=(const vector &rhs) const;

        bool operator>=(const vector &rhs) const;

        ~vector();

        bool operator<(const vector &rhs) const;

    private:
        T *m_data = nullptr;
        memorySize m_size;
        memorySize m_maxAlloc;
    };

    template<class T>
    vector<T>::vector() {
        m_size = 0;
        m_maxAlloc = 0;
        m_data = static_cast<T *>(std::calloc(0, sizeof(T)));
    }

    template<class T>
    vector<T>::vector(uint32_t size) {
        m_size = size;
        m_maxAlloc = size;
        m_data = static_cast<T *>(std::calloc(size, sizeof(T)));
    }

    template<class T>
    vector<T>::vector(uint32_t size, T data) {
        m_size = size;
        m_maxAlloc = size;
        m_data = static_cast<T *>(std::calloc(size, sizeof(T)));
        std::uninitialized_fill(m_data, m_data + m_size + sizeof(T), data);
    }

    template<class T>
    void vector<T>::push_back(T data) {
        m_size++;
        if (m_size > m_maxAlloc) {
            memorySize newSize = sizeof(T) * m_size * 2;
            m_data = static_cast<T *>(std::realloc(m_data, newSize));
            m_maxAlloc = newSize / sizeof(T);
            m_data[m_size - 1] = data;
#ifdef VEC_DEBUG
            std::cout << std::endl
                      << "\tMemory allocated: " << m_maxAlloc << std::endl
                      << "\tSize: " << m_length << std::endl;
#endif
        } else {
            m_data[m_size - 1] = data;
        }
    }

    template<class T>
    void vector<T>::pop_back() {
        m_size--;
    }

    template<class T>
    void vector<T>::insert(memorySize index, T data) {
        m_data[index] = data;
    }

    template<class T>
    void vector<T>::resize(vector<T>::memorySize size) {
        if (m_size < size) {
            memorySize newSize = sizeof(T) * m_size;
            m_data = static_cast<T *>(realloc(m_data, newSize));
            m_maxAlloc = newSize / sizeof(T);
        } else {
            shrink_to_fit();
        }
        m_size = size;
    }

    template<class T>
    typename vector<T>::memorySize vector<T>::capacity() const {
        return m_maxAlloc;
    }

    template<class T>
    typename vector<T>::memorySize vector<T>::size() const {
        return m_size;
    }

    template<class T>
    typename vector<T>::memorySize vector<T>::max_size() const {
        memorySize temp = 0;
        return ~temp;
    }

    template<class T>
    typename vector<T>::iterator vector<T>::begin() {
        return this->m_data;
    }

    template<class T>
    typename vector<T>::iterator vector<T>::end() {
        return this->m_data + m_size;
    }

    template<class T>
    T &vector<T>::at(memorySize index) const {
        if (index >= m_size) {
            //TODO Remove std::string
            std::string error("Index (");
            error += std::to_string(index);
            error += ") is <= than this->size() (";
            error += std::to_string(this->size());
            error += ')';
            throw std::out_of_range(error);
        }
        return m_data[index];
    }

    template<class T>
    T &vector<T>::front() const {
        return m_data[0];
    }

    template<class T>
    T &vector<T>::back() const {
        return m_data[m_size - 1];
    }

    template<class T>
    T &vector<T>::operator[](memorySize index) const {
        return m_data[index];
    }

    template<class T>
    vector<T>::~vector() {
        free(m_data);
    }

    template<class T>
    T *vector<T>::data() const {
        return m_data;
    }

    template<class T>
    void vector<T>::clear() {
        m_size = 0;
    }

    template<class T>
    void vector<T>::shrink_to_fit() {
        if (m_size != m_maxAlloc) {
            m_data = static_cast<T *>(std::realloc(m_data, sizeof(T) * m_size));
            m_maxAlloc = m_size;
        }
    }

    template<class T>
    vector<T> &vector<T>::operator=(const vector &lhs) {
        //Handle self assigment
        if (this == &lhs)
            return *this;
        this->m_size = lhs.m_size;
        if (this->m_maxAlloc < lhs.m_maxAlloc) {
            this->m_maxAlloc = lhs.m_maxAlloc;
            this->m_data = static_cast<T *>(std::realloc(this->m_data, sizeof(T) * this->m_size));
        }
        std::memcpy(this->m_data, lhs.m_data, this->m_size);
        return *this;
    }

    template<class T>
    void vector<T>::erase(T *index) {
        for (auto i = this->begin() + *index; i < this->end(); ++i) {
            m_data[*i] = m_data[*i + 1];
        }
        --m_size;
    }

    template<class T>
    void vector<T>::erase(T *first, T *last) {
        /*for (auto i = this->begin() + *first; i < this->cbegin() + *last; ++i) {
            m_data[*i] = m_data[*i + 1];
        }
         */
        int i = 0;
        for (; last != this->end(); ++first, ++last, ++i) {
            *first = std::move(*last);
        }
        m_size -= i + 1;

    }

    template<class T>
    vector<T>::vector(vector &&v) noexcept {
        this->m_size = v.m_size;
        this->m_maxAlloc = v.m_maxAlloc;
        this->m_data = v.m_data;
        v.m_data = nullptr;
    }

    template<class T>
    vector<T> &vector<T>::operator=(vector &&lhs) noexcept {
        this->m_size = lhs.m_size;
        this->m_maxAlloc = lhs.m_maxAlloc;
        this->m_data = lhs.m_data;
        lhs.m_data = nullptr;
        return *this;
    }

    template<class T>
    bool vector<T>::operator==(const vector &rhs) {
        iterator first = this->begin();
        iterator last = this->end();
        const_iterator second = rhs.cbegin();
        while (first != last) {
            if (*first != *second)
                return false;
            ++first;
            ++second;
        }
        return true;
    }

    template<class T>
    bool vector<T>::operator!=(const vector &rhs) const {
        return rhs != *this;
    }

    template<class T>
    bool vector<T>::operator<(const vector &rhs) const {
        return m_size < rhs.m_size;
    }

    template<class T>
    bool vector<T>::operator>(const vector &rhs) const {
        return rhs < *this;
    }

    template<class T>
    bool vector<T>::operator<=(const vector &rhs) const {
        return !(rhs < *this);
    }

    template<class T>
    bool vector<T>::operator>=(const vector &rhs) const {
        return !(*this < rhs);
    }

    template<class T>
    typename vector<T>::reverse_iterator vector<T>::rbegin() {
        return std::make_reverse_iterator(end());
    }

    template<class T>
    typename vector<T>::reverse_iterator vector<T>::rend() {
        return std::make_reverse_iterator(begin());
    }

    template<class T>
    vector<T>::vector(std::initializer_list<T> l)
            :m_size(0), m_maxAlloc(0) {
        resize(l.size());
        std::copy(l.begin(), l.end(), this->begin());
    }

    template<class T>
    void vector<T>::reserve(vector<T>::memorySize size) {
        if (m_maxAlloc < size) {
            m_maxAlloc = size;
            m_data = static_cast<T *>(std::realloc(m_data, size * sizeof(T)));
        }
    }

    template<class T>
    typename vector<T>::const_iterator vector<T>::cbegin() const {
        return this->m_data;
    }

    template<class T>
    typename vector<T>::const_iterator vector<T>::cend() const {
        return this->m_data + this->m_size;
    }

    template<class T>
    void vector<T>::erase(vector::memorySize index) {
        for (auto i = this->begin() + index; i != this->end(); ++i) {
            //m_data[*i] = m_data[*i + 1];
            *i = *(i + 1);
        }
        --m_size;
    }

} // namespace spt

#endif //__SPT_VECTOR_HPP__
