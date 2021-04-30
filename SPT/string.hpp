//
// Created by karl on 28.02.21.
//

#ifndef SPT_STRING_HPP
#define SPT_STRING_HPP

#include <cstring>
#include <ios>
#include <ostream>
#include <any>
#include "vector.hpp"

namespace spt1 {

    template<class T>
    class basic_string {
    public:
        basic_string();

        explicit basic_string(const T *str);

        basic_string(const basic_string &str);

        basic_string(basic_string &&str);

        static void strcpy(T *dest, T *src);

        const T *c_string() const;

        void erase(int64_t pos, int64_t n);

        T *begin() const;

        T *end() const;

        basic_string &operator=(const basic_string &str);

        T &operator[](uint64_t index) const;

        bool operator<(const basic_string &rhs) const;

        bool operator>(const basic_string &rhs) const;

        bool operator<=(const basic_string &rhs) const;

        bool operator>=(const basic_string &rhs) const;

        bool operator==(const basic_string &rhs) const;

        bool operator!=(const basic_string &rhs) const;

        template<class U>
        friend std::ostream &operator<<(std::ostream &os, const basic_string<U> &string);

    private:
        static uint64_t strlen(const char *str);

    private:
        spt1::vector<T> m_string;
        uint64_t m_length;
    };

    template<class T>
    basic_string<T>::basic_string() :
            m_length(0) {}

    template<class T>
    basic_string<T>::basic_string(const basic_string<T> &str) {
        this->m_length = str.m_length;
        this->m_string = str.m_string;
        if (this->m_string.size() > this->m_string.capacity()) {
            this->m_string[this->m_string.size() + 1] = '\0';
        } else {
            this->m_string.push_back('\0');
        }
    }

    template<class T>
    basic_string<T>::basic_string(const T *str)
            : m_string(0), m_length(strlen(str)) {
        m_string.resize(m_length);
        //std::memcpy(m_string.data(), str, m_length);
        strcpy(m_string.data(), const_cast<T *>(str));
    }

    template<class T>
    basic_string<T>::basic_string(basic_string &&str) {
        this->m_length = str.m_length;
        this->m_string = std::move(str.m_string);
        str.m_string.clear();
        str.m_string.shrink_to_fit();
    }

    template<class T>
    uint64_t basic_string<T>::strlen(const char *str) {
        const char *begin = str;
        while (*str)
            ++str;
        return str - begin;
    }

    template<class U>
    std::ostream &operator<<(std::ostream &os, const spt1::basic_string<U> &string) {
        os << string.m_string.data();
        return os;
    }

    template<class T>
    basic_string<T> &basic_string<T>::operator=(const basic_string &str) {
        this->m_length = str.m_length;
        this->m_string = str.m_string;
        if (this->m_string.size() > this->m_string.capacity()) {
            this->m_string[this->m_string.size() + 1] = '\0';
        } else {
            this->m_string.push_back('\0');
        }
        return *this;
    }

    template<class T>
    const T *basic_string<T>::c_string() const {
        return m_string.data();
    }

    template<class T>
    T &basic_string<T>::operator[](uint64_t index) const {
        return m_string[index];
    }


    template<class T>
    void basic_string<T>::erase(int64_t pos, int64_t n) {
        m_string.erase(m_string.begin() + pos, m_string.begin() + pos + n);
        m_length -= n;
        m_string[m_length] = '\0';
    }

    template<class T>
    T *basic_string<T>::begin() const {
        return m_string.data();
    }

    template<class T>
    T *basic_string<T>::end() const {
        return m_string.data() + m_length;
    }

    template<class T>
    bool basic_string<T>::operator==(const basic_string &rhs) const {
        return this->m_string == rhs.m_string;
    }

    template<class T>
    bool basic_string<T>::operator!=(const basic_string &rhs) const {
        return !(rhs == *this);
    }

    template<class T>
    bool basic_string<T>::operator<(const basic_string &rhs) const {
        if (m_string < rhs.m_string)
            return true;
        if (rhs.m_string < m_string)
            return false;
        return m_length < rhs.m_length;
    }

    template<class T>
    bool basic_string<T>::operator>(const basic_string &rhs) const {
        return rhs < *this;
    }

    template<class T>
    bool basic_string<T>::operator<=(const basic_string &rhs) const {
        return !(rhs < *this);
    }

    template<class T>
    bool basic_string<T>::operator>=(const basic_string &rhs) const {
        return !(*this < rhs);
    }

    template<class T>
    void basic_string<T>::strcpy(T *dest, T *src) {
        auto cdest = dest;
        auto csrc = src;
        while (*csrc) {
            *cdest = *csrc;
            ++cdest;
            ++csrc;
        }
    }

} //namespace spt1

#endif //SPT_STRING_HPP
