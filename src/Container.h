//
// Created by jotac on 18/05/2021.
//

#ifndef CAL_LAST_CONTAINER_H
#define CAL_LAST_CONTAINER_H

#include <string>

enum GarbageType{
    VIDRO,
    PLASTICO,
    PAPEL,
    METAL,
    ORGANICO,
    NAORECICLAVEL
};

class Container {
    GarbageType garbageType;
    int capacity;
    int volume;
public:
    Container(std::string s, int cap, int vol);
    Container(std::string s, int vol);
    bool hasCapacity(int n);
    bool deposit(int n);
    bool empty();
    int getVolume() const;
    GarbageType getGarbageType() const;

};

GarbageType getGarbageTypeString(std::string type);

std::string getStringGarbageType(GarbageType type);


#endif //CAL_LAST_CONTAINER_H
