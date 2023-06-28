//
// Created by jotac on 18/05/2021.
//

#include "Container.h"

Container::Container(std::string garbageType, int cap, int vol) : capacity(cap), volume(vol) {
    if (garbageType == "plastico") this->garbageType = PLASTICO;
    if (garbageType == "vidro") this->garbageType = VIDRO;
    if (garbageType == "papel") this->garbageType = PAPEL;
    if (garbageType == "metal") this->garbageType = METAL;
    if (garbageType == "organico") this->garbageType = ORGANICO;
    if (garbageType == "naoreciclavel") this->garbageType = NAORECICLAVEL;
}

bool Container::hasCapacity(int n) {
    return n + volume <= capacity;
}

bool Container::deposit(int n) {
    if (hasCapacity(n)){
        volume += n;
        return true;
    }
    return false;
}

bool Container::empty(){
    volume = 0;
    return true;
}

int Container::getVolume() const{
    return volume;
}

GarbageType Container::getGarbageType() const{
    return garbageType;
}

Container::Container(std::string garbageType, int vol) :volume(vol){
    if (garbageType == "plastico") this->garbageType = PLASTICO;
    if (garbageType == "vidro") this->garbageType = VIDRO;
    if (garbageType == "papel") this->garbageType = PAPEL;
    if (garbageType == "metal") this->garbageType = METAL;
    if (garbageType == "organico") this->garbageType = ORGANICO;
    if (garbageType == "naoreciclavel") this->garbageType = NAORECICLAVEL;
    capacity = 0;
}


GarbageType getGarbageTypeString(std::string garbageType) {
    if (garbageType == "plastico") return PLASTICO;
    if (garbageType == "vidro") return VIDRO;
    if (garbageType == "papel") return PAPEL;
    if (garbageType == "metal") return METAL;
    if (garbageType == "organico") return ORGANICO;
    if (garbageType == "naoreciclavel") return NAORECICLAVEL;
}

std::string getStringGarbageType(GarbageType garbageType){
    if (garbageType == PLASTICO) return "plastico";
    if (garbageType == VIDRO) return "vidro";
    if (garbageType == PAPEL) return "papel";
    if (garbageType == METAL) return "metal";
    if (garbageType == ORGANICO) return "organico";
    if (garbageType == NAORECICLAVEL) return "naoreciclavel";
}
