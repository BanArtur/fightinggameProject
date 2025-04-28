#include "MenuController.h"
#include <iostream>

MenuController::MenuController(Shader& sh, Renderer& rend, GLFWwindow* wind, ApplicationState& app, bool& hitb, firebase::App* app_p, bool& userlogged, DatabaseHandler* datab, firebase::auth::Auth* au) : shader(sh), renderer(rend), window(wind), state(app), textureMenuBackground("res/textures/background.png"), showHitboxes(hitb), application(app_p), userLoggedIn(userlogged), database(datab), authentication(au) {
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
    errorMessage = "";
    Init();
}

MenuController::~MenuController() {
    delete MenuBackground;
}

void MenuController::Init() {
    menuState = MenuState::Main;
    userLoggedIn = false;
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
        size.y = 230;
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
        if (ImGui::Button("Play", buttonSize)) {
            state = ApplicationState::GameStart;
        }
        if (ImGui::Button("Account", buttonSize)) {
            if (userLoggedIn) {
                menuState = MenuState::AccountManage;
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
            memset(emailAddress, 0, sizeof(emailAddress));
            memset(password, 0, sizeof(password));
        }
        if (ImGui::Button("Register", buttonSize)) {
            menuState = MenuState::AccountRegister;
            memset(emailAddress, 0, sizeof(emailAddress));
            memset(username, 0, sizeof(username));
            memset(password, 0, sizeof(password));
            memset(passwordAgain, 0, sizeof(passwordAgain));
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
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        ImVec2 size, pos, buttonSize;
        size.x = 250;
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
        ImGui::InputText("email", emailAddress, IM_ARRAYSIZE(emailAddress));
        ImGui::InputText("username", username, IM_ARRAYSIZE(username));
        ImGui::InputText("password", password, IM_ARRAYSIZE(password));
        ImGui::InputText("passwordAgain", passwordAgain, IM_ARRAYSIZE(passwordAgain));
        if (ImGui::Button("Register Account", buttonSize)) {
            if (!IsEmailValid(emailAddress)) {
                errorMessage = "Entered email address was not valid!";
                menuState = MenuState::AccountError;
            }
            else if (!(std::string(password) == std::string(passwordAgain))) {
                errorMessage = "Reentered password did not match the original!";
                menuState = MenuState::AccountError;
            }
            else if (!IsPasswordValid(password, passwordAgain)) {
                errorMessage = "The entered password did not fit requirements!";
                menuState = MenuState::AccountError;
            }
            else {
                firebase::Future<firebase::auth::AuthResult> registerFutureResult = authentication->CreateUserWithEmailAndPassword(emailAddress, password);
                while (registerFutureResult.status() == firebase::kFutureStatusPending) {
                    std::cout << "Registering account..\n";
                }
                firebase::auth::AuthError error = static_cast<firebase::auth::AuthError>(registerFutureResult.error());
                if (error != firebase::auth::kAuthErrorNone) {
                    errorMessage = registerFutureResult.error_message();
                    menuState = MenuState::AccountError;
                }
                else {
                    firebase::Future<firebase::auth::AuthResult> signInFutureResult = authentication->SignInWithEmailAndPassword(emailAddress, password);
                    while (signInFutureResult.status() == firebase::kFutureStatusPending) {
                        std::cout << "Registering account..\n";
                    }
                    firebase::auth::AuthError error = static_cast<firebase::auth::AuthError>(signInFutureResult.error());
                    if (error != firebase::auth::kAuthErrorNone) {
                        errorMessage = signInFutureResult.error_message();
                        menuState = MenuState::AccountError;
                    }
                    else {
                        firebase::auth::User user = signInFutureResult.result()->user;
                        database->CreateNewUserData(user.uid(), UserInfo{username,500});
                        userLoggedIn = true;
                        menuState = MenuState::AccountSuccess;
                    }
                }
            }
        }
        if (ImGui::Button("Back", buttonSize)) {
            menuState = MenuState::Main;
        }
        ImGui::End();
    }
    break;
    case AccountSuccess:
    {
        ImGuiInputTextCallbackData callback;
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        ImVec2 size, pos, buttonSize;
        size.x = 250;
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
        ImGui::Text("Account successfully registered!");
        ImGui::Text("You are now logged in");
        if (ImGui::Button("Back", buttonSize)) {
            menuState = MenuState::Main;
        }
        ImGui::End();
    }
    break;
    case AccountError:
    {
        ImGuiInputTextCallbackData callback;
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        ImVec2 size, pos, buttonSize;
        size.x = 250;
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
        ImGui::Text(errorMessage.c_str());
        if (ImGui::Button("Back", buttonSize)) {
            menuState = MenuState::Main;
        }
        ImGui::End();
    }
    break;
    case AccountLogin:
    {
        ImGuiInputTextCallbackData callback;
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        ImVec2 size, pos, buttonSize;
        size.x = 250;
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
        ImGui::Begin("AccountLogin", &open, window_flags);
        ImGui::InputText("email", emailAddress, IM_ARRAYSIZE(emailAddress));
        ImGui::InputText("password", password, IM_ARRAYSIZE(password));
        if (ImGui::Button("Login", buttonSize)) {
            firebase::Future<firebase::auth::AuthResult> signInFutureResult = authentication->SignInWithEmailAndPassword(emailAddress, password);
            while (signInFutureResult.status() == firebase::kFutureStatusPending) {
                std::cout << "Registering account..\n";
            }
            firebase::auth::AuthError error = static_cast<firebase::auth::AuthError>(signInFutureResult.error());
            if (error != firebase::auth::kAuthErrorNone) {
                errorMessage = signInFutureResult.error_message();
                menuState = MenuState::AccountError;
            }
            else {
                userLoggedIn = true;
                menuState = MenuState::AccountSuccess;
            }
        }
        if (ImGui::Button("Back", buttonSize)) {
            menuState = MenuState::Main;
        }
        ImGui::End();
    }
    break;
    case AccountManage:
        if (userLoggedIn) {
            {
                ImGuiInputTextCallbackData callback;
                int width, height;
                glfwGetWindowSize(window, &width, &height);
                ImVec2 size, pos, buttonSize;
                size.x = 250;
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
                ImGui::Begin("AccountManage", &open, window_flags);
                if (ImGui::Button("Account Info", buttonSize)) {
                    menuState = MenuState::AccountInfo;
                }
                if (ImGui::Button("Log out", buttonSize)) {
                    authentication->SignOut();
                    menuState = MenuState::Main;
                    userLoggedIn = false;
                }
                if (ImGui::Button("Back", buttonSize)) {
                    menuState = MenuState::Main;
                }
                ImGui::End();
            }
        }
        else {
            menuState = MenuState::AccountMain;
        }
        break;
    case AccountInfo:
        {
            UserInfo userInfo = database->GetUserInfo(authentication->current_user().uid());
            ImGuiInputTextCallbackData callback;
            int width, height;
            glfwGetWindowSize(window, &width, &height);
            ImVec2 size, pos, buttonSize;
            size.x = 250;
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
            ImGui::Begin("AccountInfo", &open, window_flags);
            ImGui::Text(("Username: " + userInfo.UserName).c_str());
            ImGui::Text(("Rating: " + std::to_string(userInfo.ratingScore)).c_str());
            if (ImGui::Button("Back", buttonSize)) {
                menuState = MenuState::Main;
            }
            ImGui::End();
        }
        break;
    default:
        break;
    }
}
