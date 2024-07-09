# Código fuente de proyecto semestral TEL341: Simulador de Comportamiento de Redes LoRaWAN en entornos urbanos  

## Integrantes:  
- **Diego Vásquez**
- **Ricardo Díaz**
- **Eduardo Mendoza**

## Instrucciones para compilar el proyecto:

Para compilar el proyecto se necesita tener instalado un compilador de C++23 y CMake.

### Linux

Dirigirse a la carpeta que contiene el proyecto y ejecutar los siguientes comandos:
    

    cmake .
    make

Para ejecutar el proyecto se debe ejecutar el siguiente comando:

    ./SimRedesProyecto


### Windows

Dirigirse a la carpeta que contiene el proyecto y ejecutar los siguientes comandos en la terminal:

    cmake -G "MinGW Makefiles" .
    mingw32-make

Para ejecutar el proyecto se debe ejecutar el siguiente comando:
    
    SimRedesProyecto.exe

## Formato de entrada JSON

El simulador espera un archivo de configuración llamado `config.json` en el mismo path que el ejecutable. 

El formato de las opciones es el siguiente:

* `SubSteps`: Número de subiteraciones para cálculo de probabilidad, mientras más alto, mejor es el resultado.
* `PFall` : Caída de probabilidad por unidad de distancia. Para simular efectos de atenuación.
* `Receptores` : Lista de receptores con objetos con los siguientes parámetros:
    - `Nombre` : Nombre de receptor (Para salida).
    - `Pos` : Vector 2D representando la posición del receptor.
    - `PerdidaProb` : Pérdida de probabilidad asociada a este receptor.

* `Obstaculos`: Lista de obstáculos con objetos con los siguientes parámetros:
    - `Pos` : Vector 2D representando la posición.
    - `Radio` : Representa el radio de influencia del obstáculo.
    - `RFunc` : Función radial de densidad de probabilidad de bloqueo $f(r)$ asociada al obstáculo. Puede ser cualquier función aritmética de la variable $r$. El simulador incluye un parser hecho a mano para interpretar las expresiones matemáticas.
    - `Factor` : Este valor se multiplica por el resultado de evaluar la función de densidad.

### Salidas
El simulador está configurado para entregar una lista de probabilidades de bloqueo asociadas a cada receptor, calculadas mediante una integración de las probabilidades de bloqueo de cada obstáculo. Entrega la salida formateada por `stdout`.