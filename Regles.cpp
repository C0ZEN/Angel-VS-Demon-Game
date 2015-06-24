#include "stdafx.h"

#include <Windows.h>
#include <iostream>
#include <string>

#include "Regles.h"
#include "Couleurs.h"

using namespace std;

int Regles::force = 1;
int Regles::tour = 0;

// Constructeur
Regles::Regles()
{
}

// Demande la force de l'ange
void Regles::forceAnge()
{
    bool intCorrect = false;
    char bufCon[80];

    while (intCorrect == false)
    {
        try
        {
            // Demande à l'utilisateur la force de l'ange
            Couleurs::jaune();
            CharToOemA(" Saisir la force de l'ange : ", bufCon);
            cout << bufCon;
            Couleurs::turquoise();
            cin >> force;

            if (!cin) // Gère l'erreur
            {
                throw logic_error(" Le rang de force est un nombre.");
            }

            if (force < 1 || force > 5) // Si la taille n'est pas bonne
            {
                throw logic_error(" Le rang de force doit être compris entre 1 et 5.");
            }

            // Tout est bon
            intCorrect = true;
            Couleurs::vert();
            CharToOemA(" La force de l'ange est de ", bufCon);
            cout << bufCon << force << "." << endl;
        }
        catch (const exception & e) // Affiche l'erreur
        {
            Couleurs::rouge();
            CharToOemA(e.what(), bufCon);
            cerr << bufCon << endl;
            cin.sync();
            cin.clear();
        }
    }
}

// Get force
int Regles::getForce()
{
    return Regles::force;
}

// Commence la partie
void Regles::debutJeu()
{
    char bufCon[80];
    Couleurs::blanc();
    CharToOemA(" La partie commence dans : ", bufCon);
    cout << bufCon << endl;
    Sleep(1000);
    cout << " 3" << endl;
    Sleep(1000);
    cout << " 2" << endl;
    Sleep(1000);
    cout << " 1" << endl;
    Sleep(1000);
}

// Vérifie que les coordonnées sont correctes avec le plateau
bool Regles::coordonneesCorrectes(int coord, int dim)
{
    char bufCon[80];
    bool coordCorrecte = false;

    if (coord < 0) // Coordonnée trop petite
    {
        Couleurs::rouge();
        CharToOemA(" La coordonnée doit être supérieure à 0.", bufCon);
        cout << bufCon << endl;
    }
    else if (coord > 50) // Coordonnée trop grande
    {
        Couleurs::rouge();
        CharToOemA(" La coordonnée doit être inférieur à 51.", bufCon);
        cout << bufCon << endl;
    }
    else if (coord > dim - 1) // Coordonnées supérieure au plateau
    {
        Couleurs::rouge();
        CharToOemA(" La coordonnée est plus grande que la plateau.", bufCon);
        cout << bufCon << endl;
    }
    else // La coordonnée est bonne
    {
        coordCorrecte = true;
    }

    return coordCorrecte;
}

// Démarre un nouveau tour
void Regles::nouveauTour()
{
    ++tour;
    system("cls");
    cout << " The Angel And Demon Game";
    Couleurs::gris();
    cout << " >> ";
    Couleurs::bleu();
    cout << tour << endl;
}

// Fait une pause à la fin du tour
void Regles::pause()
{
    char bufCon[80];
    Couleurs::blanc();
    CharToOemA(" Fin du tour.", bufCon);
    cout << bufCon << endl;
    Sleep(2000);
}

// Vérifie si l'ange remporte la partie
bool Regles::victoireAnge(int dim, string** plateau)
{
    bool victoire = false;
    char bufCon[80];

    for (int posX = 0; posX < dim; posX++)
    {
        for (int posY = 0; posY < dim; posY++)
        {
            if (plateau[posY][posX] == "O") // On cherche la position actuelle de l'ange
            {
                // On vérifie s'il touche un bord du plateau
                if (posX == 0) // Bordure left
                {
                    victoire = true;
                }
                else if (posY == 0) // Bordure top
                {
                    victoire = true;
                }
                else if (posX == dim - 1) // Bordure right
                {
                    victoire = true;
                }
                else if (posY == dim - 1) // Bordure bot
                {
                    victoire = true;
                }
                // Si ici alors pas de victoire
            }
        }
    }

    if (victoire == true) // Victoire !
    {
        Couleurs::blanc();
        CharToOemA(" L'ange remporte la partie en ", bufCon);
        cout << bufCon << tour << " tours." << endl;
    }

    return victoire;
}

// Vérifie si le démon remporte la partie
bool Regles::victoireDemon(int dim, string** plateau)
{
    bool victoire = true;
    char bufCon[80];
    int compteur = 0;

    for (int posX = 0; posX < dim; posX++)
    {
        for (int posY = 0; posY < dim; posY++)
        {
            if (plateau[posY][posX] == "O") // On cherche la position actuelle de l'ange
            {
                // On vérifie si toutes les cases aux alentours sont détruites
                // Parcours le tableau en fonction de la force
                for (int i = posX - force; i < posX + force * 2; i++)
                {
                    for (int j = posY - force; j < posY + force * 2; j++)
                    {
                        // Si une case est vide, c'est que le démon ne gagne pas
                        if (plateau[j][i] == " ")
                        {
                            compteur++;
                        }
                    }
                }
            }
        }
    }

    // Si une case est encore vide, alors pas de victoire
    if (compteur > 0)
    {
        victoire = false;
    }

    if (victoire == true) // Victoire !
    {
        Couleurs::blanc();
        CharToOemA(" Le démon remporte la partie en ", bufCon);
        cout << bufCon << tour << " tours." << endl;
    }

    return victoire;
}

// Fermeture du jeu
void Regles::fermeture()
{
    Couleurs::blanc();
    char bufCon[80];
    CharToOemA(" Le jeu se fermera dans 5 secondes.", bufCon);
    cout << "" << endl;
    cout << bufCon << endl;
    Sleep(1000);
    cout << " 5" << endl;
    Sleep(1000);
    cout << " 4" << endl;
    Sleep(1000);
    cout << " 3" << endl;
    Sleep(1000);
    cout << " 2" << endl;
    Sleep(1000);
    cout << " 1" << endl;
    Sleep(1000);
}

// Destructeur
Regles::~Regles()
{
}
