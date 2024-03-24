#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    // 1、初始化
    string s;
    string s1("ssss");
    string s2(10, 'c');
    string s3 = "hiya";
    string s4 = string(10, 'c');

    // 2、复制、拷贝
    string s5(s1);
    string s6 = s1;

    // string s(cp,n)
    char cs[] = "12345";
    string s7(cs, 3); // 复制字符串cs的前3个字符到s当中

    // string s(s2,pos2)
    string s8 = "asdfghjkl";
    string s9(s8, 2); // 从s8下标2开始到最后拷贝

    // string s(s2,pos2,len2)
    string s10 = "qweqweqweq";
    string s11(s10, 3, 4);  // 从s10下标3开始4个字符的拷贝
    string s12(s10, 3, 10); // 超过s10长度只会到s10末尾

    // 3、substr分割截取
    string ss = "abcdefg";
    // s.substr(pos1,n)返回字符串位置为pos1后面的n个字符组成的串
    string s13 = ss.substr(2, 3);  // cde
    string s14 = ss.substr(2, 10); // cdefg

    // s.substr(pos)//得到一个pos到结尾的串
    string s15 = ss.substr(4); // efg
    // string s16=ss.substr(10);//空串

    // 4、insert
    string str = "to be question";

    // s.insert(pos,str)//在s的pos位置插入str
    str.insert(6, "the "); // to be the question

    // s.insert(pos,str,a,n)在s的pos位置插入str中插入位置a到后面的n个字符
    str.insert(6, "or not to be", 3, 4); // to be not the question

    // s.insert(pos,cstr,n)//在pos位置插入cstr字符串从开始到后面的n个字符
    str.insert(10, "that is cool", 8); // to be not that is the question

    // s.insert(pos,n,ch)在s.pos位置上面插入n个ch *注意这里是单引号，是char类型*
    str.insert(15, 1, ':'); // to be not that :is the question
    str.insert(15, 3, ':'); // to be not that ::::is the question

    // 5、大小
    s = "1234567";
    cout << "size=" << s.size() << endl;         // size=7
    cout << "length=" << s.length() << endl;     // length=7
    cout << "max_size=" << s.max_size() << endl; //
    cout << "capacity=" << s.capacity() << endl; // capacity>=length

    // 6、迭代器
    s1 = "abcdef";

    string::iterator iter = s1.begin();
    for (; iter < s1.end(); iter++)
    {
        cout << *iter;
    }
    cout << endl; // abcdef

    string::reverse_iterator riter = s1.rbegin();
    for (; riter < s1.rend(); riter++)
    {
        cout << *riter;
    }
    cout << endl; // fedcba

    string::iterator it;
    // s.insert(s.it,ch)在s的it指向位置前面插入一个字符ch，返回新插入的位置的迭代器
    it = str.insert(str.begin() + 5, ','); // to be, not that ::::is the question
    string str1 = "be or not";
    // s.insert(it,str.ita,str.itb)在it所指向的位置的前面插入[ita,itb)的字符串
    str.insert(it + 2, str1.begin() + 3, str1.begin() + 6); // to be, or not that ::::is the question

    // 7、push_back、append拼接
    string s17 = "12345";
    s17.push_back('6'); // 123456
    cout << s17 << endl;
    s17.append("789"); // 123456789
    cout << s17 << endl;
    string s18="1011";
    s17+=s18; // 1234567891011
    cout<<s17<<endl;

    // 8.erase
    s1 = "123456789";
    s1.erase(s1.begin() + 1);               // 结果：13456789
    s1.erase(s1.begin() + 1, s1.end() - 2); // 结果：189
    s1 = "123456789";
    s1.erase(1, 6);                         // 结果：189

    // 9、replace
    s1="hello,world!";
    s1.replace(6, 5, "girl");                      // 结果：hello,girl!
    s1.replace(s1.size() - 1, 1, 2, '.');          // 结果：hello,girl..
    s1.replace(s1.begin(), s1.begin() + 5, "boy"); // 结果：boy,girl.
    
    //10 sort and reverse需要#include <algorithm>
    s1="285670";
    sort(s1.begin(),s1.end()); // 025678
    cout<<s1<<endl;
    reverse(s1.begin(),s1.end()); // 876520
    cout<<s1<<endl;
    return 0;
}
