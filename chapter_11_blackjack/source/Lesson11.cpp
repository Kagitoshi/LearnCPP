#include <algorithm> //for std::shuffle
#include <array>
#include <cassert>
#include <ctime>  //for std::time
#include <iostream>
#include <random> //for std::mt19937
#include <string>


enum class CardRank
{
    rank_2,
    rank_3,
    rank_4,
    rank_5,
    rank_6,
    rank_7,
    rank_8,
    rank_9,
    rank_10,
    rank_jack,
    rank_queen,
    rank_king,
    rank_ace,

    max_ranks
};

enum class CardSuit
{
    club,
    diamond,
    heart,
    spade,

    max_suit
};

enum class BlackjackResult
{
    player_win,
    dealer_win,
    tie
};

struct Card
{
    CardRank rank{};
    CardSuit suit{};
};

void printCard(const Card& card)
{
    switch (card.rank)
    {
    case CardRank::rank_2:
        std::cout << '2'; break;
    case CardRank::rank_3:
        std::cout << '3'; break;
    case CardRank::rank_4:
        std::cout << '4'; break;
    case CardRank::rank_5:
        std::cout << '5'; break;
    case CardRank::rank_6:
        std::cout << '6'; break;
    case CardRank::rank_7:
        std::cout << '7'; break;
    case CardRank::rank_8:
        std::cout << '8'; break;
    case CardRank::rank_9:
        std::cout << '9'; break;
    case CardRank::rank_10:
        std::cout << 'T'; break;
    case CardRank::rank_jack:
        std::cout << 'J';  break;
    case CardRank::rank_queen:
        std::cout << 'Q'; break;
    case CardRank::rank_king:
        std::cout << 'K'; break;
    case CardRank::rank_ace:
        std::cout << 'A'; break;

    default:
        std::cout << '?'; break;
    }

    switch (card.suit)
    {
    case CardSuit::club:
        std::cout << 'C'; break;
    case CardSuit::spade:
        std::cout << 'S'; break;
    case CardSuit::diamond:
        std::cout << 'D'; break;
    case CardSuit::heart:
        std::cout << 'H'; break;

    default:
        std::cout << '?'; break;
    }
}


std::array<Card, 52> createDeck()
{
    std::array<Card, 52> deck{};

    for (int i{ 0 }; i < static_cast<int>(CardSuit::max_suit); ++i)
    {
        for (int j{ 0 }; j < static_cast<int>(CardRank::max_ranks); ++j)
        {
            deck[(i * static_cast<int>(CardRank::max_ranks)) + j].suit = static_cast<CardSuit>(i);
            
            deck[(i * static_cast<int>(CardRank::max_ranks)) + j].rank = static_cast<CardRank>(j);
        }
    }

    return deck;
}

void printDeck(const std::array<Card, 52>& deck)
{

    for (const auto card: deck)
    {
       printCard(card);
       std::cout << ' ';
    }
    std::cout << "\n \n";
 }

void shuffleDeck(std::array<Card,52>& deck)
{
    std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr))};
    
    std::shuffle(deck.begin(), deck.end(), mt);
}

int getCardValue(const Card& card)
{
    switch (card.rank)
    {
    case CardRank::rank_2:
        return 2;
    case CardRank::rank_3:
        return 3;
    case CardRank::rank_4:
        return 4;
    case CardRank::rank_5:
        return 5;
    case CardRank::rank_6:
        return 6;
    case CardRank::rank_7:
        return 7;
    case CardRank::rank_8:
        return 8;
    case CardRank::rank_9:
        return 9;
    case CardRank::rank_10:
    case CardRank::rank_jack:
    case CardRank::rank_queen:
    case CardRank::rank_king:
        return 10;
    case CardRank::rank_ace:
        return 11;
    default:
        assert(false && "should never happen");
        return 0;
    }
}

