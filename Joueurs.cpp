#include "stdafx.h"

#include <Windows.h>
#include <iostream>
#include <string>

#include "Joueurs.h"
#include "Couleurs.h"
#include "Regles.h"

using namespace std;

// Constructeur
Joueurs::Joueurs()
{
}

// Vérifie si le nom du joueur est correct
bool Joueurs::nomCorrect(string nom)
{
    char bufCon[80];
    bool nomCorrect = false;

    if (nom.length() < 1) // Nom trop court
    {
        Couleurs::rouge();
        CharToOemA(" Le nom du joueur est trop court.", bufCon);
        cout << bufCon << endl;
    }
    else if (nom.length() > 30) // Nom trop long
    {
        Couleurs::rouge();
        CharToOemA(" Le nom du joueur est trop long.", bufCon);
        cout << bufCon << endl;
    }
    else // Le nom est correct
    {
        nomCorrect = true;
    }

    return nomCorrect;
}

// Demande au joueur de placer un pion
void Joueurs::choisirCoords(int dim, string** plateau)
{
    char bufCon[80];
    bool intCorrect = false;

    while (intCorrect == false)
    {
        try
        {
            Couleurs::rose();
            cout << " " << this->nomJoueur;
            Couleurs::gris();
            cout << " >> ";
            Couleurs::jaune();
            CharToOemA("Placer votre pion en x : ", bufCon);
            cout << bufCon;
            Couleurs::turquoise();
            cin >> this->x;

            if (!cin) // Gère l'erreur
            {
                CharToOemA(" La coordonnée x n'est pas un nombre entier.", bufCon);
                throw logic_error(bufCon);
            }

            // Si c'est un return true alors tout est bon
            intCorrect = Regles::coordonneesCorrectes(this->x, dim);
        }
        catch (const exception & e) // Affiche l'erreur
        {
            Couleurs::rouge();
            cerr << e.what() << endl;
            cin.sync();
            cin.clear();
        }
    }

    // La coordonnée x est bonne
    intCorrect = false;

    while (intCorrect == false)
    {
        try
        {
            Couleurs::rose();
            cout << " " << this->nomJoueur;
            Couleurs::gris();
            cout << " >> ";
            Couleurs::jaune();
            CharToOemA("Placer votre pion en y : ", bufCon);
            cout << bufCon;
            Couleurs::turquoise();
            cin >> this->y;

            if (!cin) // Gère l'erreur
            {
                CharToOemA(" La coordonnée y n'est pas un nombre entier.", bufCon);
                throw logic_error(bufCon);
            }

            // Si c'est un return true alors tout est bon
            intCorrect = Regles::coordonneesCorrectes(this->y, dim);
        }
        catch (const exception & e) // Affiche l'erreur
        {
            Couleurs::rouge();
            cerr << e.what() << endl;
            cin.sync();
            cin.clear();
        }
    }

    bool placementBon = pionBienPlacer(this->x, this->y, dim, plateau);

    if (placementBon == true)
    {
        deplacement();
        placerPion(this->x, this->y, plateau, dim);
    }
    else
    {
        choisirCoords(dim, plateau);
    }
}

// Déplacement
void Joueurs::deplacement()
{
    // Méthode override
}

// Get nomJoueur
string Joueurs::getNomJoueur()
{
    return this->nomJoueur;
}

// Placer pion
void Joueurs::placerPion(int x, int y, std::string** plateau, int dim)
{
    // Méthode override
}

// Vérifie que le point peut être posé là
bool Joueurs::pionBienPlacer(int x, int y, int dim, string** plateau)
{
    // Méthode override
    return false;
}

// Destructeur
Joueurs::~Joueurs()
{
}
