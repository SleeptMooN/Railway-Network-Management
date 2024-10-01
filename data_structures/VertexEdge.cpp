// By: Gonçalo Leão

#include "VertexEdge.h"

/************************* Vertex  **************************/


/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
Edge * Vertex::addEdge(Vertex *d, int w, double cost) {
    auto newEdge = new Edge(this, d, w);
    newEdge->set_Cost(cost);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}


/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
bool Vertex::removeEdge(std::string destStation) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        Vertex *dest = edge->getDest();
        if (dest->getStation().get_name() == destStation) {
            it = adj.erase(it);
            // Also remove the corresponding edge from the incoming list
            auto it2 = dest->incoming.begin();
            while (it2 != dest->incoming.end()) {
                if ((*it2)->getOrig()->getStation().get_name() == destStation) {
                    it2 = dest->incoming.erase(it2);
                }
                else {
                    it2++;
                }
            }
            delete edge;
            removedEdge = true; // allows for multiple edges to connect the same pair of vertices (multigraph)
        }
        else {
            it++;
        }
    }
    return removedEdge;
}

bool Vertex::operator<(Vertex & vertex) const {
    return this->dist < vertex.dist;
}

std::vector<Edge*> Vertex::getAdj() const {
    return this->adj;
}

bool Vertex::isVisited() const {
    return this->visited;
}

Edge *Vertex::getPath() const {
    return this->path;
}

std::vector<Edge *> Vertex::getIncoming() const {
    return this->incoming;
}

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

void Vertex::setPath(Edge *path) {
    this->path = path;
}

double const Vertex::getCapacity() {
    return this->capacity;
}

Vertex::Vertex(Station station1) {
    this->station = station1;
}

Station Vertex::getStation() const {
    return this->station;
}

void Vertex::setCapacity(double capacity1) {
    this->capacity = capacity1;
}

double Vertex::getCost() const {
    return this->cost;
}

void Vertex::set_Cost(double cost1) {
    this->cost = cost1;
}

void Vertex::addPathForCost(pair<string, int> pair1) {
    pathForCost.push_back(pair1);
}

vector<pair<string, int>> Vertex::getPathForCost() {
    return this->pathForCost;
}

void Vertex::setPathForCost(vector<pair<string, int>> vec_pair) {
    this->pathForCost = vec_pair;
}


/********************** Edge  ****************************/

Edge::Edge(Vertex *orig, Vertex *dest, int w): orig(orig), dest(dest), weight(w) {}

Vertex * Edge::getDest() const {
    return this->dest;
}

double Edge::getWeight() const {
    return this->weight;
}

Vertex * Edge::getOrig() const {
    return this->orig;
}

Edge *Edge::getReverse() const {
    return this->reverse;
}

bool Edge::isSelected() const {
    return this->selected;
}

int Edge::getFlow() const {
    return flow;
}

void Edge::setSelected(bool selected) {
    this->selected = selected;
}

void Edge::setReverse(Edge *reverse) {
    this->reverse = reverse;
}

void Edge::setFlow(int flow) {
    this->flow = flow;
}

double Edge::get_Cost() const {
    return this->cost;
}

void Edge::set_Cost(double cost1) {
    this->cost = cost1;
}
