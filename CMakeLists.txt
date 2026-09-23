cmake_minimum_required(VERSION 3.19)
project(my_hpx_project CXX)

# --- FORZAR C++17 ESTRICTAMENTE ---
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # Desactiva extensiones como gnu++17
# ----------------------------------

find_package(HPX REQUIRED)

add_executable(my_hpx_program src/main.cpp)

target_link_libraries(my_hpx_program HPX::hpx HPX::wrap_main HPX::iostreams_component)