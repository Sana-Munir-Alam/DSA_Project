// GameLogic.cpp
#include "GameLogic.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <sstream>

// Add to GameLogic.cpp
Player* GameManager::findExistingPlayer(const std::string& name) {
    // Search in current players first
    for (auto player : players) {
        if (player->name == name) {
            return player;
        }
    }
    
    // Search in leaderboard/history
    auto allPlayers = leaderboard.getInOrder();
    for (auto player : allPlayers) {
        if (player->name == name) {
            return player;
        }
    }
    
    return nullptr;
}

// CardNode implementation
CardNode::CardNode(char v, int index) : value(v), flipped(false), matched(false), guiIndex(index), next(nullptr), prev(nullptr) {}

// CustomStack Node implementation
template<typename T>
CustomStack<T>::StackNode::StackNode(T d) : data(d), next(nullptr) {}

// CustomStack implementation
template<typename T>
CustomStack<T>::CustomStack() : top(nullptr), size(0) {}

template<typename T>
CustomStack<T>::~CustomStack() {
    clear();
}

template<typename T>
void CustomStack<T>::push(T data) {
    StackNode* newNode = new StackNode(data);
    newNode->next = top;
    top = newNode;
    size++;
}

template<typename T>
T CustomStack<T>::pop() {
    if (!top) return T();
    StackNode* temp = top;
    T data = top->data;
    top = top->next;
    delete temp;
    size--;
    return data;
}

template<typename T>
T CustomStack<T>::peek() const {
    return top ? top->data : T();
}

template<typename T>
bool CustomStack<T>::isEmpty() const { 
    return top == nullptr; 
}

template<typename T>
int CustomStack<T>::getSize() const { 
    return size; 
}

template<typename T>
void CustomStack<T>::clear() {
    while (!isEmpty()) pop();
}

// CustomQueue Node implementation
template<typename T>
CustomQueue<T>::QueueNode::QueueNode(T d) : data(d), next(nullptr) {}

// CustomQueue implementation
template<typename T>
CustomQueue<T>::CustomQueue() : front(nullptr), rear(nullptr), size(0) {}

template<typename T>
CustomQueue<T>::~CustomQueue() {
    while (!isEmpty()) dequeue();
}

template<typename T>
void CustomQueue<T>::enqueue(T data) {
    QueueNode* newNode = new QueueNode(data);
    if (!rear) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    size++;
}

template<typename T>
T CustomQueue<T>::dequeue() {
    if (!front) return T();
    QueueNode* temp = front;
    T data = front->data;
    front = front->next;
    if (!front) rear = nullptr;
    delete temp;
    size--;
    return data;
}

template<typename T>
T CustomQueue<T>::peekFront() const {
    return front ? front->data : T();
}

template<typename T>
bool CustomQueue<T>::isEmpty() const { 
    return front == nullptr; 
}

template<typename T>
int CustomQueue<T>::getSize() const { 
    return size; 
}

// Player implementation
Player::Player(std::string n, int c) : name(n), colorId(c), score(0), streak(0), 
                                      undoLeft(2), wins(0), totalScoreSum(0), gamesPlayed(0) {}

double Player::getAverageScore() const {
    return gamesPlayed > 0 ? static_cast<double>(totalScoreSum) / gamesPlayed : 0;
}

// AVLNode implementation
AVLNode::AVLNode(Player* p) : player(p), height(1), left(nullptr), right(nullptr) {}

// AVLTree implementation
AVLTree::AVLTree() : root(nullptr) {}

AVLTree::~AVLTree() {
    clear();
}

void AVLTree::clearTree(AVLNode* node) {
    if (!node) return;
    clearTree(node->left);
    clearTree(node->right);
    delete node;
}

void AVLTree::clear() {
    clearTree(root);
    root = nullptr;
}

int AVLTree::getHeight(AVLNode* node) {
    return node ? node->height : 0;
}

int AVLTree::getBalance(AVLNode* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

AVLNode* AVLTree::rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    
    x->right = y;
    y->left = T2;
    
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    
    return x;
}

