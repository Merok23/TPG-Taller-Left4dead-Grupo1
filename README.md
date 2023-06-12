# TPG-Taller-Left4dead-Grupo1

## Manual de instalación
Este manual proporciona instrucciones paso a paso para instalar los recursos necesarios para utilizar el juego Left 4 dead. Asegúrate de seguir cada paso cuidadosamente para una instalación exitosa.

### GCC (con soporte para el estándar C++17):
----------
Para sistemas Ubuntu o Debian:

1. Actualiza los repositorios de paquetes ejecutando el siguiente comando:
```
sudo apt update
```
2. Instala los paquetes esenciales de compilación, incluido GCC, ejecutando el siguiente comando:
```
sudo apt install build-essential
```
Esto instalará GCC en tu sistema con soporte para el estándar C++17.

### CMAKE (versión 3.26):
----------------
Para sistemas Ubuntu o Debian:
1. Actualiza los repositorios de paquetes ejecutando el siguiente comando:
```
sudo apt update
```
2. Instala CMake ejecutando el siguiente comando:
```
sudo apt install cmake
```
Asegúrate de tener instalada la versión 3.26 o superior de CMake.

### SDLPP
----------------
Para sistemas Ubuntu o Debian:
1. Abre una terminal y ejecuta el siguiente comando para instalar las dependencias necesarias utilizando apt-get:
```
sudo apt-get install libjpeg-dev libpng-dev libfreetype-dev libopusfile-dev libflac-dev libxmp-dev libfluidsynth-dev libwavpack-dev cmake libmodplug-dev libsdl2-dev

```
2. Descarga los archivos fuente de las siguientes bibliotecas en formato zip:

