#pragma once
#include <windows.h>

/* ========================================
            UTILIDADES DE CONSOLA
   ========================================*/

   // Oculta el cursor del terminal
void ocultarCursor();

// Mueve el cursor a una posición específica (y, x)
void moverCursor(int y, int x);

// Mueve el cursor al inicio de la pantalla (0,0)
void moverCursorInicio();