AVLNode* AVLTree::leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    
    y->left = x;
    x->right = T2;
    
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    
    return y;
}

bool AVLTree::isPlayerBetter(Player* a, Player* b) {
    if (a->score != b->score) return a->score > b->score;
    if (a->wins != b->wins) return a->wins > b->wins;
    if (a->getAverageScore() != b->getAverageScore()) 
        return a->getAverageScore() > b->getAverageScore();
    return a->name < b->name;
}

AVLNode* AVLTree::insertNode(AVLNode* node, Player* player) {
    if (!node) return new AVLNode(player);
    
    if (isPlayerBetter(player, node->player)) {
        node->left = insertNode(node->left, player);
    } else {
        node->right = insertNode(node->right, player);
    }
    
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    
    int balance = getBalance(node);
    
    // Left Left Case - inserted in left subtree of left child
    if (balance > 1 && isPlayerBetter(player, node->left->player))
        return rightRotate(node);
    
    // Right Right Case - inserted in right subtree of right child  
    if (balance < -1 && !isPlayerBetter(player, node->right->player))
        return leftRotate(node);
    
    // Left Right Case - inserted in right subtree of left child
    if (balance > 1 && !isPlayerBetter(player, node->left->player)) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    
    // Right Left Case - inserted in left subtree of right child
    if (balance < -1 && isPlayerBetter(player, node->right->player)) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    
    return node;
}

void AVLTree::inOrderTraversal(AVLNode* node, std::vector<Player*>& result) {
    if (!node) return;
    inOrderTraversal(node->left, result);
    result.push_back(node->player);
    inOrderTraversal(node->right, result);
}

void AVLTree::preOrderTraversal(AVLNode* node, std::vector<Player*>& result) {
    if (!node) return;
    result.push_back(node->player);
    preOrderTraversal(node->left, result);
    preOrderTraversal(node->right, result);
}

void AVLTree::postOrderTraversal(AVLNode* node, std::vector<Player*>& result) {
    if (!node) return;
    postOrderTraversal(node->left, result);
    postOrderTraversal(node->right, result);
    result.push_back(node->player);
}

void AVLTree::searchByScoreHelper(AVLNode* node, int targetScore, std::vector<Player*>& result) {
    if (!node) return;
    
    // Since it's a BST sorted by player quality, we need to search both subtrees
    searchByScoreHelper(node->left, targetScore, result);
    if (node->player->score == targetScore) {
        result.push_back(node->player);
    }
    searchByScoreHelper(node->right, targetScore, result);
}
void AVLTree::insert(Player* player) {
    // First check if player already exists
    auto allPlayers = getInOrder();
    for (auto existingPlayer : allPlayers) {
        if (existingPlayer->name == player->name) {
            // Update existing player instead of inserting duplicate
            // Preserve the existing wins and accumulate other stats
            existingPlayer->score = player->score; // Current game score
            // existingPlayer->wins = player->wins;   // This should include the current game win
            existingPlayer->gamesPlayed = player->gamesPlayed;
            existingPlayer->totalScoreSum = player->totalScoreSum;
            return; // Don't insert duplicate
        }
    }
    
    // If player doesn't exist, insert new one
    root = insertNode(root, player);
}

std::vector<Player*> AVLTree::getInOrder() {
    std::vector<Player*> result;
    inOrderTraversal(root, result);
    return result;
}

std::vector<Player*> AVLTree::getPreOrder() {
    std::vector<Player*> result;
    preOrderTraversal(root, result);
    return result;
}

std::vector<Player*> AVLTree::getPostOrder() {
    std::vector<Player*> result;
    postOrderTraversal(root, result);
    return result;
}

std::vector<Player*> AVLTree::searchByScore(int targetScore) {
    std::vector<Player*> result;
    searchByScoreHelper(root, targetScore, result);
    return result;
}

// CardList implementation
CardList::CardList() : head(nullptr), tail(nullptr), size(0) {}

