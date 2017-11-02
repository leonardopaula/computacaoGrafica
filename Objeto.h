#ifndef OBJETO_H
#define OBJETO_H

#include "Malha.h"
#include <vector>
#include <string>

class Objeto {
public:
    /* Dados do objeto */
    std::vector<Malha> malhas;
    
    Objeto(std::string const &caminhoObjeto);

    Objeto(const Objeto& orig);
    virtual ~Objeto();
private:

};

#endif /* OBJETO_H */

