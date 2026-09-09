#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include <vector> 

using namespace std;

struct Jugador {
    string nombre;
    string posicion;      
    string calidadBase;
    string club;
    string liga; 
    int media;
    int ritmo;
    int tiros;
    int pases;
    int regates;
    int defensa;
    int fisico;        
};

void cargarJugadores(string rutaArchivo, vector<Jugador*>& listaJugadores);

void mostrarJugador(Jugador* j);

#endif