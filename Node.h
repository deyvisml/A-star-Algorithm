#ifndef _NODE_H_
#define _NODE_H_

#include <string>
#include <vector>

//Forward declare Node so Edge can see it
class Node;

struct Edge
{
	Edge(Node* node, int cost) : pNode(node), moveCost(cost){}
	Node* pNode;
	int moveCost;
};

class Node
{
public:
	Node(void);
	Node(const std::string& name, int heuristic);
	~Node(void);

	void createEdge(Node* pTarget, int moveCost);

	void setGCost(int cost);
	void setClosed(bool closed);
	void setParent(Node* pParent);

	int getGCost(void);
	int getFCost(void);
	bool getClosed(void);
	Node* getParent(void);
	const std::string& getName(void);
	std::vector<Edge*>* getEdges(void);

	void calcFCost(void);
	void reset(void);
	
private:
	int mGCost;
	int mTotal;
	bool mClosed;
	Node* mpParent;
	std::string mName;
	int mHeur;
	std::vector<Edge*> mEdges;
};

#endif