+ [libsdl2-image (versión 2.6.3)](https://github.com/libsdl-org/SDL_image/releases/tag/release-2.6.3)
+ [libsdl2-mixer (versión 2.6.3)](https://github.com/libsdl-org/SDL_mixer/releases/tag/release-2.6.3)
+ [libsdl2-ttf (versión 2.20.2)](https://github.com/libsdl-org/SDL_ttf/releases/tag/release-2.20.2)

3. Descomprime cada archivo zip descargado y accede a la carpeta resultante.
4.  En cada carpeta, crea un directorio llamado "build" y accede a él. Por ejemplo:
```
cd libsdl2-image-2.6.3
mkdir build
cd build
```
5. Ejecuta los siguientes comandos en cada carpeta "build" para compilar e instalar las bibliotecas correspondientes:
```
cmake ..
make -j4
sudo make install
```
6. Repite los pasos anteriores (3-5) para cada una de las bibliotecas (libsdl2-mixer y libsdl2-ttf) descargadas.


7. Descarga el archivo fuente de [libsdl2pp(versión 0.18.1)](https://github.com/libSDL2pp/libSDL2pp/releases/tag/0.18.1) en formato zip.


8. Descomprime el archivo zip descargado y accede a la carpeta resultante.
   
9.  Crea un directorio llamado "build" y accede a él. Por ejemplo:
```
cd libSDL2pp-0.18.1
mkdir build
cd build
```
10. Ejecuta los siguientes comandos para compilar e instalar libsdl2pp:
```
cmake ..
make -j4
sudo make install
```

### CATCH2
----------------
Para sistemas Ubuntu o Debian:
1. Descarga el archivo fuente de [Catch2 (versión 2.13.4)](https://github.com/catchorg/Catch2)
2. Descomprime el archivo zip descargado y accede a la carpeta resultante.
3. Crea un directorio llamado "build" y accede a él. Por ejemplo:
```
cd Catch2-2.13.4
mkdir build
cd build
```
4. Ejecuta los siguientes comandos para compilar e instalar Catch2:
```
cmake ..
make -j4
sudo make install
```

### QT (versión 5.12.8)
----------------

1. Abre un navegador web y ve a la página oficial de [Qt](https://www.qt.io/download).


2. En la página de descargas, elige tu sistema operativo y selecciona "Download".
   
3.  Una vez que hayas descargado el instalador, ábrelo y sigue las instrucciones del asistente de instalación. Asegúrate de instalar la versión "Qt 5.12.8" y cualquier otro componente adicional que necesites para tu desarrollo.

4. Durante la instalación, se te pedirá que aceptes los términos de la licencia de Qt. Lee los términos y, si estás de acuerdo, acepta la licencia para continuar con la instalación.

5. Después de que la instalación se complete, deberías tener Qt5 instalado en tu sistema. Puedes verificar la instalación abriendo una terminal y ejecutando el comando qmake --version para ver la información de la versión de Qt.


## Como ejecutar el juego
----------------
1. Abre una terminal, crea un directorio donde guardar el juego, luego ejecuta el siguiente comando para clonar el repositorio, y acceder al directorio del juego:
```
git clone git@github.com:Merok23/TPG-Taller-Left4dead-Grupo1.git
cd TPG-Taller-Left4dead-Grupo1
```
2. Crea un directorio llamado "build" y accede a él. Por ejemplo:
```
mkdir build && cd build
```
3. Ejecuta los siguientes comandos para compilar el juego, y accede a la carpeta con el ejecutable:
```
cmake ..
make -j4
cd target
```
4. Para ejecutar el servidor del juego, ejecuta el siguiente comando "./server port" donde port es el puerto donde se ejecutará el servidor, por ejemplo:
```
./server 8082
```
5. Para ejecutar el cliente del juego, abre una nueva terminal y navega hasta la carpeta target del juego, ejecuta el siguiente comando "./client localhost port" donde localhost es un nombre de dominio especial que se utiliza para referirse al dispositivo en el que se realiza la solicitud de red, y port es el puerto donde se ejecuta el servidor, por ejemplo:
```
cd TPG-Taller-Left4dead-Grupo1/build/target
./client localhost 8082
```

## Jugar
----------------
### Como crear o unirse a una partida
Se abrirá la pantalla principal del juego donde puedes seleccionar crear una partida o unirte a una partida existente.
   + Para crear una partida, haz clic en el botón "New Match", luego ingresa el nombre de la partida, el modo de juego y elige el tipo de soldado con el que jugar. 
   + Para unirse a una partida, haz clic en el botón "Join Match", luego ingresa el id de la partida a la que deseas unirte y elige el tipo de soldado con el que jugar.

### Objetivo del juego
El objetivo del juego depende del modo elegido: 
   + Survival:  a medida que pasa el tiempo aparecen más y más infectados y estos se van haciendo progresivamente más fuertes, resistentes y veloces. No hay condición de victoria: la muerte es inevitable y solo se compite por ver quién resiste más tiempo.
   + En “clear the zone” la cantidad de infectados en un escenario es fija y los jugadores ganan cuando eliminan a todos ellos.
   + No se generarán enemigos. Simplemente disfruta de un paseo en un entorno apocalíptico.

### Puntos de vida, derribo y muerte
+ Cuando un jugador recibe demasiado daño y sus puntos de vida llegan a 0 este es derribado. Otro jugador puede asistirlo y levantarlo, esto se logra acercandose al jugador caído y esperando a que se levante.

+ El jugador caído se levanta recuperando la mitad de sus puntos de vida.
  
+ Un jugador que es derribado por tercera vez cae muerto. Un jugador derribado que no es asistido por uncompañero en el plazo de 30 segundos muere también.

### Armas
El jugador puede elegir un soldado con el arma de preferencia. Las armas disponibles son:
+ IDF: Este rifle de asalto produce una rafaga de 20 balas con un daño considerable a corta distancia pero uno mucho menor a larga distancia reflejando su imprecisión. Debe recargar el arma cada 50 rafaga
+ P90: Con rafagas de 10 balas, es un rifle más balanceado con una performance más consistente en largas distancias. Debe recargar el arma cada 30 rafagas.
+ Scout: A diferencia del IDF y P90, el Scout es un rifle que dispara de a 1 bala. No obstante cada bala daña a todo infectado que se encuentre en su trayectoria  Se recarga cada 20 balas.
  
### Infectados
Los infectados son los enemigos del juego. Existen 3 tipos de infectados:
+ Común: Los infectados caminan o permanecen quietos en las calles si no son molestados pero la mayoría empezará a caminar hacia los jugadores en cuanto estén a la vista para matarlos. 
+ Spear: A pesar de que la mayoría de los infectados muestran un nivel cognitivo básico, algunos han llegado a evolucionar a tal punto de ser capaces de usar armas como lanzas.
+ Witch: Esta infectada ocasionalmente se pone a gritar atrayendo a más infectados que llegaran corriendo a la zona desde todas las direcciones. Los jugadores deberían eliminarla lo antes posible.

### Controles
+ Para moverte, utiliza las teclas de dirección. 
+ Para disparar, utiliza la barra espaciadora. 
+ Para recargar, utiliza la tecla "R". 
+ Para salir del juego, presiona la tecla "Q".

### Cheats 
Los cheats disponibles son:
+ Vida infinita: Para activar la vida infinita, presiona las teclas "Shift + H".
+ Aparecer un infectado común: Para aparecer un infectado común, presiona las teclas "Shift + Z".
+ Matar a todos los infectados: Para matar a todos los infectados, presiona las teclas "Shift + C".

## Configuración
------------    
Todos los atributos del juego pueden ser cambiados vía un archivo de
configuración, llamado "config", podes encontrar el .h y .cpp. Por ejemplo se debe poder cambiar el daño por bala por arma, la cantidad de balas en cada rafaga, la cantidad de rafagas antes de cada recarga, la velocidad de cada infectado; etc.