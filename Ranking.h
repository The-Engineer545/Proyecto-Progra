#pragma once
#include <string>
#include <vector>

/* ========================================
            ESTRUCTURA PARA JSON
   ========================================*/

struct Jugador {
    int puntos;
    std::string nombre;
};

class Ranking {
public:
    static std::vector<Jugador> cargar();
    static void guardar(const std::vector<Jugador>& ranking);
    static void mostrar();
    static void agregarYGuardar(int score, const std::string& nombre);
};