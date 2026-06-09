#include "raylib.h"
#include "raymath.h"
#include <cstdlib>   
#include <ctime> 
#include <sstream>
#include <iostream>
#include "raygui.h"
#include "game.h"

void Game::init(){

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Pong");
    gameState = Gamestate::Menu;

    std::srand(std::time(nullptr));

    // Variable Definitions.
    playerX = PLAYER_X_POSITION;
    playerY = PLAYER_Y_POSITION;
    botX = BOT_X_POSITION;
    botY = BOT_Y_POSITION;

    paddleSpeed = 8.5f;
    botPaddleSpeed = 5.5f;
    dashHeight = 30;   
    gapHeight  = 15;  
    lineWidth = 10;
    dashedLineX = WINDOW_WIDTH / 2 - lineWidth/2;

    ballRadius = 13.0f;
    ballSpeed = BALL_SPEED;
    ballDirX = -1; 
    ballDirY = 1; 
    ballXpos = WINDOW_WIDTH / 2;
    ballYpos = WINDOW_HEIGHT / 2;

    isGameSelection2players;
    isInputSelectionMouse;
    inputCooldown = 0;
    topBorderHit = false;
    bottomBorderHit = false;
    botTopBorderHit = false;
    botBottomBorderHit = false;
    playerWonRound = false;
    botWonRound = false;
    playerScore = 0;
    botScore = 0;

    roundOverTime = 0; 
    roundTimerActive = false;
    scoreUpdated = false;
    playerPlusScoreUpdate = false;
    botPlusScoreUpdate = false;
    playerWonGame = false;
    botWonGame = false;

    was2PlayerHowToPlayDisplayed = false;
    wasAgainstABotHowToPlayDisplayed = false;

    infoText = MeasureText("How To Play:", MENU_TEXT_SIZE);
    infoTextCentered = WINDOW_WIDTH/2 - infoText/2;


    // Measuring Texts For 'How To Play' For 2 Players.
    howToPlayTextBase = MeasureText("Player Yellow Plays With W And S Keys.",
                HOWTOPLAY_TEXT_SIZE);
    howToPlayTextCentered = WINDOW_WIDTH/2 - howToPlayTextBase/2;
    howToPlayTextPart1 = howToPlayTextCentered + 
                MeasureText("Player ", HOWTOPLAY_TEXT_SIZE);
    howToPlayTextPart2 = howToPlayTextCentered + 
                MeasureText("Player Yellow ", HOWTOPLAY_TEXT_SIZE);
    howToPlayTextPart3 = howToPlayTextCentered + 
                MeasureText("Player Yellow Plays With ", HOWTOPLAY_TEXT_SIZE);
    howToPlayTextPart4 = howToPlayTextCentered + 
                MeasureText("Player Yellow Plays With W ", HOWTOPLAY_TEXT_SIZE);
    howToPlayTextPart5 = howToPlayTextCentered + 
                MeasureText("Player Yellow Plays With W And ", HOWTOPLAY_TEXT_SIZE);
    howToPlayTextPart6 = howToPlayTextCentered + 
                MeasureText("Player Yellow Plays With W And S ", HOWTOPLAY_TEXT_SIZE);

    howToPlayTextNextLineBase = MeasureText("Player Red Plays With UP",
                HOWTOPLAY_TEXT_SIZE);
    howToPlayTextNextLineCentered = WINDOW_WIDTH/2 - howToPlayTextNextLineBase/2;
    howToPlayTextNextLinePart1 = howToPlayTextNextLineCentered + 
                MeasureText("Player ", HOWTOPLAY_TEXT_SIZE);
    howToPlayTextNextLinePart2 = howToPlayTextNextLineCentered + 
                MeasureText("Player Red ", HOWTOPLAY_TEXT_SIZE);
    howToPlayTextNextLinePart3 = howToPlayTextNextLineCentered + 
                MeasureText("Player Red Plays With ", HOWTOPLAY_TEXT_SIZE);

    howToPlayTextNextLine2Base = MeasureText("And DOWN Arrow Keys.",
                HOWTOPLAY_TEXT_SIZE);
    howToPlayTextNextLine2Centered = WINDOW_WIDTH/2 - howToPlayTextNextLine2Base/2;
    howToPlayTextNextLine2Part1 = howToPlayTextNextLine2Centered +
                MeasureText("And ", HOWTOPLAY_TEXT_SIZE);
    howToPlayTextNextLine2Part2 = howToPlayTextNextLine2Centered + 
                MeasureText("And DOWN ", HOWTOPLAY_TEXT_SIZE);


    // Measuring Texts For 'How To Play' For Against A Bot.
    botHowToPlayTextBase = MeasureText("Play By Moving Your MOUSE",
                HOWTOPLAY_TEXT_SIZE);
    botHowToPlayTextCentered = WINDOW_WIDTH/2 - botHowToPlayTextBase/2;
    botHowToPlayTextPart1 = botHowToPlayTextCentered + 
                MeasureText("Play By Moving Your ", HOWTOPLAY_TEXT_SIZE);

    botHowToPlayTextNextLineBase = MeasureText("Up And Down, Or",
                HOWTOPLAY_TEXT_SIZE);
    botHowToPlayTextNextLineCentered = WINDOW_WIDTH/2 - botHowToPlayTextNextLineBase/2;

    botHowToPlayTextNextLine2Base = MeasureText("By Pressing UP And DOWN Arrow Keys.",
                HOWTOPLAY_TEXT_SIZE);
    botHowToPlayTextNextLine2Centered = WINDOW_WIDTH/2 - botHowToPlayTextNextLine2Base/2;
    botHowToPlayTextNextLine2Part1 = botHowToPlayTextNextLine2Centered + 
                MeasureText("By Pressing ", HOWTOPLAY_TEXT_SIZE);
    botHowToPlayTextNextLine2Part2 = botHowToPlayTextNextLine2Centered + 
                MeasureText("By Pressing UP ", HOWTOPLAY_TEXT_SIZE);
    botHowToPlayTextNextLine2Part3 = botHowToPlayTextNextLine2Centered + 
                MeasureText("By Pressing UP And ", HOWTOPLAY_TEXT_SIZE);
    botHowToPlayTextNextLine2Part4 = botHowToPlayTextNextLine2Centered + 
                MeasureText("By Pressing UP And DOWN ", HOWTOPLAY_TEXT_SIZE);

    
    // Measuring Other Texts (Main Menu, Input Selection, Scores...).
    nameText = MeasureText("Pong - Made With C++ & Raylib", MENU_TEXT_SIZE);
    nameTextCentered = WINDOW_WIDTH/2 - nameText/2;
    selectionText = MeasureText("Select How You Would Like To Play:", MENU_TEXT_SIZE);
    selectionTextCentered = WINDOW_WIDTH/2 - selectionText/2;

    playerPlusScoreText = MeasureText("+1", PLUS_SCORE_TEXT_SIZE);
    botPlusScoreText = MeasureText("+1", PLUS_SCORE_TEXT_SIZE);

    playerWonText = MeasureText("RED WINS!", WON_TEXT_SIZE);
    playerWonTextCentered = WON_TEXT_WIDTH - playerWonText/2;
    botWonText = MeasureText("YELLOW WINS!", WON_TEXT_SIZE);
    botWonTextCentered = WON_TEXT_WIDTH - botWonText/2;

    // Colors.
    red = {255, 20, 75, 255};
    yellow = {255, 230, 25, 255};
    purple = {30, 0, 45, 255};
    orange = {255, 125, 30, 255};
    gray = {125, 125, 125, 120};
}

