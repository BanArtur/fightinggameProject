#include "TextureHandler.h"

TextureHandler::TextureHandler() {
    player1IdleRight = new Texture("res/textures/playercharacter1idleright.png");
    player1IdleLeft = new Texture("res/textures/playercharacter1idleleft.png");
    player1WalkForwardRight = new Texture("res/textures/playercharacter1walkforwardright.png");
    player1WalkForwardLeft = new Texture("res/textures/playercharacter1walkforwardleft.png");
    player1WalkBackRight = new Texture("res/textures/playercharacter1walkbackright.png");
    player1WalkBackLeft = new Texture("res/textures/playercharacter1walkbackleft.png");
    player1LightRight = new Texture("res/textures/playercharacter1lightright.png");
    player1LightLeft = new Texture("res/textures/playercharacter1lightleft.png");
    player1HeavyRight = new Texture("res/textures/playercharacter1heavyright.png");
    player1HeavyLeft = new Texture("res/textures/playercharacter1heavyleft.png");
    player2IdleRight = new Texture("res/textures/playercharacter2idleright.png");
    player2IdleLeft = new Texture("res/textures/playercharacter2idleleft.png");
    player2WalkForwardRight = new Texture("res/textures/playercharacter2walkforwardright.png");
    player2WalkForwardLeft = new Texture("res/textures/playercharacter2walkforwardleft.png");
    player2WalkBackRight = new Texture("res/textures/playercharacter2walkbackright.png");
    player2WalkBackLeft = new Texture("res/textures/playercharacter2walkbackleft.png");
    player2LightRight = new Texture("res/textures/playercharacter2lightright.png");
    player2LightLeft = new Texture("res/textures/playercharacter2lightleft.png");
    player2HeavyRight = new Texture("res/textures/playercharacter2heavyright.png");
    player2HeavyLeft = new Texture("res/textures/playercharacter2heavyleft.png");
}

TextureHandler::~TextureHandler() {
    delete player1IdleRight;
    delete player1IdleLeft;
    delete player1WalkForwardRight;
    delete player1WalkForwardLeft;
    delete player1WalkBackRight;
    delete player1WalkBackLeft;
    delete player1LightRight;
    delete player1LightLeft;
    delete player1HeavyRight;
    delete player1HeavyLeft;
    delete player2IdleRight;
    delete player2IdleLeft;
    delete player2WalkForwardRight;
    delete player2WalkForwardLeft;
    delete player2WalkBackRight;
    delete player2WalkBackLeft;
    delete player2LightRight;
    delete player2LightLeft;
    delete player2HeavyRight;
    delete player2HeavyLeft;
}


void TextureHandler::BindTexture(PlayerStateEnum state, int playernum, int orientation) {
    switch (state)
    {
    case Idle:
        if (playernum == 1 && orientation == 1) {
            player1IdleRight->Bind(0);
        }
        else if (playernum == 1 && orientation == -1) {
            player1IdleLeft->Bind(0);
        }
        else if (playernum == 2 && orientation == 1) {
            player2IdleRight->Bind(0);
        }
        else {
            player2IdleLeft->Bind(0);
        }
        break;
    case MovingLeft:
        if (playernum == 1 && orientation == 1) {
            player1WalkBackRight->Bind(0);
        }
        else if (playernum == 1 && orientation == -1) {
            player1WalkForwardLeft->Bind(0);
        }
        else if (playernum == 2 && orientation == 1) {
            player2WalkBackRight->Bind(0);
        }
        else {
            player2WalkForwardLeft->Bind(0);
        }
        break;
    case MovingRight:
        if (playernum == 1 && orientation == 1) {
            player1WalkForwardRight->Bind(0);
        }
        else if (playernum == 1 && orientation == -1) {
            player1WalkBackLeft->Bind(0);
        }
        else if (playernum == 2 && orientation == 1) {
            player2WalkForwardRight->Bind(0);
        }
        else {
            player2WalkBackLeft->Bind(0);
        }
        break;
    case AttackL:
        if (playernum == 1 && orientation == 1) {
            player1LightRight->Bind(0);
        }
        else if (playernum == 1 && orientation == -1) {
            player1LightLeft->Bind(0);
        }
        else if (playernum == 2 && orientation == 1) {
            player2LightRight->Bind(0);
        }
        else {
            player2LightLeft->Bind(0);
        }
        break;
    case AttackH:
        if (playernum == 1 && orientation == 1) {
            player1HeavyRight->Bind(0);
        }
        else if (playernum == 1 && orientation == -1) {
            player1HeavyLeft->Bind(0);
        }
        else if (playernum == 2 && orientation == 1) {
            player2HeavyRight->Bind(0);
        }
        else {
            player2HeavyLeft->Bind(0);
        }
        break;
    default:
        break;
    }
}
