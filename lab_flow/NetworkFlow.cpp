/**
 * @file NetworkFlow.cpp
 * CS 225: Data Structures
 */

#include <vector>
#include <algorithm>
#include <set>

#include "graph.h"
#include "edge.h"

#include "NetworkFlow.h"

int min(int a, int b) {
  if (a<b)
    return a;
  else return b;
}

NetworkFlow::NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink) :
  g_(startingGraph), residual_(Graph(true,true)), flow_(Graph(true,true)), source_(source), sink_(sink) {

  // YOUR CODE HERE
  vector<Vertex> graphVertices = g_.getVertices();
  vector<Edge> graphEdges = g_.getEdges();

  int noWeight = 0;

  for(Vertex & vert : graphVertices) {
    residual_.insertVertex(vert);
    flow_.insertVertex(vert);
  }

  for(Edge & edge : graphEdges) {
    Vertex begin = edge.source;
    Vertex end = edge.dest;

    int edgeWeight = edge.getWeight();

    flow_.insertEdge(begin, end);
    flow_.setEdgeWeight(begin, end, noWeight);
    residual_.insertEdge(begin, end);
    residual_.insertEdge(end, begin);
    residual_.setEdgeWeight(begin, end, edgeWeight);
    residual_.setEdgeWeight(end, begin, noWeight);
  }

}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the helper function.
   *
   * @param source  The starting (current) vertex
   * @param sink    The destination vertex
   * @param path    The vertices in the path
   * @param visited A set of vertices we have visited
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink,
  std::vector<Vertex> &path, std::set<Vertex> &visited) {

  if (visited.count(source) != 0)
    return false;
  visited.insert(source);

  if (source == sink) {
    return true;
  }

  vector<Vertex> adjs = residual_.getAdjacent(source);
  for(auto it = adjs.begin(); it != adjs.end(); it++) {
    if (visited.count(*it) == 0 && residual_.getEdgeWeight(source,*it) > 0) {
      path.push_back(*it);
      if (findAugmentingPath(*it,sink,path,visited))
        return true;
      else {
        path.pop_back();
      }
    }
  }

  return false;
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the main function.  It initializes a set to keep track of visited vertices.
   *
   * @param source The starting (current) vertex
   * @param sink   The destination vertex
   * @param path   The vertices in the path
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex> &path) {
   std::set<Vertex> visited;
   path.clear();
   path.push_back(source);
   return findAugmentingPath(source,sink,path,visited);
}

  /**
   * pathCapacity - Determine the capacity of a path in the residual graph.
   *
   * @param path   The vertices in the path
   */

int NetworkFlow::pathCapacity(const std::vector<Vertex> & path) const {
  // YOUR CODE HERE
  int count = 0;
  int size = (path.size() - 1);
  int currMin = residual_.getEdgeWeight(path[0], path[1]);
  while(count < size) {
    int min = residual_.getEdgeWeight(path[count], path[count+1]);
    if(min < currMin) {
      currMin = min;
    }
    count++;
  }
  return currMin;
}

  /**
   * calculuateFlow - Determine the capacity of a path in the residual graph.
   * Sets the member function `maxFlow_` to be the flow, and updates the
   * residual graph and flow graph according to the algorithm.
   *
   * @return The network flow graph.
   */

const Graph & NetworkFlow::calculateFlow() {
  // YOUR CODE HERE
  vector<Vertex> graphVertices;
  vector<Edge> graphEdges;
  int total = 0;


  while(findAugmentingPath(source_, sink_, graphVertices)) {
    int current = pathCapacity(graphVertices);
    int size = (graphVertices.size() - 1);
    total = total + current;

    for(int v = 0; v < size; v++) {

      if(flow_.edgeExists(graphVertices[v], graphVertices[v+1])) {
        int edgeWeight = flow_.getEdgeWeight(graphVertices[v], graphVertices[v+1]);
        edgeWeight = edgeWeight + current;
        flow_.setEdgeWeight(graphVertices[v], graphVertices[v+1], edgeWeight);
      }
      else {
        int edgeWeight = flow_.getEdgeWeight(graphVertices[v+1], graphVertices[v]);
        edgeWeight = edgeWeight - current;
        flow_.setEdgeWeight(graphVertices[v+1], graphVertices[v], edgeWeight);
      }

      residual_.setEdgeWeight(graphVertices[v], graphVertices[v+1], residual_.getEdgeWeight(graphVertices[v], graphVertices[v+1]) - current);
      residual_.setEdgeWeight(graphVertices[v+1], graphVertices[v], residual_.getEdgeWeight(graphVertices[v+1], graphVertices[v]) + current);

    }
  }

  maxFlow_ = total;
  return flow_;
}

int NetworkFlow::getMaxFlow() const {
  return maxFlow_;
}

const Graph & NetworkFlow::getGraph() const {
  return g_;
}

const Graph & NetworkFlow::getFlowGraph() const {
  return flow_;
}

const Graph & NetworkFlow::getResidualGraph() const {
  return residual_;
}
