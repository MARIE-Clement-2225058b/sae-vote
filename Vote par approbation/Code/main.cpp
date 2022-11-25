#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

typedef vector<string> vecStr;
typedef vector<vector<string>> matStr;

void recupCandidat (vecStr & tabCandidat);
void recupVote (vecStr tabNom, matStr matVote);
unsigned indiceDuPlusGrand (vector<unsigned> tabEntierNaturel);
void voteAprobation ();

unsigned indiceDuPlusGrand (vector<unsigned> tabEntierNaturel)
{
    unsigned nbLePlusGrand(0);
    for (size_t i(0); i < tabEntierNaturel.size(); ++i)
        if (tabEntierNaturel[nbLePlusGrand] > tabEntierNaturel[i+1]) nbLePlusGrand = tabEntierNaturel[i];
    return nbLePlusGrand;
}
void recupCandidat (vecStr & tabCandidat)
{
    string nomCandidat;
    while (true)
    {
        getline(cin, nomCandidat);
        if (nomCandidat == "") break;
        cout << nomCandidat << endl;
        tabCandidat.push_back(nomCandidat);
    }
}

void recupVote (vecStr tabNom, matStr matVote)
{
    string nomVotant, prenomVotant, nomPrenom, vote, debug;
    while (true)
    {
        getline(cin, nomVotant);
        if (cin.eof()) break;
        getline(cin, prenomVotant);
        nomPrenom = nomVotant + " " + prenomVotant;
        cout << nomPrenom << endl;
        tabNom.push_back(nomPrenom);
        for (size_t i(0); i < matVote.size(); ++i)
        {
            cin >> vote;
            cout << vote << endl;
            matVote[i].push_back(vote);
        }
        getline(cin, debug);
    }
}

void voteAprobation (matStr & matVote, vecStr & tabCandidat, vecStr & tabNomPrenom, vector<unsigned> tabCandidatCompteur)
{
    // Initialise une matrice pour contenir les vote en fonction du candidat, elle est vide
    // Initialise un vecteur (tableau) pour contenir respectivement les candidats et les nom + prenom des votant, ils sont vide
    // Initialise d'entier naturel pour stocker le nombres des votes de chacuns des candidats
    unsigned nbCandidat = tabCandidat.size(); // Stock dans une variable le nombre de candidat, ça veux dire que le programme est censé fonctionner pour tous nombres de candidats
    recupCandidat(tabCandidat); // Récupère les candidats grâce à la fonction faite précèdemment qui les prend du fichier d'entrée et les place dans le tableau de candidat pour pouvoir les manipuler ensuite
    recupVote(tabNomPrenom, matVote); // Pareil que pour les candidat mais pour les vote les informations liés aux votes (nom + prenom / vote)
    for (size_t i(0); i < matVote[0].size(); ++i) // Parcours la matrice de 0 à la fin
        for (size_t j(0); j < nbCandidat; ++j) // Boucle de 0 au nombre de candidats
        {
            if (matVote[j][i] == "oui") ++tabCandidatCompteur[j]; // Incrémente le compteur du candidat si l'utilisateur a rentrer le nom du candidat, ce qui correspond à dire qu'il approuve le candidat
        }
    unsigned indiceVainqueur = indiceDuPlusGrand(tabCandidatCompteur); // Récupère l'indice du vainqueur dans le tableau des compteur pour identifier le nom du candidat qui a le plus de vote
    string vainqueur = tabCandidat[indiceVainqueur]; // Récupère le nom du candidat qui a le plus de vote
    cout << endl << "Le vainqueur est : " << vainqueur << " !"; // Saute une ligne puis affiche la vainqueur
}

int main()
{
    vecStr tabCandidat, tabNomPrenom;
    vector<unsigned> tabCandidatCompteur;

    recupCandidat(tabCandidat);
    matStr matVote (size(tabCandidat));
    recupVote(tabNomPrenom, matVote);
    voteAprobation(matVote, tabCandidat, tabNomPrenom, tabCandidatCompteur);
    return 0;
}
