//
// Created by jotac on 16/05/2021.
//

#include "Address.h"

std::string Address::getName() {
    return name;
}

Address::Address(std::string n, int x, int y) : name(n), x(x), y(y){
}

int Address::getX() const {
    return x;
}

int Address::getY() const {
    return y;
}

bool Address::operator==(const Address &a2) const {
    return (name==a2.name && x==a2.x && y==a2.y);
}

Address::Address(int id, int x, int y) : id(id), x(x), y(y){
}

int Address::getId() const {
    return id;
}

bool Address::operator!=(const Address &a2) const {
    return (x!=a2.x || y!=a2.y);
}

nodeType Address::getType() const {
    return type;
}

void Address::setType(const nodeType type) {
    Address::type = type;
}