CardList::~CardList() {
    CardNode* current = head;
    while (current) {
        CardNode* next = current->next;
        delete current;
        current = next;
    }
}

void CardList::addCard(char value, int guiIndex) {
    CardNode* newNode = new CardNode(value, guiIndex);
    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;
    
    // Ensure indexMap is large enough
    if (guiIndex >= indexMap.size()) {
        indexMap.resize(guiIndex + 1, nullptr);
    }
    indexMap[guiIndex] = newNode;
}

CardNode* CardList::getNodeByIndex(int index) {
    if (index < 0 || index >= indexMap.size()) return nullptr;
    return indexMap[index];
}

void CardList::removeNode(CardNode* node) {
    if (!node) return;
    
    // Update neighbors
    if (node->prev) node->prev->next = node->next;
    if (node->next) node->next->prev = node->prev;
    
    // Update head/tail
    if (node == head) head = node->next;
    if (node == tail) tail = node->prev;
    
    // Mark as removed in indexMap
    if (node->guiIndex < indexMap.size()) {
        indexMap[node->guiIndex] = nullptr;
    }
    
    delete node;
    size--;
}

int CardList::getSize() const { 
    return size; 
}

bool CardList::isEmpty() const { 
    return size == 0; 
}

void CardList::debugPrint() {
    std::cout << "Cards: ";
    CardNode* current = head;
    while (current) {
        std::cout << current->value << "(" << current->guiIndex << ") ";
        current = current->next;
    }
    std::cout << std::endl;
}

// GameManager implementation
GameManager::GameManager() : currentPlayer(nullptr), firstSelection(-1), secondSelection(-1),
                           totalCards(20), gameOver(false), 
                           flipBackTimer(0), waitingForFlipBack(false) {
    std::srand(std::time(0));
    loadPlayerHistory();
    loadLeaderboard();
}

GameManager::~GameManager() {
    for (auto player : players) {
        delete player;
    }
}
// void GameManager::initGame(int numPlayers, const std::vector<std::string>& names) {
//     // Clear previous game state for new game
//     players.clear();
//     playerQueue = CustomQueue<Player*>();
//     cards = CardList();
//     gameOver = false;
//     firstSelection = -1;
//     secondSelection = -1;
//     waitingForFlipBack = false;
    
//     // Load historical players
//     std::vector<Player*> historicalPlayers = leaderboard.getInOrder();
    
//     // Create players - check for existing ones
//     for (int i = 0; i < numPlayers; i++) {
//         Player* gamePlayer = nullptr;
        
//         // Search in historical data
//         for (auto historicalPlayer : historicalPlayers) {
//             if (historicalPlayer->name == names[i]) {
//                 // Existing player - copy historical data but reset current game stats
//                 gamePlayer = new Player(historicalPlayer->name, i);
//                 // DON'T copy wins - start fresh for this game
//                 gamePlayer->gamesPlayed = historicalPlayer->gamesPlayed;
//                 gamePlayer->totalScoreSum = historicalPlayer->totalScoreSum;
//                 // Reset current game stats
//                 gamePlayer->score = 0;
//                 gamePlayer->streak = 0;
//                 gamePlayer->undoLeft = 2;
//                 gamePlayer->wins = 0;  // IMPORTANT: Start with 0 wins for new game
//                 break;
//             }
//         }
//         // New player
//         if (!gamePlayer) {
//             gamePlayer = new Player(names[i], i);
//         }
        
//         players.push_back(gamePlayer);
//     }
    
//     // Initialize queue
//     for (auto player : players) {
//         playerQueue.enqueue(player);
//     }
    
//     currentPlayer = playerQueue.dequeue();
//     initCards();
// }

