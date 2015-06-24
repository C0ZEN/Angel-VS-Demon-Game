#include "stdafx.h"

#include <Windows.h>
#include <iostream>

#include "Plateau.h"
#include "Regles.h"
#include "Ange.h"
#include "Demon.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
    // Titre de la console
    SetConsoleTitleA("The angel and devil game");
    // Récupère la fenêtre de la console
    HWND console = GetConsoleWindow();
    // Déclare un rectangle
    RECT rect;
    // Récupère les dimensions de la console
    GetWindowRect(console, &rect);
    // Déplace la fenêtre avec les nouvelles dimensions
    int height = 800;
    int width = 600;
    MoveWindow(console, rect.left, rect.top, height, width, TRUE);
    // Efface l'écran
    system("cls");

    // Initialise le plateau et l'affiche
    Plateau creationPlateau;
    creationPlateau.setDim();
    creationPlateau.creationPlateau();
    creationPlateau.angePlacement();
    creationPlateau.affichagePlateau();

    // Règle les paramètres pour l'ange
    Regles::forceAnge();
    Ange joueurAnge;
    joueurAnge.setNomJoueur();
    string nomAnge = joueurAnge.getNomJoueur();

    // Règles les paramètres pour le démon
    Demon joueurDemon;
    joueurDemon.setNomJoueur(nomAnge);

    // Début de la partie
    Regles::debutJeu();
    int dim;
    bool victoire = false;
    dim = creationPlateau.getDim();
    string** plateau;
    plateau = creationPlateau.getPlateau();

    // Tant que personne ne gagne
    while (victoire == false)
    {
        // Tour de l'ange
        Regles::nouveauTour();
        creationPlateau.affichagePlateau();
        joueurAnge.choisirCoords(dim, plateau);
        creationPlateau.affichagePlateau();
        victoire = Regles::victoireAnge(dim, plateau);

        // Tour du démon
        while (victoire == false)
        {
            joueurDemon.choixCoup(creationPlateau);
            dim = creationPlateau.getDim();
            plateau = creationPlateau.getPlateau();
            creationPlateau.affichagePlateau();
            victoire = Regles::victoireDemon(dim, plateau);

            if (victoire == false)
            {
                Regles::pause();
            }
            break;
        }
    }

    Regles::fermeture();

	return EXIT_SUCCESS;
}
