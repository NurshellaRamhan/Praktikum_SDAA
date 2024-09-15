#include <iostream>
using namespace std;

void proses_buat(int baris_awal[], int baris[], int size){
    baris[0] = 1;
    for (int x = 1; x < size - 1; x++){
        baris[x] = baris_awal[x-1] + baris_awal[x];
    }
    baris[size - 1] = 1;
}

void pascal (int n, int segitiga[][3], int baris = 0){
    if (baris == n)
    return;
    if (baris == 0){
        segitiga[baris][0] = 1;
    }
    else {
        proses_buat(segitiga[baris - 1], segitiga[baris], baris + 1);
    }
    pascal(n, segitiga, baris + 1);
}

void segitiga_siku(int segitiga [][3], int n){
    for (int i = 0; i < n; ++i){
        for (int x = 0; x <= i; ++x){
            cout << segitiga[i][x] << " ";
        }
        cout << endl;
    }
}


int main(){
    const int lantai = 3;
    int segitiga[lantai][lantai] = {0};
    pascal (lantai,segitiga);
    segitiga_siku(segitiga, lantai);
    return 0;
}