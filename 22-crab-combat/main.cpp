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

int get_score(deque<int> d) {
    int score = 0;
    for (int turn = d.size(); !d.empty(); turn--) {
        score += d.front() * turn;
        d.pop_front();
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

            if (!rec1.empty()) {
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
}

void combat(deque<int> &d1, deque<int> &d2) {
    if (d2.front() > d1.front()) 
        swap(d1, d2);
    
    d1.push_back(d1.front());
    d1.push_back(d2.front());
    d1.pop_front(); d2.pop_front();
}

int p2(deque<int> d1, deque<int> d2) {
    recursive_combat(d1, d2);
    return !d1.empty() ? get_score(d1) : get_score(d2);
}

int p1(deque<int> d1, deque<int> d2) {
    while (!d1.empty() && !d2.empty())
        combat(d1, d2);

    return !d1.empty() ? get_score(d1) : get_score(d2);
}

int main() {
    deque<int> d1 = get_deck(), d2 = get_deck();
    printf("p1: %d\np2: %d\n", p1(d1, d2), p2(d1, d2));
}