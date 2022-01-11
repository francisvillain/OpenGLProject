#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "ErrorHandler.h"
#include "Texture.h"
#include <Windows.h>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // sync to vsync propably 60 fps

    if (glewInit() != GLEW_OK)
        std::cout << "Error glewInit!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        float positions[] = {
            -0.5f,-0.5f, 0.0f, 0.0f,
             0.5f, -0.5f, 1.0f, 0.0f,
             0.5f, 0.5f, 1.0f, 1.0f,
             -0.5f, 0.5f, 0.0f, 1.0f
        };

        unsigned int indices[] = {
            0,1,2,
            2,3,0
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        VertexArray va;
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);
       
        IndexBuffer ib(indices, 6);

        Shader shader("res/shaders/Basic.shader");
        shader.Bind();

        Texture texture0("res/texture/dark-parquet.png");
        texture0.Bind(1);
        shader.SetUniform1i("woodTexture", 0);

        Texture texture1("res/texture/lava.png");
        texture1.Bind(2);
        shader.SetUniform1i("lightfireTexture", 1);

        Texture texture2("res/texture/fire-dark.png");
        texture2.Bind(3);
        shader.SetUniform1i("darkFireTexture",2);
        
        Texture texture3("res/texture/blend-map-3.png");
        texture3.Bind(4);
        shader.SetUniform1i("blendMapTexture", 3);

        Texture texture4("res/texture/blend-map-2.png");
        texture4.Bind(5);

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        Renderer renderer;
        

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            //load another blend-map on right and left mouse button click to render different textures mix
            if ((GetKeyState(VK_RBUTTON) & 0x80) != 0)
            {
                shader.SetUniform1i("blendMapTexture", 4);
            }
            if ((GetKeyState(VK_LBUTTON) & 0x80) != 0)
            {
                shader.SetUniform1i("blendMapTexture", 3);
            }
            /* Render here */
            renderer.Clear();

            shader.Bind();

            renderer.Draw(va, ib, shader);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

    }
    glfwTerminate();
    return 0;
}