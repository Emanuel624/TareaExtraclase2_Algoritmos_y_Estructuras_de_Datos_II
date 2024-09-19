cmake_minimum_required(VERSION 3.5)

# Nombre del proyecto
project(TareaExtraclase2_Algoritmos_y_Estructuras_de_Datos_II)

set(CMAKE_CXX_STANDARD 17)

# Busca los módulos necesarios de Qt (Widgets y Charts)
find_package(Qt5 COMPONENTS Widgets Charts REQUIRED)

# Incluye los directorios de Qt necesarios
include_directories(${Qt5Widgets_INCLUDE_DIRS} ${Qt5Charts_INCLUDE_DIRS})

add_executable(TareaExtraclase2_Algoritmos_y_Estructuras_de_Datos_II main.cpp
        Algoritmos.cpp
        LinkedList.cpp
        BinarySearchTree.cpp
        Graphs.cpp)

# Enlazar las bibliotecas de Qt
target_link_libraries(TareaExtraclase2_Algoritmos_y_Estructuras_de_Datos_II Qt5::Widgets Qt5::Charts)
