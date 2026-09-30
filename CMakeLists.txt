# БЛОК 1 НАЗВАНИЕ ПРОЕКТА И СТАНДАРТЫ ЯЗЫКА
cmake_minimum_required(VERSION 3.20) # Требует версию CMake не ниже 3.20
project(lab01 LANGUAGES CXX)         # Называет проект lab01 и указывает язык C++ (CXX)
set(CMAKE_CXX_STANDARD 20)           # Строго включает стандарт C++20 (как просили в методичке)
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Если компилятор не поддерживает C++20, сборка упадет
set(CMAKE_CXX_EXTENSIONS OFF)        # Запрещает нестандартные расширения компилятора (чистый C++)


if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(FATAL_ERROR "Use GNU GCC: configure with -DCMAKE_CXX_COMPILER=g++")
endif()

add_compile_options(-Wall -Wextra -Wpedantic -g)

include(CheckCXXSourceCompiles)
set(CMAKE_REQUIRED_FLAGS "-fsanitize=address")
set(CMAKE_REQUIRED_LINK_OPTIONS "-fsanitize=address")
check_cxx_source_compiles("int main() { return 0; }" ASAN_SUPPORTED)
unset(CMAKE_REQUIRED_FLAGS)
unset(CMAKE_REQUIRED_LINK_OPTIONS)

if(ASAN_SUPPORTED)
    message(STATUS "AddressSanitizer поддерживается, включаю")
    add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address)
else()
    message(WARNING "AddressSanitizer недоступен в этом тулчейне (MinGW-сборки GCC часто не включают libasan). Продолжаю сборку без него — проверяй утечки вручную (каждый new[] должен иметь парный delete[]).")
endif()

# БЛОК 3 УСТАНОВКА ЕСЛИ НЕТ GTEST
find_package(GTest QUIET) 
# ^ Пытается найти установленный на компьютере GTest.
if(NOT GTest_FOUND)
    # Если не нашел, то включается магия FetchContent:
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.15.2
    )
    FetchContent_MakeAvailable(googletest)
    # ^ CMake сам скачает нужную версию Google Test с гитхаба и соберет её! Тебе не нужно ничего качать вручную.
endif()

# БЛОК 4 СБОРКА БИБЛИОТЕКИ ИЗ ФУНКЦИЙ ПРОЕКТА
add_library(lab01_lib src/array_ops.cpp)
# ^ Берет твои .cpp файлы с функциями и делает из них библиотеку lab01_lib. 
# Зачем? Чтобы эту логику можно было подключить и к main.cpp, и к тестам!

target_include_directories(lab01_lib PUBLIC include)
# ^ Говорит компилятору: "Папка include — это место, где лежат заголовочные файлы (.hpp)".

# БЛОК 5 СБОРКА ОСНОВНОЙ ПРОГРАММЫ
add_executable(lab01_main src/main.cpp)
# ^ Создает исполняемый файл lab01_main.exe из твоего main.cpp

target_link_libraries(lab01_main PRIVATE lab01_lib)
# ^ Прикрепляет к main.exe твою библиотеку с функциями (lab01_lib).

# БЛОК 6 СБОРКА ТЕСТОВ
add_executable(tests tests/array_ops_test.cpp)
# ^ Создает исполняемый файл tests.exe из файлов с тестами.

target_link_libraries(tests PRIVATE lab01_lib GTest::gtest_main)
# ^ Прикрепляет к тестам твою библиотеку логики И саму библиотеку Google Test (gtest_main).

enable_testing()
add_test(NAME Lab01Tests COMMAND tests)
# ^ Включает поддержку CTest (встроенный в CMake запускатор тестов).