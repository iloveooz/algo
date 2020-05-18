/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 8. ������� ��� �������� ����������                *
*          8.2. ������ � ����������� ������ �� ��������� ����� *
*               � ������ ������                                *
*                                                              *
*  �����       : �. ���������                                  *
*  ����        : workersimpl.cpp                               *
*  ��������    : ���������� ��������������� ���������          *
*                ������������� ������� ���� � �����������      *
*                �������������������                           *
***************************************************************/

#include "workersimpl.h"

//-----------------------------------------------------------------------
// ����������� ������� recAssignment ������ � ������ ������
// ����������� maxWorkers ���������� ��� �������, ��� busy ������� ����
// ��� ������, � ��� ����������� ������������ ���������� assign �������.
//-----------------------------------------------------------------------
SmartPtr<Assignment> recAssignment(
           const SmartPtr<Assignment> assign, int busy, int maxWorkers) {
  if (busy == maxWorkers) {
    // ��� ������� ��� �����������, ����� �������� 
    // ��������� �� ���������� ����������� ����������.
    return assign;
  } else {
    // ������������ ����������� ������������������
    double maxAchieved = -1;
    // ������ �����������, ��� ������� ���� ����������
    // ��� ������������ ������������������
    SmartPtr<Assignment> bestAchieved;
    // ���� �������� ���������� ������� � ���������� �� ����� �����
    for (int num = 0;  num < maxWorkers;  num++) {
      if (assign->free(num)) {
        // ������ ��������� ��������� ��������, ������� ������� ��� ��
        // ����� busy+1 � ��������� ��������� � ���� �������� �����������
        SmartPtr<Assignment> next(new NewAssignment(num, busy, assign));
        SmartPtr<Assignment> newAssign = recAssignment(
                                              next, busy+1, maxWorkers);
        // ��������� ����������� ������������������:
        double curAchieved = newAssign->prod();
        if (curAchieved > maxAchieved) {
          // �������� ���-�� ������, ��� ����
          maxAchieved = curAchieved;
          bestAchieved = newAssign;
        }
      }
    }
    // ��������� - ������ �� ����������� �����������
    return bestAchieved;
  }
}

// �������, ����������� ������ ����������� �������
SmartPtr<Assignment> bestAssignment(fProd output, int n) {
  SmartPtr<Assignment> basePtr(new EmptyAssignment(output));
  return recAssignment(basePtr, 0, n);
}

