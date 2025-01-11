# Tarea2_C-

## Introduccion

El presente proyecto consiste en el desarrollo de una aplicación con interfaz gráfica diseñada para simular y optimizar un sistema de distribución de paquetería. Esta herramienta innovadora aborda el complejo problema de la logística de transporte, ofreciendo soluciones eficientes para la distribución de productos desde múltiples tiendas de origen hacia diversos puntos de destino.

La aplicación permite al usuario interactuar de manera intuitiva, especificando las tiendas destinatarias y las cantidades de producto a distribuir. Una característica destacada es la flexibilidad en la elección del algoritmo de optimización, ofreciendo tres métodos ampliamente reconocidos en el campo de la investigación de operaciones: el método de la esquina noroeste, la aproximación de Vogel y el método del mínimo costo.

Una vez seleccionados los parámetros, el sistema procesa la información utilizando el algoritmo elegido y proporciona como resultado una ruta de distribución optimizada. Esta ruta considera la red de tiendas físicas disponibles como puntos de origen, garantizando así una solución práctica y aplicable. Además, el sistema calcula y presenta los costos asociados a la ruta propuesta, ofreciendo una visión completa de la eficiencia logística y económica de la solución.

Este proyecto no solo representa una herramienta valiosa para la gestión logística, sino que también sirve como un ejemplo práctico de la aplicación de algoritmos de optimización en problemas del mundo real, demostrando cómo la tecnología puede mejorar significativamente la eficiencia en los procesos de distribución y transporte.

## Dependencias 

1. Git para clonar el repositorio:
   ```bash
   sudo apt-get install git

2. CMake para generar los archivos de compilación:
   ```bash
   sudo apt-get install cmake

3. Compilador C++ para compilar el código:
   ```bash
   sudo apt-get install g++

4. Make para ejecutar el comando 'make':
   ```bash
   sudo apt-get install make


## Compilación e Instalación

Sigue estos pasos para compilar e instalar el proyecto:

1. Clona el repositorio:
   ```bash
   git clone https://github.com/marcelo1799/Tarea2_C-.git

2. Abre el repositorio y dirigete al directorio de compilacion
   ```bash
   cd ~/Tarea2_C-/Centro_de_distribucion/
   mkdir build && cd build

3. Ejecuta CMake para generar los archivos de compilación:
   ```bash
      cmake ..
      make

4. Ejecuta el programa:
    ```bash
   ./Ejecutable
