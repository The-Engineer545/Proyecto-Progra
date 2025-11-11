#include "Ranking.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <conio.h>
using namespace std;

/* ========================================
          LECTURA Y ESCRITURA DE RANKING
   ========================================*/

vector<Jugador> Ranking::cargar() {
    vector<Jugador> ranking;
    ifstream leer("ranking.json");
    if (!leer.is_open()) return ranking;

    // Lee línea por línea para evitar errores con saltos de línea
    string linea;
    while (getline(leer, linea)) {
        // Ignorar líneas vacías o que no contengan un objeto JSON
        if (linea.find('{') == string::npos) continue;
        size_t inicio = linea.find('{');
        size_t fin = linea.find('}');
        if (inicio == string::npos || fin == string::npos) continue;
        string objeto = linea.substr(inicio + 1, fin - inicio - 1);

        // --- EXTRAER PUNTOS ---
        size_t p1 = objeto.find("\"puntos\":");
        if (p1 == string::npos) continue;
        p1 += 9;
        size_t p2 = objeto.find_first_not_of("0123456789", p1);
        if (p2 == string::npos) p2 = objeto.size();
        int pts = stoi(objeto.substr(p1, p2 - p1));

        // --- EXTRAER NOMBRE ---
        size_t n1 = objeto.find("\"nombre\":\"");
        if (n1 == string::npos) continue;
        n1 += 10;
        size_t n2 = objeto.find('"', n1);
        if (n2 == string::npos) continue;
        string nom = objeto.substr(n1, n2 - n1);

        ranking.push_back({ pts, nom });
    }
    leer.close();
    return ranking;
}

void Ranking::guardar(const vector<Jugador>& ranking) {
    ofstream archivo("ranking.json");
    if (!archivo.is_open()) return;
    // Formato limpio y válido
    archivo << "[\n";
    int maxGuardar = min(10, (int)ranking.size());
    for (int i = 0; i < maxGuardar; i++) {
        archivo << " {\"puntos\":" << ranking[i].puntos
            << ", \"nombre\":\"" << ranking[i].nombre << "\"}";
        if (i < maxGuardar - 1) archivo << ",";
        archivo << "\n";
    }
    archivo << "]";
}

void Ranking::mostrar() {
    system("cls");
    auto ranking = cargar();
    cout << "==============================================================" << endl;
    cout << "                   TOP 10 GLOBAL                            " << endl;
    cout << "==============================================================" << endl << endl;

    if (ranking.empty()) {
        cout << "   No hay jugadores en el ranking aún.\n\n";
    }
    else {
        for (int i = 0; i < min(10, (int)ranking.size()); i++) {
            cout << (i + 1) << ". " << ranking[i].nombre << " - " << ranking[i].puntos << " pts" << endl;
        }
    }
    cout << "\nPresiona cualquier tecla para volver...";
    _getch();
}

void Ranking::agregarYGuardar(int score, const string& nombre) {
    auto ranking = cargar();
    // --- AÑADIR NUEVA PARTIDA ---
    ranking.push_back({ score, nombre });
    // --- ORDENAR DESCENDENTE ---
    sort(ranking.begin(), ranking.end(), [](const Jugador& a, const Jugador& b) {
        return a.puntos > b.puntos; // ¡Mayor primero!
        });
    guardar(ranking);
}