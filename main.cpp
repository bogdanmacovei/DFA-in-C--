#include <bits/stdc++.h>
#include <cstdio>
#include <cstring>

using namespace std;

vector <string> word;                               // cuvintele de verificat

/**
                                MATRICE SIMBOLURI

        Nume               |      Variabila    |   Tip
        =======================================================================
        nr stari           |      nrStari      |   int
        -----------------------------------------------------------------------
        starile            |      Q            |   vector <int>
        -----------------------------------------------------------------------
        litere             |      Sigma        |   vector <char>
        -----------------------------------------------------------------------
        stare intiala      |      q0           |   int
        -----------------------------------------------------------------------
        nr starilor finale |      nrFinale     |   int
        -----------------------------------------------------------------------
        starile finale     |      F            |   vector <int>
        -----------------------------------------------------------------------
        tranzitii          |      delta        |   map <pair <int, char>, int>
        -----------------------------------------------------------------------
        lista cuvinte      |      cuvant       |   string

**/

void citireDate (vector<int> &Q, vector<char> &Sigma, vector<int> &F, int &q0, map <pair <int, char>, int> &delta)
{
    ifstream fin ("fa.in");

    /// Citirea numarului de stari

    int nrStari;
    fin >> nrStari;

    /// Citirea starilor

    for(int i = 0; i < nrStari; ++i)
    {
        int q;
        fin >> q;
        Q.push_back(q);
    }

    /// Citirea alfabetului Sigma

    char litera;

    do
    {
        fin >> litera;

        if (litera != ';')
            Sigma.push_back(litera);
    }
    while(litera != ';');

    /// Citirea starii initiale

    fin >> q0;

    /// Citirea numarului de stari finale

    int nrFinale;
    fin >> nrFinale;

    /// Citirea starilor finale

    for(int i = 0; i < nrFinale; ++i)
    {
        int f;
        fin >> f;
        F.push_back(f);
    }

    /// Citirea tranzitiilor

    int stare1, stare2;

    do
    {
        fin >> stare1 >> litera >> stare2;
        if (stare1 == -1)
            break;
        delta[{stare1, litera}] = stare2;

//        cout << "delta(" << stare1 <<", " << litera << ") = " << delta[{stare1, litera}] << "\n";
    }
    while(stare1 != -1);

    fin >> stare1;


//    string w;
//    while (fin >> w)
//    {
//        word.push_back(w);
//        cout << w << " ";
//    }

    /// De ce ajunge pe EOF?

    cout << fin << " ";

    char c;

    while (fin >> c)
    {
        cout << c << " ";
    }

    fin.close();
}

int deltaTilda (int s, string w, map <pair <int, char>, int> delta)
{
	if (w.length() == 1)
		return delta[{s, w[0]}];
	else
		return deltaTilda(delta[{s, w[0]}], w.substr(1, w.length()), delta);
}

bool stareFinala(int p, vector<int> F)
{
    for(vector<int>::iterator it = F.begin(); it != F.end(); it++)
        if (*it == p)
            return true;
    return false;
}

int main()
{
    /// Datele pentru DFA

    vector <int> Q;                                     // multimea starilor initiale
    vector <char> Sigma;                                // multimea neterminalelor
    vector <int> F;                                     // multmea starilor finale
    int  q0;                                            // starea intiala
    map <pair <int, char>, int> delta;                  // functia de tranzitie

    citireDate(Q, Sigma, F, q0, delta);

    char cuv[256];

    char opt[1];

    do
    {
        cout << "Introduceti un cuvant: ";

        cin >> cuv;

        int p = deltaTilda(q0, cuv, delta);

        if(stareFinala(p, F))
            cout << "Cuvantul introdus a fost acceptat";
        else
            cout << "Cuvantul introdus a fost respins";

        cout << "\n\nDoriti sa refolositi functia? d/n: ";
        cin >> opt;
        cout << "\n\n";

    }
    while (opt[0] != 'n');


    return 0;
}
