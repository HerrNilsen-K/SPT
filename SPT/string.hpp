//
// Created by karl on 28.02.21.
//

#ifndef SPT_STRING_HPP
#define SPT_STRING_HPP

#include <cstring>
#include <ios>
#include <ostream>
#include <any>
#include <sstream>
#include <type_traits>
#include <tuple>
#include "vector.hpp"

namespace spt {
    template<class T>
    class basic_string;

    using string = basic_string<char>;

    void strcat(char *dest, const char *src);

    void strcat(char *dest, const char src);

    uint64_t strlen(const char *str);

    string toString(short num);

    string toString(int num);

    string toString(long num);

    string toString(long long num);

    string toString(float num);

    string toString(double num);

    string toString(long double num);

    void strcpy(char *dest, const char *src);

    const char *strstr(const char *haystack, const char *needle);

    const char *strchr(const char *haystack, const char needle);

    char toUpper(char c);

    char toLower(char c);


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

        memorySize size() const;

        //Clear the string
        void clear();

        //Erase n elements after pos
        void erase(memorySize pos, memorySize n);

        //Reserves memory, but doesn't change the size
        void reserve(memorySize n);

        //Returns the index of the first occurence of the substring
        //Throws -1 if no substring was found
        memorySize find(const basic_string<T> &str);

        memorySize find(const char c);

        memorySize find(const char *str);

        //Transform chars to upper/lower:

        //The entire string
        void toUpper();

        //A single char at index i
        void toUpper(memorySize i);

        //An substring from start to end
        void toUpper(iterator start, iterator end);

        //The entire string
        void toLower();

        //A single char at index i
        void toLower(memorySize i);

        //An substring from start to end
        void toLower(iterator start, iterator end);

        //Replace index i with c
        void replace(memorySize i, char c);

        //Replace after i - 1 with str for strlen(str)
        void replace(memorySize i, const char *str);

        //Replace after i - 1 with str for str.length()
        void replace(memorySize i, const basic_string<T> &str);

        iterator begin();

        iterator end();

        const_iterator cbegin() const;

        const_iterator cend() const;

        reverse_iterator rbegin();

        reverse_iterator rend();

        basic_string operator+(const basic_string &str);

        basic_string operator+(const char *str) const;

        basic_string operator+(char str);

        basic_string &operator+=(const basic_string &str);

        basic_string &operator+=(const char *str);

        basic_string &operator+=(char str);

        basic_string &operator=(const char *str);

        basic_string &operator=(const basic_string &str);

        T &operator[](memorySize index) const noexcept;

        //Out of bounce safe indexing
        T &at(memorySize index) const;

        bool operator<(const basic_string &rhs) const;

        bool operator>(const basic_string &rhs) const;

        bool operator<=(const basic_string &rhs) const;

        bool operator>=(const basic_string &rhs) const;

        bool operator==(const basic_string &rhs);

        bool operator!=(const basic_string &rhs) const;

        template<class U>
        friend std::ostream &operator<<(std::ostream &os, const basic_string<U> &str);

        template<class U>
        friend std::istream &operator>>(std::istream &is, const basic_string<U> &str);


    private:
        static memorySize strlen(const char *str);

