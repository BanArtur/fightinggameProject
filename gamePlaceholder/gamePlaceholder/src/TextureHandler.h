#pragma once
#include "Texture.h"
#include "PlayerStateEnum.h"

class TextureHandler {
private:
    Texture* player1IdleRight;
    Texture* player1IdleLeft;
    Texture* player1WalkForwardRight;
    Texture* player1WalkForwardLeft;
    Texture* player1WalkBackRight;
    Texture* player1WalkBackLeft;
    Texture* player1LightRight;
    Texture* player1LightLeft;
    Texture* player1HeavyRight;
    Texture* player1HeavyLeft;
    Texture* player2IdleRight;
    Texture* player2IdleLeft;
    Texture* player2WalkForwardRight;
    Texture* player2WalkForwardLeft;
    Texture* player2WalkBackRight;
    Texture* player2WalkBackLeft;
    Texture* player2LightRight;
    Texture* player2LightLeft;
    Texture* player2HeavyRight;
    Texture* player2HeavyLeft;
    TextureHandler();
public:
    ~TextureHandler();

    void operator=(TextureHandler const&) = delete;
    TextureHandler(TextureHandler const&) = delete;

    void BindTexture(PlayerStateEnum state, int playernum, int orientation);

    static TextureHandler& GetInstance() {
        static TextureHandler INSTANCE;
        return INSTANCE;
    }
};
