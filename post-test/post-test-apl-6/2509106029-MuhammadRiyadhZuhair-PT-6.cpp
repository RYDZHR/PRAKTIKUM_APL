#include <iostream>

using namespace std;

struct penumpang {
    string Nobooking;
    double harga;
    string nama;
    string kursi;
    string maskapai;
    string pesawat;
};


// linear search - mencari nama dalam data penumpang
penumpang* cariNamapenumpang(penumpang arr[], int jumlah, string cariNama){
    cout << "Nama yang dicari: ";
    cin.ignore();
    getline(cin, cariNama);

    for(int i = 0; i < jumlah; i++){
        if(arr[i].nama == cariNama){
            return &arr[i];
        }
    }
    return nullptr;
}

// Binary search - mencari nomor booking
penumpang* cariNobooking(penumpang arr[], int jumlah, string cariBooking){
    cout << "Nomor yang dicari?: ";
    cin.ignore();
    getline(cin, cariBooking);

    int kiri = 0;
    int kanan = jumlah - 1;

    while (kiri <= kanan){
        int tengah = (kiri + kanan) / 2;

        if (arr[tengah].Nobooking == cariBooking){
            return &arr[tengah];
        }else if (arr[tengah].Nobooking < cariBooking){
            kiri = tengah + 1;
        } else {
            kanan = tengah -1;
        }
    }
    return nullptr;
}

void identitasPenumpang(penumpang* p){
    cout << "\n==================== INFO PENUMPANG ====================\n";
    cout << " Nomor Booking : " << p->Nobooking << endl;
    cout << " Harga         : " << p->harga << endl;
    cout << " Nama          : " << p->nama << endl;
    cout << " Kursi         : " << p->kursi << endl;
    cout << " Maskapai      : " << p->maskapai << endl;
    cout << " Pesawat       : " << p->pesawat << endl;
    cout << "\n========================================================\n";

}

int main(){
    int pilihan;

    penumpang daftarPenumpang[]{
        {"FA0001", 300000, "Kanye Barat", "A022", "Garuda Indonesia", "Boeing 737-800"},
        {"FA0002", 280000, "Ucok Sableng", "A012", "Garuda Indonesia", "Boeing 737-800"},
        {"FA0003", 500000, "Rusdi Barbershop", "A013", "Garuda Indonesia", "Boeing 737-800"},
        {"FA0004", 800000, "Eja Auditore", "B22", "Garuda Indonesia", "Boeing 737-800"},
        {"FA0005", 800000, "Ladhesigh", "B23", "Garuda Indonesia", "Boeing 737-800"},
    };

    int jumlah = sizeof(daftarPenumpang) / sizeof(daftarPenumpang[0]);

    cout << "\n==================== G.A Management System =================\n";

    cout << "1. Cari Nama." << endl;
    cout << "2. Cari No. booking" << endl;
    cout << "3. Lihat list penumpang" << endl;
    cout << "4. GET OUT!" << endl;
    cout << ": ";
    cin >> pilihan;

    cout << "\n============================================================\n";

    if (pilihan == 1){
        string cariNama;
        penumpang* hasil = cariNamapenumpang(daftarPenumpang, jumlah, cariNama);
        if (hasil != nullptr){
            identitasPenumpang(hasil);
        }else {
            cout << "Takde Orangnya" << endl;
        }
    } else if (pilihan == 2){
        string cariBooking;
        penumpang* hasilNobook = cariNobooking(daftarPenumpang, jumlah, cariBooking);

        if (hasilNobook != nullptr){
            identitasPenumpang(hasilNobook);
        } else {
            cout << "Nomor tidak terdaftar" << endl;
        }
    } else if(pilihan == 3){
        for (int i = 0; i < jumlah; i++){
            cout << "\n[" << i + 1 <<" ]" << endl;
            cout << "No. Booking : " << daftarPenumpang[i].Nobooking << endl;
            cout << "Nama        : " << daftarPenumpang[i].nama << endl;
            cout << "Harga       : " << daftarPenumpang[i].harga << endl;
            cout << "Kursi       : " << daftarPenumpang[i].kursi << endl;
            cout << "Maskapai    : " << daftarPenumpang[i].maskapai << endl;
            cout << "Pesawat     : " << daftarPenumpang[i].maskapai << endl;
        }
    }else if (pilihan == 4) {
        return 0;
    }else{
        cout << "Pilihan Gak valid" << endl;
    }

    return 0;
}
