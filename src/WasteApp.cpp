//
// Created by jotac on 16/05/2021.
//

#include "WasteApp.h"

void WasteApp::addUser(User *user) {
    users.push_back(user);
}

void WasteApp::addHomeUser(User *user) {
    homeUsers.push_back(user);
}

void WasteApp::removeUser(User *user) {
    auto u = users.begin();
    for (; u < users.end(); u++) {
        if (user == (*u)){
            users.erase(u);
        }
    }
}

void WasteApp::removeHomeUser(User *user) {
    auto u = homeUsers.begin();
    for (; u < homeUsers.end(); u++) {
        if (user == (*u)){
            homeUsers.erase(u);
        }
    }
}

void WasteApp::addCollectingPoint(CollectingPoint *collectingPoint) {
    collectingPoints.push_back(collectingPoint);
}

void WasteApp::removeCollectingPoint(CollectingPoint *collectingPoint) {
    auto u = collectingPoints.begin();
    for (; u < collectingPoints.end(); u++) {
        if (collectingPoint == (*u)){
            collectingPoints.erase(u);
        }
    }
}

WasteApp::WasteApp(){
    path = new std::vector<int>();
    this->gv = new GraphViewer(600, 600, false);
}

void WasteApp::createUser() {
    std::string name;
    int id;
    while(true){
        std::cout << "\nUser name: ";
        std::cin >> name;
        std::cout << "\nAddress ID: ";
        std::cin >> id;
        auto v1 = graph.findVertex(id);
        if (v1 != NULL) {
            addUser(new User(name, *v1->getInfo()));
            gv->setVertexColor(id, "orange");
            gv->rearrange();
            return;
        }
        std::cout << "\nInvalid Address";
    }
}

void WasteApp::createCollectingPoint() {
    int id;
    while (true) {
        std::cout << "\nAddress ID: ";
        std::cin >> id;
        auto v1 = graph.findVertex(id);
        if (v1 != NULL) {
            addCollectingPoint(new CollectingPoint(*v1->getInfo()));
            break;
        }
    }
}

/*void WasteApp::createHomeUser(User * user) {
    int volume;
    std::cout << "\nVolume: ";
    std::cin >> volume;
    user->setVolume(volume);
    addHomeUser(user);
}*/

std::vector<CollectingPoint *> WasteApp::getCollentingPoints() {
    return collectingPoints;
}

std::vector<User *> WasteApp::getUsers() {
    return users;
}

std::vector<int> WasteApp::findContainer(User *user) {

    graph.dijkstraShortestPath(user->getAddress());
    std::vector<CollectingPoint*> col;
    for (int i = 0; i < collectingPoints.size(); ++i) {
        if (*user <= collectingPoints.at(i)){
            col.push_back(collectingPoints.at(i));
        }
    }

    if(col.size() == 0){
        cout << "Nao foi encontrado um contentor com capacidade suficiente" << endl;
        return std::vector<int>();
    }

    int shor = shortestContainer(user, col);
    std::cout << "\nShortest Container: " << shor;
    std::cout << "\nShortest path: ";
    auto v1 = graph.findVertex(shor);
    std::vector<Address> a = graph.getPath(user->getAddress(), *v1->getInfo());
    std::vector<int> b = graph.getEdgePath(user->getAddress(), *v1->getInfo());
    for (auto ad : a){
        std::cout << ad.getId() << " ";
    }
    std::cout << "\nShortest Edge path: ";
    for (auto bb : b){
        std::cout << bb << " ";
    }

    b.erase(b.begin());

    for (int i = 0; i < collectingPoints.size(); ++i) {
        if (collectingPoints.at(i)->getAddress().getId() == shor){
            for(Container* container1 : collectingPoints.at(i)->getContainers()){
                for(Container* container2 : user->getContainers()){
                    if(container1->getGarbageType() == container2->getGarbageType())
                        container1->deposit(container2->getVolume());
                        container2->empty();
                }
            }
        }
    }



    return b;

}

int WasteApp::shortestContainer(User *user, std::vector<CollectingPoint *> col) {
    int shor = col.at(0)->getAddress().getId();
    for (int i = 1; i < col.size(); ++i) {
        auto v1 = graph.findVertex(shor);
        auto v2 = graph.findVertex(col.at(i)->getAddress().getId());
        if (v2->getDist() < v1->getDist()){
            shor = v2->getInfo()->getId();
        }
    }
    return shor;
}


