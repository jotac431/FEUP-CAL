/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <algorithm>
//#include "MutablePriorityQueue.h"


template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;


#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
    int id;
    T info;						// content of the vertex
    std::vector<Edge<T> > adj;		// outgoing edges

    double dist = 0;
    Vertex<T> *path = NULL;
    int lastEdge = 0;
    int queueIndex = 0; 		// required by MutablePriorityQueue

    bool visited = false;		// auxiliary field
    bool processing = false;	// auxiliary field

    void addEdge(int id, Vertex<T> *dest, double w);

public:
    Vertex(int id, T in);
    T *getInfo();
    double getDist() const;
    Vertex *getPath() const;
    std::vector<Edge<T> > getEdges() const;

    bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
    friend class Graph<T>;
    //friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(int id, T in): id(id), info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(int id, Vertex<T> *d, double w) {
    adj.push_back(Edge<T>(id, d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
    return this->dist < vertex.dist;
}

template <class T>
T *Vertex<T>::getInfo() {
    return &(this->info);
}

template <class T>
double Vertex<T>::getDist() const {
    return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
    return this->path;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
    int id;
    Vertex<T> * dest;      // destination vertex
    double weight;         // edge weight
public:
    Edge(int id, Vertex<T> *d, double w);
    friend class Graph<T>;
    friend class Vertex<T>;
    int getID() const;
    Vertex<T> * getDest() const;
};

template <class T>
Edge<T>::Edge(int id, Vertex<T> *d, double w): id(id), dest(d), weight(w) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
    std::vector<Vertex<T> *> vertexSet;    // vertex set

public:
    Vertex<T> *findVertex(const T &in) const;
    Vertex<T> *findVertex(int id) const;
    bool addVertex(int id, const T &in);
    bool addEdge(int id, const T &sourc, const T &dest, double w);
    int getNumVertex() const;
    std::vector<Vertex<T> *> getVertexSet() const;

    // Fp06 - single source
    void unweightedShortestPath(const T &s);    //TODO...
    void dijkstraShortestPath(const T &s);
    void bellmanFordShortestPath(const T &s);   //TODO...
    std::vector<T> getPath(const T &origin, const T &dest) const;
    std::vector<int> getEdgePath(const T &origin, const T &dest) const;

    // Fp06 - all pairs
    void floydWarshallShortestPath();   //TODO...
    std::vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;   //TODO...

};

template<class T>
int Edge<T>::getID() const {
    return id;
}

template<class T>
Vertex<T> *Edge<T>::getDest() const {
    return dest;
}

template<class T>
std::vector <Edge<T>> Vertex<T>::getEdges() const {
    return adj;
}

template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template <class T>
std::vector<Vertex<T> *> Graph<T>::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->info == in)
            return v;
    return NULL;
}

template <class T>
Vertex<T> * Graph<T>::findVertex(int id) const {
    for (auto v : vertexSet)
        if (v->id == id)
            return v;
    return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(int id, const T &in) {
    if ( findVertex(in) != NULL)
        return false;
    vertexSet.push_back(new Vertex<T>(id, in));
    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(int id, const T &sourc, const T &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(id, v2,w);
    return true;
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
    // TODO implement this
}

template<class T>
bool myfunction (Vertex<T>* i,Vertex<T>* j) { return (i->getDist() < j->getDist()); }

template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
    auto v = findVertex(origin);
    std::vector<Vertex<T> *> vertexSetCopy = vertexSet;
    std::for_each(vertexSetCopy.begin(), vertexSetCopy.end(), [](Vertex<T> * vertex){vertex->dist = INF; vertex->visited = false; vertex->path = NULL; vertex->lastEdge = 0;});
    v->dist = 0;
    std::sort(vertexSetCopy.begin(), vertexSetCopy.end(), [](Vertex<T> * v1, Vertex<T> * v2){return v1->dist < v2->dist;});
    for(int i = 0; i < vertexSet.size(); ++i) {
        int per1 = i * 100;
        int per = per1 /vertexSet.size();
        if (i%1000 == 0) {
            std::cout << per << "%" << std::endl;
        }
        Vertex<T> * nextV = vertexSetCopy.front();
        for (auto edge : nextV->adj){
            if (!edge.dest->visited) {
                if(nextV->dist + edge.weight < edge.dest->dist || edge.dest->dist == 0) {
                    edge.dest->dist = nextV->dist + edge.weight;
                    edge.dest->path = nextV;
                    edge.dest->lastEdge = edge.id;
                }
            }
        }
        nextV->visited = true;
        vertexSetCopy.erase(vertexSetCopy.begin());
        std::sort(vertexSetCopy.begin(), vertexSetCopy.end(), [](Vertex<T> * vertex1, Vertex<T> * vertex2){return vertex1->dist < vertex2->dist;});
    }
}


template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
    // TODO implement this
}


template<class T>
std::vector<T> Graph<T>::getPath(const T &origin, const T &dest) const {
    std::vector<T> res;
    std::vector<T> res1;
    auto v = findVertex(dest);
    if (v==NULL) return res;
    res.push_back(v->info);
    T destT = dest;
    while (origin != destT) {
        v = v->path;
        destT = v->info;
        res.push_back(destT);
    }
    for (int i = res.size()-1; i > -1; i--) {
        res1.push_back(res[i]);
    }
    return res1;
}



/**************** All Pairs Shortest Path  ***************/

template<class T>
void Graph<T>::floydWarshallShortestPath() {
    // TODO implement this
}

template<class T>
std::vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
    std::vector<T> res;
    // TODO implement this
    return res;
}

template<class T>
std::vector <int> Graph<T>::getEdgePath(const T &origin, const T &dest) const {
    std::vector<int> res;
    std::vector<int> res1;
    auto v = findVertex(dest);
    if (v==NULL) return res;
    res.push_back(v->lastEdge);
    T destT = dest;
    while (origin != destT) {
        v = v->path;
        destT = v->info;
        res.push_back(v->lastEdge);
    }
    for (int i = res.size()-1; i > -1; i--) {
        res1.push_back(res[i]);
    }
    return res1;
}


#endif /* GRAPH_H_ */
