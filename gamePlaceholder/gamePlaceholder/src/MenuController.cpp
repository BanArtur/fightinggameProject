#include "MenuController.h"

MenuController::MenuController(Shader& sh, Renderer& rend) : shader(sh), renderer(rend){
    menuState = MenuState::Main;
}

MenuController::~MenuController() {
}
/*
void MenuController::Render(int windowWidth, int windowHeight) {
    shader.Bind();
    shader.SetUniformMat4f("u_MVP", menuMVP);
    textureMenuBackground.Bind(0);
    shader.SetUniform1i("u_Texture", 0);

    renderer.Draw(vaMenuBackground, ibMenuBackground, shader);

    switch (menuState)
    {
    case Main:
    {
        ImVec2 size, pos, buttonSize;
        size.x = 120;
        size.y = 200;
        pos.x = floor(windowWidth / 2) - floor(size.x / 2);
        pos.y = floor(3 * windowHeight / 4) - floor(size.y / 2);
        buttonSize.x = 100;
        buttonSize.y = 50;
        ImGuiWindowFlags window_flags = 0;
        window_flags |= ImGuiWindowFlags_NoBackground;
        window_flags |= ImGuiWindowFlags_NoTitleBar;
        window_flags |= ImGuiWindowFlags_NoResize;
        ImGui::SetNextWindowSize(size);
        ImGui::SetNextWindowPos(pos);
        bool open = true;

        ImGui::Begin("Menu", &open, window_flags);
        if (ImGui::Button("Local Game", buttonSize)) {
            state = ApplicationState::GameStart;
        }
        if (ImGui::Button("Settings", buttonSize)) {
            menuState = MenuState::Settings;
            std::cout << "Settings clicked" << std::endl;
        }
        if (ImGui::Button("Exit", buttonSize)) {
            glfwSetWindowShouldClose(window, 1);
        }
        ImGui::End();
    }
    break;
    case Settings:
    {
        ImVec2 size, pos, buttonSize;
        size.x = 140;
        size.y = 200;
        pos.x = floor(windowWidth / 2) - floor(size.x / 2);
        pos.y = floor(3 * windowHeight / 4) - floor(size.y / 2);
        buttonSize.x = 120;
        buttonSize.y = 50;
        ImGuiWindowFlags window_flags = 0;
        window_flags |= ImGuiWindowFlags_NoBackground;
        window_flags |= ImGuiWindowFlags_NoTitleBar;
        window_flags |= ImGuiWindowFlags_NoResize;
        ImGui::SetNextWindowSize(size);
        ImGui::SetNextWindowPos(pos);
        bool open = true;

        ImGui::Begin("Settings", &open, window_flags);
        ImGui::Checkbox("Show hit- and\nhurtboxes", &showHitboxes);
        if (ImGui::Button("Back to\nmain menu", buttonSize)) {
            menuState = MenuState::Main;
        }
        ImGui::End();
    }
    break;
    default:
        break;
    }
}*/
