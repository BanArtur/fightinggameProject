#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "RenderableObject.h"
#include "GameModel.h"
#include "InputHandler.h"
#include "TextureHandler.h"

#include "AppEnums.h"

#include "MenuController.h"
#include "GameController.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

#include <firebase/app.h>
#include <firebase/database.h>
#include <firebase/auth.h>
#include <firebase/firestore.h>

int main(void)
{

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a window and its OpenGL context */


    /*
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    window = glfwCreateWindow(mode->width, mode->height, "My Title", monitor, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }*/

    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);


    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        std::cout << "Error during glewinit" << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    {
        const char* glsl_version = "#version 130";

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        firebase::AppOptions appOptions;
        appOptions.set_app_id("1:698482346110:android:54e7665125e3402b98b02f");
        appOptions.set_api_key("AIzaSyD0FUhK3TmHAckxU6qmCBLmTZCQpiTZfRY");
        appOptions.set_project_id("fightinggameproject-d00a1");
        firebase::App* app = firebase::App::Create(appOptions);
        firebase::database::Database* database = firebase::database::Database::GetInstance(app);
        firebase::firestore::Firestore* firestore = firebase::firestore::Firestore::GetInstance(app);

        ApplicationState state = ApplicationState::StartUp;

        Shader shader("res/shaders/Basic.Shader");
        shader.Bind();

        Texture textureMenuBackground("res/textures/background.png");
        textureMenuBackground.Bind(0);
        shader.SetUniform1i("u_Texture", 0);

        Shader shaderAnimation("res/shaders/Animation.Shader");
        shaderAnimation.Bind();

        shaderAnimation.Unbind();

        Renderer renderer;


        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui::StyleColorsDark();
        ImGui_ImplOpenGL3_Init(glsl_version);

        bool showHitboxes = false;
        MenuController menuController(shader, renderer, window, state, showHitboxes);
        GameController gameController(shader, shaderAnimation, renderer, window, state, showHitboxes);

        GameModel gameModel;

        InputHandler inputHandler;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            switch (state)
            {
            case StartUp:
                state = ApplicationState::MenuStart;
                break;
            case MenuStart:
                state = ApplicationState::MenuOngoing;
                menuController.Init();
                break;
            case MenuOngoing:
                menuController.Render();
                break;
            case GameStart:
                state = ApplicationState::GameOngoing;
                gameController.Init();
                break;
            case GameOngoing:
                gameController.Render();
                break;
            case GameEnd:
                gameController.RenderGameEnd();
                break;
            default:
                break;
            }
            

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        delete firestore;
        delete database;
        delete app;
    }

    glfwTerminate();
    return 0;
}