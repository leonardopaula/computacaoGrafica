#include "Objeto.h"
#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include <fstream>

using namespace std;

Objeto::Objeto(std::string const &caminhoArquivo) 
{
    carregaArquivo(caminhoArquivo);
}

void Objeto::carregaArquivo(std::string const &caminhoArquivo)
{
    cout << "Carregando arquivo: " << caminhoArquivo.c_str() << endl;

    try
    {
        string linha;
        ifstream handleArquivo;
        stringstream stringStream;

        handleArquivo.exceptions(ifstream::badbit);
        handleArquivo.open(caminhoArquivo.c_str(), ifstream::in);
            
        // Percorre o arquivo linha a linha
        while(getline(handleArquivo, linha))
        {
            trataLinha(linha);
        }
            
        handleArquivo.close();
    } 
    catch(exception e)
    {
        cerr << "[ERRO] " << e.what() << ":" << caminhoArquivo.c_str() << endl;
    }
}

void Objeto::trataLinha(string linha)
{
    // Verifica se a linha possui conteúdo
    if (linha != "")
    {
        vector<string> dados;
        dados = explode(linha, ' ');
        string tipo = dados[0].c_str();
        
        //cout << tipo << endl;

        for(int i = 1; i < dados.size(); i++)
        {
            if (tipo != "#")
            {
                if (tipo == "v") // Vertices
                {
                    //vertices.push_back(atof(dados[i].c_str()));
                    //cout << "|" << dados[i] << "|";
                } else if (tipo == "f") // Faces
                {
                    //indices.push_back(atoi(dados[i].c_str())-1);
                    //cout << "|" << dados[i] << "|";
                } else if (tipo == "vn") // Vetor normal
                {
                    //normais.push_back(atof(dados[i].c_str()));
                } else if (tipo == "mtllib") {

                    // Armazenamos o arquivo com as texturas
                    arquivoMtl = dados[i].c_str();

                } else if (tipo == "vt") {
                } else {
                    //cout << "-> " << tipo << endl;
                }
            }
        }
    }
}

const vector<string> Objeto::explode(const string& s, const char& c)
{
    string buff = "";
    vector<string> v;

    for(int i = 0; i < s.length(); i++)
    {
        if(s[i] != c && s[i] != ' ') buff+=s[i]; else
        if(s[i] == c && buff != "") { v.push_back(buff); buff = ""; }
    }
    if (buff != "") v.push_back(buff);

    return v;
}

Objeto::Objeto(const Objeto& orig) {
}

Objeto::~Objeto() {
}

