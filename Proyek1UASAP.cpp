#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
using namespace std;

struct Petugas {
    string nama;
    string id;
};

struct Mobil {
    string plat;
    string merk;
    string warna;
    time_t waktuMasuk;
};

const int MAX_PARKIR = 20;
vector<Mobil> daftarMobil;

// Function hitung durasi parkir
void tampilDurasi(time_t waktuMasuk) {
    time_t sekarang = time(0);
    int detik = difftime(sekarang, waktuMasuk);

    int jam = detik / 3600;
    detik %= 3600;

    int menit = detik / 60;
    detik %= 60;

    cout << jam << " jam "
         << menit << " menit "
         << detik << " detik";
}

// Function tambah kendaraan
void tambahMobil() {
    int jumlah;

    cout << "\nMasukkan jumlah mobil yang akan diparkir : ";
    cin >> jumlah;
    cin.ignore();

    if (daftarMobil.size() + jumlah > MAX_PARKIR) {
        cout << "Maaf, parkiran hanya dapat memuat 20 mobil !\n";
        return;
    }

    for (int i = 0; i < jumlah; i++) {
        Mobil m;

        cout << "\nMobil ke-" << i + 1 << endl;

        cout << "Masukkan plat mobil : ";
        getline(cin, m.plat);

        cout << "Masukkan merk mobil : ";
        getline(cin, m.merk);

        cout << "Masukkan warna mobil : ";
        getline(cin, m.warna);

        m.waktuMasuk = time(0);

        daftarMobil.push_back(m);
    }

    cout << "\nData mobil berhasil ditambahkan!\n";
}

// Function tampil daftar kendaraan
void tampilMobil() {
    if (daftarMobil.empty()) {
        cout << "\nBelum ada mobil yang parkir.\n";
        return;
    }

    cout << "\nDAFTAR MOBIL YANG SUDAH TERPARKIR :\n";
    cout << "================================================\n";

    for (int i = 0; i < daftarMobil.size(); i++) {
        cout << "\nMobil ke-" << i + 1 << endl;
        cout << "Plat mobil  : " << daftarMobil[i].plat << endl;
        cout << "Merk mobil  : " << daftarMobil[i].merk << endl;
        cout << "Warna mobil : " << daftarMobil[i].warna << endl;

        cout << "Waktu parkir : ";
        tampilDurasi(daftarMobil[i].waktuMasuk);
        cout << endl;

        cout << "================================================\n";
    }
}

// Function pembayaran
void pembayaran() {
    if (daftarMobil.empty()) {
        cout << "\nTidak ada mobil di parkiran.\n";
        return;
    }

    string cariPlat;
    cout << "\nMasukkan plat mobil yang ingin dibayar : ";
    cin.ignore();
    getline(cin, cariPlat);

    bool ditemukan = false;

    for (int i = 0; i < daftarMobil.size(); i++) {
        if (daftarMobil[i].plat == cariPlat) {
            ditemukan = true;

            time_t sekarang = time(0);
            int detik = difftime(sekarang, daftarMobil[i].waktuMasuk);

            // Tarif Rp100 per menit
            int biaya = (detik / 60) * 100;

            if (biaya == 0)
                biaya = 100;

            cout << "\nBIAYA PARKIR : Rp " << biaya << endl;

            daftarMobil.erase(daftarMobil.begin() + i);
            cout << "Mobil keluar dari parkiran.\n";

            break;
        }
    }

    if (!ditemukan) {
        cout << "PLAT TIDAK DITEMUKAN !\n";
    }
}

// Function menu
void menu() {
    int opsi;

    do {
        cout << "\n========================================\n";
        cout << "      SISTEM PARKIR MALL PRIENAL       \n";
        cout << "========================================\n";
        cout << "1. Tambahkan Daftar Kendaraan\n";
        cout << "2. Tampilkan Daftar Kendaraan\n";
        cout << "3. Pembayaran\n";
        cout << "4. Keluar Program\n";
        cout << "Masukkan opsi : ";
        cin >> opsi;

        switch (opsi) {
            case 1:
                tambahMobil();
                break;

            case 2:
                tampilMobil();
                break;

            case 3:
                pembayaran();
                break;

            case 4:
                cout << "\nProgram selesai.\n";
                break;

            default:
                cout << "\nOpsi tidak valid!\n";
        }

    } while (opsi != 4);
}

int main() {
    system("cls");
    Petugas p;

    cout << "========================================\n";
    cout << "          SELAMAT DATANG                \n";
    cout << "      DI PORTAL PARKIR MOBIL            \n";
    cout << "========================================\n";

    cout << "\nMasukkan nama petugas : ";
    getline(cin, p.nama);

    cout << "Masukkan ID petugas : ";
    getline(cin, p.id);

    cout << "\nNama Petugas : " << p.nama << endl;
    cout << "ID Petugas   : " << p.id << endl;

    menu();

    return 0;
}