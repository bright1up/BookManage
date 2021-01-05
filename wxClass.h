#pragma once
#include"wx/wx.h"
#include"ConnDB.h"
#include"Book.h"

//主程序类
class Manage_Books :public wxApp {
public:
	virtual bool OnInit();
};



/********************************************************************************/

/*以下部分为窗口类*/



//主菜单类
class Main_Menu :public wxFrame {
public:
	Main_Menu(const wxString&);
	void Close_this(wxCommandEvent&);
	void func_insertbook(wxCommandEvent&);
	void func_diplaybooks(wxCommandEvent&);
	void func_searchbyisbn(wxCommandEvent&);
	void func_searchbyname(wxCommandEvent&);
	void func_deletebyisbn(wxCommandEvent&);
	void OnAbout(wxCommandEvent&);
private:
	DECLARE_EVENT_TABLE()
};

//0.设置操作的基类

//class baseClass :public wxFrame {
//public:
//	/*基类函数创建窗口，使用子类给定的标题和按钮的文本构造不同的窗口；
//	每个子类中进行重写操作，由于子类函数需要绑定不同的响应窗口，所以还是由子窗口实现事件与函数的绑定。
//	*/
//	baseClass(const wxString&, const wxString&);
//	virtual void btn_func(wxCommandEvent&);
//	void Close_this(wxCommandEvent&);
//protected:
//	wxPanel *panel;
//	wxButton *apply;
//	wxButton *cancel;
//	wxStaticText *display;
//private:
//	DECLARE_EVENT_TABLE()
//};

//1.添加图书

/*采用baseClass会出现问题，现在直接使用各个窗体*/


class InsertBook :public wxFrame {
public:
	InsertBook(Main_Menu*, const wxString&title, const wxString&btn_text);
	void func_insert(wxCommandEvent&);
	void func_close(wxCommandEvent&);
private:
	wxTextCtrl *name;
	wxTextCtrl *isbn;
	wxTextCtrl *price;
	wxTextCtrl *author;
	wxStaticText* display;
	static const int NUM1 = 50;
	static const int NUM2 = 30;
private:
	DECLARE_EVENT_TABLE()
};

//2.展示所有图书

class DisplayBooks :public wxFrame {
public:
	DisplayBooks(Main_Menu*, const wxString&title, const wxString&btn_text);
	void func_display(wxCommandEvent&);
	void func_close(wxCommandEvent&);
private:
	wxStaticText* display;
private:
	DECLARE_EVENT_TABLE()
};

//3.ISBN查找图书

class SearchBookByISBN :public wxFrame {
public:
	SearchBookByISBN(Main_Menu*, const wxString&title, const wxString&btn_text);
	void func_search(wxCommandEvent&);
	void func_close(wxCommandEvent&);
private:
	wxTextCtrl *isbn;
	wxStaticText* display;
	static const int ISBN_SIZE = 50;
private:
	DECLARE_EVENT_TABLE()
};

//4.模糊查找图书

class SearchBookByName :public wxFrame {
public:
	SearchBookByName(Main_Menu*, const wxString&title, const wxString&btn_text);
	void func_search(wxCommandEvent&);
	void func_close(wxCommandEvent&);
private:
	wxTextCtrl* name;
	wxStaticText* display;
	static const int NAME_SIZE = 50;
private:
	DECLARE_EVENT_TABLE()
};

//5.删除图书

class DeleteBookByISBN :public wxFrame {
public:
	DeleteBookByISBN(Main_Menu*, const wxString&title, const wxString&btn_text);
	void func_delete(wxCommandEvent&);
	void func_close(wxCommandEvent&);
private:
	wxTextCtrl* isbn;
	wxStaticText* display;
	static const int ISBN_SIZE = 50;
private:
	DECLARE_EVENT_TABLE()
};

/********************************************************************************/

/*以下部分为宏，主程序指明和事件表*/

//可以使用MyApp& wxGetApp()
//DECLARE_APP(Manage_Books)

//指明主程序
IMPLEMENT_APP(Manage_Books)

//主菜单的事件表
BEGIN_EVENT_TABLE(Main_Menu, wxFrame)
	EVT_MENU(wxID_EXIT, Main_Menu::Close_this)
	EVT_MENU(wxID_ABOUT,Main_Menu::OnAbout)
	EVT_BUTTON(6001,Main_Menu::func_insertbook)
	EVT_BUTTON(6002, Main_Menu::func_diplaybooks)
	EVT_BUTTON(6003, Main_Menu::func_searchbyisbn)
	EVT_BUTTON(6004, Main_Menu::func_searchbyname)
	EVT_BUTTON(6005, Main_Menu::func_deletebyisbn)
END_EVENT_TABLE()

//基类的事件表
//BEGIN_EVENT_TABLE(baseClass, wxFrame)
//	EVT_BUTTON(wxID_CANCEL, baseClass::Close_this)
//END_EVENT_TABLE()

//1.图书入库
BEGIN_EVENT_TABLE(InsertBook,wxFrame)
	EVT_BUTTON(wxID_APPLY,InsertBook::func_insert)
	EVT_BUTTON(wxID_CANCEL,InsertBook::func_close)
END_EVENT_TABLE()

//2.浏览图书
BEGIN_EVENT_TABLE(DisplayBooks, wxFrame)
	EVT_BUTTON(wxID_APPLY, DisplayBooks::func_display)
	EVT_BUTTON(wxID_CANCEL, DisplayBooks::func_close)
END_EVENT_TABLE()

//3.精确查找
BEGIN_EVENT_TABLE(SearchBookByISBN, wxFrame)
	EVT_BUTTON(wxID_APPLY, SearchBookByISBN::func_search)
	EVT_BUTTON(wxID_CANCEL, SearchBookByISBN::func_close)
END_EVENT_TABLE()

//4.模糊查找
BEGIN_EVENT_TABLE(SearchBookByName, wxFrame)
	EVT_BUTTON(wxID_APPLY, SearchBookByName::func_search)
	EVT_BUTTON(wxID_CANCEL, SearchBookByName::func_close)
END_EVENT_TABLE()

//5.删除图书
BEGIN_EVENT_TABLE(DeleteBookByISBN, wxFrame)
	EVT_BUTTON(wxID_APPLY, DeleteBookByISBN::func_delete)
	EVT_BUTTON(wxID_CANCEL, DeleteBookByISBN::func_close)
END_EVENT_TABLE()
