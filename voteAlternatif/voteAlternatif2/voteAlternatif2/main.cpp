#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

typedef vector<string> vecStr;
typedef vector<unsigned> vecUInt;
typedef vector<vector<string>> matStr;
typedef vector<vector<unsigned>> matUInt;

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

void depouillage (const vecStr & tabCandidat, const matStr & matVote, vecUInt & tabScore) {
    tabScore.resize(tabCandidat.size(),  0);
    for (auto & vote : matVote) {
        for (size_t j (0) ; j < tabCandidat.size() ; ++j) {
            if (tabCandidat[j] == vote[0]) tabScore[j] += 1;
        }
    }
}

void elimination (vecStr & tabCandidat, matStr & matVote, vecUInt & tabScore) {
    string elimine;
    unsigned min = 0;
    for (size_t i (1) ; i < tabScore.size() ; ++i) {
        if (tabScore[i] < tabScore[min]) min = i;
    }
    elimine = tabCandidat[min];
    tabCandidat.erase(find(tabCandidat.begin(), tabCandidat.end(), elimine));
    for (auto & i : matVote) {
        i.erase(find(i.begin(), i.end(), elimine));
    }
}

unsigned majoriteAbs (const vecStr & tabCandidat, const vecUInt & tabScore, const matStr & matVote) {
    float score = 0;
    for (size_t i (0) ; i < tabScore.size() ; ++i) {
        score = float(tabScore[i]*100)/matVote.size();
        cout << endl << tabCandidat[i] << " : " << score << endl << endl;
        if (score >= 50) return i;
    }
    cout << "-";
    return tabScore.size();
}

void afficheTab(const matStr & tab) {
    for (auto & i : tab) {
        for (auto & j : i)
            cout << j << ",";
        cout << endl;
    }
}

int main()
{
    vecStr tabCandidat;
    vecStr tabNomVotant;
    vecUInt tabScore;
    matStr matVote;

    unsigned elu (0);

    recupCandidat(tabCandidat);
    recupVote(tabNomVotant, matVote, tabCandidat);
    while (true) {
        depouillage(tabCandidat, matVote, tabScore);
        elu = majoriteAbs(tabCandidat, tabScore, matVote);
        if (elu != tabScore.size()) break;
        elimination(tabCandidat, matVote, tabScore);
    }
    cout << endl << "Le candidat élu est : " << tabCandidat[elu];
    return 0;
}
