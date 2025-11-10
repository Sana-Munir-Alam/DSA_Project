// #include "raylib.h"
// #include "GameLogic.h"
// #include <vector>
// #include <string>
// #include <algorithm>
// #include <cstring>

// using namespace std;

// // Screen states
// enum ScreenState {
//     TITLE_SCREEN,
//     INSTRUCTIONS_SCREEN,
//     SELECT_PLAYERS_SCREEN,
//     NAME_ENTRY_SCREEN,
//     GAME_PLAY_SCREEN,
//     GAME_OVER_SCREEN,
//     LEADERBOARD_SCREEN,
//     BST_VIEW_SCREEN,
//     BST_SEARCH_SCREEN
// };

// // Colors - Updated for better consistency
// const Color BACKGROUND_COLOR = {245, 245, 220, 255}; // Beige
// const Color BUTTON_ACTIVE = {220, 20, 60, 255}; // Red
// const Color BUTTON_INACTIVE = {128, 128, 128, 255}; // Grey
// const Color TEXT_COLOR = {40, 40, 40, 255}; // Dark gray - Bold and readable
// const Color HEADER_COLOR = {101, 67, 33, 255}; // Brown
// const Color PLAYER_COLORS[] = {
//     {255, 0, 0, 255},     // Red
//     {0, 0, 255, 255},     // Blue
//     {0, 255, 0, 255},     // Green
//     {255, 255, 0, 255}    // Yellow
// };
// const Color ACTIVE_PLAYER_GLOW = {255, 165, 0, 255}; // Orange
// const Color TABLE_HEADER_BG = {200, 200, 180, 255};
// const Color TABLE_ROW_BG = {230, 230, 210, 255};

// // Game manager
// GameManager gameManager;
// ScreenState currentScreen = TITLE_SCREEN;

// // Game state variables
// int selectedPlayerCount = 0;
// bool vsBot = false;
// vector<string> playerNames(4);
// int currentInputField = 0;
// bool inputFieldsActive[4] = {false};

// // Particle for confetti
// struct Particle {
//     Vector2 position;
//     Vector2 velocity;
//     Color color;
//     float size;
//     float life;
// };

// vector<Particle> particles;

// // Function declarations
// void InitGame();
// void UpdateGame();
// void DrawGame();
// void DrawTitleScreen();
// void DrawInstructionsScreen();
// void DrawSelectPlayersScreen();
// void DrawNameEntryScreen();
// void DrawGamePlayScreen();
// void DrawGameOverScreen();
// void DrawLeaderboardScreen();
// void DrawBSTViewScreen();
// void DrawBSTSearchScreen();
// void CreateConfetti();
// void UpdateConfetti();

// int main() {
//     const int screenWidth = 1800;
//     const int screenHeight = 1100;
    
//     InitWindow(screenWidth, screenHeight, "Matching Tile Game");
//     SetTargetFPS(60);
    
//     InitGame();
    
//     while (!WindowShouldClose()) {
//         UpdateGame();
//         DrawGame();
//     }
    
//     CloseWindow();
//     return 0;
// }

// void InitGame() {
//     srand(time(NULL));
//     currentScreen = TITLE_SCREEN;
// }

// void UpdateGame() {
//     gameManager.update(GetFrameTime());
    
//     if (currentScreen == GAME_OVER_SCREEN) {
//         static double lastConfettiTime = 0;
//         double currentTime = GetTime();
        
//         UpdateConfetti();
//         if (currentTime - lastConfettiTime > 0.1) {
//             CreateConfetti();
//             lastConfettiTime = currentTime;
//         }
//     }
// }

// void DrawGame() {
//     BeginDrawing();
//     ClearBackground(BACKGROUND_COLOR);
    
//     switch (currentScreen) {
//         case TITLE_SCREEN: DrawTitleScreen(); break;
//         case INSTRUCTIONS_SCREEN: DrawInstructionsScreen(); break;
//         case SELECT_PLAYERS_SCREEN: DrawSelectPlayersScreen(); break;
//         case NAME_ENTRY_SCREEN: DrawNameEntryScreen(); break;
//         case GAME_PLAY_SCREEN: DrawGamePlayScreen(); break;
//         case GAME_OVER_SCREEN: DrawGameOverScreen(); break;
//         case LEADERBOARD_SCREEN: DrawLeaderboardScreen(); break;
//         case BST_VIEW_SCREEN: DrawBSTViewScreen(); break;
//         case BST_SEARCH_SCREEN: DrawBSTSearchScreen(); break;
//     }
    
//     EndDrawing();
// }

// void DrawTitleScreen() {
//     // Game title - centered
//     DrawText("Matching Tile Game", 550, 150, 70, HEADER_COLOR);
    
//     // Buttons - centered and spaced properly
//     Rectangle instructionsBtn = {650, 350, 500, 90};
//     Rectangle newGameBtn = {650, 470, 500, 90};
//     Rectangle leaderboardBtn = {650, 590, 500, 90};
    
//     DrawRectangleRec(instructionsBtn, BUTTON_ACTIVE);
//     DrawRectangleRec(newGameBtn, BUTTON_ACTIVE);
//     DrawRectangleRec(leaderboardBtn, BUTTON_ACTIVE);
    
//     DrawText("Instructions", 760, 380, 40, WHITE);
//     DrawText("New Game", 780, 500, 40, WHITE);
//     DrawText("Leader Board", 750, 620, 40, WHITE);
    
//     if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
//         Vector2 mousePos = GetMousePosition();
//         if (CheckCollisionPointRec(mousePos, instructionsBtn)) {
//             currentScreen = INSTRUCTIONS_SCREEN;
//         } else if (CheckCollisionPointRec(mousePos, newGameBtn)) {
//             currentScreen = SELECT_PLAYERS_SCREEN;
//         } else if (CheckCollisionPointRec(mousePos, leaderboardBtn)) {
//             currentScreen = LEADERBOARD_SCREEN;
//         }
//     }
// }

// void DrawInstructionsScreen() {
//     DrawText("Instructions", 650, 80, 60, HEADER_COLOR);
    
//     int yPos = 200;
//     int lineSpacing = 55;
    
//     DrawText("Goal is to match two pair of tiles.", 150, yPos, 28, TEXT_COLOR); yPos += lineSpacing;
//     DrawText("Bonus Points when a player consecutively matches tiles.", 150, yPos, 28, TEXT_COLOR); yPos += lineSpacing;
//     DrawText("If a player mismatch a tile, the turn goes to the next player.", 150, yPos, 28, TEXT_COLOR); yPos += lineSpacing;
//     DrawText("Game runs until all tiles have been matched.", 150, yPos, 28, TEXT_COLOR); yPos += lineSpacing;
//     DrawText("At each player's turn as long as the card qty is greater than 10,", 150, yPos, 28, TEXT_COLOR); yPos += lineSpacing;
//     DrawText("the player gets 2 chances of undoing the first card they selected ONLY.", 150, yPos, 28, TEXT_COLOR); yPos += lineSpacing;
//     DrawText("When card qty decreases to 10 and below, no undo option is active.", 150, yPos, 28, TEXT_COLOR);
    
//     Rectangle backBtn = {700, 750, 400, 80};
//     DrawRectangleRec(backBtn, BUTTON_ACTIVE);
//     DrawText("Back", 860, 780, 40, WHITE);
    
