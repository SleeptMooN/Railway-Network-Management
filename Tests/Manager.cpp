#include "Manager.h"
#include <limits>
#include <queue>
#include <iostream>
#include <vector>
#include <unordered_map>
/**
 * This function reads the networks.csv file.
 * @param networks
 */
void Manager::read_networks(vector<Network> &networks) {
    string stationA;
    string stationB;
    string capacity_str;
    int capacity;
    string service;
    string dummy;

    ifstream input;
    input.open("../dataset/network.csv");
    if (input.is_open()) {
        getline(input, dummy);
        while (input.good()) {
            getline(input, stationA, ',');
            getline(input, stationB, ',');
            getline(input, capacity_str, ',');
            getline(input, service, '\n');

            capacity = stoi(capacity_str);
            Network network(stationA, stationB, capacity, service);
            double cost = 0.0;
            if (service[service.size() - 1] == '\r')
                service.erase(service.size() - 1);
            if (service == "STANDARD") cost = 2.0;
            else if (service == "ALFA PENDULAR") cost = 4.0;
            graph.addBidirectionalEdge(stationA, stationB, capacity/2, cost);
            networks.push_back(network);
        }
    }
    else {
        cout << "ERROR: File Not Open" << '\n';
    }
    input.close();
    networks.pop_back();
}

/**
 * This function prints the networks.
 * @param networks
 */
void Manager::print_networks(vector<Network> networks) {
    for (auto &i : networks) {
        cout << i.get_stationA() << ", " << i.get_stationB() << ", " << i.get_capacity() << ", " << i.get_service() << endl;
    }
}

/**
 * This function reads the stations.csv file.
 */
void Manager::read_stations(vector<Station> &stations) {
    string name;
    string district;
    string municipality;
    string township;
    string line;
    string dummy;

    ifstream input;
    input.open("../dataset/stations.csv");
    if (input.is_open()) {
        getline(input, dummy);
        while (input.good()) {
            getline(input, name, ',');
            getline(input, district, ',');
            getline(input, municipality, ',');
            getline(input, township, ',');
            getline(input, line, '\n');

            Station station(name, district, municipality, township, line);
            graph.addVertex(station);
            stations.push_back(station);
        }
    }
    else {
        cout << "ERROR: File Not Open" << '\n';
    }
    input.close();
    stations.pop_back();
}

/**
 *  This function prints the stations.csv file.
 */
void Manager::print_stations(vector<Station> stations) {
    for (auto &i : stations) {
        cout << i.get_name() << ", " << i.get_district() << ", " << i.get_municipality() << ", " << i.get_township() << ", " << i.get_line() << endl;
    }
}

Manager::Manager() {

}

// 2.1
/**
 * The overall time complexity of this function is O(V * E^2),
 * where V is the number of vertices and E is the number of edges in the input graph.
 */
void Manager::maxTrainBetweenStations(Graph graph1) {
    std::string station_a, station_b;

    std::cout << "Station A: ";
    getline(std::cin >> ws , station_a);

    std::cout << "Station B: ";
    getline(std::cin >> ws , station_b);

    int max_trains = graph1.edmondsKarp(station_a, station_b);

    std::cout << "Max number of trains between " << station_a << " and " << station_b << ": " << max_trains << "\n";
}

// 2.2
/**
 * The time complexity of this function is O(V^3 * E^2),
 * where V is the number of vertices and E is the number of edges in the graph.
 * This is because there are two nested loops iterating over all the vertices in the graph,
 * and the edmondsKarp function is called for each pair of vertices, which has a time complexity of O(V * E^2).
 * Additionally, the getVertexSet and getAdj functions have a time complexity of O(V + E) each,
 * so their time complexity is also included in the overall time complexity.
 * Therefore, the overall time complexity is O(V^3 * E^2).
 */
void Manager::maxTrainBetweenStationsPairs() {
    vector<pair<pair<string, string>, int>> max_pairs;
    int max_trains = 0;
    std::string v1;
    std::string v2;
    for (auto i : graph.getVertexSet()){
        for (auto j : graph.getVertexSet()){
            if (i != j) {
                int a = graph.edmondsKarp(i->getStation().get_name(), j->getStation().get_name());
                for (auto v : graph.getVertexSet()) {
                    for (auto e : v->getAdj()) {
                        e->setFlow(0);
                    }
                }
                if (a > max_trains) {
                    max_pairs.clear();
                    max_pairs.emplace_back(std::make_pair(i->getStation().get_name(), j->getStation().get_name()), a);
                    max_trains = a;
                    v1 = i->getStation().get_name();
                    v2 = j->getStation().get_name();
                }
                else if (a == max_trains) {
                    max_trains = a;
                    max_pairs.emplace_back(std::make_pair(i->getStation().get_name(), j->getStation().get_name()), a);
                    v1 = i->getStation().get_name();
                    v2 = j->getStation().get_name();
                }
            }
        }
    }

    for (int i = 0; i < max_pairs.size(); i++) {
        std::cout << "Max number of trains between " << max_pairs[i].first.first << " and " << max_pairs[i].first.second << ": " << max_pairs[i].second << "\n";
    }
}

