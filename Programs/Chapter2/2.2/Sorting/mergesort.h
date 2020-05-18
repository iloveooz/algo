/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 2. ������� ���������                              *
*          2.2. ���������� � ����� � ��������                  *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : mergesort.h                                      *
*  �������� : ������� ���������� ��������� ������� �������     *
*             ����������������� �������                        *
***************************************************************/

#ifndef __MERGE_SORT_H
#define __MERGE_SORT_H

#include "merge.h"
#include <math.h>

//-------------------------------------------------------------
// ������ move ������ ��������������� �������, ������� ������
// ��������� �������� ������� �� ������ ��������� �������
// � ������ �������� ���� �� ������ ��� ������� �������.
//   - Key - �����, �������� ��� ��������� �������;
//   - src - �������� �������� �������;
//   - sLow, sHigh - �������, �������� �������� � �������� �������;
//   - dst - �������������� �������� �������;
//   - dLow - ������, �������� ������ ������� ��������������� �������.
//-------------------------------------------------------------

template <class Key>
void move(Key * src, int sLow, int sHigh, Key * dst, int dLow) {
  for (int pSrc = sLow, pDst = dLow; pSrc <= sHigh; ) {
    dst[pDst++] = src[pSrc++];
  }
}

//-------------------------------------------------------------
// ������ mergeSort ������ ������� ���������� ���������
// ������� ������� ���������������� �������.
//   - Key - �����, �������� ��� ��������� �������;
//   - array - ��������������� ������;
//   - low, high - �������, �������� �������� ����������;
//-------------------------------------------------------------

template <class Key>
void mergeSort(Key * array, int low, int high) {
  // ��������������, ��� � ������ ������ low <= high
  // � ���������� ���������� ���������� ������������� ��������
  // ������� � ��������� �� low �� high
  int n = high - low + 1;    // ����� �������
  int frag = n;              // ����� ������������� ����������
  int len = 1;               // ����� ��������� ����������
  Key * source = array,      // ������, �� �������� ���������� �������
      * dest = new Key[n];   // ������, � ������� ���������� �������
  int sourceLow = low,       // ������ ������� �������� �������-���������
      destLow = 0;           // ������ ������� �������� �������-����������

  while (frag > 1) {
    // ���� ��� ����� ������� ������� � �������� ������� ����������
    // ��������� ������� � �������� ���������� ��������� ���������
    // �� ��������� ������� � ��������������.
    int pSource = sourceLow, pDest = destLow;
    do {
      int nextSource = min(pSource + 2*len, sourceLow + n);
      if (nextSource > pSource + len) {
        merge<Key>(source, pSource, pSource+len-1,
                   source, pSource+len, nextSource-1,
                   dest, pDest);
      } else {
        move<Key>(source, pSource, nextSource-1,
                  dest, pDest);
      }
      pSource = nextSource; pDest += 2*len;
    } while (pSource < sourceLow+n);
    len *= 2;
    frag = (frag+1)/2;
    Key * tempArray = dest; dest = source; source = tempArray;
    int tempLow = destLow; destLow = sourceLow; sourceLow = tempLow;
  }
  if (source != array) {
    move<Key>(source, sourceLow, sourceLow+n-1, dest, destLow);
  }
}

#endif
