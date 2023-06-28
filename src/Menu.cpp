#include "menu.h"


void mainMenu(WasteApp &app) {

    int choice;
    bool running = true;
    while (running){
        cout << "*******************************\n";
        cout << " 1 - User register.\n";
        cout << " 2 - User log in.\n";
        cout << " 3 - Create Collecting Point\n";
        cout << " 4 - Show Graph\n";
        cout << " 5 - Exit.\n";
        cout << " Enter your choice and press return: ";

        cin >> choice;

        int id;
        switch (choice)
        {
            case 1:
                cout << "User register\n";
                app.createUser();
                break;
            case 2:
                while(true){
                    cout << "User log in\n";
                    cout << "User ID: \n";
                    cin >> id;
                    User * u = app.findUser(id);
                    if (u != NULL){
                        menuUser(app, u);
                        break;
                    }
                    cin.clear();
                    fflush(stdin);
                }
                break;
            case 3:
                cout << "Create Collecting Point\n";
                app.createCollectingPoint();
                break;
            case 4:
                cout << "Show Graph\n";
                app.buildGraphViewer();
                getchar();
                break;
            case 5:
                cout << "Obrigado por usar a WhastApp!\n";
                running = false;
                break;
            default:
                cout << "Not a Valid Choice. \n";
                cout << "Choose again.\n";
                cin >> choice;
                break;
        }

        cin.clear();
        fflush(stdin);

    }
}

void menuUser(WasteApp &app, User *u){
    int choice;
    bool running = true;
    while (running){
        cout << "*******************************\n";
        cout << " 1 - Levar o lixo.\n";
        cout << " 2 - Recolha de residuos.\n";
        cout << " 3 - Adicionar lixo.\n";
        cout << " 4 - Ver o meu lixo\n";
        cout << " 5 - Voltar.\n";
        cout << " Enter your choice and press return: ";

        cin >> choice;

        std::vector<int> edgeIds;

        switch (choice)
        {
            case 1:
                cout << "Levar o lixo\n";

                for(int i : *app.getPath()){
                    app.getGraphViewer()->setEdgeColor(i, "black");
                }

                app.setPath(app.findContainer(u));

                for(int i : *app.getPath()){
                    app.getGraphViewer()->setEdgeColor(i, "orange");
                }

                break;
            case 2:
                cout << "Recolha de residuos\n";
                // rest of code here
                break;
            case 3:
                cout << "Adicionar lixo\n";
                u->createContainer();
                break;
            case 4:
                for(Container* container : u->getContainers()){
                    cout << getStringGarbageType(container->getGarbageType()) << " - " << container->getVolume() << endl;
                }
                break;
            case 5:
                running = false;
                break;
            default:
                cout << "Not a Valid Choice. \n";
                cout << "Choose again.\n";
                cin >> choice;
                break;
        }

    }
}
