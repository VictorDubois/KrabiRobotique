#include <iostream>
# include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

string desordonner(string mot)
{
    srand(time(0));
    int l(mot.size());
    string motDesordonne("");
    while (l!=0)
    {
        int position=rand() % l;
        motDesordonne+=mot[position];
        mot.erase(position,1);
        l=mot.size();
    }
    return motDesordonne;
}


int main()
{
    int *pointeur(0);
    pointeur=new int;
    cout << "quel est votre age ?"<< endl;
    cin >> *pointeur;
    cout << "votre age est : " << *pointeur << endl;
    delete pointeur;
    pointeur=0;
    return 0;
}


