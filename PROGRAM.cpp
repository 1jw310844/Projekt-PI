#include <iostream>
#include <cmath>
#include <cassert>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

using namespace std;

// Funkcja rysuje planszę gry w kółko i krzyżyk
//---------------------------------------------
void plansza(char t[])
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

// Funkcja zwraca true, jeśli nastąpiła
// wygrana danego zawodnika
//-------------------------------------
bool wygrana(char t[], char g)
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
        plansza(t);
        cout << "\nGRACZ " << g << " WYGRYWA!!!\n\n";
        return true;
    }
    return false;
}

// Funkcja zwraca true, jeśli na planszy nie ma już
// żadnego wolnego pola na ruch.
//-------------------------------------------------
bool remis(char t[])
{
    for (int i = 1; i <= 9; i++)
        if (t[i] == ' ') return false;
    plansza(t);
    cout << "\nREMIS !!!\n\n";
    return true;
}

// Funkcja umożliwia ruch gracza
// Po ruchu następuje zamiana gracza
//------------------------------------
void ruch(char t[], char& gracz)
{
    int r;

    plansza(t);
    cout << "\nGRACZ " << gracz << " : Twoj ruch : ";
    cin >> r;
    cout << "-----------------------\n\n";
    if ((r >= 1) && (r <= 9) && (t[r] == ' ')) t[r] = gracz;
    gracz = (gracz == 'O') ? 'X' : 'O';
}
int createZombie() {
    if (rand() % 67 < 10)
        return 11;

    else
        return rand() % 10 + 1;
}

int main()
{
    int wybor;
    cout << "1. Kółko i Krzyżyk dla 2 osób\n2. Zombie" << endl;
    cout << "W co chcesz zagrać?";
    cin >> wybor;
    switch(wybor)
    {
    case 1:
        char p[10], g, w;

        do
        {
            cout << "Gra w Kolko i Krzyzyk dla dwoch graczy - Jakub Wesoly\n"
                "======================================\n\n";
            for (int i = 1; i <= 9; i++) p[i] = ' ';
            g = 'O';
            while (!wygrana(p, 'X') && !wygrana(p, 'O') && !remis(p)) ruch(p, g);
            cout << "Chcesz zagrać jeszcze raz ? (T = TAK) : ";
            cin >> w;
            cout << "\n\n\n";
        } while ((w == 'T') || (w == 't'));
        break;
        
    default:
        srand(time(NULL));
        char enter;

        // game stats
        int playerAlive = true;
        int playerSkill = 9;
        int playerScore = 1;
        string playerName = "";
        int zombieCount = 0;
        int zombiesKilled = 0;

        // title
        cout << "Welcome to Zombie War." << endl << "Press [ENTER] to start.";
        cin.get();

        // player name
        cout << "Please enter your name: ";
        cin >> playerName;

        // ask how many zombies
        cout << "How many zombies do you wish to fight? ";
        cin >> zombieCount;

        cout << "Get ready to fight for your life, " << playerName << "!" << endl;

        // main game loop
        while (playerAlive && zombiesKilled < zombieCount) {
            // create a random zombie
            int zombieSkill = createZombie();

            // battle sequence
            if (zombieSkill > 10) {
                cout << endl << "Here comes a huge zombie!" << endl;
            }
            else {
                cout << endl << "Here comes zombie " << zombiesKilled + 1 << endl;
            }

            cout << "Fighting..." << endl;
            Sleep(2);

            // zombie killed the player
            if (playerSkill < zombieSkill) {
                playerAlive = false;
                cout << "You have died." << endl;
            }

            // player killed the zombie
            else {
                if (playerSkill - zombieSkill > 7) {
                    cout << "You wasted the zombie!" << endl;
                    playerScore = playerScore * 2;
                }

                else if (playerSkill - zombieSkill > 5) {
                    cout << "You decapitated the zombie!" << endl;
                    playerScore = playerScore * 2;
                }

                else if (playerSkill - zombieSkill > 0) {
                    cout << "You killed the zombie!" << endl;
                    playerScore = playerScore * 2;
                }

                else {
                    cout << "You killed the zombie, but suffered injuries." << endl;
                }

                zombiesKilled++;
            }

            cout << endl;
            Sleep(1);
        }

        // end game
        if (zombiesKilled == zombieCount) {
            // victory
            cout << "You have survived the onslaught!" << endl;
        }
        else {
            // lost
            cout << "You did not survive the zombie war." << endl;
        }

        cout << "Zombies killed: " << zombiesKilled << endl;
        cout << "Final score: " << playerScore << endl << endl;
        break;
    }
    
}