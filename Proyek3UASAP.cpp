#include <iostream>
#include <vector>
g namespace std;

struct Barang{
    string kode;
    string nama;
    int harga;
    int stok;
};

vector<Barang> daftarBarang;

void tambahBarang(){

    Barang barang;

    cout << "\n=== Tambah Barang ===\n";
    cout << "Kode Barang : ";
    cin >> barang.kode;
    cin.ignore();

    cout << "Nama Barang : ";
    getline(cin, barang.nama);

    do{
        cout << "Harga : ";
        cin >> barang.harga;
        if(barang.harga < 0){
            cout << "Harga tidak boleh negatif!\n";
        }

    }while(barang.harga < 0);
    do{
        cout << "Stok : ";
        cin >> barang.stok;

        if(barang.stok < 0){
            cout << "Stok tidak boleh negatif!\n";
        }
    }while(barang.stok < 0);
    daftarBarang.push_back(barang);
    cout << "Barang berhasil ditambahkan!\n";
}

// Tampilkan Semua Barang
void tampilkanBarang(){

    if(daftarBarang.empty()){
        cout << "\nBelum ada data barang.\n";
        return;
    }
    cout << "\n=== DAFTAR BARANG ===\n";
    for(int i = 0; i < daftarBarang.size(); i++){
        cout << "\nBarang ke-" << i+1 << endl;
        cout << "Kode  : " << daftarBarang[i].kode << endl;
        cout << "Nama  : " << daftarBarang[i].nama << endl;
        cout << "Harga : " << daftarBarang[i].harga << endl;
        cout << "Stok  : " << daftarBarang[i].stok << endl;
    }
}

// Cari Barang Termahal
void cariBarangTermahal(){

    if(daftarBarang.empty()){
        cout << "\nBelum ada data barang.\n";
        return;
    }
    int index = 0;
    for(int i = 1; i < daftarBarang.size(); i++){

        if(daftarBarang[i].harga > daftarBarang[index].harga){
            index = i;
        }
    }
    cout << "\n=== BARANG TERMAHAL ===\n";
    cout << "Kode  : " << daftarBarang[index].kode << endl;
    cout << "Nama  : " << daftarBarang[index].nama << endl;
    cout << "Harga : " << daftarBarang[index].harga << endl;
    cout << "Stok  : " << daftarBarang[index].stok << endl;
}

// Hitung Total Inventaris
void hitungTotalInventaris(){

    int total = 0;
    for(int i = 0; i < daftarBarang.size(); i++){
        total += daftarBarang[i].harga * daftarBarang[i].stok;
    }
    cout << "\nTotal Nilai Inventaris = Rp "
         << total << endl;
}
// Cek Restock
void cekRestock(){
    bool ada = false;
    cout << "\n=== BARANG PERLU RESTOCK ===\n";
    for(int i = 0; i < daftarBarang.size(); i++){
        if(daftarBarang[i].stok < 5){
            ada = true;
            cout << daftarBarang[i].kode
                 << " - "
                 << daftarBarang[i].nama
                 << " (stok: "
                 << daftarBarang[i].stok
                 << ")" << endl;
        }
    }

    if(!ada){
        cout << "Tidak ada barang yang perlu direstock.\n";
    }
}
// Update Stok (Pointer)
void updateStok(){
    string kode;
    cout << "\nMasukkan kode barang : ";
    cin >> kode;
    for(int i = 0; i < daftarBarang.size(); i++){
        if(daftarBarang[i].kode == kode){
            int *ptr = &daftarBarang[i].stok;
            cout << "Stok sekarang : "
                 << *ptr << endl;
            cout << "Masukkan stok baru : ";
            cin >> *ptr;
            cout << "Stok berhasil diperbarui!\n";
            return;
        }
    }

    cout << "Barang tidak ditemukan.\n";
}

int main(){
    int pilihan;
    do{
        cout << "\n========================";
        cout << "\nSISTEM INVENTARIS TOKO";
        cout << "\n========================";
        cout << "\n1. Tambah Barang";
        cout << "\n2. Tampilkan Semua Barang";
        cout << "\n3. Cari Barang Termahal";
        cout << "\n4. Hitung Total Inventaris";
        cout << "\n5. Cek Restock";
        cout << "\n6. Update Stok";
        cout << "\n7. Keluar";
        cout << "\nPilihan : ";
        cin >> pilihan;

        switch(pilihan){
            case 1:
                tambahBarang();
                break;
            case 2:
                tampilkanBarang();
                break;
            case 3:
                cariBarangTermahal();
                break;
            case 4:
                hitungTotalInventaris();
                break;
            case 5:
                cekRestock();
                break;
            case 6:
                updateStok();
                break;
            case 7:
                cout << "\nProgram selesai.\n";
                break;
            default:
                cout << "\nPilihan tidak valid!\n";
        }

    }while(pilihan != 7);
    return 0;
}
