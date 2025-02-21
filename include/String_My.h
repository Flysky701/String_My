#ifndef STRING_MY_H
#define STRING_MY_H

#include <iostream>
#include <cstring>

class String{
public:
    // 构造函数
    String() noexcept{
        data = nullptr;
        len = 0;
        cap = 0;
    }
    String(const char* str)
    {
        len = strlen(str);
        cap = len + 1;
        data = new char[cap];
        strcpy(data, str);
    }
    String(const String& other){
        data = other.data;
        len = other.len;
    }
    String(String&& other) noexcept{
        data = other.data;
        len = other.len;
        cap = other.cap;
        other.data = nullptr;
        other.len = 0;
        other.cap = 0;
    }

    // 析构函数
    ~String() noexcept{
        delete[] data;
    }

    //
    String& operator=(const String& other){
        if(this != &other){
            delete[] data;
            data = other.data;
            len = other.len;
            cap = other.cap;
            strcpy(data, other.data);
        }
        return *this;
    }

    String& operator=(String && other) noexcept{
        if(this != &other){
            delete[] data;
            data = other.data;
            len = other.len;
            cap = other.cap;
            other.data = nullptr;
            other.len = 0;
            other.cap = 0;
        }
        return *this;
    }

    char& operator[](size_t index){
        return data[index];
    }
    const char& operator[](size_t index) const{
        return data[index];
    }
    // += / == / + 



private:
    char* data;
    size_t len;
    size_t cap;
};
#endif // STRING_MY_H