/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 2. ������� ���������                              *
*          2.2. ���������� � ����� � ��������                  *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : heapsort.h                                       *
*  �������� : ������� ���������� ��������� ������� �������     *
*             ������������� ����������                         *
***************************************************************/

#ifndef __HEAP_SORT_H
#define __HEAP_SORT_H

//-------------------------------------------------------------
// ������ heapSort ������ ������� ���������� ���������
// ������� ������� ������������� ����������.
//   - Key - �����, �������� ��� ��������� �������;
//   - array - ��������������� ������;
//   - low, high - �������, �������� �������� ����������;
//-------------------------------------------------------------

template <class Key>
void heapSort(Key * array, int low, int high) {
  // ��������������, ��� � ������ ������ low <= high
  // � ���������� ���������� ���������� ������������� ��������
  // ������� � ��������� �� low �� high
  int heapLength = 1;

  // 1. ������������ ��������
  while (heapLength <= high-low) {
    // ������� � �������� low+heapLength ���������� � ��������
    int ndx = low + heapLength;
    Key elem = array[ndx];
    while (ndx > low && elem > array[(ndx-low-1)/2]) {
      array[ndx] = array[(ndx-low-1)/2];
      ndx = (ndx-low-1)/2;
    }
    array[ndx] = elem;
    heapLength++;
  }

  // 2. �������������� ���������
  while (heapLength > 1) {
    heapLength--;
    Key elem = array[low + heapLength];
    array[low + heapLength] = array[low];
    int ndx = low;
    while (2*(ndx-low) < heapLength-1) {
      int child1 = low + 2*(ndx-low) + 1,
          child2 = low + 2*(ndx-low) + 2;
      if (child2 <= low + heapLength - 1 &&
          array[child2] > array[child1]) {
        child1 = child2;
      }
      if (elem > array[child1]) break;
      array[ndx] = array[child1];
      ndx = child1;
    }
    array[ndx] = elem;
  }
}

#endif
