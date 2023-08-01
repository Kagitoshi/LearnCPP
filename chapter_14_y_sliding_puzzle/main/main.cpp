#include <array>
#include <cassert>
#include <iostream>
#include <numeric>

#include "Random.h"

// Increase amount of new lines if your board isn't
// at the very bottom of the console
constexpr int g_consoleLines{ 25 };

class Direction
{
public:
    enum Type
    {
        up,
        down,
        left,
        right,
        max_directions
    };

    Direction(Type type)
        :m_type{ type }
    {
    }

    Type getType() const
    {
        return m_type;
    }

    Direction operator-() const
    {
        switch (m_type)
        {
        case up:    return Direction{ down };
        case down:  return Direction{ up };
        case left:  return Direction{ right };
        case right: return Direction{ left };
        }

        assert(0 && "Unsupported direction was passed!");
        return Direction{ up };

    }

    friend std::ostream& operator<<(std::ostream & stream, Direction dir)
    {
        switch (dir.getType())
        {
        case Direction::up:    return (stream << "up");
        case Direction::down:  return (stream << "down");
        case Direction::left:  return (stream << "left");
        case Direction::right: return (stream << "right");
        default:               return(stream << "Unknown direction");
        }
    }

    static Direction getRandomDirection()
    {
        Type random{ static_cast<Type>(Random::get(0, Type::max_directions - 1)) };
        return Direction{ random };
    }

private:
    Type m_type{};
};

struct Point
{
    int x{};
    int y{};

    friend bool operator == (Point p1, Point p2)
    {
        return p1.x == p2.x && p1.y == p2.y;
    }

    friend bool operator!=(Point p1, Point p2)
    {
        return !(p1 == p2);
    }

   Point getAdjacentPoint(Direction dir) const
   {
       switch (dir.getType())
       {
       case Direction::up:      return Point{ x,     y - 1 };
       case Direction::down:    return Point{ x,     y + 1 };
       case Direction::left:    return Point{ x - 1, y };
       case Direction::right:   return Point{ x + 1, y };
       }

       return *this;
   }

};

namespace UserInput
{
    //Checking to see which controls are valid.
    // return true if input is one of w,a,s,d
    // is called by getCommandFromUser()
    bool isValidCommand(char input)
    {
        return input == 'w' || input == 'W' ||
               input == 'a' || input == 'A' ||
               input == 's' || input == 'S' ||
               input == 'd' || input == 'D' ||
               input == 'q' || input == 'Q';

    }

    //Ignores any extra input
    // is called by getCharacter()
    void ignoreLine()
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    //Getting a character input from getCommandFromUser() 
    // and calling ignoreLine() to remove any extra input after the first character
    char getCharacter()
    {
        char operation{};
        std::cin >> operation;
        ignoreLine(); // Remove any extra input
        return operation;
    }

    // Called from main() to get a character from the user
    // Called isValidCommand() to check if the first chracter is valid
    // if not valid, it will loop until a valid command is inputted
    // getCharacter() will be called to remove any extra characters and return the first character
    // then lastly this function will return a character to main()
    char getCommandFromUser()
    {
        char ch{};
        while (!isValidCommand(ch))
            ch = getCharacter();

        return ch;
    }

    Direction charToDirection(char ch)
    {
        switch (ch)
        {
        case 'w':
        case 'W' : return Direction{Direction::up};

        case 's': 
        case 'S': return Direction{ Direction::down };

        case 'a':
        case 'A': return Direction{ Direction::left };

        case 'd':
        case 'D': return Direction{ Direction::right };

        }

        assert(0 && "Unsupported direction was passed!");
        return Direction{ Direction::up };
    }


};

class Tile
{

public:
    Tile() = default;
    explicit Tile(int number)
        : m_num{ number }
    {
    }