void GameManager::initGame(int numPlayers, const std::vector<std::string>& names) {
    // Clear previous game state but preserve leaderboard
    players.clear();
    playerQueue = CustomQueue<Player*>();
    cards = CardList();
    gameOver = false;
    firstSelection = -1;
    secondSelection = -1;
    waitingForFlipBack = false;
    
    // Load historical players
    std::vector<Player*> historicalPlayers = leaderboard.getInOrder();
    
    // Create players - use historical data if available
    for (int i = 0; i < numPlayers; i++) {
        Player* gamePlayer = nullptr;
        
        // Search in historical data
        for (auto historicalPlayer : historicalPlayers) {
            if (historicalPlayer->name == names[i]) {
                // Found existing player - use their historical data
                // But reset current game stats only
                gamePlayer = new Player(historicalPlayer->name, i);
                // PRESERVE historical data
                gamePlayer->wins = historicalPlayer->wins;
                gamePlayer->gamesPlayed = historicalPlayer->gamesPlayed;
                gamePlayer->totalScoreSum = historicalPlayer->totalScoreSum;
                gamePlayer->streak = historicalPlayer->streak;
                // Reset current game stats only
                gamePlayer->score = 0;
                gamePlayer->undoLeft = 2;
                break;
            }
        }
        
        // New player
        if (!gamePlayer) {
            gamePlayer = new Player(names[i], i);
        }
        
        players.push_back(gamePlayer);
    }
    
    // Initialize queue
    for (auto player : players) {
        playerQueue.enqueue(player);
    }
    
    currentPlayer = playerQueue.dequeue();
    initCards();
}

void GameManager::continueGame(const std::vector<std::string>& names) {
    // Clear current game state but preserve leaderboard
    players.clear();
    playerQueue = CustomQueue<Player*>();
    cards = CardList();
    gameOver = false;
    firstSelection = -1;
    secondSelection = -1;
    waitingForFlipBack = false;
    
    // Load historical players
    std::vector<Player*> historicalPlayers = leaderboard.getInOrder();
    
    // Create players for current game
    for (int i = 0; i < names.size(); i++) {
        Player* gamePlayer = nullptr;
        
        // Find in historical data
        for (auto historicalPlayer : historicalPlayers) {
            if (historicalPlayer->name == names[i]) {
                // Create new player instance with ALL historical data
                gamePlayer = new Player(historicalPlayer->name, i);
                // COPY ALL HISTORICAL DATA
                gamePlayer->wins = historicalPlayer->wins;
                gamePlayer->gamesPlayed = historicalPlayer->gamesPlayed;
                gamePlayer->totalScoreSum = historicalPlayer->totalScoreSum;
                gamePlayer->streak = historicalPlayer->streak;
                // Reset current game stats (they will be accumulated when game ends)
                gamePlayer->score = 0;
                gamePlayer->undoLeft = 2;
                break;
            }
        }
        
        // If not found in history, create new player
        if (!gamePlayer) {
            gamePlayer = new Player(names[i], i);
        }
        
        players.push_back(gamePlayer);
    }
    
    // Initialize queue and start game
    for (auto player : players) {
        playerQueue.enqueue(player);
    }
    
    currentPlayer = playerQueue.dequeue();
    initCards();
}

// void GameManager::continueGame(const std::vector<std::string>& names) {
//     // Clear current game state but preserve leaderboard
//     players.clear();
//     playerQueue = CustomQueue<Player*>();
//     cards = CardList();
//     gameOver = false;
//     firstSelection = -1;
//     secondSelection = -1;
//     waitingForFlipBack = false;
    
//     // Load historical players
//     std::vector<Player*> historicalPlayers = leaderboard.getInOrder();
    
//     // Create players for current game
//     for (int i = 0; i < names.size(); i++) {
//         Player* gamePlayer = nullptr;
        
//         // Find in historical data
//         for (auto historicalPlayer : historicalPlayers) {
//             if (historicalPlayer->name == names[i]) {
//                 // Create new player instance with accumulated historical data
//                 gamePlayer = new Player(historicalPlayer->name, i);
//                 // Copy ALL historical data
//                 gamePlayer->wins = historicalPlayer->wins;
//                 gamePlayer->gamesPlayed = historicalPlayer->gamesPlayed;
//                 gamePlayer->totalScoreSum = historicalPlayer->totalScoreSum;
//                 gamePlayer->streak = historicalPlayer->streak;
//                 // Reset current game stats (they will be accumulated when game ends)
//                 gamePlayer->score = 0;
//                 gamePlayer->undoLeft = 2;
//                 break;
//             }
//         }
        
