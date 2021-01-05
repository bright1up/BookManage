#include "ConnDB.h"
#include <exception>
#include <fstream>
bool Lib_db::OnInitADOConn() {//连接数据库，m_pConnection指向数据库
	try {
		return true;
	}
	catch (std::exception e) {
		return false;

	}
}
std::string Lib_db::GetRecordSet(std::string bstrSQL) {//根据传入的SQL进行数据库的查询，返回数据集指针，不用返回也可以，直接调用私有变量即可
	try {
	}
	catch (std::exception e) {
		e.what();
	}
	return "成功";
}
bool Lib_db::ExecuteSQL(std::string bstrSQL) {
	try {
		return true;
	}
	catch (std::exception e) {
		e.what();
		return false;
	}
}

void Lib_db::ExitConnect() {
	
}

std::string Lib_db::ShowAll() {
	/*try {
		std::fstream file;
		file.open("db.dat", std::ios::in);
		if (!file.is_open()) {
			return "文件打开出错。";
		}
		std::string name, isbn, price, author, result;
		while (!file.eof()){
			file >> name >> isbn >> price >> author;
			result += name + '\t' + isbn + '\t' + price + '\t' + author + '\n';
		}
		file.close();
		return result;
	}
	catch (std::exception e) {
		return e.what();
	}*/
	return "显示全部";
}

std::string Lib_db::InsertItem(CBook *book) {
	/*if (book == NULL) {
		return "输入为空。";
	}
	if (this->IsExits(book->GetIsbn())) {
		return "库中已存在该书籍。";
	}
	try {
		std::ofstream file;
		file.open("db.dat", std::ios::app);
		file << book->GetName << " " << book->GetIsbn << " " << book->GetPrice << " " << book->GetAuthor << '\n';
		return "入库成功。";
	}
	catch (std::exception e) {
		return e.what();
	}*/
	return "插入图书";
}

std::string Lib_db::SearchByIsbn(char *isbn) {
	//if (isbn == NULL) {
	//	return "输入ISBN为空。";
	//}
	//try {
	//	if (0) {
	//		//this->ExitConnect();
	//		return "查询结果为空。";
	//	}
	//	else {
	//		std::string result = this->ShowAll();
	//		//this->ExitConnect();
	//		return result;
	//	}
	//}
	//catch (std::exception e) {
	//	return "出错。";
	//}
	return "按照ISBN查找";
}

std::string Lib_db::SearchByName(char* name) {
	//if (name == NULL) {
	//	return "输入的图书名为空。";
	//}
	//try {
	//	_bstr_t SQL = "SELECT * FROM Books WHERE Name LIKE '%" + (_bstr_t)name + "%' ORDER BY Isbn;";
	//	m_pRecordset = this->GetRecordSet(SQL);
	//	if (m_pRecordset->GetRecordCount() == 0) {
	//		//this->ExitConnect();
	//		return "查询结果为空。";
	//	}
	//	else {
	//		_bstr_t result = "";
	//		result += "查询结果 " + (_bstr_t)m_pRecordset->GetRecordCount() + "\n";
	//		result += this->Frame_display(m_pRecordset);
	//		//this->ExitConnect();
	//		return result;
	//		}
	//	}
	//catch (std::exception e) {
	//	return e.what();
	//}
	return "按照书名查找";
}

std::string Lib_db::DeleteItem(char* isbn) {
	//if (isbn == NULL) {
	//	return "输入ISBN为空。";
	//}
	//if (!this->IsExits(isbn)) {
	//	return "库中不存在此书籍。";
	//}
	//if (m_pConnection == NULL) {
	//	this->OnInitADOConn();
	//}
	//try {
	//	_bstr_t SQL = "DELETE FROM Books WHERE Isbn = '" + (_bstr_t)isbn + "';";
	//	BOOL status = this->ExecuteSQL(SQL);
	//	//this->ExitConnect();
	//	if (status)
	//		return "已删除";
	//	else
	//		return "删除出错";
	//}
	//catch (std::exception e) {
	//	return e.what();
	//}
	return "删除图书";
}

bool Lib_db::IsExits(char* isbn) {
	//if (isbn == NULL) {
	//	return false;
	//}
	//if (m_pConnection == NULL) {
	//	this->OnInitADOConn();
	//}
	////if (!this->IsConnected()) {
	////	this->OpenConnect();
	////}
	//try {
	//	_bstr_t SQL = "SELECT * FROM Books WHERE Isbn = '" + (_bstr_t)isbn + "';";
	//	m_pRecordset = this->GetRecordSet(SQL);
	//	//this->ExitConnect();
	//	//this->CloseConnect();
	//	//std::cout << m_pRecordset->GetRecordCount() << std::endl;
	//	if (this->m_pRecordset->GetRecordCount())
	//		return true;
	//	else
	//		return false;
	//}
	//catch (_com_error e) {
	//	//std::cout << e.Description() << std::endl;
	//	return false;
	//}
	return true;
}

std::string Lib_db::Frame_display(std::string& m_pset) {
	/*if (m_pset == NULL) {
		return "error";
	}
	try {
		m_pset->MoveFirst();
		std::map<int, _bstr_t> result_map;
		int tag = 1;
		while (!m_pset->adoEOF){
			_bstr_t result = "";
			result += (_bstr_t)m_pset->GetCollect("Name") + "\t";
			result += (_bstr_t)m_pset->GetCollect("Isbn") + "\t";
			result += (_bstr_t)m_pset->GetCollect("Price") + "\t";
			result += (_bstr_t)m_pset->GetCollect("Author");
			result_map.insert(std::map<int, _bstr_t>::value_type(tag++, result));
			m_pset->MoveNext();
		}
		_bstr_t result = "";

		for (std::map<int, _bstr_t>::iterator it = result_map.begin(); it != result_map.end(); it++) {
			result += (_bstr_t)it->first + "\t" + it->second + "\n";
		}

		return result;
	}
	catch (_com_error e) {
		return e.Description();
	}*/
	return "显示";
}