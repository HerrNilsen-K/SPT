//
// Created by karl on 28.02.21.
//

#ifndef __SPT_VECTOR_HPP__
#define __SPT_VECTOR_HPP__

#include <cstdint>
#include <memory>
//Debugging macro
//#define VEC_DEBUG

namespace spt {

    template<class T>
    class vector {
    private:
        using memorySize = uint64_t;

    public:
        vector();

        vector(uint32_t size);

        vector(uint32_t size, T data);

        void push_back(T data);

        void pop_back();

        void insert(memorySize index, T data);

        void resize(memorySize size);

        memorySize capacity() const;

        memorySize size() const;

        memorySize max_size() const;

        T *begin() const;

        T *end() const;

        T &at(memorySize index) const;

        T &front() const;

        T &back() const;

        T &operator[](memorySize index) const;

        ~vector();

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
                      << "\tSize: " << m_size << std::endl;
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

} // namespace spt

#endif //SPT_VECTOR_HPP
