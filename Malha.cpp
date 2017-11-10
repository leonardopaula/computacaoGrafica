#include "Malha.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

Malha::Malha(std::vector<Vertice> vertices, std::vector<unsigned int> indices, Textura textures)
{
    this->vertices = vertices;
    this->indices  = indices;
    this->textura  = textures;
    
    configuraMalha();
}

void Malha::desenha(Shader shader)
{
    glm::mat4 mInicial = glm::rotate(glm::mat4(), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    shader.setMat4("model", mInicial);
    
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);   
}

void Malha::configuraMalha()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // Vamos carregar os dados
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertice), &vertices[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    
    // Posições das vértices
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertice), (void*)0);

    // Normais
    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertice), (void*)offsetof(Vertice, Normal));

    // Coordenadas de textura
    //glEnableVertexAttribArray(2);	
    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertice), (void*)offsetof(Vertice, CoordTextura));
    
    glBindVertexArray(0);
}

Malha::Malha(const Malha& orig) {
    cout << "destruiu malha orig" << endl;
}

Malha::~Malha() {
    cout << "destruiu malha" << endl;
}

