/* Estruturas para os objetos */

#include <string>
#include <glm/glm.hpp>

#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

// Todas informações vindas do .mtl (pikachu)
struct Textura {
    unsigned int id; // Id na GPU
    string tipo;     // Tipo da textura
    string caminho; // Caminho para a textura
    int Ns;         // Ns 10
    float Ni;       // Ni 1.0
    float d;        // d 1.0
    glm::vec3 Tf;   // Tf 1 1 1
    int illum;      // illum 2
    glm::vec3 Ka;   // Ka 0.5 0.5 0.5
    glm::vec3 Kd;   // Kd 0.9 0.9 0.9
    glm::vec3 Ks;   // Ks 0.0 0.0 0.0
    
};

// Vertices
struct Vertices {
    glm::vec3 Posicao;      // Posições (v)
    glm::vec3 CoordTextura; // Coordenadas de textura (vt)
    glm::vec3 Normal;       // Normais (vn)
};


#endif /* ESTRUTURAS_H */

