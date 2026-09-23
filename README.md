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

Y en `src/main.cpp` puedes usar este ejemplo básico:

```cpp
#include <hpx/hpx_main.hpp>
#include <hpx/iostream.hpp>

int main()
{
    hpx::cout << "Hello World!\n" << std::flush;
    return 0;
}
```

---

## 3) Crear la carpeta build

Desde la raíz del proyecto:

```bash
cd ~/HPX_Project
rm -rf build
mkdir build
cd build
```

> Si `build` ya existe de un intento anterior, es recomendable borrarlo antes para evitar que CMake use una caché vieja creada desde otra ruta.

---

## 4) Configurar con CMake

Usa la ruta de instalación de HPX en tu sistema:

```bash
cmake -DHPX_DIR=/usr/lib64/cmake/HPX ..
```

Si tu instalación está en otra carpeta, cambia la ruta por la que corresponda en tu equipo, por ejemplo:

```bash
cmake -DHPX_DIR=/path/to/hpx/installation ..
```
---

## 5) Compilar el proyecto

```bash
cmake --build .
```

---

## 6) Ejecutar el programa

```bash
./my_hpx_program
```

Si todo salió bien, deberías ver una salida similar a:

```text
Hello World!
```

---

## Comandos completos en orden

```bash
cd ~/HPX_Project
rm -rf build
mkdir build
cd build
cmake -DHPX_DIR=/usr/lib64/cmake/HPX ..
cmake --build .
./my_hpx_program
```

---

