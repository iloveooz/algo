/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 3. ��������� �������                              *
*          3.1. ������� ������������� �����                    *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : ListString.cpp                                   *
*  �������� : ������������� ������ � ���� ������ ���������,    *
*             ���������� ��������� ������: ���������� �������� *
***************************************************************/

#include "ListString.h"

//--------------------------------------------------
// ����������� ��� �������� ������� ��������� ������
// �������� ������, ����� �� �� ��������� ������
// ITEM_SIZE, � ��������� �� � ������ ���������
//--------------------------------------------------
ListString::StringItem::StringItem(const char *src, StringItem *nextItem) {
  // �������, ��� ������ �������� ���� �� ���� ������
  int len = strlen(src);
  if (len > ITEM_SIZE) {
    // ����������� ����� ������������:
    nextItem = new StringItem(src + ITEM_SIZE, nextItem);
  }
  // �������� ����� ������ ��� �� ���������� ��������
  size = (len < ITEM_SIZE ? len : ITEM_SIZE);
  // ���������� ��������
  strncpy(symbols, src, size);
  next = nextItem;
}

//-------------------------------------------------------------
// ������� ������������ ������, ������� ���������� ������,
// � ��������� ������
//-------------------------------------------------------------
void ListString::destroy() {
  StringItem * current = first, // ������� ������� ������
             * pred = NULL;     // ���������� ������� ������
  // ���� �� ��������� ������
  while (current) {
    pred = current;
    current = current->next;
    delete pred;
  }
  // ��������� ������
  first = NULL;
}

//-------------------------------------------------------------
// ������� ������ ���������� �������� � ������������� ������
//-------------------------------------------------------------
ListString::StringItem * ListString::getLast() const {
  StringItem * current = first, // ������� ������� ������
             * pred = NULL;     // ���������� ������� ������
  // ���� �� ��������� ������
  while (current) {
    pred = current;
    current = current->next;
    // ��������, ������ �� ����������� ������� ��������� pred � current
    while (current && pred->size + current->size <= ITEM_SIZE) {
      // ����������� ��������
      strncpy(pred->symbols + pred->size, current->symbols, current->size);
      // ��������� �������� pred
      pred->size += current->size;
      pred->next = current->next;
      StringItem *toDelete = current;
      current = current->next;
      // ����������� ������� ��������
      delete toDelete;
    }
  }
  // ������� ����������
  return pred;
}

//-------------------------------------------------------------
// ������� ������ ������� ������� ������ � �������� ��������
//-------------------------------------------------------------
ListString::SymbolPosition ListString::findPos(int index) const {
  if (index < 0) {
    throw IndexException("String indexing with index < 0");
  }

  // ���������� ��������, ������� ���� ��� ���������:
  unsigned short curIndex = (unsigned short)index;

  // ��������� �� ������� �������:
  StringItem * current = first;  

  // ���� �� ��������� ������
  while (current && current->size <= curIndex) {
    curIndex -= current->size;
    current = current->next;
  }

  if (current == NULL) { // ������ ���������, � ������ ��� �� ���������
    throw IndexException("String indexing with index greater than string length");
  }
  // ������ ����������:
  return SymbolPosition(current, curIndex);
}

//-------------------------------------------------------------
// ������� �������������� ������ � ����������� ������������� ��
//-------------------------------------------------------------
ListString::operator char* () const {
  // ����� ��� ������ �������� ������:
  char * res = new char[this->length() + 1];
  // ��������� �������� ����� ��� ������ ��������
  char * ptr = res;

  // ���� �� ��������� ������
  for (StringItem * current = first; current; current = current->next) {
    // ������ � ����� �������� �� ���������� ��������
    strncpy(ptr, current->symbols, current->size);
    ptr += current->size;
  }
  *ptr = 0;
  return res;
}

//-------------------------------------------------------------
// ������� ���������� ����� ������
//-------------------------------------------------------------
int ListString::length() const {
  int length = 0;  // ���������� ��� ���������� �����
  // ���� �� ��������� ������
  for (StringItem * current = first; current; current = current->next) {
    length += current->size;
  }
  return length;
}

//-------------------------------------------------------------
// �������� ���������� ������
//-------------------------------------------------------------
char & ListString::operator [] (int index) {
  // ���������� ������� ������� � ������ � ������� ������� findPos
  SymbolPosition sp = findPos(index);
  // ������ ������� � �������������� ����������� �������
  return sp.item->symbols[sp.pos];
}

//-------------------------------------------------------------
// �������� ���������� ������
//-------------------------------------------------------------
char ListString::operator [] (int index) const {
  // ���������� ������� ������� � ������ � ������� ������� findPos
  SymbolPosition sp = findPos(index);
  // ������ ������� � �������������� ����������� �������
  return sp.item->symbols[sp.pos];
}

//-------------------------------------------------------------
// �������� ������������ � ������������ ������
//-------------------------------------------------------------
ListString & ListString::operator = (const ListString & src) {
  // ������� �������� ���������� � ���� char* ��������� ���
  // ������� ������ � ���������� �����, � ����� ��������
  // ������������ �������� ����� �������� ������.
  destroy();
  return *this = (char*)src;
}

//-------------------------------------------------------------
// �������� ������������ � ������������ ������
//-------------------------------------------------------------
ListString & ListString::operator = (const char * src) {
  destroy();
  if (src && src[0]) {
    first = new StringItem(src);
  }
  return *this;
}

