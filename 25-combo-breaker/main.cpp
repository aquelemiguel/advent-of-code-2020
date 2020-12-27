#include <bits/stdc++.h>
using namespace std;

int main() {
    unsigned long long card_pk, door_pk, loop = 0, encrypt = 1; 
    cin >> card_pk >> door_pk;

    for (int value = 1; value != card_pk; loop++)
        value = (value * 7) % 20201227;

    for (int i = 0; i < loop; i++)
        encrypt = (encrypt * door_pk) % 20201227;

    cout << "p1: " << encrypt << endl;
}