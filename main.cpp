#include "wxClass.h"
#include "ConnDB.h"

/*主程序相关函数实现*/

bool Manage_Books::OnInit() {
	Main_Menu *main_menu = new Main_Menu(wxT("图书管理系统"));
	main_menu->Show();
	return true;
}

/********************************************************************************/

/*主菜单相关函数实现*/

/*
在调用子窗口的时候如果不关闭主窗口，主窗口照样可以调出新的子窗口，同时访问数据库的话会涉及到数据的并发处理
*/

Main_Menu::Main_Menu(const wxString&title) :wxFrame(NULL, wxID_ANY, title, wxPoint(500, 80), wxSize(400, 560)) {
	//设置图标
	SetIcon(wxIcon(wxT("icon.png")));

	wxPanel* panel = new wxPanel(this, wxID_ANY);
	
	//设置标题
	wxStaticText* tag = new wxStaticText(panel, 6000, wxT("图书管理系统"), wxPoint(100, 10), wxSize(200, 30));
	wxButton* btn1 = new wxButton(panel, 6001, wxT("添加图书"), wxPoint(100, 60), wxSize(200, 50));
	wxButton* btn2 = new wxButton(panel, 6002, wxT("浏览全部"), wxPoint(100, 130), wxSize(200, 50));
	wxButton* btn3 = new wxButton(panel, 6003, wxT("精确查找"), wxPoint(100, 210), wxSize(200, 50));
	wxButton* btn4 = new wxButton(panel, 6004, wxT("模糊查找"), wxPoint(100, 290), wxSize(200, 50));
	wxButton* btn5 = new wxButton(panel, 6005, wxT("删除图书"), wxPoint(100, 370), wxSize(200, 50));

	//wxButton* close = new wxButton(panel, 6006, wxT("退出程序"), wxPoint(100, 450), wxSize(200, 50));
	
	/*以下为菜单区域*/

	wxMenu* fileMenu = new wxMenu;
	wxMenu* helpMenu = new wxMenu;
	helpMenu->Append(wxID_ABOUT, wxT("关于\tF1"), wxT("关于该系统"));
	fileMenu->Append(wxID_EXIT, wxT("退出\tAlt-X"), wxT("退出系统"));
	wxMenuBar *menuBar = new wxMenuBar();
	menuBar->Append(fileMenu, wxT("文件"));
	menuBar->Append(helpMenu, wxT("帮助"));
	SetMenuBar(menuBar);
	CreateStatusBar(2);
	SetStatusText(wxT("2020年11月"));
}

void Main_Menu::Close_this(wxCommandEvent& event) {
	this->Close();
}

void Main_Menu::OnAbout(wxCommandEvent& event) {
	wxString msg;
	msg.Printf(wxT("界面开发平台：%s"),
		wxVERSION_STRING);

	wxMessageBox(msg, wxT("关于"),
		wxOK | wxICON_INFORMATION, this);
}

void Main_Menu::func_insertbook(wxCommandEvent& event) {
	//this->Show(false);
	InsertBook *insert_frame = new InsertBook(this, wxT("图书入库"), wxT("入库"));
	insert_frame->Show(true);
}

void Main_Menu::func_diplaybooks(wxCommandEvent& event) {
	DisplayBooks *display_frame = new DisplayBooks(this, wxT("显示图书"), wxT("显示所有"));
	display_frame->Show(true);
}

void Main_Menu::func_searchbyisbn(wxCommandEvent& event) {
	SearchBookByISBN *search_frame = new SearchBookByISBN(this, wxT("精确查找"), wxT("查找"));
	search_frame->Show(true);
}

void Main_Menu::func_searchbyname(wxCommandEvent& event) {
	SearchBookByName *search_frame = new SearchBookByName(this, wxT("模糊查找"), wxT("查找"));
	search_frame->Show(true);
}

void Main_Menu::func_deletebyisbn(wxCommandEvent& event) {
	DeleteBookByISBN *delete_frame = new DeleteBookByISBN(this, wxT("删除图书"), wxT("删除"));
	delete_frame->Show(true);
}
/********************************************************************************/

/*以下为各项功能类的函数实现*/

//0.功能基类的函数实现

//baseClass::baseClass(const wxString& title, const wxString&btn_text) :wxFrame(NULL, wxID_ANY, title, wxPoint(500, 80), wxSize(400, 560)) {
//	panel = new wxPanel;
//	wxStaticText *text = new wxStaticText(panel, wxID_EXECUTE, title, wxPoint(100, 20), wxSize(200, 30));
//
//	apply = new wxButton(panel, wxID_APPLY, btn_text, wxPoint(300, 470), wxSize(150, 50));
//	cancel = new wxButton(panel, wxID_CANCEL, wxT("取消"), wxPoint(220, 470), wxSize(150, 50));
//
//	display = new wxStaticText(panel, 7000, wxT(""), wxPoint(30, 270), wxSize(340, 180));
//
//	CreateStatusBar(1);
//	SetStatusText(wxT("结果状态显示栏"));
//
//}
//
//void baseClass::Close_this(wxCommandEvent& event) {
//	Close();
//}

