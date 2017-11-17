/*
 * Casillero.h
 *
 *  Created on: Nov 7, 2017
 *      Author: juan
 */

#ifndef CASILLERO_H_
#define CASILLERO_H_

#include "Bandera.h"
#include "Comunes.h"

class Casillero{

 private:

	 bool bomba;
	 bool esVisible;
	 Bandera* bandera;

 public:

	 /*
	  * Post: Crea casillero sin bomba o bandera y tapado
	  */
	 Casillero();

	 /*
	  * Post: Crea casillero tapado, sin bandera. Si tiene o no bomba depende de conBomba
	  */
	 Casillero(bool conBomba);

	 /*
	  *
	  */
	 void colocarBandera(int jugador);

	 /*
	  *
	  */
	 void quitarBandera();

	 /* Pre: El casillero tiene bandera
	  * Post: Devuelve quien la puso.
	  */
	 int quienPusoLaBandera();

	 /*
	  *
	  */
	 bool tieneBomba();

	 /*
	  *
	  */
	 bool tieneBandera();

	 /*
	  *
	  */
	 bool estaDescubierto();

	 /*
	  *
	  */
	 void destapar();

	 /*
	  * Post: Libera los recursos asociados, especificalente los pedidos para la bandera
	  */
	 ~Casillero();
 };



#endif /* CASILLERO_H_ */
