//
// Created by karl on 28.02.21.
//

#ifndef SPT_STRING_HPP
#define SPT_STRING_HPP

#include <cstring>
#include <ios>
#include <ostream>
#include "vector.hpp"

namespace spt {

    class string {
    public:
        string(const char *str);

        const unsigned char* c_string() const;

        string &operator=(const string &str);

        unsigned char &operator[](uint64_t index) const;
        friend std::ostream &operator<<(std::ostream &os, const string &string);

    private:
        template<uint64_t N>
        constexpr uint64_t c_strlen(char const(&)[N]);

        uint64_t strlen(const char *str) const;

    private:
        spt::vector<unsigned char> m_string;
        uint64_t m_size;
    };

    string::string(const char *str)
            : m_string(0), m_size(strlen(str)) {
        m_string.resize(m_size);
        std::memcpy(m_string.data(), str, m_size);
        //std::strcpy(m_string.data(), str);
    }

    template<uint64_t N>
    constexpr uint64_t c_strlen(char const (&)[N]) {
        return N - 1;
    }

    uint64_t string::strlen(const char *str) const {
        uint64_t i = 0;
        while (str[i])++i;
        return i;
    }

    std::ostream &operator<<(std::ostream &os, const spt::string &string) {
        os << string.m_string.data();
        return os;
    }

    string &string::operator=(const string &str) {
        this->m_size = str.m_size;
        this->m_string = str.m_string;
        if(this->m_string.size() > this->m_string.capacity()){
            this->m_string[this->m_string.size() + 1] = '\0';
        } else {
            this->m_string.push_back('\0');
        }
        return *this;
    }

    const unsigned char *string::c_string() const {
        return m_string.data();
    }

    unsigned char &string::operator[](uint64_t index) const {
        return m_string[index];
    }

} //namespace spt

#endif //SPT_STRING_HPP
