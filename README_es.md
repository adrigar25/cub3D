*Este proyecto ha sido creado como parte del currículo de 42 por agarcia, adriescr.*

# cub3D — Mi primer RayCaster con miniLibX

## Descripción

**cub3D** es un motor de renderizado 3D en primera persona inspirado en *Wolfenstein 3D*, el legendario FPS de 1992 desarrollado por Id Software. El objetivo es implementar un motor de ray-casting desde cero en C usando la librería gráfica miniLibX, generando una vista realista del interior de un laberinto definido en un fichero de escena `.cub`.

El proyecto abarca conceptos fundamentales de gráficos por computador: matemáticas del ray-casting, renderizado de paredes con proyección basada en distancia, mapeo de texturas, gestión de ventanas por eventos y análisis sintáctico del fichero de escena con manejo estricto de errores.

### Funcionalidades obligatorias

- Motor de ray-casting que renderiza paredes, suelo y techo con colores configurables.
- Cuatro texturas de pared según la orientación (Norte, Sur, Este, Oeste).
- Parseo del fichero de descripción de escena (formato `.cub`) con manejo completo de errores.
- Gestión fluida de la ventana (minimizar, cambiar de ventana, cerrar).
- Controles de teclado:
  - `W` `A` `S` `D` — mover al jugador por el laberinto.
  - `←` `→` — rotar el punto de vista.
  - `ESC` o clic en el botón de cerrar ventana — salir limpiamente.

### Funcionalidades bonus

- **Colisiones con paredes** — el jugador no puede atravesar muros.
- **Sistema de minimapa** — minimapa cenital renderizado en tiempo real.
- **Puertas** — puertas que se abren y cierran dinámicamente (carácter `2` en el mapa).
- **Sprites animados** — enemigos con animación de múltiples fotogramas.
- **Rotación con el ratón** — girar el punto de vista usando el ratón.

---

## Instrucciones

### Requisitos

- Compilador C (`cc`) con flags `-Wall -Wextra -Werror`.
- miniLibX (incluida en `libs/mlx/` o `libs/mlx_linux/` según el sistema operativo).
- `libft` (incluida en `libs/libft/`).
- GNU Make.
- macOS o Linux.

### Compilación

```bash
# Parte obligatoria
make

# Parte bonus
make bonus

# Limpiar ficheros objeto
make clean

# Limpieza completa (elimina los binarios)
make fclean

# Recompilar todo
make re
```

### Ejecución

```bash
# Obligatorio
./cub3D maps/map1.cub

# Bonus
./cub3D_bonus maps/map1.cub
```

El programa acepta un único argumento: la ruta a un fichero de descripción de escena `.cub`.

### Formato del fichero de escena (`.cub`)

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

1111111
1000001
10N0001
1111111
```

| Identificador | Significado                                  |
|---------------|----------------------------------------------|
| `NO`          | Ruta a la textura de la pared norte          |
| `SO`          | Ruta a la textura de la pared sur            |
| `WE`          | Ruta a la textura de la pared oeste          |
| `EA`          | Ruta a la textura de la pared este           |
| `F`           | Color del suelo `R,G,B` (rango 0–255)        |
| `C`           | Color del techo `R,G,B` (rango 0–255)        |

Caracteres del mapa:
- `0` — espacio vacío
- `1` — pared
- `2` — puerta *(solo bonus)*
- `N`, `S`, `E`, `W` — posición inicial y orientación del jugador

El mapa debe ser el **último elemento** del fichero y estar completamente cerrado por paredes.

### Manejo de errores

Ante cualquier configuración incorrecta, el programa termina con `Error\n` seguido de un mensaje descriptivo.

En el directorio `maps/` se incluyen mapas inválidos de ejemplo para pruebas.

---

## Recursos

### Referencias sobre ray-casting

- **Tutorial de Ray-Casting de Lode** — recurso fundamental para este proyecto:
  https://lodev.org/cgtutor/raycasting.html
- **Documentación de miniLibX** — librería gráfica usada para el renderizado:
  https://harm-smits.github.io/42docs/libs/minilibx
- **Wolfenstein 3D (juego original, jugable en el navegador)**:
  http://users.atw.hu/wolf3d/
- **3D Game Shaders For Beginners** — lectura complementaria sobre técnicas de renderizado:
  https://github.com/lettier/3d-game-shaders-for-beginners
- **Wikipedia — Ray casting**:
  https://en.wikipedia.org/wiki/Ray_casting

### Uso de IA

Las herramientas de IA (GitHub Copilot) se utilizaron durante este proyecto de forma limitada y verificada en los siguientes casos:

- **Documentación y comentarios**: generación de borradores iniciales de comentarios a nivel de función, revisados y corregidos manualmente a posteriori.
- **Ayuda en depuración**: consultas sobre comportamiento específico de C (p. ej., aritmética de punteros, escenarios de comportamiento indefinido) para confirmar la comprensión antes de aplicar correcciones.
- **Borrador del README**: generación de un primer borrador de este fichero basado en los requisitos del enunciado, revisado y adaptado para reflejar la implementación real del proyecto.

Todo el contenido generado por IA fue revisado críticamente, probado y comprendido antes de su incorporación. No se incluyó ningún código generado por IA sin comprensión plena y revisión entre pares.
