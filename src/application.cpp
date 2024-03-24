#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/*GL ABSTRACTION INCLUDES*/
#include "renderer.h"
#include "vertexBuffer.h"
#include "vertexBufferLayout.h"
#include "indexBuffer.h"
#include "vertexArray.h"
#include "shader.h"
#include "texture.h"
#include "camera.h"
#include "chunk.h"

const int width  = 1000;
const int height = 1000;
bool looking = true;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        looking = !looking;
        std::cout << looking << std::endl;
    }
}

int main(void)
{
    /* DECLARING THE WINDOW */
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "minecraft java edition", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSetWindowPos(window, 200, 200);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    glViewport(0, 0, width, height);


    std::cout << "VERSION " << glGetString(GL_VERSION) << std::endl;
    {
        shader shader("resources/shaders/basic.shader");
        shader.Bind();

        texture text("resources/textures/textureAtlas.png");
        text.Bind();
        shader.setUniform1i("uTexture", 0);

        int textureIndex = 4;

        int dimension = text.getAtlasDimension();
        float xOffset = text.getTextureXOffset(textureIndex);
        float yOffset = text.getTextureYOffset(textureIndex);

        shader.setAtlasUniform("uDimension", "uOffset", dimension, xOffset, yOffset);
        shader.setMatrixUniform("uModelMatrix", glm::mat4(1.0f));

        renderer simpleRender;

        glEnable(GL_DEPTH_TEST);

        glfwSetKeyCallback(window, key_callback);

        camera playerCam(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

        chunk Chunk({0.0f, 0.0f, -5.0f});

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            if (looking) playerCam.inputs(window);
            playerCam.matrix(90.0f, 0.1f, 100.0f, shader, "uCameraMatrix");

            Chunk.renderChunk(shader, simpleRender);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}