//1.添加图书

InsertBook::InsertBook(Main_Menu* m, const wxString& title, const wxString& btn_text) :wxFrame(m, wxID_ANY, title, wxPoint(500, 80), wxSize(400, 560)) {
	wxPanel *panel = new wxPanel(this);
	wxStaticText *text = new wxStaticText(panel, wxID_EXECUTE, title, wxPoint(150, 20), wxSize(200, 30));

	wxStaticText *label1 = new wxStaticText(panel, wxID_ANY, wxT("书名："), wxPoint(30, 50), wxSize(50, 20));
	wxStaticText *label2 = new wxStaticText(panel, wxID_ANY, wxT("ISBN："), wxPoint(30, 80), wxSize(50, 20));
	wxStaticText *label3 = new wxStaticText(panel, wxID_ANY, wxT("价格："), wxPoint(30, 110), wxSize(50, 20));
	wxStaticText *label4 = new wxStaticText(panel, wxID_ANY, wxT("作者："), wxPoint(30, 140), wxSize(50, 20));

	name = new wxTextCtrl(panel, 7001, wxT(""), wxPoint(100, 50), wxSize(210, 20));
	isbn = new wxTextCtrl(panel, 7002, wxT(""), wxPoint(100, 80), wxSize(210, 20));
	price = new wxTextCtrl(panel, 7003, wxT(""), wxPoint(100, 110), wxSize(210, 20));
	author = new wxTextCtrl(panel, 7004, wxT(""), wxPoint(100, 140), wxSize(210, 20));

	wxButton* apply = new wxButton(panel, wxID_APPLY, btn_text, wxPoint(30, 450), wxSize(100, 40));
	wxButton* cancel = new wxButton(panel, wxID_CANCEL, wxT("取消"), wxPoint(230, 450), wxSize(100, 40));
	wxStaticText* pre_label = new wxStaticText(panel, wxID_ANY, wxT("这是显示区域:"), wxPoint(30, 180), wxSize(100, 20));
	display = new wxStaticText(panel, wxID_ANY, wxT(""), wxPoint(30, 200), wxSize(340, 230));

	CreateStatusBar(1);
	SetStatusText(wxT("结果状态显示栏"));
}

void InsertBook::func_insert(wxCommandEvent& event) {
	char get_name[NUM1];
	char get_isbn[NUM1];
	char get_price[NUM2];
	char get_author[NUM2];
	strncpy(get_name, name->GetValue(), NUM1);
	strncpy(get_isbn, isbn->GetValue(), NUM1);
	strncpy(get_price, price->GetValue(), NUM2);
	strncpy(get_author, author->GetValue(), NUM2);

	CBook *book = new CBook(get_name, get_isbn, atof(get_price), get_author);
	Lib_db *db = new Lib_db;
	std::string result = db->InsertItem(book) + "\n操作后的结果：\n";
	result += db->ShowAll();
	db->ExitConnect();

	display->SetLabel(result);
	
	SetStatusText(wxT("操作完成。"));
}

void InsertBook::func_close(wxCommandEvent& event) {
	Close();
}

//2.展示所有图书

DisplayBooks::DisplayBooks(Main_Menu* m, const wxString& title, const wxString& btn_text) :wxFrame(m, wxID_ANY, title, wxPoint(500, 80), wxSize(400, 560)) {
	wxPanel *panel = new wxPanel(this);
	wxStaticText *text = new wxStaticText(panel, wxID_EXECUTE, title, wxPoint(150, 20), wxSize(200, 30));
	
	wxButton* apply = new wxButton(panel, wxID_APPLY, btn_text, wxPoint(30, 450), wxSize(100, 40));
	wxButton* cancel = new wxButton(panel, wxID_CANCEL, wxT("取消"), wxPoint(230, 450), wxSize(100, 40));
	wxStaticText* label2 = new wxStaticText(panel, wxID_ANY, wxT("这是显示区域:"), wxPoint(30, 100), wxSize(100, 20));
	display = new wxStaticText(panel, 7000, wxT(""), wxPoint(30, 120));
	CreateStatusBar(1);
	SetStatusText(wxT("结果状态显示栏"));
}

void DisplayBooks::func_display(wxCommandEvent& event) {

	Lib_db *db = new Lib_db;
	std::string result = db->ShowAll();
	display->SetLabel(result);
	db->ExitConnect();

	SetStatusText(wxT("操作完成。"));

}

void DisplayBooks::func_close(wxCommandEvent& event) {
	Close();
}

//3.ISBN查找图书

