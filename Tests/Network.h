#include <iostream>
#include <string>
using namespace std;
#ifndef PROJ1_NETWORK_H
#define PROJ1_NETWORK_H

/**
    @brief A class representing a network connection between two stations.
 */
class Network {

/**
    * @brief Constructs a new Network object with the given parameters.
    *
    * @param stationA The name of the first station in the network.
    * @param stationB The name of the second station in the network.
    * @param capacity The maximum capacity of the network connection.
    * @param service The name of the service that operates on this network connection.
*/
public:
    Network(string stationA, string stationB, int capacity, string service);

    /**
    * @brief Gets the name of the first station in the network.
    *
    * @return string The name of the first station in the network.
    */
    string get_stationA() const;

    /**
    * @brief Gets the name of the second station in the network.
    *
    * @return string The name of the second station in the network.
    */
    string get_stationB() const;

    /**
    * @brief Gets the maximum capacity of the network connection.
    *
    * @return int The maximum capacity of the network connection.
    */
    int get_capacity() const;

    /**
    * @brief Gets the name of the service that operates on this network connection.
    *
    * @return string The name of the service that operates on this network connection.
    */
    string get_service() const;

    /**
    * @brief Sets the name of the first station in the network.
    *
    * @param nStationA The new name for the first station in the network.
    */
    void set_stationA(string nStationA);

/**
    * @brief Sets the name of the second station in the network.
    *
    * @param nStationB The new name for the second station in the network.
 */
    void set_stationB(string nStationB);

    /**
    * @brief Sets the maximum capacity of the network connection.
    *
    * @param nCapacity The new maximum capacity of the network connection.
    */
    void set_capacity(int nCapacity);

    /**
    * @brief Sets the name of the service that operates on this network connection.
    *
    * @param nService The new name of the service that operates on this network connection.
    */
    void set_service(string nService);

private:
    string stationA;
    string stationB;
    int capacity;
    string service;
};

#endif //PROJ1_NETWORK_H
