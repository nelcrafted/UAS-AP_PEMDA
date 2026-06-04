#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Minesweeper {
private:
    static const int MAKS = 10;
    int N;                           
    int jmlBom;                      
    char papan[MAKS][MAKS];          
    bool bom[MAKS][MAKS];            
    int hitungBom[MAKS][MAKS];       
    bool terbuka[MAKS][MAKS];        
    bool bendera[MAKS][MAKS];        
    int jmlBendera;                  
    time_t waktuMulai;               
    bool selesai;                    
    bool menang;                     

    void hitungSekitar() {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                hitungBom[i][j] = 0;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (bom[i][j]) continue;
                int cnt = 0;
                for (int di = -1; di <= 1; di++) {
                    for (int dj = -1; dj <= 1; dj++) {
                        if (di == 0 && dj == 0) continue;
                        int ni = i + di, nj = j + dj;
                        if (ni >= 0 && ni < N && nj >= 0 && nj < N && bom[ni][nj])
                            cnt++;
                    }
                }
                hitungBom[i][j] = cnt;
            }
        }
    }

    void tempatkanBom() {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                bom[i][j] = false;

        int terpasang = 0;
        while (terpasang < jmlBom) {
            int r = rand() % N;
            int c = rand() % N;
            if (!bom[r][c]) {
                bom[r][c] = true;
                terpasang++;
            }
        }
        hitungSekitar();
    }

    void bukaKosong(int r, int c) {
        if (r < 0 || r >= N || c < 0 || c >= N) return;
        if (terbuka[r][c] || bom[r][c]) return;
        terbuka[r][c] = true;
        if (hitungBom[r][c] > 0) return;
        for (int dr = -1; dr <= 1; dr++)
            for (int dc = -1; dc <= 1; dc++)
                if (dr != 0 || dc != 0)
                    bukaKosong(r + dr, c + dc);
    }

    bool cekMenang() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (bom[i][j] && !bendera[i][j]) return false;
                if (!bom[i][j] && bendera[i][j]) return false;
            }
        }
        return true;
    }

    void updateTampilan() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (bendera[i][j] && !terbuka[i][j]) {
                    papan[i][j] = 'F';
                } else if (terbuka[i][j]) {
                    if (bom[i][j]) papan[i][j] = '*';
                    else if (hitungBom[i][j] == 0) papan[i][j] = ' ';
                    else papan[i][j] = '0' + hitungBom[i][j];
                } else {
                    papan[i][j] = '?';
                }
            }
        }
    }

