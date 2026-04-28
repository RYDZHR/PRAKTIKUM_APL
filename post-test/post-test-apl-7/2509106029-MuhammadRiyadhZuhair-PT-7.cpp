#include <exception>
#include <iostream>
#include <stdexcept>


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
penumpang& cariNamapenumpang(penumpang arr[], int jumlah,const string& cariNama){
   if(cariNama.empty()){
    throw invalid_argument("Gak boleh kosong");
   }

    for(int i = 0; i < jumlah; i++){
        if(arr[i].nama == cariNama){
            return arr[i];
        }
    }
    throw runtime_error("Penumpang dengan nama \"" + cariNama + "\" Tidak Terdaftar");
}

// Binary search - mencari nomor booking
penumpang& cariNobooking(penumpang arr[], int jumlah,const string& cariBooking){
   if (cariBooking.empty()){
    throw invalid_argument("Gak boleh kosong.");
   }

    int kiri = 0;
    int kanan = jumlah - 1;

    while (kiri <= kanan){
        int tengah = (kiri + kanan) / 2;

        if (arr[tengah].Nobooking == cariBooking){
            return arr[tengah];
        }else if (arr[tengah].Nobooking < cariBooking){
            kiri = tengah + 1;
        } else {
            kanan = tengah -1;
        }
    }
    throw runtime_error("ID \"" + cariBooking + "\" Tidak Terdaftar");
}

void identitasPenumpang(const penumpang& p){
    cout << "\n==================== INFO PENUMPANG ====================\n";
    cout << " Nomor Booking : " << p.Nobooking << endl;
    cout << " Harga         : " << p.harga << endl;
    cout << " Nama          : " << p.nama << endl;
    cout << " Kursi         : " << p.kursi << endl;
    cout << " Maskapai      : " << p.maskapai << endl;
    cout << " Pesawat       : " << p.pesawat << endl;
    cout << "\n========================================================\n";

}

int main(){
    

    penumpang daftarPenumpang[]{
        {"FA0001", 300000, "Kanye Barat", "A022", "Garuda Indonesia", "Boeing 737-800"},
        {"FA0002", 280000, "Ucok Sableng", "A012", "Garuda Indonesia", "Boeing 737-800"},
        {"FA0003", 500000, "Rusdi Barbershop", "A013", "Garuda Indonesia", "Boeing 737-800"},
        {"FA0004", 800000, "Eja Auditore", "B22", "Garuda Indonesia", "Boeing 737-800"},
        {"FA0005", 800000, "Ladhesigh", "B23", "Garuda Indonesia", "Boeing 737-800"},
    };

    int jumlah = sizeof(daftarPenumpang) / sizeof(daftarPenumpang[0]);
    bool running = true;

    

    do{
        cout << "\n==================== G.A Management System =================\n";

        cout << "1. Cari Nama." << endl;
        cout << "2. Cari No. booking" << endl;
        cout << "3. Lihat list penumpang" << endl;
        cout << "4. GET OUT!" << endl;
        cout << ": ";

        try{
            string Rawinput;
            getline(cin, Rawinput);

            if(Rawinput.empty()){
                throw invalid_argument("Pilihan tidak boleh kosong");
            }

            for (char c : Rawinput){
                if (!isdigit(c)){
                    throw invalid_argument("Input harus angka");
                }
            }

            int pilihan = stoi(Rawinput);

            
            cout << "\n============================================================\n";

            if (pilihan == 1){
                string cariNama;
                cout << "Nama yang dicari?: ";
            
                getline(cin, cariNama);

                penumpang& hasil = cariNamapenumpang(daftarPenumpang, jumlah, cariNama);
                identitasPenumpang(hasil);

            }else if (pilihan == 2){
                string cariBooking;
                cout << "Masukin Idnya: ";
                
                getline(cin, cariBooking);

                penumpang& hasil = cariNobooking(daftarPenumpang, jumlah, cariBooking);
                identitasPenumpang(hasil);

            } else if(pilihan == 3){
                for (int i = 0; i < jumlah; i++){
                    cout << "\n[" << i + 1 <<" ]" << endl;
                    cout << "No. Booking : " << daftarPenumpang[i].Nobooking << endl;
                    cout << "Nama        : " << daftarPenumpang[i].nama << endl;
                    cout << "Harga       : " << daftarPenumpang[i].harga << endl;
                    cout << "Kursi       : " << daftarPenumpang[i].kursi << endl;
                    cout << "Maskapai    : " << daftarPenumpang[i].maskapai << endl;
                    cout << "Pesawat     : " << daftarPenumpang[i].pesawat << endl;
                }

            }else if (pilihan == 4) {
                cout << "Have a nice trip ;)";
                return 0;
            }

        } catch (invalid_argument e){
            cerr << "[ERR] - Invalid Input" << e.what() << endl;
        }catch (runtime_error e){
            cerr << "[ERR] -" << e.what() << endl;
        }catch(exception& e){
            cerr << "[ERR]" << e.what() << endl;
        }


    } while (running);

    return 0;

    

}
