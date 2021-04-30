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

namespace spt1 {

    template<class T>
    class vector {
    private:
        using memorySize = uint64_t;

    public:
        vector();

        explicit vector(uint32_t size);

        vector(uint32_t size, T data);

        vector(vector &&v);

        void push_back(T data);

        void pop_back();

        void insert(memorySize index, T data);

        void resize(memorySize size);

        memorySize capacity() const;

        memorySize size() const;

        memorySize max_size() const;

        T *begin() const;

        T *end() const;

        T *data() const;

        void clear();

        void shrink_to_fit();

        void erase(T *index);

        void erase(T *first, T *last);

        T &at(memorySize index) const;

        T &front() const;

        T &back() const;

        T &operator[](memorySize index) const;

        vector<T> &operator=(const vector &lhs);

        vector<T> &operator=(vector &&lhs) noexcept;

        bool operator==(const vector &rhs) const;

        bool operator!=(const vector &rhs) const;

                bool operator>(const vector &rhs) const;

        bool operator<=(const vector &rhs) const;

        bool operator>=(const vector &rhs) const;

        ~vector();

        bool operator<(const vector &rhs) const;

    private:
        T *m_data;
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
        memorySize oldSize = m_size;
        m_size = size;
        if (oldSize < m_size) {
            memorySize newSize = sizeof(T) * m_size;
            m_data = static_cast<T *>(realloc(m_data, newSize));
            m_maxAlloc = newSize / sizeof(T);
        }
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
    T *vector<T>::begin() const {
        return this->m_data;
    }

    template<class T>
    T *vector<T>::end() const {
        return this->m_data + m_size;
    }

    template<class T>
    T &vector<T>::at(memorySize index) const {
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
        m_data = static_cast<T *>(std::realloc(m_data, sizeof(T) * m_size));
        m_maxAlloc = m_size;
    }

    template<class T>
    vector<T> &vector<T>::operator=(const vector &lhs) {
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
        /*for (auto i = this->begin() + *first; i < this->begin() + *last; ++i) {
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
    vector<T>::vector(vector &&v) {
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
    bool vector<T>::operator==(const vector &rhs) const {
        T *first = this->begin();
        T *last = this->end();
        T *second = rhs.begin();
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

} // namespace spt1

namespace spt2 {
    template<class T>
    class allocator {

    };

    template<class T, class alloc = allocator<T>>
    class vector {
    private:
        using sizeType_t = uint64_t;

        std::unique_ptr<T[]> m_dataContainer{nullptr};
        sizeType_t m_dataSize{};
        //Allocated space is counted as (Allocated bytes / sizeof(T))
        sizeType_t m_allocated{};
    public:
        vector();

        vector<T, alloc> &push_back(T data);
    };

    template<class T, class alloc>
    vector<T, alloc> &vector<T, alloc>::push_back(T data) {
        ++m_dataSize;
        if (m_dataSize > m_allocated) {
            //Use allocator to allocate memory
        }

        return *this;
    }

    template<class T, class alloc>
    vector<T, alloc>::vector() = default;

}

#endif //__SPT_VECTOR_HPP__
