
/*
 * Arbitro.cpp
 *
 *  Created on: Oct 22, 2017
 *      Author: juan
 */

#include "Juego.h"

Juego::Juego(uint dificultadPedida, uint numeroDeJugadores, uint filas, uint columnas, cadena* nombresDeJugadores){

	this->filaMaxima = filas;
	this->columnaMaxima = columnas;

	this->columnaDeJugada = 0;
	this->filaDeJugada = 0;
	this->diferenciaDePuntaje = 0;

	this->dibujante = new Dibujante(columnas, filas, numeroDeJugadores);
	this->arbitro = new Arbitro(nombresDeJugadores, numeroDeJugadores, dificultadPedida);

	this->tablero = new Casillero**[columnaMaxima];

	inicializarTablero(dificultadPedida);

	this->jugadorActual = 0;

	this->casillerosDestapados = 0;
	this->bombasTotales =  (dificultadPedida * filaMaxima * columnaMaxima) % 16;
}

void Juego::inicializarTablero(uint dificultad){

	//A cada columna le asigno un array de n casilleros, n = nro de filas
	for(uint col =0; col < columnaMaxima; col++){

		tablero[col] = new Casillero*[filaMaxima];

		for(uint fil = 0; fil < filaMaxima; fil++ ){

			tablero[col][fil] = NULL;
		}
	}
}

uint Juego::pedirNumero(std::string mensaje){

	uint numeroIngresado;
	std::cout << mensaje << std::endl;
	std::cin >> numeroIngresado;
	if(numeroIngresado == 0){
		std::cout << "El numero debe ser mayor a cero!" << std::endl;
		this->pedirNumero(mensaje);
	}
	return numeroIngresado;
}

uint Juego::pedirNumero(std::string mensaje, uint numeroMaximo){

	uint numeroIngresado;
	std::cout << mensaje << std::endl;
	std::cin >> numeroIngresado;
	if(numeroIngresado == 0 || numeroIngresado > numeroMaximo){
		std::cout << "Numero no valido! " << std::endl;
		this->pedirNumero(mensaje);
	}
	return numeroIngresado;
}

uint Juego::tomarTipoDeJugada(){

	std::string pedido = "Ingrese el numero de la opcion elegida: \n";
	std::string opcion1 = "1) Colocar / quitar bandera \n";
	std::string opcion2 = "2) Descubrir casillero \n";
	std::string mensajeDeOpciones = pedido + opcion1 + opcion2;

	uint tipoDeJugada = pedirNumero(mensajeDeOpciones, 3);
	return tipoDeJugada;
}

void Juego::tomarUbicacionDeJugada(){
	filaDeJugada = pedirNumero("Por favor, ingrese la fila donde desea realizar la jugada", filaMaxima);
	columnaDeJugada = pedirNumero("Por favor, ingrese la columna donde desea realizar la jugada", columnaMaxima);
}

void Juego::avanzarTurno(){
	arbitro->avanzarTurno();
}

