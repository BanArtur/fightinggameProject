#include "MenuController.h"

MenuController::MenuController(Shader& sh, Renderer& rend, GLFWwindow* wind, ApplicationState& app, bool& hitb) : shader(sh), renderer(rend), window(wind), state(app), textureMenuBackground("res/textures/background.png"), showHitboxes(hitb) {
    menuProj = glm::ortho(0.0f, 150.0f, 0.0f, 100.0f, -1.0f, 1.0f);
    menuView = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

    float menuBackgroundPositions[] = {
            0.0f,   0.0f,   0.0f, 0.0f,
            150.0f, 0.0f,   1.0f, 0.0f,
            150.0f, 100.0f, 1.0f, 1.0f,
            0.0f,   100.0f, 0.0f, 1.0f,
    };

    unsigned int menuBackgroundIndices[] = {
        0,1,2,
        2,3,0,
    };

    MenuBackground = RenderableObject::MakeObject2D(menuBackgroundPositions, 4 * 4 * sizeof(float), menuBackgroundIndices, 6, shader);
    Init();
}

MenuController::~MenuController() {
    delete MenuBackground;
}

void MenuController::Init() {
    menuState = MenuState::Main;
}

void MenuController::Render() {
    glm::mat4 menuModel = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    glm::mat4 menuMVP = menuProj * menuView * menuModel;

    shader.Bind();
    shader.SetUniformMat4f("u_MVP", menuMVP);
    textureMenuBackground.Bind(0);
    shader.SetUniform1i("u_Texture", 0);

    renderer.Draw(MenuBackground->vertexArray, MenuBackground->indexBuffer, MenuBackground->relatedShader);

    switch (menuState)
    {
    case Main:
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

        ImGui::Begin("Menu", &open, window_flags);
        if (ImGui::Button("Local Game", buttonSize)) {
            state = ApplicationState::GameStart;
        }
        if (ImGui::Button("Online Game", buttonSize)) {
            if (false) {
                //TODO logged in
            }
            else {
                menuState = MenuState::AccountMain;
            }
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
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        ImVec2 size, pos, buttonSize;
        size.x = 140;
        size.y = 200;
        pos.x = floor(width / 2) - floor(size.x / 2);
        pos.y = floor(3 * height / 4) - floor(size.y / 2);
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
    case AccountMain:
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

        ImGui::Begin("AccountMain", &open, window_flags);
        if (ImGui::Button("Login", buttonSize)) {
            menuState = MenuState::AccountLogin;
        }
        if (ImGui::Button("Register", buttonSize)) {
            menuState = MenuState::AccountRegister;
        }
        if (ImGui::Button("Back", buttonSize)) {
            menuState = MenuState::Main;
        }
        ImGui::End();
    }
    break;    
    case AccountRegister:
    {
        ImGuiInputTextCallbackData callback;
        char emailAddress[256], username[256], password[256], passwordAgain[256];
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
        ImGui::InputText("email", emailAddress, IM_ARRAYSIZE(emailAddress));
        ImGui::InputText("username", username, IM_ARRAYSIZE(username));
        ImGui::InputText("password", password, IM_ARRAYSIZE(password));
        ImGui::InputText("passwordAgain", passwordAgain, IM_ARRAYSIZE(passwordAgain));
        ImGui::Begin("AccountMain", &open, window_flags);
        if (ImGui::Button("Register Account", buttonSize)) {
            if (false) {
                //correct
            }
            else {
                //incorrect
            }
        }
        if (ImGui::Button("Back", buttonSize)) {
            menuState = MenuState::Main;
        }
        ImGui::End();
    }
    break;
    case AccountLogin:

    break;
    case AccountManage:
        if (false) {
            //TODO logged in
        }
        else {
            menuState = MenuState::AccountMain;
        }
        break;
    default:
        break;
    }
}