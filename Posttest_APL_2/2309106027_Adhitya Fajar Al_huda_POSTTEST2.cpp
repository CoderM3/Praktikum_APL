#include <iostream>
#include <iomanip>
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
        cin.ignore();

        if (nama == "Adhitya Fajar Al-Huda" && nim == "2309106027") {
            cout << "Login berhasil. Selamat datang, " << nama << "!" << endl;
            int maxRecords = 300; // Batas maksimum catatan pengeluaran
		    int recordCount = 0; // Jumlah catatan saat ini
		    int id[maxRecords];
		    string name[maxRecords];
		    double price[maxRecords];
            int pilihan;

            while (true) {
	            cout << "Catatan Pengeluaran Uang:" << endl;
	            cout << "1. Tambah data jika ada mengeluarkan uang bulan ini" << endl;
	            cout << "2. Lihat data pengeluaran" << endl;
	            cout << "3. Ganti atau update pengeluaran uang" << endl;
	            cout << "4. Delete data pengeluaran " << endl;
	            cout << "5. Keluar" << endl;
	            cout << "Pilih menu (1-5): ";
	            cin >> pilihan;
	
	            switch (pilihan) {
	                case 1:
	                if (recordCount < maxRecords) {
	                    recordCount++;
	                    id[recordCount] = recordCount;
				        cin.ignore();

	                    cout << "Input Nama barang: ";
	                    getline(cin, name[recordCount]);
	                    
	                    string priceInput;
				        cout << "Input Harga: ";
				        cin >> priceInput;
					
					try {
				        price[recordCount] = stoi(priceInput);
				        } catch (const invalid_argument& e) {
				            cout << "Harga harus berupa bilangan bulat. Coba lagi." << endl;
				            recordCount--;
				        }
					}
					else {
	                    cout << "Batas catatan tercapai. Tidak dapat menambah lebih banyak." << endl;
	                }
	                break;
	            	
					case 2:
					    cout << "ID       Nama        Harga" << endl;
					    for (int i = 1; i <= recordCount; i++) {
					        cout << id[i] << "         " << name[i] << "      " << fixed << setprecision(2) << price[i] << endl;
					    }
					    break;
	            	
	            	case 3:
	                int editId;
				    cout << "Masukkan ID catatan yang ingin diedit: ";
				    cin >> editId;
				    if (editId >= 1 && editId <= recordCount) {
				        
				        cin.ignore();
						cout << "Input Nama Baru: ";
				        getline(cin, name[editId]);

				        string priceInput;
				        cout << "Input Harga Baru: ";
				        cin >> priceInput;
				        
				    try {
				        price[recordCount] = stoi(priceInput);
				        } catch (const invalid_argument& e) {
				            cout << "Harga harus berupa bilangan bulat. Coba lagi." << endl;
				        }
					}
					else {
	                    cout << "ID tidak ditemukan" << endl;
	                }
	                break;
					                                                                         
	            	case 4:
				    int deleteId;
				    cout << "Masukkan ID catatan yang ingin dihapus: ";
				    cin >> deleteId;
				
				    if (cin.fail()) {
				        cout << "ID harus berupa bilangan bulat. Coba lagi." << endl;
				        cin.clear(); 
				        cin.ignore();
				    } else if (deleteId >= 1 && deleteId <= recordCount) {
					    // Geser semua catatan setelah ID yang dihapus ke posisi sebelumnya
					    for (int i = deleteId; i < recordCount; i++) {
					        id[i] = id[i + 1];
					        name[i] = name[i + 1];
					        price[i] = price[i + 1];
					    }
					    recordCount--;
					    cout << "Catatan dengan ID " << deleteId << " berhasil dihapus." << endl;
					} else {
					    cout << "ID tidak valid. Tidak ada catatan dengan ID tersebut." << endl;
					}
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
