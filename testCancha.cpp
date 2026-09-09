#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "jugador.h" 

using namespace std;

struct Usuario {
    string nombre;
    int presupuesto = 500;
    char tecla;
    vector<Jugador*> equipo;
};

void mostrarCancha(Usuario* u) {
    cout << "\n======================================================\n";
    cout << "            ALINEACION DE " << u->nombre << " (4-2-3-1)\n";
    cout << "======================================================\n";
    
    if(u->equipo.size() < 11) {
        cout << "[Alineacion en construccion: " << u->equipo.size() << "/11 jugadores]\n";
        return;
    }

    cout << "                     [" << u->equipo[10]->nombre << "]\n\n";
    cout << "   [" << u->equipo[7]->nombre << "]     [" << u->equipo[8]->nombre << "]     [" << u->equipo[9]->nombre << "]\n\n";
    cout << "             [" << u->equipo[5]->nombre << "]       [" << u->equipo[6]->nombre << "]\n\n";
    cout << "[" << u->equipo[1]->nombre << "]  [" << u->equipo[2]->nombre << "]  [" << u->equipo[3]->nombre << "]  [" << u->equipo[4]->nombre << "]\n\n";
    cout << "                     [" << u->equipo[0]->nombre << "]\n";
    cout << "======================================================\n\n";
}

int main() {
    srand(time(NULL));
    vector<Jugador*> todosLosJugadores;
    
    cargarJugadores("jugadores.csv", todosLosJugadores); 

    if (todosLosJugadores.empty()) {
        cout << "Error: No hay jugadores disponibles en el archivo.\n";
        return 1;
    }

    Usuario u1;
    u1.nombre = "Equipo Prueba";

    // Llenar el 11 al azar
    for (int i = 0; i < 11; i++) {
        int indiceRandom = rand() % todosLosJugadores.size();
        u1.equipo.push_back(todosLosJugadores[indiceRandom]);
    }

    // Probar la impresion visual
    mostrarCancha(&u1);
    
    return 0;
}