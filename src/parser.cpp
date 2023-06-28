#include "parser.h"


void parserMapa1( const char * nodeFile, const char * edgeFile) { // todo: return graph, not void

    //todo: inicialize Graph<Node> grapf;
    //todo: inicialize Node node;
    string line;
    int nNodes; // todo: for future use in other maps

    ifstream myNodeFile(nodeFile); // opens nodes file

    if(!myNodeFile.is_open())
    {
        printf("error open node file");
        exit(1);
    }

    while (!myNodeFile.eof())  // reading nodes
    {
        getline(myNodeFile,line);    // reads line
        int id,x,y;
        if(!line.empty())
        {
            sscanf(line.c_str(), "%d;%d;%d", &id, &x, &y);

            cout << id << endl;
            cout << x << endl;
            cout << y << endl;
        }
        else{
            break;
        }


    }

    myNodeFile.close();     // close nodes file


    ifstream myEdgeFile(edgeFile); // opens edges file

    if(!myEdgeFile.is_open())
    {
        printf("error open edge file");
        exit(1);
    }

    while (!myEdgeFile.eof())  // reading edges
    {
        getline(myEdgeFile,line);    // reads line
        int id,x,y;
        if(!line.empty())
        {
            sscanf(line.c_str(), "%d;%d;%d", &id, &x, &y);

            cout << id << endl;
            cout << x << endl;
            cout << y << endl;
        }
        else{
            break;
        }


    }

    myEdgeFile.close();     // close edges file


}