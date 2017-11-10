#include <cstdlib>
#include "Objeto.h"
#include "Janela.h"
#include "Camera.h"

using namespace std;

void processaEntradas(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Camera camera(glm::vec3(0.0f, 0.5f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// Timing
float deltaTime = 0.0f;	// "FPS"
float lastFrame = 0.0f;
glm::vec3 lightPos(0.8f, 0.8f, 1.0f);

int main(int argc, char** argv) 
{
    Janela jan(800, 600, "Pokemon");
    
    Objeto obj("/home/leonardo/Dropbox/Unisinos/2017-2/Computação Gráfica/Projetos/Final/objs/Pikachus/Pikachu.obj");
    
    Shader shaderObjetos("shaders/shader.basic_light.vs", "shaders/shader.basic_light.fs");
    
    //Habilita o z-buffer
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(jan.getJanela()))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processaEntradas(jan.getJanela());
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
        
        // Ativa o shader principal
        shaderObjetos.use();
        shaderObjetos.setVec3("objectColor", 1.0f, 1.0f, 1.0f);
        shaderObjetos.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        shaderObjetos.setVec3("lightPos", lightPos);
        
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        shaderObjetos.setMat4("projection", projection);

        glm::mat4 view = camera.GetViewMatrix();
        shaderObjetos.setMat4("view", view);

        obj.desenha(shaderObjetos);
        
        glfwSwapBuffers(jan.getJanela());
        glfwPollEvents();
    }

    return 0;
}

void processaEntradas(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// Captura Mouse
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    /*if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
    */
}

// Captura scroll do mouse
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    //camera.ProcessMouseScroll(yoffset);
}