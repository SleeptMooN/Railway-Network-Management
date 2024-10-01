#include <limits>
#include "Menu.h"
#include "Auxiliar.h"
#include "Manager.h"
#include "../data_structures/Graph.h"
#include "../data_structures/Heap.h"
#include "../data_structures/MutablePriorityQueue.h"
#include "../data_structures/UFDS.h"
#include "../data_structures/VertexEdge.h"
using namespace std;

void Menu::mainMenu() {
    title("Main Menu");
    showMenu(menuOptions);

    int key = getInt("Choose an option");
    while (key < 1 || key > 11) key = getInt("Not a valid option. Choose a valid option.");

    switch (key) {
        case 1:
            state = 1;
            break;
        case 2:
            state = 2;
            break;
        case 3:
            state = 3;
            break;
        default:
            state = 11;
    }
}

bool Menu::nextState(vector<Network> &networks, vector<Station> &stations) {
    clearSCR();
    std::string option;
    switch (state) {
        case 0:
            mainMenu();
            return true;
        case 1:
            algoOptions();
            return true;
        case 2:
            costoOptions();
            return true;
        case 3:
            reliabilityoOptions();
            return true;
        case 4:
            first(networks, stations);
            state = 11;
            return true;
        case 5:
            second(networks, stations);
            state = 11;
            return true;
        case 6:
            third(networks, stations);
            state = 11;
            return true;
        case 7:
            fourth(networks, stations);
            state = 11;
            return true;
        case 8:
            fifth(networks, stations);
            state = 11;
            return true;
        case 9:
            sixth(networks, stations);
            state = 11;
            return true;
        case 10:
            seventh(networks, stations);
            state = 11;
            return true;
        default:
            return false;
    }}

void Menu::algoOptions() {
    title("Choose a process:");
    showMenu(basicOptions);

    int key = getInt("Choose an option");
    while (key<1 || key>6){
        key = getInt("Not a valid option. Choose a valid option.");
    }

    switch (key) {
        case 1:
            state = 4;
            break;
        case 2:
            state = 5;
            break;
        case 3:
            state = 6;
            break;
        case 4:
            state = 7;
            break;
        case 5:
            state = 8;
            break;
        default:
            state = 11;
    }
}

void Menu::costoOptions() {
    title("Choose a process:");
    showMenu(costOptions);

    int key = getInt("Choose an option");
    while (key<1 || key>3){
        key = getInt("Not a valid option. Choose a valid option.");
    }

    if(key == 1) state = 9;
    else state = 11;
}

void Menu::reliabilityoOptions() {
    title("Choose a process:");
    showMenu(reliabilityOptions);

    int key = getInt("Choose an option");
    while (key<1 || key>3){
        key = getInt("Not a valid option. Choose a valid option.");
    }

    switch (key) {
        case 1:
            state = 10;
            break;
        case 2:
            state = 11;
            break;
        default:
            state = 11;
    }
}

void Menu::first(vector<Network> &networks, vector<Station> &stations) {
    Manager manager = Manager();
    manager.read_stations(stations);
    manager.read_networks(networks);

    Graph graph = manager.graph;

    for (auto v : manager.graph.getVertexSet()) {
        double cap = 0;
        for (auto e : v->getAdj()) {
            cap += e->getWeight();
        }
        v->setCapacity(cap);
    }

    manager.maxTrainBetweenStations(manager.graph);

    cout << "Thanks for using our program!" << endl;
    cout << "Click Enter!";
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cin.get();
}

void Menu::second(vector<Network> &networks, vector<Station> &stations) {
    Manager manager = Manager();
    manager.read_stations(stations);
    manager.read_networks(networks);

    Graph graph = manager.graph;

    for (auto v : manager.graph.getVertexSet()) {
        double cap = 0;
        for (auto e : v->getAdj()) {
            cap += e->getWeight();
        }
        v->setCapacity(cap);
    }

    manager.maxTrainBetweenStationsPairs();

    cout << "Thanks for using our program!" << endl;
    cout << "Click Enter!";
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cin.get();
}

void Menu::third(vector<Network> &networks, vector<Station> &stations) {
    Manager manager = Manager();
    manager.read_stations(stations);
    manager.read_networks(networks);

    Graph graph = manager.graph;

    for (auto v : manager.graph.getVertexSet()) {
        double cap = 0;
        for (auto e: v->getAdj()) {
            cap += e->getWeight();
        }
        v->setCapacity(cap);
    }

    manager.managementByMunicipalities();

    cout << "Thanks for using our program!" << endl;
    cout << "Click Enter!";
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cin.get();
}

void Menu::fourth(vector<Network> &networks, vector<Station> &stations) {
    Manager manager = Manager();
    manager.read_stations(stations);
    manager.read_networks(networks);

    Graph graph = manager.graph;

    for (auto v : manager.graph.getVertexSet()) {
        double cap = 0;
        for (auto e : v->getAdj()) {
            cap += e->getWeight();
        }
        v->setCapacity(cap);
    }

    manager.managementByDistrict();

    cout << "Thanks for using our program!" << endl;
    cout << "Click Enter!";
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cin.get();
}

void Menu::fifth(vector<Network> &networks, vector<Station> &stations) {
    Manager manager = Manager();
    manager.read_stations(stations);
    manager.read_networks(networks);

    Graph graph = manager.graph;

    for (auto v : manager.graph.getVertexSet()) {
        double cap = 0;
        for (auto e : v->getAdj()) {
            cap += e->getWeight();
        }
        v->setCapacity(cap);
    }

    manager.maxTrainsArrivingAtStation();

    cout << "Thanks for using our program!" << endl;
    cout << "Click Enter!";
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cin.get();
}

void Menu::sixth(vector<Network> &networks, vector<Station> &stations) {
    Manager manager = Manager();
    manager.read_stations(stations);
    manager.read_networks(networks);

    Graph graph = manager.graph;

    for (auto v : manager.graph.getVertexSet()) {
        double cap = 0;
        for (auto e : v->getAdj()) {
            cap += e->getWeight();
        }
        v->setCapacity(cap);
    }

    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    manager.maxTrainsWithMinCost();

    cout << "Thanks for using our program!" << endl;
    cout << "Click Enter!";
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cin.get();
}

void Menu::seventh(vector<Network> &networks, vector<Station> &stations) {
    Manager manager = Manager();
    manager.read_stations(stations);
    manager.read_networks(networks);

    Graph graph = manager.graph;

    for (auto v : manager.graph.getVertexSet()) {
        double cap = 0;
        for (auto e : v->getAdj()) {
            cap += e->getWeight();
        }
        v->setCapacity(cap);
    }

    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    manager.maxTrainsWithReducedConnectivity();

    cout << "Thanks for using our program!" << endl;
    cout << "Click Enter!";
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cin.get();
}