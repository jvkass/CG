/*
 * Vetor.h
 *
 *  Created on: 31 de ago de 2018
 *      Author: joao
 */

#ifndef VETOR_H_
#define VETOR_H_

#include "Matriz.h"

class Vetor: public Matriz {
public:
	Vetor(int altura);
	virtual ~Vetor();
};

#endif /* VETOR_H_ */
