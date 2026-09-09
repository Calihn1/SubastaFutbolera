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

int main() {
    srand(time(NULL));
    vector<Jugador*> todosLosJugadores;
    
    cargarJugadores("jugadores.csv", todosLosJugadores); 

    if (todosLosJugadores.empty()) {
        cout << "Error: No hay jugadores disponibles en el archivo.\n";
        return 1;
    }

    Usuario u1, u2;
    u1.nombre = "Jugador Uno";
    u2.nombre = "Jugador Dos";

    // Generar 11 jugadores aleatorios para ambos usuarios
    for (int i = 0; i < 11; i++) {
        u1.equipo.push_back(todosLosJugadores[rand() % todosLosJugadores.size()]);
        u2.equipo.push_back(todosLosJugadores[rand() % todosLosJugadores.size()]);
    }

    cout << "\n======================================================\n";
    cout << "             EL ENFRENTAMIENTO DEFINITIVO             \n";
    cout << "======================================================\n";
    
    int scoreU1 = 0;
    int scoreU2 = 0;

    for (int i = 0; i < 11; i++) {
        Jugador* j1 = u1.equipo[i];
        Jugador* j2 = u2.equipo[i];
        
        cout << "Duelo " << i+1 << ": " << j1->nombre << " (" << j1->media << ") vs " << j2->nombre << " (" << j2->media << ") -> ";
        
        if (j1->media > j2->media) {
            cout << "Gana " << u1.nombre << "\n";
            scoreU1++;
        } else if (j2->media > j1->media) {
            cout << "Gana " << u2.nombre << "\n";
            scoreU2++;
        } else {
            cout << "Empate\n";
        }
    }

    cout << "\n------------------------------------------------------\n";
    cout << "RESULTADO FINAL: " << u1.nombre << " [" << scoreU1 << "] - [" << scoreU2 << "] " << u2.nombre << "\n";
    
    if (scoreU1 > scoreU2) cout << "EL ONCE DE " << u1.nombre << " ES EL GANADOR\n";
    else if (scoreU2 > scoreU1) cout << "EL ONCE DE " << u2.nombre << " ES EL GANADOR\n";
    else cout << "HAY UN EMPATE TECNICO ENTRE AMBOS EQUIPOS\n";
    
    return 0;
}