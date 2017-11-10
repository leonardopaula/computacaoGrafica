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

void Objeto::desenha(Shader shader)
{
    for(int i=0; i < malhas.size(); i++)
    {
        malhas[i]->desenha(shader);
    }
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
            //cout << linha << endl;
            if (linha != "\r")
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
                if (tipoLeitura == "f" && tipo != "f")
                    processaMalha();
                tipoLeitura = tipo;
                
                if (tipo == "v") // Vertices
                {
                    // Adiciona vértices
                    v.push_back(atof(dados[i++].c_str()));
                    v.push_back(atof(dados[i++].c_str()));
                    v.push_back(atof(dados[i].c_str()));

                } else if (tipo == "f") // Faces
                {
                    
                    vector<string> dadosFace;
                    // São 3 grupos
                    for(int j = 0; j < 3; j++)
                    {
                        dadosFace = explode(dados[i++].c_str(), '/');
                    
                        // São índices de arrays (começam em 0)
                        vf.push_back(atoi(dadosFace[0].c_str())-1);
                        vtf.push_back(atoi(dadosFace[1].c_str())-1);
                        vnf.push_back(atoi(dadosFace[2].c_str())-1);
                    }

                } else if (tipo == "vn") // Vetor normal
                {

                    vn.push_back(atof(dados[i].c_str()));
                } else if (tipo == "usemtl") 
                {
                    if (iTextura >= 0)
                    {
                        //processaMalha();
                    }

                    for(int j = 0; j < texturas.size(); j++)
                    {
                        if (texturas.at(j).tipo ==  dados[i].c_str())
                        {
                            iTextura = j; // Retorna o índice no vetor de texturas
                            break;
                        }
                    }
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
                } else if (tipo == "newmtl")
                {
                    if (t.tipo != dados[i].c_str() && t.tipo != "")
                    {
                        texturas.push_back(t);
                    }
                    t.caminho = arquivoMtl;
                    t.tipo    = dados[i].c_str();

                } else if (tipo == "Ka") {
                    t.Ka.x = atof(dados[i++].c_str());
                    t.Ka.y = atof(dados[i++].c_str());
                    t.Ka.z = atof(dados[i++].c_str());

                } else if (tipo == "Kd") {
                    t.Kd.x = atof(dados[i++].c_str());
                    t.Kd.y = atof(dados[i++].c_str());
                    t.Kd.z = atof(dados[i++].c_str());

                } else if (tipo == "Ks") {
                    t.Ks.x = atof(dados[i++].c_str());
                    t.Ks.y = atof(dados[i++].c_str());
                    t.Ks.z = atof(dados[i++].c_str());

                } else if (tipo == "map_Kd") {
                    t.caminho = dados[i].c_str();
                } else {
                    //cout << "-> " << tipo << dados[i] << endl;
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
    cout << v.size() << "TAM" << endl;
    for(int i = 0; i < v.size(); i++)
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

        cout << __v.x << "," << __v.y << "," << __v.z << endl;

        vertice.Posicao      = __v;
        vertice.CoordTextura = __vt;
        vertice.Normal       = __vn;

        vv.push_back(vertice);
    }

    malhas.push_back(new Malha(vv, vf, texturas[iTextura]));
    
    // Limpa dados locais
    //v.clear();
    //vt.clear();
    //vn.clear();
    //vf.clear();
}

const vector<string> Objeto::explode(const string& s, const char& c)
{
    string buff = "";
    vector<string> v;

    for(int i = 0; i < s.length(); i++)
    {
        if(s[i] != c && s[i] != ' ' && s[i] != '\t' && s[i] != '\r') buff+=s[i]; else
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

