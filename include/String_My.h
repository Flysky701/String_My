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

    bool operator==(const String &other) const {
        if (len != other.len) return false;
        return memcmp(data, other.data, len) == 0;
    }

    // 常见函数操作
    size_t size(){
        return this -> len;
    }
    size_t capaccity() const{
        return this -> cap;
    }
    bool empty(){
        return len == 0 ? true : false;
    }
    void clear(){
        if(data)data[0] = '\0';
        len = 0;
    }
    
    void insert(size_t pos, const char *str){
        if(str == nullptr || *str == '\0')return;
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

    String substr(size_t pos, size_t length = 0){
        if(pos >= len)return String();
        size_t n_len = (length == 0 || pos + length > len) ? len - pos : length;
        String sub;
        sub.reserve(n_len + 1);
        if(n_len > 0)
            memcpy(sub.data, data + pos, n_len);
        sub.data[n_len] = '\0';
        sub.len = n_len;
        return sub;
    }

    //输入输出 
    friend std::ostream& operator<<(std::ostream &os, String& str){
        if(str.data != nullptr)
            os << str.data; 
        else 
            os << "";
        return os;
    }
    friend std::istream& operator>>(std::istream& io, String& str){
        str.clear();
        char c;

        while (io.get(c) && std::isspace(c)) {}
        if(io.good() == false)return io;
        
        do{
            // if(str.len + 1 >= str.cap)
            //     reserve(str.cap * 2);
            str += c;
        }while(io.get(c) && c != '\n' && c != '\0' && !std::isspace(c));
        
        return io;
    }

   
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
        if(cap > len + 1){
            if(len == 0){
                delete[] data;
                cap = 0;
            }
            else 
                reserve(len + 1);
        }
    }
    
private:
    char* data;
    size_t len;
    size_t cap;
};
#endif // STRING_MY_H