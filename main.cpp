#include <bits/stdc++.h>
using namespace std;

#include "Graph.h"

int main()
{
	//Graph Creation
	Graph* pRomania = new Graph();
	
	// TODO: Nombre y posición
	pRomania->addNode("Arad", 130, 185);
	pRomania->addNode("Timisoara", 133, 290);
	pRomania->addNode("Sibiu", 279, 228);
	pRomania->addNode("Zerind", 151, 133);
	pRomania->addNode("Lugoj", 224, 330);
	pRomania->addNode("RimnicuVilcea", 311, 290);
	pRomania->addNode("Fagaras", 406, 239);
	pRomania->addNode("Oradea", 180, 82);
	pRomania->addNode("Mehadia", 228, 381);
	pRomania->addNode("Craiova", 337, 446);
	pRomania->addNode("Pitesti", 423, 344);
	pRomania->addNode("Bucarest", 527, 395);
	pRomania->addNode("Dobreta", 224, 432);
	pRomania->addNode("Giurgiu", 493, 468);
	pRomania->addNode("Urziceni", 599, 367);
	pRomania->addNode("Hirsova", 697, 366);
	pRomania->addNode("Vaslui", 666, 245);
	pRomania->addNode("Eforie", 734, 439);
	pRomania->addNode("Iasi", 621, 166);
	pRomania->addNode("Neamt", 533, 126);


	pRomania->connect("Arad", "Timisoara");
	pRomania->connect("Arad", "Sibiu");
	pRomania->connect("Arad", "Zerind");
	pRomania->connect("Timisoara", "Lugoj");
	pRomania->connect("Sibiu", "RimnicuVilcea");
	pRomania->connect("Sibiu", "Fagaras");
	pRomania->connect("Sibiu", "Oradea");
	pRomania->connect("Zerind", "Oradea");
	pRomania->connect("Lugoj", "Mehadia");
	pRomania->connect("RimnicuVilcea", "Craiova");
	pRomania->connect("RimnicuVilcea", "Pitesti");
	pRomania->connect("Fagaras", "Bucarest");
	pRomania->connect("Mehadia", "Dobreta");
	pRomania->connect("Craiova", "Pitesti");
	pRomania->connect("Craiova", "Dobreta");
	pRomania->connect("Pitesti", "Bucarest");
	pRomania->connect("Bucarest", "Giurgiu");
	pRomania->connect("Bucarest", "Urziceni");
	pRomania->connect("Urziceni", "Hirsova");
	pRomania->connect("Urziceni", "Vaslui");
	pRomania->connect("Hirsova", "Eforie");
	pRomania->connect("Vaslui", "Iasi");
	pRomania->connect("Iasi", "Neamt");
	//Graph Creation End*/


    string start, end;
    cout << "Ingrese la ciudad origen y destino: \n";
	cout <<"-> Origen: ";
    cin >> start;
	cout << "-> Destino: ";
    cin >> end;

    while(start != "quit")
    {
        if(start == "list")
        {
            pRomania->listNodes();
        }
        else
        {
            cout << "\r\nLa mejor ruta de " << start << " a "<<end<<"\r\n------------------\r\n";

            if(!pRomania->findPath(start, end))
                cout << "No se encontro una ruta\r\n\r\n";

            pRomania->reset();
        }

        cout << "Ingrese la ciudad origen y destino: \n";
		cout <<"-> Origen: ";
		cin >> start;
		cout << "-> Destino: ";
		cin >> end;
    }

    delete pRomania;

	return 0;
}
