//
// Created by laureano on 08/11/19.
//

#ifndef AEDA_PROJETO_MUSEUM_H
#define AEDA_PROJETO_MUSEUM_H

#include "string"
#include "Address.h"
#include "Atracao.h"
#include "Cliente.h"
#include <vector>

using namespace std;

class Museum : public Atracao {

public:
    Museum();


    void venderBilhete();

    void reservarBilhete();

};


#endif //AEDA_PROJETO_MUSEUM_H
