#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "jugador.h" 

using namespace std;

void cargarJugadores(string rutaArchivo, vector<Jugador*>& listaJugadores) {
    ifstream archivo(rutaArchivo); 
    string linea;

    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo " << rutaArchivo << endl;
        return;
    }

    getline(archivo, linea);

    while (getline(archivo, linea)) {
        stringstream ss(linea); 
        string dato;
        
        Jugador* nuevoJugador = new Jugador();

        getline(ss, nuevoJugador->nombre, ',');
        getline(ss, nuevoJugador->posicion, ',');
        getline(ss, nuevoJugador->calidadBase, ',');
        getline(ss, nuevoJugador->club, ',');
        getline(ss, nuevoJugador->liga, ',');

        getline(ss, dato, ','); nuevoJugador->media = stoi(dato);
        getline(ss, dato, ','); nuevoJugador->ritmo = stoi(dato);
        getline(ss, dato, ','); nuevoJugador->tiros = stoi(dato);
        getline(ss, dato, ','); nuevoJugador->pases = stoi(dato);
        getline(ss, dato, ','); nuevoJugador->regates = stoi(dato);
        getline(ss, dato, ','); nuevoJugador->defensa = stoi(dato);
        getline(ss, dato, ','); nuevoJugador->fisico = stoi(dato);      

        listaJugadores.push_back(nuevoJugador);
    }

    archivo.close(); 
}