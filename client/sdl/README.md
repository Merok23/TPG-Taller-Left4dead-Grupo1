# Demo de SDL

Para compilar es necesario instalar `libsdl2-dev` y `libsdl2-image-dev`. Se recomienda el uso de CMake

## Compilar con CMake

Crear una carpeta vacía (ej: build) e invocar a CMake pasando como argumento el directorio donde está CMakeLists.txt

~~~{.bash}
mkdir build
cd build
cmake ..
make && make install
~~~

## Ejecución

### Hello SDL

Carga una imagen y la muestra en pantalla durante 3 segundos

Ejecutar escribiendo `./sdl-hello`

### Eventos básicos

Carga una animación y la muestra en pantalla. Desplaza la imagen, animandolá por el canvas al presionar las teclas
direccionales

Ejecutar escribiendo `./sdl-events`

### Stencil buffer

Carga una imagen estática y la superpone con un stencil, que actua como sombreado para simular un *field of view*.
Este mismo campo de visión puede ser modificado con las teclas direccionales.

Ejecutar escribiendo `./sdl-alpha-blending
