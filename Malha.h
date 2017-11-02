#ifndef MALHA_H
#define MALHA_H

#include "Estruturas.h"
#include <string>
#include <vector>

class Malha {
public:
    // Informações da malha
    std::vector<Vertice> vertices;
    std::vector<Textura> texturas;
    
    Malha();
    Malha(const Malha& orig);
    virtual ~Malha();
private:

};

#endif /* MALHA_H */

