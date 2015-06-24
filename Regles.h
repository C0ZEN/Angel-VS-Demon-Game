#pragma once

class Regles
{
private:

    static int force;
    static int tour;

public:

    // Constructeur
    Regles();

    // Demande la force de l'ange
    static void forceAnge();

    // Get force
    static int getForce();

    // Commence la partie
    static void debutJeu();

    // Vérifie que les coordonnées sont correctes avec le plateau
    static bool coordonneesCorrectes(int coord, int dim);

    // Démarre un nouveau tour
    static void nouveauTour();

    // Fait une pause à la fin du tour
    static void pause();

    // Vérifie si l'ange remporte la partie
    static bool victoireAnge(int dim, std::string** plateau);

    // Vérifie si le démon remporte la partie
    static bool victoireDemon(int dim, std::string** plateau);

    // Fermeture du jeu
    static void fermeture();

    // Destructeur
    virtual ~Regles();
};