SearchBookByISBN::SearchBookByISBN(Main_Menu* m, const wxString& title, const wxString& btn_text) :wxFrame(m, wxID_ANY, title, wxPoint(500, 80), wxSize(400, 560)) {
	wxPanel *panel = new wxPanel(this);
	wxStaticText *text = new wxStaticText(panel, wxID_EXECUTE, title, wxPoint(150, 20), wxSize(200, 30));

	wxStaticText *label1 = new wxStaticText(panel, wxID_ANY, wxT("ISBN："), wxPoint(30, 50), wxSize(50, 20));
	isbn = new wxTextCtrl(panel, 7001, wxT(""), wxPoint(100, 50), wxSize(210, 20));

	wxButton* apply = new wxButton(panel, wxID_APPLY, btn_text, wxPoint(30, 450), wxSize(100, 40));
	wxButton* cancel = new wxButton(panel, wxID_CANCEL, wxT("取消"), wxPoint(230, 450), wxSize(100, 40));
	wxStaticText* label2=new wxStaticText(panel, wxID_ANY, wxT("这是显示区域:"), wxPoint(30, 100), wxSize(100, 20));
	display = new wxStaticText(panel, 7000, wxT(""), wxPoint(30, 120), wxSize(340, 300));

	CreateStatusBar(1);
	SetStatusText(wxT("结果状态显示栏"));
}

void SearchBookByISBN::func_search(wxCommandEvent& event) {
	char get_isbn[ISBN_SIZE];
	strncpy(get_isbn, isbn->GetValue(), ISBN_SIZE);
	Lib_db *db = new Lib_db;
	std::string result = db->SearchByIsbn(get_isbn);
	db->ExitConnect();
	display->SetLabel(result);
	SetStatusText(wxT("查找完成"));
}

void SearchBookByISBN::func_close(wxCommandEvent& event) {
	Close();
}

//4.模糊查找图书

SearchBookByName::SearchBookByName(Main_Menu* m, const wxString& title, const wxString& btn_text) :wxFrame(m, wxID_ANY, title, wxPoint(500, 80), wxSize(400, 560)) {
	wxPanel *panel = new wxPanel(this);
	wxStaticText *text = new wxStaticText(panel, wxID_EXECUTE, title, wxPoint(150, 20), wxSize(200, 30));

	wxStaticText *label1 = new wxStaticText(panel, wxID_ANY, wxT("书名："), wxPoint(30, 50), wxSize(50, 20));
	name = new wxTextCtrl(panel, 7001, wxT(""), wxPoint(100, 50), wxSize(210, 20));

	wxButton* apply = new wxButton(panel, wxID_APPLY, btn_text, wxPoint(30, 450), wxSize(100, 40));
	wxButton* cancel = new wxButton(panel, wxID_CANCEL, wxT("取消"), wxPoint(230, 450), wxSize(100, 40));
	wxStaticText* label2 = new wxStaticText(panel, wxID_ANY, wxT("这是显示区域:"), wxPoint(30, 100), wxSize(100, 20));
	display = new wxStaticText(panel, 7000, wxT(""), wxPoint(30, 120), wxSize(340, 300));

	CreateStatusBar(1);
	SetStatusText(wxT("结果状态显示栏"));
}

void SearchBookByName::func_search(wxCommandEvent& event) {
	char get_name[NAME_SIZE];
	strncpy(get_name, name->GetValue(), NAME_SIZE);
	Lib_db *db = new Lib_db;
	std::string result = db->SearchByName(get_name);
	db->ExitConnect();
	display->SetLabel(result);
	SetStatusText("查找完成。");
}

void SearchBookByName::func_close(wxCommandEvent& event) {
	Close();
}

//5.删除图书

DeleteBookByISBN::DeleteBookByISBN(Main_Menu* m, const wxString& title, const wxString& btn_text) :wxFrame(m, wxID_ANY, title, wxPoint(500, 80), wxSize(400, 560)) {
	wxPanel *panel = new wxPanel(this);
	wxStaticText *text = new wxStaticText(panel, wxID_EXECUTE, title, wxPoint(150, 20), wxSize(200, 30));

	wxStaticText *label1 = new wxStaticText(panel, wxID_ANY, wxT("ISBN："), wxPoint(30, 50), wxSize(50, 20));
	isbn = new wxTextCtrl(panel, 7001, wxT(""), wxPoint(100, 50), wxSize(210, 20));

	wxButton* apply = new wxButton(panel, wxID_APPLY, btn_text, wxPoint(30, 450), wxSize(100, 40));
	wxButton* cancel = new wxButton(panel, wxID_CANCEL, wxT("取消"), wxPoint(230, 450), wxSize(100, 40));
	wxStaticText* label2 = new wxStaticText(panel, wxID_ANY, wxT("这是显示区域:"), wxPoint(30, 100), wxSize(100, 20));
	display = new wxStaticText(panel, 7000, wxT(""), wxPoint(30, 120), wxSize(340, 300));

	CreateStatusBar(1);
	SetStatusText(wxT("结果状态显示栏"));
}

void DeleteBookByISBN::func_delete(wxCommandEvent& event) {
	char get_isbn[ISBN_SIZE];
	strncpy(get_isbn, isbn->GetValue(), ISBN_SIZE);
	Lib_db* db = new Lib_db;
	std::string result = db->DeleteItem(get_isbn) + "\n操作后的结果：\n";
	result += db->ShowAll();
	db->ExitConnect();
	display->SetLabel(result);
	SetStatusText("操作完成。");
}

void DeleteBookByISBN::func_close(wxCommandEvent& event) {
	Close();
}
