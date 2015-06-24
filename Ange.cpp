#include "stdafx.h"

#include <Windows.h>
#include <iostream>
#include <string>

#include "Ange.h"
#include "Plateau.h"
#include "Joueurs.h"
#include "Couleurs.h"
#include "Regles.h"

using namespace std;

// Constructeur
Ange::Ange()
{
}

// Place un ange sur le plateau
void Ange::placerPion(int x, int y, string** plateau, int dim)
{
    // Supprime l'ancienne position de l'ange (car déplacement)
    for (int posX = 0; posX < dim; posX++)
    {
        for (int posY = 0; posY < dim; posY++)
        {
            // Cherche la case ou se situe l'ange
            if (plateau[posX][posY] == "O")
            {
                // La supprime par du vide
                plateau[posX][posY] = " ";
            }
        }
    }

    // Place un O (ange) à la postion donnée
    // Il faut inverser x et y
    plateau[y][x] = "O";
}

// Demande le nom du joueur
void Ange::setNomJoueur()
{
    bool nomCorrect = false;
    char bufCon[80];

    while (nomCorrect == false)
    {
        // Demande le nom de l'ange
        Couleurs::jaune();
        CharToOemA(" Saisir le nom de l'ange : ", bufCon);
        cout << bufCon;

        Couleurs::turquoise();
        cin >> nomJoueur;

        // Vérifie si le nom est conforme, return true si oui
        nomCorrect = Joueurs::nomCorrect(nomJoueur);
    }

    Couleurs::vert();
    CharToOemA(" Le nom de l'ange est ", bufCon);
    cout << bufCon << nomJoueur << "." << endl;
}

// Déplacement
void Ange::deplacement()
{
    Couleurs::vert();
    char bufCon[80];
    CharToOemA(" L'ange se déplace aux coordonnées [", bufCon);
    cout << bufCon << this->x << "," << this->y << "]." << endl;
}

// Vérifie que le pion peut être posé là
bool Ange::pionBienPlacer(int x, int y, int dim, string** plateau)
{
    bool bon = true;
    char bufCon[80];
    int force = Regles::getForce();

    if (plateau[y][x] == "X") // Si la case est déjà détruite
    {
        Couleurs::rouge();
        CharToOemA(" La case est détruite.", bufCon);
        cout << bufCon << endl;
        bon = false;
    }
    else if (plateau[y][x] == "O") // Si la case est occupé par l'ange
    {
        Couleurs::rouge();
        CharToOemA(" L'ange occupe déjà cette case.", bufCon);
        cout << bufCon << endl;
        bon = false;
    }

    // Il faut vérifier les déplacement de l'ange en fonction de sa force
    for (int posX = 0; posX < dim; posX++)
    {
        for (int posY = 0; posY < dim; posY++)
        {
            if (plateau[posY][posX] == "O") // On cherche la position actuelle de l'ange
            {
                // On passe aux vérifications
                Couleurs::rouge();
                CharToOemA(" L'ange ne respecte pas la force (", bufCon);

                if (y < posY - force) // Position Top
                {
                    bon = false;
                    cout << bufCon << force << ")." << endl;
                }
                else if (y > posY + force) // Position Bot
                {
                    bon = false;
                    cout << bufCon << force << ")." << endl;
                }
                else if (x < posX - force) // Position Left
                {
                    bon = false;
                    cout << bufCon << force << ")." << endl;
                }
                else if (x > posX + force) // Position Right
                {
                    bon = false;
                    cout << bufCon << force << ")." << endl;
                }
                // Si on arrive ici, tout est bon
            }
        }
    }

    return bon;
}

// Destructeur
Ange::~Ange()
{
}
