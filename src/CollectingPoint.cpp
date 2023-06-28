//
// Created by jotac on 16/05/2021.
//

#include "CollectingPoint.h"

Address CollectingPoint::getAddress() {
    return address;
}

CollectingPoint::CollectingPoint(Address a) : address(a) {
    addContainer("plastico", 500, 0);
    addContainer("vidro", 500, 0);
    addContainer("papel", 500, 0);
    addContainer("metal", 500, 0);
    addContainer("organico", 500, 0);
    addContainer("naoreciclavel", 500, 0);
}

std::vector<Container*> CollectingPoint::getContainers() const{
    return containers;
}

void CollectingPoint::addContainer(std::string garbageType, int capacity, int volume) {
    containers.push_back(new Container(garbageType, capacity, volume));
}

void CollectingPoint::createContainer() {
    std::string garbage;
    int volume, capacity;
    std::cout << "\nType of Garbage: ";
    std::cin >> garbage;
    std::cout << "\nVolume: ";
    std::cin >> volume;
    std::cout << "\nCapacity: ";
    std::cin >> capacity;
    addContainer(garbage, capacity, volume);
}