//-------------------------------------------------------------
// �������� ��������� ��������� � �� ������������
//-------------------------------------------------------------
ListString ListString::substr(int begin, int end) const {
  // ��������� ������������ ������� ����������
  int len = length();
  if (begin < 0 || begin > len) {
    throw IndexException("Wrong start index in substr");
  } else if (end > len || end < begin) {
    end = len;
  }

  // ���� ����������� �������� ������ � ������������� �����
  int leftSymbols = end - begin;

  // ������� ���������, ���� �� ������ ���-�� ����������
  if (leftSymbols == 0) return ListString();

  // ������� ��������� ������� ��� ����������� � ���������� �����
  SymbolPosition startPos = findPos(begin);
  char * buffer = new char[leftSymbols+1];
  char * ptr = buffer;

  // ���� ������������, ���� ��� ���� ��� ����������
  while (leftSymbols) {
    // ���������, ������� �������� ����� ����� �� �������� ��������
    int lenToCopy = startPos.item->size - startPos.pos;
    if (leftSymbols < lenToCopy) lenToCopy = leftSymbols;

    // �������� �������
    strncpy(ptr, startPos.item->symbols + startPos.pos, lenToCopy);
    ptr += lenToCopy;
    leftSymbols -= lenToCopy;

    // ������������ � ���������� ��������
    startPos.item = startPos.item->next;
    startPos.pos = 0;
  }
  // ���������� � ����� ������ ����� ������
  *ptr = 0;

  // ������� ����� ������ �� ��������, ���������� � �����
  ListString result(buffer);
  // ���������� �����
  delete buffer;
  // ���������� ���������
  return result;
}

//-------------------------------------------------------------
// ���������� ������� � ����� ������
//-------------------------------------------------------------
ListString & ListString::operator += (char ch) {
  StringItem * last = getLast();  // ��������� ������� ������
  if (last == NULL) {
    // ����� ������� ���������� ������ � ������������ � ������
    first = new StringItem(&ch);
  } else if (last->size < ITEM_SIZE) {
    // ������ ������ ����������� � ��������� ������� ������
    last->symbols[last->size++] = ch;
  } else {
    // ����� ������� �������������� � ����� ������
    last->next = new StringItem(&ch);
  }
  return *this;
}

//-------------------------------------------------------------
// ���������� ������ ������ ��������� � ����� ������
// ��������: �������� �������� ������ �� ����������!
//-------------------------------------------------------------
ListString & ListString::operator += (const ListString & src) {
  StringItem * last = getLast();  // ��������� ������� ������
  if (last == NULL) {
    // ���������� ��������� �� ������ ������� ������
    first = src.first;
  } else {
    // ����� �������� �������������� � ����� ������
    last->next = src.first;
  }
  return *this;
}

//-------------------------------------------------------------
// ���������� ����� �������� � ����� ������
//-------------------------------------------------------------
ListString & ListString::operator += (const char * src) {
  return *this += *(new ListString(src));
}

//-------------------------------------------------------------
// ������� ��������� ������ ������ ������
//-------------------------------------------------------------
ListString & ListString::insert (int index, const ListString & src) {
  if (index < 0) {
    throw IndexException("insert: negative insertion index");
  }
  // ���������� ������� �������� � �������� ��������
  // �������� ��� ��, ��� � �������� findPos
  StringItem * current = first;  // ��������� �� ������� �������
  StringItem * pred = NULL;      // ��������� �� ���������� �������
  int curIndex = index;          // ���������� ��� ������� ��������
  while (current && current->size <= curIndex) {
    curIndex -= current->size;
    pred = current;
    current = current->next;
  }
  // �������� ������������ ������� �������
  if (current == NULL && curIndex != 0) {
    throw IndexException("insert: insertion index is too big");
  }
  if (src.first == NULL) {
    // ����������, � ���������-�� ���� ������!
    // �� ������������ ������� ���� ���� ��������� ��� �����
    return * this;
  }
  // ��������� ������� ������������ ���������:
  StringItem * lastInSource = src.getLast();

  if (curIndex > 0) {
    // ��������� ������� ���� ��������� �� ��� �����.
    // ��������� ������ �� ���� ������
    char * buffer = new char[current->size - curIndex + 1];
    strncpy(buffer, current->symbols + curIndex, current->size - curIndex);
    buffer[current->size - curIndex] = 0;
    StringItem * newItem = new StringItem(buffer, current->next);
    // ������ ��������� ����� ������ �����
    current->size = (unsigned short)curIndex;
    // ��������� ����� ������� ������ ����� ����� ����� �������
    current->next = newItem;
    pred = current;
    current = newItem;
  }
  // ������������� ������������ ���������� � ������:
  if (pred == NULL) {
    first = src.first;
  } else {
    pred->next = src.first;
  }
  lastInSource->next = current;
  return *this;
}

//-------------------------------------------------------------
// ������� ������ � ����������� ������������� ������ ������
//-------------------------------------------------------------
ListString & ListString::insert (int index, const char * src) {
  return insert(index, *(new ListString(src)));
}

//-------------------------------------------------------
// ��� ��������, �������� � �������� ���������� �����
// ������������ ��������� ������ (����� ���������)
//-------------------------------------------------------

ostream & operator <<= (ostream & out, const ListString & src) {
  ListString::StringItem * current = src.first;
  out << '[';
  while (current) {
    out << current->size;
    if (current = current->next) {
      out << ", ";
    }
  }
  return out << ']';
}
