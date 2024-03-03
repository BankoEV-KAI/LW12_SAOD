#include"menu.h"
#include "BSTstruct.h"
#include <iostream>

//Бинарное дерево поиска (не сбалансированное)

int main()
{
    setlocale(LC_ALL, "ru");
    int operation{ 0 };
    while (true) {
        printMenu(1);
        enteringNumber(0, 6, operation);
        switch (operation)
        {
        case 0:
            return 0;
        case 1:
            create();
            break;
        case 2:
            addNode();
            break;
        case 3:
            searchNode();
            break;
        case 4:
            print();
            break;
        case 5:
            printKeys();
            break;
        case 6:
            deleteN();
            break;
        default:
            break;
        }
    }
}

