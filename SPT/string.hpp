//
// Created by karl on 28.02.21.
//

/*
 * TODO
 *  ADD:
 *      find()
 *      toString()
 *      replace()
 *      toUpper/Lower
 *      check for primitive type in template
 *  REFACTOR:
 */

#ifndef SPT_STRING_HPP
#define SPT_STRING_HPP

#include <cstring>
#include <ios>
#include <ostream>
#include <any>
#include <sstream>
#include "vector.hpp"

namespace spt {
    template<class T>
    class basic_string;

    using string = basic_string<char>;

    void strcat(char *dest, const char *src);

    void strcat(char *dest, const char src);

    uint64_t strlen(const char *str);

    basic_string<char> toString(short num);

    basic_string<char> toString(int num);

    basic_string<char> toString(long num);

    basic_string<char> toString(long long num);

    basic_string<char> toString(float num);

    basic_string<char> toString(double num);

    basic_string<char> toString(long double num);

    void strcpy(char *dest, const char *src);


    template<class T>
    class basic_string {
    public:
        using iterator = T *;
        using const_iterator = const T *;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<reverse_iterator>;
        using memorySize = typename spt::vector<T>::memorySize;

    public:
        basic_string();

        explicit basic_string(const T *str);

        basic_string(const basic_string &str);

        basic_string(basic_string &&str) noexcept;

        const T *c_string() const;

        void erase(memorySize pos, memorySize n);

        void reserve(memorySize n);

        iterator begin();

        iterator end();

        const_iterator cbegin() const;

        const_iterator cend() const;

        reverse_iterator rbegin();

        reverse_iterator rend();

        basic_string operator+(const basic_string &str);

        basic_string operator+(const char *str);

        basic_string operator+(char str);

        basic_string &operator+=(const basic_string &str);

        basic_string &operator+=(const char *str);

        basic_string &operator+=(char str);

        basic_string &operator=(const basic_string &str);

        T &operator[](memorySize index) const;

        T &at(memorySize index) const;

        [[nodiscard]] bool operator<(const basic_string &rhs) const;

        [[nodiscard]] bool operator>(const basic_string &rhs) const;

        [[nodiscard]] bool operator<=(const basic_string &rhs) const;

        [[nodiscard]] bool operator>=(const basic_string &rhs) const;

        [[nodiscard]] bool operator==(const basic_string &rhs);

        [[nodiscard]] bool operator!=(const basic_string &rhs) const;

        template<class U>
        friend std::ostream &operator<<(std::ostream &os, const basic_string<U> &string);

    private:
        static memorySize strlen(const char *str);

    private:
        spt::vector<T> m_string{0};
        memorySize m_length = 0;
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
        m_string.resize(m_length + 1);
        strcpy(m_string.data(), const_cast<T *>(str));
    }

    template<class T>
    basic_string<T>::basic_string(basic_string &&str) noexcept {
        this->m_length = str.m_length;
        this->m_string = std::move(str.m_string);
        str.m_string.clear();
        str.m_string.shrink_to_fit();
    }

    template<class T>
    typename basic_string<T>::memorySize basic_string<T>::strlen(const char *str) {
        const char *begin = str;
        while (*str)
            ++str;
        return str - begin;
    }

