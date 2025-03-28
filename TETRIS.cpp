#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <sstream>
using namespace std;

const int WIDTH = 10;
const int HEIGHT = 20;

// Class for managing console output
class Console {
public:
    HANDLE hConsole;

    Console() {
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    }

    void setCursorPosition(int x, int y) {
        COORD pos = { (SHORT)x, (SHORT)y };
        SetConsoleCursorPosition(hConsole, pos);
    }

    void setColorForCell(char c) {
        switch (c) {
            case '1': SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY); break;
            case '2': SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); break;
            case '3': SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY); break;
            case '4': SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); break;
            case '5': SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY); break;
            case '6': SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY); break;
            case '7': SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY); break;
            default:  SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); break;
        }
    }
};

// Class representing a Tetromino
class Tetromino {
public:
    vector<vector<int>> shape;
    int x, y;

    Tetromino(vector<vector<int>> s, int startX, int startY) : shape(s), x(startX), y(startY) {}

    void rotate() {
        int rows = shape.size();
        int cols = shape[0].size();
        vector<vector<int>> rotated(cols, vector<int>(rows, 0));
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                rotated[j][rows - 1 - i] = shape[i][j];
            }
        }
        shape = rotated;
    }
};

// Class for managing the game grid
class Grid {
private:
    char grid[HEIGHT][WIDTH];
public:
    Grid() {
        resetGrid();
    }

    void resetGrid() {
        for (int i = 0; i < HEIGHT; i++)
            for (int j = 0; j < WIDTH; j++)
                grid[i][j] = '.';
    }

    bool canMove(int dx, int dy, const Tetromino &tetromino) {
        for (int i = 0; i < tetromino.shape.size(); i++) {
            for (int j = 0; j < tetromino.shape[i].size(); j++) {
                if (tetromino.shape[i][j]) {
                    int newX = tetromino.x + j + dx;
                    int newY = tetromino.y + i + dy;
                    if (newX < 0 || newX >= WIDTH || newY < 0 || newY >= HEIGHT)
                        return false;
                    if (grid[newY][newX] != '.')
                        return false;
                }
            }
        }
        return true;
    }

    void placeTetromino(const Tetromino &tetromino) {
        for (int i = 0; i < tetromino.shape.size(); i++) {
            for (int j = 0; j < tetromino.shape[i].size(); j++) {
                if (tetromino.shape[i][j]) {
                    grid[tetromino.y + i][tetromino.x + j] = char('0' + tetromino.shape[i][j]);
                }
            }
        }
    }

    void clearLines(int &score) {
        for (int i = HEIGHT - 1; i >= 0; i--) {
            bool full = true;
            for (int j = 0; j < WIDTH; j++) {
                if (grid[i][j] == '.') {
                    full = false;
                    break;
                }
            }
            if (full) {
                for (int row = i; row > 0; row--)
                    for (int col = 0; col < WIDTH; col++)
                        grid[row][col] = grid[row - 1][col];
                for (int col = 0; col < WIDTH; col++)
                    grid[0][col] = '.';
                score += 100;
                i++;
            }
        }
    }

