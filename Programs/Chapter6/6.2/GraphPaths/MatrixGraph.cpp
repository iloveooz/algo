/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 6. ��������� ��������� ������� ����������         *
*          6.2. ����� ���������� �����                         *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : MatrixGraph.cpp                                  *
*  �������� : ���������� ������� ������ MatrixGraph            *
***************************************************************/

#include "MatrixGraph.h"

// �����������
MatrixGraph::MatrixGraph(int n) {
  graph = new bool*[vertexNumber = n];
  for (int i=0; i<n; i++) {
    // �������� ������
    bool *row = graph[i] = new bool[n];
    // ������������� ��������� ������
    for (int j = 0; j < n; j++) {
      row[j] = false;
    }
  }
}

// ����������� �����������
MatrixGraph::MatrixGraph(const MatrixGraph & src) {
  int n = src.vertexCount();
  graph = new bool*[vertexNumber = n];
  for (int i=0; i<n; i++) {
    // �������� ������
    bool *row = graph[i] = new bool[n];
    bool *srcRow = src.graph[i];
    // ������������� ��������� ������
    for (int j = 0; j < n; j++) {
      row[j] = srcRow[j];
    }
  }
}

// ����������
MatrixGraph::~MatrixGraph() {
  for (int i = 0; i < vertexNumber; i++) {
    delete graph[i];
  }
  delete graph;
}

// �������� �����������
MatrixGraph & MatrixGraph::operator = (const MatrixGraph & src) {
  // ����������� ���������:
  int n;
  if (vertexNumber != (n = src.vertexCount())) {
    this->~MatrixGraph();
    graph = new bool*[vertexNumber = n];
    for (int i = 0; i < n; i++) {
      // �������� ������
      bool *row = graph[i] = new bool[n];
    }
  }

  // ����������� ���������
  for (int i = 0; i < n; i++) {
    bool * row = graph[i];
    bool * srcRow = src.graph[i];
    for (int j = 0; j < n; j++) {
      row[j] = srcRow[j];
    }
  }
}

// ���������� ���� - ������� ������� ��������������� � true
void MatrixGraph::addArc(int from, int to) {
  if (from < 0 || from >= vertexNumber || to < 0 || to >= vertexNumber)
    return;    // ����������� ������ ����
  graph[from][to] = true;
}

// �������� ���� - ������� ������� ��������������� � false
void MatrixGraph::removeArc(int from, int to) {
  if (from < 0 || from >= vertexNumber || to < 0 || to >= vertexNumber)
    return;    // ����������� ������ ����
  graph[from][to] = false;
}

// �������� ������������� ����
bool MatrixGraph::hasArc(int from, int to) const {
  if (from < 0 || from >= vertexNumber || to < 0 || to >= vertexNumber)
    return false;    // ����������� ������ ����
  return graph[from][to];
}

std::ostream & operator << (std::ostream &out, const MatrixGraph & matrix) {
  for (int i = 0; i < matrix.vertexCount(); i++) {
    for (int j = 0; j < matrix.vertexCount(); j++) {
      out << (matrix.hasArc(i, j) ? " 1" : " 0");
    }
    out << std::endl;
  }
  return out;
}

MatrixGraph mult(const MatrixGraph & G1, const MatrixGraph & G2) throw(IncompatibleSizes) {
  int n;
  MatrixGraph result(n = G1.vertexCount());
  if (n != G2.vertexCount()) {
    throw IncompatibleSizes();
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        if (G1.graph[i][k] && G2.graph[k][j]) {
          result.addArc(i, j);
          break;
        }
      }
    }
  }
  return result;
}

MatrixGraph add(const MatrixGraph & G1, const MatrixGraph & G2) throw(IncompatibleSizes) {
  int n;
  MatrixGraph result(n = G1.vertexCount());
  if (n != G2.vertexCount()) {
    throw IncompatibleSizes();
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      result.graph[i][j] = G1.graph[i][j] || G2.graph[i][j];
    }
  }
  return result;
}

MatrixGraph closure(const MatrixGraph & G) {
  MatrixGraph Gi = G;
  for (int i = 0; i < G.vertexCount(); i++) {
    Gi = add(mult(Gi, G), G);
  }
  return Gi;
}

void FloydWarshall(MatrixGraph & G) {
  int n = G.vertexCount();
  for (int k = 1; k < n; k++) {
    for (int i = 0;  i < n;  i++) {
      for (int j = 0;  j < n;  j++) {
        if (i != k-1 && !G.graph[i][j]) {
          G.graph[i][j] = G.graph[i][k-1] && G.graph[k-1][j];
        }
      }
    }
  }
}

void getMinPaths(const MatrixGraph & G,   // �������� ����
                 const GraphWeight & w,   // �������� �� ����
                 double ** & P,           // ���������� ��� ������� �����
                 int ** & D               // ...� ��� ������� �����������
                ) {
  int n = G.vertexCount();      // ����� ������ �����

  // ������������� ������.
  // � ������� ���� ����� ������������ ����� ��� ��������� �����:
  P = new double*[n];
  for (int i = 0; i < n; i++) {
    double * row = P[i] = new double[n];
    for (int j = 0; j < n; j++) {
      row[j] = w.arcLength(i, j);
    }
  }
  // � ������� ����������� ������������ ���������� � ������������
  // ��� ��������� ����� (-1, ���� ����������� �� ����������):
  D = new int*[n];
  for (int i = 0; i < n; i++) {
    int * row = D[i] = new int[n];
    for (int j = 0; j < n; j++) {
      row[j] = (G.hasArc(i, j) ? j : -1);
    }
  }

  // ���������� ���������� ����� � �����������
  // �� ��������� ������-��������
  for (int k = 1; k < n; k++) {
    for (int i = 0;  i < n;  i++) {
      for (int j = 0;  j < n;  j++) {
        if (i != k-1 && P[i][k-1] < INFINITY && P[k-1][j] < INFINITY &&
            P[i][j] > P[i][k-1] + P[k-1][j]) {
          P[i][j] = P[i][k-1] + P[k-1][j];
          D[i][j] = D[i][k-1];
        }
      }
    }
  }
}