//         // If not found in history, create new player
//         if (!gamePlayer) {
//             gamePlayer = new Player(names[i], i);
//         }
        
//         players.push_back(gamePlayer);
//     }
    
//     // Initialize queue and start game
//     for (auto player : players) {
//         playerQueue.enqueue(player);
//     }
    
//     currentPlayer = playerQueue.dequeue();
//     initCards();
// }

void GameManager::initCards(int total) {
    totalCards = total;
    cards = CardList(); // Reset cards
    
    // Validate total cards (must be even)
    if (total % 2 != 0) total = 20;
    
    // Create pairs of letters
    std::vector<char> cardValues;
    for (int i = 0; i < total/2; i++) {
        char letter = 'A' + (i % 26); // Wrap around if more than 26 pairs
        cardValues.push_back(letter);
        cardValues.push_back(letter);
    }
    
    // Shuffle
    for (int i = 0; i < total; i++) {
        int j = rand() % total;
        std::swap(cardValues[i], cardValues[j]);
    }
    
    // Create card nodes
    for (int i = 0; i < total; i++) {
        cards.addCard(cardValues[i], i);
    }
    
    // Debug print
    cards.debugPrint();
}

bool GameManager::selectCard(int guiIndex) {
    if (waitingForFlipBack || gameOver) return false;
    
    CardNode* card = cards.getNodeByIndex(guiIndex);
    if (!card || card->flipped || card->matched) return false;
    
    card->flipped = true;
    
    if (firstSelection == -1) {
        firstSelection = guiIndex;
        return true;
    } else {
        secondSelection = guiIndex;
        checkMatch();
        return true;
    }
}

void GameManager::checkMatch() {
    CardNode* card1 = cards.getNodeByIndex(firstSelection);
    CardNode* card2 = cards.getNodeByIndex(secondSelection);
    
    if (card1 && card2 && card1->value == card2->value) {
        // Match found
        card1->matched = true;
        card2->matched = true;
        
        currentPlayer->streak++;
        currentPlayer->streakStack.push(currentPlayer->streak);
        currentPlayer->score += 10 * currentPlayer->streak;
        
        cards.removeNode(card1);
        cards.removeNode(card2);
        totalCards -= 2;
        
        // Check if game over
        if (cards.isEmpty()) {
            gameOver = true;
            
            // Find the actual winner (highest score)
            auto sortedPlayers = getSortedLeaderboard();
            if (!sortedPlayers.empty()) {
                Player* winner = sortedPlayers[0];
                winner->wins++;
                // Update all players' game history
                for (auto player : players) {
                    player->gamesPlayed++;
                    player->totalScoreSum += player->score;
                }
            }
            saveResults();
        }
        
        resetSelections();
    } else {
        // No match
        currentPlayer->streak = 0;
        currentPlayer->streakStack.clear();
        waitingForFlipBack = true;
        flipBackTimer = 1.0f; // 1 second delay
    }
}

bool GameManager::undo() {
    if (firstSelection == -1 || secondSelection != -1 || 
        currentPlayer->undoLeft <= 0 || totalCards <= 10) {
        return false;
    }
    
    CardNode* card = cards.getNodeByIndex(firstSelection);
    if (card) {
        card->flipped = false;
    }
    
    firstSelection = -1;
    currentPlayer->undoLeft--;
    return true;
}

void GameManager::update(float deltaTime) {
    if (waitingForFlipBack) {
        flipBackTimer -= deltaTime;
        if (flipBackTimer <= 0) {
            flipCardsBack();
            nextTurn();
            waitingForFlipBack = false;
        }
    }
}

void GameManager::flipCardsBack() {
    if (firstSelection != -1) {
        CardNode* card1 = cards.getNodeByIndex(firstSelection);
        if (card1) card1->flipped = false;
    }
    if (secondSelection != -1) {
        CardNode* card2 = cards.getNodeByIndex(secondSelection);
        if (card2) card2->flipped = false;
    }
    resetSelections();
}

