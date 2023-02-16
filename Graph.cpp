#include "StdAfx.h"
#include "Graph.h"
#include <iostream>
#include <algorithm>
#include <stack>

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

void Graph::addNode(const std::string& name, int heuristic)
{
	mNodes.push_back(new Node(name,heuristic));
}

void Graph::connect(const std::string& first, const std::string& second, int moveCost)
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

void Graph::findNodes(const std::string& firstName, Node** ppFirstNode, const std::string& secondName, Node** ppSecondNode)
{
	Node* pFirst = NULL;
	Node* pSecond = NULL;

	for(std::vector<Node*>::iterator itr = mNodes.begin(); itr != mNodes.end(); ++itr)
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
	for(std::vector<Node*>::iterator itr = mNodes.begin(); itr != mNodes.end(); ++itr)
	{
		std::cout << (*itr)->getName() << "\r\n";
	}
}

bool Graph::findPath(const std::string& start, const std::string& end)
{
	if(start.compare(end) == 0)
	{
		std::cout << "Start node is Goal node\r\n\r\n";
		return true;
	}

	Node* pStart = NULL;
	Node* pEnd = NULL;

	findNodes(start,&pStart,end,&pEnd);
	if(pStart != NULL && pEnd != NULL)
		return findPath(pStart,pEnd);
	return false;
}

bool Graph::findPath(Node* pStart, Node* pEnd)
{
	if(pStart == pEnd)
	{
		std::cout << "Start node is Goal node\r\n\r\n";
		return true;
	}

	std::vector<Node*> openList;

	openList.push_back(pStart);
	Node* pCurrNode = NULL;

	while(!openList.empty())
	{
		//Get best node from open list (lowest F value).
		//Since we sort the list at the end of the previous loop we know
		//the front node is the best
		pCurrNode = openList.front();

		//Exit if we're are the goal
		if(pCurrNode == pEnd)
			break;

		//Remove the node from the open list and place it in the closed
		openList.erase(openList.begin());
		pCurrNode->setClosed(true); //We use a flag instead of a list for speed

		//Test all of the edge nodes from the current node
		std::vector<Edge*>* pEdges = pCurrNode->getEdges();
		for(std::vector<Edge*>::iterator i = pEdges->begin(); i != pEdges->end(); ++i)
		{
			Node* pEdgeNode = (*i)->pNode;

			//If it's closed we've already analysed it
			if(!pEdgeNode->getClosed())
			{
				if(!inList(pEdgeNode,&openList))
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
						pEdgeNode->setParent(pCurrNode);
					}
				}
			}
		}

		//Place the lowest F cost item in the open list at the top, so we can
		//access it easily next iteration
		std::sort(openList.begin(), openList.end(),  Graph::compareNodes);
	}

	//Make sure we actually found a path
	if(pEnd->getParent() != NULL)
	{
		//Output the path
		//Use a stack because it is LIFO
		std::stack<Node*> path;
		while(pCurrNode != NULL)
		{
			path.push(pCurrNode);
			pCurrNode = pCurrNode->getParent();
		}

		while(!path.empty())
		{
			std::cout << path.top()->getName() << "\r\n";
			path.pop();
		}
		std::cout << "\r\n";
		
		return true;
	}

	return false;
}

bool Graph::inList(Node* pNode, std::vector<Node*>* pList)
{
	for(std::vector<Node*>::iterator i = pList->begin(); i != pList->end(); ++i)
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
	for(std::vector<Node*>::iterator i = mNodes.begin(); i != mNodes.end(); ++i)
	{
		(*i)->reset();
	}
}