//     if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
//         Vector2 mousePos = GetMousePosition();
//         if (CheckCollisionPointRec(mousePos, backBtn)) {
//             currentScreen = TITLE_SCREEN;
//         }
//     }
// }

// void DrawSelectPlayersScreen() {
//     DrawText("Select Players", 650, 120, 60, HEADER_COLOR);
    
//     Rectangle btn2 = {650, 280, 500, 80};
//     Rectangle btn3 = {650, 390, 500, 80};
//     Rectangle btn4 = {650, 500, 500, 80};
//     Rectangle btnBot = {650, 610, 500, 80};
//     Rectangle backBtn = {650, 720, 500, 80};
    
//     DrawRectangleRec(btn2, BUTTON_ACTIVE);
//     DrawRectangleRec(btn3, BUTTON_ACTIVE);
//     DrawRectangleRec(btn4, BUTTON_ACTIVE);
//     DrawRectangleRec(btnBot, BUTTON_ACTIVE);
//     DrawRectangleRec(backBtn, BUTTON_ACTIVE);
    
//     DrawText("2 Players", 810, 310, 35, WHITE);
//     DrawText("3 Players", 810, 420, 35, WHITE);
//     DrawText("4 Players", 810, 530, 35, WHITE);
//     DrawText("VS Bot", 840, 640, 35, WHITE);
//     DrawText("Back", 860, 750, 35, WHITE);
    
//     if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
//         Vector2 mousePos = GetMousePosition();
//         if (CheckCollisionPointRec(mousePos, btn2)) {
//             selectedPlayerCount = 2;
//             vsBot = false;
//             currentScreen = NAME_ENTRY_SCREEN;
//         } else if (CheckCollisionPointRec(mousePos, btn3)) {
//             selectedPlayerCount = 3;
//             vsBot = false;
//             currentScreen = NAME_ENTRY_SCREEN;
//         } else if (CheckCollisionPointRec(mousePos, btn4)) {
//             selectedPlayerCount = 4;
//             vsBot = false;
//             currentScreen = NAME_ENTRY_SCREEN;
//         } else if (CheckCollisionPointRec(mousePos, btnBot)) {
//             selectedPlayerCount = 1;
//             vsBot = true;
//             currentScreen = NAME_ENTRY_SCREEN;
//         } else if (CheckCollisionPointRec(mousePos, backBtn)) {
//             currentScreen = TITLE_SCREEN;
//         }
//     }
// }

// void DrawNameEntryScreen() {
//     DrawText("Enter Player Names", 600, 80, 60, HEADER_COLOR);
    
//     int actualPlayers = vsBot ? 1 : selectedPlayerCount;
    
//     for (int i = 0; i < actualPlayers; i++) {
//         Rectangle inputBox = {600, 220 + i * 120, 600, 70};
//         Color borderColor = inputFieldsActive[i] ? RED : GRAY;
        
//         DrawRectangleLinesEx(inputBox, 3, borderColor);
//         DrawText(TextFormat("P%d: ", i + 1), 520, 235 + i * 120, 35, PLAYER_COLORS[i]);
//         DrawText(playerNames[i].c_str(), 620, 235 + i * 120, 35, TEXT_COLOR);
        
//         if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
//             Vector2 mousePos = GetMousePosition();
//             if (CheckCollisionPointRec(mousePos, inputBox)) {
//                 inputFieldsActive[i] = true;
//                 currentInputField = i;
//             } else {
//                 inputFieldsActive[i] = false;
//             }
//         }
        
//         if (inputFieldsActive[i]) {
//             int key = GetCharPressed();
//             while (key > 0) {
//                 if ((key >= 32) && (key <= 125) && (playerNames[i].length() < 20)) {
//                     playerNames[i] += (char)key;
//                 }
//                 key = GetCharPressed();
//             }
            
//             if (IsKeyPressed(KEY_BACKSPACE) && !playerNames[i].empty()) {
//                 playerNames[i].pop_back();
//             }
//         }
//     }
    
//     bool canStart = true;
//     for (int i = 0; i < actualPlayers; i++) {
//         if (playerNames[i].empty()) {
//             canStart = false;
//             break;
//         }
//     }
    
//     Rectangle startBtn = {600, 250 + actualPlayers * 120, 300, 80};
//     Color startBtnColor = canStart ? BUTTON_ACTIVE : BUTTON_INACTIVE;
    
//     DrawRectangleRec(startBtn, startBtnColor);
//     DrawText("Start", 710, 280 + actualPlayers * 120, 35, WHITE);
    
//     Rectangle backBtn = {950, 250 + actualPlayers * 120, 300, 80};
//     DrawRectangleRec(backBtn, BUTTON_ACTIVE);
//     DrawText("Back", 1065, 280 + actualPlayers * 120, 35, WHITE);
    
//     if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
//         Vector2 mousePos = GetMousePosition();
//         if (CheckCollisionPointRec(mousePos, startBtn) && canStart) {
//             vector<string> names;
//             for (int i = 0; i < actualPlayers; i++) {
//                 names.push_back(playerNames[i]);
//             }
//             gameManager.initGame(actualPlayers, names, vsBot);
//             currentScreen = GAME_PLAY_SCREEN;
//         } else if (CheckCollisionPointRec(mousePos, backBtn)) {
//             currentScreen = SELECT_PLAYERS_SCREEN;
//         }
//     }
// }

// void DrawGamePlayScreen() {
//     vector<Player*> players = gameManager.getPlayers();
//     Player* currentPlayer = gameManager.getCurrentPlayer();
//     int totalCards = gameManager.getTotalCards();
    
//     // Draw player quadrants - adjusted positions for 1800x1000
//     for (int i = 0; i < players.size(); i++) {
//         int cornerX, cornerY;
//         switch (i) {
//             case 0: cornerX = 80; cornerY = 80; break;
//             case 1: cornerX = 1600; cornerY = 80; break;
//             case 2: cornerX = 80; cornerY = 850; break;
//             case 3: cornerX = 1600; cornerY = 850; break;
//         }
        
//         if (players[i] == currentPlayer) {
//             DrawCircleLines(cornerX + 50, cornerY + 50, 45, ACTIVE_PLAYER_GLOW);
//             DrawCircleLines(cornerX + 50, cornerY + 50, 48, ACTIVE_PLAYER_GLOW);
//         }
        
//         DrawCircle(cornerX + 50, cornerY + 50, 40, PLAYER_COLORS[i]);
//         DrawText(players[i]->name.c_str(), cornerX, cornerY + 110, 24, TEXT_COLOR);
//     }
    
//     // Draw scoreboard - centered
//     int startX = 500;
//     DrawText("Scoreboard", 780, 20, 35, HEADER_COLOR);
    
//     for (int i = 0; i < players.size(); i++) {
//         DrawText(players[i]->name.c_str(), startX + i * 280, 70, 24, PLAYER_COLORS[i]);
//     }
    
//     for (int i = 0; i < players.size(); i++) {
//         string scoreText = TextFormat("Score: %d", players[i]->score);
//         string streakText = TextFormat("Streak: %d", players[i]->streak);
//         DrawText(scoreText.c_str(), startX + i * 280, 100, 22, TEXT_COLOR);
//         DrawText(streakText.c_str(), startX + i * 280, 130, 22, TEXT_COLOR);
//     }
    
