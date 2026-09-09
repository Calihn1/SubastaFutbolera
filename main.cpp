#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <conio.h> 
#include <iomanip>
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

void mostrarCarta(Jugador* j) {
    cout << "\n===========================\n";
    cout << "| " << setw(23) << left << j->media << " |\n";
    cout << "| " << setw(23) << left << j->posicion << " |\n";
    cout << "|                         |\n";
    cout << "| " << setw(23) << left << j->nombre << " |\n";
    cout << "===========================\n";
    cout << "| RIT: " << setw(2) << j->ritmo << "    DEF: " << setw(2) << j->defensa << "  |\n";
    cout << "| TIR: " << setw(2) << j->tiros << "    FIS: " << setw(2) << j->fisico << "  |\n";
    cout << "| PAS: " << setw(2) << j->pases << "    REG: " << setw(2) << j->regates << "  |\n";
    cout << "===========================\n\n";
}

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

Usuario* iniciarSubasta(Jugador* j, Usuario* u1, Usuario* u2) {
    int precioBase = (j->media > 85) ? (rand() % 41 + 60) : (rand() % 76 + 5); /
    int ofertaActual = 0;
    Usuario* maxPostor = nullptr;
    
    cout << "--------------------------------------------------\n";
    cout << "JUGADOR EN SUBASTA! Posicion: " << j->posicion << " | Media: " << j->media << "\n";
    cout << "PRECIO BASE: " << precioBase << " Millones\n";
    cout << "Presupuestos -> " << u1->nombre << ": " << u1->presupuesto << "M | " << u2->nombre << ": " << u2->presupuesto << "M\n";
    cout << "Oprime '" << u1->tecla << "' para " << u1->nombre << " | Oprime '" << u2->tecla << "' para " << u2->nombre << "\n";
    cout << "--------------------------------------------------\n";

    auto inicio = chrono::steady_clock::now();
    int ultimoSegundoImpreso = 10;
    int tiempoTotal = 10;

    while (true) {
        auto ahora = chrono::steady_clock::now();
        int transcurrido = chrono::duration_cast<chrono::seconds>(ahora - inicio).count();
        int tiempoRestante = tiempoTotal - transcurrido;

        if (tiempoRestante != ultimoSegundoImpreso) {
            cout << "\rTiempo restante: " << tiempoRestante << " segundos... " << flush;
            ultimoSegundoImpreso = tiempoRestante;
        }

        if (tiempoRestante <= 0) break;

        if (_kbhit()) {
            char tecla = _getch();
            Usuario* postorIntento = nullptr;

            if (tolower(tecla) == tolower(u1->tecla)) postorIntento = u1;
            else if (tolower(tecla) == tolower(u2->tecla)) postorIntento = u2;

            if (postorIntento) {
                cout << "\n\n>>" << postorIntento->nombre << " presiono para ofertar!\n";
                
                if (ofertaActual == 0) {
                    if (postorIntento->presupuesto >= precioBase) {
                        ofertaActual = precioBase;
                        maxPostor = postorIntento;
                        cout << postorIntento->nombre << " iguala el precio base de " << precioBase << "M.\n";
                        inicio = chrono::steady_clock::now(); // Reinicia cronómetro
                    } else {
                        cout << "Fondos insuficientes para el precio base.\n";
                    }
                } else {
                    int aumento;
                    cout << "Ingrese la cantidad a aumentar (Minimo 10M, Presupuesto libre: " << (postorIntento->presupuesto - ofertaActual) << "M): ";
                    cin >> aumento;
                    
                    if (aumento >= 10 && (ofertaActual + aumento) <= postorIntento->presupuesto) {
                        ofertaActual += aumento;
                        maxPostor = postorIntento;
                        cout << postorIntento->nombre << " sube la oferta a " << ofertaActual << "M!\n";
                        inicio = chrono::steady_clock::now(); // Reinicia cronómetro
                    } else {
                        cout << "Monto invalido o fondos insuficientes. La subasta continua...\n";
                    }
                }
                cout << "\nReanudando reloj...\n";
            }
        }
    }

    cout << "\n\nTIEMPO AGOTADO!\n";
    if (maxPostor) {
        maxPostor->presupuesto -= ofertaActual;
        cout << maxPostor->nombre << " ficha a " << j->nombre << " por " << ofertaActual << " Millones!\n";
        mostrarCarta(j);
    } else {
        cout << "Nadie oferto por " << j->nombre << ". El jugador queda libre.\n";
    }
    
    return maxPostor;
}

