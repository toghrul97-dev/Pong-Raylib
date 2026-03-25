#include <sstream>
#include <string>
#include "raylib.h"
#include "cmath"

// Preprocessors.
#define WINDOW_WIDTH 1100
#define WINDOW_HEIGHT 750

#define CONTAINER_WIDTH_START 6
#define CONTAINER_WIDTH_END (1100 - 6)
#define CONTAINER_HEIGHT_START 6
#define CONTAINER_HEIGHT_END (750 - 6)
#define CONTAINER_BORDER_WIDTH 6

#define PLAYER_WIDTH 25
#define PLAYER_HEIGHT 130
#define PLAYER_X_POSITION (WINDOW_WIDTH - 100)
#define PLAYER_Y_POSITION (WINDOW_HEIGHT/2 - PLAYER_HEIGHT/2)
#define BOT_X_POSITION (100 - PLAYER_WIDTH)
#define BOT_Y_POSITION (PLAYER_Y_POSITION)

#define BUTTONS_WIDTH 330
#define BUTTONS_HEIGHT 330
#define BUTTON1_X_POS (WINDOW_WIDTH/2 - BUTTONS_WIDTH - 45)
#define BUTTON2_X_POS (WINDOW_WIDTH/2 + 45)
#define BUTTONS_Y_POS (WINDOW_HEIGHT/2 - 75)

#define BUTTON_GAMEOVER_WIDTH 300
#define BUTTON_GAMEOVER_HEIGHT 120
#define BUTTON_GAMEOVER_X_POS (WINDOW_WIDTH/2 - BUTTON_GAMEOVER_WIDTH/2)
#define BUTTON_GAMEOVER_Y_POS (WINDOW_HEIGHT - 180)
#define BUTTON_GAMEOVER_TEXT_SIZE 50

#define BUTTON_HOWTOPLAY_WIDTH 300
#define BUTTON_HOWTOPLAY_HEIGHT 120
#define BUTTON_HOWTOPLAY_X_POS (WINDOW_WIDTH/2 - BUTTON_GAMEOVER_WIDTH/2)
#define BUTTON_HOWTOPLAY_Y_POS (WINDOW_HEIGHT - 180)
#define BUTTON_HOWTOPLAY_TEXT_SIZE 50

#define MENU_TEXT_WIDTH 120
#define MENU_TEXT_HEIGHT 120
#define BUTTON_BORDER_WIDTH 6
#define BUTTON1_TEXT_SIZE 40
#define BUTTON2_TEXT_SIZE 50
#define MENU_TEXT_SIZE 45

#define HOWTOPLAY1_TEXT_HEIGHT 270
#define HOWTOPLAY2_TEXT_HEIGHT (HOWTOPLAY1_TEXT_HEIGHT + 110)
#define HOWTOPLAY2_TEXT_HEIGHT_FOR_BOT (HOWTOPLAY1_TEXT_HEIGHT + 70)
#define HOWTOPLAY3_TEXT_HEIGHT (HOWTOPLAY1_TEXT_HEIGHT + 175)
#define HOWTOPLAY_TEXT_SIZE 48

#define BOT_SCORE_TEXT_WIDTH (WINDOW_WIDTH/2 - 140)
#define PLAYER_SCORE_TEXT_WIDTH (WINDOW_WIDTH/2 + 140)
#define SCORE_TEXT_HEIGHT 70
#define SCORE_TEXT_SIZE 90

#define BOT_SCORE_PLUS_TEXT_WIDTH (WINDOW_WIDTH/2 - 140)
#define PLAYER_SCORE_PLUS_TEXT_WIDTH (WINDOW_WIDTH/2 + 140)
#define PLUS_SCORE_TEXT_HEIGHT 180
#define PLUS_SCORE_TEXT_SIZE 40

#define WON_TEXT_WIDTH (WINDOW_WIDTH/2)
#define WON_TEXT_HEIGHT 345
#define WON_TEXT_SIZE 85

#define BALL_CONTACT_MARGIN 5
#define MAX_SCORE 10

class Game{

    private:
        enum class Gamestate{
            Menu, InputSelection, HowToPlay, Playing, RoundOver, GameOver
        };
        Gamestate gameState;

        // Variable Declarations.
        int playerX;
        int playerY;
        int botX;
        int botY;

        int paddleSpeed;
        int botPaddleSpeed;
        int dashHeight;   
        int gapHeight;  
        int lineWidth;
        int dashedLineX;

        float ballRadius;
        float ballSpeed;
        float ballDirX; 
        float ballDirY; 
        int ballXpos;
        int ballYpos;

        bool isGameSelection2players;
        bool isInputSelectionMouse;
        int inputCooldown;
        bool topBorderHit;
        bool bottomBorderHit;
        bool botTopBorderHit;
        bool botBottomBorderHit;
        bool playerWonRound;
        bool botWonRound;
        int playerScore;
        int botScore;

        double roundOverTime; 
        bool roundTimerActive;
        bool scoreUpdated;
        bool playerPlusScoreUpdate;
        bool botPlusScoreUpdate;
        bool playerWonGame;
        bool botWonGame;

        bool was2PlayerHowToPlayDisplayed;
        bool wasAgainstABotHowToPlayDisplayed;
        
        int infoText;
        int infoTextCentered;


        int howToPlayTextBase;
        int howToPlayTextCentered;
        int howToPlayTextPart1;
        int howToPlayTextPart2;
        int howToPlayTextPart3;
        int howToPlayTextPart4;
        int howToPlayTextPart5;
        int howToPlayTextPart6;

        int howToPlayTextNextLineBase;
        int howToPlayTextNextLineCentered;
        int howToPlayTextNextLinePart1;
        int howToPlayTextNextLinePart2;
        int howToPlayTextNextLinePart3;

        int howToPlayTextNextLine2Base;
        int howToPlayTextNextLine2Centered;
        int howToPlayTextNextLine2Part1;
        int howToPlayTextNextLine2Part2;


        int botHowToPlayTextBase;
        int botHowToPlayTextCentered;
        int botHowToPlayTextPart1;

        int botHowToPlayTextNextLineBase;
        int botHowToPlayTextNextLineCentered;

        int botHowToPlayTextNextLine2Base;
        int botHowToPlayTextNextLine2Centered;
        int botHowToPlayTextNextLine2Part1;
        int botHowToPlayTextNextLine2Part2;
        int botHowToPlayTextNextLine2Part3;
        int botHowToPlayTextNextLine2Part4;


        int nameText;
        int nameTextCentered;
        int selectionText;
        int selectionTextCentered;

        int playerPlusScoreText;
        int botPlusScoreText;

        int playerWonText;
        int playerWonTextCentered;
        int botWonText;
        int botWonTextCentered;

        Color red;
        Color yellow; 
        Color purple;
        Color orange; 
        Color gray;

    public:
        // Function Declarations.
        void init();
        void update();
        void draw();
        void clean();
        void startBall();
        void reset();
        void restart();
};