//     // Draw cards (4x5 grid) - centered
//     int cardWidth = 100;
//     int cardHeight = 140;
//     int startGridX = 500;
//     int startGridY = 250;
    
//     for (int row = 0; row < 4; row++) {
//         for (int col = 0; col < 5; col++) {
//             int index = row * 5 + col;
//             int x = startGridX + col * (cardWidth + 20);
//             int y = startGridY + row * (cardHeight + 20);
            
//             Rectangle cardRect = {(float)x, (float)y, (float)cardWidth, (float)cardHeight};
            
//             CardNode* card = gameManager.getCards().getNodeByIndex(index);
//             if (card && !card->matched) {
//                 if (card->flipped) {
//                     DrawRectangleRec(cardRect, WHITE);
//                     DrawRectangleLinesEx(cardRect, 3, BLACK);
                    
//                     if (index == gameManager.getFirstSelection() || index == gameManager.getSecondSelection()) {
//                         DrawRectangleLinesEx(cardRect, 5, RED);
//                     }
                    
//                     string valueStr = string(1, card->value);
//                     DrawText(valueStr.c_str(), x + cardWidth/2 - 15, y + cardHeight/2 - 20, 40, BLACK);
//                 } else {
//                     DrawRectangleRec(cardRect, LIGHTGRAY);
//                     DrawRectangleLinesEx(cardRect, 3, DARKGRAY);
                    
//                     DrawLine(x, y, x + cardWidth, y + cardHeight, DARKGRAY);
//                     DrawLine(x + cardWidth, y, x, y + cardHeight, DARKGRAY);
//                 }
                
//                 if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
//                     Vector2 mousePos = GetMousePosition();
//                     if (CheckCollisionPointRec(mousePos, cardRect) && !card->flipped) {
//                         gameManager.selectCard(index);
//                     }
//                 }
//             }
//         }
//     }
    
//     // Draw Undo button - centered
//     Rectangle undoBtn = {750, 850, 300, 80};
//     bool undoActive = currentPlayer->undoLeft > 0 && gameManager.getFirstSelection() != -1 && 
//                      gameManager.getSecondSelection() == -1 && totalCards > 10;
    
//     Color undoColor = undoActive ? BUTTON_ACTIVE : BUTTON_INACTIVE;
//     DrawRectangleRec(undoBtn, undoColor);
//     DrawText(TextFormat("Undo (%d)", currentPlayer->undoLeft), 820, 880, 30, WHITE);
    
//     if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && undoActive) {
//         Vector2 mousePos = GetMousePosition();
//         if (CheckCollisionPointRec(mousePos, undoBtn)) {
//             gameManager.undo();
//         }
//     }
    
//     if (gameManager.isGameOver()) {
//         currentScreen = GAME_OVER_SCREEN;
//     }
// }

// void DrawGameOverScreen() {
//     for (const Particle& particle : particles) {
//         DrawRectangle(particle.position.x, particle.position.y, particle.size, particle.size, particle.color);
//     }
    
//     DrawText("Game Over!", 650, 120, 70, HEADER_COLOR);
    
//     vector<Player*> sortedPlayers = gameManager.getSortedLeaderboard();
    
//     for (int i = 0; i < sortedPlayers.size(); i++) {
//         string rankText = TextFormat("%d. %s - Score: %d", i + 1, 
//                                          sortedPlayers[i]->name.c_str(), 
//                                          sortedPlayers[i]->score);
//         DrawText(rankText.c_str(), 600, 280 + i * 60, 35, PLAYER_COLORS[sortedPlayers[i]->colorId]);
//     }
    
//     Rectangle homeBtn = {500, 700, 350, 80};
//     Rectangle leaderboardBtn = {950, 700, 350, 80};
    
//     DrawRectangleRec(homeBtn, BUTTON_ACTIVE);
//     DrawRectangleRec(leaderboardBtn, BUTTON_ACTIVE);
    
//     DrawText("Home", 630, 730, 35, WHITE);
//     DrawText("Leader Board", 1030, 730, 30, WHITE);
    
//     if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
//         Vector2 mousePos = GetMousePosition();
//         if (CheckCollisionPointRec(mousePos, homeBtn)) {
//             currentScreen = TITLE_SCREEN;
//         } else if (CheckCollisionPointRec(mousePos, leaderboardBtn)) {
//             currentScreen = LEADERBOARD_SCREEN;
//         }
//     }
// }

// void DrawBSTViewScreen() {
//     DrawText("BST Traversal View", 600, 60, 55, HEADER_COLOR);
    
//     vector<Player*> inOrder = gameManager.getLeaderboard().getInOrder();
//     vector<Player*> preOrder = gameManager.getLeaderboard().getPreOrder();
//     vector<Player*> postOrder = gameManager.getLeaderboard().getPostOrder();
    
//     if (inOrder.empty()) {
//         DrawText("No leaderboard data available. Play some games first!", 400, 400, 30, TEXT_COLOR);
//     } else {
//         // In-Order
//         int yPos = 180;
//         DrawText("In-Order Traversal:", 100, yPos, 30, HEADER_COLOR);
//         yPos += 45;
//         for(int i = 0; i < inOrder.size() && i < 10; i++) {
//             Player* p = inOrder[i];
//             DrawText(TextFormat("%d. %s", i+1, p->name.c_str()), 120, yPos, 24, PLAYER_COLORS[p->colorId % 4]);
//             DrawText(TextFormat("Score: %d, Wins: %d", p->score, p->wins), 320, yPos, 24, TEXT_COLOR);
//             yPos += 35;
//         }
        
//         // Pre-Order
//         yPos = 180;
//         DrawText("Pre-Order Traversal:", 650, yPos, 30, HEADER_COLOR);
//         yPos += 45;
//         for(int i = 0; i < preOrder.size() && i < 10; i++) {
//             Player* p = preOrder[i];
//             DrawText(TextFormat("%d. %s", i+1, p->name.c_str()), 670, yPos, 24, PLAYER_COLORS[p->colorId % 4]);
//             DrawText(TextFormat("Score: %d", p->score), 870, yPos, 24, TEXT_COLOR);
//             yPos += 35;
//         }
        
//         // Post-Order
//         yPos = 180;
//         DrawText("Post-Order Traversal:", 1200, yPos, 30, HEADER_COLOR);
//         yPos += 45;
//         for(int i = 0; i < postOrder.size() && i < 10; i++) {
//             Player* p = postOrder[i];
//             DrawText(TextFormat("%d. %s", i+1, p->name.c_str()), 1220, yPos, 24, PLAYER_COLORS[p->colorId % 4]);
//             DrawText(TextFormat("Score: %d", p->score), 1420, yPos, 24, TEXT_COLOR);
//             yPos += 35;
//         }
//     }
    
//     Rectangle backBtn = {700, 800, 400, 80};
//     DrawRectangleRec(backBtn, BUTTON_ACTIVE);
//     DrawText("Back to Leaderboard", 735, 830, 28, WHITE);
    
//     if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
//         Vector2 mousePos = GetMousePosition();
//         if (CheckCollisionPointRec(mousePos, backBtn)) {
//             currentScreen = LEADERBOARD_SCREEN;
//         }
//     }
// }

// void DrawBSTSearchScreen() {
//     DrawText("Search in BST", 650, 80, 60, HEADER_COLOR);
    
//     DrawText("Enter score to search:", 600, 200, 32, TEXT_COLOR);
    
