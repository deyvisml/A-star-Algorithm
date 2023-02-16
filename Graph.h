#ifndef _GRAPH_H_
#define _GRAPH_H

#include "Node.h"

class Graph
{
private:
	void findNodes(string firstName, Node** ppFirstNode, string secondName, Node** ppSecondNode);
	bool inList(Node* pNode, vector<Node*>* pList);
	static bool compareNodes(Node* pFirst, Node* pSecond);
	vector<Node*> mNodes;

public:
	Graph(void);
	~Graph(void);

	void addNode(string name, int heuristic);
	void connect(string left, string right, int moveCost);
	void listNodes(void);
	bool findPath(string start, string end);
	bool findPath(Node* pStart, Node* pEnd);
	void reset(void);
};




Graph::Graph(void)
{
}

Graph::~Graph(void)
{
	while(!mNodes.empty())
	{
		delete mNodes.back();
		mNodes.pop_back();
	}
}

void Graph::addNode(string name, int heuristic)
{
	mNodes.push_back(new Node(name,heuristic));
}

void Graph::connect(string first, string second, int moveCost)
{
	Node* pFirst = NULL;
	Node* pSecond = NULL;

	findNodes(first, &pFirst, second, &pSecond);
	if(pFirst != NULL && pSecond != NULL)
	{
		pFirst->createEdge(pSecond, moveCost);
		pSecond->createEdge(pFirst, moveCost);
	}
}

void Graph::findNodes(string firstName, Node** ppFirstNode, string secondName, Node** ppSecondNode)
{
	Node* pFirst = NULL;
	Node* pSecond = NULL;

	for(vector<Node*>::iterator itr = mNodes.begin(); itr != mNodes.end(); ++itr)
	{
		if((*itr)->getName().compare(firstName) == 0)
		{
			pFirst = (*itr);
			if(pSecond != NULL)
				break;
		}
		else if((*itr)->getName().compare(secondName) == 0)
		{
			pSecond = (*itr);
			if(pFirst != NULL)
				break;
		}
	}

	*ppFirstNode = pFirst;
	*ppSecondNode = pSecond;
}

void Graph::listNodes(void)
{
	for(vector<Node*>::iterator itr = mNodes.begin(); itr != mNodes.end(); ++itr)
	{
		cout << (*itr)->getName() << "\r\n";
	}
}

bool Graph::findPath(string start, string end)
{
	if(start.compare(end) == 0)
	{
		cout << "El nodo de inicio es el nodo objetivo :|\r\n\r\n";
		return true;
	}

	Node* pStart = NULL;
	Node* pEnd = NULL;

	findNodes(start,&pStart,end,&pEnd);
	if(pStart != NULL && pEnd != NULL)
		return findPath(pStart, pEnd);

	return false;
}

bool Graph::findPath(Node* pStart, Node* pEnd)
{
	if(pStart == pEnd)
	{
		cout << "El nodo de inicio es el nodo objetivo :|\r\n\r\n";
		return true;
	}

	vector<Node*> openList;

	openList.push_back(pStart);
	Node* pCurrNode = NULL;

	while(!openList.empty())
	{
		//Get best node from open list (lowest F value).
		//Since we sort the list at the end of the previous loop we know
		//the front node is the best
		pCurrNode = openList.front();

		//Exit if we're are the goal
		if(pCurrNode == pEnd) // TODO: EN UNA PRIMERA VUELTA ESTO NUNCA SE CUMPLE POR EL IF DEL INICIO
			break;

		//Remove the node from the open list and place it in the closed
		openList.erase(openList.begin());
		pCurrNode->setClosed(true); //We use a flag instead of a list for speed

		//Test all of the edge nodes from the current node
		vector<Edge*>* pEdges = pCurrNode->getEdges(); // TODO: SE OBTIENEN TODOS LOS ENLACES DEL NODO ACTUAL
		for(vector<Edge*>::iterator i = pEdges->begin(); i != pEdges->end(); ++i)
		{
			Node* pEdgeNode = (*i)->pNode;

			//If it's closed we've already analysed it
			if(!pEdgeNode->getClosed())
			{
				if(!inList(pEdgeNode,&openList)) // TODO: VERIFICAR SI EL NODO ACTUAL NO SE ENCUENTRA EN LA LISTA DE NODOS ABIERTOS
				{
					openList.push_back(pEdgeNode);
					pEdgeNode->setGCost(pCurrNode->getGCost()+(*i)->moveCost);
					pEdgeNode->calcFCost();
					pEdgeNode->setParent(pCurrNode);

					//Normally we'd also calculate the heuristic here, but in this case 
					//they are precalculated
				}
				else
				{
					//If this is a better node (lower G cost)
					if(pEdgeNode->getGCost() > pCurrNode->getGCost()+(*i)->moveCost)
					{
						pEdgeNode->setGCost(pCurrNode->getGCost()+(*i)->moveCost);
						pEdgeNode->calcFCost();
						pEdgeNode->setParent(pCurrNode); // TODO: SE LE CAMBIA DE PADRE AL NODO
					}
				}
			}
		}

		//Place the lowest F cost item in the open list at the top, so we can
		//access it easily next iteration
		sort(openList.begin(), openList.end(),  Graph::compareNodes); // TODO: ESTO ESTA ORDENADO DE FORMA ASCENDENTE (REMEMBER: EL MENOR COSTE ES EL MEJOR)
	}


	//Make sure we actually found a path
	if(pEnd->getParent() != NULL)
	{
		//Output the path
		//Use a stack because it is LIFO
		stack<Node*> path;
		while(pCurrNode != NULL)
		{
			path.push(pCurrNode);
			pCurrNode = pCurrNode->getParent();
		}

		while(!path.empty())
		{
			cout << path.top()->getName() << "\r\n";
			path.pop();
		}
		cout << "\r\n";
		
		return true;
	}

	return false;
}


bool Graph::inList(Node* pNode, vector<Node*>* pList)
{
	for(vector<Node*>::iterator i = pList->begin(); i != pList->end(); ++i)
	{
		if((*i) == pNode)
		{
			return true;
		}
	}

	return false;
}

bool Graph::compareNodes(Node* pFirst, Node* pSecond)
{
	return pFirst->getFCost() < pSecond->getFCost();
}

void Graph::reset(void)
{
	for(vector<Node*>::iterator i = mNodes.begin(); i != mNodes.end(); ++i)
	{
		(*i)->reset();
	}
}

#endif

