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

ApplicationState state = ApplicationState::StartUp;

static float AnimationStripHeight = 128.0f;
static float AnimationStripLength = 1280.0f;

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

        Shader shader("res/shaders/Basic.Shader");
        shader.Bind();

        Texture textureMenuBackground("res/textures/background.png");
        textureMenuBackground.Bind(0);
        shader.SetUniform1i("u_Texture", 0);

        float gameBackgroundPositions[] = {
            0.0f,   0.0f,   0.0f, 0.0f,
            400.0f, 0.0f,   1.0f, 0.0f,
            400.0f, 200.0f, 1.0f, 1.0f,
            0.0f,   200.0f, 0.0f, 1.0f,
        };

        unsigned int gameBackgroundIndices[] = {
            0,1,2,
            2,3,0,
        };

        RenderableObject *GameBackground = RenderableObject::MakeObject2D(gameBackgroundPositions, 4 * 4 * sizeof(float), gameBackgroundIndices, 6, shader);

        glm::mat4 gameProj = glm::ortho(0.0f , 300.f, 0.0f , 300.0f * 540.0f / 960.0f);
        glm::mat4 gameView = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 25.0f, 0));

        Texture textureGameBackground("res/textures/gameBackground.png");
        textureMenuBackground.Bind(0);
        shader.SetUniform1i("u_Texture", 0);

        float boxPositions[] = {
            0.0f, 0.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            0.0f, 1.0f, 0.0f, 1.0f,
        };

        unsigned int boxIndices[] = {
            0,1,2,
            2,3,0,
        };

        RenderableObject *Box = RenderableObject::MakeObject2D(boxPositions, 4 * 4 * sizeof(float), boxIndices, 6, shader);

        Texture textureHitbox("res/textures/hitbox.png");
        textureHitbox.Bind(0);
        shader.SetUniform1i("u_Texture", 0);

        Texture textureHurtbox("res/textures/hurtbox.png");
        textureHurtbox.Bind(0);
        shader.SetUniform1i("u_Texture", 0);

        Shader shaderAnimation("res/shaders/Animation.Shader");
        shaderAnimation.Bind();

        float playerPositions[] = {
            -64.0f,   0.0f, 0.1f,   0.0f, 0.0f,
            64.0f, 0.0f, 0.1f,   AnimationStripHeight / AnimationStripLength, 0.0f,
            64.0f, 128.0f, 0.1f, AnimationStripHeight / AnimationStripLength, 1.0f,
            -64.0f,   128.0f, 0.1f, 0.0f, 1.0f,
        };

        unsigned int playerIndices[] = {
            0,1,2,
            2,3,0,
        };

        RenderableObject* Player = RenderableObject::MakeObject3D(playerPositions, 5 * 4 * sizeof(float), playerIndices, 6, shaderAnimation);

        shaderAnimation.Unbind();

        Renderer renderer;


        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui::StyleColorsDark();
        ImGui_ImplOpenGL3_Init(glsl_version);

        bool showHitboxes = false;

        double currentFrame = glfwGetTime();
        double lastFrame = glfwGetTime();
        double elapsedTimeBuffer = 0.0f;
        int physicsFrames = 0;
        float frameLength = 1.0f / 30.0f;

        float player1pos = 100.0f;
        float player2pos = 300.0f;

        float playermidpoint = 200.0f;
        float cameraPos = 50.0f;

        int gameEndFrames = 0;

        MenuController menuController(shader, renderer, window, state, showHitboxes);

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

            currentFrame = glfwGetTime();
            double deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            elapsedTimeBuffer += deltaTime;
            physicsFrames = elapsedTimeBuffer / frameLength;

            elapsedTimeBuffer = fmod(elapsedTimeBuffer,frameLength);

            inputHandler.CheckButtons();
            std::pair<PlayerStateEnum, PlayerStateEnum> playeractions = inputHandler.GetPlayerActions();

            glm::mat4 gameBackgroundModel = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
            glm::mat4 gameBackgroundMVP;

            glm::mat4 player1Model;
            glm::mat4 player1MVP;

            glm::mat4 player2Model;
            glm::mat4 player2MVP;

            glm::mat4 boxModel;
            glm::mat4 boxMVP;

            Rectangle player1hurtBox;
            Rectangle player1hitBox;
            Rectangle player2hurtBox;
            Rectangle player2hitBox;

            int framenum = 0;

            //TODO: make classes for individual switch cases
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
                gameEndFrames = 0;
                gameModel.Init();
                inputHandler.Init();
                break;
            case GameOngoing:
                std::cout << gameModel.GetPlayerPosition(1).x << ' ' << gameModel.GetPlayerPosition(2).x << std::endl;

                if (!gameModel.P1Won() && !gameModel.P2Won()) {
                    gameModel.PlayerAction(1, playeractions.first);
                    gameModel.PlayerAction(2, playeractions.second);
                }
                else {
                    gameModel.PlayerAction(1, PlayerStateEnum::Idle);
                    gameModel.PlayerAction(2, PlayerStateEnum::Idle);
                    gameEndFrames += physicsFrames;
                }

                if (gameEndFrames > 150) {
                    state = ApplicationState::GameEnd;
                }

                gameModel.GameAdvance(physicsFrames);


                player1hurtBox = gameModel.GetPlayerHurtBox(1);
                player1hitBox = gameModel.GetPlayerHitBox(1);
                player2hurtBox = gameModel.GetPlayerHurtBox(2);
                player2hitBox = gameModel.GetPlayerHitBox(2);

                player1pos = gameModel.GetPlayerPosition(1).x;
                player2pos = gameModel.GetPlayerPosition(2).x;
                playermidpoint = (player1pos + player2pos) / 2.0f;
                cameraPos = playermidpoint - 150.0f;
                if (cameraPos < 0.0f) {
                    cameraPos = 0.0f;
                }
                else if (cameraPos > 100.0f) {
                    cameraPos = 100.0f;
                }
                gameView = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f * cameraPos, 25.0f, 0));
                gameBackgroundMVP = gameProj * gameView * gameBackgroundModel;
                shader.Bind();
                shader.SetUniformMat4f("u_MVP", gameBackgroundMVP);
                textureGameBackground.Bind(0);
                shader.SetUniform1i("u_Texture", 0);
                
                renderer.Draw(GameBackground->vertexArray, GameBackground->indexBuffer, GameBackground->relatedShader);
                
                player1Model = glm::translate(glm::mat4(1.0f), glm::vec3(gameModel.GetPlayerPosition(1).x, gameModel.GetPlayerPosition(1).y, 0));
                player1MVP = gameProj * gameView * player1Model;
                shaderAnimation.Bind();
                shaderAnimation.SetUniformMat4f("u_MVP", player1MVP);
                TextureHandler::GetInstance().BindTexture(gameModel.GetPlayerState(1), 1, gameModel.GetPlayerOrientation(1));
                
                framenum = gameModel.GetPlayerFrameNum(1);

                shaderAnimation.SetUniform1i("u_Texture", 0);
                shaderAnimation.SetUniform1f("u_FrameOffset", float(AnimationStripHeight / AnimationStripLength * framenum));

                renderer.Draw(Player->vertexArray, Player->indexBuffer, shaderAnimation);

                player2Model = glm::translate(glm::mat4(1.0f), glm::vec3(gameModel.GetPlayerPosition(2).x, gameModel.GetPlayerPosition(2).y, 0));
                player2MVP = gameProj * gameView * player2Model;
                shaderAnimation.Bind();
                shaderAnimation.SetUniformMat4f("u_MVP", player2MVP);
                TextureHandler::GetInstance().BindTexture(gameModel.GetPlayerState(2), 2, gameModel.GetPlayerOrientation(2));
                
                framenum = gameModel.GetPlayerFrameNum(2);

                shaderAnimation.SetUniform1i("u_Texture", 0);
                shaderAnimation.SetUniform1f("u_FrameOffset", float(AnimationStripHeight / AnimationStripLength * framenum));

                renderer.Draw(Player->vertexArray, Player->indexBuffer, shaderAnimation);

                boxModel = glm::translate(glm::mat4(1.0f), glm::vec3(player1hurtBox.lowerLeft.x,player1hurtBox.lowerLeft.y,0)) * glm::scale(glm::mat4(1.0f), glm::vec3(player1hurtBox.upperRight.x - player1hurtBox.lowerLeft.x, player1hurtBox.upperRight.y - player1hurtBox.lowerLeft.y, 1));
                boxMVP = gameProj * gameView * boxModel;

                shader.Bind();
                shader.SetUniformMat4f("u_MVP", boxMVP);
                textureHurtbox.Bind(0);
                shader.SetUniform1i("u_Texture", 0);

                if (showHitboxes)
                    renderer.Draw(Box->vertexArray, Box->indexBuffer, Box->relatedShader);

                boxModel = glm::translate(glm::mat4(1.0f), glm::vec3(player2hurtBox.lowerLeft.x, player2hurtBox.lowerLeft.y, 0)) * glm::scale(glm::mat4(1.0f), glm::vec3(player2hurtBox.upperRight.x - player2hurtBox.lowerLeft.x, player2hurtBox.upperRight.y - player2hurtBox.lowerLeft.y, 1));
                boxMVP = gameProj * gameView * boxModel;

                shader.Bind();
                shader.SetUniformMat4f("u_MVP", boxMVP);
                textureHurtbox.Bind(0);
                shader.SetUniform1i("u_Texture", 0);

                if (showHitboxes)
                    renderer.Draw(Box->vertexArray, Box->indexBuffer, Box->relatedShader);

                boxModel = glm::translate(glm::mat4(1.0f), glm::vec3(player1hitBox.lowerLeft.x, player1hitBox.lowerLeft.y, 0)) * glm::scale(glm::mat4(1.0f), glm::vec3(player1hitBox.upperRight.x - player1hitBox.lowerLeft.x, player1hitBox.upperRight.y - player1hitBox.lowerLeft.y, 1));
                boxMVP = gameProj * gameView * boxModel;

                shader.Bind();
                shader.SetUniformMat4f("u_MVP", boxMVP);
                textureHitbox.Bind(0);
                shader.SetUniform1i("u_Texture", 0);

                if (showHitboxes)
                    renderer.Draw(Box->vertexArray, Box->indexBuffer, Box->relatedShader);

                boxModel = glm::translate(glm::mat4(1.0f), glm::vec3(player2hitBox.lowerLeft.x, player2hitBox.lowerLeft.y, 0)) * glm::scale(glm::mat4(1.0f), glm::vec3(player2hitBox.upperRight.x - player2hitBox.lowerLeft.x, player2hitBox.upperRight.y - player2hitBox.lowerLeft.y, 1));
                boxMVP = gameProj * gameView * boxModel;

                shader.Bind();
                shader.SetUniformMat4f("u_MVP", boxMVP);
                textureHitbox.Bind(0);
                shader.SetUniform1i("u_Texture", 0);

                if (showHitboxes)
                    renderer.Draw(Box->vertexArray, Box->indexBuffer, Box->relatedShader);

                {
                    int width, height;
                    glfwGetWindowSize(window, &width, &height);
                    ImVec2 size, pos;
                    size.x = 70;
                    size.y = 30;
                    pos.x = 10;
                    pos.y = 10;
                    ImGuiWindowFlags window_flags = 0;
                    window_flags |= ImGuiWindowFlags_NoTitleBar;
                    window_flags |= ImGuiWindowFlags_NoResize;
                    ImGui::SetNextWindowSize(size);
                    ImGui::SetNextWindowPos(pos);
                    bool open = true;

                    ImGui::Begin("Player1 Health", &open, window_flags);
                    std::string hpbar = "HP: " + std::to_string(gameModel.GetPlayerHealth(1));
                    ImGui::Text(hpbar.c_str());
                    ImGui::End();
                }
                
                {
                    int width, height;
                    glfwGetWindowSize(window, &width, &height);
                    ImVec2 size, pos;
                    size.x = 70;
                    size.y = 30;
                    pos.x = width - 80;
                    pos.y = 10;
                    ImGuiWindowFlags window_flags = 0;
                    window_flags |= ImGuiWindowFlags_NoTitleBar;
                    window_flags |= ImGuiWindowFlags_NoResize;
                    ImGui::SetNextWindowSize(size);
                    ImGui::SetNextWindowPos(pos);
                    bool open = true;

                    ImGui::Begin("Player2 Health", &open, window_flags);
                    std::string hpbar = "HP: " + std::to_string(gameModel.GetPlayerHealth(2));
                    ImGui::Text(hpbar.c_str());
                    ImGui::End();
                }
                if (gameModel.P1Won() || gameModel.P2Won()) {
                    {
                        int width, height;
                        glfwGetWindowSize(window, &width, &height);
                        ImVec2 size, pos;
                        size.x = 134;
                        size.y = 30;
                        pos.x = width / 2 - 67;
                        pos.y = height / 2 - 15;
                        ImGuiWindowFlags window_flags = 0;
                        window_flags |= ImGuiWindowFlags_NoTitleBar;
                        window_flags |= ImGuiWindowFlags_NoResize;
                        ImGui::SetNextWindowSize(size);
                        ImGui::SetNextWindowPos(pos);
                        bool open = true;

                        ImGui::Begin("End Card", &open, window_flags);
                        std::string winner = gameModel.P1Won() ? "Player 1" : "Player 2";
                        std::string content = winner + " has won!";
                        ImGui::Text(content.c_str());
                        ImGui::End();
                    }
                }

                break;
            case GameEnd:
                {
                    int width, height;
                    glfwGetWindowSize(window, &width, &height);
                    ImVec2 size, pos, buttonSize;
                    size.x = 120;
                    size.y = 200;
                    pos.x = floor(width / 2) - floor(size.x / 2);
                    pos.y = floor(3 * height / 4) - floor(size.y / 2);
                    buttonSize.x = 100;
                    buttonSize.y = 50;
                    ImGuiWindowFlags window_flags = 0;
                    window_flags |= ImGuiWindowFlags_NoBackground;
                    window_flags |= ImGuiWindowFlags_NoTitleBar;
                    window_flags |= ImGuiWindowFlags_NoResize;
                    ImGui::SetNextWindowSize(size);
                    ImGui::SetNextWindowPos(pos);
                    bool open = true;

                    ImGui::Begin("Rematch menu", &open, window_flags);
                    if (ImGui::Button("Rematch", buttonSize)) {
                        state = ApplicationState::GameStart;
                    }
                    if (ImGui::Button("Back to menu", buttonSize)) {
                        state = ApplicationState::MenuStart;
                    }
                    ImGui::End();
                }
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
        delete GameBackground;
        delete Box;
        delete Player;

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }



    glfwTerminate();
    return 0;
}