void GameManager::nextTurn() {
    playerQueue.enqueue(currentPlayer);
    currentPlayer = playerQueue.dequeue();
    
    // Reset undo attempts if cards > 10
    if (totalCards > 10) {
        currentPlayer->undoLeft = 2;
    } else {
        currentPlayer->undoLeft = 0;
    }
    
    resetSelections();
}

void GameManager::resetSelections() {
    firstSelection = -1;
    secondSelection = -1;
}

void GameManager::forceNextTurn() {
    nextTurn();
}

Player* GameManager::findPlayerInHistory(const std::string& name) {
    // This would typically search in saved player history
    // For now, we'll search in current players (from previous games in same session)
    for (auto player : players) {
        if (player->name == name) {
            return player;
        }
    }
    return nullptr;
}

void GameManager::savePlayerHistory() {
    // Get all players from leaderboard (AVL tree)
    std::vector<Player*> allPlayers = leaderboard.getInOrder();
    
    std::ofstream file("player_history.txt", std::ios::trunc);
    if (!file) {
        std::cerr << "Error: Could not save player history!" << std::endl;
        return;
    }
    
    for (auto player : allPlayers) {
        file << player->name << "," 
             << player->score << "," 
             << player->wins << "," 
             << player->streak << ","
             << player->gamesPlayed << "," 
             << player->totalScoreSum << "\n";
    }
    file.close();
}
void GameManager::loadPlayerHistory() {
    std::ifstream file("player_history.txt");
    if (!file) {
        std::cout << "No existing player history file found. Starting fresh." << std::endl;
        return;
    }
    
    std::string line;
    int loadedCount = 0;
    
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;
        
        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        
        if (tokens.size() >= 6) {
            // Create player with historical data
            Player* player = new Player(tokens[0], 0);
            player->score = std::stoi(tokens[1]);
            player->wins = std::stoi(tokens[2]);
            player->streak = std::stoi(tokens[3]);
            player->gamesPlayed = std::stoi(tokens[4]);
            player->totalScoreSum = std::stod(tokens[5]);
            
            // Add to leaderboard
            leaderboard.insert(player);
            loadedCount++;
        }
    }
    file.close();
}

void GameManager::loadLeaderboard() {
    // Leaderboard is loaded through loadPlayerHistory
}

