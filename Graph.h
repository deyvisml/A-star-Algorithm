#ifndef _GRAPH_H_
#define _GRAPH_H

#include <string>
#include <vector>
#include "Node.h"

class Graph
{
public:
	Graph(void);
	~Graph(void);

	void addNode(const std::string& name, int heuristic);
	void connect(const std::string& left, const std::string& right, int moveCost);
	void listNodes(void);
	bool findPath(const std::string& start, const std::string& end);
	bool findPath(Node* pStart, Node* pEnd);
	void reset(void);
private:
	void findNodes(const std::string& firstName, Node** ppFirstNode, const std::string& secondName, Node** ppSecondNode);
	bool inList(Node* pNode, std::vector<Node*>* pList);
	static bool compareNodes(Node* pFirst, Node* pSecond);

	std::vector<Node*> mNodes;
};

#endif

