# Proyecto HPX

Este proyecto usa HPX y se compila con CMake.

## 1) Instalar HPX

Primero instala la dependencia de HPX siguiendo la documentación oficial.

En Fedora, normalmente se hace así:

```bash
sudo dnf install hpx*
sudo dnf install cmake make gcc-c++ -y
```


Si ya tienes HPX instalado, puedes comprobar dónde está:

```bash
find /usr /opt ~/.local -name HPXConfig.cmake 2>/dev/null
```

En este entorno, la ruta correcta fue:

```bash
/usr/lib64/cmake/HPX
```

---

## 2) Crear el archivo CMakeLists.txt



En la raíz del proyecto crea un archivo llamado `CMakeLists.txt` con este contenido el cual se va en la documentación como:

```cmake
cmake_minimum_required(VERSION 3.19)
project(my_hpx_project CXX)
find_package(HPX REQUIRED)
add_executable(my_hpx_program main.cpp)
target_link_libraries(my_hpx_program HPX::hpx HPX::wrap_main HPX::iostreams_component)
```

Se cambiaron los parametros a los siguintes para cumplir el requsito de c++ 17:

```cmake
cmake_minimum_required(VERSION 3.19)
project(my_hpx_project CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(HPX REQUIRED)
add_executable(my_hpx_program src/main.cpp)
target_link_libraries(my_hpx_program HPX::hpx HPX::wrap_main HPX::iostreams_component)
```

El programa de [src/main.cpp](src/main.cpp) crea ocho tareas HPX. Cada tarea
realiza un trabajo de CPU durante unos 100 ms e informa qué trabajador la
ejecutó. Al final muestra el tiempo de pared total.

---

## 3) Configurar con CMake

Desde la raíz del proyecto, configura el directorio de compilación:

```bash
cmake -S . -B build -DHPX_DIR=/usr/lib64/cmake/HPX
```

Si tu instalación está en otra carpeta, cambia la ruta por la que corresponda en tu equipo, por ejemplo:

```bash
cmake -S . -B build -DHPX_DIR=/path/to/hpx/installation
```
---

## 4) Compilar el proyecto

```bash
cmake --build build
```

---

## 5) Ejecutar con uno o varios trabajadores

Desde la raíz del proyecto, ejecuta con un solo trabajador:

```sh
./build/my_hpx_program --hpx:threads=1
```

Ejecuta con cuatro trabajadores:

```sh
./build/my_hpx_program --hpx:threads=4
```

Para usar todos los trabajadores disponibles:

```sh
./build/my_hpx_program --hpx:threads=all
```

La salida indica cuántos trabajadores se habilitaron, qué trabajador ejecutó
cada tarea, las iteraciones realizadas y cuánto tardaron las ocho tareas.
Como cada tarea ocupa la CPU unos 100 ms, con un trabajador el tiempo será
aproximadamente 800 ms; con varios trabajadores, el trabajo puede ejecutarse
en paralelo y el tiempo normalmente disminuye. Los trabajadores de HPX son
hilos de ejecución; el sistema operativo decide en qué núcleos físicos se
ejecutan. El tiempo puede variar según la carga y el hardware.
