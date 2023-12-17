#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shaderClass.h"
#include "VBO.h"
#include "VAO.h"
#include "IBO.h"



// Define vertex data for a cube
float vertices[] = {
    -0.5f, -0.5f, 0.0f,  /* Vertex 0 */
    0.0f, 0.5f, 0.0f,   /* Vertex 1 */
    0.5f, -0.5f, 0.0f,    /* Vertex 2 */
};

// Define indices for a cube
GLuint indices[] = {
    0, 1, 2
};



int main() {
    // Initialise GLFW
    if (!glfwInit()) {
        return -1;
    }

    // Create window object
    GLFWwindow* window = glfwCreateWindow(640, 640, "Solid Filled Square Window", nullptr, nullptr);
    if (!window) {
        // Window creation failed - destroy remaining windows
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        // GLEW initialization failed
        glfwTerminate();
        return -1;
    }


    Shader shaderProgram("Default.vert", "Default.frag");


    VAO VAO1;
    VAO1.Bind();
    VBO VBO1(vertices, sizeof(vertices));
    IBO IBO1(indices, sizeof(indices));

    VAO1.linkAttrib(VBO1, 0, 3, GL_FLOAT, 3*sizeof(float), (void*)0);

    VAO1.Unbind();
    VBO1.Unbind();
    IBO1.Unbind();

    // Main window loop
    while (!glfwWindowShouldClose(window)) {
        // Render here
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        // Bind the shader program
        shaderProgram.Activate();

        // Bind the VAO and IBO
        VAO1.Bind();
        IBO1.Bind();

        // Draw the cube using indices
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            printf("OpenGL Error %d\n", error);
        }

        // Unbind VAO and IBO
        IBO1.Unbind();
        VAO1.Unbind();

        GLenum framebufferStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (framebufferStatus != GL_FRAMEBUFFER_COMPLETE) {
            printf("Framebuffer not complete! Error: %x\n", framebufferStatus);
        }

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Clean up
    IBO1.Delete();
    VAO1.Delete();
    VBO1.Delete();
    shaderProgram.Delete();

    glfwTerminate();
    return 0;
}
