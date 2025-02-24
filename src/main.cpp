#include<iostream>
#include "String_My.h"

using std::endl;
using std::cout;
using std::cin;

int main(){
    cout << "测试1" << std::endl;
    String a1("abcd");
    String a2(a1);
    cout << a1 << " " << a2;

    String s1 = a1.substr(0, 2);
    cout << s1 << endl;

    String s2;
    cin >> s2;
    cout << s2 << endl;

    int a;
    cin >> a;
    cout << a;
    
}