#include "StdAfx.h"
#include "Node.h"

Node::Node(void)
{
}

Node::Node(const std::string& name, int heuristic) : mGCost(0), mTotal(0), mClosed(false), mpParent(NULL), mName(name), mHeur(heuristic)
{
}

Node::~Node(void)
{
	while(!mEdges.empty())
	{
		delete mEdges.back();
		mEdges.pop_back();
	}
}

const std::string& Node::getName(void)
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

std::vector<Edge*>* Node::getEdges(void)
{
	return &mEdges;
}

int Node::getGCost(void)
{
	return mGCost;
}

void Node::setGCost(int cost)
{
	mGCost = cost;
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