//     Rectangle searchBox = {600, 260, 300, 70};
//     static char searchInput[10] = "";
//     static bool searchActive = false;
//     static vector<Player*> searchResults;
//     static bool hasSearched = false;
    
//     DrawRectangleLinesEx(searchBox, 3, searchActive ? RED : GRAY);
//     DrawText(searchInput, 620, 280, 35, TEXT_COLOR);
    
//     if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
//         Vector2 mousePos = GetMousePosition();
//         searchActive = CheckCollisionPointRec(mousePos, searchBox);
//     }
    
//     if (searchActive) {
//         int key = GetCharPressed();
//         while (key > 0) {
//             if ((key >= '0') && (key <= '9') && (strlen(searchInput) < 9)) {
//                 strncat(searchInput, (char*)&key, 1);
//             }
//             key = GetCharPressed();
//         }
        
//         if (IsKeyPressed(KEY_BACKSPACE) && strlen(searchInput) > 0) {
//             searchInput[strlen(searchInput) - 1] = '\0';
//         }
//     }
    
//     Rectangle searchBtn = {950, 260, 250, 70};
//     DrawRectangleRec(searchBtn, BUTTON_ACTIVE);
//     DrawText("Search", 1020, 280, 32, WHITE);
    
//     if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
//         Vector2 mousePos = GetMousePosition();
//         if (CheckCollisionPointRec(mousePos, searchBtn) && strlen(searchInput) > 0) {
//             int score = atoi(searchInput);
//             searchResults = gameManager.searchByScore(score);
//             hasSearched = true;
//         }
//     }
    
//     if (hasSearched) {
//         if (searchResults.empty()) {
//             DrawText(TextFormat("No players found with score: %s", searchInput), 600, 380, 28, RED);
//         } else {
//             DrawText(TextFormat("Players with score %s:", searchInput), 600, 380, 30, HEADER_COLOR);
            
//             int yPos = 440;
//             for (int i = 0; i < searchResults.size(); i++) {
//                 string result = TextFormat("%d. %s", i+1, searchResults[i]->name.c_str());
//                 DrawText(result.c_str(), 620, yPos, 26, PLAYER_COLORS[searchResults[i]->colorId % 4]);
                
//                 string details = TextFormat("Wins: %d, Avg Score: %.1f", 
//                     searchResults[i]->wins,
//                     searchResults[i]->getAverageScore());
//                 DrawText(details.c_str(), 820, yPos, 26, TEXT_COLOR);
//                 yPos += 45;
//             }
//         }
//     }
    
//     Rectangle backBtn = {700, 800, 400, 80};
//     DrawRectangleRec(backBtn, BUTTON_ACTIVE);
//     DrawText("Back to Leaderboard", 735, 830, 28, WHITE);
    
//     if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
//         Vector2 mousePos = GetMousePosition();
//         if (CheckCollisionPointRec(mousePos, backBtn)) {
//             currentScreen = LEADERBOARD_SCREEN;
//             hasSearched = false;
//             searchInput[0] = '\0';
//         }
//     }
// }

// void DrawLeaderboardScreen() {
//     DrawText("Leaderboard", 700, 60, 60, HEADER_COLOR);
    
//     vector<Player*> leaderboardPlayers = gameManager.getLeaderboard().getInOrder();
    
//     if (leaderboardPlayers.empty()) {
//         DrawText("No leaderboard data available. Play some games first!", 400, 300, 30, TEXT_COLOR);
//     } else {
//         // Table header background
//         Rectangle headerRect = {200, 160, 1400, 50};
//         DrawRectangleRec(headerRect, TABLE_HEADER_BG);
//         DrawRectangleLinesEx(headerRect, 2, GRAY);
        
//         // Table headers
//         DrawText("Rank", 250, 175, 28, HEADER_COLOR);
//         DrawText("Name", 450, 175, 28, HEADER_COLOR);
//         DrawText("Score", 750, 175, 28, HEADER_COLOR);
//         DrawText("Wins", 1000, 175, 28, HEADER_COLOR);
//         DrawText("Avg Score", 1250, 175, 28, HEADER_COLOR);
        
//         // Table rows
//         for (int i = 0; i < leaderboardPlayers.size() && i < 10; i++) {
//             Player* player = leaderboardPlayers[i];
//             int yPos = 220 + i * 50;
            
//             // Row background
//             Rectangle rowRect = {200, yPos - 5, 1400, 45};
//             DrawRectangleRec(rowRect, TABLE_ROW_BG);
//             DrawRectangleLinesEx(rowRect, 1, LIGHTGRAY);
            
//             // Row data
//             DrawText(TextFormat("%d", i + 1), 270, yPos, 26, TEXT_COLOR);
//             DrawText(player->name.c_str(), 450, yPos, 26, PLAYER_COLORS[player->colorId % 4]);
//             DrawText(TextFormat("%d", player->score), 770, yPos, 26, TEXT_COLOR);
//             DrawText(TextFormat("%d", player->wins), 1030, yPos, 26, TEXT_COLOR);
//             DrawText(TextFormat("%.1f", player->getAverageScore()), 1300, yPos, 26, TEXT_COLOR);
//         }
//     }
    
//     // Buttons
//     Rectangle homeBtn = {300, 800, 300, 80};
//     Rectangle viewBSTBtn = {650, 800, 300, 80};
//     Rectangle searchBSTBtn = {1000, 800, 300, 80};
    
//     DrawRectangleRec(homeBtn, BUTTON_ACTIVE);
//     DrawRectangleRec(viewBSTBtn, BUTTON_ACTIVE);
//     DrawRectangleRec(searchBSTBtn, BUTTON_ACTIVE);
    
//     DrawText("Home", 410, 830, 35, WHITE);
//     DrawText("View BST", 730, 830, 30, WHITE);
//     DrawText("Search BST", 1055, 830, 28, WHITE);
    
//     if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
//         Vector2 mousePos = GetMousePosition();
//         if (CheckCollisionPointRec(mousePos, homeBtn)) {
//             currentScreen = TITLE_SCREEN;
//         } else if (CheckCollisionPointRec(mousePos, viewBSTBtn)) {
//             currentScreen = BST_VIEW_SCREEN;
//         } else if (CheckCollisionPointRec(mousePos, searchBSTBtn)) {
//             currentScreen = BST_SEARCH_SCREEN;
//         }
//     }
// }

// void CreateConfetti() {
//     for (int i = 0; i < 5; i++) {
//         Particle p;
//         p.position = {(float)(rand() % 1800), -10};
//         p.velocity = {(float)(rand() % 100 - 50) / 10.0f, (float)(rand() % 100 + 50) / 10.0f};
//         p.color = ColorFromHSV(rand() % 360, 0.8f, 0.9f);
//         p.size = (float)(rand() % 10 + 5);
//         p.life = (float)(rand() % 100 + 50);
//         particles.push_back(p);
//     }
// }

// void UpdateConfetti() {
//     for (auto it = particles.begin(); it != particles.end();) {
//         it->position.x += it->velocity.x;
//         it->position.y += it->velocity.y;
//         it->velocity.y += 0.1f; // Gravity
//         it->life -= 1.0f;
        
//         if (it->life <= 0 || it->position.y > 1000) {
//             it = particles.erase(it);
//         } else {
//             ++it;
//         }
//     }
// }

#include "raylib.h"
#include "GameLogic.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

