/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 6. ��������� ��������� ������� ����������         *
*          6.1. ������ � ����� � ������                        *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : ListGraph.cpp                                    *
*  �������� : ����������� ���������� ������� ������ ListGraph  *
***************************************************************/

#include "ListGraph.h"
#include "liststack.h"
#include "listqueue.h"

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

//**************************************************************
// ������ �������� ��������� ������ ����� (����� "� �������")
//**************************************************************

// ����������� �������� ��������� ������ �����
ListGraph::ExtGraphIterator::ExtGraphIterator(ListGraph *graph) :
    // ��������� ������������ ������:
    setNotPassed(0, graph->vertexCount()-1),
    // ������� ������� - ����������� ����� ������� �������:
    current(0),
    // ����� ���������� ��������� ���������:
    components(0),
    // ���� ��������������� ���:
    arcs(new ListStack<Iterator<int>*>),
    // ����, ���������� ������: 
    graph(graph) 
{
  // � ��������� ������������ ������ ���������� ��� ������� �����
  setNotPassed.addScale(0, graph->vertexCount()-1);
}

// �������, ��������������� � �������� ������� ��������� �������
// �� ���� ������ ����� "� �������"
Iterator<int> & ListGraph::ExtGraphIterator::operator ++() {
  // 1. �������� ������������ ������
  if (!hasMoreElements()) return *this;

  // 2. �������� ������� �������
  setNotPassed -= current;

  // 3. ������� ��������� �������
  // ������� ������������� ����, ��������� �� ������� �������
  Iterator<int> *nextPoints = (graph->graph)[current].iterator();
  for (;;) {
    if (!nextPoints->hasMoreElements()) {
      // ��������� ���� ���
      delete nextPoints;
      if (arcs->empty()) {
        // ���� ��� ����� ����: ���������� ��������� ��������,
        // �������� ��������� �� ��������� ������������ ������
        components++;
        Iterator<int> * setIterator = setNotPassed.iterator();
        current = (setIterator->hasMoreElements() ? **setIterator : -1);
        delete setIterator;
        return *this;
      } else {
        // �������� ��������� ���� �� �����
        nextPoints = **arcs;
        arcs->pop();
      }
    }
    // ����, ������� � ��������� �������, �������
    int vertex = **nextPoints;     // ��� ����� ��������� �������
    ++*nextPoints;
    if (setNotPassed.has(vertex)) {
      // ��� ������������ �������; ��� ����������� �������
      current = vertex;
      if (nextPoints->hasMoreElements()) {
        // ���� ���� ��� ����, ������� �� ���� �������,
        // �� �������� ��������� ������ ������������ � ����
        arcs->push(nextPoints);
      } else {
        delete nextPoints;
      }
      return *this;
    }
  }
}

//**************************************************************
// ������, ����������� ��������� ���������� ��������� ������ �����
//**************************************************************

void ListGraph::traverseDepthRec(GraphActor & actor) {
  // ��������� ������������ ������:
  Set setNotPassed(0, vertexCount()-1);
  setNotPassed.addScale(0, vertexCount()-1);

  // ���� �� ����������� ��������� �����
  while (!setNotPassed.empty()) {
    // �������� ������������ ������� �� ��� �� ����������
    Iterator<int> * setIterator = setNotPassed.iterator();
    int first = **setIterator;
    delete setIterator;

    // �������� ����� � ����� ���������� ���������
    actor.newSelection(first);

    // ������������ ����� ���������� ���������
    // � ������� ��������������� ����������� �������
    traverseDepthRec(first, actor, setNotPassed);
  }
}

void ListGraph::traverseDepthRec(int v, GraphActor & actor, Set & setNotPassed) {
  // �������� ���� � �������...
  actor.vertexIn(v);
  // ...� ������� �� �� ������ ������������ ������
  setNotPassed -= v;

  // ���������� ���� �� �����, ��������� �� ���� �������
  Iterator<int> * curList = graph[v].iterator();
  while (curList->hasMoreElements()) {
    int e = **curList;          // ����� ������� �� ����� ��������� ����
    bool newVertex = setNotPassed.has(e);  // ������� ��� �� ��������?

    // �������� ���� �� ����������� �� ����������
    actor.arcForward(v, e, newVertex);

    // ���� ������ � ��� �� ���������� �������,
    // �� ���������� ����������� ����� �������
    if (newVertex) {
      traverseDepthRec(e, actor, setNotPassed);
    }

    // �������� ���� � �������� �����������
    actor.arcBackward(v, e);

    // ��������� � ��������� ����
    ++*curList;
  }
  delete curList;

  // �������� ����� �� �������
  actor.vertexOut(v);
}

