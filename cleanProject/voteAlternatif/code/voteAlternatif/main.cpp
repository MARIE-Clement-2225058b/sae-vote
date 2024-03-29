#include <iostream>
#include <vector>

using namespace std;

typedef vector<string> vecStr;
typedef vector<vector<string>> matStr;
typedef vector<vector<unsigned>> matUInt;


//______________________Signature fonction et procedure______________________//

void recupCandidat (vecStr & tabCandidat);
void recupVote (vecStr & tabNomVotant, matStr & matVote, const vecStr & tabCandidat);



vector<vector<string>> depouiller (vector<vector<string>> & scrutin, vector<string> & reference);
vector<unsigned> compterNbDeVotes (const vector<vector<string>> & scrutin, const vector<string> & reference);
bool majoriteabsolue (const vector<unsigned> & nbvotes, const unsigned & indice);
vector<string> & supprimer (vector<string> & Vstring, const unsigned & indiceElement);
vector<vector<string>> & supprimer (vector<vector<string>> & scrutin, const string & candidatElimine);
string candidatAEliminer (vector<unsigned> & nbvotes, vector<string> & reference);
unsigned indiceCandidat (const vector<string> & bulletin, const string & candidat);


//______________________Fonction et procedure______________________//


//______________________Recupere les entrer______________________//

void recupCandidat (vecStr & tabCandidat) {
    string nomCandidat;
    while (true) {
        getline(cin, nomCandidat);
        if (nomCandidat == "") break;
        cout << nomCandidat << endl;
        tabCandidat.push_back(nomCandidat);
    }
}

void recupVote (vecStr & tabNomVotant, matStr & matVote, const vecStr & tabCandidat) {
    string nomVotant, prenomVotant, nomPrenom;
    string Buf;
    unsigned vote;
    string conv;
    vecStr bulletin (tabCandidat.size());
    while (true) {
        getline(cin, nomVotant);
        if (cin.eof()) break;
        getline(cin, prenomVotant);
        nomPrenom = nomVotant + " " + prenomVotant;
        tabNomVotant.push_back(nomPrenom);
        for (size_t i (0); i < tabCandidat.size() ; ++i) {
            cin >> vote;
            conv = tabCandidat[vote-1];
            bulletin[i] = conv;
        }
        matVote.push_back(bulletin);
        getline(cin, Buf);
    }
}


//______________________Systeme de vote______________________//

vector<vector<string>> depouiller (vector<vector<string>> & scrutin, vector<string> & reference)
{
    cout << endl << "debut du tour" << endl;
    vector<unsigned> nbvotes = compterNbDeVotes(scrutin, reference); // recupere le nb de vote par candiat
    unsigned cpt = 0;
    while(true)
    {
        // majorité
        if (reference.size() == cpt) break;
        cout << reference[cpt] << " : ";
        if (majoriteabsolue(nbvotes, cpt)) // etat trivial
        {
            cout << reference[cpt] << " remporte le vote à la majorité absolue" << endl;
            return scrutin;
        }
        ++cpt;
    }
    string candidatElimine = candidatAEliminer(nbvotes, reference);
    cout << "le candidat " << candidatElimine << " est éliminé" << endl;
    scrutin = supprimer(scrutin, candidatElimine); // supprime le candidat elimine
    reference = supprimer(reference, indiceCandidat(reference, candidatElimine)); // supprime le candidat elimine
    cout << "tour suivant" << endl;
    depouiller (scrutin, reference); // appel recursif
    return scrutin;
}

vector<unsigned> compterNbDeVotes (const vector<vector<string>> & scrutin, const vector<string> & reference)
{
    vector<unsigned> nbvotes (reference.size(),0);
    for (unsigned i=0; i < reference.size(); ++i){ // parcourt reference
        for (unsigned j=0; j < scrutin.size(); ++j){ // parcour la liste de bulletin
            if (reference[i] == scrutin[j][0]){ // compare seulement avec le premier element de chaque bulletin
                nbvotes[i] = nbvotes[i]+ 1;
            }
        }
    }
    return nbvotes;
}

bool majoriteabsolue (const vector<unsigned> & nbvotes, const unsigned & indice)
{
    float nbTotalDeVotes = 0;
    for (unsigned i=0; i < nbvotes.size(); ++i) // i vaut le nb de vote par candidat
    {
        nbTotalDeVotes += nbvotes[i];
    }

    float majoriteabsolue = (float(nbvotes[indice])*100)/float(nbTotalDeVotes); //produit en croix
    cout << majoriteabsolue << endl;
    return majoriteabsolue > 50;
}

vector<string> & supprimer (vector<string> & Vstring, const unsigned & indiceElement) // supprime un element dont on a l'indice dans vector<string>
{
    for (unsigned i=indiceElement; i < Vstring.size() -1; ++i)
    {
        Vstring[i] = Vstring[i+1];
    }
    Vstring.resize(Vstring.size() -1);
    return Vstring;
}

vector<vector<string>> & supprimer (vector<vector<string>> & scrutin, const string & candidatElimine) // parcour ma liste de bulletin
{
    for (unsigned i=0; i < scrutin.size(); ++i) // applique a chaque bulletin (vector<string>) la fonction supprimer
    {
        scrutin[i] = supprimer(scrutin[i], indiceCandidat(scrutin[i], candidatElimine));
    }
    return scrutin;
}

string candidatAEliminer (vector<unsigned> & nbvotes, vector<string> & reference) // equivalent a une fonction minimum
{
    unsigned indiceMin = 0;
    for (unsigned i=1; i < nbvotes.size(); ++i)
    {
        if (nbvotes[indiceMin] > nbvotes[i])
            indiceMin = i;
    }
    return reference[indiceMin]; // return le nom du candidat qui a obtenu le moins bon resultat grâce au tableau reference range dans le meme ordre
}

unsigned indiceCandidat (const vector<string> & bulletin, const string & candidat) // renvoie l'indice d'un candidat (string) dans un vector<string>
{
    unsigned indice = 0;
    while (indice < bulletin.size())
    {
        if (bulletin[indice] == candidat){
            return indice;
        }
        ++indice;

    }
    return indice;
}


int main()
{

    vecStr tabCandidat;
    vecStr tabNomVotant;
    matStr tabVote;
    recupCandidat(tabCandidat);
    recupVote(tabNomVotant, tabVote, tabCandidat);
    depouiller(tabVote, tabCandidat);
    return 0;
}
