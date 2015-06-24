#include "stdafx.h"

#include <Windows.h>
#include <iostream>
#include <string>
#include <queue>

#include "Plateau.h"
#include "Couleurs.h"
#include "Ange.h"

using namespace std;

// Constructeur
Plateau::Plateau()
{
    char bufCon[80];
    Couleurs::blanc();
    CharToOemA(" Bienvenu dans le jeu The Angel And Devil.", bufCon);
    cout << bufCon << endl;
    CharToOemA(" Vous devez commencé par régler les paramètres du jeu.", bufCon);
    cout << bufCon << endl;
    cout << "" << endl;
}

// Set dim
void Plateau::setDim()
{
    bool dimCorrect = false;
    char bufCon[80];

    // Vérification de la saisie de l'utilisateur
    while (dimCorrect == false)
    {
        userSetDim();

        if (this->userDim < 5) // dim trop petite
        {
            Couleurs::rouge();
            CharToOemA(" La dimension du plateau doit être supérieure à 5.", bufCon);
            cout << bufCon << endl;
        }
        else if (this->userDim >= 50) // dim trop grande
        {
            Couleurs::rouge();
            CharToOemA(" La dimension du plateau doit être inférieure à 50.", bufCon);
            cout << bufCon << endl;
        }
        else if (this->userDim % 2 == 0) // dim paire
        {
            Couleurs::rouge();
            CharToOemA(" La dimension du plateau doit être impaire.", bufCon);
            cout << bufCon << endl;
            Couleurs::vert();
            CharToOemA(" La dimension était de ", bufCon);
            cout << bufCon << this->userDim;
            this->userDim = this->userDim + 1;
            cout << " et est maintenant de " << this->userDim << "." << endl;
            dimCorrect = true;
        }
        else // dim impaire
        {
            Couleurs::vert();
            cout << " La dimension du plateau est de " << this->userDim << "." << endl;
            dimCorrect = true;
        }
    }

    this->dim = this->userDim;
}

void Plateau::setDim(int dim)
{
    this->dim = dim;
}

// Get dim
int Plateau::getDim()
{
    return this->dim;
}

// Saisir la dim
void Plateau::userSetDim()
{
    bool intCorrect = false;

    while (intCorrect == false)
    {
        try
        {
            Couleurs::jaune();
            cout << " Saisir la dimension du plateau : ";
            Couleurs::turquoise();
            cin >> this->userDim;

            if (!cin) // Gère l'erreur
            {
                throw logic_error(" La dimension n'est pas un nombre entier.");
            }

            // Tout est bon
            intCorrect = true;
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

// Création d'un plateau
void Plateau::creationPlateau()
{
    // Création du plateau en deux dim
    this->plateauStr = new string *[this->dim];

    for (int i = 0; i < this->dim; i++)
    {
        this->plateauStr[i] = new string[this->dim];
    }

    // Initialise les cases du tableau par des espaces (évite un bug d'affichage)
    for (int x = 0; x < this->dim; x++)
    {
        for (int y = 0; y < this->dim; y++)
        {
            this->plateauStr[x][y] = ' ';
        }
    }

    Couleurs::vert();
    char bufCon[80];
    CharToOemA(" Le plateau a était correctement initialisé.", bufCon);
    cout << bufCon << endl;
}

// Place l'ange a la case initiale
void Plateau::angePlacement()
{
    // Il faut calculer l'emplacement de l'ange
    int dimCp = this->dim;
    dimCp = dimCp - 1;
    // On le divise par deux pour obtenir le centre
    dimCp = dimCp / 2;
    // On place l'ange
    Ange unAnge;
    unAnge.placerPion(dimCp, dimCp, this->plateauStr, dim);

    Couleurs::vert();
    char bufCon[80];
    CharToOemA(" Un ange a était ajouté au centre du plateau.", bufCon);
    cout << bufCon << endl;
}

// Affiche le plateau
void Plateau::affichagePlateau()
{
    cout << endl;
    string quadrillage;
    string coords = "    ";

    // Ligne de coordonnées en Y
    for (int nbColY = 0; nbColY < this->dim; nbColY++)
    {
        if (nbColY > 10)
        {
            coords = coords + to_string(nbColY);
        }
        else
        {
            coords = coords + to_string(nbColY) + " ";
        }
    }

    // Affiche le tableau
    Couleurs::rose();
    cout << coords << endl;

    for (int i = 0; i < this->dim; i++)
    {
        // Affiche une ligne de quadrillage
        quadrillage = quadrillagePlateau();
        Couleurs::gris();
        cout << "   " << quadrillage << endl;

        // Affiche le tableau case par case
        for (int j = 0; j < this->dim; j++)
        {
            if (j == 0) // Seulement pour la première ligne
            {
                Couleurs::rose();
                cout << " " << i << "  ";
            }

            Couleurs::blanc();
            cout << this->plateauStr[i][j] << " ";
        }

        cout << endl;
    }

    Couleurs::gris();
    cout << "   " << quadrillage << endl;
    cout << endl;
}

// Création du quadrillage du plateau
string Plateau::quadrillagePlateau()
{
    string quadrillage;
    int colonnes = this->dim + 1;

    // Détermine la taille de la ligne
    for (int i = 0; i < colonnes; i++)
    {
        quadrillage = quadrillage + "+ ";
    }

    return quadrillage;
}

// Get plateau
string** Plateau::getPlateau()
{
    return this->plateauStr;
}

// Agrandir plateau
void Plateau::agrandirPlateau()
{
    int oldDim = dim;
    char bufCon[80];

    // Augmente la dim du plateau (+2)
    dim = dim + 2;

    // Création d'un tableau avec les nouvelles dim
    string** plateauCp = new string *[dim];
    for (int i = 0; i < dim; i++)
    {
        plateauCp[i] = new string[dim];
    }

    // Ajoute les valeurs par défaut
    for (int x = 0; x < dim; x++)
    {
        for (int y = 0; y < dim; y++)
        {
            plateauCp[x][y] = " ";
        }
    }

    // Ajoute les valeurs de l'ancien plateau dans le nouveau plateau
    for (int x = 0; x < oldDim; x++)
    {
        for (int y = 0; y < oldDim; y++)
        {
            plateauCp[x + 1][y + 1] = plateauStr[x][y];
        }
    }

    // Supprime l'ancien tableau
    for (int x = 0; x < oldDim; x++)
    {
            delete[] plateauStr[x];
    }

    delete[] plateauStr;

    // ancien tableau = nouveau tableau
    plateauStr = plateauCp;

    Couleurs::vert();
    CharToOemA(" Le démon agrandit le tableau.", bufCon);
    cout << bufCon << endl;
}

// Destructeur
Plateau::~Plateau()
{
}
