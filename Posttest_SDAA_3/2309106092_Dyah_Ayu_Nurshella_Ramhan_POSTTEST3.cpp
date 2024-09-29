#include <iostream>
#include <string>
#include <limits> // handling input invalid
using namespace std;

// Struct untuk node di linked list
struct Node {
    string nama;
    string jenis;
    int umur;
    string pemilik;
    Node* berikutnya; 
};

// Pointer untuk head dari linked list
Node* head = nullptr;

// untuk memastikan input integer valid
int inputInteger() {
    int angka;
    while (true) {
        cin >> angka;
        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Menghapus input yang tidak valid
            cout << "Input tidak valid. Masukkan angka: ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Menghapus sisa input
            return angka;
        }
    }
}

void tambahHewan() {
    Node* nodeBaru = new Node;

    cout << "Masukkan nama hewan: ";
    getline(cin, nodeBaru->nama);
    cout << "Masukkan jenis hewan: ";
    getline(cin, nodeBaru->jenis);

    cout << "Masukkan umur hewan (angka): ";
    nodeBaru->umur = inputInteger();

    cout << "Masukkan nama pemilik: ";
    getline(cin, nodeBaru->pemilik);

    nodeBaru->berikutnya = head;
    head = nodeBaru;

    cout << "Data hewan berhasil ditambahkan.\n";
}

void tampilkanHewan() {
    if (head == nullptr) {
        cout << "Tidak ada data hewan.\n";
    } else {
        Node* nodeSaatIni = head;
        int nomor = 1;
        while (nodeSaatIni != nullptr) {
            cout << "Hewan ke-" << nomor << ":\n";
            cout << "Nama: " << nodeSaatIni->nama << "\n";
            cout << "Jenis: " << nodeSaatIni->jenis << "\n";
            cout << "Umur: " << nodeSaatIni->umur << " tahun\n";
            cout << "Pemilik: " << nodeSaatIni->pemilik << "\n\n";
            nodeSaatIni = nodeSaatIni->berikutnya;
            nomor++;
        }
    }
}

void editHewan(int indeks) {
    if (head == nullptr) {
        cout << "Tidak ada data untuk diedit.\n";
        return;
    }

    Node* nodeSaatIni = head;
    int nomor = 1;

    while (nodeSaatIni != nullptr && nomor != indeks) {
        nodeSaatIni = nodeSaatIni->berikutnya;
        nomor++;
    }

    if (nodeSaatIni == nullptr) {
        cout << "Nomor hewan tidak valid.\n";
    } else {
        cout << "Masukkan nama hewan baru: ";
        getline(cin, nodeSaatIni->nama);
        cout << "Masukkan jenis hewan baru: ";
        getline(cin, nodeSaatIni->jenis);
        
        // Validasi umur
        cout << "Masukkan umur hewan baru (angka): ";
        nodeSaatIni->umur = inputInteger();
        
        cout << "Masukkan nama pemilik baru: ";
        getline(cin, nodeSaatIni->pemilik);

        cout << "Data hewan berhasil diubah.\n";
    }
}

void hapusHewan(int indeks) {
    if (head == nullptr) {
        cout << "Tidak ada data untuk dihapus.\n";
        return;
    }

    Node* nodeSaatIni = head;
    Node* nodeSebelumnya = nullptr;
    int nomor = 1;

    while (nodeSaatIni != nullptr && nomor != indeks) {
        nodeSebelumnya = nodeSaatIni;
        nodeSaatIni = nodeSaatIni->berikutnya;
        nomor++;
    }

    if (nodeSaatIni == nullptr) {
        cout << "Nomor hewan tidak valid.\n";
    } else {
        if (nodeSebelumnya == nullptr) {
            // Jika node yang dihapus adalah node pertama
            head = nodeSaatIni->berikutnya;
        } else {
            // Jika node yang dihapus bukan node pertama
            nodeSebelumnya->berikutnya = nodeSaatIni->berikutnya;
        }
        delete nodeSaatIni;
        cout << "Data hewan berhasil dihapus.\n";
    }
}

int main() {
    int pilihan;
    int indeks;

    do {
        cout << "\n===========================================================\n";
        cout << "|        Selamat Datang di Penitipan Hewan Peliharaan Berry |\n";
        cout << "=============================================================\n";
        cout << "|              1. Titip Hewan Peliharaan                    |\n";
        cout << "|              2. Tampilkan Daftar Hewan                    |\n";
        cout << "|              3. Edit Data Hewan                           |\n";
        cout << "|              4. Hapus Data Hewan                          |\n";
        cout << "|              5. Keluar                                    |\n";
        cout << "=============================================================\n";

        cout << "Masukkan pilihan: ";
        pilihan = inputInteger();

        switch (pilihan) {
            case 1:
                tambahHewan();
                break;
            case 2:
                tampilkanHewan();
                break;
            case 3:
                cout << "Masukkan nomor hewan yang akan diedit: ";
                indeks = inputInteger();
                editHewan(indeks);
                break;
            case 4:
                cout << "Masukkan nomor hewan yang akan dihapus: ";
                indeks = inputInteger();
                hapusHewan(indeks);
                break;
            case 5:
                cout << "Terima kasih telah menggunakan berkunjung.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }
    } while (pilihan != 5);

    return 0;
}
