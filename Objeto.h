#ifndef OBJETO_H
#define OBJETO_H

#include "Malha.h"
#include <vector>
#include <string>
#include <GL/gl.h>

using namespace std;

class Objeto {
public:
    /* Dados do objeto */
    vector<Malha*> malhas;
    Objeto(string const &caminhoArquivo);
    Objeto(const Objeto& orig);
    virtual ~Objeto();
    void desenha(Shader shader);

private:
    string arquivoMtl;

    // Vetores para leitura temporária
    vector<GLfloat> v;
    vector<GLfloat> vt;
    vector<GLfloat> vn;
    vector<Textura> texturas;
    int iTextura = -1;
    string tipoLeitura = "";
    
    vector<unsigned int> vf;
    vector<unsigned int> vtf;
    vector<unsigned int> vnf;
    
    Textura t;

    const vector<string> explode(const string& s, const char& c);
    void carregaArquivo(string const &caminhoArquivo);
    void trataLinha(string linha);
    void processaMalha();
};

#endif /* OBJETO_H */