BlackjackResult playBlackjack(std::array<Card, 52>& deck)
{
    bool result{ true };

    int dealerTimesHit{ 0 };
    int playerTimesHit{ 0 };

    bool playersTurn{ true };

    while (true)
    {
        int cardNum{ 0 };

        int dealerScore{ 0 };
        int playerScore{ 0 };

        // Dealer's Logic
        std::cout << "****************************************\n";
        std::cout << "Dealer's Showing Hand: ";
        printCard(deck[cardNum]);
        dealerScore += getCardValue(deck[cardNum]);
        cardNum++;

        for (int i{ 0 }; i < dealerTimesHit; ++i)
        {
            std::cout << ' ';
            printCard(deck[i + 3 + playerTimesHit]);
            if ((getCardValue(deck[i + 3 + playerTimesHit]) == 11) && (dealerScore > 11))
            {
                ++dealerScore;
            }
            else
            {
                dealerScore += getCardValue(deck[i + 3 + playerTimesHit]);
            }

        }
        std::cout << "\n----------------------------------------\n";

        //Player's Logic
        std::cout << "Your Hand: ";
        printCard(deck[cardNum]);
        playerScore += getCardValue(deck[cardNum]);
        cardNum++;
        std::cout << ' ';
        printCard(deck[cardNum]);
        playerScore += getCardValue(deck[cardNum]);
        cardNum++;


        for (int i{ 0 }; i < playerTimesHit; ++i)
        {
            std::cout << ' ';
            printCard(deck[cardNum]);
            if ((getCardValue(deck[cardNum]) == 11) && (playerScore > 11))
            {
                ++playerScore;
            }
            else
            {
                playerScore += getCardValue(deck[cardNum]);
            }
            cardNum++;
        }
        std::cout << "\n----------------------------------------\n";

        std::cout << "The Dealer's Score: " << dealerScore << '\n';
        std::cout << "Your Score: " << playerScore;
        std::cout << "\n----------------------------------------\n";


        if (playerScore > 21 || (((dealerScore >= 17 && dealerScore <= 21) && dealerScore > playerScore) && !playersTurn) || (dealerScore == 21))
        {
            return BlackjackResult::dealer_win;
        }
        else if (dealerScore > 21 || (dealerScore >= 17 && dealerScore < playerScore))
        {
            return BlackjackResult::player_win;
        }
        else if ((playerScore == dealerScore) && (dealerScore >= 17 && dealerScore <= 21))
        {
            return BlackjackResult::tie;
        }

        if (!playersTurn && dealerScore <= 17 )
        {
            ++dealerTimesHit;
            std::cout << "\n \n";
        }
        else
        {
            std::cout << "Do you wish to HIT or STAND?" << '\n'
                << "Press 'a' to HIT" << '\n'
                << "Press 'k' to STAND" << '\n';

            char playersChoice{};

            std::cin >> playersChoice;

            if (playersChoice == 'a' || playersChoice == 'A')
            {
                ++playerTimesHit;
                std::cout << "\n \n";
            }
            else if (playersChoice == 'k' || playersChoice == 'K')
            {
                playersTurn = false;
                std::cout << "\n \n";
            }
            else
            {
                std::cout << "\n \n";
                std::cout << "Not a valid choice, Please try again... During Player's turn.";
                std::cout << "\n \n";
            }
        }
    }
}

int main()
{
    auto deck(createDeck());

    while (true)
    {
        shuffleDeck(deck);
        BlackjackResult result{ playBlackjack(deck) };

        if (result == BlackjackResult::dealer_win)
        {
            std::cout << "****************************************\n\n";
            std::cout << "You have lost the game!\n \n";
        }

        else if(result == BlackjackResult::player_win)
        {
            std::cout << "****************************************\n\n";
            std::cout << "You are the Winrar! \n \n";
        }

        else
        {
            std::cout << "****************************************\n\n";
            std::cout << "It is a tie. That's no fun. \n \n";
        }

        std::cout << "Would you like to play again? (y/n) \n";

        char playersChoice{};

        std::cin >> playersChoice;

        if (playersChoice == 'y' || playersChoice == 'Y')
        {
            std::cout << "Good Luck!";
            std::cout << "\n \n";
        }
        else if (playersChoice == 'n' || playersChoice == 'N')
        {
            std::cout << "Thanks for playing.";
            std::cout << "\n \n";
            break;
        }
        else
        {
            std::cout << "\n \n";
            std::cout << "Not a valid choice, Please try again... During Replay choice.";
            std::cout << "\n \n";
        }


    }


    return 0;
}