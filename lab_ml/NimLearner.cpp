/**
 * @file NimLearner.cpp
 * CS 225: Data Structures
 */

#include "NimLearner.h"
#include <ctime>

using namespace std;

/**
 * Constructor to create a game of Nim with `startingTokens` starting tokens.
 *
 * This function creates a graph, `g_` representing all of the states of a
 * game of Nim with vertex labels "p#-X", where:
 * - # is the current player's turn; p1 for Player 1, p2 for Player2
 * - X is the tokens remaining at the start of a player's turn
 *
 * For example:
 *   "p1-4" is Player 1's turn with four (4) tokens remaining
 *   "p2-8" is Player 2's turn with eight (8) tokens remaining
 *
 * All legal moves between states are created as edges with initial weights
 * of 0.
 *
 * @param startingTokens The number of starting tokens in the game of Nim.
 */
NimLearner::NimLearner(unsigned startingTokens) : g_(true, true) {
    /* Your code goes here! */
    unsigned int tokenNumber = 0;
    while(tokenNumber < startingTokens) {
      g_.insertVertex("p1-" + to_string(tokenNumber));
      g_.insertVertex("p2-" + to_string(tokenNumber));
      tokenNumber++;
    }

    for(unsigned int token = startingTokens; token > 1; token--) {
      g_.insertEdge("p1-" + to_string(token), "p2-" + to_string(token - 1));
      g_.insertEdge("p1-" + to_string(token), "p2-" + to_string(token - 2));
      g_.insertEdge("p2-" + to_string(token), "p1-" + to_string(token - 1));
      g_.insertEdge("p2-" + to_string(token), "p1-" + to_string(token - 2));
      g_.setEdgeWeight("p1-" + to_string(token), "p2-" + to_string(token - 1), 0);
      g_.setEdgeWeight("p1-" + to_string(token), "p2-" + to_string(token - 2), 0);
      g_.setEdgeWeight("p2-" + to_string(token), "p1-" + to_string(token - 1), 0);
      g_.setEdgeWeight("p2-" + to_string(token), "p1-" + to_string(token - 2), 0);
    }
    g_.insertEdge("p1-" + to_string(1), "p2-" + to_string(0));
    g_.insertEdge("p2-" + to_string(1), "p1-" + to_string(0));
    g_.setEdgeWeight("p1-" + to_string(1), "p2-" + to_string(0), 0);
    g_.setEdgeWeight("p2-" + to_string(1), "p1-" + to_string(0), 0);

    startingVertex_ = ("p1-" + to_string(startingTokens));
}

/**
 * Plays a random game of Nim, returning the path through the state graph
 * as a vector of `Edge` classes.  The `origin` of the first `Edge` must be
 * the vertex with the label "p1-#", where # is the number of starting
 * tokens.  (For example, in a 10 token game, result[0].origin must be the
 * vertex "p1-10".)
 *
 * @returns A random path through the state space graph.
 */
std::vector<Edge> NimLearner::playRandomGame() const {
  vector<Edge> path;
 /* Your code goes here! */
   Vertex nextVertex;
   Vertex currentVertex = startingVertex_;
   vector<Vertex> adjacentVertices = g_.getAdjacent(currentVertex);

   while(adjacentVertices.size() != 0) {
     adjacentVertices = g_.getAdjacent(currentVertex);
     nextVertex = adjacentVertices[rand() % adjacentVertices.size()];
     Edge tempEdge = g_.getEdge(currentVertex, nextVertex);
     path.push_back(tempEdge);
     currentVertex = nextVertex;
     adjacentVertices = g_.getAdjacent(currentVertex);
   }
   return path;
 }


/*
 * Updates the edge weights on the graph based on a path through the state
 * tree.
 *
 * If the `path` has Player 1 winning (eg: the last vertex in the path goes
 * to Player 2 with no tokens remaining, or "p2-0", meaning that Player 1
 * took the last token), then all choices made by Player 1 (edges where
 * Player 1 is the source vertex) are rewarded by increasing the edge weight
 * by 1 and all choices made by Player 2 are punished by changing the edge
 * weight by -1.
 *
 * Likewise, if the `path` has Player 2 winning, Player 2 choices are
 * rewarded and Player 1 choices are punished.
 *
 * @param path A path through the a game of Nim to learn.
 */
void NimLearner::updateEdgeWeights(const std::vector<Edge> & path) {
 /* Your code goes here! */
 Edge tempEdge;
 int changedWeight = 1;
 int size = path.size();

 for(int currentVertex = size - 1; currentVertex >= 0; currentVertex--) {
   tempEdge = path[currentVertex];
   g_.setEdgeWeight(tempEdge.source, tempEdge.dest, (g_.getEdgeWeight(tempEdge.source, tempEdge.dest) + changedWeight));
   changedWeight = changedWeight * -1;
 }
}

/**
 * Label the edges as "WIN" or "LOSE" based on a threshold.
 */
void NimLearner::labelEdgesFromThreshold(int threshold) {
  for (const Vertex & v : g_.getVertices()) {
    for (const Vertex & w : g_.getAdjacent(v)) {
      int weight = g_.getEdgeWeight(v, w);

      // Label all edges with positve weights as "WINPATH"
      if (weight > threshold)           { g_.setEdgeLabel(v, w, "WIN"); }
      else if (weight < -1 * threshold) { g_.setEdgeLabel(v, w, "LOSE"); }
    }
  }
}

/**
 * Returns a constant reference to the state space graph.
 *
 * @returns A constant reference to the state space graph.
 */
const Graph & NimLearner::getGraph() const {
  return g_;
}
