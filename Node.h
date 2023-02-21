#ifndef _NODE_H_
#define _NODE_H_

//Forward declare Node so Edge can see it
class Node;

struct Coordenada
{
	int x;
	int y;
};

struct Edge
{
	Node* pNode;
	int moveCost;
	Edge(Node* node, int cost) : pNode(node), moveCost(cost){}
};

class Node
{
private:
	Coordenada coordenada;
	int mGCost; // TODO: G coste de ir al siguiente nodo
	int mTotal; // TODO: Representaria la suma del G + H
	bool mClosed;
	Node* mpParent;
	string mName;
	int mHeur;
	vector<Edge*> mEdges;

public:
	Node(void);
	Node(string name, int x, int y);
	~Node(void);

	void createEdge(Node* pTarget, int moveCost);

	void setHCost(int cost);
	void setGCost(int cost);
	void setClosed(bool closed);
	void setParent(Node* pParent);

	int getGCost(void);
	int getHCost(void);
	int getFCost(void);
	bool getClosed(void);
	Node* getParent(void);
	string getName(void);
	vector<Edge*>* getEdges(void);

	Coordenada get_coordenada(void);

	void calcFCost(void);
	void reset(void);
};









Node::Node(void)
{
}

Node::Node(string name, int x, int y)
{
	mGCost = 0;
	mTotal = 0;
	mClosed = false;
	mpParent = NULL;
	mName = name;
	coordenada.x = x;
	coordenada.y = y;
}

Node::~Node(void)
{
	while(!mEdges.empty())
	{
		delete mEdges.back();
		mEdges.pop_back();
	}
}

string Node::getName(void)
{
	return mName;
}

void Node::createEdge(Node* pTarget, int moveCost)
{
	mEdges.push_back(new Edge(pTarget, moveCost));
}

void Node::setClosed(bool closed)
{
	mClosed = closed;
}

bool Node::getClosed(void)
{
	return mClosed;
}

vector<Edge*>* Node::getEdges(void)
{
	return &mEdges;
}

int Node::getGCost(void)
{
	return mGCost;
}

int Node::getHCost(void)
{
	return mHeur;
}

void Node::setGCost(int cost)
{
	mGCost = cost;
}

void Node::setHCost(int cost)
{
	mHeur = cost;
}

void Node::calcFCost(void)
{
	mTotal = mGCost + mHeur;
}

void Node::setParent(Node* pParent)
{
	mpParent = pParent;
}

int Node::getFCost(void)
{
	return mTotal;
}

Node* Node::getParent(void)
{
	return mpParent;
}

void Node::reset(void)
{
	mGCost = 0;
	mTotal = 0;
	mClosed = false;
	mpParent = NULL;
}

Coordenada Node::get_coordenada(void)
{
	return coordenada;
}


#endif