    private:
        spt::vector<T> m_string{0};
        memorySize m_length = 0;
    };

    template<class T>
    basic_string<T>::basic_string(const basic_string<T> &str) {
        /*this->m_length = str.m_length;
        this->m_string = str.m_string;
        if (this->m_string.size() > this->m_string.capacity()) {
            this->m_string[this->m_string.size() + 1] = '\0';
        } else {
            this->m_string.push_back('\0');
        }
         */
        this->m_string = str.m_string;
        this->m_length = str.m_length;
    }

    template<class T>
    basic_string<T>::basic_string(const T *str) {
        m_length = spt::strlen(str);
        m_string.resize(m_length + 1);
        m_string.at(m_length) = '\0';
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
    std::ostream &operator<<(std::ostream &os, const spt::basic_string<U> &str) {
        os << str.m_string.data();
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
    T &basic_string<T>::operator[](memorySize index) const noexcept {
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
    basic_string<T> basic_string<T>::operator+(const char *str) const {
        /*
        memorySize len = spt::strlen(str);
        m_string.resize(len + m_string.size());
        m_length += len;
        spt::strcat(this->m_string.data(), str);
        return *this;
         */

        basic_string<T> result = *this;
        memorySize len = spt::strlen(str);
        result.m_string.resize(len + result.m_length + 1);
        result.m_length += len;
        spt::strcat(result.m_string.data(), str);
        return result;
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

    template<class T>
    typename basic_string<T>::memorySize basic_string<T>::find(const char *str) {
        const char *pos = spt::strstr(this->c_string(), str);
        if (pos == nullptr)
            throw -1;
        return pos - this->c_string();
    }

    template<class T>
    typename basic_string<T>::memorySize basic_string<T>::find(const basic_string<T> &str) {
        const char *pos = spt::strstr(this->c_string(), str.c_string());
        if (pos == nullptr)
            // TODO Make own exception
            throw std::runtime_error("No substr found");
        return pos - this->c_string();
    }

    template<class T>
    typename basic_string<T>::memorySize basic_string<T>::find(const char c) {
        const char *pos = spt::strchr(this->c_string(), c);
        if (pos == nullptr)
            // TODO Make own exception
            throw std::runtime_error("No substr found");
        return pos - this->c_string();
    }

    template<class U>
    std::istream &operator>>(std::istream &is, const basic_string<U> &str) {
        char c[1024];
        is >> str.m_string.data();
        return is;
    }

    template<class T>
    basic_string<T>::basic_string() {
    }

    template<class T>
    void basic_string<T>::toUpper() {
        for (auto &i : *this)
            i = static_cast<T>(spt::toUpper(i));
    }

    template<class T>
    void basic_string<T>::toUpper(basic_string::memorySize i) {
        m_string.at(i) = static_cast<T>(spt::toUpper(m_string.at(i)));
    }

    template<class T>
    void basic_string<T>::toUpper(basic_string::iterator start, basic_string::iterator end) {
        for (auto i = start; i != end; ++i)
            *i = static_cast<T>(spt::toUpper(*i));
    }

    template<class T>
    void basic_string<T>::toLower() {
        for (auto &i : *this)
            i = static_cast<T>(spt::toLower(i));
    }

    template<class T>
    void basic_string<T>::toLower(basic_string::memorySize i) {
        m_string.at(i) = static_cast<T>(spt::toLower(m_string.at(i)));
    }

    template<class T>
    void basic_string<T>::toLower(basic_string::iterator start, basic_string::iterator end) {
        for (auto i = start; i != end; ++i)
            *i = static_cast<T>(spt::toLower(*i));
    }

    template<class T>
    void basic_string<T>::replace(basic_string::memorySize i, char c) {
        m_string.at(i) = c;
    }

    template<class T>
    void basic_string<T>::replace(basic_string::memorySize i, const char *str) {
        spt::strcpy(begin() + i, str);
    }

    template<class T>
    void basic_string<T>::replace(basic_string::memorySize i, const basic_string<T> &str) {
        spt::strcpy(begin() + i, str.c_string());
    }

    template<class T>
    typename basic_string<T>::memorySize basic_string<T>::size() const {
        return m_length;
    }

    template<class T>
    void basic_string<T>::clear() {
        m_string.clear();
        m_string.push_back('\0');
        m_length = 0;
    }

    template<class T>
    basic_string<T> &basic_string<T>::operator=(const char *str) {
        *this = basic_string<T>(str);
        return *this;
    }


    void strcat(char *dest, const char *src) {
        /*while (*dest)
            dest++;
        while ((*dest++ = *src++)){
            int i;
            i = 0;
        }*/
        std::strcat(dest, src);
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

    string spt::toString(short num) {
        char buf[25];
        sprintf(buf, "%i", num);
        return string(buf);
    }

    string toString(int num) {
        char buf[25];
        sprintf(buf, "%i", num);
        return string(buf);
    }

    string spt::toString(long num) {
        char buf[25];
        sprintf(buf, "%li", num);
        return string(buf);
    }

    string spt::toString(long long int num) {
        char buf[25];
        sprintf(buf, "%lli", num);
        return string(buf);
    }

    string spt::toString(float num) {
        char buf[25];
        sprintf(buf, "%f", num);
        return string(buf);
    }

    string spt::toString(double num) {
        char buf[25];
        sprintf(buf, "%f", num);
        return string(buf);
    }

    string spt::toString(long double num) {
        char buf[25];
        sprintf(buf, "%Lf", num);
        return string(buf);
    }

    const char *strstr(const char *haystack, const char *needle) {
        ///TODO Make own implementation
        return std::strstr(haystack, needle);
    }

    const char *spt::strchr(const char *haystack, const char needle) {
        ///TODO Make own implementation
        return std::strchr(haystack, needle);
    }

    char toUpper(char c) {
        return (c >= 'a' && c <= 'z') ? c - 32 : c;
    }

    char toLower(char c) {
        return (c >= 'A' && c <= 'Z') ? c + 32 : c;
    }


} //namespace spt

#endif //SPT_STRING_HPP