void Juego::tomarJugada(){

	cadena tipoDeJugada;

	uint opcionElegida = this->tomarTipoDeJugada();

	uint jugadorActual = this->arbitro->devolverTurno();

	tomarUbicacionDeJugada();

	//Si es colocar/quitar bandera:
	if (opcionElegida == 1){

		this->prepararCasillero();

		//No hay bandera, pone
		if ( ! tablero[columnaDeJugada][filaDeJugada]->tieneBandera() ){

			tipoDeJugada = "bandera";

			if ( (tablero[columnaDeJugada][filaDeJugada])->tieneBomba() ){ // es una bandera donde hay bomba
				this->arbitro->sumarPuntaje(1);
			} else { // no hay bomba
				this->arbitro->sumarPuntaje(-1);
			}

			this->dibujante->cambiarCuadrante(columnaDeJugada,filaDeJugada,tipoDeJugada, this->arbitro->devolverTurno(), false);
			this->dibujante->cambiarPuntaje( this->arbitro->devolverPuntaje(), jugadorActual );
			this->tablero[columnaDeJugada][filaDeJugada]->colocarBandera(jugadorActual);

		// Hay bandera, saca
		} else {

			tipoDeJugada = "cubierto"; //POR EL AMOR DE JEHOVA USEMOS CONSTANTES

			//No pertenece a este jugador
			if ( tablero[columnaDeJugada][filaDeJugada]->quienPusoLaBandera() == jugadorActual ){ //es el mismo
				// elimina bandera de la lista cuando sale
				tipoDeJugada = "cubierto";

			} else { // es otro, caso en que corrige jugada del otro
				if (  ){ // es una bandera donde hay bomba
					// la quita cuando sale pero le resta puntos porque si habia bomba


				} else { // era una bandera mal puesta

				}
			}
			// elimina la bandera
			this->eliminarBandera(fila, columna);
		}

	} else { //Descubrir casillero

		// ver si las coordenadas son validas
		Bomba supuestaBomba(this->columnaDeJugada, this->filaDeJugada);

		if (existeBomba(supuestaBomba)){
			this->jugadorActual->asignarEstado(true); // (perdio)
			this->tipoDeJugada = "boom";
			// se saca de la lista de jugadores y se agrega a la de eliminados
			this->eliminarJugador();
		} else { //Debo pasar en string el numero de bombas circundantes.

			uint numeroDeBombasCircundantes = evaluarBombasCircundantes(columnaDeJugada, filaDeJugada);
			std::ostringstream ossCircundantes;
			ossCircundantes << numeroDeBombasCircundantes;
			this->tipoDeJugada = ossCircundantes.str();
		}
	}
}

void Juego::prepararCasillero(){
	if(tablero[columnaDeJugada][filaDeJugada] == 0){
		tablero[columnaDeJugada][filaDeJugada] = new Casillero();
	}
}

uint Juego::evaluarBombasCircundantes(uint columnaDeCasillero, uint filaDeCasillero){
	uint cantidadDeCircundantes = 0;
	for(int dFila = -1; dFila < 2; dFila++){
		for(int dColumna = -1; dColumna < 2; dColumna++ ){

			int columnaAEvaluar = columnaDeCasillero - dColumna;
			int filaAEvaluar = filaDeCasillero - dFila;

			if( (filaAEvaluar > -1 ) && (columnaAEvaluar > -1) &&
					(filaAEvaluar <= (int)this->filaMaxima) &&
					(columnaAEvaluar <= (int)this->columnaMaxima) ){
				if (){
					cantidadDeCircundantes++;
				}
			}
		}
	}
	this->casillerosDestapados++;
	return cantidadDeCircundantes;
}

uint Juego::devolverColumnaDeJugada(){
	return columnaDeJugada;
}

uint Juego::devolverFilaDeJugada(){
	return filaDeJugada;
}

void Juego::declararTurno(){
	std::cout << "Es el turno de "<< (arbitro->devolverJugadorActual())->consultarNombre() << std::endl;
}

int Juego::devolverPuntaje(){
	int puntajeJugador = arbitro->devolverJugadorActual()->consultarPuntaje();
	if (puntajeJugador < 0) {
		return 0;
	} else {
		return puntajeJugador;
	}
}

void Juego::crearBombas(uint dificultad){

	srand (time(NULL));
	int bombasRestantes = bombasTotales;
	while (bombasRestantes > 0){
		//Genero dos numeros semi-aleatorios para usar de coordenada
		uint xAleatorio = rand() % filaMaxima;
		uint yAleatorio = rand() % columnaMaxima;
		//solo afecta el casillero si no hay una mina ya sobre el
		if ( tablero[xAleatorio][yAleatorio] == 0 ){

			(tablero[xAleatorio][yAleatorio]) = new Casillero(true);

			bombasRestantes --;

		}
	}
}

void Juego::eliminarBandera(uint fila, uint columna){
	tablero[columna][fila]->quitarBandera();
}

bool Juego::terminoLaPartida(){
	return (arbitro->murieronTodos() || this->noQuedanCasilleros() );
}

bool Juego::noQuedanCasilleros(){
	return (casillerosDestapados == ( (filaMaxima * columnaMaxima) - bombasTotales ));
}

cadena Juego::hacerCadena(int numero){
	std::ostringstream ossnumero;
	ossnumero << numero;
	return ossnumero.str();
}


Juego::~Juego(){
	//LIBERAR MEMORIA DEL TABLERO!!

}
