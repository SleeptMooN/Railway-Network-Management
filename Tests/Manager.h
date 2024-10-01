#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Station.h"
#include "Network.h"
#include "../data_structures/Graph.h"
using namespace std;

/**
 * @file Manager.h
 * @brief Defines the Manager class for reading and processing network and station data.
 */

#ifndef PROJ1_MANAGER_H
#define PROJ1_MANAGER_H

/**
 * @brief The Manager class manages the reading and processing of input files.
 */
class Manager {
public:
    /**
     * @brief Construct a new Manager object
     */
    Manager();

    Graph graph; /**< The graph that represents the railway network. */

    /**
     * @brief Reads network data from a file and populates the given vector with Network objects.
     *
     * @param networks The vector to populate with Network objects.
     */
    void read_networks(vector<Network> &networks);

    /**
     * @brief Reads station data from a file and populates the given vector with Station objects.
     *
     * @param stations The vector to populate with Station objects.
     */
    void read_stations(vector<Station> &stations);

    /**
     * @brief Prints the given vector of Network objects to the console.
     *
     * @param networks The vector of Network objects to print.
     */
    void print_networks(vector<Network> networks);

    /**
     * @brief Prints the given vector of Station objects to the console.
     *
     * @param stations The vector of Station objects to print.
     */
    void print_stations(vector<Station> stations);

    /**
     * @brief Finds the maximum number of trains that can simultaneously travel between two specific stations.
     *
     * @param graph1 The graph that represents the railway network.
     */
    void maxTrainBetweenStations(Graph graph1); // 2.1

    /**
     * @brief Finds the maximum number of trains that can simultaneously travel between pairs of stations.
     */
    void maxTrainBetweenStationsPairs(); // 2.2

    /**
     * @brief Finds the n districts with the highest average number of stations per municipality.
     *
     */
    void managementByDistrict(); // 2.3

    /**
     * @brief Finds the n municipalities with the highest average number of stations per township.
     *
     */
    void managementByMunicipalities(); // 2.3

    /**
     * @brief Finds the maximum number of trains arriving at a specific station.
     *
     * @param arrivingStation The station to find the maximum number of trains arriving at.
     */
    void maxTrainsArrivingAtStation(); // 2.4

    /**
     * @brief Finds the maximum number of trains that can travel between two specific stations with minimum cost.
     */
    void maxTrainsWithMinCost(); // 3.1

    /**
 * @brief This function performs Dijkstra's shortest path algorithm between two stations.
 *
 * @param first The name of the first station.
 * @param second The name of the second station.
 */
    void dijkstra(std::string first, std::string second); // 3.1 sub-function

/**
 * @brief This function finds the maximum number of trains that can run while maintaining reduced connectivity.
 */
    void maxTrainsWithReducedConnectivity(); // 4.1

/**
 * @brief This function returns a reduced version of the original graph, where each node only has edges to its 2 nearest neighbors.
 *
 * @return The reduced graph.
 */
    Graph reducedGraph(); // 4.1 sub-function

/**
 * @brief This function generates a report of the k most affected stations due to reduced connectivity.
 *
 * @param k The number of stations to include in the report.
 */
    void mostAffectedStationsReport(int k); // 4.2

/**
 * @brief Comparator class for vertices based on their cost.
 */
    class Comparator_Stations {
    public:
        /**
         * @brief Comparison operator for two vertices.
         *
         * @param station_a The first vertex.
         * @param station_b The second vertex.
         * @return True if the cost of station_a is greater than the cost of station_b, false otherwise.
         */
        bool operator()(Vertex *station_a, const Vertex *station_b) {
            return station_a->getCost() > station_b->getCost();
        }
    };
};

#endif //PROJ1_MANAGER_H