// 2.4
/**
 * O(E * V^2).
 * Report the maximum number of trains that can simultaneously arrive at a given station,
taking into consideration the entire railway grid.
 * @param arrivingStation
 */
void Manager::maxTrainsArrivingAtStation() {
    std::string arrivingStation;
    std::cout << "Arriving station: ";
    getline(std::cin >> ws , arrivingStation);
    std::vector<std::string> stat;
    Station station("st", "none", "none", "none", "none");
    graph.addVertex(station);
    for (auto s: graph.getVertexSet()) {
        if (s->getAdj().size() == 1 && (s->getStation().get_name() != arrivingStation) && (s->getStation().get_name()!=station.get_name()))
            stat.push_back(s->getStation().get_name());
    }
    for (auto stname : stat){
        graph.addEdge("st", stname, std::numeric_limits<int>::max(), 2.0);
    }

    double result = graph.edmondsKarp("st", arrivingStation);
    result /= 2;
    for (auto v : graph.getVertexSet()) {
        if (v->getStation().get_name() == "st") {
            for (auto stname : stat) {
                v->removeEdge(stname);
            }
        }
    }
    std::cout << "The maximum number of trains that can simultaneously arrive at the station of " << arrivingStation << " is : " << result*2 << '\n';
}

// 2.3 - Districts
/**
  * O(V log V)
  * Calculates the number of trains in each district and outputs the top n districts in descending order.
  * @param n The number of districts to output.
*/
void Manager::managementByDistrict() {
    std::string num;
    std::cout << "Number: ";
    getline(std::cin >> ws , num);
    int number;
    number = stoi(num);
    unordered_map<string, int> result;
    for(auto c: graph.getVertexSet()){
        result[c->getStation().get_district()] += c->getCapacity();
    }
    vector<pair<string, int>> vec(result.begin(), result.end());

    // Sort the vector by the second element (the value) in descending order
    sort(vec.begin(), vec.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
    });
    int max = vec[0].second;
    auto c = vec.begin();
    int i = 1;
    while(number>0){
        if(c->second<max){
            number--;
            if(number==0)break;
            i++;
        }
        cout <<"In "<<i<<"º place, the district of "<< c->first << " has: " << c->second << " trains." << endl;
        c++;
    }
}

// 2.3 - Municipalities
/**
 * O(V log V)
 * Calculates the number of trains in each municipality and outputs the top n municipalities in descending order.
 * @param n The number of municipalities to output.
 */
void Manager::managementByMunicipalities() {
    std::string num;
    std::cout << "Number: ";
    getline(std::cin >> ws , num);
    int number;
    number = stoi(num);
    unordered_map<string, int> result;
    for(auto c: graph.getVertexSet()){
        result[c->getStation().get_municipality()] += c->getCapacity();
    }
    vector<pair<string, int>> vec(result.begin(), result.end());

    // Sort the vector by the second element (the value) in descending order
    sort(vec.begin(), vec.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
    });
    int max = vec[0].second;
    auto c = vec.begin();
    int i = 1;
    while(number>0){
        if(c->second<max){
            number--;
            if(number==0)break;
            i++;
        }
        cout <<"In "<<i<<"º place, the municipality of "<< c->first << " has: " << c->second << " trains." << endl;
        c++;
    }
}

/**
 * The time complexity of Dijkstra's algorithm is O(E log V), where E is the number of edges and V is the number of vertices in the graph.
 * @param first
 * @param second
 */
