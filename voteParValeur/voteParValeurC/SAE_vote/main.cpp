#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<string> vecStr;
typedef vector<vector<unsigned>> matUInt;

//Création d'une fonction générique d'affichage de tableau
template <typename type>
void affichVector (const vector <type> & V)
{
    for (unsigned i(0) ; i < V.size() ; ++i)
        cout << V[i] << " " ;
    cout << endl ;
}

//Création d'une fonction permettant de trouver l'indice d'un élément dans un tableau, renvoie la taille sinon
unsigned findIndex (const vector<unsigned> & vect , const unsigned & val)
{
    for (unsigned i(0) ; i < vect.size() ; ++i)
        if (vect[i] == val)
            return i ;
    return vect.size() ;
}

//Récupération de la liste des candidats dans le fichier d'entrée
void recupCandidat (vecStr & tabCandidat)
{
    string nomCandidat ;
    while (true)
    {
        getline(cin , nomCandidat) ;
        if (nomCandidat == "") break ;
        tabCandidat.push_back(nomCandidat) ;
    }
}

//Récupération des votes de chaque votant
void recupVote (vecStr & tabNomVotant , matUInt & tabVote)
{
    string nomPrenom ;
    string Buf ;
    unsigned vote ;
    while (true)
    {
        getline(cin , nomPrenom) ;
        if (cin.eof()) break ;
        tabNomVotant.push_back(nomPrenom) ;
        for (unsigned i(0) ; i < tabVote.size() ; ++i)
        {
            cin >> vote ;
            tabVote[i].push_back(vote) ;
        }
        getline(cin , Buf) ;
    }
}

//Fonction de vote associée
void voteParValeur (const matUInt & votes , const vecStr & tabCandidat)
{
    //Déclaration du tableau accueillant les notes de chaque candidat
    vector<unsigned> notes (votes.size() , 0) ;
    //Deux boucles imbriquées pour récupérer l'intégralité des votes donnés et les additionner pour obtenir les notes en question
    for (unsigned i(0) ; i < votes.size() ; ++i)
    {
        for (unsigned j(0) ; j < votes[i].size() ; ++j)
        {
            notes [i] += votes[i][j] ;
        }
    }
    //Affichage des candidats ainsi que leur score
    for (unsigned i(0) ; i < tabCandidat.size() ; ++i)
        cout << tabCandidat[i] << " : " << notes[i] << endl ;
    //Récupération de la plus grande valeur du tableau
    int max = *max_element(notes.begin(), notes.end());
    //Recherche de l'indice de l'élément maximum dans le tableau de notes
    unsigned vainq = findIndex(notes, max) ;
    //Affichage du vainquer
    cout << "Le vainqueur est : " <<tabCandidat[vainq] << endl ;

}

int main()
{
    vecStr candidats ;
    vecStr votants ;
    recupCandidat(candidats) ;
    matUInt votes (candidats.size()) ;
    recupVote(votants , votes) ;
    voteParValeur(votes , candidats) ;
}