void WasteApp::parseMap(std::string file_path_nodes, std::string file_path_edges, std::string file_path_tags) {


    // ---- git Opening files
    std::ifstream fileNodes(file_path_nodes);
    std::ifstream fileEdges(file_path_edges);
    std::ifstream fileTags(file_path_tags);

    if(!fileNodes.is_open()) {
        cout << "ERROR: opening file in " << file_path_nodes << endl;
        exit(EXIT_FAILURE);
    } else if (!fileEdges.is_open()) {
        cout << "ERROR: opening file in " << file_path_edges << endl;
        exit(EXIT_FAILURE);
    } else if (!fileTags.is_open()) {
        cout << "ERROR: opening file in " << file_path_tags << endl;
        exit(EXIT_FAILURE);
    }

    // ---- parsing nodes
    parseNodes(fileNodes);
    fileNodes.close();

    // ---- parsing edges
    parseEdges(fileEdges);
    fileEdges.close();

    // ---- parsing tags
    /*if (file_path_tags == MYMAP_TAGS_MAP)
        parseRandomTags(returnGraph);
    else*/
        parseTags(fileTags);
    //fileTags.close();


}

void WasteApp::parseNodes(std::ifstream & fileNodes) {
    string line;

    int idNo=0;
    int X=0;
    int Y=0;
    int cnt = 0;

    while(getline(fileNodes, line))
    {
        cnt++;

        if (cnt%1000 == 0) {
            cout << "A carregar vertices" << endl;
            printProgressBar(cnt, 26000);
        }

        stringstream linestream(line);
        string         data;

        linestream >> idNo;

        getline(linestream, data, ';');  // read up-to the first ; (discard ;).
        linestream >> X;
        getline(linestream, data, ';');  // read up-to the first ; (discard ;).
        linestream >> Y;
        Address a(idNo, X, Y);
        graph.addVertex(idNo, a);

    }
}

void WasteApp::parseEdges(std::ifstream & fileEdges) {
    string line;

    int idAresta=0;
    int idNoOrigem=0;
    int idNoDestino=0;
    int cnt = 0;

    while(getline(fileEdges, line))
    {
        cnt++;

        if (cnt%1000 == 0) {
            cout << "A carregar arestas" << endl;
            printProgressBar(cnt, 29000);
        }

        stringstream linestream(line);
        string data;

        linestream >> idNoOrigem;
        getline(linestream, data, ';');  // read up-to the first ; (discard ;).
        linestream >> idNoDestino;

        auto v1 = graph.findVertex(idNoOrigem);
        auto v2 = graph.findVertex(idNoDestino);

        if (v1 != NULL && v2 != NULL){

            double w = sqrt(pow(v2->getInfo()->getX() - v1->getInfo()->getX(),2) + pow(v2->getInfo()->getY() - v1->getInfo()->getY(),2));

            graph.addEdge(idAresta, *v1->getInfo(), *v2->getInfo(), w);
        }

        idAresta++;
    }
}

void WasteApp::parseTags(std::ifstream & fileTags) {

    std::string currLine = "";
    int cnt = 0;
    getline(fileTags, currLine);

    while(!fileTags.eof()) {

        cnt++;

        if (cnt%1000 == 0) {
            cout << "A carregar tags" << endl;
            printProgressBar(cnt, 2200);
        }


        // ---- getting type
        getline(fileTags, currLine);
        std::string tag = currLine;
        nodeType type = getNodeType(currLine);
        // ---- getting number of tags of the same type
        getline(fileTags, currLine);
        int num_iter = stoi(currLine);

        // ---- getting tags
        for(int i = 0; i < num_iter; i++) {
            getline(fileTags, currLine);
            unsigned int nodeID = stoi(currLine);
            auto a = graph.findVertex(nodeID)->getInfo();
            a->setType(type);
            if(type == COLLECTING){
                collectingPoints.push_back(new CollectingPoint(*a));
            }
            else if(type == USER){
                users.push_back(new User(*a));
            }
        }
    }
}
/*
void WasteApp::parseRandomTags(Graph<Address> &graph) {

    // ---- generate random non repeating nodes
    srand(time(0));

    vector<unsigned int> randomNodeIDs;

    for(int i = 2; i < 900; i++) {
        randomNodeIDs.push_back(i);
    } 1875969802

    random_shuffle(randomNodeIDs.begin(), randomNodeIDs.end());


    for (int i = 0; i < 30; i++) {
        graph.getNode(randomNodeIDs.at(i)).setType(COLLECTING);
    }

    for (int i = 30; i < 60; i++) {
        graph.getNode(randomNodeIDs.at(i)).setType(USER);
    }
}
*/
nodeType WasteApp::getNodeType(std::string tag) {
    if (tag == "collecting")
        return COLLECTING;
    else if (tag == "user")
        return USER;
    else if (tag == "central")
        return CENTRAL;
    else
        return REGULAR;
}