void Manager::dijkstra(string first, string second) {
    std::priority_queue<Vertex*, std::vector<Vertex*>, Comparator_Stations> aux;
    double flow = numeric_limits<int>::max();
    Vertex* startNode = graph.findVertex(first);
    startNode->set_Cost(0.0);
    startNode->addPathForCost({first, numeric_limits<int>::max()});
    aux.push(startNode);
    while (!aux.empty()) {
        Vertex* currentVertex = aux.top();
        aux.pop();
        if (currentVertex->isVisited()) {
            continue;
        }
        currentVertex->setVisited(true);
        if(currentVertex->getStation().get_name() == graph.findVertex(second)->getStation().get_name()) {
            std::cout << "Shortest path from " << first << " to " << second << " is: " << endl;
            for (auto node : currentVertex->getPathForCost()) {
                std::cout << " " << node.first<< endl;
                if (node.second < flow) {
                    flow = node.second;
                }
            }
            std::cout << " (cost without flow = " << currentVertex->getCost()<<")" << std::endl;
            std::cout << " (cost with flow = " << currentVertex->getCost() * flow  <<")" << std::endl;
            return;
        }
        for (auto edge : currentVertex->getAdj()) {
            Vertex* nextNode = edge->getDest();
            if (!nextNode->isVisited()) {
                double newCost = currentVertex->getCost() + edge->get_Cost();
                if (newCost < nextNode->getCost()) {
                    nextNode->set_Cost(newCost);
                    nextNode->setPath(edge);
                    nextNode->setPathForCost(currentVertex->getPathForCost());
                    nextNode->addPathForCost({nextNode->getStation().get_name(), edge->getWeight()});
                    aux.push(nextNode);
                }
            }
        }
    }
}

// 3.1

/**
 * O(E log V)
 * Calculate the maximum amount of trains that can simultaneously travel between
two specific stations with minimum cost for the company. Note that your system should also take any
valid source and destination stations as input;
 */
void Manager::maxTrainsWithMinCost() {
    std::string station_A, station_B;

    std::cout << "First station: ";
    getline(std::cin, station_A);
    cin.ignore();
    Vertex* source = graph.findVertex(station_A);
    if (source == nullptr) {
        std::cout << "This station doesn't exists!\n";
        return;
    }

    std::cout << "Second station: ";
    getline(std::cin, station_B);
    cin.ignore();
    Vertex* dest = graph.findVertex(station_B);
    if (dest == nullptr) {
        std::cout << "This station doesn't exists!\n";
        return;
    }
    dijkstra(station_A, station_B);

    int flow = std::numeric_limits<int>::max();
    //int cost = dest->getCost();

    Vertex* auxiliar = dest;
    while (auxiliar->getStation().get_name() != station_A) {
        if (flow > auxiliar->getPath()->getWeight()) {
            flow = auxiliar->getPath()->getWeight();
        }
        auxiliar = auxiliar->getPath()->getOrig();
    }

    std::cout << "The minimum cost from " << station_A << " to " << station_B << " is " << flow << "." << '\n';
}

// 4.1
/**
  * O(V^2 + E)
  * Removes stations or edges from the graph to create a reduced version of the original graph.
*/
Graph Manager::reducedGraph() {
    Graph graph_reduced = Graph(graph);
    bool rm_stations = true, rm_edges = true;
    std::string answer1;
    cout << "Do you want to remove a station? (y/n) ";
    getline(std::cin, answer1);
    if (answer1 == "n") {
        rm_stations = false;
    }
    while (rm_stations) {
        std::string st_name;
        cout << "Which station do you want to remove (due to repairs, services, disasters, etc)? ";
        getline(std::cin, st_name);
        Vertex* v = graph.findVertex(st_name);
        if (v == nullptr) {
            std::cout << "This station doesn't exists!\n";
            continue;
        }

        graph_reduced.removeVertex(st_name);

        std::string answer;
        cout << "Do you want remove another one (answer y/n)? ";
        getline(std::cin, answer);
        if (answer == "n"){
            rm_stations = false;
        }
    }
    std::string answer2;
    cout << "Do you want to remove a edge/connection? (y/n) ";
    getline(std::cin, answer2);
    if (answer2 == "n") {
        rm_edges = false;
    }
    while (rm_edges) {
        std::string st_source, st_dest;
        cout << "Source station? ";
        getline(std::cin, st_source);
        cout << "Destination station? ";
        getline(std::cin, st_dest);
        Vertex* src = graph.findVertex(st_source);
        Vertex* dest = graph.findVertex(st_dest);
        if (src == nullptr || dest == nullptr) {
            std::cout << "One of this stations doesn't exists!\n";
            continue;
        }

        for (auto e : src->getAdj()) {
            if (e->getDest() == dest) {
                src->removeEdge(st_dest);
            }
        }

        std::string answer;
        cout << "Do you want remove another one (answer y/n)? ";
        getline(std::cin, answer);
        if (answer == "n"){
            rm_edges = false;
        }
    }
    return graph_reduced;
}

// 4.1
void Manager::maxTrainsWithReducedConnectivity() {
    Graph reduced_graph = reducedGraph();
    maxTrainBetweenStations(reduced_graph);
}

// 4.2
void Manager::mostAffectedStationsReport(int k) {
    // we tried ahah :)
    cout << "Doesn`t work." << endl;
}
