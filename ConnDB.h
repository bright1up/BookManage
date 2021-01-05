#pragma once
//#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","adoEOF")
#include "Book.h"
#include <map>
#include <string>


class Lib_db
{
public:
	std::string ShowAll();//显示数据库表中的所有记录
	std::string InsertItem(CBook *book);//图书入库，以类指针的方式传递
	std::string SearchByIsbn(char* isbn);//查找图书，以字符串的形式传递ISBN
	std::string SearchByName(char* name);//按照图书名查找图书，以字符串的形式传递
	std::string DeleteItem(char* isbn);//删除图书，以字符串的形式传递ISBN
	void ExitConnect();//断开连接
protected:
	bool OnInitADOConn();//连接数据库，连接默认的数据库
	std::string GetRecordSet(std::string bstrSQL);//执行查询，返回记录集，自动更新私有数据集指针指向的内容
	bool ExecuteSQL(std::string bstrSQL);//执行SQL语句，不更新数据集的内容
	bool IsExits(char* isbn);//判断记录在数据库中是否存在
	std::string Frame_display(std::string&);//用来排列字符串
private:
	//_ConnectionPtr m_pConnection;//数据库连接指针，指向数据库
	//_RecordsetPtr m_pRecordset;//记录集，返回查询结果
};