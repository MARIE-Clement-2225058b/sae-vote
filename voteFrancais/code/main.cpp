#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
//initialisation des vecteur string et unsigned
typedef vector<string> vecStr;
typedef vector<unsigned> vecUInt;

//récupération des candiats
void recupCandidat (vecStr & tabCandi){
    string nomCandi;
    while (true){
        getline(cin, nomCandi);
        if (nomCandi == "")break;
        tabCandi.push_back(nomCandi);
    }
}
//fonction d'affichage avec le nom des candidats et leurs score
template <typename Vect>
void affiche(const Vect & vote, const vecStr & tabCandi) {
    unsigned j = 0;
    for (auto & i : vote){
        cout << tabCandi[j] << " = "<< i << endl;
        ++j;
    }
}

//récupération des votes
void recupVote (vecUInt & tabVote, vecStr & tabVotant){
    string nomVotant, prenomVotant, buf;
    unsigned vote;
    while (true){
        getline(cin, nomVotant);
        if (nomVotant == "")break;
        getline(cin,prenomVotant);
        tabVotant.push_back(nomVotant + " " + prenomVotant);
        cin >> vote;
        tabVote.push_back(vote);
        getline(cin,buf);
    }
}

void voteFr (const vecStr & tabCandidatTour1, vecStr & tabCandidatTour2, const vecUInt & tabVote) {
    vecUInt tabScore (tabCandidatTour1.size(), 0);
    for (size_t i (0) ; i < tabVote.size() ; ++i)
        tabScore[tabVote[i]] += 1;
    cout << "--- Score ---" << endl;
    affiche(tabScore,tabCandidatTour1);//affichage score par candidats

    vecUInt tabScoreTmp = tabScore;
    vecUInt tabCandidatTri (tabScore.size(),0);
    unsigned max = 1;
    for (size_t i (1) ; i < tabScore.size() ; ++i) {
        max = 1;
        for (size_t j (2) ; j < tabScore.size() ; ++j) {
            if (tabScoreTmp[j] > tabScoreTmp[max]) max = j;
        }
        tabScoreTmp[max] = 0;
        tabCandidatTri[i] = max;
    }
    cout << "--- Position ---" << endl;
    affiche(tabCandidatTri,tabCandidatTour1);//affichage de la position des candidats

    if (tabCandidatTour1.size() > 3) {
        for (size_t i (0) ; i < 3 ; ++i)
            tabCandidatTour2.push_back(tabCandidatTour1[tabCandidatTri[i]]);
    }
    else
        cout << "Le gagnant est : " << tabCandidatTour2[tabCandidatTri[1]] << endl;
}

int main()
{
    vecUInt tabVoteTour1, tabVoteTour2;
    vecStr tabCandidatTour1, tabCandidatTour2, tabVotant;
    //initialisation tour 1
    recupCandidat(tabCandidatTour1);
    recupVote(tabVoteTour1, tabVotant);
    cout << "---- Tour 1 ----"<< endl;
    voteFr(tabCandidatTour1, tabCandidatTour2, tabVoteTour1);
    //initialisation tour 2
    recupVote(tabVoteTour2, tabVotant);
    cout << "---- Tour 2 ----"<< endl;
    voteFr(tabCandidatTour2, tabCandidatTour2, tabVoteTour2);
}
