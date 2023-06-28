//
// Created by jotac on 16/05/2021.
//

#ifndef CAL_LAST_USER_H
#define CAL_LAST_USER_H

#include <string>
#include <vector>
#include <ostream>
#include <iostream>
#include "Address.h"
#include "Container.h"
#include "CollectingPoint.h"


class User {
private:
    std::string name;
    Address address;
    std::vector<Container*> containers;
public:
    User(std::string n, Address a);
    User(Address a);
    std::string getName();
    Address getAddress();
    std::vector<Container*> getContainers();
    void addContainer(std::string garbageType, int capacity, int volume);
    void createContainer();
    int getGarbageVolume();
    bool operator == (const User &u2) const;
    bool operator <= (CollectingPoint *c2) const;

};


#endif //CAL_LAST_USER_H