    //Overloads << to display each Tile_m_num and properly spaces
    // the numbers or prints an empty tile if m_num == 0
    friend std::ostream& operator<< (std::ostream& stream, Tile tile)
    {
        if (tile.m_num > 9)
        {
            stream << ' ' << tile.m_num << ' ';
        }
        else if (tile.m_num > 0)
        {
            stream << "  "  << tile.m_num << ' ';
        }
        else if (tile.m_num == 0)
        {
            stream << "    ";
        }

        return stream;
    }

    bool isEmpty()  const
    {
        return m_num == 0;
    }

    int getNum() const { return m_num; }
    
private:
    int m_num{};
};

class Board
{
public:
    Board() = default;

    //Print empty lines so the board shows at the bottom.
    static void printEmptyLines(int count)
    {
        for (int i{ 1 }; i <= count; ++i)
        {
            std::cout << '\n';
        }
    }

    //Places a value in each element of Board::m_board
    // in the solved state with the last element being zero (empty)
    void solvedState()
    {
        //Fill out board in solved state
        for (int y{ 0 }; y < m_size; ++y)
        {
            for (int x{ 0 }; x < m_size; ++x)
            {
                m_board[y][x] = static_cast<Tile>(((y * m_size) + x) + 1);
            } 
        }

        m_board[m_size - 1][m_size - 1] = static_cast<Tile>(0);
    }

    //Overloads << to call printEmptyLines() so the board shows up at the bottom
    // and to display the board with each element being a Tile::m_tile
    friend std::ostream& operator<< (std::ostream& stream, Board &board)
    {

        printEmptyLines(g_consoleLines);

        //Print 2D array
        for (int y{ 0 }; y < m_size; ++y)
        {
            for (int x{ 0 }; x < m_size; ++x)
            {
                stream << board.m_board[y][x];
            }
            stream << '\n';
        }


        stream << '\n';

        return stream;
    }

    Point getEmptyTilePos() const
    {
        for (int y{ 0 }; y < m_size; ++y)
            for (int x{ 0 }; x < m_size; ++x)
                if (m_board[y][x].isEmpty())
                    return { x , y };

        assert(0 && "There is no empty tile in the board!!!");
        return { -1,-1 };
    }

    bool isValidTilePos(Point point)
    {
        return (point.x >= 0 && point.x < m_size)
            && (point.y >= 0 && point.y < m_size);
    }

    void swapTiles(Point p1, Point p2)
    {
        std::swap(m_board[p1.y][p1.x], m_board[p2.y][p2.x]);
    }

    friend bool operator==(const Board& f1, const Board& f2)
    {
        for (int y{ 0 }; y < m_size; ++y)
            for (int x{ 0 }; x < m_size; ++x)
                if (f1.m_board[y][x].getNum() != f2.m_board[y][x].getNum())
                    return false;

        return true;
    }

    bool moveTile(Direction dir)
    {
        Point emptyTile{ getEmptyTilePos() };
        Point adj{ emptyTile.getAdjacentPoint(-dir) };

        if (!isValidTilePos(adj))
            return false;

        swapTiles(adj, emptyTile);
        return true;
    }

    bool playerWon() const
    {
        static Board s_solved{};
        s_solved.solvedState();
        return s_solved == *this;
    }

     void randomize()
    {
        int shuffleCount{ Random::get(1000, 2000) };

        for (int i{ 0 }; i <= shuffleCount; ++i)
        {
            bool success = moveTile(Direction::getRandomDirection());
            if (!success)
                --i;
        }
    }

private:
    constexpr static int m_size{ 4 };
    std::array <std::array<Tile, m_size>, m_size> m_board{};

};

int main()
{
    Board board{};
    board.solvedState();
    board.randomize();
    std::cout << board;

    while (!board.playerWon())
    {
        char userInput{UserInput::getCommandFromUser()};

        if (userInput == 'q' || userInput == 'Q')
        {
            std::cout << "\n\nPEACE OUT HOMIE!\n\n";
            return 0;
        }

        Direction dir{ UserInput::charToDirection(userInput) };

        bool userMoved{ board.moveTile(dir) };
        if (userMoved)
            std::cout << board;

    }

    std::cout << "\n\nYou are the Winrar!\n\n";

    return 0;
}