int main() {
    srand(time(NULL));
    
    // Configuración Inicial
    Usuario u1, u2;
    u1.tecla = 'e';
    u2.tecla = 'p';

    cout << "========================================\n";
    cout << "        SUBASTA FUTBOLERA DEFINITIVA    \n";
    cout << "========================================\n";
    cout << "Ingrese nombre del Jugador 1 (Tecla 'E'): ";
    cin >> u1.nombre;
    cout << "Ingrese nombre del Jugador 2 (Tecla 'P'): ";
    cin >> u2.nombre;

    vector<Jugador*> todosLosJugadores;
    // IMPORTANTE: Asegúrate de tener el archivo "jugadores.csv" en la misma carpeta
    cargarJugadores("jugadores.csv", todosLosJugadores); 

    if (todosLosJugadores.empty()) {
        cout << "Error: No hay jugadores disponibles para subastar.\n";
        return 1;
    }

    // Para simplificar, simulamos un pool de 22 jugadores al azar (11 para cada uno)
    // En un sistema avanzado, filtrarías por posiciones específicas.
    cout << "\nPreparando la subasta de 22 jugadores estelares...\n\n";

    for (int i = 0; i < 22; i++) {
        // Validación de quiebra
        if (u1.presupuesto <= 0 && u1.equipo.size() < 11) {
            cout << u1.nombre << " se quedo sin dinero y no pudo completar su 11! PIERDE AUTOMATICAMENTE.\n";
            return 0;
        }
        if (u2.presupuesto <= 0 && u2.equipo.size() < 11) {
            cout << u2.nombre << " se quedo sin dinero y no pudo completar su 11! PIERDE AUTOMATICAMENTE.\n";
            return 0;
        }

        // Obtener jugador aleatorio
        int indiceRandom = rand() % todosLosJugadores.size();
        Jugador* jSubasta = todosLosJugadores[indiceRandom];

        // Se ejecuta la subasta
        Usuario* ganador = iniciarSubasta(jSubasta, &u1, &u2);
        
        if (ganador) {
            ganador->equipo.push_back(jSubasta);
        } else {
            // Si nadie lo compra, repetimos el ciclo para asegurar que completen los 22 fichajes
            i--; 
        }
        
        system("pause"); // Pausa antes del siguiente jugador
        system("cls"); // Limpia consola (En Windows)
    }

    // FASE FINAL: Muestra de canchas y Enfrentamiento
    mostrarCancha(&u1);
    mostrarCancha(&u2);

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
            cout << "Gana " << u1.nombre << "!\n";
            scoreU1++;
        } else if (j2->media > j1->media) {
            cout << "Gana " << u2.nombre << "!\n";
            scoreU2++;
        } else {
            cout << "Empate!\n";
        }
    }

    cout << "\n------------------------------------------------------\n";
    cout << "RESULTADO FINAL: " << u1.nombre << " [" << scoreU1 << "] - [" << scoreU2 << "] " << u2.nombre << "\n";
    
    if (scoreU1 > scoreU2) cout << "EL ONCE DE " << u1.nombre << " ES EL GANADOR!\n";
    else if (scoreU2 > scoreU1) cout << "EL ONCE DE " << u2.nombre << " ES EL GANADOR!\n";
    else cout << "HAY UN EMPATE TECNICO ENTRE AMBOS EQUIPOS!\n";
    
    return 0;
}