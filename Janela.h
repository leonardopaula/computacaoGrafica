#ifndef JANELA_H
#define JANELA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Janela {
public:
    Janela(int w = 800, int h = 600, const char* titulo = "");
    virtual ~Janela();
    GLFWwindow* getJanela(){ return o_janela; }

private:
    // Referência da janela
    GLFWwindow* o_janela;

    // Função para tratamento de erro
    static void erroCallBack(int id_erro, const char* descricao);
    
    /* Não funciona o callback aqui...
    // Tratamento do tamanho
    static void redimensiona_callback(GLFWwindow* janela, int w, int h);
    */
    
    // Dados da janela
    int w, h;
    char* titulo;
};

#endif /* JANELA_H */

