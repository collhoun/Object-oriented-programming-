#include <iostream>

int* array_create(std::size_t size) {
    return new int[size]();  // если память не выделилась, то new самостоятельно бросает
                             // исключение,() - заполняет нулями
}

void array_delete(int*& arr) {
    delete[] arr;
    arr = nullptr;
}

int* array_resize(int* arr, std::size_t size, std::size_t new_size) {  // новая память + копия
    //  фактически мы можем как уменьшать массив, так и увеличивать его
    if (new_size == size) {
        return arr;
    }
    if (new_size == 0) {
        array_delete(arr);
        return nullptr;
    }
    if (!arr) {
        return nullptr;
    }
    int* new_array = array_create(new_size);
    std::size_t elements_to_copy = (size < new_size) ? size : new_size;
    for (std::size_t i = 0; i < elements_to_copy; i++) {
        new_array[i] = arr[i];
    }
    array_delete(arr);
    return new_array;
}
int* array_insert(int* arr, std::size_t& size, std::size_t pos, int value) {
    // поскольку capacity нет, то будем расширять массив неоптимально на 1 элемент
    if (pos > size) {
        return arr;
    }
    if (!arr) {
        return nullptr;
    }
    int* new_arr = array_create(size + 1);
    for (std::size_t i = 0; i < pos; i++) {
        new_arr[i] = arr[i];
    }
    new_arr[pos] = value;
    for (std::size_t i = pos; i < size; i++) {
        new_arr[i + 1] = arr[i];
    }
    array_delete(arr);
    size++;
    return new_arr;
}
int* array_remove(int* arr, std::size_t& size, std::size_t pos) {
    if (pos >= size) {
        return arr;
    }
    if (!arr) {
        return nullptr;
    }
    if (size < 2) {
        array_delete(arr);
        size = 0;
        return nullptr;
    }
    int* new_arr = array_create(size - 1);
    for (std::size_t i = 0; i < pos; i++) {
        new_arr[i] = arr[i];
    }
    for (std::size_t i = pos + 1; i < size; i++) {
        new_arr[i - 1] = arr[i];
    }
    array_delete(arr);
    size--;
    return new_arr;
}
void array_print(const int* arr, std::size_t size) {
    if (!arr) {
        return;
    }
    for (std::size_t i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << '\n';
}
bool array_binary_search(const int* arr, std::size_t size, int target, std::size_t& out_index) {
    if (!arr) {
        return false;
    }
    std::size_t left, right, mid;
    left = 0;
    right = size;
    while (left < right) {
        mid = left + (right - left) / 2;
        if (arr[mid] > target) {
            right = mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            out_index = mid;
            return true;
        }
    }
    return false;
}

void quick_sort(int* arr, int left, int right) {
    // возможно стоило сделать функцию типа bool
    if (!arr) {
        return;
    }
    if (left >= right) {
        return;
    }
    int pivot = arr[left + (right - left) / 2];

    int i = left;
    int j = right;

    while (i <= j) {
        while (arr[i] < pivot) {
            i++;
        }

        while (arr[j] > pivot) {
            j--;
        }

        if (i <= j) {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    if (left < j) {
        quick_sort(arr, left, j);
    }
    if (i < right) {
        quick_sort(arr, i, right);
    }
}

int array_kth_smallest(int* arr, size_t size, size_t k) {
    if (!arr) {
        return 0;  // нужно бросить исключение
    }
    if (size < 1) {
        return 0;  // нужно бросить исключение
    }
    if (k > size || k == 0) {
        return 0;  // нужно бросить исключение
    }
    int* sorted_array = array_create(size);
    for (std::size_t i = 0; i < size; i++) {
        sorted_array[i] = arr[i];
    }
    quick_sort(sorted_array, 0, size - 1);
    int ans = sorted_array[k - 1];
    array_delete(sorted_array);
    return ans;
}