// Screen states
enum ScreenState {
    TITLE_SCREEN,
    INSTRUCTIONS_SCREEN,
    SELECT_PLAYERS_SCREEN,
    NAME_ENTRY_SCREEN,
    DUPLICATE_PLAYER_SCREEN,
    GAME_PLAY_SCREEN,
    GAME_OVER_SCREEN,
    LEADERBOARD_SCREEN,
    AVL_VIEW_SCREEN,
    AVL_SEARCH_SCREEN
};

// Colors - Updated for better consistency
const Color BACKGROUND_COLOR = {245, 245, 220, 255}; // Beige
const Color BUTTON_ACTIVE = {220, 20, 60, 255}; // Red
const Color BUTTON_INACTIVE = {128, 128, 128, 255}; // Grey
const Color TEXT_COLOR = {40, 40, 40, 255}; // Dark gray - Bold and readable
const Color HEADER_COLOR = {101, 67, 33, 255}; // Brown
const Color PLAYER_COLORS[] = {
    {255, 0, 0, 255},     // Red
    {0, 0, 255, 255},     // Blue
    {0, 255, 0, 255},     // Green
    {255, 255, 0, 255}    // Yellow
};
const Color ACTIVE_PLAYER_GLOW = {255, 165, 0, 255}; // Orange
const Color TABLE_HEADER_BG = {200, 200, 180, 255};
const Color TABLE_ROW_BG = {230, 230, 210, 255};
const Color WARNING_COLOR = {220, 20, 60, 255}; // Red for warnings
const Color HIGHLIGHT_COLOR = {255, 215, 0, 255}; // Gold for highlighting

// Game manager
GameManager gameManager;
ScreenState currentScreen = TITLE_SCREEN;

// Game state variables
int selectedPlayerCount = 0;
bool vsBot = false;
vector<string> playerNames(4);
int currentInputField = 0;
bool inputFieldsActive[4] = {false};

// Duplicate player handling
string duplicatePlayerName;
int duplicatePlayerIndex = -1;

// Particle for confetti
struct Particle {
    Vector2 position;
    Vector2 velocity;
    Color color;
    float size;
    float life;
};

vector<Particle> particles;

// Function declarations
void InitGame();
void UpdateGame();
void DrawGame();
void DrawTitleScreen();
void DrawInstructionsScreen();
void DrawSelectPlayersScreen();
void DrawNameEntryScreen();
void DrawDuplicatePlayerScreen();
void DrawGamePlayScreen();
void DrawGameOverScreen();
void DrawLeaderboardScreen();
void DrawAVLViewScreen();
void DrawAVLSearchScreen();
void CreateConfetti();
void UpdateConfetti();

int main() {
    const int screenWidth = 1800;
    const int screenHeight = 1100;
    
    InitWindow(screenWidth, screenHeight, "Matching Tile Game");
    SetTargetFPS(60);
    
    InitGame();
    
    while (!WindowShouldClose()) {
        UpdateGame();
        DrawGame();
    }
    
    CloseWindow();
    return 0;
}

void InitGame() {
    srand(time(NULL));
    currentScreen = TITLE_SCREEN;
}

void UpdateGame() {
    gameManager.update(GetFrameTime());
    
    if (currentScreen == GAME_OVER_SCREEN) {
        static double lastConfettiTime = 0;
        double currentTime = GetTime();
        
        UpdateConfetti();
        if (currentTime - lastConfettiTime > 0.1) {
            CreateConfetti();
            lastConfettiTime = currentTime;
        }
    }
}

void DrawGame() {
    BeginDrawing();
    ClearBackground(BACKGROUND_COLOR);
    
    switch (currentScreen) {
        case TITLE_SCREEN: DrawTitleScreen(); break;
        case INSTRUCTIONS_SCREEN: DrawInstructionsScreen(); break;
        case SELECT_PLAYERS_SCREEN: DrawSelectPlayersScreen(); break;
        case NAME_ENTRY_SCREEN: DrawNameEntryScreen(); break;
        case DUPLICATE_PLAYER_SCREEN: DrawDuplicatePlayerScreen(); break;
        case GAME_PLAY_SCREEN: DrawGamePlayScreen(); break;
        case GAME_OVER_SCREEN: DrawGameOverScreen(); break;
        case LEADERBOARD_SCREEN: DrawLeaderboardScreen(); break;
        case AVL_VIEW_SCREEN: DrawAVLViewScreen(); break;
        case AVL_SEARCH_SCREEN: DrawAVLSearchScreen(); break;
    }
    
    EndDrawing();
}

void DrawTitleScreen() {
    // Game title - centered
    DrawText("Matching Tile Game", 550, 150, 70, HEADER_COLOR);
    
    // Buttons - centered and spaced properly
    Rectangle instructionsBtn = {650, 350, 500, 90};
    Rectangle newGameBtn = {650, 470, 500, 90};
    Rectangle leaderboardBtn = {650, 590, 500, 90};
    
    DrawRectangleRec(instructionsBtn, BUTTON_ACTIVE);
    DrawRectangleRec(newGameBtn, BUTTON_ACTIVE);
    DrawRectangleRec(leaderboardBtn, BUTTON_ACTIVE);
    
    DrawText("Instructions", 760, 380, 40, WHITE);
    DrawText("New Game", 780, 500, 40, WHITE);
    DrawText("Leader Board", 750, 620, 40, WHITE);
    
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, instructionsBtn)) {
            currentScreen = INSTRUCTIONS_SCREEN;
        } else if (CheckCollisionPointRec(mousePos, newGameBtn)) {
            currentScreen = SELECT_PLAYERS_SCREEN;
        } else if (CheckCollisionPointRec(mousePos, leaderboardBtn)) {
            currentScreen = LEADERBOARD_SCREEN;
        }
    }
}

void DrawInstructionsScreen() {
    DrawText("Instructions", 650, 80, 60, HEADER_COLOR);
    
    int yPos = 200;
    int lineSpacing = 55;
    
    DrawText("Goal is to match two pair of tiles.", 150, yPos, 28, TEXT_COLOR); yPos += lineSpacing;
    DrawText("Bonus Points when a player consecutively matches tiles.", 150, yPos, 28, TEXT_COLOR); yPos += lineSpacing;
    DrawText("If a player mismatch a tile, the turn goes to the next player.", 150, yPos, 28, TEXT_COLOR); yPos += lineSpacing;
    DrawText("Game runs until all tiles have been matched.", 150, yPos, 28, TEXT_COLOR); yPos += lineSpacing;
    DrawText("At each player's turn as long as the card qty is greater than 10,", 150, yPos, 28, TEXT_COLOR); yPos += lineSpacing;
    DrawText("the player gets 2 chances of undoing the first card they selected ONLY.", 150, yPos, 28, TEXT_COLOR); yPos += lineSpacing;
    DrawText("When card qty decreases to 10 and below, no undo option is active.", 150, yPos, 28, TEXT_COLOR);
    
    Rectangle backBtn = {700, 750, 400, 80};
    DrawRectangleRec(backBtn, BUTTON_ACTIVE);
    DrawText("Back", 860, 780, 40, WHITE);
    
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, backBtn)) {
            currentScreen = TITLE_SCREEN;
        }
    }
}

