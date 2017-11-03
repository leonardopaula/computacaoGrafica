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
    vector<Malha> malhas;
    
    Objeto(string const &caminhoArquivo);

    Objeto(const Objeto& orig);
    virtual ~Objeto();
private:
    string arquivoMtl;
    int tipoLeitura;

    // Vetores para leitura temporária
    vector<GLfloat> v;
    vector<GLfloat> vt;
    vector<GLfloat> vn;
    

    const vector<string> explode(const string& s, const char& c);
    void carregaArquivo(string const &caminhoArquivo);
    void trataLinha(string linha);
    void processaMalha();
};

#endif /* OBJETO_H */

