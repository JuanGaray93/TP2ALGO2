
/*
 * Arbitro.cpp
 *
 *  Created on: Oct 22, 2017
 *      Author: juan
 */

#include "Juego.h"

Juego::Juego(int dificultad, int numeroDeJugadores, int filas, int columnas, std::string* nombresDeJugadores){

	if (filas < 0 || columnas < 0){
		throw std::string("Error: Intenta crear tablero con dimension negativa.");
	}
	bomba = "boom";
	bandera = "bandera";
	casilleroCubierto = "cubierto";
	margen = "margen";

	this->columnaDeJugada = 0;
	this->filaDeJugada = 0;
	this->seDebeEliminarJugador = false;

	this->dibujante = new Dibujante(columnas, filas, numeroDeJugadores, nombresDeJugadores);
	this->arbitro = new Arbitro(nombresDeJugadores, numeroDeJugadores, dificultad);

	tablero.asignarDimensionesYDificultad(columnas, filas, dificultad);

	dibujarTablero();
}

//UI y pedidos de datos

int Juego::pedirNumero(std::string mensaje){

	int numeroIngresado;
	std::cout << mensaje << std::endl;
	std::cin >> numeroIngresado;

	while (std::cin.fail()){
		std::cin.clear();
		std::cin.ignore();
		std::cin >> numeroIngresado;
	}

	if(numeroIngresado <= 0){

		std::cout << "El numero debe ser mayor a cero!" << std::endl;
		numeroIngresado =  pedirNumero(mensaje);
	}
	return numeroIngresado;
}

int Juego::pedirNumero(std::string mensaje, int numeroMaximo){

	int numeroIngresado = 0;
	std::cout << mensaje << std::endl;
	std::cin >> numeroIngresado;

	while (std::cin.fail()){
		std::cin.clear();
		std::cin.ignore();
		std::cin >> numeroIngresado;
	}

	if(numeroIngresado <= 0 || numeroIngresado > numeroMaximo){

		std::cout << "Numero no valido! " << std::endl;
		numeroIngresado = pedirNumero(mensaje, numeroMaximo);
	}
	return numeroIngresado;
}

int Juego::tomarTipoDeJugada(){

	std::string pedido = "Ingrese el numero de la opcion elegida: \n";
	std::string opcion1 = "1) Colocar / quitar bandera \n";
	std::string opcion2 = "2) Descubrir casillero \n";
	std::string mensajeDeOpciones = pedido + opcion1 + opcion2;

	int tipoDeJugada = pedirNumero(mensajeDeOpciones, 2);
	return tipoDeJugada;
}

void Juego::tomarUbicacionDeJugada(){
	filaDeJugada = pedirNumero("Por favor, ingrese la FILA donde desea realizar la jugada", tablero.obtenerFilaMaxima() ) - 1;
	columnaDeJugada = pedirNumero("Por favor, ingrese la COLUMNA donde desea realizar la jugada", tablero.obtenerColumnaMaxima() ) - 1;
}

void Juego::tomarJugada(){
	std::string queDibujar;
	bool haJugado = false;
	int opcionElegida;
	int jugadorActual;

	while (! haJugado){

		opcionElegida = tomarTipoDeJugada();
		jugadorActual = arbitro->devolverNumeroDeTurno();
		tomarUbicacionDeJugada();

		//Es colocar/quitar bandera:
		if ((opcionElegida == 1) && (! tablero.estaDescubierto(columnaDeJugada, filaDeJugada) )){

			cambiarBandera(jugadorActual);
			haJugado = true;

		//Es destapar
		} else if ( ! tablero.hayBanderaEn(columnaDeJugada, filaDeJugada) ) {

			descubrirCasillero(columnaDeJugada, filaDeJugada, jugadorActual);
			haJugado = true;

		} else {
			std::cout << "Esa jugada no es valida!" << std::endl;
		}
	}
}

//Logica de juego

void Juego::avanzarTurno(){
	if (seDebeEliminarJugador){
		std::cout << (arbitro->devolverJugador()).consultarNombre() << " fue eliminado!" << std::endl;
	}
	arbitro->avanzarTurno(seDebeEliminarJugador);
	seDebeEliminarJugador = false;
}

