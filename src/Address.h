//
// Created by jotac on 16/05/2021.
//

#ifndef CAL_LAST_ADDRESS_H
#define CAL_LAST_ADDRESS_H

#include <string>
#include <ostream>

enum nodeType {
    COLLECTING,             // collecting trash point
    USER,                   // app user
    CENTRAL,                // recycling central
    REGULAR,                // regular node
};

class Address {

private:

    nodeType type;
    int id;
    std::string name;
    int x,y;
public:
    Address(int id, int x, int y);
    Address(std::string n, int x, int y);
    nodeType getType() const;
    void setType(const nodeType type);
    int getId() const;
    std::string getName();
    int getX() const;
    int getY() const;
    bool operator == (const Address &a2) const;
    bool operator != (const Address &a2) const;

};


#endif //CAL_LAST_ADDRESS_H
