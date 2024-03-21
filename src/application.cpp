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

    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        /*POSITION ARRAY FOR TRIANGLE VERTEXES*/
        const float positions[] = {
            // Front face
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // Bottom-left
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // Bottom-right
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // Top-right
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // Top-left

            // Back face
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // Bottom-right
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // Top-right
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // Top-left

            // Right face
             0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // Bottom-left
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // Bottom-right
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // Top-right
             0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // Top-left

            // Left face
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
            -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // Bottom-right
            -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // Top-right
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // Top-left

            // Top face
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, // Bottom-left
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // Bottom-right
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // Top-right
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // Top-left

            // Bottom face
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // Bottom-right
             0.5f, -0.5f,  0.5f,  1.0f, 1.0f, // Top-right
            -0.5f, -0.5f,  0.5f,  0.0f, 1.0f  // Top-left
        };

        // Index array
        const unsigned int indices[] = {
            // Front face
            0, 1, 2,
            2, 3, 0,
            // Back face
            4, 5, 6,
            6, 7, 4,
            // Right face
            8, 9, 10,
            10, 11, 8,
            // Left face
            12, 13, 14,
            14, 15, 12,
            // Top face
            16, 17, 18,
            18, 19, 16,
            // Bottom face
            20, 21, 22,
            22, 23, 20
        };

        /*CREATE BUFFER*/
        vertexArray vArray;
        vertexBuffer vBuffer(positions, /*number of vertices*/ 24 * /*number of bytes*/ 5 * sizeof(float));
        vertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(2);
        vArray.addBuffer(vBuffer, layout);

        /*CREATE INDEX BUFFER*/ 
        indexBuffer iBuffer(indices, 6 * 6);

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

        vArray.unBind();
        vBuffer.unBind();
        iBuffer.unBind();
        shader.unBind();

        renderer simpleRender;

        glEnable(GL_DEPTH_TEST);

        camera playerCam(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

        glfwSetKeyCallback(window, key_callback);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            simpleRender.Clear();

            shader.Bind();

            if (looking) playerCam.inputs(window);
            playerCam.matrix(45.0f, 0.1f, 100.0f, shader, "uCameraMatrix");

            vArray.Bind();

            iBuffer.Bind();

            simpleRender.Draw(vArray, iBuffer, shader);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}