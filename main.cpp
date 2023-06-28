#include "src/GraphViewer/graphviewer.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include "src/parser.h"
#include "src/Menu.h"

using namespace std;

int main() {

    const char *nodeFileStrongPorto = "../resources/Mapa da cidade do Porto-20210513/porto_strong_nodes_xy.txt";
    const char *edgeFileStrongPorto = "../resources/Mapa da cidade do Porto-20210513/porto_strong_edges.txt";
    const char *tagFileStrongPorto = "../resources/Mapa da cidade do Porto-20210513/porto_strong_nodes_tags.txt";


    WasteApp app;

    app.parseMap(nodeFileStrongPorto, edgeFileStrongPorto, tagFileStrongPorto);

    app.buildGraphViewer();

    mainMenu(app);

    return 0;

}
