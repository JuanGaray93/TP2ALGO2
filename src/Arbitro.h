/*
 * Arbitro.h
 *
 *  Created on: Oct 19, 2017
 *      Author: juan
 */
#ifndef ARBITRO_H_
#define ARBITRO_H_

#include <sstream>
#include "Lista.h"
#include "Jugador.h"


typedef unsigned int uint;
typedef std::string cadena;

class Arbitro{

  private:

	uint dificultad;
	uint cantJugadores;
	uint filaMaxima;
	uint columnaMaxima;

	uint columnaDeJugada;
	uint filaDeJugada;

	bool finDeJuego;
	
	Lista<Jugador> listaDeJugadores;
	Lista<Bomba> listaDeBombas;
	Lista<Bandera> listaDeBanderas;

	void inicializarListaDeJugadores();
	void inicializarListaDeBombas();

	/*
	 * Post: Pide que el usuario ingrese un numero hasta recibir uno mayor a cero.
	 * 		 Devuelve el numero ingresado.
	 */
	uint pedirNumero(std::string mensaje);

	/*
	 * Post: Pide que el usuario ingrese un numero hasta recibir uno mayor a cero.
	 * 		 Devuelve el numero ingresado.
	 */
	uint pedirNumero(std::string mensaje, uint numeroMaximo);

	/*
	 *
	 */
	void tomarTipoDeJugada();

	/*
	 *
	 */
	void tomarUbicacionDeJugada();

  public:
	/* Pre: Se le pasan numeros naturales.
	 * Post: Crea un arbitro listo para pasarle jugadas
	 */
	Arbitro(uint dificultadPedida, uint numeroDeJugadores, uint filas, uint columnas, cadena* listaDeNombresDeJugadores);
	
	/*
	 * Post: Le toma la jugada al usuario. 
	 * Decide el resultado de la jugada.
	 */
	void tomarJugada();
	
	/*
	 * Post: Devuelve en que columna se realizo la ultima jugada tomada.
	 */
	uint devolverColumnaDeJugada();
	
	/*
	 * Post: Devuelve en que columna se realizo la ultima jugada tomada.
	 */
	uint devolverFilaDeJugada();
	
	/*
	 * Post: Devuelve string con el tipo de jugada que se realizo.
	 */
	std::string devolverTipoDeJugada();
	
	/*
	 * Post: Devuelve el numero de jugador que realizo la ultima jugada.
	 */
	uint devolverTurno();
	
	/*
	 *
	 */
	void declararTurno();
	
	/*
	 * Post: Devuelve el puntaje total del jugador que jugo ultimo.
	 *	 Devuelve -1 si no se modifica.
	 */
	int devolverPuntaje();
	
	/*
	 * Post: 
	 */
	bool terminoElJuego();

};



#endif /* ARBITRO_H_ */
