#pragma once

#include "Joueurs.h"

class Ange : public Joueurs
{
public:

    // Constructeur
    Ange();

    // Place un ange sur le plateau
    void placerPion(int x, int y, std::string** plateau, int dim) override;

    // Demande le nom du joueur
    void setNomJoueur();

    // Déplacement
    void deplacement() override;

    // Vérifie que le pion peut être posé là
    bool pionBienPlacer(int x, int y, int dim, std::string** plateau) override;

    // Destructeur
    virtual ~Ange();
};