void DrawSelectPlayersScreen() {
    DrawText("Select Players", 650, 120, 60, HEADER_COLOR);
    
    Rectangle btn2 = {650, 280, 500, 80};
    Rectangle btn3 = {650, 390, 500, 80};
    Rectangle btn4 = {650, 500, 500, 80};
    Rectangle btnBot = {650, 610, 500, 80};
    Rectangle backBtn = {650, 720, 500, 80};
    
    DrawRectangleRec(btn2, BUTTON_ACTIVE);
    DrawRectangleRec(btn3, BUTTON_ACTIVE);
    DrawRectangleRec(btn4, BUTTON_ACTIVE);
    DrawRectangleRec(btnBot, BUTTON_ACTIVE);
    DrawRectangleRec(backBtn, BUTTON_ACTIVE);
    
    DrawText("2 Players", 810, 310, 35, WHITE);
    DrawText("3 Players", 810, 420, 35, WHITE);
    DrawText("4 Players", 810, 530, 35, WHITE);
    DrawText("VS Bot", 840, 640, 35, WHITE);
    DrawText("Back", 860, 750, 35, WHITE);
    
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, btn2)) {
            selectedPlayerCount = 2;
            vsBot = false;
            currentScreen = NAME_ENTRY_SCREEN;
        } else if (CheckCollisionPointRec(mousePos, btn3)) {
            selectedPlayerCount = 3;
            vsBot = false;
            currentScreen = NAME_ENTRY_SCREEN;
        } else if (CheckCollisionPointRec(mousePos, btn4)) {
            selectedPlayerCount = 4;
            vsBot = false;
            currentScreen = NAME_ENTRY_SCREEN;
        } else if (CheckCollisionPointRec(mousePos, btnBot)) {
            selectedPlayerCount = 1;
            vsBot = true;
            currentScreen = NAME_ENTRY_SCREEN;
        } else if (CheckCollisionPointRec(mousePos, backBtn)) {
            currentScreen = TITLE_SCREEN;
        }
    }
}

void DrawNameEntryScreen() {
    DrawText("Enter Player Names", 600, 80, 60, HEADER_COLOR);
    
    int actualPlayers = vsBot ? 1 : selectedPlayerCount;
    
    for (int i = 0; i < actualPlayers; i++) {
        Rectangle inputBox = {600, 220 + i * 120, 600, 70};
        Color borderColor = inputFieldsActive[i] ? RED : GRAY;
        
        // Highlight if this is the duplicate field
        if (i == duplicatePlayerIndex) {
            DrawRectangleLinesEx(inputBox, 4, HIGHLIGHT_COLOR);
        } else {
            DrawRectangleLinesEx(inputBox, 3, borderColor);
        }
        
        DrawText(TextFormat("P%d: ", i + 1), 520, 235 + i * 120, 35, PLAYER_COLORS[i]);
        DrawText(playerNames[i].c_str(), 620, 235 + i * 120, 35, TEXT_COLOR);
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            if (CheckCollisionPointRec(mousePos, inputBox)) {
                inputFieldsActive[i] = true;
                currentInputField = i;
                duplicatePlayerIndex = -1; // Reset highlight when clicking
            } else {
                inputFieldsActive[i] = false;
            }
        }
        
        if (inputFieldsActive[i]) {
            int key = GetCharPressed();
            while (key > 0) {
                if ((key >= 32) && (key <= 125) && (playerNames[i].length() < 20)) {
                    playerNames[i] += (char)key;
                }
                key = GetCharPressed();
            }
            
            if (IsKeyPressed(KEY_BACKSPACE) && !playerNames[i].empty()) {
                playerNames[i].pop_back();
            }
        }
    }
    
    bool canStart = true;
    for (int i = 0; i < actualPlayers; i++) {
        if (playerNames[i].empty()) {
            canStart = false;
            break;
        }
    }
    
    Rectangle startBtn = {600, 250 + actualPlayers * 120, 300, 80};
    Color startBtnColor = canStart ? BUTTON_ACTIVE : BUTTON_INACTIVE;
    
    DrawRectangleRec(startBtn, startBtnColor);
    DrawText("Start", 710, 280 + actualPlayers * 120, 35, WHITE);
    
    Rectangle backBtn = {950, 250 + actualPlayers * 120, 300, 80};
    DrawRectangleRec(backBtn, BUTTON_ACTIVE);
    DrawText("Back", 1065, 280 + actualPlayers * 120, 35, WHITE);
    
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, startBtn) && canStart) {
            // Check for duplicate players
            bool hasDuplicate = false;
            for (int i = 0; i < actualPlayers; i++) {
                Player* existingPlayer = gameManager.findExistingPlayer(playerNames[i]);
                if (existingPlayer) {
                    duplicatePlayerName = playerNames[i];
                    duplicatePlayerIndex = i;
                    hasDuplicate = true;
                    break;
                }
            }
            
            if (hasDuplicate) {
                currentScreen = DUPLICATE_PLAYER_SCREEN;
            } else {
                vector<string> names;
                for (int i = 0; i < actualPlayers; i++) {
                    names.push_back(playerNames[i]);
                }
                gameManager.initGame(actualPlayers, names, vsBot);
                currentScreen = GAME_PLAY_SCREEN;
            }
        } else if (CheckCollisionPointRec(mousePos, backBtn)) {
            currentScreen = SELECT_PLAYERS_SCREEN;
        }
    }
}

void DrawDuplicatePlayerScreen() {
    DrawText("Duplicate Player Found", 600, 120, 60, WARNING_COLOR);
    
    DrawText(TextFormat("Player '%s' already exists!", duplicatePlayerName.c_str()), 
             550, 250, 40, TEXT_COLOR);
    DrawText("Continuing will update this player's record.", 550, 310, 35, TEXT_COLOR);
    DrawText("Do you want to continue?", 550, 370, 35, TEXT_COLOR);
    
    Rectangle continueBtn = {500, 500, 400, 80};
    Rectangle backBtn = {1000, 500, 400, 80};
    
    DrawRectangleRec(continueBtn, BUTTON_ACTIVE);
    DrawRectangleRec(backBtn, BUTTON_ACTIVE);
    
    DrawText("Continue", 620, 530, 35, WHITE);
    DrawText("Change Name", 1080, 530, 30, WHITE);
    
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, continueBtn)) {
            vector<string> names;
            int actualPlayers = vsBot ? 1 : selectedPlayerCount;
            for (int i = 0; i < actualPlayers; i++) {
                names.push_back(playerNames[i]);
            }
            gameManager.initGame(actualPlayers, names, vsBot);
            currentScreen = GAME_PLAY_SCREEN;
            duplicatePlayerIndex = -1;
        } else if (CheckCollisionPointRec(mousePos, backBtn)) {
            currentScreen = NAME_ENTRY_SCREEN;
        }
    }
}