    template<class U>
    std::ostream &operator<<(std::ostream &os, const spt::basic_string<U> &string) {
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
    T &basic_string<T>::operator[](memorySize index) const {
        return m_string[index];
    }


    template<class T>
    void basic_string<T>::erase(memorySize pos, memorySize n) {
        m_string.erase(m_string.begin() + pos, m_string.begin() + pos + n);
        m_length -= n;
        m_string[m_length] = '\0';
    }

    template<class T>
    typename basic_string<T>::iterator basic_string<T>::begin() {
        return m_string.begin();
    }

    template<class T>
    typename basic_string<T>::iterator basic_string<T>::end() {
        return m_string.end();
    }

    template<class T>
    bool basic_string<T>::operator==(const basic_string &rhs) {
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
    typename basic_string<T>::reverse_iterator basic_string<T>::rbegin() {
        return m_string.rbegin();
    }

    template<class T>
    typename basic_string<T>::reverse_iterator basic_string<T>::rend() {
        return m_string.rend();
    }

    template<class T>
    basic_string<T> basic_string<T>::operator+(const basic_string &str) {
        m_string.resize(str.m_length + m_string.size());
        m_length += str.m_length;
        spt::strcat(this->m_string.data(), str.m_string.data());
        return *this;
    }

    template<class T>
    typename basic_string<T>::const_iterator basic_string<T>::cbegin() const {
        return m_string.cbegin();
    }

    template<class T>
    typename basic_string<T>::const_iterator basic_string<T>::cend() const {
        return m_string.cend();
    }


    template<class T>
    void basic_string<T>::reserve(memorySize n) {
        m_string.reserve(n);
    }

    template<class T>
    basic_string<T> &basic_string<T>::operator+=(const basic_string &str) {
        m_string.resize(str.m_length + m_string.size());
        m_length += str.m_length;
        spt::strcat(this->m_string.data(), str.m_string.data());
        return *this;
    }

    template<class T>
    basic_string<T> &basic_string<T>::operator+=(const char *str) {
        memorySize len = spt::strlen(str);
        m_string.resize(len + m_string.size());
        m_length += len;
        spt::strcat(this->m_string.data(), str);
        return *this;
    }

    template<class T>
    basic_string<T> &basic_string<T>::operator+=(const char str) {
        m_string.resize(1 + m_string.size());
        ++m_length;
        spt::strcat(this->m_string.data(), str);
        return *this;
    }

    template<class T>
    basic_string<T> basic_string<T>::operator+(const char *str) {
        memorySize len = spt::strlen(str);
        m_string.resize(len + m_string.size());
        m_length += len;
        spt::strcat(this->m_string.data(), str);
        return *this;
    }

    template<class T>
    basic_string<T> basic_string<T>::operator+(const char str) {
        m_string.resize(1 + m_string.size());
        ++m_length;
        spt::strcat(this->m_string.data(), str);
        return *this;
    }

    template<class T>
    T &basic_string<T>::at(memorySize index) const {
        return m_string.at(index);
    }


    void strcat(char *dest, const char *src) {
        while (*dest)
            dest++;
        while ((*dest++ = *src++));
    }

    void strcat(char *dest, const char src) {
        while (*dest)
            dest++;
        *dest = src;
    }

    uint64_t strlen(const char *str) {
        const char *n = str;
        while (*(++n));
        return n - str;
    }

    void strcpy(char *dest, const char *src) {
        auto cdest = dest;
        auto csrc = src;
        while (*csrc) {
            *cdest = *csrc;
            ++cdest;
            ++csrc;
        }
    }

    //TODO Remove sstream for all to implementations
    basic_string<char> spt::toString(short num) {
        std::stringstream result;
        result << num;
        return string(result.str().c_str());
    }

    string toString(int num) {
        std::stringstream result;
        result << num;
        return string(result.str().c_str());
    }

    basic_string<char> spt::toString(long num) {
        std::stringstream result;
        result << num;
        return string(result.str().c_str());
    }

    basic_string<char> spt::toString(long long int num) {
        std::stringstream result;
        result << num;
        return string(result.str().c_str());
    }

    basic_string<char> spt::toString(float num) {
        std::stringstream result;
        result << num;
        return string(result.str().c_str());
    }

    basic_string<char> spt::toString(double num) {
        std::stringstream result;
        result << num;
        return string(result.str().c_str());
    }

    basic_string<char> spt::toString(long double num) {
        std::stringstream result;
        result << num;
        return string(result.str().c_str());
    }


} //namespace spt

#endif //SPT_STRING_HPP
