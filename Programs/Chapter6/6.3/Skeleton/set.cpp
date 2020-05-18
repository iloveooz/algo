/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 6. ��������� ��������� ������� ����������         *
*          6.2. ����� ���������� �����                         *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : set.cpp                                          *
*  �������� : ���������� ������ Set                            *
***************************************************************/

// ����������� �������������� ��������:
#include <stdexcept>

#include "set.h"

using namespace std;

// �����������
Set::Set(int min, int max) {
  // ������������ min < max
  if (min > max) {
    minElem = max;
    maxElem = min;
  } else {
    minElem = min;
    maxElem = max;
  }
  int num = maxElem - minElem + 1;     // ���������� ����� � �����
  numWords = (num + 15) >> 4;          // ���������� ���� (WORDs)
  elems = new WORD[numWords];
  // ��������� �����:
  for (int i = 0; i < numWords; i++) {
    elems[i] = 0;
  }
}

// ����������� �����������
Set::Set(const Set & s) {
  minElem = s.minElem;
  maxElem = s.maxElem;
  elems = new WORD[numWords = s.numWords];
  for (int i = 0;  i < numWords;  i++) {
    elems[i] = s.elems[i];
  }
}

// ����������
Set::~Set() {
  delete[] elems;
}

// ������� �������� �������������� �������� ���������
bool Set::has(int n) const {
  if (n > maxElem || n < minElem)
    return false;    // ������� ������� �� ������� ���������
  // "�����" ��������:
  int word = (n - minElem) >> 4;
  int bit = (n - minElem) & 15;
  return (elems[word] & (1 << bit)) != 0;
}

// ���������� �������� � ���������
Set & Set::operator |= (int n) {
  if (n <= maxElem && n >= minElem) {
    // "�����" ��������:
    int word = (n - minElem) >> 4;
    int bit = (n - minElem) & 15;
    elems[word] |= (1 << bit);
  } else {
    throw out_of_range("Cannot add an element: it is out of range");
  }
  return *this;
}

// ���������� ����� �� ��������� ���������
Set & Set::addScale(int from, int to) {
  if (from < minElem || to > maxElem) {
    throw out_of_range("Cannot add an element: it is out of range");
  } else if (from <= to) {
    // "�����" ������� ��������
    int wordFrom = (from - minElem) >> 4;
    int bitFrom = (from - minElem) & 15;
    // "�����" ���������� ��������
    int wordTo = (to - minElem) >> 4;
    int bitTo = (to - minElem) & 15;
    for (int i = wordFrom + 1; i < wordTo; i++) {
      elems[i] = 0xFFFF;
    }
    if (wordFrom == wordTo) {
      elems[wordFrom] |= (0xFFFF << bitFrom) & ~(0xFFFF << (bitTo+1));
    } else {
      elems[wordFrom] |= (0xFFFF << bitFrom);
      elems[wordTo] |= ~(0xFFFF << (bitTo+1));
    }
  }
  return *this;
}

// �������� ����� �� ��������� ���������
Set & Set::remScale(int from, int to) {
  if (from < minElem || to > maxElem) {
    throw out_of_range("Cannot add an element: it is out of range");
  } else if (from <= to) {
    // "�����" ������� ��������
    int wordFrom = (from - minElem) >> 4;
    int bitFrom = (from - minElem) & 15;
    // "�����" ���������� ��������
    int wordTo = (to - minElem) >> 4;
    int bitTo = (to - minElem) & 15;
    for (int i = wordFrom + 1; i < wordTo; i++) {
      elems[i] = 0;
    }
    if (wordFrom == wordTo) {
      elems[wordFrom] &= ~(0xFFFF << bitFrom) | (0xFFFF << bitTo);
    } else {
      elems[wordFrom] &= ~(0xFFFF << bitFrom);
      elems[wordTo] &= (0xFFFF << bitTo);
    }
  }
  return *this;
}

// ���������� ��������� � ��������� (����������� ��������)
Set & Set::operator |= (const Set & other) {
  if (other.minElem != minElem || other.maxElem != maxElem) {
    throw out_of_range("Sets incomparable");
  }
  for (int i = 0;  i < numWords;  i++) {
    elems[i] |= other.elems[i];
  }
  return *this;
}

// ����������� ��������
Set & Set::operator &= (const Set & other) {
  if (other.minElem != minElem || other.maxElem != maxElem) {
    throw out_of_range("Sets incomparable");
  }
  for (int i = 0;  i < numWords;  i++) {
    elems[i] &= other.elems[i];
  }
  return *this;
}

// �������� �������� �� ���������
Set & Set::operator -= (int n) {
  if (n <= maxElem && n >= minElem) {
    // "�����" ��������:
    int word = (n - minElem) >> 4;
    int bit = (n - minElem) & 15;
    elems[word] &= ~(1 << bit);
  }
  return *this;
}

// �������� ��������� �� ��������� (�������� ��������)
Set & Set::operator -= (const Set & other) {
  if (other.minElem != minElem || other.maxElem != maxElem) {
    throw out_of_range("Sets incomparable");
  }
  for (int i = 0;  i < numWords;  i++) {
    elems[i] &= ~other.elems[i];
  }
  return *this;
}

// �������� (���������� ����������) ���������
Set & Set::inverse() {
  for (int i = 0;  i < numWords;  i++) {
    elems[i] = ~elems[i];
  }
  return *this;
}

// ������� ����� ��������� ���������
int Set::card() const {
  int c = 0;
  for (int i = 0;  i < numWords;  i++) {
    WORD elem = elems[i];
    while (elem != 0) {
      c += (elem & 1);
      elem >>= 1;
    }
  }
  return c;
}

// �������� ������� ���������
bool Set::empty() const {
  for (int i = 0;  i < numWords;  i++) {
    if (elems[i]) return false;
  }
  return true;
}


Iterator<int> & Set::SetIterator::operator ++() {
  if (left == 0) return *this;
  --left;
  while (++nextBit < 16 && ((set->elems)[nextWord] & (1 << nextBit)) == 0) ;
  if (nextBit < 16) return *this;
  while (++nextWord < set->numWords && (set->elems)[nextWord] == 0) ;
  nextBit = -1;
  while (++nextBit < 16 && ((set->elems)[nextWord] & (1 << nextBit)) == 0) ;
  return *this;
}

// �������� ��� �����������, ������������� � ���� �����������
// ���������� (��� ����������� ������)

// ����������� ��������
const Set & operator | (const Set & s1, const Set & s2) {
  return Set(s1) |= s2;
}

// ����������� ��������
const Set & operator & (const Set & s1, const Set & s2) {
  return Set(s1) &= s2;
}

// �������� ��������
const Set & operator - (const Set & s1, const Set & s2) {
  return Set(s1) -= s2;
}

// ���������� ���������
const Set & operator - (const Set & s) {
  return Set(s).inverse();
}
