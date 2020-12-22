#include <bits/stdc++.h>
#include <regex>
using namespace std;

deque<int> get_deck() {
    deque<int> deck;

    for (string line; getline(cin, line);) {
        if (any_of(line.begin(), line.end(), ::isalpha)) continue;
        if (line.empty()) break;
        deck.push_back(stoi(line));
    }
    return deck;
}

int get_score(deque<int> deck) {
    int score = 0;
    for (int turn = deck.size(); !deck.empty(); turn--) {
        score += deck.front() * turn;
        deck.pop_front();
    }
    return score;
}


void recursive_combat(deque<int> &p1, deque<int> &p2) {
    set<pair<deque<int>, deque<int>>> turns;
    
    while (!p1.empty() && !p2.empty()) {
        if (turns.find({p1, p2}) != turns.end()) {
            p2.clear();
            return;
        }
        turns.insert({p1, p2});
        
        int top_p1 = p1.front(), top_p2 = p2.front();
        p1.pop_front(); p2.pop_front();
        
        if (top_p1 <= p1.size() && top_p2 <= p2.size()) {

            deque<int> rec1 = p1, rec2 = p2; 

            for (int i = 0; i < p1.size() - top_p1; i++) rec1.pop_back();
            for (int i = 0; i < p2.size() - top_p2; i++) rec2.pop_back();

            recursive_combat(rec1, rec2);

            if (rec1.size()) {
                p1.push_back(top_p1);
                p1.push_back(top_p2);
            } 
            else {
                p2.push_back(top_p2);
                p2.push_back(top_p1);
            }

        } 
        else {
            if (top_p1 > top_p2) {
                p1.push_back(top_p1);
                p1.push_back(top_p2);
            } else {
                p2.push_back(top_p2);
                p2.push_back(top_p1);
            }
        }
    }
    return;
}

void combat(deque<int> &p1, deque<int> &p2) {
    cout << p1.front() << " " << p2.front() << endl;

    if (p1.front() > p2.front()) {
        p1.push_back(p1.front());
        p1.push_back(p2.front());
    } else {
        p2.push_back(p2.front());
        p2.push_back(p1.front());
    }

    p1.pop_front(); p2.pop_front();
}


int main() {
    deque<int> p1 = get_deck(), p2 = get_deck();

    // while (p1.size() != 0 && p2.size() != 0) {
    //     combat(p1, p2);
    // }

    // int res = p1.size() ? get_score(p1) : get_score(p2);
    // cout << res << endl;

    
    recursive_combat(p1, p2);
    
    // while (!p1.empty()) {
    //     cout << p1.front() << " ";
    //     p1.pop_front();
    // }
    // cout << endl;

    // while (!p2.empty()) {
    //     cout << p2.front() << " ";
    //     p2.pop_front();
    // }
    // cout << endl;

    int res = p1.size() ? get_score(p1) : get_score(p2);
    cout << res << endl;
}