#include "menu.h"
#include <iostream>

void enteringNumber(int rangeStart, int rangeStop, int& value) {
    while (true) {
        std::cout << "Введите число от " << rangeStart << " до " << rangeStop << " >> ";
        std::cin >> value;

        if (std::cin.fail() || std::cin.peek() != '\n') {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Некорректный ввод. ";
        }
        else if (value >= rangeStart && value <= rangeStop) {
            return;
        }
        else {
            std::cout << "Некорректное число. ";
        }
    }
}

void printMenu(int operation) {
    switch (operation)
    {
    case 1:
        std::cout << "1. Создание дерева (произвольное заполнение)" << std::endl
            << "2. Добавление вершины в дерево" << std::endl
            << "3. Поиск вершины с заданным ключом" << std::endl
            << "4. Посторочный вывод (обратно-симметричный)" << std::endl
            << "5. Вывод всех вершин в порядке возрастания их ключей" << std::endl
            << "6. Удаление вершины с заданным ключом" << std::endl
            << "0. Завершение программы" << std::endl
            << std::endl;
        break;
    default:
        break;
    }
}