void Game::startBall(){
    float randomArrY[] = {-0.4, 0.4};
    float randomArrX[] = {-1, 1};
    int size = sizeof(randomArrY) / sizeof(randomArrY[0]);
    int indexY = std::rand() % 2;
    int indexX = std::rand() % 2;

    ballDirY = randomArrY[indexY];
    ballDirX = randomArrX[indexX];
    if(botWonRound) ballDirX = 1;
    else if(playerWonRound) ballDirX = -1;
}

void Game::update(){  

    if (inputCooldown > 0) inputCooldown--;
    
    if(gameState == Gamestate::Menu && inputCooldown == 0){

        if(GuiButton({BUTTON1_X_POS, BUTTONS_Y_POS,
             BUTTONS_WIDTH, BUTTONS_HEIGHT}, "Against A Bot")){
                isGameSelection2players = false;
                gameState = Gamestate::InputSelection;
                inputCooldown = 30;
        }
        if(GuiButton({BUTTON2_X_POS, BUTTONS_Y_POS,
             BUTTONS_WIDTH, BUTTONS_HEIGHT}, "2 Players")){
                isGameSelection2players = true;
                isInputSelectionMouse = false;
                if(!was2PlayerHowToPlayDisplayed){
                    gameState = Gamestate::HowToPlay;
                    was2PlayerHowToPlayDisplayed = true;
                }
                else gameState = Gamestate::Playing;
                inputCooldown = 30;
        }
    }

    if(gameState == Gamestate::InputSelection && inputCooldown == 0){

        if(GuiButton({BUTTON1_X_POS, BUTTONS_Y_POS,
             BUTTONS_WIDTH, BUTTONS_HEIGHT}, "Keyboard")){
                isInputSelectionMouse = false;
                if(!wasAgainstABotHowToPlayDisplayed){
                    gameState = Gamestate::HowToPlay;
                    wasAgainstABotHowToPlayDisplayed = true;
                }
                else gameState = Gamestate::Playing;
                inputCooldown = 30;
        }
        if(GuiButton({BUTTON2_X_POS, BUTTONS_Y_POS,
             BUTTONS_WIDTH, BUTTONS_HEIGHT}, "Mouse")){
                isInputSelectionMouse = true;
                if(!wasAgainstABotHowToPlayDisplayed){
                    gameState = Gamestate::HowToPlay;
                    wasAgainstABotHowToPlayDisplayed = true;
                }
                else gameState = Gamestate::Playing;
                inputCooldown = 30;
        }
    }

    if(gameState == Gamestate::HowToPlay){
        if(GuiButton({BUTTON_HOWTOPLAY_X_POS, BUTTON_HOWTOPLAY_Y_POS,
             BUTTON_HOWTOPLAY_WIDTH, BUTTON_HOWTOPLAY_HEIGHT}, "Play")){
                gameState = Gamestate::Playing;
        }
    }

    if(gameState == Gamestate::Playing || gameState == Gamestate::RoundOver){

        if(!isInputSelectionMouse){
            if(IsKeyDown(KEY_DOWN) && !bottomBorderHit){
                playerY += paddleSpeed;
                topBorderHit = false;
            }

            if(IsKeyDown(KEY_UP) && !topBorderHit){
                playerY -= paddleSpeed;
                bottomBorderHit = false;
            }

            if(isGameSelection2players){

                if(IsKeyDown(KEY_S) && !botBottomBorderHit){
                    botY += paddleSpeed;
                    botTopBorderHit = false;
                }

                if(IsKeyDown(KEY_W) && !botTopBorderHit){
                    botY -= paddleSpeed;
                    botBottomBorderHit = false;
                }
            }
        }
        
        if(isInputSelectionMouse){
            int mouseY = GetMouseY();
            Vector2 mouseDelta = GetMouseDelta();

            if(mouseDelta.y > 0 && !bottomBorderHit){
                playerY = mouseY - PLAYER_HEIGHT/2;
                topBorderHit = false;
            }
            
            else if(mouseDelta.y < 0 && !topBorderHit){
                playerY = mouseY - PLAYER_HEIGHT/2;
                bottomBorderHit = false;
            }
            SetMousePosition(WINDOW_WIDTH/2, playerY + PLAYER_HEIGHT/2); 
        }

        HideCursor();

        float length = sqrt(ballDirX*ballDirX + ballDirY*ballDirY);
        float normX = ballDirX / length;
        float normY = ballDirY / length;

        ballXpos += normX * ballSpeed;
        ballYpos += normY * ballSpeed;

        if(ballYpos + ballRadius >= CONTAINER_HEIGHT_END){
            ballYpos = CONTAINER_HEIGHT_END - ballRadius;
            ballDirY *= -1;
        } 
        else if(ballYpos - ballRadius <= CONTAINER_HEIGHT_START){
            ballYpos = CONTAINER_HEIGHT_START + ballRadius;
            ballDirY *= -1;
        }

        float ballLeft = ballXpos - ballRadius;
        float ballRight = ballXpos + ballRadius;
        float ballTop = ballYpos - ballRadius;
        float ballBottom = ballYpos + ballRadius;

        float paddleLeft = playerX;
        float paddleRight = playerX + PLAYER_WIDTH;
        float paddleTop = playerY;
        float paddleBottom = playerY + PLAYER_HEIGHT;

        float margin = ballSpeed + BALL_CONTACT_MARGIN;

        if(ballDirX > 0 && 
            ballRight + margin >= paddleLeft &&
            ballLeft - margin <= paddleRight &&
            ballBottom + margin >= paddleTop && 
            ballTop - margin <= paddleBottom){
            
            float overlapLeft = ballRight - paddleLeft;
            float overlapTop = ballBottom - paddleTop;
            float overlapBottom = paddleBottom - ballTop;
            
            if(overlapLeft <= overlapTop && overlapLeft <= overlapBottom){
                float paddleCenter = playerY + PLAYER_HEIGHT / 2.0f;
                float ballOffset = ballYpos - paddleCenter;
                float normalized = ballOffset / (PLAYER_HEIGHT / 2.0f);
                normalized = Clamp(normalized, -1.0f, 1.0f);

                float maxBounceAngle = 60 * DEG2RAD;
                float bounceAngle = normalized * maxBounceAngle;

                ballDirX *= -1;
                ballDirY = sin(bounceAngle);

                ballXpos = paddleLeft - ballRadius;
            }
            else if(overlapTop <= overlapBottom) {
                ballDirY = -fabs(ballDirY);
                ballYpos = paddleTop - ballRadius - BALL_CONTACT_MARGIN;
            }
            else {
                ballDirY = fabs(ballDirY);
                ballYpos = paddleBottom + ballRadius + BALL_CONTACT_MARGIN;
            }
        }

        if(playerY + PLAYER_HEIGHT >= CONTAINER_HEIGHT_END){
            bottomBorderHit = true;
            playerY = CONTAINER_HEIGHT_END - PLAYER_HEIGHT;
        }
        if(playerY <= CONTAINER_HEIGHT_START){
            topBorderHit = true;
            playerY = CONTAINER_HEIGHT_START;
        }

        
        float botPaddleLeft = botX;
        float botPaddleRight = botX + PLAYER_WIDTH;
        float botPaddleTop = botY;
        float botPaddleBottom = botY + PLAYER_HEIGHT;

        if(ballDirX < 0 && 
            ballRight + margin >= botPaddleLeft &&
            ballLeft - margin <= botPaddleRight &&
            ballBottom + margin >= botPaddleTop && 
            ballTop - margin <= botPaddleBottom){
            float botOverlapRight = botPaddleRight - ballLeft;
            float botOverlapTop = ballBottom - botPaddleTop;
            float botOverlapBottom = botPaddleBottom - ballTop;
            if(botOverlapRight <= botOverlapTop && botOverlapRight <= botOverlapBottom){
                float botPaddleCenter = botY + PLAYER_HEIGHT / 2.0f;
                float botBallOffset = ballYpos - botPaddleCenter;
                float botNormalized = botBallOffset / (PLAYER_HEIGHT / 2.0f);
                botNormalized = Clamp(botNormalized, -1.0f, 1.0f);
                float maxBounceAngle = 60 * DEG2RAD;
                float botBounceAngle = botNormalized * maxBounceAngle;
                ballDirX *= -1;
                ballDirY = sin(botBounceAngle);
                ballXpos = botPaddleRight + ballRadius;
            }
            else if(botOverlapTop <= botOverlapBottom){
                ballDirY = -fabs(ballDirY);
                ballYpos = botPaddleTop - ballRadius;
            }
            else{
                ballDirY = fabs(ballDirY);
                ballYpos = botPaddleBottom + ballRadius;
            }
        }

        if(!isGameSelection2players){

            int botCenter = botY + PLAYER_HEIGHT/2;
            int botBottomMargin = botCenter + 30;
            int botTopMargin = botCenter - 30;
            if(ballDirX < 0 && botBottomMargin < ballYpos && !botBottomBorderHit){
                botY += botPaddleSpeed;
                botTopBorderHit = false;
            }
            else if(ballDirX < 0 && botTopMargin > ballYpos && !botTopBorderHit){
                botY -= botPaddleSpeed;
                botBottomBorderHit = false;
            }
        }

        if(botY + PLAYER_HEIGHT >= CONTAINER_HEIGHT_END){
            botY = CONTAINER_HEIGHT_END - PLAYER_HEIGHT;
            botBottomBorderHit = true;
        }
        else if(botY <= CONTAINER_HEIGHT_START){
            botY = CONTAINER_HEIGHT_START;
            botTopBorderHit = true;
        }

        if(ballXpos - ballRadius < CONTAINER_WIDTH_START){
            playerWonRound = true;
            gameState = Gamestate::RoundOver;
        }

        else if(ballXpos + ballRadius > CONTAINER_WIDTH_END){
            botWonRound = true;
            gameState = Gamestate::RoundOver;
        }

        ballSpeed = ballSpeed + 0.0007;
    }

    if(gameState == Gamestate::RoundOver){
        
        if(!roundTimerActive){
            roundOverTime = GetTime(); 
            roundTimerActive = true;
        }
        if(playerWonRound && !scoreUpdated){
            playerScore++;
            playerPlusScoreUpdate = true;
            scoreUpdated = true;
        }

        if(botWonRound && !scoreUpdated){
            botScore++;
            botPlusScoreUpdate = true;
            scoreUpdated = true;
        }

        if(GetTime() - roundOverTime >= 1.25){
            if(playerScore != MAX_SCORE && botScore != MAX_SCORE){
                reset();
            }

            else{
                gameState = Gamestate::GameOver;
                if(playerScore == MAX_SCORE){
                    playerWonGame = true;
                }
                else if(botScore == MAX_SCORE){
                    botWonGame = true;
                }
            }

            playerPlusScoreUpdate = false;
            botPlusScoreUpdate = false;
        }
    }

    if(gameState == Gamestate::GameOver){
        if(GuiButton({BUTTON_GAMEOVER_X_POS, BUTTON_GAMEOVER_Y_POS,
             BUTTON_GAMEOVER_WIDTH, BUTTON_GAMEOVER_HEIGHT}, "Main Menu")){
                restart();
        }
    }
}

