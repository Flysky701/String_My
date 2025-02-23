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
        len = other.len;
        cap = other.cap;
        data = new char[cap];
        memcpy(data, other.data, len + 1);
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

    //拷贝
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

    // 操作重载
    String& operator+=(const String &other){
        if(other.len == 0)return *this;

        size_t n_len = len + other.len;
        if(n_len + 1 > cap)
            reserve(n_len * 2);
        
        memcpy(data + len, other.data, other.len);
        len = n_len;
        data[len] = '\0';
        return *this;
    }

    String& operator+= (char c){
        if(len + 1 >= cap)
            reserve(cap == 0 ? 1 : cap * 2);
        data[len] = c;
        data[len + 1] = '\0';
        len ++;
        return *this;
    }

    String& operator+=(const char* str) {
        if (str == nullptr) return *this;
    
        size_t str_len = strlen(str);
        if (str_len == 0) return *this;
    
        size_t n_len = len + str_len;
        if (n_len + 1 > cap) 
            reserve(n_len * 2);
    
        memcpy(data + len, str, str_len);
        len = n_len;
        data[len] = '\0';
        return *this;
    } 
    char& operator[](size_t index){
        return data[index];
    }
    const char& operator[](size_t index) const{
        return data[index];
    }

    String& operator==(const String &other){
        if(len != other.len)return false;
        return memcmp(data, other.data, len) == 0;
    }

    // 常见函数操作
    size_t size(){
        return this -> len;
    }
    size_t capaccity(){
        return this -> cap;
    }
    bool empty(){
        return len == 0 ? true : false;
    }
    void clear(){
        data[0] = '\0';
        len = 0;
    }
    
    void insert(size_t pos, const char *str){
        if(str == nullptr || *str == "\0")return;
        if(pos > len)return;
        size_t str_len = strlen(str);
        size_t n_len = str_len + len;
        
        if(n_len + 1> cap)reserve(n_len * 2);
        memmove(data + pos + str_len, data + pos, len - pos + 1);
        memcpy(data + pos, str, str_len);
        len = n_len;
        data[len] = '\0';
    }
    void insert(size_t pos, String &other){
        insert(pos, other.data);
    }
    void insert(size_t pos, char c){
        if(pos > len)return;
        if(len + 2 > cap)reserve((cap == 0) ? 1 : cap * 2);
        memmove(data + pos + 1, data + pos, len - pos + 1);
        data[pos] = c;
        len ++;
        data[len] = '\0';
    }

    //输入输出 
    friend std::ostream& operator<<(std::ostream os, String& str){
        if(str.data != nullptr)
            os << str.data; 
        else os << "";
    }
    friend std::itream& operator>>(std::istream io)

   

    // 内存管理
    void reserve(size_t n_cap) {
        if (n_cap <= cap) return;
        char* n_data = new char[n_cap]; 
        if (data != nullptr) {
            memcpy(n_data, data, len + 1);
            delete[] data;
        }
        data = n_data;
        cap = n_cap;
    }
    void shrink_to_fit(){
        if(cap > len + 1)
            reserve(len + 1);
    }
    
private:
    char* data;
    size_t len;
    size_t cap;
};
#endif // STRING_MY_H