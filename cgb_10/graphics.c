#include <stdio.h>
#include "graphics.h"
#include "scene.h"
#include "camera.h"

static GLFWwindow *window;
static int resized = 0;

int startGraphics(int width, int height)
{
    /* TODO: What is set to the error code? */
    /*
    is called after the error code is set.
    passes the error code to the callback.
    The callback is called on the thread, where the error occured
    The callback can be `NULL`.
    returns the previous set callback.
    */
    /* `glfwGetError` returns the error code */
    glfwSetErrorCallback(errorCallback);

    /*
    is called `glfwTerminate` should be called before the application terminates.
    if it succeeds it returns `GLFW_TRUE` else it returns `GLFW_FALSE`.
    */
    if (!glfwInit())
    {
        printf("Error initilizing graphics.");
        return 1;
    }
    glfwWindowHint(GLFW_SAMPLES, 4);

    window = glfwCreateWindow(width, height, "Engine", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        printf("Error opening window.");
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glEnable(GL_MULTISAMPLE);
    /* https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/glEnable.xml */
    /* TODO: Why is there server-side?*/
    /* is disabled by default. */
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    enableCameraMouseControl(window);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    loadScene(window);
    while (!glfwWindowShouldClose(window))
    {
        renderScene();
        glfwSwapBuffers(window);
        glfwPollEvents();
        printFps();
        if (resized)
        {
            resized = 0;
            setViewportSize(window);
        }
    }
    unloadScene();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

static void errorCallback(int error, const char *description)
{
    printf("Error: %s\n", description);
}

static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    else if (key == GLFW_KEY_M && action == GLFW_PRESS)
    {
        if (glfwGetWindowAttrib(window, GLFW_MAXIMIZED))
        {
            glfwRestoreWindow(window);
        }
        else
        {
            glfwMaximizeWindow(window);
        }
    }
}

static void framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    resized = 1;
}

static void printFps()
{
    static double previousTime = 0;
    static int frameCount = 0;

    double currentTime = glfwGetTime();
    if (currentTime - previousTime >= 1.0)
    {
        printf("FPS: %i\n", frameCount);

        frameCount = 0;
        previousTime = currentTime;
    }
    frameCount++;
}