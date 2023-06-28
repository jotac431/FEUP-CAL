//
// Created by jotac on 16/05/2021.
//

#ifndef CAL_LAST_COLLECTINGPOINT_H
#define CAL_LAST_COLLECTINGPOINT_H

#include <vector>
#include <iostream>
#include "Address.h"
#include "Container.h"

class CollectingPoint {
    Address address;
    std::vector<Container*> containers;
public:
    CollectingPoint(Address a);
    Address getAddress();
    std::vector<Container*> getContainers() const;
    void addContainer(std::string garbageType, int capacity, int volume);
    void createContainer();
};


#endif //CAL_LAST_COLLECTINGPOINT_H
