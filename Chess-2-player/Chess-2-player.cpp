#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>

#define B_PAWN -6
#define W_PAWN 6
#define B_ROOK -1
#define W_ROOK 1
#define B_KNIGHT -2
#define W_KNIGHT 2
#define B_BISHOP -3
#define W_BISHOP 3
#define B_QUEEN -4
#define W_QUEEN 4
#define B_KING -5
#define W_KING 5

using namespace sf;

int size = 106;

Sprite f[32];//figures

int board[8][8] = {
    -1,-2,-3,-4,-5,-3,-2,-1,
    -6,-6,-6,-6,-6,-6,-6,-6,
     0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0,
     6, 6, 6, 6, 6, 6, 6, 6,
     1, 2, 3, 4, 5, 3, 2, 1
};

bool prevwhite = false;

std::string toChessNote(Vector2f p)
{
    std::string s = "";
    s += char(p.x / size + 97);
    s += char(7 - p.y / size + 49);
    return s;
}

Vector2f toCoord(char a, char b)
{
    int x = int(a) - 97;
    int y = 7 - int(b) + 49;
    return Vector2f(x * size, y * size);
}

void updateboard(std::string str)
{
    int x1 = int(str[0]) - 97;
    int y1 = 7 - int(str[1]) + 49;

    int x2 = int(str[2]) - 97;
    int y2 = 7 - int(str[3]) + 49;

    board[y2][x2] = board[y1][x1];
    board[y1][x1] = 0;
}

void move(std::string str)
{
    Vector2f oldPos = toCoord(str[0], str[1]);
    Vector2f newPos = toCoord(str[2], str[3]);

    for (int i = 0; i < 32; i++)
    {
        if (f[i].getPosition() == newPos) f[i].setPosition(-100, -100);
    }
    for (int i = 0; i < 32; i++)
    {
        if (f[i].getPosition() == oldPos) f[i].setPosition(newPos);
    }
    updateboard(str);
}

std::string position = "";
void loadPosition()
{
    int k = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            int n = board[i][j];
            if (!n) continue;
            int x = abs(n) - 1;
            int y = n > 0 ? 1 : 0;
            f[k].setTextureRect(IntRect(size * x + size * y * 6, 0, size, size));
            f[k].setPosition(size * j, size * i);
            k++;
        }
    }

    for (int i = 0; i < position.length(); i += 5)
        move(position.substr(i, 4));
}