    void printGrid(const Tetromino &tetromino, Console &console) {
        char temp[HEIGHT][WIDTH];
        for (int i = 0; i < HEIGHT; i++)
            for (int j = 0; j < WIDTH; j++)
                temp[i][j] = grid[i][j];

        for (int i = 0; i < tetromino.shape.size(); i++) {
            for (int j = 0; j < tetromino.shape[i].size(); j++) {
                if (tetromino.shape[i][j])
                    temp[tetromino.y + i][tetromino.x + j] = char('0' + tetromino.shape[i][j]);
            }
        }

        console.setCursorPosition(0, 0);
        for (int i = 0; i < WIDTH + 2; i++) cout << "#";
        cout << "\n";
        for (int i = 0; i < HEIGHT; i++) {
            cout << "#";
            for (int j = 0; j < WIDTH; j++) {
                if (temp[i][j] == '.') {
                    SetConsoleTextAttribute(console.hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    cout << '.';
                } else {
                    console.setColorForCell(temp[i][j]);
                    cout << '#';
                }
            }
            SetConsoleTextAttribute(console.hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            cout << "#\n";
        }
        for (int i = 0; i < WIDTH + 2; i++) cout << "#";
        cout << "\n";
    }
};

// Class to manage the overall game
class Game {
private:
    Grid grid;
    Console console;
    int score;
    int highScore;
    vector<vector<vector<int>>> tetrominoes;
    Tetromino currentTetromino;

    void spawnTetromino() {
        vector<vector<int>> shape = tetrominoes[rand() % tetrominoes.size()];
        currentTetromino = Tetromino(shape, WIDTH / 2 - shape[0].size() / 2, 0);
    }

    void handleInput() {
        while (_kbhit()) {
            int ch = _getch();
            if (ch == 224) {
                int arrow = _getch();
                if (arrow == 75 && grid.canMove(-1, 0, currentTetromino))
                    currentTetromino.x--;
                else if (arrow == 77 && grid.canMove(1, 0, currentTetromino))
                    currentTetromino.x++;
                else if (arrow == 80 && grid.canMove(0, 1, currentTetromino))
                    currentTetromino.y++;
                else if (arrow == 72)
                    currentTetromino.rotate();
            }
        }
    }

    int calculateFallSpeed() {
        int baseSpeed = 500;
        int speedIncrease = score / 500;
        int newSpeed = baseSpeed - (speedIncrease * 50);
        return max(newSpeed, 100);
    }

public:
    Game() : score(0), highScore(0), currentTetromino({{0}}, 0, 0) {
        tetrominoes = {
            {{1, 1, 1, 1}},
            {{2, 2}, {2, 2}},
            {{0, 3, 0}, {3, 3, 3}},
            {{0, 4, 4}, {4, 4, 0}},
            {{5, 5, 0}, {0, 5, 5}},
            {{6, 0, 0}, {6, 6, 6}},
            {{0, 0, 7}, {7, 7, 7}}
        };
        srand((unsigned)time(0));
    }

    int runGameSession() {
        system("cls");
        grid.resetGrid();
        score = 0;
        spawnTetromino();
        if (!grid.canMove(0, 0, currentTetromino)) {
            grid.printGrid(currentTetromino, console);
            return score;
        }
        DWORD lastFallTime = GetTickCount();

        while (true) {
            grid.printGrid(currentTetromino, console);
            handleInput();
            DWORD now = GetTickCount();
            int fallSpeed = calculateFallSpeed();
            if (now - lastFallTime >= fallSpeed) {
                if (grid.canMove(0, 1, currentTetromino))
                    currentTetromino.y++;
                else {
                    grid.placeTetromino(currentTetromino);
                    grid.clearLines(score);
                    spawnTetromino();
                    if (!grid.canMove(0, 0, currentTetromino)) {
                        grid.printGrid(currentTetromino, console);
                        return score;
                    }
                }
                lastFallTime = now;
            }
            Sleep(30);
        }
    }

    void startGame() {
        bool exitGame = false;
        while (!exitGame) {
            int finalScore = runGameSession();
            if (finalScore > highScore)
                highScore = finalScore;
            
            cout << "\nGame Over!\n";
            cout << "Your Score: " << finalScore << "\n";
            cout << "High Score: " << highScore << "\n\n";
            cout << "Press [R] to Restart or [X] to Exit.\n";
            
            bool validChoice = false;
            while (!validChoice) {
                if (_kbhit()) {
                    char ch = _getch();
                    if (ch == 'R' || ch == 'r')
                        validChoice = true;
                    else if (ch == 'X' || ch == 'x') {
                        validChoice = true;
                        exitGame = true;
                    }
                }
                Sleep(50);
            }
            system("cls");
        }
        system("cls");
        cout << "Thanks for playing TETRIS!\n";
        cout << "Final High Score: " << highScore << "\n";
        system("pause");
    }
};

int main() {
    Game tetris;
    tetris.startGame();
    return 0;
}
