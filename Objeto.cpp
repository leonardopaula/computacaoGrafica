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

        handleArquivo.exceptions(ifstream::badbit|ifstream::failbit);
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

        for(int i = 1; i < dados.size(); i++)
        {
            if (tipo != "#")
            {
                if (tipo == "v") // Vertices
                {
                    // Adiciona vértices
                    v.push_back(atof(dados[i].c_str()));
                } else if (tipo == "f") // Faces
                {
                    //indices.push_back(atoi(dados[i].c_str())-1);
                    //cout << "|" << dados[i] << "|";
                } else if (tipo == "vn") // Vetor normal
                {

                    vn.push_back(atof(dados[i].c_str()));

                } else if (tipo == "mtllib") 
                {
                    // Armazenamos o arquivo com as texturas
                    std::stringstream ss;
                    ss << "./objs/Pikachus/" << dados[i].c_str();
                    arquivoMtl = ss.str();
                    
                    // Carrega texturas
                    carregaArquivo(arquivoMtl);

                } else if (tipo == "vt") 
                {
                    vt.push_back(atof(dados[i].c_str()));
                } else if (tipo == "usemtl") 
                {
                    cout << "Ativa Textura" << tipo << endl;
                } else if (tipo == "newmtl")
                {
                    cout << "Material: " << dados[i] << endl;
                } else {
                    cout << "-> " << tipo << endl;
                }
            }
        }
    }
}

void Objeto::processaMalha()
{
    // Dados para repassar à malha
    vector<Vertice> vv;
    glm::vec3 __v; 
    glm::vec3 __vt;
    glm::vec3 __vn;
    
    Vertice vertice;
    for(int i; i < sizeof(v); i++)
    {
        __v.x  = v[i];
        __vt.x = vt[i];
        __vn.x = vn[i++];
        
        __v.y  = v[i];
        __vt.y = vt[i];
        __vn.y = vn[i++];
        
        __v.z  = v[i];
        __vt.z = vt[i];
        __vn.z = vn[i];
        
        vertice.Posicao = __v;
        vertice.CoordTextura = __vt;
        vertice.Normal  = __vn;

        vv.push_back(vertice);
    }
    
}

const vector<string> Objeto::explode(const string& s, const char& c)
{
    string buff = "";
    vector<string> v;

    for(int i = 0; i < s.length(); i++)
    {
        if(s[i] != c && s[i] != ' ' && s[i] != '\t') buff+=s[i]; else
        if(s[i] == c && buff != "") 
        { 
            v.push_back(buff); buff = ""; 
        }
    }
    if (buff != "") v.push_back(buff);

    return v;
}

Objeto::Objeto(const Objeto& orig) {
}

Objeto::~Objeto() {
}