void Game::draw(){
    
    BeginDrawing();
    ClearBackground(purple);

    if(gameState == Gamestate::Menu){

        DrawText("Pong - Made With C++ & Raylib", nameTextCentered,
             MENU_TEXT_HEIGHT, MENU_TEXT_SIZE, RAYWHITE);
        
        // Button Costumization.
        GuiSetStyle(BUTTON, BORDER_WIDTH, BUTTON_BORDER_WIDTH);
        GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, ColorToInt(red));
        GuiSetStyle(BUTTON, BORDER_COLOR_FOCUSED, ColorToInt(RAYWHITE));
        GuiSetStyle(BUTTON, BORDER_COLOR_PRESSED, ColorToInt(red));
        GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(yellow));
        GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, ColorToInt(yellow));
        GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, ColorToInt(yellow));
        GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(red));
        GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED, ColorToInt(red));
        GuiSetStyle(BUTTON, TEXT_COLOR_PRESSED, ColorToInt(red));
        GuiSetStyle(DEFAULT, TEXT_SIZE, BUTTON1_TEXT_SIZE);
        GuiButton({BUTTON1_X_POS, BUTTONS_Y_POS,
             BUTTONS_WIDTH, BUTTONS_HEIGHT}, "Against A Bot");

        GuiSetStyle(BUTTON, BORDER_WIDTH, BUTTON_BORDER_WIDTH);
        GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, ColorToInt(yellow));
        GuiSetStyle(BUTTON, BORDER_COLOR_PRESSED, ColorToInt(yellow));
        GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(red));
        GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, ColorToInt(red));
        GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, ColorToInt(red));
        GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(yellow));
        GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED, ColorToInt(yellow));
        GuiSetStyle(BUTTON, TEXT_COLOR_PRESSED, ColorToInt(yellow));
        GuiSetStyle(DEFAULT, TEXT_SIZE, BUTTON1_TEXT_SIZE);
        GuiButton({BUTTON2_X_POS, BUTTONS_Y_POS,
             BUTTONS_WIDTH, BUTTONS_HEIGHT}, "2 Players");
    }

    if(gameState == Gamestate::InputSelection){

        DrawText("Select How You Would Like To Play:", selectionTextCentered,
             MENU_TEXT_HEIGHT, MENU_TEXT_SIZE, RAYWHITE);

        // Button Costumization.
        GuiSetStyle(BUTTON, BORDER_WIDTH, BUTTON_BORDER_WIDTH);
        GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, ColorToInt(red));
        GuiSetStyle(BUTTON, BORDER_COLOR_PRESSED, ColorToInt(red));
        GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(purple));
        GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, ColorToInt(purple));
        GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, ColorToInt(purple));
        GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(red));
        GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED, ColorToInt(red));
        GuiSetStyle(BUTTON, TEXT_COLOR_PRESSED, ColorToInt(red));
        GuiSetStyle(DEFAULT, TEXT_SIZE, BUTTON2_TEXT_SIZE);
        GuiButton({BUTTON1_X_POS, BUTTONS_Y_POS,
             BUTTONS_WIDTH, BUTTONS_HEIGHT}, "Keyboard");

        GuiSetStyle(BUTTON, BORDER_WIDTH, BUTTON_BORDER_WIDTH);
        GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, ColorToInt(yellow));
        GuiSetStyle(BUTTON, BORDER_COLOR_PRESSED, ColorToInt(yellow));
        GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(yellow));
        GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED, ColorToInt(yellow));
        GuiSetStyle(BUTTON, TEXT_COLOR_PRESSED, ColorToInt(yellow));
        GuiSetStyle(DEFAULT, TEXT_SIZE, BUTTON2_TEXT_SIZE);
        GuiButton({BUTTON2_X_POS, BUTTONS_Y_POS,
             BUTTONS_WIDTH, BUTTONS_HEIGHT}, "Mouse");
    }

    if(gameState == Gamestate::HowToPlay){

        DrawText("How To Play:", infoTextCentered,
            MENU_TEXT_HEIGHT, MENU_TEXT_SIZE, orange);

        if(isGameSelection2players){

            // Setting Each Color Appropriately.
            DrawText("Player ", 
                howToPlayTextCentered,
                HOWTOPLAY1_TEXT_HEIGHT, HOWTOPLAY_TEXT_SIZE, RAYWHITE);
            DrawText("Yellow ", howToPlayTextPart1,
                HOWTOPLAY1_TEXT_HEIGHT, HOWTOPLAY_TEXT_SIZE, yellow);
            DrawText("Plays With ", howToPlayTextPart2,
                HOWTOPLAY1_TEXT_HEIGHT, HOWTOPLAY_TEXT_SIZE, RAYWHITE);
            DrawText("W ", howToPlayTextPart3,
                HOWTOPLAY1_TEXT_HEIGHT, HOWTOPLAY_TEXT_SIZE, yellow);
            DrawText("And ", howToPlayTextPart4,
                HOWTOPLAY1_TEXT_HEIGHT, HOWTOPLAY_TEXT_SIZE, RAYWHITE);
            DrawText("S ", howToPlayTextPart5,
                HOWTOPLAY1_TEXT_HEIGHT, HOWTOPLAY_TEXT_SIZE, yellow);
            DrawText("Keys.", howToPlayTextPart6,
                HOWTOPLAY1_TEXT_HEIGHT, HOWTOPLAY_TEXT_SIZE, RAYWHITE);


            // Setting Each Color Appropriately.
            DrawText("Player ", 
                howToPlayTextNextLineCentered,
                HOWTOPLAY2_TEXT_HEIGHT, HOWTOPLAY_TEXT_SIZE, RAYWHITE);
            DrawText("Red ", howToPlayTextNextLinePart1,
                HOWTOPLAY2_TEXT_HEIGHT, HOWTOPLAY_TEXT_SIZE, red);
            DrawText("Plays With ", howToPlayTextNextLinePart2,
                HOWTOPLAY2_TEXT_HEIGHT, HOWTOPLAY_TEXT_SIZE, RAYWHITE);
            DrawText("UP", howToPlayTextNextLinePart3,
                HOWTOPLAY2_TEXT_HEIGHT, HOWTOPLAY_TEXT_SIZE, red);


            // Setting Each Color Appropriately.
            DrawText("And ", 
                howToPlayTextNextLine2Centered,
                HOWTOPLAY3_TEXT_HEIGHT, HOWTOPLAY_TEXT_SIZE, RAYWHITE);
            DrawText("DOWN ", howToPlayTextNextLine2Part1,
                HOWTOPLAY3_TEXT_HEIGHT, HOWTOPLAY_TEXT_SIZE, red);
            DrawText("Arrow Keys.", howToPlayTextNextLine2Part2,
                HOWTOPLAY3_TEXT_HEIGHT, HOWTOPLAY_TEXT_SIZE, RAYWHITE);
        }

        if(!isGameSelection2players){
            
            // Setting Each Color Appropriately.
            DrawText("Play By Moving Your ", 
                botHowToPlayTextCentered,
                HOWTOPLAY1_TEXT_HEIGHT, HOWTOPLAY_TEXT_SIZE, RAYWHITE);
            DrawText("MOUSE ", botHowToPlayTextPart1,
                HOWTOPLAY1_TEXT_HEIGHT, HOWTOPLAY_TEXT_SIZE, red);


            // Setting Each Color Appropriately.
            DrawText("Up And Down, Or", 
                botHowToPlayTextNextLineCentered,
                HOWTOPLAY2_TEXT_HEIGHT_FOR_BOT, HOWTOPLAY_TEXT_SIZE, RAYWHITE);


            // Setting Each Color Appropriately.
            DrawText("By Pressing ", 
                botHowToPlayTextNextLine2Centered,
                HOWTOPLAY3_TEXT_HEIGHT, HOWTOPLAY_TEXT_SIZE, RAYWHITE);
            DrawText("UP ", botHowToPlayTextNextLine2Part1,
                HOWTOPLAY3_TEXT_HEIGHT, HOWTOPLAY_TEXT_SIZE, red);
            DrawText("And ", botHowToPlayTextNextLine2Part2,
                HOWTOPLAY3_TEXT_HEIGHT, HOWTOPLAY_TEXT_SIZE, RAYWHITE);
            DrawText("DOWN ", botHowToPlayTextNextLine2Part3,
                HOWTOPLAY3_TEXT_HEIGHT, HOWTOPLAY_TEXT_SIZE, red);
            DrawText("Arrow Keys.", botHowToPlayTextNextLine2Part4,
                HOWTOPLAY3_TEXT_HEIGHT, HOWTOPLAY_TEXT_SIZE, RAYWHITE);
        }
        // Button Costumization.
        GuiSetStyle(BUTTON, BORDER_WIDTH, BUTTON_BORDER_WIDTH);
        GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, ColorToInt(orange));
        GuiSetStyle(BUTTON, BORDER_COLOR_PRESSED, ColorToInt(orange));
        GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(purple));
        GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, ColorToInt(purple));
        GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, ColorToInt(purple));
        GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(orange));
        GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED, ColorToInt(orange));
        GuiSetStyle(BUTTON, TEXT_COLOR_PRESSED, ColorToInt(orange));
        GuiSetStyle(DEFAULT, TEXT_SIZE, BUTTON_HOWTOPLAY_TEXT_SIZE);
        GuiButton({BUTTON_HOWTOPLAY_X_POS, BUTTON_HOWTOPLAY_Y_POS,
             BUTTON_HOWTOPLAY_WIDTH, BUTTON_HOWTOPLAY_HEIGHT}, "Play");
        
    }

    if(gameState == Gamestate::Playing || gameState == Gamestate::RoundOver || 
        gameState == Gamestate::GameOver){

        std::ostringstream botOss;
        botOss << botScore;
        std::string botScoreString = botOss.str();
        
        int botScoreText = MeasureText(botScoreString.c_str(), SCORE_TEXT_SIZE);
        DrawText(botScoreString.c_str(), BOT_SCORE_TEXT_WIDTH, 
            SCORE_TEXT_HEIGHT, SCORE_TEXT_SIZE, RAYWHITE);

        std::ostringstream playerOss;
        playerOss << playerScore;
        std::string playerScoreString = playerOss.str();
        
        int playerScoreText = MeasureText(playerScoreString.c_str(), SCORE_TEXT_SIZE);
        DrawText(playerScoreString.c_str(), PLAYER_SCORE_TEXT_WIDTH - playerScoreText, 
            SCORE_TEXT_HEIGHT, SCORE_TEXT_SIZE, RAYWHITE);


        DrawRectangle(playerX, playerY, 
            PLAYER_WIDTH, PLAYER_HEIGHT, red);
        
        for(int y = 0; y < WINDOW_HEIGHT; y += dashHeight + gapHeight) {
            DrawRectangle(dashedLineX, y, lineWidth, dashHeight, gray);
        }

        DrawCircle(ballXpos, ballYpos,
            ballRadius, orange);         
    
        DrawRectangle(botX, botY, 
        PLAYER_WIDTH, PLAYER_HEIGHT, yellow);
        
    }

    if(gameState == Gamestate::RoundOver){

        if(playerPlusScoreUpdate){
            DrawText("+1", PLAYER_SCORE_PLUS_TEXT_WIDTH - playerPlusScoreText, 
                PLUS_SCORE_TEXT_HEIGHT, PLUS_SCORE_TEXT_SIZE, RAYWHITE);
        }

        else if(botPlusScoreUpdate){
            DrawText("+1", BOT_SCORE_PLUS_TEXT_WIDTH, 
                PLUS_SCORE_TEXT_HEIGHT, PLUS_SCORE_TEXT_SIZE, RAYWHITE);
        }
    }

    if(gameState == Gamestate::GameOver){

        ShowCursor();

        bool showText = ((int)(GetTime() * 4) % 4) != 0;

        if(showText){
            if(playerWonGame){
                DrawText("RED WINS!", playerWonTextCentered,
                    WON_TEXT_HEIGHT, WON_TEXT_SIZE, red);
            }
            else if(botWonGame){
                DrawText("YELLOW WINS!", botWonTextCentered, 
                    WON_TEXT_HEIGHT, WON_TEXT_SIZE, yellow);
            }
        }
        // Button Costumization.
        GuiSetStyle(BUTTON, BORDER_WIDTH, BUTTON_BORDER_WIDTH);
        GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, ColorToInt(orange));
        GuiSetStyle(BUTTON, BORDER_COLOR_PRESSED, ColorToInt(orange));
        GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(purple));
        GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, ColorToInt(purple));
        GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, ColorToInt(purple));
        GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(orange));
        GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED, ColorToInt(orange));
        GuiSetStyle(BUTTON, TEXT_COLOR_PRESSED, ColorToInt(orange));
        GuiSetStyle(DEFAULT, TEXT_SIZE, BUTTON_GAMEOVER_TEXT_SIZE);
        GuiButton({BUTTON_GAMEOVER_X_POS, BUTTON_GAMEOVER_Y_POS,
             BUTTON_GAMEOVER_WIDTH, BUTTON_GAMEOVER_HEIGHT}, "Main Menu");
    }

    DrawRectangleLinesEx({0, 0, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT}, 
        CONTAINER_BORDER_WIDTH, RAYWHITE);    

    EndDrawing();
}

void Game::reset(){

    playerY = PLAYER_Y_POSITION;
    botY = BOT_Y_POSITION;
    ballXpos = WINDOW_WIDTH/2;
    ballYpos = WINDOW_HEIGHT/2;
    startBall();
    gameState = Gamestate::Playing;
    topBorderHit = false;
    bottomBorderHit = false;
    botBottomBorderHit = false;
    botTopBorderHit = false;
    scoreUpdated = false;
    ballSpeed = BALL_SPEED;
    playerWonRound = false;
    botWonRound = false;
    roundTimerActive = false;
}

void Game::restart(){
    reset();
    isInputSelectionMouse = false;
    isGameSelection2players = false;
    botWonGame = false;
    playerWonGame = false;
    gameState = Gamestate::Menu;
    botScore = 0;
    playerScore = 0;
}

void Game::clean(){
    CloseWindow();
}