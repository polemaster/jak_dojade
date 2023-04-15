#pragma once
#include <iostream>

const std::size_t INITIAL_MAX_STR_LEN = 8;

class String {
public:
    String();
    ~String();
    explicit String(const char ch);
    String(const char* chars); // to change
    String(const String& other);
    String(String&& other); // needs to be implicit in order for + operator to work

    String& operator=(const String& right);
    String& operator=(String&& right);
    String& operator=(const char* right);
    String& operator=(const char ch);
    char& operator[](std::size_t index);
    const char& operator[](std::size_t index) const;
    String operator+(const String& right) const;
    String operator+(const char* right) const;
    String operator+(const char ch) const;
    String& operator+= (const String& right);
    String& operator+= (const char* right);
    String& operator+= (const char ch);

    char* c_str() const;
    std::size_t length() const;
    std::size_t size() const;

    bool empty() const;
    int compare(const String& other) const;
    int compare(const char* other) const;
    // friend std::istream& getline(std::istream& is, String& str);
    void trimWhitespace();
    // if correctly converted, returns non-negative integer; otherwise returns -1
    int toInt() const;
    bool isInt() const;
    void clear();
private:
    char *_str; // cstring (with \0)
    std::size_t _size; // length of _str (without \0)
    std::size_t _chars_alloc; // max length of _str (also without \0)

    void _free();
};

std::ostream& operator<<(std::ostream& ostr, const String &str);
std::istream& operator>>(std::istream& is, String& str);
bool operator==(const String& left, const String& right);
bool operator==(const String& left, const char* right);
bool operator!=(const String& left, const String& right);
bool operator!=(const String& left, const char* right);
bool operator>(const String& left, const char* right);
bool operator>(const String& left, const String& right);



std::size_t str_len (const char *str) {
    std::size_t length = 0;
    while (str[length] != '\0')
        ++length;

    return length;
}

void str_cpy(char* dest, const char* src) {
    while ( *src != '\0' ) {
        *dest = *src;
        ++dest;
        ++src;
    }
    *dest = '\0';
}

char *str_cat(char *dest, const char *src) {
    char *tmp = dest;

    while (*dest != '\0')
        ++dest;
    str_cpy(dest, src);
    return tmp;
}

int str_cmp(const char* str1, const char* str2) {
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 < *str2)
            return -1;
        else if (*str1 > *str2)
            return 1;

        ++str1;
        ++str2;
    }
    if (*str1 == '\0' && *str2 == '\0')
        return 0;
    else if (*str1 == '\0')
        return -1;
    else
        return 1;
}

String::String() {
    _str = nullptr;
    _size = 0;
    _chars_alloc = 0;
}

String::String(const char ch) {
    _chars_alloc = INITIAL_MAX_STR_LEN + 1;
    _str = new char[_chars_alloc + 1];
    _str[0] = ch;
    _str[1] = '\0';
    _size = 1;
}

String::String(const char *chars) {
    if (chars == nullptr) {
        _str = nullptr;
        _size = 0;
        _chars_alloc = 0;
        return;
    }
    _size = str_len(chars);
    _chars_alloc = _size + INITIAL_MAX_STR_LEN;
    _str = new char[_chars_alloc + 1];
    str_cpy(_str, chars);
}

String::String(const String& other) {
    _size = other._size;
    _chars_alloc = other._chars_alloc;
    _str = new char[_chars_alloc + 1];
    str_cpy(_str, other._str);
}

String::String(String&& other) {
    _str = other._str;
    _size = other._size;
    _chars_alloc = other._chars_alloc;

    other._str = nullptr;
    other._size = 0;
    other._chars_alloc = 0;
}

void String::_free() {
    if (_str != nullptr) {
        delete[] _str;
        _str = nullptr;
        _size = 0;
        _chars_alloc = 0;
    }
}

String::~String() {
    _free();
}

String& String::operator=(const String& right) {
    if (this == &right)
        return *this;


    String new_str(right);
    std::swap(*this, new_str);

    return *this;
}

String& String::operator=(String&& right) {
    if (this == &right)
        return *this;

    _free();

    _str = right._str;
    _size = right._size;
    _chars_alloc = right._chars_alloc;

    right._str = nullptr;
    right._size = 0;
    right._chars_alloc = 0;

    return *this;
}

String& String::operator=(const char* right) {
    String new_str(right);
    std::swap(*this, new_str);

    return *this;
}

String& String::operator=(const char ch) {
    String new_str(ch);
    std::swap(*this, new_str);

    return *this;
}

char& String::operator[] (std::size_t index) {
    if (index >= _size)
        throw std::out_of_range("Tried to access string outside of range");
    return _str[index];
}

const char& String::operator[](std::size_t index) const {
    if (index >= _size)
        throw std::out_of_range("Tried to access string outside of range");
    return _str[index];
}


