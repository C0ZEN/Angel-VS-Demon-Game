#pragma once

#include "Joueurs.h"
#include "Plateau.h"

class Demon : public Joueurs
{
public:

    // Constructeur
    Demon();

    // Demande le nom du joueur
    void setNomJoueur(std::string nomAnge);

    // Déplacement
    void deplacement() override;

    // Placer pion
    void placerPion(int x, int y, std::string** plateau, int dim) override;

    // Vérifie que le point peut être posé là
    bool pionBienPlacer(int x, int y, int dim, std::string** plateau) override;

    // Demande au démon ce qu'il vaut faire
    void choixCoup(Plateau &plateauObj);

    // Destructeur
    virtual ~Demon();
};