void ListGraph::traverseDepth(GraphActor & actor) {
  // ��������� ������������ ������:
  Set setNotPassed(0, vertexCount()-1);
  setNotPassed.addScale(0, vertexCount()-1);

  // ���� ���:
  ListStack<Pair> arcs;

  // ���� �� ����������� ��������� �����
  while (!setNotPassed.empty()) {
    // �������� ������������ ������� �� ��� �� ����������
    Iterator<int> * setIterator = setNotPassed.iterator();
    int current = **setIterator;
    // �������� ����� � ����� ���������� ���������
    actor.newSelection(current);
    delete setIterator;
    // ������ ��������������� ���, ��������� �� ��������� �������
    Iterator<int> * curList = graph[current].iterator();

    // ���� �� �������� ����� ���������� ���������
    while (current != -1) {
      // �������� ������� �������
      setNotPassed -= current;
      actor.vertexIn(current);

      // ���� ������� �� �����
      for (;;) {
        // ���� ����, ������� �� ������� �������?
        if (curList->hasMoreElements()) {
          int arcEnd = **curList;
          bool newVertex = setNotPassed.has(arcEnd);
          ++*curList;
          // �������� ������ �� ��������� ����
          actor.arcForward(current, arcEnd, newVertex);
          if (newVertex) {
            // ���� ����� � ����� ����� �� ������������� �������.
            // ���������� ��������, ������ ��� ������ �� ��������� ����
            // � ��������� � ������������ ��������� �������
            arcs.push(Pair(current, curList));
            current = arcEnd;
            curList = graph[current].iterator();
            break;
          } else {
            // ���� ����� � ��� ���������� �������.
            // ��������� �������� ������ �� ���� ����
            actor.arcBackward(current, arcEnd);
          }
        } else {
          // �������� ������������ ������� ������� �
          // ������������ � ���������� ��������
          actor.vertexOut(current);
          delete curList;
          if (arcs.empty()) {
            // ���������� ��������� �������� ���������
            current = -1;
            break;
          } else {
            // ������ �������� ������ �� ����, ����������� �� ����� ���
            Pair previous = *arcs;
            arcs.pop();
            actor.arcBackward(previous.sourceVertex, current);
            current = previous.sourceVertex;
            curList = previous.iterator;
          }
        }
      }
    }
  }
}

//**************************************************************
// ������ �������� ��������� ������ ����� (����� "� ������")
//**************************************************************

// ����������� �������� ��������� ������ �����
ListGraph::BreadthGraphIterator::BreadthGraphIterator(ListGraph *graph) :
    // ��������� ������������ ������:
    setNotPassed(0, graph->vertexCount()-1),
    // ���� ��������������� ���:
    qNext(new ListQueue<int>),
    // ����, ���������� ������: 
    graph(graph) 
{
  // � ��������� ������������ ������ ���������� ��� ������� �����
  setNotPassed.addScale(0, graph->vertexCount()-1);
  // �������� ��������� �������
  operator ++();
}

// ������� ������ ��������� �� ��������� �������
// � ������� ������ ������ ����� "� �������"
Iterator<int> & ListGraph::BreadthGraphIterator::operator ++() {
  // ������� ��������� �������; ���� ��� �� �����,
  // �� ���� ������� �� ��� ��������� ������� �
  // ��������� � ������� �� ������������ ��������
  if (!qNext->empty()) {
    // �������� ������� �� �������
    int vertex = qNext->head();
    qNext->dequeue();

    // ������������� ����, ������� �� ���� �������
    Iterator<int> *arcs = (graph->graph)[vertex].iterator();
    while (arcs->hasMoreElements()) {
      int next = **arcs;
      if (setNotPassed.has(next)) {
        qNext->enqueue(next);
        setNotPassed -= next;
      }
      ++*arcs;
    }
  }

  // ������ ���������, ���� �� ��� ������������ �������
  if (!hasMoreElements()) {
    return *this;
  }

  // �������, ���� ������� �� �������� ������ ������,
  // �� ��������� ������� ������� �� ��������� ������������.
  if (qNext->empty()) {
    // �������� ������������ ������� �� ��� �� ����������
    Iterator<int> * setIterator = setNotPassed.iterator();
    int selected = **setIterator;
    delete setIterator;

    qNext->enqueue(selected);
    setNotPassed -= selected;
  }
  return *this;
}

//**************************************************************
// ����� ��� ���������� �������� ������ ����� (����� "� ������")
//**************************************************************

void ListGraph::traverseBreadth(GraphActor & actor) {
  // ������� ������
  Queue<int> *qNext = new ListQueue<int>;
  // ��������� ��� �� ���������� ������
  Set setNotPassed;
  setNotPassed.addScale(0, vertexCount()-1);

  while (!(qNext->empty() && setNotPassed.empty())) {
    if (qNext->empty()) {
      // ����� ��������� �������� �������
      Iterator<int> * setIterator = setNotPassed.iterator();
      int selected = **setIterator;
      delete setIterator;

      // ������� �������� � ������� qNext
      actor.newSelection(selected);
      qNext->enqueue(selected);
      setNotPassed -= selected;
    }

    // ����� ������� �� �������
    int vertex = qNext->head();
    qNext->dequeue();

    actor.vertexIn(vertex);
    // �������� ���� ���, ������� �� ���� �������
    Iterator<int> *iArcs = graph[vertex].iterator();
    while (iArcs->hasMoreElements()) {
      int next = **iArcs;
      bool newVertex = setNotPassed.has(next);
      actor.arcForward(vertex, next, newVertex);
      if (newVertex) {
        qNext->enqueue(next);
        setNotPassed -= next;
      }
      ++*iArcs;
    }
    delete iArcs;
  }
}