void DrawGamePlayScreen() {
    vector<Player*> players = gameManager.getPlayers();
    Player* currentPlayer = gameManager.getCurrentPlayer();
    int totalCards = gameManager.getTotalCards();
    
    // Draw player quadrants - adjusted positions for 1800x1000
    for (int i = 0; i < players.size(); i++) {
        int cornerX, cornerY;
        switch (i) {
            case 0: cornerX = 80; cornerY = 80; break;
            case 1: cornerX = 1600; cornerY = 80; break;
            case 2: cornerX = 80; cornerY = 850; break;
            case 3: cornerX = 1600; cornerY = 850; break;
        }
        
        if (players[i] == currentPlayer) {
            DrawCircleLines(cornerX + 50, cornerY + 50, 45, ACTIVE_PLAYER_GLOW);
            DrawCircleLines(cornerX + 50, cornerY + 50, 48, ACTIVE_PLAYER_GLOW);
        }
        
        DrawCircle(cornerX + 50, cornerY + 50, 40, PLAYER_COLORS[i]);
        DrawText(players[i]->name.c_str(), cornerX, cornerY + 110, 24, TEXT_COLOR);
    }
    
    // Draw scoreboard - centered
    int startX = 500;
    DrawText("Scoreboard", 780, 20, 35, HEADER_COLOR);
    
    for (int i = 0; i < players.size(); i++) {
        DrawText(players[i]->name.c_str(), startX + i * 280, 70, 24, PLAYER_COLORS[i]);
    }
    
    for (int i = 0; i < players.size(); i++) {
        string scoreText = TextFormat("Score: %d", players[i]->score);
        string streakText = TextFormat("Streak: %d", players[i]->streak);
        DrawText(scoreText.c_str(), startX + i * 280, 100, 22, TEXT_COLOR);
        DrawText(streakText.c_str(), startX + i * 280, 130, 22, TEXT_COLOR);
    }
    
    // Draw cards (4x5 grid) - properly centered
    int cardWidth = 100;
    int cardHeight = 140;
    int gridWidth = 5 * cardWidth + 4 * 20; // 5 cards with 20px spacing
    int gridHeight = 4 * cardHeight + 3 * 20; // 4 rows with 20px spacing
    int startGridX = (1800 - gridWidth) / 2; // Center horizontally
    int startGridY = 300; // Position from top
    
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 5; col++) {
            int index = row * 5 + col;
            int x = startGridX + col * (cardWidth + 20);
            int y = startGridY + row * (cardHeight + 20);
            
            Rectangle cardRect = {(float)x, (float)y, (float)cardWidth, (float)cardHeight};
            
            CardNode* card = gameManager.getCards().getNodeByIndex(index);
            if (card && !card->matched) {
                if (card->flipped) {
                    DrawRectangleRec(cardRect, WHITE);
                    DrawRectangleLinesEx(cardRect, 3, BLACK);
                    
                    if (index == gameManager.getFirstSelection() || index == gameManager.getSecondSelection()) {
                        DrawRectangleLinesEx(cardRect, 5, RED);
                    }
                    
                    string valueStr = string(1, card->value);
                    DrawText(valueStr.c_str(), x + cardWidth/2 - 15, y + cardHeight/2 - 20, 40, BLACK);
                } else {
                    DrawRectangleRec(cardRect, LIGHTGRAY);
                    DrawRectangleLinesEx(cardRect, 3, DARKGRAY);
                    
                    DrawLine(x, y, x + cardWidth, y + cardHeight, DARKGRAY);
                    DrawLine(x + cardWidth, y, x, y + cardHeight, DARKGRAY);
                }
                
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    Vector2 mousePos = GetMousePosition();
                    if (CheckCollisionPointRec(mousePos, cardRect) && !card->flipped) {
                        gameManager.selectCard(index);
                    }
                }
            }
        }
    }
    
    // Draw Undo button - bottom center
    Rectangle undoBtn = {750, 950, 300, 80}; // Moved to bottom
    bool undoActive = currentPlayer->undoLeft > 0 && gameManager.getFirstSelection() != -1 && 
                     gameManager.getSecondSelection() == -1 && totalCards > 10;
    
    Color undoColor = undoActive ? BUTTON_ACTIVE : BUTTON_INACTIVE;
    DrawRectangleRec(undoBtn, undoColor);
    DrawText(TextFormat("Undo (%d)", currentPlayer->undoLeft), 820, 980, 30, WHITE);
    
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && undoActive) {
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, undoBtn)) {
            gameManager.undo();
        }
    }
    
    if (gameManager.isGameOver()) {
        currentScreen = GAME_OVER_SCREEN;
    }
}

void DrawGameOverScreen() {
    for (const Particle& particle : particles) {
        DrawRectangle(particle.position.x, particle.position.y, particle.size, particle.size, particle.color);
    }
    
    DrawText("Game Over!", 650, 120, 70, HEADER_COLOR);
    
    vector<Player*> sortedPlayers = gameManager.getSortedLeaderboard();
    
    for (int i = 0; i < sortedPlayers.size(); i++) {
        string rankText = TextFormat("%d. %s - Score: %d", i + 1, 
                                         sortedPlayers[i]->name.c_str(), 
                                         sortedPlayers[i]->score);
        DrawText(rankText.c_str(), 600, 280 + i * 60, 35, PLAYER_COLORS[sortedPlayers[i]->colorId]);
    }
    
    Rectangle homeBtn = {500, 700, 350, 80};
    Rectangle leaderboardBtn = {950, 700, 350, 80};
    
    DrawRectangleRec(homeBtn, BUTTON_ACTIVE);
    DrawRectangleRec(leaderboardBtn, BUTTON_ACTIVE);
    
    DrawText("Home", 630, 730, 35, WHITE);
    DrawText("Leader Board", 1030, 730, 30, WHITE);
    
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, homeBtn)) {
            currentScreen = TITLE_SCREEN;
        } else if (CheckCollisionPointRec(mousePos, leaderboardBtn)) {
            currentScreen = LEADERBOARD_SCREEN;
        }
    }
}

void DrawAVLViewScreen() {
    DrawText("AVL Tree Traversal View", 580, 60, 55, HEADER_COLOR);
    
    vector<Player*> inOrder = gameManager.getLeaderboard().getInOrder();
    vector<Player*> preOrder = gameManager.getLeaderboard().getPreOrder();
    vector<Player*> postOrder = gameManager.getLeaderboard().getPostOrder();
    
    if (inOrder.empty()) {
        DrawText("No leaderboard data available. Play some games first!", 400, 400, 30, TEXT_COLOR);
    } else {
        // In-Order
        int yPos = 180;
        DrawText("In-Order Traversal:", 100, yPos, 30, HEADER_COLOR);
        yPos += 45;
        for(int i = 0; i < inOrder.size() && i < 10; i++) {
            Player* p = inOrder[i];
            DrawText(TextFormat("%d. %s", i+1, p->name.c_str()), 120, yPos, 24, PLAYER_COLORS[p->colorId % 4]);
            DrawText(TextFormat("Score: %d, Wins: %d", p->score, p->wins), 320, yPos, 24, TEXT_COLOR);
            yPos += 35;
        }
        
        // Pre-Order
        yPos = 180;
        DrawText("Pre-Order Traversal:", 650, yPos, 30, HEADER_COLOR);
        yPos += 45;
        for(int i = 0; i < preOrder.size() && i < 10; i++) {
            Player* p = preOrder[i];
            DrawText(TextFormat("%d. %s", i+1, p->name.c_str()), 670, yPos, 24, PLAYER_COLORS[p->colorId % 4]);
            DrawText(TextFormat("Score: %d", p->score), 870, yPos, 24, TEXT_COLOR);
            yPos += 35;
        }
        
        // Post-Order
        yPos = 180;
        DrawText("Post-Order Traversal:", 1200, yPos, 30, HEADER_COLOR);
        yPos += 45;
        for(int i = 0; i < postOrder.size() && i < 10; i++) {
            Player* p = postOrder[i];
            DrawText(TextFormat("%d. %s", i+1, p->name.c_str()), 1220, yPos, 24, PLAYER_COLORS[p->colorId % 4]);
            DrawText(TextFormat("Score: %d", p->score), 1420, yPos, 24, TEXT_COLOR);
            yPos += 35;
        }
    }
    
    Rectangle backBtn = {700, 800, 400, 80};
    DrawRectangleRec(backBtn, BUTTON_ACTIVE);
    DrawText("Back to Leaderboard", 735, 830, 28, WHITE);
    
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, backBtn)) {
            currentScreen = LEADERBOARD_SCREEN;
        }
    }
}

