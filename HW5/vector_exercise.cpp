#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
	// // 1.定义,设置大小
	// vector<string> myvt;
	// myvt.reserve(4);

	// // 2.添加内容
	// myvt.push_back("Hello");
	// myvt.push_back("World");

	// // 3.迭代，打印内容
	// vector<string>::iterator it;
	// for (it = myvt.begin(); it != myvt.end(); it++)
	// {
	// 	cout << *it << endl;
	// }

	// // 4.获取大小，容量
	// int m = myvt.size();	 // 获取大小:返回矢量中的元素数。
	// int n = myvt.capacity(); // 获取容量:返回当前为向量分配的存储空间的大小，以元素表示。
	// cout << "vector:myvt, size is " << m << endl;
	// cout << "vector:myvt, capacity is " << n << endl;

	// // 5.重设大小
	// myvt.resize(6);
	// cout << "vector:myvt, size is " << myvt.size() << endl;
	// cout << "vector:myvt, capacity is " << myvt.capacity() << endl;

	// // 如果为空值则打印 * 号
	// for (it = myvt.begin(); it != myvt.end(); it++)
	// {
	// 	if (*it == "")
	// 		cout << "******" << endl;
	// 	cout << *it << endl;
	// }

	// // // 6.定义和构造
	// std::vector<int> first;								  // 空矢量
	// std::vector<int> second(4, 100);					  // 值为100的四个整数
	// std::vector<int> third(second.begin(), second.end()); // 遍历构造
	// std::vector<int> fourth(third);						  // 赋值构造

	// // 迭代器构造函数也可用于从数组构造：
	// int myints[] = {16, 2, 77, 29};
	// std::vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));
	// // sizeof(myints) / sizeof(int)得到数组中元素的个数

	// // 7.判断容器中是否有元素，若无元素，则返回 true；反之，返回 false。
	// //	8.添加元素到容器尾部、删除容器尾部元素
	// std::vector<int> myvector;
	// int sum(0);
	// for (int i = 1; i <= 10; i++)
	// 	myvector.push_back(i);
	// while (!myvector.empty())
	// {
	// 	sum += myvector.back();
	// 	myvector.pop_back();
	// }

	// //9.返回第一个元素的引用、返回最后一个元素的引用
	// myvector.push_back(78);
	// myvector.push_back(16);
	// cout<<myvector.front()<<endl;
	// cout<<myvector.back()<<endl;
	
	//10.将新内容分配给向量，替换其当前内容，并相应地修改其大小
	std::vector<int> first;
	std::vector<int> second;
	std::vector<int> third;

	first.assign(7, 100);             // 7个整数，值为100

	second.assign(3,20);

	for (int i = 0; i < second.size(); i++)
	{
		cout << second[i] << " ";
	}
	cout<<endl;

	std::vector<int>::iterator it;
	it = first.begin() + 1;
	second.assign(it, first.end() - 1); // 从第2个值到到数第1个值

	for (int i = 0; i < second.size(); i++)
	{
		cout << second[i] << " ";
	}
	cout<<endl;

	int myints[] = { 17,76,7,4 };
	third.assign(myints, myints + 3);   // 从数组分配
	for (int i = 0; i < third.size(); i++)
	{
		cout << third[i] << " ";
	}
	return 0;
}
