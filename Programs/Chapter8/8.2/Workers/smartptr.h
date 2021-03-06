/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 8. ������� ��� �������� ����������                *
*          8.2. ������ � ����������� ������ �� ��������� ����� *
*               � ������ ������                                *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : smartptr.h                                       *
*  �������� : ����������� ������� ��� ���������� "�����"       *
*             ����������                                       *
***************************************************************/

#ifndef __SMART_PTR
#define __SMART_PTR

#include <stdlib.h>

//--------------------------------------------------------------
// ������ RefCount ������������ ���� �� ��������� � ��������
// ������ �� ���� ���������. ����������� ������ �������� ���������
//--------------------------------------------------------------
template <class Object>
class RefCount {
  Object * obj;    // ��������� �� ������
  int cnt;         // ������� ���������� ������

public :
  // ����������� �������������� ������� ������,
  // ������������ ��� ������ �������
  RefCount(Object * o) : obj(o), cnt(1) {}
  
  // ����������� ������ ������, ��������� � ������� ����������� �������
  // ������ RefCount ��������� �� ������ ��� ������ ���� ���������
  ~RefCount() {}

  // ������� ������������� ������ ����������� �������� ��������
  void addRef() { ++cnt; }

  // ������� ������������ �� ������ ��������� �������� ��������
  // ������, �� � ���������� ������, ���� ���� ������� ���� ����� ����.
  void release() {
    if (--cnt == 0) {
      delete obj;   // ������������ ������, �� ������� ����� ���� ������
      delete this;  // ������������ � ��� ������ ������ RefCount
    }
  }

  // ������ � ������� ���������� � ���� ��������� ���������� � ����
  operator Object*() const { return obj; }
};

//--------------------------------------------------------------
// ������ SmartPtr ������������ "�����" ���������. �� ����������
// ������������� ������� ������ � �������� � ��� ��� ����������
// �������� ������������ � ����������� ���������.
//--------------------------------------------------------------
template <class Object>
class SmartPtr {
  RefCount<Object> * ptr;   // ������������� ������� ������

public :
  // ����������� ������� ������� ������ � ���������� ��������� �� ������.
  // ���� �������� ��������� ����, �� ��������� "������ ������"
  SmartPtr(Object * o = NULL) {
    if (o == NULL) {
      ptr = NULL;
    } else {
      ptr = new RefCount<Object>(o);
    }
  }

  // ����������� ����������� ����������� ������� ������
  // � ����� � ���������� ����� ����� ���������
  SmartPtr(const SmartPtr<Object> & p) : ptr(p.ptr) {
    if (ptr) ptr->addRef();
  }

  // ���������� ��������� �������� �������� ������
  // (� ���������� ������ ����� ���� ���������)
  ~SmartPtr() { if (ptr) ptr->release(); }

  // �������� ������������ ��������� �������� ������ ��������
  // ������ � ����������� �������� ������� ��������. ������, ������
  // �� ������� ������������, � ���������� ���� ����� ���� ���������
  SmartPtr & operator = (const SmartPtr<Object> & p) {
    if (ptr != p.ptr) {
      if (ptr) ptr->release();
      if (p.ptr) p.ptr->addRef();
      ptr = p.ptr;
    }
    return *this;
  }

  // ��������, �� �������� �� ��������� "������ ������"
  bool empty() const { return ptr == NULL; }

  //--------------------------------------------------------------
  // ���������, �������������� ������ � ������� "��� ����� ������� ���������"
  //--------------------------------------------------------------

  // �������� �������������� ���� � "��������" ���������
  operator Object* () { return (Object*)*ptr; }

  // ��������� ������ � ������� �� ���������
  Object & operator *() { return *(Object*)*ptr; }
  const Object & operator *() const { return *(Object*)*ptr; }

  // ��������� ������ � ����� � ������� �������
  Object * operator ->() { return (Object*)*ptr; }
  Object * operator ->() const { return (Object*)*ptr; }

  // �������� �������
  operator bool() const { return !empty(); }
  bool operator !() const { return empty(); }

  // ��������� ������� �� ���������� ����������
  bool operator == (const SmartPtr<Object> & p) const {
    return ptr == p.ptr;
  }
  bool operator == (Object * o) const {
    if (o == NULL) return ptr == NULL;
    if (ptr == NULL) return false;
    return *ptr == o;
  }

  // ��������� �������� �� ������������ ����������
  bool operator != (const SmartPtr<Object> & p) const { return !operator ==(p); }
  bool operator != (Object * o) const { return !operator ==(o); }
};

#endif
