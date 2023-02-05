//
// Created by dza02 on 10/26/2022.
//


#ifndef LESSON_2022_TRACKED_STRING_H
#define LESSON_2022_TRACKED_STRING_H

#include <cstring>
#include <string_view>
#include <iostream>

#ifdef _MSC_VER
#define pp() std::printf("%s\n", __FUNCSIG__)
#else
#define pp() std::printf("===TRACE===: %s\n", __PRETTY_FUNCTION__)
#endif



#define TRACE_SPECIAL (1)
#define TRACE_ALL (1)


#if ((defined(TRACE_SPECIAL) && TRACE_SPECIAL) || (defined(TRACE_ALL) && TRACE_ALL))
#define TRSP() pp()
#else
#define TRSP()
#endif

#if ((defined(TRACE_ALL) && TRACE_ALL))
#define TRAL() pp()
#else
#define TRAL()
#endif

inline static int count_{0};

inline int count(){
    return ++count_;
}

inline void reset() { count_ = 0; }

template <typename CH = char>
struct basic_tracked_string{
    static constexpr auto DEF_SZ{1};

    using value_type = CH;
    using iterator = CH*;
    using const_iterator = CH const *;

    basic_tracked_string(const CH* str):
            basic_tracked_string{std::strlen(str)}
    {
        TRSP();
        count();
        std::memcpy(str_, str, len_);
    }

    basic_tracked_string(std::basic_string_view<CH> sv):
            basic_tracked_string{sv.length()}
    {
        TRSP();
        count();
        std::memcpy(str_, sv.data(), len_);
    }

    basic_tracked_string(): basic_tracked_string{DEF_SZ} {
        count();
        TRSP();
    }

    basic_tracked_string(const basic_tracked_string& other):
            basic_tracked_string{other.len_}{
        TRSP();
        count();
        std::memcpy(str_, other.c_str(), len_);
    }

    basic_tracked_string& operator=(const basic_tracked_string& other){
        TRSP();
        count();
        if (this == &other) return *this;

        auto str = str_;

        if (len_ != other.len_){
            str = new CH[other.len_];
        }
        else {
            str_ = nullptr;
        }

        memcpy(str, other.str_, other.len_);
        delete[] str_;
        str_ = str;
        len_ = other.len_;

        return *this;
    }

    basic_tracked_string(basic_tracked_string&& other):
            basic_tracked_string{DEF_SZ}
    {
        TRSP();
        std::swap(len_, other.len_);
        std::swap(str_, other.str_);
    }
    basic_tracked_string& operator=(basic_tracked_string&& other){
        TRSP();
        if (this == &other) return *this;
        std::swap(len_, other.len_);
        std::swap(str_, other.str_);
        memset(other.str_, 0, other.len_);
        other.len_ = 0;
        return *this;
    }

    ~basic_tracked_string() noexcept {
        TRSP();
        delete[] str_;
    }

    void swap(basic_tracked_string& other){
        TRSP();
        std::swap(len_, other.len_);
        std::swap(str_, other.str_);
    }

    operator std::string_view() const {
        TRAL();
        return {str_, len_};
    }

    std::size_t length() const {
        TRAL();
        return len_;
    }

    std::size_t size() const {
        TRAL();
        return len_;
    }

    CH operator[](std::size_t index) const {
        TRAL();
        return *(str_ + index);
    }

    CH& operator[](std::size_t index) {
        TRAL();
        return *(str_ + index);
    }

    CH at(std::size_t index) const {
        TRAL();
        if (index > len_) throw std::out_of_range("Index is out of range.");
        return *(str_ + index);
    }

    CH& at(std::size_t index) {
        TRAL();
        if (index > len_) throw std::out_of_range("Index is out of range.");
        return *(str_ + index);
    }

    iterator begin() {
        TRAL();
        return str_;
    }

    iterator end() {
        TRAL();
        return str_ + len_ + 1;
    }

    const_iterator begin() const {
        TRAL();
        return str_;
    }

    const_iterator end() const {
        TRAL();
        return str_ + len_ + 1;
    }

    CH const * c_str() const {
        TRAL();
        return str_;
    }

    CH * data() {
        TRAL();
        return str_;
    }

private:
    basic_tracked_string(std::size_t len):
            len_{len},
            str_{ new CH[len + 1]{} }
    {}

    std::size_t len_;
    char * str_;
};

using tracked_string = basic_tracked_string<char>;

template <typename CH>
void swap(basic_tracked_string<CH>& a, basic_tracked_string<CH>& b){
    TRSP();
    a.swap(b);
}

template <typename CH>
std::ostream& operator<<(std::ostream& out, basic_tracked_string<CH> const& str){
    TRAL();
    return out << str.c_str();
}

#endif //LESSON_2022_TRACKED_STRING_H