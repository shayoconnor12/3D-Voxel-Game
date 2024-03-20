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

const int width  = 800;
const int height = 800;

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
        float squarePositions[] = 
        {
            //COORDINATES  /                 TEXTURE COORDINATES //
            -0.5f, -0.5f,  0.0f,                 0.0f, 0.0f, //0
             0.5f, -0.5f,  0.0f,                 1.0f, 0.0f, //1
             0.5f,  0.5f,  0.0f,                 1.0f, 1.0f, //2
            -0.5f,  0.5f,  0.0f,                 0.0f, 1.0f, //3
        };
        float positions[] =
        {
            //COORDINATES  /                 TEXTURE COORDINATES //
            -0.5f,  0.0f,  0.5f,                 0.0f, 0.0f, //0
            -0.5f,  0.0f, -0.5f,                 1.0f, 0.0f, //1
             0.5f,  0.0f, -0.5f,                 0.0f, 0.0f, //2
             0.5f,  0.0f,  0.5f,                 1.0f, 0.0f, //3
             0.0f,  0.8f,  0.0f,                 0.5f, 1.0f, //3
        };

        unsigned int oldIndices[] = 
        {
            0, 1, 2, //right triangle
            2, 3, 0  //left triangle
        };

        unsigned int indices[] =
        {
            0, 1, 2, 
            0, 2, 3,
            0, 1, 4,
            1, 2, 4,
            2, 3, 4,
            3, 0, 4
        };

        /*CREATE BUFFER*/
        vertexArray vArray;
        vertexBuffer vBuffer(positions, 5 * 5 * sizeof(float));
        vertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(2);
        vArray.addBuffer(vBuffer, layout);

        /*CREATE INDEX BUFFER*/ 
        indexBuffer iBuffer(indices, 3 * 6);

        shader shader("resources/shaders/basic.shader");
        shader.Bind();

        texture text("resources/textures/textureAtlas.png");
        text.Bind();
        shader.setUniform1i("uTexture", 0);

        int textureIndex = 6;

        int dimension = text.getAtlasDimension();
        float xOffset = text.getTextureXOffset(textureIndex);
        float yOffset = text.getTextureYOffset(textureIndex);


        shader.setAtlasUniform("uDimension", "uOffset", dimension, xOffset, yOffset);

        vArray.unBind();
        vBuffer.unBind();
        iBuffer.unBind();
        shader.unBind();

        renderer simpleRender;

        float rotation = 0.0f;
        double prevTime = glfwGetTime();

        glEnable(GL_DEPTH_TEST);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {

            simpleRender.Clear();

            shader.Bind();

            double crntTime = glfwGetTime();
            if (crntTime - prevTime >= 1 / 60)
            {
                rotation += 0.5f;
                prevTime = crntTime;
            }

            glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 view = glm::mat4(1.0f);
            glm::mat4 projection = glm::mat4(1.0f);

            model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
            view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
            projection = glm::perspective(glm::radians(45.0f), (float)(width / height), 0.1f, 100.0f);

            shader.setMatrixUniform("uModel", model);
            shader.setMatrixUniform("uView", view);
            shader.setMatrixUniform("uProjection", projection);

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