void DrawAVLSearchScreen() {
    DrawText("Search in AVL Tree", 630, 80, 60, HEADER_COLOR);
    
    DrawText("Enter score to search:", 600, 200, 32, TEXT_COLOR);
    
    Rectangle searchBox = {600, 260, 300, 70};
    static char searchInput[10] = "";
    static bool searchActive = false;
    static vector<Player*> searchResults;
    static bool hasSearched = false;
    
    DrawRectangleLinesEx(searchBox, 3, searchActive ? RED : GRAY);
    DrawText(searchInput, 620, 280, 35, TEXT_COLOR);
    
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();
        searchActive = CheckCollisionPointRec(mousePos, searchBox);
    }
    
    if (searchActive) {
        int key = GetCharPressed();
        while (key > 0) {
            if ((key >= '0') && (key <= '9') && (strlen(searchInput) < 9)) {
                strncat(searchInput, (char*)&key, 1);
            }
            key = GetCharPressed();
        }
        
        if (IsKeyPressed(KEY_BACKSPACE) && strlen(searchInput) > 0) {
            searchInput[strlen(searchInput) - 1] = '\0';
        }
    }
    
    Rectangle searchBtn = {950, 260, 250, 70};
    DrawRectangleRec(searchBtn, BUTTON_ACTIVE);
    DrawText("Search", 1020, 280, 32, WHITE);
    
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, searchBtn) && strlen(searchInput) > 0) {
            int score = atoi(searchInput);
            searchResults = gameManager.searchByScore(score);
            hasSearched = true;
        }
    }
    
    if (hasSearched) {
        if (searchResults.empty()) {
            DrawText(TextFormat("No players found with score: %s", searchInput), 600, 380, 28, RED);
        } else {
            DrawText(TextFormat("Players with score %s:", searchInput), 600, 380, 30, HEADER_COLOR);
            
            int yPos = 440;
            for (int i = 0; i < searchResults.size(); i++) {
                string result = TextFormat("%d. %s", i+1, searchResults[i]->name.c_str());
                DrawText(result.c_str(), 620, yPos, 26, PLAYER_COLORS[searchResults[i]->colorId % 4]);
                
                string details = TextFormat("Wins: %d, Avg Score: %.1f", 
                    searchResults[i]->wins,
                    searchResults[i]->getAverageScore());
                DrawText(details.c_str(), 820, yPos, 26, TEXT_COLOR);
                yPos += 45;
            }
        }
    }
    
    Rectangle backBtn = {700, 800, 400, 80};
    DrawRectangleRec(backBtn, BUTTON_ACTIVE);
    DrawText("Back to Leaderboard", 735, 830, 28, WHITE);
    
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, backBtn)) {
            currentScreen = LEADERBOARD_SCREEN;
            hasSearched = false;
            searchInput[0] = '\0';
        }
    }
}

void DrawLeaderboardScreen() {
    DrawText("Leaderboard", 700, 60, 60, HEADER_COLOR);
    
    vector<Player*> leaderboardPlayers = gameManager.getLeaderboard().getInOrder();
    
    if (leaderboardPlayers.empty()) {
        DrawText("No leaderboard data available. Play some games first!", 400, 300, 30, TEXT_COLOR);
    } else {
        // Table header background
        Rectangle headerRect = {200, 160, 1400, 50};
        DrawRectangleRec(headerRect, TABLE_HEADER_BG);
        DrawRectangleLinesEx(headerRect, 2, GRAY);
        
        // Table headers
        DrawText("Rank", 250, 175, 28, HEADER_COLOR);
        DrawText("Name", 450, 175, 28, HEADER_COLOR);
        DrawText("Score", 750, 175, 28, HEADER_COLOR);
        DrawText("Wins", 1000, 175, 28, HEADER_COLOR);
        DrawText("Avg Score", 1250, 175, 28, HEADER_COLOR);
        
        // Table rows
        for (int i = 0; i < leaderboardPlayers.size() && i < 10; i++) {
            Player* player = leaderboardPlayers[i];
            int yPos = 220 + i * 50;
            
            // Row background
            Rectangle rowRect = {200, yPos - 5, 1400, 45};
            DrawRectangleRec(rowRect, TABLE_ROW_BG);
            DrawRectangleLinesEx(rowRect, 1, LIGHTGRAY);
            
            // Row data
            DrawText(TextFormat("%d", i + 1), 270, yPos, 26, TEXT_COLOR);
            DrawText(player->name.c_str(), 450, yPos, 26, PLAYER_COLORS[player->colorId % 4]);
            DrawText(TextFormat("%d", player->score), 770, yPos, 26, TEXT_COLOR);
            DrawText(TextFormat("%d", player->wins), 1030, yPos, 26, TEXT_COLOR);
            DrawText(TextFormat("%.1f", player->getAverageScore()), 1300, yPos, 26, TEXT_COLOR);
        }
    }
    
    // Buttons
    Rectangle homeBtn = {300, 800, 300, 80};
    Rectangle viewAVLBtn = {650, 800, 300, 80};
    Rectangle searchAVLBtn = {1000, 800, 300, 80};
    
    DrawRectangleRec(homeBtn, BUTTON_ACTIVE);
    DrawRectangleRec(viewAVLBtn, BUTTON_ACTIVE);
    DrawRectangleRec(searchAVLBtn, BUTTON_ACTIVE);
    
    DrawText("Home", 410, 830, 35, WHITE);
    DrawText("View AVL", 730, 830, 30, WHITE);
    DrawText("Search AVL", 1055, 830, 28, WHITE);
    
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, homeBtn)) {
            currentScreen = TITLE_SCREEN;
        } else if (CheckCollisionPointRec(mousePos, viewAVLBtn)) {
            currentScreen = AVL_VIEW_SCREEN;
        } else if (CheckCollisionPointRec(mousePos, searchAVLBtn)) {
            currentScreen = AVL_SEARCH_SCREEN;
        }
    }
}

void CreateConfetti() {
    for (int i = 0; i < 5; i++) {
        Particle p;
        p.position = {(float)(rand() % 1800), -10};
        p.velocity = {(float)(rand() % 100 - 50) / 10.0f, (float)(rand() % 100 + 50) / 10.0f};
        p.color = ColorFromHSV(rand() % 360, 0.8f, 0.9f);
        p.size = (float)(rand() % 10 + 5);
        p.life = (float)(rand() % 100 + 50);
        particles.push_back(p);
    }
}

void UpdateConfetti() {
    for (auto it = particles.begin(); it != particles.end();) {
        it->position.x += it->velocity.x;
        it->position.y += it->velocity.y;
        it->velocity.y += 0.1f; // Gravity
        it->life -= 1.0f;
        
        if (it->life <= 0 || it->position.y > 1000) {
            it = particles.erase(it);
        } else {
            ++it;
        }
    }
}