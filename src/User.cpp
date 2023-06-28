//
// Created by jotac on 16/05/2021.
//

#include "User.h"

std::string User::getName() {
    return name;
}

Address User::getAddress() {
    return address;
}

User::User(std::string n, Address a) : name(n), address(a){
}

User::User(Address a) : address(a){
    addContainer("plastico", 99999999, 0);
    addContainer("vidro", 99999999, 0);
    addContainer("papel", 99999999, 0);
    addContainer("metal", 99999999, 0);
    addContainer("organico", 99999999, 0);
    addContainer("naoreciclavel", 99999999, 0);
}

bool User::operator==(const User &u2) const {
    return (name==u2.name && address==u2.address);
}

std::vector<Container*> User::getContainers() {
    return containers;
}

void User::addContainer(std::string garbageType, int capacity, int volume) {
    containers.push_back(new Container(garbageType, capacity, volume));
}

void User::createContainer() {
    std::string garbage;
    int volume, capacity;
    std::cout << "\nType of Garbage: ";
    std::cin >> garbage;
    while(garbage != "plastico" && garbage != "papel" && garbage != "vidro" && garbage != "metal" && garbage != "naoreciclavel" && garbage != "organico" )
    {
        std::cin.clear();
        std::cin.ignore(100, '\n');
        std::cout << "Please enter a valid type:\n";
        std::cin >> garbage;
    }
    std::cout << "\nVolume: ";
    std::cin >> volume;
    for(Container* container : containers){
        if(container->getGarbageType() == getGarbageTypeString(garbage)){
            container->deposit(volume);
        }
    }
    //addContainer(garbage, 0, volume);
}

int User::getGarbageVolume() {
    int cnt;
    for (int i = 0; i < containers.size(); ++i) {
        cnt += containers.at(i)->getVolume();
    }
    return cnt;
}

bool User::operator<=(CollectingPoint *c2) const {
    bool check = true;
    for (int i = 0; i < containers.size(); ++i) {
        if (!check) break;
        bool hasElement = false;
        for (int j = 0; j < c2->getContainers().size(); ++j) {
            if (containers.at(i)->getGarbageType() == c2->getContainers().at(j)->getGarbageType()){
                hasElement = true;
                if (!c2->getContainers().at(j)->hasCapacity(containers.at(i)->getVolume())){
                    check = false;
                    break;
                }
            }
        }

        if (!hasElement) {
            check = false;
            break;
        }
    }

    return check;
}


