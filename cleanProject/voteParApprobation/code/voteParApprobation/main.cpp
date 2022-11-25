#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

typedef vector<string> vecStr;
typedef vector<vector<string>> matStr;

void recupCandidat (vecStr & tabCandidat);
void recupVote (vecStr & tabNom, matStr & matVote);
unsigned indiceDuPlusGrand (vector<unsigned> & tabEntierNaturel);
void voteAprobation (matStr & matVote, vecStr & tabCandidat, vecStr & tabNomPrenom, vector<unsigned> tabCandidatCompteur);

unsigned indiceDuPlusGrand (vector<unsigned> & tabEntierNaturel) {
    unsigned nbLePlusGrand(0);
    for (size_t i(1); i < tabEntierNaturel.size(); ++i)
        if (tabEntierNaturel[nbLePlusGrand] > tabEntierNaturel[i]) nbLePlusGrand = i; // récupère l'indice du plus grand dans le vecteur
    return nbLePlusGrand;
}

void recupCandidat (vecStr & tabCandidat) {
    string nomCandidat;
    while (true) {
        getline(cin, nomCandidat); // récupère le nom du candidat
        if (nomCandidat == "") break; // si mon nom de candidat est vide on sort
        tabCandidat.push_back(nomCandidat); // ajout du candidat dans 'tabCandidat'
    }
}

void recupVote (vecStr & tabNom, matStr & matVote)
{
    string nomVotant, prenomVotant, vote, debug;
    while (true) {
        getline(cin, nomVotant); // récupère le nom du votant
        if (cin.eof()) break; // si on arrive à la fin du fichier sortir
        getline(cin, prenomVotant); // récupère le prenom du votant
        tabNom.push_back(nomVotant + " " + prenomVotant); // ajoute le 'nom prenom' dans le tableau tabNom
        for (size_t i(0); i < matVote.size(); ++i) { // récupère les votes 1 par un sous forme de string 'oui' ou 'non'
            cin >> vote;
            matVote[i].push_back(vote); // ajout des votes dans la matrice 'matVote' sous forme de string
        }
        getline(cin, debug); // pour aller à la ligne dans le fichier et nettoyer l'entrée 'cin'
    }
}

void voteAprobation (matStr & matVote, vecStr & tabCandidat, vecStr & tabNomPrenom, vector<unsigned> tabCandidatCompteur)
{
    recupCandidat(tabCandidat); // Récupère les candidats grâce à la fonction faite précèdemment qui les prend du fichier d'entrée et les place dans le tableau de candidat pour pouvoir les manipuler ensuite
    recupVote(tabNomPrenom, matVote); // Pareil que pour les candidat mais pour les vote les informations liés aux votes (nom + prenom / vote)
    for (size_t i(0); i < matVote[0].size(); ++i) // Parcours la matrice de 0 à la fin
        for (size_t j(0); j < tabCandidat.size(); ++j) // Boucle de 0 au nombre de candidats
        {
            if (matVote[j][i] == "oui") tabCandidatCompteur[j]+=1; // Incrémente le compteur du candidat si l'utilisateur a rentrer le nom du candidat, ce qui correspond à dire qu'il approuve le candidat
        }
    unsigned indiceVainqueur = indiceDuPlusGrand(tabCandidatCompteur); // Récupère l'indice du vainqueur dans le tableau des compteur pour identifier le nom du candidat qui a le plus de vote
    string vainqueur = tabCandidat[indiceVainqueur]; // Récupère le nom du candidat qui a le plus de vote
    for (size_t i (0) ; i < tabCandidat.size() ; ++i)
        cout << tabCandidat[i] << " : " << tabCandidatCompteur[i] << endl;
    cout << endl << "Le vainqueur est : " << vainqueur << " !"; // Saute une ligne puis affiche la vainqueur
}

int main()
{
    vecStr tabCandidat, tabNomPrenom; // Initialise de plusieurs vecteur de string pour stocker les candidats et les nom + prénom
    recupCandidat(tabCandidat); // Récupère les candidat dans le fichier d'entrée
    vector<unsigned> tabCandidatCompteur (tabCandidat.size()); // Initialise un tableau d'entier naturel pour compter les scores des candidats
    matStr matVote (tabCandidat.size()); // Initialise une matrice de string et initialise ça taille à la taille du tableau des candidat pour éviter un débordement de tableau
    recupVote(tabNomPrenom, matVote); // Récupère les vote et les nom + prénom des candidats
    voteAprobation(matVote, tabCandidat, tabNomPrenom, tabCandidatCompteur); // Programme principal du vote par aprobation, calcul le résultat en fonction de toutes les données récupérer
    return 0;
}
