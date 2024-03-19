#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <sstream>
#include "renderer.h"
#include "vertexBuffer.h"
#include "vertexBufferLayout.h"
#include "indexBuffer.h"
#include "vertexArray.h"
#include "shader.h"



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

    window = glfwCreateWindow(700, 400, "Unreal engine 6", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    {
        /*POSITION ARRAY FOR TRIANGLE VERTEXES*/
        float positions[] = {
            -0.5f, -0.5f, //0
             0.5f, -0.5f, //1
             0.5f,  0.5f, //2
            -0.5f,  0.5f, //3
        };

        unsigned int indices[] = {
            0, 1, 2, //right triangle
            2, 3, 0  //left triangle
        };

        /*CREATE BUFFER*/
        vertexArray vArray;
        vertexBuffer vBuffer(positions, 4 * 2 * sizeof(float));
        vertexBufferLayout layout;
        layout.Push<float>(2);
        vArray.addBuffer(vBuffer, layout);

        /*CREATE INDEX BUFFER*/
        indexBuffer iBuffer(indices, 6);

        shader shader("resources/shaders/basic.shader");
        shader.Bind();
        shader.setUniform4f("uColour", 0.2f, 0.3f, 0.8f, 1.0f);

        vArray.unBind();
        vBuffer.unBind();
        iBuffer.unBind();
        shader.unBind();

        renderer simpleRender;

        float r = 1.0f;
        float g = 0.0f;
        float b = 0.0f;
        float increment = 0.01f;
        float gincrement = 0.01f;
        bool lerping = false;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {

            simpleRender.Clear();

            shader.Bind();
            shader.setUniform4f("uColour", r, g, b, 1.0f);

            vArray.Bind();
            iBuffer.Bind();

            simpleRender.Draw(vArray, iBuffer, shader);

            if (!lerping)
            {
                if (r > 0)
                    r -= increment;

                if (g >= 1) 
                    gincrement = -0.01f;
                else if (g <= 0)
                    gincrement = 0.01f;

                g += gincrement;

                if (r <= 0)
                    b += increment;

                if (b >= 1.0) {
                    // Smoothly transition from blue to red
                    lerping = true;
                }
            }
            else
            {
                r += increment;
                g += gincrement;
                b -= increment;

                if (r >= 1.0f && (g <= 0.0f || g >= 1.0) && b <= 0.0f)
                    lerping = false;
            }

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}