void GameManager::merge(std::vector<Player*>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    
    std::vector<Player*> L(n1), R(n2);
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    
    int i = 0, j = 0, k = l;
    
    while (i < n1 && j < n2) {
        if (isPlayerBetter(L[i], R[j])) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
std::vector<Player*> GameManager::getMergeSortedLeaderboard() {
    // Get all players from AVL tree (historical data)
    std::vector<Player*> allPlayers = leaderboard.getInOrder();
    
    // Sort using merge sort
    if (!allPlayers.empty()) {
        mergeSort(allPlayers, 0, allPlayers.size() - 1);
    }
    return allPlayers;
}
void GameManager::mergeSort(std::vector<Player*>& arr, int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

// // Update the comparison function for current game only
// bool GameManager::isPlayerBetter(Player* a, Player* b) {
//     // For current game ranking, only consider current game score
//     if (a->score != b->score) return a->score > b->score;
//     return a->name < b->name;
// }
bool GameManager::isPlayerBetter(Player* a, Player* b) {
    // For historical leaderboard ranking, consider multiple factors
    if (a->score != b->score) return a->score > b->score;
    if (a->wins != b->wins) return a->wins > b->wins;
    if (a->getAverageScore() != b->getAverageScore()) 
        return a->getAverageScore() > b->getAverageScore();
    return a->name < b->name;
}
// Getters implementation
Player* GameManager::getCurrentPlayer() const { 
    return currentPlayer; 
}

int GameManager::getTotalCards() const { 
    return totalCards; 
}

bool GameManager::isGameOver() const { 
    return gameOver; 
}

CardList& GameManager::getCards() { 
    return cards; 
}

std::vector<Player*> GameManager::getPlayers() const { 
    return players; 
}

int GameManager::getFirstSelection() const { 
    return firstSelection; 
}

int GameManager::getSecondSelection() const { 
    return secondSelection; 
}

std::vector<Player*> GameManager::getSortedLeaderboard() {
    // Create a copy of current game players only
    auto currentGamePlayers = players;
    
    // Sort by current game score only (not historical data)
    if (!currentGamePlayers.empty()) {
        mergeSort(currentGamePlayers, 0, currentGamePlayers.size() - 1);
    }
    return currentGamePlayers;
}

std::vector<Player*> GameManager::searchByScore(int score) {
    return leaderboard.searchByScore(score);
}

// void GameManager::saveResults() {
//     // First find the winner of current game
//     Player* currentGameWinner = nullptr;
//     if (!players.empty()) {
//         currentGameWinner = players[0];
//         for (auto p : players) {
//             if (p->score > currentGameWinner->score) {
//                 currentGameWinner = p;
//             }
//         }
//         currentGameWinner->wins++; // Increment wins for the winner
//     }
    
//     // Update each player's historical data and add to leaderboard
//     for (auto currentPlayer : players) {
//         // Update game history for current player
//         currentPlayer->gamesPlayed++;
//         currentPlayer->totalScoreSum += currentPlayer->score;
        
//         // Insert/Update in leaderboard
//         leaderboard.insert(currentPlayer);
//     }
    
//     // Save to file
//     savePlayerHistory();
    
//     // Store last game players for continue feature
//     lastGamePlayers.clear();
//     for (auto player : players) {
//         lastGamePlayers.push_back(player->name);
//     }
// }

void GameManager::saveResults() {
    // Only save when game is actually over
    if (!gameOver) {
        return;
    }

    // Find the winner of this completed game
    Player* gameWinner = nullptr;
    if (!players.empty()) {
        gameWinner = players[0];
        for (auto p : players) {
            if (p->score > gameWinner->score) {
                gameWinner = p;
            }
        }
    }
    
    // Update each player in the leaderboard with FINAL results
    for (auto currentPlayer : players) {
        // Search for existing player in leaderboard
        Player* existingPlayer = nullptr;
        auto allLeaderboardPlayers = leaderboard.getInOrder();
        for (auto lbPlayer : allLeaderboardPlayers) {
            if (lbPlayer->name == currentPlayer->name) {
                existingPlayer = lbPlayer;
                break;
            }
        }
        
        if (existingPlayer) {
            // UPDATE EXISTING PLAYER - Accumulate lifetime stats
            existingPlayer->gamesPlayed += 1;  // One more game played
            existingPlayer->totalScoreSum += currentPlayer->score; // Add this game's score to lifetime total
            
            // Update wins if this player won the current game
            if (currentPlayer == gameWinner) {
                existingPlayer->wins += 1;
            }
            
            // Update current score display (most recent game score)
            existingPlayer->score = currentPlayer->score;
            
            // Update best streak if current streak is better
            if (currentPlayer->streak > existingPlayer->streak) {
                existingPlayer->streak = currentPlayer->streak;
            }
        } else {
            // NEW PLAYER - First time playing
            Player* newPlayer = new Player(currentPlayer->name, currentPlayer->colorId);
            newPlayer->score = currentPlayer->score;
            newPlayer->wins = (currentPlayer == gameWinner) ? 1 : 0;
            newPlayer->streak = currentPlayer->streak;
            newPlayer->gamesPlayed = 1;
            newPlayer->totalScoreSum = currentPlayer->score;
            
            leaderboard.insert(newPlayer);
        }
    }
    
    // Save to file
    savePlayerHistory();
    
    // Store last game players for continue feature
    lastGamePlayers.clear();
    for (auto player : players) {
        lastGamePlayers.push_back(player->name);
    }
}

// Explicit template instantiation
template class CustomStack<int>;

template class CustomQueue<Player*>;
