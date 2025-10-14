#include <iostream>
#include <random>
#include <algorithm>
using namespace std;

class CardNode {
public:
    char cardsType;
    bool flipped;
    CardNode* next;
    CardNode* prev;
    CardNode(char type) {
        cardsType = type;
        flipped = false;    // card is unflipped
        next = NULL;
        prev = NULL;
    }
};

class DoublyLinkedList {
    CardNode* head;
    CardNode* tail;
    int TotalCards;
    int Score;
    int BonusMultiplier;    // yaar ye interesting karega game ko, cuase hum is main leader board add karsakte hain...and for that we can use stack to, push in users as they enter, and pop out them when asking for leader board etc...abhi socha hai not sure wheteher to include leaderboard or not.

    public:
    DoublyLinkedList(int total = 20) {
        head = NULL;
        tail = NULL;
        TotalCards = total;
        Score = 0;
        BonusMultiplier = 1; // Initial one, in case streak breaks it will be back to 1
    }

    void initializeCards() {
        vector<char> cards;
        for (char c = 'A'; c < 'A' + TotalCards / 2; c++) { // dividing by 2 cause we need 10 unique cards, the other 10 is the duplicate to match
            cards.push_back(c); // Storing the first of card pair
            cards.push_back(c); // Storing it's second of card pair
        }

        // Random Assigning of cards
        random_device rd;
        mt19937 g(rd());
        shuffle(cards.begin(), cards.end(), g);

        for (char c : cards) {
            insertAtStart(c);   // This will call insert function, which will create these alphabets nodes in the list
        }
    }

    int countCards() {
        int count = 0;
        CardNode* temp = head;
        while (temp) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    void insertAtStart(char type) {
        CardNode* newCard = new CardNode(type);
        if (head == NULL) {         // first Card
            head = tail = newCard;
        } else{
            newCard->next = head;
            head->prev = newCard;
            head = newCard;
        }
        
    }

    CardNode* findCard(int pos) {
        CardNode* temp = head;
        int count = 1;
        while (count != pos) {
            temp = temp->next;
            count++;
        }
        return temp;
    }

    bool flipCard(int pos) {
        CardNode* card = findCard(pos);
        card->flipped = true;
        return card->flipped;
    }

    void removeMatchingCard() { // take two class nodes as paarameter (first card of a pair, second card of a pair)
        // simple check if the nodes/values actually exist if not return
        // simply make sure the connection remains of both the crads prev and next when delteing them
    }


    void display() {
        // Suno adeena you gotta change this...ke for running as well as debugging, print the list twice.
        // The first would be what the user sees a linked list of cards all marked as X (which denotes unturned)
        // and the second list should show the actual value.
        // for eg:
        /*
        cout << "Original Unflipped List: NULL <-"
        while (temp){
            if(temp->flipped){ // meaning the card the temp points is flipped hence true
                // so print out the actual temp value
            }else{
             print "X" ya jo dil kare tumhara
            }

            if (temp->next){
                cout << "<->";      // lol tumhare us extra arrow ka solution for the Tail NULL hehe
            }
            temp = temp->next;
        }
        
        */

        // ye wala to sahi hai ye actual values print karega...isko daikh kar hum scoring wali cheez jaldi match karliya karainge warna khuwari ho gi match karna lol
        CardNode* temp = head;
        cout << "NULL <- ";
        while (temp != NULL) {
            cout << temp->cardsType << " <-> ";
            temp = temp->next;
        }
        cout << "NULL";
    }
};

int main(){
    DoublyLinkedList list;
    list.initializeCards();
    list.display();
    return 0;
}
