#include<iostream>
#include "String_My.h"

using std::endl;
using std::cout;
using std::cin;

int main(){
    cout << "test1" << std::endl;

    String a1("abcd");
    String a2(a1);
    cout << a1 << " " << a2 << endl;

    a1 += a2;
    a1 += '1';
    a1 += "23";
    for(int i = 0; i <= 10; i ++)
        cout << a1[i] << " ";
    cout << endl;

    a1.insert(2, "987");
    a1.insert(9, a2);
    a1.insert(0, '0');
    cout << a1 << endl;
    a2.clear();
    cout << a2 << endl;
    if(a2.empty())cout << "empty" << endl;

    cout << a1.size() << " " << a1.capaccity() << endl;
    a2 = a1;
    cout << (a1 == a2 ? "Yes" : "No") << endl;
    a2.insert(0, "0");
    cout << (a1 == a2 ? "Yes" : "No") << endl;

    // String s1 = a1.substr(0, 2);
    // cout << s1 << endl;

    String s2;
    cin >> s2;
    cout << s2 << endl;


}