void WasteApp::buildGraphViewer() {

    gv->createWindow(900, 900);
    gv->defineVertexColor("blue");
    gv->defineEdgeColor("black");

    /*double yPercent, xPercent;

    auto n = graph.getVertexSet().at(0);

    double minX = n->getInfo()->getX();
    double minY = n->getInfo()->getY();
    double maxX = n->getInfo()->getX();
    double maxY = n->getInfo()->getY();

    for (int i = 0; i < graph.getVertexSet().size(); ++i) {

        auto n = graph.getVertexSet().at(i);

        if (n->getInfo()->getX() > maxX) {
            maxX = n->getInfo()->getX();
        } else if (n->getInfo()->getX() < minX) {
            minX = n->getInfo()->getX();
        }

        if (n->getInfo()->getY() > maxY) {
            maxY = n->getInfo()->getY();
        } else if (n->getInfo()->getY() < minY) {
            minY = n->getInfo()->getY();
        }
    }


    double graphHeight = maxY - minY;
    double graphWidth = maxX - minX;
*/

    for (int i = 0; i < graph.getVertexSet().size(); ++i) {
        auto n = graph.getVertexSet().at(i);

        /*xPercent = (n->getInfo()->getX() - minX) / graphWidth;
        yPercent = 1.0 - ((n->getInfo()->getY() - minY) / graphHeight);*/

        gv->addNode(n->getInfo()->getId(), n->getInfo()->getX(), n->getInfo()->getY());


        switch (n->getInfo()->getType()) {

            case CENTRAL:
                gv->setVertexColor(n->getInfo()->getId(), "red");
                break;
            case COLLECTING:
                gv->setVertexColor(n->getInfo()->getId(), "green");
                break;
            case USER:
                gv->setVertexColor(n->getInfo()->getId(), "yellow");
                break;
            default:
                break;
        }



        // ---- drawing starting and ending points
        /*if (isStartingNode(*n))
            gv->setVertexColor(n->getInfo().getId(), "cyan");
        if (isFinalNode(*n))
            gv->setVertexColor(n->getInfo().getId(), "red");*/
    }



    vector<Edge<Address>> edges;

    for (int i = 0; i < graph.getVertexSet().size(); ++i) {
        auto n = graph.getVertexSet().at(i);
        edges = n->getEdges();
        for (auto e : edges) {
            gv->removeEdge(e.getID());
            gv->addEdge(e.getID(), n->getInfo()->getId(), e.getDest()->getInfo()->getId(), EdgeType::DIRECTED);
        }
    }

    gv->rearrange();

}

void WasteApp::buildGraphViewer(std::vector<int> path) {

    gv->createWindow(900, 900);
    gv->defineVertexColor("blue");
    gv->defineEdgeColor("black");

    double yPercent, xPercent;

    auto n = graph.getVertexSet().at(0);

    double minX = n->getInfo()->getX();
    double minY = n->getInfo()->getY();
    double maxX = n->getInfo()->getX();
    double maxY = n->getInfo()->getY();

    for (int i = 0; i < graph.getVertexSet().size(); ++i) {

        auto n = graph.getVertexSet().at(i);

        if (n->getInfo()->getX() > maxX) {
            maxX = n->getInfo()->getX();
        } else if (n->getInfo()->getX() < minX) {
            minX = n->getInfo()->getX();
        }

        if (n->getInfo()->getY() > maxY) {
            maxY = n->getInfo()->getY();
        } else if (n->getInfo()->getY() < minY) {
            minY = n->getInfo()->getY();
        }
    }


    double graphHeight = maxY - minY;
    double graphWidth = maxX - minX;

    for (int i = 0; i < graph.getVertexSet().size(); ++i) {
        auto n = graph.getVertexSet().at(i);

        xPercent = (n->getInfo()->getX() - abs(minX)) / graphWidth;
        yPercent = 1.0 - ((n->getInfo()->getY() - abs(minY)) / graphHeight);

        gv->addNode(n->getInfo()->getId(), (int) (xPercent * 4000), (int) (yPercent * 2000));


        switch (n->getInfo()->getType()) {

            case CENTRAL:
                gv->setVertexColor(n->getInfo()->getId(), "red");
                break;
            case COLLECTING:
                gv->setVertexColor(n->getInfo()->getId(), "green");
                break;
            case USER:
                gv->setVertexColor(n->getInfo()->getId(), "yellow");
                break;
            default:
                break;
        }



        // ---- drawing starting and ending points
        /*if (isStartingNode(*n))
            gv->setVertexColor(n->getInfo().getId(), "cyan");
        if (isFinalNode(*n))
            gv->setVertexColor(n->getInfo().getId(), "red");*/
    }



    vector<Edge<Address>> edges;

    for (int i = 0; i < graph.getVertexSet().size(); ++i) {
        auto n = graph.getVertexSet().at(i);
        edges = n->getEdges();
        for (auto e : edges) {
            gv->removeEdge(e.getID());
            gv->addEdge(e.getID(), n->getInfo()->getId(), e.getDest()->getInfo()->getId(), EdgeType::DIRECTED);
        }
    }

    for(int i : path){
        gv->setEdgeColor(i, "red");
    }

    gv->rearrange();

}

