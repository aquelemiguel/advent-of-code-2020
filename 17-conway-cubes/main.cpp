#include <bits/stdc++.h>
using namespace std;

typedef tuple<int,int,int> Cube;
typedef tuple<int,int,int,int> Hypercube;

bool is_active(set<Cube> &cubes, int x, int y, int z) {
    return cubes.find(make_tuple(x, y, z)) != cubes.end();
}

bool is_active(set<Hypercube> &cubes, int x, int y, int z, int w) {
    return cubes.find(make_tuple(x, y, z, w)) != cubes.end();
}

void next2(set<Hypercube> &cubes, int limit) {
    set<Hypercube> dupes = cubes;

    for (int x = -8 -limit; x <= 8 + limit; x++) {
        for (int y = -8 -limit; y <= 8 + limit; y++) {
            for (int z = -8 - limit; z <= 8 + limit; z++) {
                for (int w = -1-limit; w <= 1+limit; w++) {
                    int active = 0;

                    for (int dx = -1; dx <= 1; dx++) {
                        for (int dy = -1; dy <= 1; dy++) {
                            for (int dz = -1; dz <= 1; dz++) {
                                for (int dw = -1; dw <= 1; dw++) {
                                    if (dx == 0 && dy == 0 && dz == 0 && dw == 0) continue;
                                    if (is_active(cubes, x+dx, y+dy, z+dz, w+dw)) active++;
                                }
                            }
                        }
                    }

                    bool act = is_active(cubes, x, y, z, w);

                    if (act && !(active == 2 || active == 3)) {
                        dupes.erase(make_tuple(x, y, z, w));
                    }

                    else if (!act && active == 3) {
                        dupes.insert(make_tuple(x, y, z, w));
                    }    
                }
            }
        }
    }
    cubes = dupes;
}

void next(set<Cube> &cubes, int limit) {
    set<Cube> dupes = cubes;

    for (int x = -8 -limit; x <= 8 + limit; x++) {
        for (int y = -8 -limit; y <= 8 + limit; y++) {
            for (int z = -1 - limit; z <= 1 + limit; z++) {

                int active = 0;

                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        for (int dz = -1; dz <= 1; dz++) {
                            if (dx == 0 && dy == 0 && dz == 0) continue;
                            if (is_active(cubes, x+dx, y+dy, z+dz)) active++;
                        }
                    }
                }

                bool act = is_active(cubes, x, y, z);

                if (act && !(active == 2 || active == 3)) {
                    dupes.erase(make_tuple(x, y, z));
                }

                else if (!act && active == 3) {
                    dupes.insert(make_tuple(x, y, z));
                }    
            }
        }
    }
    cubes = dupes;
}

int main() {
    string line;
    // set<Cube> cubes;

    // for (int i = 0; !cin.eof(); i++) {
    //     getline(cin, line);
    //     vector<char> slice(line.begin(), line.end());

    //     for (int j = 0; j < slice.size(); j++)
    //         if (slice[j] == '#') cubes.insert(make_tuple(i, j, 0));
    // }

    set<Hypercube> cubes;

    for (int i = 0; !cin.eof(); i++) {
        getline(cin, line);
        vector<char> slice(line.begin(), line.end());

        for (int j = 0; j < slice.size(); j++)
            if (slice[j] == '#') cubes.insert(make_tuple(i, j, 0, 0));
    }

    cout << cubes.size() << endl;

    // for (int i = 0; i < 6; i++) {
    //     next(cubes, i+1);
    //     cout << cubes.size() << endl;
    // }

    for (int i = 0; i < 6; i++) {
        next2(cubes, i+1);
        cout << cubes.size() << endl;
    }
}