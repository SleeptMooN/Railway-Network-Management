/**
 * @file Menu.h
 * @brief Defines the Menu class and its member functions
 */

#ifndef PROJ1_MENU_H
#define PROJ1_MENU_H

#include "vector"
#include "string"
#include "Network.h"
#include "Station.h"
#include "Manager.h"

using namespace std;

/**
 * @brief A class representing the menu of the train network system
 */
class Menu {
private:
    vector<string> menuOptions = {"Basic Service Metrics", "Operation Cost Optimization", "Reliability and Sensitivity to Line Failures", "Exit"}; /**< An array containing the main menu options */
    vector<string> basicOptions = {"Maximum number of trains that can simultaneously travel between two specific stations", "Which pair of stations require the most amount of trains when taking full advantage of the existing network capacity", "Assign larger budgets for the purchasing and maintenance of trains by municipalities", "Assign larger budgets for the purchasing and maintenance of trains by district", "Maximum number of trains that can simultaneously arrive at a given station", "Exit"}; /**< An array containing the algorithm menu options */
    vector<string> costOptions = {"Maximum amount of trains that can simultaneously travel between two specific stations with minimum cost for the company", "Exit"};
    vector<string> reliabilityOptions = {"Maximum number of trains that can simultaneously travel between two specific stations in a network of reduced connectivity", "Report on the stations that are the most affected by each segment failure", "Exit"};

    int state = 0; /**< An integer representing the current state of the menu */
    /**
     * @brief Displays the algorithm options menu
     */
    void algoOptions();
    /**
     * @brief Displays the cost options menu
     */
    void costoOptions();
    /**
     * @brief Displays the reliability options menu
     */
    void reliabilityoOptions();
    /**
     * @brief Displays the main menu
     */
    void mainMenu();
    /**
     * @brief Runs the first scenario
     * @param packages A vector of Network objects representing the network of the train system
     * @param stations A vector of Station objects representing the stations of the train system
     */
    void first(vector<Network>& packages, vector<Station>& stations);
    /**
     * @brief Runs the second scenario
     * @param packages A vector of Network objects representing the network of the train system
     * @param stations A vector of Station objects representing the stations of the train system
     */
    void second(vector<Network>& packages, vector<Station>& stations);
    /**
    * @brief Runs the second scenario
    * @param packages A vector of Network objects representing the network of the train system
    * @param stations A vector of Station objects representing the stations of the train system
    */
    void third(vector<Network>& packages, vector<Station>& stations);
    /**
    * @brief Runs the third scenario
    * @param packages A vector of Network objects representing the network of the train system
    * @param stations A vector of Station objects representing the stations of the train system
    */
    void fourth(vector<Network>& packages, vector<Station>& stations);
    /**
    * @brief Runs the second scenario
    * @param packages A vector of Network objects representing the network of the train system
    * @param stations A vector of Station objects representing the stations of the train system
    */
    void fifth(vector<Network>& packages, vector<Station>& stations);
    /**
    * @brief Runs the second scenario
    * @param packages A vector of Network objects representing the network of the train system
    * @param stations A vector of Station objects representing the stations of the train system
    */
    void sixth(vector<Network>& packages, vector<Station>& stations);
    /**
    * @brief Runs the second scenario
    * @param packages A vector of Network objects representing the network of the train system
    * @param stations A vector of Station objects representing the stations of the train system
    */
    void seventh(vector<Network>& packages, vector<Station>& stations);

public:
    /**
     * @brief Helps connecting the main function and the rest of the program
     * @param packages A vector of Network objects representing the network of the train system
     * @param stations A vector of Station objects representing the stations of the train system
     * @return A boolean value indicating whether the program should continue running or not
     */
    bool nextState(vector<Network>& packages, vector<Station>& stations);
};

#endif //PROJ1_MENU_H
