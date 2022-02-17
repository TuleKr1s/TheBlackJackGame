#include <iostream>
#include <cstdlib>
#include <array>
#include <random>

class Card {
public:
    // enumeration of all card suits
    enum CardSuit {
        TREFI,
        BUBNI,
        CHERVI,
        PIKI,
        MAX_SUITS
    };

    // enumeration of all card ranks
    enum CardRank {
        RANK_2,
        RANK_3,
        RANK_4,
        RANK_5,
        RANK_6,
        RANK_7,
        RANK_8,
        RANK_9,
        RANK_10,
        RANK_VALET,
        RANK_DAMA,
        RANK_KOROL,
        RANK_TUZ,
        MAX_RANK
    };
private:
    CardRank m_rank;
    CardSuit m_suit;
public:
    Card(CardRank rank = MAX_RANK, CardSuit suit = MAX_SUITS)
        : m_rank{ rank }, m_suit{ suit } {}

    // Print of card abbreaviations
    void printCard() const {
        switch (m_rank) {
        case RANK_2:        std::cout << "2"; break;
        case RANK_3:        std::cout << "3"; break;
        case RANK_4:        std::cout << "4"; break;
        case RANK_5:        std::cout << "5"; break;
        case RANK_6:        std::cout << "6"; break;
        case RANK_7:        std::cout << "7"; break;
        case RANK_8:        std::cout << "8"; break;
        case RANK_9:        std::cout << "9"; break;
        case RANK_10:       std::cout << "10"; break;
        case RANK_VALET:    std::cout << "V"; break;
        case RANK_DAMA:     std::cout << "D"; break;
        case RANK_KOROL:    std::cout << "K"; break;
        case RANK_TUZ:      std::cout << "T"; break;
        }
        switch (m_suit) {
        case TREFI:         std::cout << "T"; break;
        case BUBNI:         std::cout << "B"; break;
        case CHERVI:        std::cout << "C"; break;
        case PIKI:          std::cout << "P"; break;
        }
    }

    // Getting points for the game based on the rank of the card
    int getCardValue() const {
        switch (m_rank) {
        case RANK_2:        return 2; break;
        case RANK_3:        return 3; break;
        case RANK_4:        return 4; break;
        case RANK_5:        return 5; break;
        case RANK_6:        return 6; break;
        case RANK_7:        return 7; break;
        case RANK_8:        return 8; break;
        case RANK_9:        return 9; break;
        case RANK_10:
        case RANK_VALET:
        case RANK_DAMA:
        case RANK_KOROL:    return 10; break;
        case RANK_TUZ:      return 11; break;
        }
    }



};

class Deck {

    std::array<Card, 52> m_deck;
    int m_cardIndex = 0;

    static void swapCard(Card& card1, Card& card2) {

        // The standard procedure for swap 2 variables
        Card temp;
        temp = card1;
        card1 = card2;
        card2 = temp;
    }

public:
    Deck() {
        // Filling the deck in order
        int card = 0;
        for (int suit = 0; suit < Card::MAX_SUITS; ++suit) {
            for (int rank = 0; rank < Card::MAX_RANK; ++rank) {
                m_deck[card] = Card(static_cast<Card::CardRank>(rank), static_cast<Card::CardSuit>(suit));
                ++card;
            }
        }
    }

    // Print full deck
    void printDeck() const {
        for (const auto& card : m_deck) {
            card.printCard();
            std::cout << " ";
        }

        std::cout << "\n";
    }

    void shuffleDeck() {

        for (int i = 0; i < 52; ++i) {

            // Using the Mesenne number to find a random number 
            std::random_device rd;
            std::mt19937 mersenne(rd());

            int min = 0, max = 51;

            // Using the formula (n % (max - min + 1)) + min,
            // where min and max are the minimum and maximum numbers respectively 
            // of the expected range, n is a random number
            int randomNum = (mersenne() % (max - min + 1)) + min;

            // The function for swap the current card and a random card which was found
            swapCard(m_deck[i], m_deck[randomNum]);
        }
        m_cardIndex = 0;
    }

    const Card& dealCard() {

        return m_deck[m_cardIndex++];

    }

};

std::string getPlayerChoice() {

    std::cout << "What do you wanna do? h/s (hit/stand): "; // Further actions of the player that affect the game
    std::string choice;
    std::cin >> choice;
    std::cout << "\n";

    return choice;
}

bool playBlackJack(Deck& deck) {



    int dealerResult = deck.dealCard().getCardValue(); // Getting a card for a dealer

    int playerCard1 = deck.dealCard().getCardValue(), playerCard2 = deck.dealCard().getCardValue(); // Getting a card for the player
    int playerResult = playerCard1 + playerCard2; // Result of all the cards that the player has

    // The loop won't end until the game is over
    while (true) {

        // Print of current points from the dealer and the player
        std::cout << "Diller Have: " << dealerResult << "\n";
        std::cout << "You Have: " << playerResult << "\n";

        // Calculation of a possible victory for a player afre the first 2 cards are drawn
        if ((playerCard1 + playerCard2) == 21) return 1;

        // If the player wanna play farther, he is take a card untill he wanna end
        // When the player wanna end their turn, the dealer start his turn untill his result exceeds 17
        if (getPlayerChoice() == "h") {

            // Add a new card to the player, print his added points and result
            int oneMoreCard = deck.dealCard().getCardValue();
            std::cout << "You have +" << oneMoreCard << " points\n";
            playerResult += oneMoreCard;

            std::cout << "\n";

            // The player will lose if sum of his points will be is more than 21
            if (playerResult > 21) return 0;

        }
        else {

            do {
                // Add a new card to the dealer and print result
                int oneMoreCard = deck.dealCard().getCardValue();
                std::cout << "Diller have +" << oneMoreCard << " points\n";
                dealerResult += oneMoreCard;
                std::cout << "Diller Have: " << dealerResult << "\n\n";

            } while (dealerResult < 17); // Add a new card to the dealler until the sum of his points is equal to 17 or more

            // Checking the results of the game after the moves made by the player and the dealer
            if (playerResult == 21 || dealerResult > 21 \
                || dealerResult < playerResult || dealerResult == playerResult)
                return 1;
            return 0;
        }

    }
}

int main() {
    system("chcp 1251>nul");

    Deck deck;

    // The function for shuffle the deck
    deck.shuffleDeck();

    // Summing up the results of the game
    if (playBlackJack(deck))  std::cout << "Congratulations, you won!\n";
    else            std::cout << "\nI'm sorry, you lost!\n";

    return 0;

}
