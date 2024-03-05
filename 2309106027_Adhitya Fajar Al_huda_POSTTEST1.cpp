#include <iostream>
using namespace std;

int main() {
    string nama;
    string nim;
    int kesempatan = 3;

    while (kesempatan > 0) {
        cout << "Masukkan nama Anda: ";
        getline(cin, nama);

        cout << "Masukkan NIM Anda: ";
        cin >> nim;

        if (nama == "Adhitya Fajar Al-Huda" && nim == "2309106027") {
            cout << "Login berhasil. Selamat datang, " << nama << "!" << endl;
            // Menu konversi mata uang
            double rupiah, dollar, euro, yen;
            int pilihan;
            
            while (true) {
	            cout << "Menu Konversi Mata Uang:" << endl;
	            cout << "1. Rupiah ke (Dollar, Euro, Yen)" << endl;
	            cout << "2. Dollar ke (Rupiah, Euro, Yen)" << endl;
	            cout << "3. Euro ke (Rupiah, Dollar, Yen)" << endl;
	            cout << "4. Yen ke (Rupiah, Dollar, Euro)" << endl;
	            cout << "5. Keluar" << endl;
	            cout << "Pilih menu (1-5): ";
	            cin >> pilihan;
	
	            switch (pilihan) {
	                case 1:
	                cout << "Masukkan jumlah Rupiah: ";
	                cin >> rupiah;
	
					
	            	dollar = rupiah / 15000; 
	            	cout << "Dollar: " << dollar << endl;
	
	            	
	            	euro = rupiah / 17000;
	            	cout << "Euro: " << euro << endl;
	
	            	
	            	yen = rupiah / 140;
	            	cout << "Yen: " << yen << endl;
	            	break;
	            	
	            	case 2:
	                cout << "Masukkan jumlah Dollar: ";
	                cin >> dollar;
	
					
	            	 rupiah = dollar * 15000; 
	            	cout << "rupiah: " << rupiah << endl;
	
	            	
	            	euro = dollar * 0.92; 
	            	cout << "Euro: " << euro << endl;
	
	            	
	            	yen = dollar * 150.51; 
	            	cout << "Yen: " << yen << endl;
	            	break;
	            	
	            	case 3:
	                cout << "Masukkan jumlah Euro: ";
	                cin >> euro;
	
					
	            	rupiah = euro * 15000; 
	            	cout << "rupiah: " << rupiah << endl;
	
	            	
	            	dollar = euro * 1.09; 
	            	cout << "Dollar: " << dollar << endl;
	
	            
	            	yen = euro * 128.91; 
	            	cout << "Yen: " << yen << endl;
	            	break;
	            	
	            	case 4:
	                cout << "Masukkan jumlah Yen: ";
	                cin >> euro;
	
					
	            	rupiah = yen * 128.91; 
	            	cout << "rupiah: " << rupiah << endl;
	
	            	
	            	dollar = yen * 0.00876; 
	            	cout << "Dollar: " << dollar << endl;
	
	            	
	            	euro = yen * 0.007;
	            	cout << "Euro: " << euro << endl;
	            	break;
	            	
	            	case 5:
                        cout << "Terima kasih telah menggunakan program. Program berakhir." << endl;
                        return 0;
	
	                default:
	                    cout << "Pilihan tidak valid." << endl;
	        	}
            }

			break;
        } else {
            kesempatan--;
            cout << "Login gagal. Sisa kesempatan: " << kesempatan << endl;
        }
    }

    if (kesempatan == 0) {
        cout << "Anda telah melebihi batas percobaan. Program berakhir." << endl;
    }

    return 0;
}