bool legal(std::string str)
{
    int x1 = int(str[0]) - 97;
    int y1 = 7 - int(str[1]) + 49;

    int x2 = int(str[2]) - 97;
    int y2 = 7 - int(str[3]) + 49;

    if ((x1 == x2) && (y1 == y2))
        return false;

    if ((board[y1][x1] < 0))
    {
        if (!prevwhite)
            return false;
    }
    else
    {
        if (prevwhite)
            return false;
    }

    if (board[y1][x1] * board[y2][x2] > 0)
        return false;


    switch (board[y1][x1])
    {
    case W_PAWN:
        if (board[y2][x2] != 0)
        {
            if ((y1 - y2 == 1) && (x1 - x2 == -1))
                return true;
            if ((y1 - y2 == 1) && (x1 - x2 == 1))
                return true;
            else
                return false;
        }
        else
        {
            if ((y1 - y2 == 1) && (x1 - x2 == 0))
                return true;
            if ((y1 == 6) && ((y1 - y2 == 2) && (x1 - x2 == 0)))
                return true;
            else
                return false;
        }
        break;
    case B_PAWN:
        if (board[y2][x2] != 0)
        {
            if ((y1 - y2 == -1) && (x1 - x2 == -1))
                return true;
            if ((y1 - y2 == -1) && (x1 - x2 == 1))
                return true;
            else
                return false;
        }
        else
        {
            if ((y1 - y2 == -1) && (x1 - x2 == 0))
                return true;
            if ((y1 == 1) && ((y1 - y2 == -2) && (x1 - x2 == 0)))
                return true;
            else
                return false;
        }
        break;
    case W_ROOK:
        if ((x2 - x1 == 0) || (y2 - y1 == 0))
        {
            if (x2 - x1 == 0)
            {
                for (int i = y1; i!=y2; i=i+(abs(y2-y1))/(y2-y1))
                {
                    if (board[i][x1] != 0)
                        return false;
                }
                return true;
            }
            if (y2 - y1 == 0)
            {
                for (int i = x1; i != x2; i = i + (abs(x2 - x1) / (x2 - x1)))
                {
                    if (board[y1][i] != 0)
                        return false;
                }
                return true;
            }
        }
        else
            return false;
        break;
    case B_ROOK:
        if ((x2 - x1 == 0) || (y2 - y1 == 0))
        {
            if (x2 - x1 == 0)
            {
                for (int i = y1; i != y2; i = i + (abs(y2 - y1)) / (y2 - y1))
                {
                    if (board[i][x1] != 0)
                        return false;
                }
                return true;
            }
            if (y2 - y1 == 0)
            {
                for (int i = x1; i != x2; i = i + (abs(x2 - x1) / (x2 - x1)))
                {
                    if (board[y1][i] != 0)
                        return false;
                }
                return true;
            }
        }
        else
            return false;
        break;
    case W_KNIGHT:
        if (abs(x2 - x1) * abs(y2 - y1) == 2)
            return true;
        else
            return false;
        break;
    case B_KNIGHT:
        if (abs(x2 - x1) * abs(y2 - y1) == 2)
            return true;
        else
            return false;
        break;
    case W_BISHOP:
        if (abs(x2 - x1) == abs(y2 - y1))
        {
            int dx = abs(x2 - x1) / (x2 - x1);
            int dy = abs(y2 - y1) / (y2 - y1);

            while ((x1 + dx != x2) && (y1 + dy != y2))
            {
                x1 = x1 + dx;
                y1 = y1 + dy;
                if (board[y1][x1] != 0)
                    return false;
            }
            return true;
        }
        else
            return false;
        break;
    case B_BISHOP:
        if (abs(x2 - x1) == abs(y2 - y1))
        {
            int dx = abs(x2 - x1) / (x2 - x1);
            int dy = abs(y2 - y1) / (y2 - y1);

            while ((x1 + dx != x2) && (y1 + dy != y2))
            {
                x1 = x1 + dx;
                y1 = y1 + dy;
                if (board[y1][x1] != 0)
                    return false;
            }
            return true;
        }
        else
            return false;
        break;
    case W_QUEEN:
        if (x2 == x1)
        {
            int dy = abs(y2 - y1) / (y2 - y1);
            while (y1 + dy != y2)
            {
                y1 = y1 + dy;
                if (board[y1][x1] != 0)
                    return false;
            }
            return true;
        }
        if (y2 == y1)
        {
            int dx = abs(x2 - x1) / (x2 - x1);
            while (x1 + dx != x2)
            {
                x1 = x1 + dx;
                if (board[y1][x1] != 0)
                    return false;
            }
            return true;
        }
        if (abs(x2 - x1) == abs(y2 - y1))
        {
            int dx = abs(x2 - x1) / (x2 - x1);
            int dy = abs(y2 - y1) / (y2 - y1);

            while ((x1 + dx != x2) && (y1 + dy != y2))
            {
                x1 = x1 + dx;
                y1 = y1 + dy;
                if (board[y1][x1] != 0)
                    return false;
            }
            return true;
        }
        return false;
        break;
    case B_QUEEN:
        if (x2 == x1)
        {
            int dy = abs(y2 - y1) / (y2 - y1);
            while (y1 + dy != y2)
            {
                y1 = y1 + dy;
                if (board[y1][x1] != 0)
                    return false;
            }
            return true;
        }
        if (y2 == y1)
        {
            int dx = abs(x2 - x1) / (x2 - x1);
            while (x1 + dx != x2)
            {
                x1 = x1 + dx;
                if (board[y1][x1] != 0)
                    return false;
            }
            return true;
        }
        if (abs(x2 - x1) == abs(y2 - y1))
        {
            int dx = abs(x2 - x1) / (x2 - x1);
            int dy = abs(y2 - y1) / (y2 - y1);

            while ((x1 + dx != x2) && (y1 + dy != y2))
            {
                x1 = x1 + dx;
                y1 = y1 + dy;
                if (board[y1][x1] != 0)
                    return false;
            }
            return true;
        }
        return false;
        break;

    case W_KING:
        if((abs(x2 - x1) == 1) && (abs(y2 - y1) == 1))
            return true;
        if ((abs(x2 - x1) == 0) && (abs(y2 - y1) == 1))
            return true;
        if ((abs(x2 - x1) == 1) && (abs(y2 - y1) == 0))
            return true;
        return false;
        break;
    case B_KING:
        if ((abs(x2 - x1) == 1) && (abs(y2 - y1) == 1))
            return true;
        if ((abs(x2 - x1) == 0) && (abs(y2 - y1) == 1))
            return true;
        if ((abs(x2 - x1) == 1) && (abs(y2 - y1) == 0))
            return true;
        return false;
        break;
    default:
        break;
    }
}

int main()
{
    RenderWindow window(VideoMode(849, 849), "Chess!");

    Texture t1, t2;
    t1.loadFromFile("figures_c_1.png");
    t2.loadFromFile("board.png");

    Sprite s(t1);
    Sprite sBoard(t2);

    for (int i = 0; i < 32; i++) f[i].setTexture(t1);

    loadPosition();

    bool isMove = false;
    float dx = 0, dy = 0;
    Vector2f oldPos, newPos;
    std::string str;
    int n = 0;
    bool notmove = false;
    while (window.isOpen())
    {
        Vector2i pos = Mouse::getPosition(window);
        Event e;
        bool notmove = false;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
            /*moveback
            if (e.type == Event::KeyPressed)
                if (e.key.code == Keyboard::BackSpace)
                {
                    position.erase(position.length() - 6, 5); loadPosition();
                }*/
            //drag drop
            if (e.type == Event::MouseButtonPressed)
                if (e.key.code == Mouse::Left)
                    for (int i = 0; i < 32; i++)
                        if (f[i].getGlobalBounds().contains(pos.x, pos.y))
                        {
                            isMove = true; n = i;
                            dx = pos.x - f[i].getPosition().x;
                            dy = pos.y - f[i].getPosition().y;
                            oldPos = f[i].getPosition();
                        }

            if (e.type == Event::MouseButtonReleased)
                if (e.key.code == Mouse::Left)
                {
                    isMove = false;
                    Vector2f p = f[n].getPosition() + Vector2f(size / 2, size / 2);
                    Vector2f newPos = Vector2f(size * int(p.x / size), size * int(p.y / size));
                    str = toChessNote(oldPos) + toChessNote(newPos);

                    if (legal(str))
                    {
                        move(str);
                        prevwhite = 1 ^ prevwhite;
                        std::cout << str << std::endl;
                        if (oldPos != newPos)position = position + str + " ";
                        f[n].setPosition(newPos);
                    }
                    else
                        notmove = true;

                }

        }

        if (isMove) f[n].setPosition(pos.x - dx, pos.y - dy);
        if (notmove) f[n].setPosition(oldPos.x, oldPos.y);
        window.clear();
        window.draw(sBoard);

        for (int i = 0; i < 32; i++) window.draw(f[i]); window.draw(f[n]);

        window.display();
    }


    return 0;
}