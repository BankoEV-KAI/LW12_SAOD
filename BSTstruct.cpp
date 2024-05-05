#include "BSTstruct.h"
#include "menu.h"
#include <iostream>

Node* Root;
Node* ParentVertex;

void printInverselySymmetrical(Node* pCurrent, int levelBST) {
    if (pCurrent != nullptr) {
        printInverselySymmetrical(pCurrent->right, levelBST + 1);

        std::string str;
        for (int i = 0; i < levelBST; i++)
            str += "     ";
        std::cout << " " << str << pCurrent->key << "\n";

        printInverselySymmetrical(pCurrent->left, levelBST + 1);
    }
}

void printForward(Node* pCurrent, int levelPBT) {
    if (pCurrent != NULL) {
        std::string str;
        for (int i = 0; i < levelPBT; i++)
            str += "     ";
        std::cout << " " << str << pCurrent->key << "\n";

        printForward(pCurrent->left, levelPBT + 1);
        printForward(pCurrent->right, levelPBT + 1);
    }
}

void printKeyCounter(Node* pCurrent) {
    if (pCurrent != nullptr) {
        printKeyCounter(pCurrent->left); 
        std::cout << pCurrent->key << "(" << pCurrent->counter << "); ";
        printKeyCounter(pCurrent->right);
    }
}

Node* searchNode(int searchKey) {
    Node* pCurrent = Root; 
    ParentVertex = nullptr;
    bool searchComplete = false;
    while ((pCurrent != nullptr) && (!searchComplete)) {
        if (searchKey < pCurrent->key) {
            ParentVertex = pCurrent;
            pCurrent = pCurrent->left;
        }
        else if (searchKey > pCurrent->key) {
            ParentVertex = pCurrent;
            pCurrent = pCurrent->right;
        }
        else
            searchComplete = true;
    }
    return pCurrent;
}

Node* addNodeRecursive(Node* pCurrent, int newKey) {
    if (pCurrent == nullptr) 
    {
        pCurrent = new Node; 
        pCurrent->key = newKey;
        pCurrent->left = pCurrent->right = nullptr;
        pCurrent->counter = 1;
    }
    else { 
        if (newKey < pCurrent->key)
            pCurrent->left = addNodeRecursive(pCurrent->left, newKey);
        else if (newKey > pCurrent->key)
            pCurrent->right = addNodeRecursive(pCurrent->right, newKey);
        else
            pCurrent->counter++; 
    }
    return pCurrent; 
}

void addNodeNonRecursive(int newKey) {
    if (Root == nullptr) {
        Root = new Node;
        Root->left = Root->right = nullptr;
        Root->key = newKey;
        Root->counter = 1;
        return;
    }

    Node* pCurrent = Root;

    while (pCurrent != nullptr) {
        ParentVertex = pCurrent;

        if (newKey < pCurrent->key)
            pCurrent = pCurrent->left;
        else if (newKey > pCurrent->key)
            pCurrent = pCurrent->right;
        else {
            pCurrent->counter++;
            return; // Вершина найдена, добавлять не нужно, завершить функцию
        }
    }

    pCurrent = new Node;
    pCurrent->left = pCurrent->right = nullptr;
    pCurrent->counter = 1;
    pCurrent->key = newKey;

    if (newKey < ParentVertex->key)
        ParentVertex->left = pCurrent;
    else if (newKey > ParentVertex->key)
        ParentVertex->right = pCurrent;
}

void addNodes(int count) {
    for (int i = 0; i < count; i++) {
        Root = addNodeRecursive(Root, rand() % 100 + 1);
    }
    std::cout << "Было создано бинарное древо поиска из " << count << "ключей, повторяющиеся ключи зафиксированы." << std::endl;
}

Node* findReplacement(Node* p) {
    while (p->right != nullptr)
        p = p->right;
    return p;
}


Node* deleteNode(Node* pCurrent, int newKey) {
    if (pCurrent == nullptr) {
        std::cout << "Удаление невозможно: искомая вершина не найдена";
    }
    else if (newKey < pCurrent->key) {
        pCurrent->left = deleteNode(pCurrent->left, newKey);
    }
    else if (newKey > pCurrent->key) {
        pCurrent->right = deleteNode(pCurrent->right, newKey);
    }
    else {
        if (pCurrent->counter > 1) {
            pCurrent->counter--;
        }
        else {
            Node* pTemp = pCurrent;
            if (pTemp->right == nullptr) {
                Node* newRoot = pTemp->left;
                delete pTemp;
                return newRoot;
            }
            else if (pTemp->left == nullptr) {
                Node* newRoot = pTemp->right;
                delete pTemp;
                return newRoot;
            }
            else {
                Node* replacementParent = pTemp;
                Node* replacement = pTemp->right;
                while (replacement->left != nullptr) {
                    replacementParent = replacement;
                    replacement = replacement->left;
                }

                pCurrent->key = replacement->key;

                if (replacementParent == pTemp)
                    replacementParent->right = replacement->right;
                else
                    replacementParent->left = replacement->right;

                delete replacement;
                return pCurrent;
            }
        }
    }
    return pCurrent;
}


//Для кратнсоти в мейне

/*
- создание дерева с заданным числом вершин со случайными ключами
- добавление в дерево одной вершины с заданным пользователем значением ключа
- поиск в дереве вершины с заданным ключом
- построчный вывод дерева в наглядном виде
- вывод всех вершин в порядке возрастания их ключей
- удаление вершины с заданным ключом
*/

void create() {
    int countNodes{ 0 };
    std::cout << "Сколько вершин необходимо создать? ";
    enteringNumber(1, 100, countNodes);
    addNodes(countNodes);
    std::cout << "Бинарное дерево поиска в обратно-симметричном виде: " << std::endl;
    printInverselySymmetrical(Root, 0);
    std::cout << std::endl;
    std::cout << "Бинарное дерево поиска в виде ключ(посторения): "; 
    printKeyCounter(Root);
    std::cout << std::endl;
}

void addNode() {
    int operation{ 0 }, newKey{ 0 };
    enteringNumber(1, 100, newKey);
    std::cout << "1. Добавить рекурсивно" << std::endl
        << "2. Добавить не рекурсивно" << std::endl;
    enteringNumber(1, 2, operation);
    if (operation == 1) Root = addNodeRecursive(Root, newKey);
    else addNodeNonRecursive(newKey);
    std::cout << "Ключ " << newKey << " добавлен в дерево " << (operation == 1 ? "рекурсивно " : "не рекурсивно") << std::endl;   
}

void searchNode() {
    int newKey;
    enteringNumber(1, 100, newKey);
    Node* pTemp = searchNode(newKey);
    if (pTemp != nullptr)
        std::cout << "Элемент с ключом " << newKey << " найден, количество повторений " << pTemp->counter << std::endl;
    else
        std::cout << "Элемент с ключом " << newKey << " не найден" << std::endl;
}

void print() {
    std::cout << "Бинарное дерево поиска в обратно-симметричном виде: " << std::endl;
    printInverselySymmetrical(Root, 0);
    std::cout << std::endl;
    std::cout << "Бинарное дерево поиска в прямом порядке: " << std::endl;
    printForward(Root, 0);
    std::cout << std::endl;
}

void printKeys() {
    std::cout << "Бинарное дерево поиска в виде ключ(посторения): ";
    printKeyCounter(Root);
    std::cout << std::endl;
}

void deleteN() {
    int deletedKey{ 0 };
    enteringNumber(1, 100, deletedKey);
    Root = deleteNode(Root, deletedKey);
    print();
}