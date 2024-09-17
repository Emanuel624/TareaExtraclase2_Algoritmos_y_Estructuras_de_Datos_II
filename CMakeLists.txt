cmake_minimum_required(VERSION 3.5)

# Nombre del proyecto
project(TareaExtraclase2_Algoritmos_y_Estructuras_de_Datos_II)

set(CMAKE_CXX_STANDARD 17)

# Buscar los módulos necesarios de Qt (Widgets y Charts)
find_package(Qt5 COMPONENTS Widgets Charts REQUIRED)

# Incluir los directorios de Qt necesarios
include_directories(${Qt5Widgets_INCLUDE_DIRS} ${Qt5Charts_INCLUDE_DIRS})

# Agregar los archivos fuente de tu proyecto
add_executable(TareaExtraclase2_Algoritmos_y_Estructuras_de_Datos_II main.cpp
        Algoritmos.cpp
        LinkedList.cpp
        BinarySearchTree.cpp)

# Enlazar las bibliotecas de Qt con tu proyecto
target_link_libraries(TareaExtraclase2_Algoritmos_y_Estructuras_de_Datos_II Qt5::Widgets Qt5::Charts)