String& String::operator+=(const String& right) {
    std::size_t new_len = _size + right._size;

    // if size of the new string is greater than max length of current string,
    // then allocate new memory
    if (new_len > _chars_alloc) {
        _chars_alloc = new_len + INITIAL_MAX_STR_LEN;
        char *new_str = new char[_chars_alloc + 1];

        str_cpy(new_str, _str);
        str_cat(new_str, right._str);

        _free();

        _str = new_str;
        _size = new_len;
        _chars_alloc = _size + INITIAL_MAX_STR_LEN;
    }
    // otherwise concatenate strings
    else {
        str_cat(_str, right._str);
        _size = new_len;
    }


    return *this;
}

String& String::operator+= (const char* right) {
    std::size_t new_len = _size + str_len(right);

    if (new_len > _chars_alloc) {
        _chars_alloc = new_len + INITIAL_MAX_STR_LEN;
        char *new_str = new char[_chars_alloc + 1];

        str_cpy(new_str, _str);
        str_cat(new_str, right);

        _free();

        _str = new_str;
        _size = new_len;
        _chars_alloc = _size + INITIAL_MAX_STR_LEN;
    }
    else {
        str_cat(_str, right);
        _size = new_len;
    }

    return *this;
}

String& String::operator+= (const char ch) {
    std::size_t new_len = _size + 1;

    if (_str == nullptr) {
        String new_str(ch);
        std::swap(*this, new_str);
    }
    else if (new_len > _chars_alloc) {
        _chars_alloc = new_len + INITIAL_MAX_STR_LEN;
        char *new_str = new char[_chars_alloc + 1];

        str_cpy(new_str, _str);
        new_str[new_len - 1] = ch;
        new_str[new_len] = '\0';

        _free();

        _str = new_str;
        _size = new_len;
        _chars_alloc = _size + INITIAL_MAX_STR_LEN;
    }
    else {
        _str[new_len - 1] = ch;
        _str[new_len] = '\0';
        _size = new_len;
    }

    return *this;
}

String String::operator+(const String& right) const {
    String result(*this);
    result += right;

    return result;
}

String String::operator+(const char* right) const {
    String result(*this);
    result += right;

    return result;
}

String String::operator+(const char ch) const {
    String result(*this);
    result += ch;

    return result;
}

size_t String::length() const {
    return _size;
}

size_t String::size() const {
    return _size;
}

char* String::c_str() const {
    return _str;
}

bool String::empty() const {
    return _size == 0;
}

int String::compare(const String& other) const {
    return str_cmp(_str, other._str);
}

int String::compare(const char* other) const {
    return str_cmp(_str, other);
}

// std::istream& getline(std::istream& is, String& str) {
//     char ch;
//     size_t n = 0, cap = 8;
//     char *buffer = new char[cap];
//     while (is.get(ch) && ch != '\n' && ch != EOF) {
//         buffer[n++] = ch;
//         if (n == cap) {
//             cap *= 2;
//             char *new_buffer = new char[cap];
//             str_cpy(new_buffer, buffer);
//             delete[] buffer;
//             buffer = new_buffer;
//         }
//     }
//     buffer[n] = '\0';

//     str._free();
//     str._size = n;
//     str._str = buffer;
//     str._chars_alloc = cap;

//     return is;
// }

void String::trimWhitespace() {
    if (_size == 0)
        return;

    char *begin = _str;
    while (*begin == ' ' || *begin == '\n' || *begin == '\t')
        ++begin;

    char *end = _str + _size - 1;
    while ((*end == ' ' || *end == '\n' || *end == '\t') && end > begin)
        --end;

    std::size_t new_size = end - begin + 1;
    if (_size != new_size) {
        *(end + 1) = '\0';
        str_cpy(_str, begin);
        _size = new_size;
    }
}

int String::toInt() const {
    int result = 0;
    char *tmp = _str;
    while (*tmp != '\0') {
        if (*tmp < '0' || *tmp > '9')
            return -1;
        result = result * 10 +  (*tmp - '0');
        ++tmp;
    }
    return result;
}

bool String::isInt() const {
    const char *str = _str;

    if (*str == '\0' || str == nullptr)
        return false;

    // if there is a sign before the number, skip it
    if (*str == '-' || *str == '+')
        ++str;

    while (*str != '\0') {
        if (*str < '0' || *str > '9')
            return false;

        ++str;
    }
    return true;
}

void String::clear() {
    _free();
}

std::ostream& operator<<(std::ostream& ostr, const String &str) {
    if (!str.empty())
        ostr << str.c_str();

    return ostr;
}

std::istream& operator>>(std::istream& is, String& str) {
    str.clear();

    is >> std::ws;

    char c;
    while (is.get(c) && !isspace(c)) { // to change
        str += c;
    }

    return is;
}


bool operator==(const String& left, const String& right) {
    return left.compare(right) == 0;
}

bool operator==(const String& left, const char* right) {
    return left.compare(right) == 0;
}

bool operator!=(const String& left, const String& right) {
    return left.compare(right) != 0;
}

bool operator!=(const String& left, const char* right) {
    return left.compare(right) != 0;
}

bool operator>(const String& left, const char* right) {
    return left.compare(right) > 0;
}

bool operator>(const String& left, const String& right) {
    return left.compare(right) > 0;
}
