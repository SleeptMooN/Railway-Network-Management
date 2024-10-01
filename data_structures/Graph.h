#ifndef DA_TP_CLASSES_GRAPH
#define DA_TP_CLASSES_GRAPH

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "MutablePriorityQueue.h"

#include "VertexEdge.h"
using namespace std;

class Graph {
public:

    Graph();

    /**

  @brief Find a vertex in the graph with the given id, if it does not exist return nullptr.
  @param name The id of the vertex to find.
  @return The vertex with the given id, or nullptr if it does not exist.
  */
    Vertex *findVertex(const std::string &name) const;

/**
@brief Add a vertex to the graph.
@param station The station to add as a vertex.
@return true if the vertex was added, false if a vertex with the same id already exists.
*/
    bool addVertex(Station station);

    /**
@brief Adds a bidirectional edge to the graph, given the contents of the source and
destination vertices and the edge weight.
Returns true if successful, and false if the source or destination vertex does not exist.
@param source The id of the source vertex.
@param dest The id of the destination vertex.
@param w The weight of the edge.
@param cost The cost of the edge.
@return true if the edge was added, false otherwise.
*/
    bool addBidirectionalEdge(const std::string& source, const std::string& dest, int w, double cost);


    /**

@brief Adds an edge to the graph, given the contents of the source and
destination vertices and the edge weight.
Returns true if successful, and false if the source or destination vertex does not exist.
@param source The id of the source vertex.
@param dest The id of the destination vertex.
@param w The weight of the edge.
@param cost The cost of the edge.
@return true if the edge was added, false otherwise.
*/

    bool addEdge(const std::string& source, const std::string& dest, int w, double cost);



    /**
@brief Get the number of vertices in the graph.
@return The number of vertices in the graph.
*/

    int getNumVertex() const;



    /**

@brief Get the vector of vertices in the graph.
@return A vector containing all vertices in the graph.
*/
    std::vector<Vertex *> getVertexSet() const;


    /**

@brief Find the maximum flow from a source to a target vertex in the graph, using the Edmonds-Karp algorithm.
@param source The id of the source vertex.
@param target The id of the target vertex.
@return The maximum flow from the source to the target vertex.
*/
    int edmondsKarp(std::string source, std::string target);




    /**

@brief Perform a breadth-first search to find a path from a source to a target vertex in the graph, for use in the Edmonds-Karp algorithm.
@param source The id of the source vertex.
@param target The id of the target vertex.
@return true if a path was found, false otherwise.
*/
    bool bfskarp(std::string source, std::string target);



    /**

@brief Removes a vertex with the given name from the graph.
@param name The name of the vertex to remove.
@return true If the vertex was successfully removed.
@return false If no vertex with the given name exists in the graph.
*/
    bool removeVertex(const std::string &name);



protected:

    /**
     * @brief Vector of graph vertexes
     */
    std::vector<Vertex *> vertexSet;    // vertex set

    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall
    /*
     * Finds the index of the vertex with a given content.
     */
    int findVertexIdx(const std::string &name) const;

};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);

#endif /* DA_TP_CLASSES_GRAPH */