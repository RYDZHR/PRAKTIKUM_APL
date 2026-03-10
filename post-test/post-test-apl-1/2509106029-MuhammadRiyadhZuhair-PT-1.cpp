#include <iostream>
#include <stdlib.h>

using namespace std;

void Cleaner(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main(){
    string user = "Riyadh";
    string pass = "029";
    string inputuser, inputpass;
    int pilihan;
    double nilai, m, km, cm;
    
    int batas = 3;

    for (int i = 1 ; i <= batas ; i++){
        cout << "Username : ";
        cin >> inputuser;
        cout << "Password : ";
        cin >> inputpass;

        if (inputuser == user && inputpass == pass){
            do {
                Cleaner();
                cout << "============ Sistem Konversi Ver.Alpha0.1 ============" << endl;
                cout << endl;
                cout << "1. Meter(M)        -->     Kilometer(KM) & Centimeter(CM)" << endl;
                cout << "2. Kilometer(KM)   -->     Meter(M) & Centimeter(CM)" << endl;
                cout << "3. Centimeter(CM)  -->     Meter(M) & Kilometer(KM)" << endl;
                cout << "4. Keluar" << endl;
                cout << endl;
                cout << "======================================================" << endl;

                cout << "silahkan pilih (1, 2, 3, 4): ";
                cin >> pilihan;
                

                switch (pilihan) {
                    case 1:
                        cout << "Masukkan Nilai (M): ";
                        cin >> nilai;
                        km = nilai / 1000.0;
                        cm = nilai * 100.0;
                        cout << "hasil dari " << nilai << "M adalah " << km << " KM dan " << cm << " CM" << endl;
                        break;
                    case 2:
                        cout << "Masukkan Nilai (KM): ";
                        cin >> nilai;
                        m = nilai * 1000.0;
                        cm = nilai * 100000.0;
                        cout << "Hasil dari " << nilai << "KM adalah " << m << " M dan " << cm << " CM" << endl;
                        break;
                    case 3:
                        cout << "Masukkan Nilai (CM): ";
                        cin >> nilai;
                        m = nilai / 100.0;
                        km = nilai / 100000.0;
                        cout << "hasil dari " << nilai << "CM adalah " << m << " M dan " << km << " KM";
                        break;
                    case 4:
                        cout << "Terima kasih, " << user << endl;
                        return 0;
                    default:
                        cout << "Pilihan Gak Valid Mas!!" << endl;
                }
                if (pilihan != 4){
                    cout << "/nTekan Enter buat lanjut";
                    cin.ignore();
                    cin.get();
                }
                
            } while (pilihan != 4);

        } else {

            int sisa = batas - i;
            if (sisa > 0) {
                cout << "Te..Tot salah, coba lagi dalam " << sisa << endl;
            } else {
                cout << "Ok sekarang. GET OUT!!!!!!!" << endl;
            }
        }

    }

    return 0;

    
}
