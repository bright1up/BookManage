#include "Book.h"
#include <cstring>
CBook::CBook(char* cName, char* cIsbn, float cPrice, char* cAuthor) {
	strcpy(m_cName, cName);
	strcpy(m_cIsbn, cIsbn);
	m_cPrice = cPrice;
	strcpy(m_cAuthor, cAuthor);
}

char* CBook::GetName() {
	return m_cName;
}

char* CBook::GetIsbn() {
	return m_cIsbn;
}

float CBook::GetPrice() {
	return m_cPrice;
}

char* CBook::GetAuthor() {
	return m_cAuthor;
}
