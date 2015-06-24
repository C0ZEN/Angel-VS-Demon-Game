#pragma once

class Joueurs
{
protected:

    std::string nomJoueur;
    int x;
    int y;

public:

    // Constructeur
    Joueurs();

    // Vérifie si le nom du joueur est correct
    bool nomCorrect(std::string nom);

    // Demande au joueur de placer un pion
    void choisirCoords(int dim, std::string** plateau);

    // Get nomJoueur
    std::string getNomJoueur();

    // Déplacement
    void virtual deplacement();

    // Placer pion
    void virtual placerPion(int x, int y, std::string** plateau, int dim);

    // Vérifie que le point peut être posé là
    bool virtual pionBienPlacer(int x, int y, int dim, std::string** plateau);

    // Destructeur
    virtual ~Joueurs();
};