public:
    Minesweeper() {
        N = 0;
        jmlBom = 0;
        jmlBendera = 0;
        selesai = false;
        menang = false;
        waktuMulai = 0;
    }

    bool mulaiBaru(int ukuran, int bom) {
        if (ukuran < 4 || ukuran > MAKS) {
            cout << "Ukuran harus 4 - " << MAKS << endl;
            return false;
        }
        if (bom < 1 || bom > ukuran * ukuran - 1) {
            cout << "Jumlah bom harus 1 - " << (ukuran * ukuran - 1) << endl;
            return false;
        }

        N = ukuran;
        jmlBom = bom;
        jmlBendera = 0;
        selesai = false;
        menang = false;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                terbuka[i][j] = false;
                bendera[i][j] = false;
                papan[i][j] = '?';
            }
        }

        tempatkanBom();
        waktuMulai = time(0);
        updateTampilan();
        return true;
    }

    void tampilkan() {
        int sisaBom = jmlBom - jmlBendera;
        if (sisaBom < 0) sisaBom = 0;
        int detik = time(0) - waktuMulai;

        cout << "\n=== MINESWEEPER ===\n";
        cout << "Sisa bom: " << sisaBom << " | Waktu: " << detik << " detik\n";
        cout << "   ";
        for (int j = 0; j < N; j++) cout << " " << j+1 << "  ";
        cout << endl;

        for (int i = 0; i < N; i++) {
            cout << i+1 << "  ";
            for (int j = 0; j < N; j++) {
                cout << " " << papan[i][j] << " ";
                if (j < N-1) cout << "|";
            }
            cout << endl;
            if (i < N-1) {
                cout << "   ";
                for (int j = 0; j < N; j++) cout << "---+";
                cout << endl;
            }
        }
        cout << "========================\n";
    }

    void buka(int r, int c) {
        if (selesai) return;
        if (r < 0 || r >= N || c < 0 || c >= N) {
            cout << "Koordinat salah!\n";
            return;
        }
        if (terbuka[r][c]) {
            cout << "Sudah terbuka.\n";
            return;
        }
        if (bendera[r][c]) {
            cout << "Hapus bendera dulu.\n";
            return;
        }
        if (bom[r][c]) {

            selesai = true;
            menang = false;
           
            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                    if (bom[i][j]) terbuka[i][j] = true;
            updateTampilan();
            tampilkan();
            cout << "\nBOOM! Kamu kena bom. Game over.\n";
        } else {
            bukaKosong(r, c);
            updateTampilan();
            if (cekMenang()) {
                selesai = true;
                menang = true;
                tampilkan();
                int detik = time(0) - waktuMulai;
                cout << "\nSELAMAT! Kamu menang dalam " << detik << " detik!\n";
            }
        }
    }

    void pasangBendera(int r, int c) {
        if (selesai) return;
        if (r < 0 || r >= N || c < 0 || c >= N) {
            cout << "Koordinat salah!\n";
            return;
        }
        if (terbuka[r][c]) {
            cout << "Sel sudah terbuka, tidak bisa dipasang bendera.\n";
            return;
        }
        if (bendera[r][c]) {
            bendera[r][c] = false;
            jmlBendera--;
            cout << "Bendera dicabut.\n";
        } else {
            bendera[r][c] = true;
            jmlBendera++;
            cout << "Bendera dipasang.\n";
        }
        updateTampilan();
        if (cekMenang()) {
            selesai = true;
            menang = true;
            tampilkan();
            int detik = time(0) - waktuMulai;
            cout << "\nSELAMAT! Kamu menang dalam " << detik << " detik!\n";
        }
    }

    bool isSelesai() { return selesai; }
    bool isMenang() { return menang; }
};

int main() {
    srand(time(0));
    Minesweeper game;
    int pilih;

    do {
        cout << "\n===== MENU UTAMA =====\n";
        cout << "1. Mulai Permainan Baru\n";
        cout << "2. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilih;

        if (pilih == 1) {
            int ukuran, bom;
            cout << "Masukkan ukuran papan (4-10): ";
            cin >> ukuran;
            while (ukuran < 4 || ukuran > 10) {
                cout << "Ukuran harus 4-10, masukkan lagi: ";
                cin >> ukuran;
            }
            int maxBom = ukuran * ukuran - 1;
            cout << "Masukkan jumlah bom (1-" << maxBom << "): ";
            cin >> bom;
            while (bom < 1 || bom > maxBom) {
                cout << "Jumlah bom harus 1-" << maxBom << ", masukkan lagi: ";
                cin >> bom;
            }

            if (!game.mulaiBaru(ukuran, bom)) {
                continue;
            }

            while (!game.isSelesai()) {
                game.tampilkan();
                int baris, kolom, aksi;
                cout << "\nMasukkan baris dan kolom (1-" << ukuran << "): ";
                cin >> baris >> kolom;
                if (baris < 1 || baris > ukuran || kolom < 1 || kolom > ukuran) {
                    cout << "Koordinat tidak valid!\n";
                    continue;
                }
                baris--; kolom--;
                cout << "Aksi (1=Buka, 2=Tandai/Hapus bendera): ";
                cin >> aksi;
                if (aksi == 1) {
                    game.buka(baris, kolom);
                } else if (aksi == 2) {
                    game.pasangBendera(baris, kolom);
                } else {
                    cout << "Pilihan aksi salah.\n";
                }
            }

            cout << "\nTekan Enter untuk kembali ke menu...";
            cin.ignore();
            cin.get();
        } else if (pilih != 2) {
            cout << "Pilihan tidak valid.\n";
        }
    } while (pilih != 2);

    cout << "Terima kasih sudah bermain!\n";
    return 0;
}