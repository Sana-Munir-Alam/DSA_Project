// GameLogic.h
#ifndef GAMELOGIC_H
#define GAMELOGIC_H

using namespace std;

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <memory>

// Card node for linked list
struct CardNode {
    char value;
    bool flipped;
    bool matched;
    int guiIndex;
    CardNode* next;
    CardNode* prev;
    
    CardNode(char v, int index);
};

// Custom Stack for streak tracking
template<typename T>
class CustomStack {
private:
    struct StackNode {
        T data;
        StackNode* next;
        StackNode(T d);
    };
    
    StackNode* top;
    int size;

public:
    CustomStack();
    ~CustomStack();
    void push(T data);
    T pop();
    T peek() const;
    bool isEmpty() const;
    int getSize() const;
    void clear();
};

// Custom Queue for player turns
template<typename T>
class CustomQueue {
private:
    struct QueueNode {
        T data;
        QueueNode* next;
        QueueNode(T d);
    };
    
    QueueNode* front;
    QueueNode* rear;
    int size;

public:
    CustomQueue();
    ~CustomQueue();
    void enqueue(T data);
    T dequeue();
    T peekFront() const;
    bool isEmpty() const;
    int getSize() const;
};

// Player structure
struct Player {
    std::string name;
    int colorId; // 0=Red, 1=Blue, 2=Green, 3=Yellow
    int score;
    int streak;
    int undoLeft;
    int wins;
    double totalScoreSum;
    int gamesPlayed;
    CustomStack<int> streakStack;
    
    Player(std::string n, int c);
    double getAverageScore() const;
};

// AVL Tree Node for Leaderboard
struct AVLNode {
    Player* player;
    int height;
    AVLNode* left;
    AVLNode* right;
    
    AVLNode(Player* p);
};

// AVL Tree for Leaderboard
class AVLTree {
private:
    AVLNode* root;
    
    int getHeight(AVLNode* node);
    int getBalance(AVLNode* node);
    AVLNode* rightRotate(AVLNode* y);
    AVLNode* leftRotate(AVLNode* x);
    bool isPlayerBetter(Player* a, Player* b);
    AVLNode* insertNode(AVLNode* node, Player* player);
    void inOrderTraversal(AVLNode* node, std::vector<Player*>& result);
    void preOrderTraversal(AVLNode* node, std::vector<Player*>& result);
    void postOrderTraversal(AVLNode* node, std::vector<Player*>& result);
    void clearTree(AVLNode* node);
    void searchByScoreHelper(AVLNode* node, int targetScore, std::vector<Player*>& result);

public:
    AVLTree();
    ~AVLTree();
    void insert(Player* player);
    std::vector<Player*> getInOrder();
    std::vector<Player*> getPreOrder();
    std::vector<Player*> getPostOrder();
    std::vector<Player*> searchByScore(int targetScore);
    void clear();
};

// Card Linked List
class CardList {
private:
    CardNode* head;
    CardNode* tail;
    int size;
    std::vector<CardNode*> indexMap; // O(1) access

public:
    CardList();
    ~CardList();
    void addCard(char value, int guiIndex);
    CardNode* getNodeByIndex(int index);
    void removeNode(CardNode* node);
    int getSize() const;
    bool isEmpty() const;
    void debugPrint();
};

// Main Game Manager
class GameManager {
private:
    CardList cards;
    CustomQueue<Player*> playerQueue;
    std::vector<Player*> players;
    std::vector<std::string> lastGamePlayers; // Store names of last game players
    AVLTree leaderboard;
    
    Player* currentPlayer;
    int firstSelection;
    int secondSelection;
    int totalCards;
    bool gameOver;
    
    float flipBackTimer;
    bool waitingForFlipBack;
    
    // File handling
    void savePlayerHistory();
    void loadPlayerHistory();
    Player* findPlayerInHistory(const std::string& name);
    
    // Merge Sort implementation
    void merge(std::vector<Player*>& arr, int l, int m, int r);
    void mergeSort(std::vector<Player*>& arr, int l, int r);
    bool isPlayerBetter(Player* a, Player* b);

public:
    GameManager();
    ~GameManager();
    void initGame(int numPlayers, const std::vector<std::string>& names);
    void continueGame(const std::vector<std::string>& names);
    void initCards(int total = 20);
    bool selectCard(int guiIndex);
    void checkMatch();
    bool undo();
    void update(float deltaTime);
    void flipCardsBack();
    void nextTurn();
    void resetSelections();
    void forceNextTurn();
    Player* findExistingPlayer(const std::string& name);
    
    // Getters
    Player* getCurrentPlayer() const;
    int getTotalCards() const;
    bool isGameOver() const;
    CardList& getCards();
    std::vector<Player*> getPlayers() const;
    std::vector<std::string> getLastGamePlayers() const { return lastGamePlayers; }
    int getFirstSelection() const;
    int getSecondSelection() const;
    AVLTree& getLeaderboard() { return leaderboard; }
    
    std::vector<Player*> getMergeSortedLeaderboard();

    std::vector<Player*> getSortedLeaderboard();
    std::vector<Player*> searchByScore(int score);
    void saveResults();
    void loadLeaderboard();
};

#endif
