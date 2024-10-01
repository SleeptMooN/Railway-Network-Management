#include "Graph.h"
#include <limits>
#include <queue>
#include <algorithm>
#include <iostream>

std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

/**
 * The complexity of this code is O(|V|), where |V| is the number of vertices in the graph.
 * @param name
 * @return
 */
Vertex* Graph::findVertex(const std::string& name)const {
    // Percorra todos os vértices do grafo
    for (auto v : vertexSet) {
        // Se o nome do vértice atual for igual ao nome da estação procurada, retorne-o
        if (v->getStation().get_name() == name) {
            return v;
        }
    }
    // Se a estação não for encontrada, retorne nullptr
    return nullptr;
}


bool Graph::removeVertex(const std::string &name) {
    Vertex* v = findVertex(name);
    if (v == nullptr) {
        return false;
    }

    for (auto e : v->getAdj()) {
        auto w = e->getDest();
        w->removeEdge(v->getStation().get_name());
        v->removeEdge(w->getStation().get_name());
    }

    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++) {
        if ((*it)->getStation().get_name() == name){
            vertexSet.erase(it);
            break;
        }
    }
    delete v;
    return true;
}

/**
 *The time complexity of this code is O(n), where n is the number of vertices in the graph.
 * Finds the index of the vertex with a given content.
 */
int Graph::findVertexIdx(const std::string &name) const {
    for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->getStation().get_name() ==name)
            return i;
    return -1;
}
/**
 *The time complexity of this code is O(n), where n is the number of vertices in the graph.
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
bool Graph::addVertex(Station station) {
    if (findVertex(station.get_name()) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(station));
    return true;
}

/**
 * Assuming that both methods have a constant time complexity, the time complexity of this code is O(1).
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
bool Graph::addEdge(const std::string& source, const std::string& dest, int w, double cost) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w, cost);
    return true;
}

/**
 * The time complexity of this code is O(1), assuming that the findVertex() method has a constant time complexity, and that the addEdge() method of Vertex class also has a constant time complexity.
 * @param source
 * @param dest
 * @param w
 * @param cost
 * @return
 */
bool Graph::addBidirectionalEdge(const std::string& source, const std::string& dest, int w, double cost) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w, cost);
    auto e2 = v2->addEdge(v1, w, cost);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}


void deleteMatrix(int **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

void deleteMatrix(double **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}


Graph::Graph() {
    deleteMatrix(distMatrix, vertexSet.size());
    deleteMatrix(pathMatrix, vertexSet.size());
}


int Graph::getNumVertex() const{
    return this->vertexSet.size();
}

/**
 * The time complexity of this code is O(V * E^2), where V is the number of vertices and E is the number of edges in the graph.
 * @param source
 * @param target
 * @return
 */
// our funcs
int Graph::edmondsKarp(std::string source, std::string target) {
    // TODO
    for(auto v : vertexSet){
        for(auto e : v->getAdj()){
            e->setFlow(0);
        }
    }
    double total_flow = 0;
    while(bfskarp(source, target)){
        int mrc = INT32_MAX;
        std::string current_node_id = target;
        while(current_node_id != source){
            auto edge = findVertex(current_node_id)->getPath();
            int residual;
            if(edge->getDest()->getStation().get_name() == current_node_id){
                residual = edge->getWeight() - edge->getFlow();
                current_node_id = edge->getOrig()->getStation().get_name();
            }
            else{
                residual = edge->getFlow();
                current_node_id = edge->getDest() ->getStation().get_name();
            }
            if(residual < mrc) mrc = residual;
        }

        current_node_id = target;
        while(current_node_id != source){
            auto edge = findVertex(current_node_id)->getPath();
            if(edge->getDest()->getStation().get_name() == current_node_id){
                edge->setFlow(edge->getFlow() + mrc);
                current_node_id = edge->getOrig()->getStation().get_name();
            }
            else{
                edge->setFlow(edge->getFlow() - mrc);
                current_node_id = edge->getDest() ->getStation().get_name();
            }
        }
        total_flow += mrc;
    }
    return total_flow;
}

/**
 * The time complexity of this code is O(E + V), where E is the number of edges and V is the number of vertices in the graph.
 * @param source
 * @param target
 * @return
 */
bool Graph::bfskarp(std::string source, std::string target) {
    std::queue<Vertex *> q;
    for (auto v: vertexSet) {
        v->setVisited(false);
        v->setPath(nullptr);
    }
    q.push(findVertex(source));
    q.front()->setVisited(true);
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        for (auto e: v->getAdj()) {
            auto w = e->getDest();
            if (!w->isVisited() && e->getWeight() - e->getFlow() > 0) {
                w->setPath(e);
                w->setVisited(true);
                q.push(w);
                if (w->getStation().get_name() == target) return true;
            }
        }
        for (auto e: v->getIncoming()) {
            auto w = e->getOrig();
            if (!w->isVisited() && e->getFlow() != 0) {
                w->setVisited(true);
                w->setPath(e);
                q.push(w);
            }
        }
    }
    return false;
}