User *WasteApp::findUser(int id) {
    for (int i = 0; i < users.size(); ++i) {
        if (users.at(i)->getAddress().getId() == id)
            return users.at(i);
    }
    return NULL;
}

void WasteApp::printProgressBar(float current, float total) {
    float percentage = 100.0 * current / total;

    printf("\rCompleted: %6.2f%% [", percentage);

    int i, len = 50;
    int pos = percentage * len / 100.0;

    for (i = 0; i < len; i++)
        i <= pos ? cout << "=" : cout << " ";

    printf("]\n\n");
}

void WasteApp::addEdgeGV(User * user) {

}

GraphViewer *WasteApp::getGraphViewer() const {
    return gv;
}

void WasteApp::setPath(vector<int> path) {
    WasteApp::path = &path;
}

std::vector<int> *WasteApp::getPath() const {
    return path;
}

/*
void WasteApp::append_vector(vector<unsigned int> &v1, vector<unsigned int> &v2) {
    for (unsigned int i :v2) {
        v1.push_back(i);
    }
}

void WasteApp::append_containers(vector<Container> &v1, vector<Container> &v2) {
    for (Container i :v2) {
        v1.push_back(i);
    }
}

bool WasteApp::isMatosinhos(Node node) {


    if (node.getX() > MATOSINHOS_X)
        return false;

    return true;
}


bool WasteApp::isStartingNode(Vertex<Address> node) {
    unsigned int id = node.getId();

    return id == MATOSINHOS_PARKING_NODE_ID || id == BOAVISTA_PARKING_NODE_ID || id == PARANHOS_PARKING_NODE_ID || id == MYMAP_PARKING_NODE_ID;
}

bool WasteApp::isFinalNode(Vertex<Address> node) {
    unsigned int id = node.getId();

    return id == MATOSINHOS_WASTE_STATION_NODE_ID || id == BOAVISTA_WASTE_STATION_NODE_ID || id == PARANHOS_WASTE_STATION_NODE_ID || id == MYMAP_WASTE_STATION_NODE_ID;
}

void WasteApp::getContainers(unsigned int startingNode, Graph<Address> &graph, vector<Container> &wasteContainers, vector<Container> &recyclingContainers) {

    if (startingNode == MATOSINHOS_PARKING_NODE_ID)
        getMatosinhosContainers(graph, wasteContainers, recyclingContainers);
    else if (startingNode == BOAVISTA_PARKING_NODE_ID)
        getBoavistaContainers(graph, wasteContainers, recyclingContainers);
    else if (startingNode == PARANHOS_PARKING_NODE_ID)
        getParanhosContainers(graph, wasteContainers, recyclingContainers);
    else if (startingNode == MYMAP_PARKING_NODE_ID)
        getMyMapContainers(graph, wasteContainers, recyclingContainers);
}

void WasteApp::getMyMapContainers(Graph<Address> &graph, vector<Container> &wasteContainers, vector<Container> &recyclingContainers) {
    DFS dfs = DFS(graph);
    NodeHashTable accessNodes = dfs.performSearch(MYMAP_PARKING_NODE_ID);
    vector<Container>::iterator iter;

    for (Vertex<Address> n : accessNodes) {
        if (n.getType() == WASTE_DISPOSAL) {
            Container newContainer = Container(n);
            if (newContainer.isValidPickup())
                wasteContainers.push_back(newContainer);
        }
        else if (n.getType() == RECYCLING_CONTAINER) {
            Container newContainer = Container(n);
            if (newContainer.isValidPickup())
                recyclingContainers.push_back(newContainer);
        }
    }
}

void WasteApp::getMatosinhosContainers(Graph<Address> &graph, vector<Container> &wasteContainers, vector<Container> &recyclingContainers) {
    DFS dfs = DFS(graph);
    NodeHashTable accessNodes = dfs.performSearch(MATOSINHOS_PARKING_NODE_ID);
    vector<Container>::iterator iter;

    for (Vertex<Address> n : accessNodes) {
        if (n.getType() == WASTE_DISPOSAL && isMatosinhos(n)) {
            Container newContainer = Container(n);
            if (newContainer.isValidPickup())
                wasteContainers.push_back(newContainer);
        }
        else if (n.getType() == RECYCLING_CONTAINER && isMatosinhos(n)) {
            Container newContainer = Container(n);
            if (newContainer.isValidPickup())
                recyclingContainers.push_back(newContainer);
        }
    }
}*/
