#include "Janela.h"

void redimensiona_callback(GLFWwindow* janela, int w, int h);

Janela::Janela(int w, int h, const char* titulo) 
{
    this->w = w;
    this->h = h;
//    this->titulo = titulo;
    
    // Iniciar GLFW
    if (! glfwInit() )
    {
        std::cerr << "Problema Iniciar GLFW" << std::endl;
    }
    
    // Define versão do OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    
    // Bloqueia funções obsoletas
    glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GL_FALSE);
    
    glfwSetErrorCallback(Janela::erroCallBack);
    
    // Criar Janela
    o_janela = glfwCreateWindow(w, h, titulo, NULL, NULL);
    
    if (!o_janela)
    {
        std::cerr << "Erro janela" << std::endl;
        return;
    }

    // Vincula janela ao contexto atual
    glfwMakeContextCurrent(o_janela);
    
    // Se a tela for redimensionada, função redesenha
    glfwSetFramebufferSizeCallback(o_janela, redimensiona_callback);

    glewExperimental = GL_TRUE;
    
    glEnable(GL_DEPTH_TEST);

    GLenum glewInitErr = glewInit();
    if (glewInitErr != GLEW_OK)
    {
        std::cerr << "Erro criando janela" << glewInitErr << std::endl;
        return;
    }

    // Coleta informações de versão
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version  = glGetString(GL_VERSION);
    std::cout << "Renderizador: " << renderer << std::endl;
    std::cout << "Versão suportada: " << version << std::endl;
    
    // Limpa buffer de cor
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

Janela::~Janela() {
    
    glfwDestroyWindow(o_janela);
    glfwTerminate();
}

void Janela::erroCallBack(int id_erro, const char* descricao)
{
    std::cerr << "Erro: " << id_erro << " => " << descricao << std::endl;
}

void redimensiona_callback(GLFWwindow* janela, int w, int h)
{
    glViewport(0, 0, w, h);
}