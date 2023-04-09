#pragma once
#include <iostream>

class String {
public:
    String();
    ~String();
    explicit String(const char ch);
    explicit String(const char* chars);
    explicit String(const String& other);
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
private:
    char *_str; // cstring (with \0)
    std::size_t _size; // length of _str (without \0)
    std::size_t _chars_alloc; // max length of _str (also without \0)

    void _free();
};

std::ostream& operator<<(std::ostream& ostr, const String &str);
bool operator==(const String& left, const String& right);
bool operator==(const String& left, const char* right);
bool operator!=(const String& left, const String& right);
bool operator!=(const String& left, const char* right);
