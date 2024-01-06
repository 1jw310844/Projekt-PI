#include <iostream>
#include <cmath>
#include <cassert>

using namespace std;

void board(char t[])
{
    for (int i = 1; i <= 9; i++)
    {
        cout << " " << t[i] << " ";
        if (i % 3)
            cout << "|";
        else if (i != 9)
            cout << "\n---+---+---\n";
        else cout << endl;
    }
}
bool win(char t[], char g)
{
    bool test;
    int i;

    test = false;
    for (i = 1; i <= 7; i += 3)
        test |= ((t[i] == g) && (t[i + 1] == g) && (t[i + 2] == g));
    for (i = 1; i <= 3; i++)
        test |= ((t[i] == g) && (t[i + 3] == g) && (t[i + 6] == g));
    test |= ((t[1] == g) && (t[5] == g) && (t[9] == g));
    test |= ((t[3] == g) && (t[5] == g) && (t[7] == g));
    if (test)
    {
        board(t);
        cout << "\nGRACZ " << g << " WYGRYWA!!!\n\n";
        return true;
    }
    return false;
}

bool draw(char t[])
{
    for (int i = 1; i <= 9; i++)
        if (t[i] == ' ') return false;
    board(t);
    cout << "\nREMIS !!!\n\n";
    return true;
}
void move(char t[], char& player)
{
    int r;

    board(t);
    cout << "\nGRACZ " << player << " : Twoj ruch : ";
    cin >> r;
    cout << "-----------------------\n\n";
    if ((r >= 1) && (r <= 9) && (t[r] == ' ')) t[r] = player;
    player = (player == 'O') ? 'X' : 'O';
}

int main()
{
    char p[10], g, again;

    do
    {
        cout << "Gra w Kolko i Krzyzyk dla dwoch graczy - Jakub Wesoły 310844, Podstawy Informatyki\n"
            "======================================\n\n";
        for (int i = 1; i <= 9; i++) p[i] = ' ';
        g = 'O';
        while (!win(p, 'X') && !win(p, 'O') && !draw(p)) move(p, g);
        cout << "Jeszcze raz ? (T = TAK) : ";
        cin >> again;
        cout << "\n\n\n";
    } while ((again == 'T') || (again == 't'));
}
