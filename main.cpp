#include <bits/stdc++.h>
using namespace std;

#include "Graph.h"

int main()
{
	//Graph Creation
	Graph* pRomania = new Graph();
	
	pRomania->addNode("Arad", 366); // TODO: Nombre y Heuristica
	pRomania->addNode("Bucharest", 0);
	pRomania->addNode("Craiova", 160);
	pRomania->addNode("Dobreta", 242);
	pRomania->addNode("Eforie", 161);
	pRomania->addNode("Fagaras", 178);
	pRomania->addNode("Giurgiu", 77);
	pRomania->addNode("Hirsova", 151);
	pRomania->addNode("Iasi", 226);
	pRomania->addNode("Lugoj", 244);
	pRomania->addNode("Mehadia", 241);
	pRomania->addNode("Neamt", 234);
	pRomania->addNode("Oradea", 380);
	pRomania->addNode("Pitesti", 98);
	pRomania->addNode("RimnicuVilcea", 193);
	pRomania->addNode("Sibiu", 253);
	pRomania->addNode("Timisoara", 329);
	pRomania->addNode("Urziceni", 80);
	pRomania->addNode("Vaslui", 199);
	pRomania->addNode("Zerind", 374);


	pRomania->connect("Arad","Zerind", 75);	
	pRomania->connect("Arad","Timisoara", 118);
	pRomania->connect("Arad","Sibiu", 140);

	pRomania->connect("Oradea","Zerind", 71);
	pRomania->connect("Oradea","Sibiu", 151);

	pRomania->connect("Timisoara","Lugoj", 111);
	pRomania->connect("Lugoj","Mehadia", 70);
	pRomania->connect("Mehadia","Dobreta", 75);

	pRomania->connect("Dobreta","Craiova", 120);	
	pRomania->connect("Craiova","Pitesti", 138);
	pRomania->connect("Craiova","RimnicuVilcea", 146);
	pRomania->connect("Pitesti","RimnicuVilcea", 97);
	pRomania->connect("Sibiu","RimnicuVilcea", 80);

	pRomania->connect("Sibiu","Fagaras", 99);
	pRomania->connect("Pitesti","Bucharest", 101);
	pRomania->connect("Fagaras","Bucharest", 211);

	pRomania->connect("Bucharest","Giurgiu", 90);
	pRomania->connect("Bucharest","Urziceni", 85);

	pRomania->connect("Eforie","Hirsova",90);
	pRomania->connect("Eforie","Bucharest",208);
	pRomania->connect("Eforie","Giurgiu",216);

	pRomania->connect("Hirsova","Vaslui",217);
	pRomania->connect("Hirsova","Fagaras",265);
	pRomania->connect("Hirsova","Bucharest",149);

	pRomania->connect("Iasi","Vaslui",58);
	pRomania->connect("Iasi","Neamt",85);

	pRomania->connect("Neamt","Vaslui",105);
	pRomania->connect("Neamt","Urziceni",315);
	//Graph Creation End*/


    string start;
    cout << "Ingrese la posicion inicial, 'quit' para salir o 'list' para listar: ";
    cin >> start;

    while(start != "quit")
    {
        if(start == "list")
        {
            pRomania->listNodes();
        }
        else
        {
            cout << "\r\nLa mejor ruta de " << start << " a Bucharest\r\n------------------\r\n";

            if(!pRomania->findPath(start, "Bucharest"))
                cout << "No se encontro una ruta\r\n\r\n";

            pRomania->reset();
        }

        cout << "Ingrese la posicion inicial, 'quit' para salir o 'list' para listar: ";
        cin >> start;
    }

    delete pRomania;

	return 0;
}