void Juego::cambiarBandera(int jugadorActual){

	std::string queDibujar = "";
	int puntajeADevolver = 0;

	//No hay bandera, la pone
	if ( ! tablero.hayBanderaEn(columnaDeJugada, filaDeJugada) ){

		bool pusoBien = tablero.colocarBandera(columnaDeJugada, filaDeJugada, jugadorActual);
		queDibujar = bandera;

		if (pusoBien){
			puntajeADevolver = 1;

		} else {
			puntajeADevolver = -1;
		}

	//Hay bandera, saca
	} else {

		int quienPuso = tablero.obtenerJugadorQueColocoBandera(columnaDeJugada, filaDeJugada);
		bool bienQuitada = tablero.quitarBandera(columnaDeJugada, filaDeJugada);
		if( quienPuso != jugadorActual ){
			if (bienQuitada){
				puntajeADevolver = 2;
			} else{
				puntajeADevolver = -2;
			}
		}

		queDibujar = casilleroCubierto;
		this->dibujante->cambiarCuadrante(columnaDeJugada, filaDeJugada, queDibujar, jugadorActual, false);
	}

	this->arbitro->sumarPuntaje(puntajeADevolver);
	int puntaje = arbitro->devolverPuntaje();
	this->dibujante->cambiarPuntaje( puntaje, jugadorActual );
	this->dibujante->cambiarCuadrante(columnaDeJugada, filaDeJugada, queDibujar, jugadorActual, false);
}

void Juego::descubrirCasillero(int columnaDeCasillero, int filaDeCasillero, int jugadorActual){

	std::string queDibujar = "";

	tablero.descubrirCasillero(columnaDeCasillero, filaDeCasillero);

	//Tiene bomba
	if (tablero.hayBombaEn(columnaDeCasillero, filaDeCasillero) ){

		queDibujar = bomba;
		seDebeEliminarJugador = true;
		dibujante->eliminarJugador(jugadorActual);

	//No tiene bomba
	} else {

		int numeroDeBombasCircundantes = tablero.obtenerNumeroDeBombasCircundantes(columnaDeCasillero, filaDeCasillero);
		queDibujar = hacerCadena(numeroDeBombasCircundantes);

		if (numeroDeBombasCircundantes == 0){
			descubrirCasillerosCircundantes(columnaDeCasillero, filaDeCasillero);
		}
	}
	this->dibujante->cambiarCuadrante(columnaDeCasillero, filaDeCasillero, queDibujar, jugadorActual, false);
}


void Juego::descubrirCasillerosCircundantes(int columnaDeCasillero, int filaDeCasillero){

	for(int dFila = -1; dFila < 2; dFila++){
		for(int dColumna = -1; dColumna < 2; dColumna++ ){

			int columnaAEvaluar = columnaDeCasillero + dColumna;
			int filaAEvaluar = filaDeCasillero + dFila;

			if ((tablero.esCoordenadaValida(columnaAEvaluar,filaAEvaluar)) && (! tablero.estaDescubierto(columnaAEvaluar, filaAEvaluar)) ){
				//Llamada recursiva entre el metodo actual y descubrirCasillero.
				descubrirCasillero(columnaAEvaluar, filaAEvaluar, 0);
			}
		}
	}
}

void Juego::declararTurno(){
	std::cout << "Es el turno de "<< (arbitro->devolverJugador()).consultarNombre() << std::endl;
}

void Juego::dibujarTablero(){
	dibujante->dibujarTablero();
}

void Juego::anunciarGanador(){
	arbitro->anunciarGanador();
}

bool Juego::terminoLaPartida(){
	bool termino = ( arbitro->quedaUno() || noQuedanCasilleros() );
	return termino;
}

bool Juego::noQuedanCasilleros(){
	return tablero.noQuedanCasilleros();
}

std::string Juego::hacerCadena(int numero){
	std::ostringstream ossnumero;
	ossnumero << numero;
	return ossnumero.str();
}

Juego::~Juego(){
	delete dibujante;
	delete arbitro;
}


