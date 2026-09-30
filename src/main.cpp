#include <windows.h>

#include <iostream>
#include <limits>

#include "lab01/array_ops.hpp"

template <typename T>  // нужно что бы передавать тип данных
void read_valid(T& arg, const char* error_msg = "Ошибка, введите число: ") {
    while (!(std::cin >> arg)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << error_msg;
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    const char* menu = R"(
1. Создать массив
2. Напечатать
3. Вставить элемент
4. Удалить элемент
5. Изменить размер
6. Алгоритм варианта
0. Выход
Выберите пункт: )";

    int action_number;
    int* array = nullptr;
    std::size_t size = 0;

    int input_buffer;
    int value;

    while (true) {
        std::cout << menu;

        read_valid(action_number);

        switch (action_number) {
            case 1:
                if (array) {
                    array_delete(array);
                }
                std::cout << "Введите размер массива:\n";
                read_valid(input_buffer);
                if (input_buffer < 0) {
                    std::cout << "Невозможно выделить отрицательную память!\n";
                    break;
                }
                size = static_cast<std::size_t>(input_buffer);
                array = array_create(size);

                if (size > 0 && array != nullptr) {
                    std::cout << "Введите " << size << " элементов массива:\n";
                    for (std::size_t i = 0; i < size; i++) {
                        read_valid(array[i]);
                    }
                    std::cout << "Массив создан и заполнен!\n";
                }
                break;

            case 2:
                if (!array) {
                    std::cout << "Массив невозможно напечатать\n";
                } else {
                    array_print(array, size);
                }
                break;

            case 3:
                std::cout << "Введите позицию куда вставить элемент и сам элемент через пробел\n";
                read_valid(input_buffer);
                if (input_buffer < 0) {
                    std::cout << "Невозможно втавить на отрицательную позицию!\n";
                    break;
                }
                read_valid(value);
                array = array_insert(array, size, static_cast<std::size_t>(input_buffer), value);
                break;

            case 4:
                std::cout << "Введите индекс удаляемого элемента\n";
                read_valid(input_buffer);
                if (input_buffer < 0) {
                    std::cout << "Невозможно удалить данный элемент\n";
                    break;
                }
                array = array_remove(array, size, static_cast<std::size_t>(input_buffer));
                break;

            case 5:
                if (!array) {
                    std::cout << "Массив еще не создан";
                    break;
                }
                std::cout << "Введите новый размер массива\n";
                read_valid(input_buffer);
                if (input_buffer < 0) {
                    std::cout << "Невозможно выполнить действие";
                    break;
                }
                array = array_resize(array, size, static_cast<std::size_t>(input_buffer));
                size = static_cast<std::size_t>(input_buffer);
                break;

            case 6:
                std::cout << "Введить номер к для поиска к-ого по величине элемента в массиве\n";
                read_valid(input_buffer);
                if (input_buffer < 0) {
                    std::cout << "Невозможно выполнить действие";
                    break;
                }
                std::cout << "К-ый по величине элемент: \n"
                          << array_kth_smallest(array, size,
                                                static_cast<std::size_t>(input_buffer));
                break;

            case 0:
                array_delete(array);
                return 0;

            default:
                std::cout << "Вы ввели номер несуществующей команды. Попробуйте снова!" << '\n';
                break;
        }
    }
    return 0;
}