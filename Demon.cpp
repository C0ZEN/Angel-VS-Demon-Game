#include "stdafx.h"

#include <Windows.h>
#include <iostream>
#include <string>

#include "Demon.h"
#include "Couleurs.h"
#include "Plateau.h"

using namespace std;

// Constructeur
Demon::Demon()
{
}

// Demande le nom du joueur
void Demon::setNomJoueur(string nomAnge)
{
    bool nomCorrect = false;
    char bufCon[80];

    while (nomCorrect == false)
    {
        // Demande le nom du démon
        Couleurs::jaune();
        CharToOemA(" Saisir le nom du démon : ", bufCon);
        cout << bufCon;

        Couleurs::turquoise();
        cin >> this->nomJoueur;

        // Vérifie si le nom est conforme, return true si oui
        nomCorrect = Joueurs::nomCorrect(nomJoueur);

        if (this->nomJoueur == nomAnge) // Si le nom est le même pour les deux joueurs
        {
            Couleurs::rouge();
            CharToOemA(" Le nom du démon ne peut pas être identique à celui de l'ange.", bufCon);
            cout << bufCon << endl;
            nomCorrect = false;
        }
    }

    Couleurs::vert();
    CharToOemA(" Le nom du démon est ", bufCon);
    cout << bufCon << nomJoueur << "." << endl;
    cout << "" << endl;
}

// Déplacement
void Demon::deplacement()
{
    Couleurs::vert();
    char bufCon[80];
    CharToOemA(" Le démon détruit la case [", bufCon);
    cout << bufCon << this->x << "," << this->y << "]." << endl;
}

// Placer pion
void Demon::placerPion(int x, int y, string** plateau, int dim)
{
    // Place un X (case détruire) à la postion donnée
    // Il faut inverser x et y
    plateau[y][x] = "X";
}

// Vérifie que le point peut être posé là
bool Demon::pionBienPlacer(int x, int y, int dim, string** plateau)
{
    bool bon = false;
    char bufCon[80];

    if (plateau[y][x] == "X") // Si la case est déjà détruite
    {
        Couleurs::rouge();
        CharToOemA(" La case est déjà détruite.", bufCon);
        cout << bufCon << endl;
    }
    else if (plateau[y][x] == "O") // Si la case est occupé par l'ange
    {
        Couleurs::rouge();
        CharToOemA(" L'ange occupe déjà cette case.", bufCon);
        cout << bufCon << endl;
    }
    else // Le placement est possible
    {
        bon = true;
    }

    return bon;
}

// Demande au démon ce qu'il vaut faire
void Demon::choixCoup(Plateau &plateauObj)
{
    bool intCorrect = false;
    char bufCon[80];
    int dim = plateauObj.getDim();
    string** plateau = plateauObj.getPlateau();
    int choix;

    while (intCorrect == false)
    {
        try
        {
            Couleurs::rose();
            cout << " " << this->nomJoueur;
            Couleurs::gris();
            cout << " >> ";
            Couleurs::jaune();
            CharToOemA("Entrez [1] pour détruire une case ou [2] pour agrandir le plateau : ", bufCon);
            cout << bufCon;
            Couleurs::turquoise();
            cin >> choix;

            if (!cin) // Gère l'erreur
            {
                CharToOemA(" La coordonnée x n'est pas un nombre entier.", bufCon);
                throw logic_error(bufCon);
            }

            if (choix == 1) // On appel la méthode pour détruire un pion
            {
                choisirCoords(dim, plateau);
                intCorrect = true;
            }
            else if (choix == 2) // On appel la méthode pour agrandir le plateau
            {
                plateauObj.agrandirPlateau();
                intCorrect = true;
            }
        }
        catch (const exception & e) // Affiche l'erreur
        {
            Couleurs::rouge();
            cerr << e.what() << endl;
            cin.sync();
            cin.clear();
        }
    }
}

// Destructeur
Demon::~Demon()
{
}
