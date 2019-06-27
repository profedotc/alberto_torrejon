Juego de la vida
================

Se trata de un **juego de cero jugadores**, su evolución está determinada por el estado inicial y no necesita ninguna entrada de datos posterior. El "tablero de juego" es una malla plana formada por cuadrados (las "células") que se extiende por el infinito en todas las direcciones. 

Cada célula tiene 8 células "vecinas", que son las que están próximas a ella, incluidas las diagonales. 

Las células tienen dos estados: **"vivas"** o **"muertas"**. 

El estado de las células evoluciona a lo largo de unidades de tiempo discretas. Todas las células se actualizan simultáneamente en cada turno, siguiendo estas reglas:

- Una célula muerta con exactamente 3 células vecinas vivas "nace" (es decir, al turno siguiente estará viva). 
- Una célula viva con 2 o 3 células vecinas vivas sigue viva, en otro caso muere (por "soledad" o "superpoblación"). 

## Compilación

Compilar y ejecutar, escribir en el terminal: 
```
$ make 
$ make ejecutar 
```

Otros:
```
$ make clean
$ make debug
$ make release
```

## Utilización

- Presionar cualquier tecla para avanzar una iteración
- Presionar la tecla `q` para cerrar el programa


