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
SmartPtr<Assignment> recAssignment(const SmartPtr<Assignment> assign,
                                   int busy, int maxWorkers, double maxFree, double * maxProds) {
  if (busy == maxWorkers) {
    // ��� ������� ��� �����������, ����� �������� 
    // ��������� �� ���������� ����������� ����������.
    return assign;
  } else {
    // ������� ���������� ������������������
    fProd output = assign->getOutput();
    // ������������ ��������� ���������� �� �������� ������������������
    int * freeWorkers = new int[maxWorkers-busy];
    for (int num = 0, k = 0;  num < maxWorkers;  num++) {
      if (assign->free(num)) freeWorkers[k++] = num;
    }
    // ���������� ������� �� �������� ������������������
    for (int i = 1; i < maxWorkers-busy; i++) {
      int j = i-1;
      int p = freeWorkers[i];
      while (j >= 0 && output(busy, freeWorkers[j]) < output(busy, p)) {
        freeWorkers[j+1] = freeWorkers[j];
        j--;
      }
      freeWorkers[j+1] = p;
    }
    // ������������ ����������� ������������������
    double maxAchieved = -1;
    // ������ �����������, ��� ������� ���� ����������
    // ��� ������������ ������������������
    SmartPtr<Assignment> bestAchieved;
    // ���� �������� ���������� ������� � ���������� �� ����� �����
    for (int k = 0;  k < maxWorkers-busy;  k++) {
      int num = freeWorkers[k];
      // �������� ���������� ���������� ��������� � ������� ������� ��� ��
      // ����� busy+1, �������� ��������� � ���� �������� �����������.
      // �������������� ���������, ����� �� ����� ������ ���������.
      if (assign->prod() + output(busy, num) + maxFree - maxProds[num] > maxAchieved) {
        SmartPtr<Assignment> next(new NewAssignment(num, busy, assign));
        SmartPtr<Assignment> newAssign = recAssignment(
            next, busy+1, maxWorkers, maxFree - maxProds[num], maxProds);
        // ��������� ����������� ������������������:
        double curAchieved = newAssign->prod();
        if (curAchieved > maxAchieved) {
          // �������� ���-�� ������, ��� ����
          maxAchieved = curAchieved;
          bestAchieved = newAssign;
        }
      }
    }
    delete[] freeWorkers;
    // ��������� - ������ �� ����������� �����������
    return bestAchieved;
  }
}

// �������, ����������� ������ ����������� �������
SmartPtr<Assignment> bestAssignment(fProd output, int n) {
  double maxFree = 0;
  double * maxProds = new double[n];
  for (int wr = 0; wr < n; wr++) {
    double max = 0, curr;
    for (int wp = 0; wp < n; wp++) {
      if ((curr = output(wp, wr)) > max) max = curr;
    }
    maxFree += (maxProds[wr] = max);
  }
  SmartPtr<Assignment> basePtr(new EmptyAssignment(output));
  SmartPtr<Assignment> bestAssign = recAssignment(basePtr, 0, n, maxFree, maxProds);
  delete[] maxProds;
  return bestAssign;
}

