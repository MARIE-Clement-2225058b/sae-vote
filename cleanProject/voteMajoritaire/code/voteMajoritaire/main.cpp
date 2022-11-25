#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
// initialisation des vecteur string et unsigned
typedef vector<string> vecStr; // création d'un tableau de string 
typedef vector<unsigned> vecUInt; // création d'un tableau d'entier

// récupération des candiats
void recupCandidat (vecStr & tabCandi)
{
    string nomCandi; // création d'une variable de string
    tabCandi.push_back("Blanc"); // initialisation du premier candidat 
    while (true){
        getline(cin, nomCandi); // récupération du nom du candidat dans nomCandi
        if (nomCandi == "")break; // condition d'arrêt de la boucle si nomCandi est vide
        tabCandi.push_back(nomCandi); // ajout de nomCandi dans tabCandi
    }
}
// fonction d'affichage avec le nom des candidats et leurs score
template <typename Vect> // création de la variable Vect qui peut être n'importe quel type 
void affiche(const Vect & vote, const vecStr & tabCandi) 
{
    unsigned j = 0; // initialisation d'un entier j de valeur 0
    for (auto & i : vote)
    {
        cout << tabCandi[j] << " = "<< i << endl; // affichage du nom d'un candidat de tabCandi à la position j puis "=" et le nombre de vote du tableau vote à la position i
        ++j; // augmentation de l'entier j de +1
    }
}

// récupération des votes
void recupVote (vecUInt & tabVote, vecStr & tabVotant)
{
    string nomVotant, prenomVotant, buf; // création des variables nomVotant, prenomVotant, buf
    unsigned vote; // création de l'entier vote
    while (true)
    {
        getline(cin, nomVotant); // récupération du nom du votant dans nomVotant
        if (nomVotant == "")break; // condition d'arrêt si nomVotant est vide
        getline(cin,prenomVotant); // récupération du prenom du votant dans prenomVotant
        tabVotant.push_back(nomVotant + " " + prenomVotant); // ajout du nom et prénom du votant dans tabVotant
        cin >> vote; // récupération du vote
        tabVote.push_back(vote); // ajout du vote dans tabVote
        getline(cin,buf); // récupération 
    }
}

void voteFr (const vecStr & tabCandidatTour1, vecStr & tabCandidatTour2, const vecUInt & tabVote) 
{
    vecUInt tabScore (tabCandidatTour1.size(), 0); // création du tableau tabScore de taille tabCandidatTour1
    for (size_t i (0) ; i < tabVote.size() ; ++i)
        tabScore[tabVote[i]] += 1; // incrémentation de 1 de tabScore à l'indice tabVote[i]
    cout << "--- Score ---" << endl; // affichage "--- Score ---" puis saut de ligne 
    affiche(tabScore,tabCandidatTour1); // affichage score par candidats
    vecUInt tabScoreTmp = tabScore; // création de tabScoreTmp et copie tabScore vers tabScoreTmp
    vecUInt tabCandidatTri (tabScore.size(),0); // création du tableau tabCandidatTri de taille tabScore
    unsigned max = 1; // création de l'entier max de valeur 1
    for (size_t i (1) ; i < tabScore.size() ; ++i) 
    {
        max = 1; // initialisation de max à 1
        for (size_t j (2) ; j < tabScore.size() ; ++j) 
        {
            if (tabScoreTmp[j] > tabScoreTmp[max]) // si tabScoreTmp à l'indice j est supérieur à tabScoreTmp à l'indice max alors 
                max = j; // max vaut j
        }
        tabScoreTmp[max] = 0; // tabScoreTmp à l'indice max vaut 0
        tabCandidatTri[i] = max; // tabCandidatTri à l'indice i vaut max
    }
    cout << "--- Position ---" << endl; // affichage de "--- Position ---" puis saut de ligne 
    affiche(tabCandidatTri,tabCandidatTour1); // affichage de la position des candidats

    if (tabCandidatTour1.size() > 3) // si la taille de tabCandidatTour1 est supéreur à 3 alors
    {
        for (size_t i (0) ; i < 3 ; ++i) 
            tabCandidatTour2.push_back(tabCandidatTour1[tabCandidatTri[i]]); // ajout dans tabCandidatTour2 de la valeur de tabCandidatTour1 d'indice tabCandidatTri d'indice i
    }
    else
        cout << "Le gagnant est : " << tabCandidatTour2[tabCandidatTri[1]] << endl; // affichage de "Le gagnant est : " puis de la valeur de tabCandidatTour2 d'indice tabCandidatTri d'indice 1 puis saut de ligne   
}

int main()
{
    vecUInt tabVoteTour1, tabVoteTour2; // création des tableaux d'entier tabVoteTour1 et tabVoteTour2
    vecStr tabCandidatTour1, tabCandidatTour2, tabVotant; // création des tableaux de string tabCandidatTour1, tabCandidatTour2 et tabVotant
    // initialisation tour 1
    recupCandidat(tabCandidatTour1); // récupération des candidat dans tabCandidatTour1 pour le 1er tour 
    recupVote(tabVoteTour1, tabVotant); // récupération des votes dans tabVoteTour1 et des noms des votants dans tabVotant
    cout << "---- Tour 1 ----"<< endl; // affichage de "---- Tour 1 ----" puis saut de ligne 
    voteFr(tabCandidatTour1, tabCandidatTour2, tabVoteTour1); // résultat du tour 1
    // initialisation tour 2
    recupVote(tabVoteTour2, tabVotant); // récupération des votes du 2ème tour 
    cout << "---- Tour 2 ----"<< endl; // affichage de "---- Tour 2 ----" puis saut de ligne 
    voteFr(tabCandidatTour2, tabCandidatTour2, tabVoteTour2); // résultat du tour 2
}
