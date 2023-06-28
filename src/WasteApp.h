//
// Created by jotac on 16/05/2021.
//

#ifndef CAL_LAST_WASTEAPP_H
#define CAL_LAST_WASTEAPP_H

#include <fstream>
#include <iostream>
#include <cmath>
#include <sstream>

#include "Graph.h"
#include "Address.h"
#include "User.h"
#include "CollectingPoint.h"
#include "GraphViewer/graphviewer.h"


class WasteApp {
    Graph<Address> graph;
    GraphViewer * gv;
    std::vector<User*> users;
    std::vector<User*> homeUsers;
    std::vector<CollectingPoint*> collectingPoints;
    Address * central;
    Address * startingPoint;
    Address * endingPoint;
    std::vector<int>* path;

public:
    WasteApp();

    void addUser(User * user);
    void removeUser(User * user);
    void createUser();
    User* findUser(int id);

    void addHomeUser(User * user);
    void removeHomeUser(User * user);
    //void createHomeUser(User * user);

    void addCollectingPoint(CollectingPoint* CollectingPoint);
    void removeCollectingPoint(CollectingPoint* CollectingPoint);
    void createCollectingPoint();

    std::vector<CollectingPoint*> getCollentingPoints();
    std::vector<User*> getUsers();

    std::vector<int> findContainer(User * user);
    int shortestContainer(User * user, std::vector<CollectingPoint*> col);

    void createGraphViewer(const char * nodeFile, const char * edgeFile);

    void parserMapa1(const char * nodeFile, const char * edgeFile);
    void parserMapaPorto(const char * nodeFile, const char * edgeFile);

    void parseMap(std::string file_path_nodes, std::string file_path_edges, std::string file_path_tags);

    void parseNodes(std::ifstream & fileEdges);

    void parseEdges(std::ifstream & fileEdges);

    void parseTags(std::ifstream & fileTags);

    void parseRandomTags(Graph<Address> &graph);

    nodeType getNodeType(std::string tag);

    void buildGraphViewer(std::vector<int> path);

    void buildGraphViewer();

    GraphViewer * getGraphViewer() const;

    void append_containers(vector<Container> &v1, vector<Container> &v2);

    bool isMatosinhos(Vertex<Address> node);

    bool isStartingNode(Vertex<Address> node);

    bool isFinalNode(Vertex<Address> node);

    void getContainers(unsigned int startingNode, Graph<Address> &graph, vector<Container> &wasteContainers, vector<Container> &recyclingContainers);

    void getMyMapContainers(Graph<Address> &graph, vector<Container> &wasteContainers, vector<Container> &recyclingContainers);

    void printProgressBar(float current, float total);

    void addEdgeGV(User * user);

    std::vector<int>* getPath() const;

    void setPath(std::vector<int> path);
};


#endif //CAL_LAST_WASTEAPP_H
