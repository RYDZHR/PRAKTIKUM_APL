#include <iostream>

using namespace std;

int main(){
    int a = 2;
    int b = 2;
    string nama;

    cout << "hello world" << a + b << endl;
    cout << "c++ on fedora linux, lets go!!!!!!!!!" << endl;

    // cout << "Namamu Siapa: ";
    // cin >> nama;

    cout << "namamu siapa?: ";
    getline (cin, nama);

    cout << "Salam Kenal, " << nama << endl;

    return 0;
}
