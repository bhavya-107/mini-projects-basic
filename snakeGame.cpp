#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

class snakeGame
{
private:
    int width, height;
    int x, y;
    int fruitX, fruitY;
    int score;
    vector<pair<int, int>> tail;
    enum direction
    {
        STOP = 0,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };
    direction dir;
    bool gameOver;

public:
    snakeGame(int w = 20, int h = 20)
    {
        width = w;
        height = h;
        gameOver = false;
        dir = STOP;
        x = width / 2;
        y = height / 2;
        fruitX = rand() % width;
        fruitY = rand() % height;
        score = 0;
        srand(time(0));
    }

    void setup()
    {
       CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
        cursorInfo.bVisible = FALSE;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
        system("cls");
    }

    void draw()
    {
       HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD coordScreen = {0, 0};
        DWORD cCharsWritten;
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        DWORD dwConSize;

        GetConsoleScreenBufferInfo(hConsole, &csbi);
        dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
        FillConsoleOutputCharacter(hConsole, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten);
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
        SetConsoleCursorPosition(hConsole, coordScreen);

        for (int i = 0; i < width + 2; i++)
            cout << "#";
        cout << endl;

        for (int i = 0; i < height; i++)
        {
            cout << "#";
            for (int j = 0; j < width; j++)
            {
                if (j == 0)
                    cout << "#";

                if (i == y && j == x)
                    cout << "O";
                else if (i == fruitY && j == fruitX)
                    cout << "F";
                else
                {
                    bool printBody = false;
                    for (auto &segment : tail)
                    {
                        if (segment.first == j && segment.second == i)
                        {
                            cout << "o";
                            printBody = true;
                            break;
                        }
                    }
                    if (!printBody)
                        cout << " ";
                }

                
            }
            cout << "#" <<endl;
        }

        for (int i = 0; i < width + 2; i++)
            cout << "#";
        cout << endl;

        cout << "Score: " << score << endl;
        cout << "Press X to quit" << endl;
    }

    void input()
    {
        if (_kbhit())
        {
            switch (_getch())
            {
            case 'a':
            case 'A':
                if (dir != RIGHT)
                    dir = LEFT;
                break;
            case 'd':
            case 'D':
                if (dir != LEFT)
                    dir = RIGHT;
                break;
            case 'w':
            case 'W':
                if (dir != DOWN)
                    dir = UP;
                break;
            case 's':
            case 'S':
                if (dir != UP)
                    dir = DOWN;
                break;
            case 'x':
            case 'X':
                gameOver = true;
                break;
            }
        }
    }

    void logic()
    {
        int prevX = x;
        int prevY = y;
        int prev2x, prev2y;

        switch (dir)
        {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        }

        if (x >= width || x < 0 || y >= height || y < 0)
            gameOver = true;
            return;

        for (auto &segment : tail)
        {
            if (segment.first == x && segment.second == y)
                gameOver = true;
                return;
        }

        if (x == fruitX && y == fruitY)
        {
            score += 10;

            fruitX = rand() % width;
            fruitY = rand() % height;

            tail.push_back({0, 0});
        }

        if (!tail.empty())
        {
            for (int i = tail.size() - 1; i > 0; i--)
            {
                tail[i] = tail[i - 1];
            }
            tail[0] = {prevX, prevY};
        }
    }

    void run() {
        setup();

         while (!gameOver) {
            input();
            if (dir != STOP) {  // Only update and redraw if moving
                logic();
                draw();
            }
            Sleep(100);  // Control game speed (100ms delay)
        }

        cout <<"\nGame Over!"<<endl;
        cout << "Final Score: " <<score <<endl;
        cout << "Press any key to exit...";
        _getch();
    }
};

int main() {
    cout << "Snake Game Controls:"<<endl;
     cout << "W - Up" << endl;
    cout << "A - Left" << endl;
    cout << "S - Down" << endl;
    cout << "D - Right" << endl;
    cout << "X - Quit" << endl;
    cout << "\nPress any key to start...";
    _getch();

    snakeGame game (20,20);
    game.run();

    return 0;
}