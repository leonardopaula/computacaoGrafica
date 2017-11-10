#ifndef MALHA_H
#define MALHA_H

#include "Estruturas.h"
#include "shader.h"
#include <string>
#include <vector>

class Malha {
public:
    
    // Informações da malha
    std::vector<Vertice> vertices;
    Textura textura;
    std::vector<unsigned int> indices;
    unsigned int VAO;
    
    Malha(std::vector<Vertice> vertices, std::vector<unsigned int> indices, Textura textures);
    Malha(const Malha& orig);
    virtual ~Malha();
    void desenha(Shader shader);

private:

    unsigned int VBO, EBO;
    void configuraMalha();
};

#endif /* MALHA_H */

