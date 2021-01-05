#pragma once
#include <string>
/*	设置图书类，使用图书类的对象实现向数据操作函数传递数据，从数据库中获取数据传递到对象，
	使用STL容器保存数据，使用map容器可以为每个对象绑定一个key值，显示的时候有序号，
	从数据库读取的时候就直接使用ISBN排序，在逐个读取的时候就可以按照序号递增标注记录
*/

class CBook
{
public:
	CBook() {};
	CBook(char* cName, char* cIsbn, float cPrice, char* cAuthor);//构造函数
	~CBook() {};
public:
	char* GetName();//返回图书名
	char* GetIsbn();//返回ISBN
	float GetPrice();//返回价格
	char* GetAuthor();//返回作者
private:
	static const int NUM1 = 50;//存储图书名、ISBN字符串的初始大小
	static const int NUM2 = 30;//存储作者字符串的初始大小
	char m_cName[NUM1];//图书名
	char m_cIsbn[NUM1];//图书ISBN
	float m_cPrice;//图书价格
	char m_cAuthor[NUM2];//图书作者
};