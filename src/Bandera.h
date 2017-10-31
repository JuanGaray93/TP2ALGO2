#ifndef BANDERA_H
#define BANDERA_H
#endif
#include "Jugador.h"
#include "Bomba.h"
#include "Lista.h"
typedef int Coordenada[2];
class Bandera{
private:
	Coordenada coordenadas;
	Jugador* jugador;
	bool bienColocada;

public:

	//POST Crea Bandera POR DEFECTO VA A ESTAR EN FALSE EL bienColocada
	Bandera(int coordenadaX, int coordenadaY, Jugador* jugador);

	//Post Bandera Vacia
	Bandera();

	//POST CAMBIA COORDENADA X
	void cambiarCoordenadaX(int coordX);

	//POST CAMBIA COORDENADA Y
	void cambiarCoordenadaY(int coordY);

	//POST DEVUELVE COORDENADA X
	int obtenerCoordenadaX();

	//POST DEVUELVE COORDENADA Y
	int obtenerCoordenadaY();

	//POST DEVUELVE SI ESTA bienColocada
	bool banderaBienColocada();

	//POST VALIDA Y CAMBIA bienColocada
	void validarColocacion(Lista<Bomba>* bombas);

	//POST DEVUELVE EL JUGADOR QUE COLOCO LA BANDERA
	Jugador* obtenerJugador();
};
