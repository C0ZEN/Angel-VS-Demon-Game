#pragma once

class Plateau
{
private:

    int dim;
    int userDim;
    std::string **plateauStr;

public:

    // Constructeur
    Plateau();

    // Set dim
    void setDim();
    void setDim(int dim);

    // Get dim
    int getDim();

    // Saisir la dim
    void userSetDim();

    // Création d'un plateau
    void creationPlateau();

    // Place l'ange a la case initiale
    void  angePlacement();

    // Affiche le plateau
    void affichagePlateau();

    // Création du quadrillage du plateau
    std::string quadrillagePlateau();

    // Get plateau
    std::string** getPlateau();

    // Agrandir plateau
    void agrandirPlateau();

    // Destructeur
    virtual ~Plateau();
};

