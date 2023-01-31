//
// Created by rgr24 on 26/10/2022.
//

#ifndef MOVE_SEMANTICS_MY_STRING_H
#define MOVE_SEMANTICS_MY_STRING_H


#include <cstddef>
#include <cstring>
#include <iostream>
inline static int start =0;
class my_string {
public:

    my_string(const char *s)
            : m_length(strlen(s)), m_data(new char[m_length + 1]) {
        std::copy(s, s + m_length + 1, m_data);
        start++;
        std::cout<<"\nCreate constructor my_string "<<this->data()<<"\n";

    }

    // copy ctor
    my_string(const my_string& other)
    : my_string(other.m_data) {
        std::cout<<"\nCopy string\n";
    }
    ///Move constructor
    my_string(my_string&&other):
    m_length(other.m_length),m_data(std::exchange(other.m_data, nullptr))
    {
        std::cout<<"\nMove constructor string\n";
    }
    // copy assignment op
    my_string& operator=(my_string other) {
        std::swap(m_data, other.m_data);
        std::swap(m_length, other.m_length);
        return *this;
    }
    ///Move assignment
    my_string& operator =(my_string&&other){
        std::cout<<"\nMove assignment string\n";
        delete[]m_data;
        m_data=std::exchange(other.m_data, nullptr);
        m_length=other.m_length;
        return *this;
    }
    // destructor
    ~my_string() noexcept {
        std::cout<<"\nDestroy my_string "<<this->data()<<"\n";
        delete[] m_data;
        start--;
    }

    auto length() const { return m_length; }

    const char *data() const { return m_data; }

private:
    size_t m_length;
    char *m_data;
};

std::ostream &operator<<(std::ostream &os, const my_string &str) {
    os << str.data();
    return os;
}

#endif //MOVE_SEMANTICS_MY_STRING_H
