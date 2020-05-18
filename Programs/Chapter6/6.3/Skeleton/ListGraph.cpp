/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 6. ��������� ��������� ������� ����������         *
*          6.3. ����������� �������� ��������                  *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : ListGraph.cpp                                    *
*  �������� : ����������� ���������� ������� ������ ListGraph  *
***************************************************************/

#include "ListGraph.h"
#include "arc.h"
#include "arrayheap.h"
#include "infinity.h"
#include "set.h"

//**************************************************************
// ������ ������ ListGraph
//**************************************************************

// ���������� ����
void ListGraph::addArc(int from, int to) {
  if (from < 0 || from >= vertexNumber || to < 0 || to >= vertexNumber)
    return;          // ����������� ������ ����
  graph[from].addLast(to);
}

// ����� ����
bool ListGraph::hasArc(int from, int to) const {
  if (from < 0 || from >= vertexNumber || to < 0 || to >= vertexNumber)
    return false;    // ����������� ������ ����
  Iterator<int> * ends = graph[from].iterator();
  bool found = false;
  while (ends->hasMoreElements() && !(found = (to == **ends))) ++*ends;
  delete ends;
  return found;
}

//--------------------------------------------------------------
// �������� �������� ���������� ������������ ��������� ������
//--------------------------------------------------------------

double ListGraph::minSkeleton(
    std::ostream & out,     // �������� ����� ��� ������ �������������� ����������
    const GraphWeight & gw  // �������� �� ����� �����
    ) {
  // ��������� ��� ���������� ������������ ��������� ������:
  double weight = 0;
  // ��������, ���������� ���������� � ������ �����:
  ArrayHeap<Arc> arcs(vertexNumber * vertexNumber / 2);

  //---------------------------------------------------------------
  // ��������� ���� � ����, �������������� �������� �����������
  // ����������� �������� ������
  //---------------------------------------------------------------
  struct SkeletonNode {
    int node;   // ����� ���� ��������� �����
    int next;   // ������ �� ������������ ����
    // ������������:
    SkeletonNode(int n = 0) : node(n), next(-1) {}
    SkeletonNode(const SkeletonNode & node) : node(node.node), next(node.next) {}
  };

  // ��������� ���������� �������� �����:
  // ��������������� ��� ����� �����,
  // � ���������� � ��� ��������� � ��������.
  for (int i = 0; i < vertexNumber; i++) {
    Iterator<int> *neighbors = graph[i].iterator();
    while (neighbors->hasMoreElements()) {
      int j = **neighbors;
      // ���� �����������������, ������� ��� ���������� ������������ ����������
      // ��������������� ������ ����, ������� �� ������� � ������� �������
      // � ������� � ������� �������. ����� (���� ��� ����) ����� �� �����������.
      if (i < j) {
        // ���������� ����� � ��������:
        arcs += Arc(i, j, gw.arcLength(i, j));
      }
      ++*neighbors;
    }
    delete neighbors;
  }

  // ��������� ���������� ����: ������ ������� ����� ������������
  // ����� ��������� ������, ��������� �� ������������ �������.
  SkeletonNode skeleton[vertexNumber];
  for (int i = 0; i < vertexNumber; i++) {
    skeleton[i] = SkeletonNode(i);
  }

  // �������� ���� �� ������, ���������� � ��������
  while (!arcs.empty()) {
    // ��������� ����� ���������� � ������� �������� � ����������� �� ���:
    Arc nextArc = *arcs;
    arcs.remove();

    // u � v - ����� ���������� �����
    int u = nextArc.from, v = nextArc.to;

    // ��������� ��� ����� ������� ����� ��������, ���������� ��� �������:
    while(skeleton[u].next != -1) u = skeleton[u].next;
    while(skeleton[v].next != -1) v = skeleton[v].next;

    if (u != v) {
      // ����� ���������� � �������� ������,...
      out << nextArc << "; ";
      weight += nextArc.weight;
      // ... � ��� ������ ����������� � ����.
      skeleton[u].next = v;
    }
  }

  return weight;
}

//--------------------------------------------------------------
// �������� ����� ���������� ������������ ��������� ������
//--------------------------------------------------------------

double ListGraph::minSkeletonPrim(std::ostream & out, const GraphWeight & gw) {
  // ��������� ������������ ������ (������� - ��� �������)
  Set notPassed(0, vertexNumber-1);
  notPassed.addScale(0, vertexNumber-1);

  // ������ ���������� �� ������ �� ��� ����������� �����
  double *dist = new double[vertexNumber];

  // ������ ����������� �� ����� ������ � ��� ����������� �����
  double *ends = new double[vertexNumber];

  // ������������� �������� ���������� � �����������
  for (int i = 0; i < vertexNumber; i++) {
    dist[i] = INFINITY;
    ends[i] = -1;
  }

  // ��������� ��� ����������� ����� ������
  double sumWeight = 0;

  // �������� ���� ������ ����� ������
  while (!notPassed.empty()) {
    // ����� ��������� �������
    double minDist = INFINITY;
    Iterator<int> *iVertices = notPassed.iterator();
    int minVertex = **iVertices;
    while (iVertices->hasMoreElements()) {
      int nextVertex = **iVertices;
      if (dist[nextVertex] < minDist) {
        minDist = dist[nextVertex];
        minVertex = nextVertex;
      }
      ++*iVertices;
    }
    delete iVertices;
      
    if (dist[minVertex] < INFINITY) {
      // ������������ ��������� �����
      out << "(" << ends[minVertex] << "," << minVertex << "); ";
      sumWeight += minDist;
    }
    notPassed -= minVertex;

    // ����� ������� ������������;
    // ������������ ���������� � �����������
    Iterator<int> *neighbors = graph[minVertex].iterator();
    while (neighbors->hasMoreElements()) {
      int next = **neighbors;
      if (notPassed.has(next) && gw.arcLength(minVertex, next) < dist[next]) {
        dist[next] = gw.arcLength(minVertex, next);
        ends[next] = minVertex;
      }
      ++*neighbors;
    }
    delete neighbors;
  }
  return sumWeight;
}
