

#ifndef DA_TP_CLASSES_VERTEX_EDGE
#define DA_TP_CLASSES_VERTEX_EDGE

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "string"
#include "../Tests/Station.h"
#include "MutablePriorityQueue.h"

class Edge;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

/**
 * @class Vertex
 * @brief Class representing a vertex in a graph.
 */
class Vertex {
public:
    /**
     * @brief Overloaded less than operator for the Vertex class.
     * @param vertex The vertex to compare to.
     * @return True if this vertex is less than the other vertex, false otherwise.
     */
    Vertex(Station station);

    /**
    * @brief Overloaded less than operator for the Vertex class.
    * @param vertex The vertex to compare to.
    * @return True if this vertex is less than the other vertex, false otherwise.
    */
    bool operator<(Vertex & vertex) const; // // required by MutablePriorityQueue

    /**
     * @brief Get the station associated with the vertex.
     * @return The station associated with the vertex.
    */
    Station getStation() const;

    /**
    * @brief Get the outgoing edges from the vertex.
    * @return A vector of outgoing edges from the vertex.
    */
    std::vector<Edge *> getAdj() const;

    /**
     * @brief Check if the vertex has been visited.
     * @return True if the vertex has been visited, false otherwise.
     */
    bool isVisited() const;

    /**
     * @brief Get the path to the vertex.
     * @return The path to the vertex.
     */
    Edge *getPath() const;

    /**
     * @brief Get the incoming edges to the vertex.
     * @return A vector of incoming edges to the vertex.
     */
    std::vector<Edge *> getIncoming() const;

    /**
     * @brief Get the capacity of the vertex.
     * @return The capacity of the vertex.
     */
    double const getCapacity();

    /**
     * @brief Get the cost of the vertex.
     * @return The cost of the vertex.
     */
    double getCost() const;

    /**
     * @brief Get the path for cost from the source vertex to this vertex.
     * @return A vector of pairs containing the station name and the line number.
     */
    vector<pair<string, int>> getPathForCost();

    /**
     * @brief Set the visited status of the vertex.
     * @param visited The visited status to set.
    */
    void setVisited(bool visited);

    /**
     * @brief Set the path to the vertex.
     * @param path The path to set.
    */
    void setPath(Edge *path);

    /**
     * @brief Set the capacity of the vertex.
     * @param capacity1 The capacity to set.
    */
    void setCapacity(double capacity1);

    /**
     * @brief Remove an edge from the vertex's adjacency list.
     * @param station The station name of the edge to remove.
     * @return True if the edge was removed successfully, false otherwise.
    */
    bool removeEdge(std::string station);

    /**
     * @brief Set the cost of the vertex.
     * @param cost1 The cost to set.
    */
    void set_Cost(double cost1);

    /**
     * @brief Add a new station and line number pair to the path for cost.
     * @param pair1 The station and line number pair to add.
     */
    void addPathForCost(pair<string, int> pair1);

    /**
     * @brief Set the path for cost.
     * @param vec_pair The vector of station and line number pairs to set as the path for
     */
    void setPathForCost(vector<pair<string, int>> vec_pair);

    /**
     * @brief Add an edge to the vertex's adjacency list.
     * @param d The destination vertex.
     * @param w The edge weight.
     * @param cost The edge cost.
     * @return A pointer to the newly created edge.
     */
    Edge *addEdge(Vertex *d, int w, double cost);

protected:
    Station station;

    std::vector<Edge *> adj;  // outgoing edges

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    unsigned int indegree; // used by topsort
    double dist = 0;
    Edge *path = nullptr;

    std::vector<Edge *> incoming; // incoming edges

    int queueIndex = 0; 		// required by MutablePriorityQueue and UFDS

    bool blocked = false;

    double capacity = 0;

    double cost = INF;
    vector<pair<string , int>> pathForCost;
};

/********************** Edge  ****************************/

/**
 * @class Edge
 * @brief Represents an edge in a graph.
 *
 * This class represents an edge in a graph, connecting two vertices.
 * Each edge has a weight and other auxiliary fields, such as flow and cost,
 * that can be used in various graph algorithms.
 */
class Edge {
public:
    /**
    * @brief Constructor with specified origin, destination, and weight.
    *
    * @param orig Pointer to the origin vertex.
    * @param dest Pointer to the destination vertex.
    * @param w Weight of the edge.
    */
    Edge(Vertex *orig, Vertex *dest, int w);

    /**
    * @brief Get the destination vertex.
    *
    * @return Pointer to the destination vertex.
    */
    Vertex * getDest() const;

    /**
     * @brief Get the edge weight.
     *
     * @return Edge weight as a double.
     */
    double getWeight() const;

    /**
     * @brief Check if the edge is selected.
     *
     * @return True if the edge is selected, false otherwise.
     */
    bool isSelected() const;

    /**
     * @brief Get the origin vertex.
     *
     * @return Pointer to the origin vertex.
     */
    Vertex * getOrig() const;

    /**
     * @brief Get the reverse edge.
     *
     * @return Pointer to the reverse edge.
     */
    Edge *getReverse() const;

    /**
     * @brief Get the flow value of the edge.
     *
     * @return Flow value as an integer.
     */
    int getFlow() const;

    /**
     * @brief Get the cost value of the edge.
     *
     * @return Cost value as an double.
     */
    double get_Cost() const;

    /**
     * @brief Set the selected state of the edge.
     *
     * @param selected Boolean value to set the selected state.
     */
    void setSelected(bool selected);

    /**
     * @brief Set the reverse edge.
     *
     * @param reverse Pointer to the reverse edge.
     */
    void setReverse(Edge *reverse);

    /**
     * @brief Set the flow value of the edge.
     *
     * @param flow Flow value as an integer.
     */
    void setFlow(int flow);

    /**
     * @brief Set the cost of the edge.
     *
     * @param cost1 Cost value as a double.
     */
    void set_Cost(double cost1);

protected:
    /**
     * @param dest Destination vertex from the edge.
     */
    Vertex * dest;

    /**
     * @param weight Weigth from the edge as a double.
     */
    double weight;

    /**
     * @param selected Selected value as a bool.
     */
    bool selected = false;

    /**
     * @param orig Origin vertex from the edge.
     */
    Vertex *orig;

    /**
     * @param reverse Reversed edge.
     */
    Edge *reverse = nullptr;

    /**
     * @param flow Flow of the edge as an int.
     */
    int flow;

    /**
     * @param cost Cost of the edge as an double. Represent the cost of the ticket.
     *
     */
    double cost;
};

#endif /* DA_TP_CLASSES_VERTEX_EDGE */