#pragma once

struct Node {
	int key;
	int counter;
	Node* left;
	Node* right;
};

extern Node* Root;
extern Node* ParentVertex;

void printInverselySymmetrical(Node* pCurrent, int levelBST);

void printForward(Node* pCurrent, int levelPBT);

void printKeyCounter(Node* pCurrent);

Node* searchNode(int searchKey);

Node* addNodeRecursive(Node* pCurrent, int newKey);

void addNodeNonRecursive(int newKey);

void addNodes(int count);

Node* findReplacement(Node* p);

Node* deleteNode(Node* pCurrent, int newKey);

void create();

void addNode();

void searchNode();

void print();

void printKeys();

void deleteN();
