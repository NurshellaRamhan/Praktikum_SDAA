#include <iostream>
#include <string>
using namespace std;

// Struct untuk menyimpan data hewan peliharaan
struct HewanPeliharaan {
    string nama;
    string jenis;
    int umur;
    string pemilik;
};

// Deklarasi array untuk menyimpan banyak data hewan peliharaan
HewanPeliharaan daftarHewan[100];
int jumlahHewan = 0;

// Fungsi untuk menambahkan data hewan peliharaan
void tambahHewan(HewanPeliharaan* hewan) {
    cout << "Masukkan nama hewan: ";
    cin >> hewan->nama;
    cout << "Masukkan jenis hewan: ";
    cin >> hewan->jenis;
    cout << "Masukkan umur hewan: ";
    cin >> hewan->umur;
    cout << "Masukkan nama pemilik: ";
    cin >> hewan->pemilik;

    daftarHewan[jumlahHewan] = *hewan;
    jumlahHewan++;
    cout << "Data hewan berhasil ditambahkan.\n";
}

// Fungsi untuk menampilkan semua data hewan peliharaan
void tampilkanHewan() {
    if (jumlahHewan == 0) {
        cout << "Tidak ada data hewan.\n";
    } else {
        for (int i = 0; i < jumlahHewan; i++) {
            cout << "Hewan ke-" << i+1 << ":\n";
            cout << "Nama: " << daftarHewan[i].nama << "\n";
            cout << "Jenis: " << daftarHewan[i].jenis << "\n";
            cout << "Umur: " << daftarHewan[i].umur << " tahun\n";
            cout << "Pemilik: " << daftarHewan[i].pemilik << "\n\n";
        }
    }
}

// Fungsi untuk mengedit data hewan peliharaan
void editHewan(int indeks, HewanPeliharaan* hewan) {
    cout << "Masukkan nama hewan baru: ";
    cin >> hewan->nama;
    cout << "Masukkan jenis hewan baru: ";
    cin >> hewan->jenis;
    cout << "Masukkan umur hewan baru: ";
    cin >> hewan->umur;
    cout << "Masukkan nama pemilik baru: ";
    cin >> hewan->pemilik;

    daftarHewan[indeks] = *hewan;
    cout << "Data hewan berhasil diubah.\n";
}

// Fungsi untuk menghapus data hewan peliharaan
void hapusHewan(int indeks) {
    for (int i = indeks; i < jumlahHewan - 1; i++) {
        daftarHewan[i] = daftarHewan[i + 1];
    }
    jumlahHewan--;
    cout << "Data hewan berhasil dihapus.\n";
}

// Fungsi utama
int main() {
    int pilihan;
    HewanPeliharaan* hewanBaru = new HewanPeliharaan; // pointer ke struct
    int indeks;

    do {
        cout << "Menu Manajemen Penitipan Hewan Peliharaan:\n";
        cout << "1. Tambah Hewan Peliharaan\n";
        cout << "2. Tampilkan Daftar Hewan\n";
        cout << "3. Edit Data Hewan\n";
        cout << "4. Hapus Data Hewan\n";
        cout << "5. Keluar\n";
        cout << "Masukkan pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahHewan(hewanBaru);
                break;
            case 2:
                tampilkanHewan();
                break;
            case 3:
                cout << "Masukkan nomor hewan yang akan diedit: ";
                cin >> indeks;
                if (indeks > 0 && indeks <= jumlahHewan) {
                    editHewan(indeks - 1, hewanBaru);
                } else {
                    cout << "Nomor hewan tidak valid.\n";
                }
                break;
            case 4:
                cout << "Masukkan nomor hewan yang akan dihapus: ";
                cin >> indeks;
                if (indeks > 0 && indeks <= jumlahHewan) {
                    hapusHewan(indeks - 1);
                } else {
                    cout << "Nomor hewan tidak valid.\n";
                }
                break;
            case 5:
                cout << "Terima kasih telah menggunakan program ini.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }
    } while (pilihan != 5);

    delete hewanBaru; // dealokasi memori
    return 0;
}
