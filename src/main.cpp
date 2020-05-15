#include <bits/stdc++.h>
#include "polinom.hpp"

using namespace std;

int main() {
  srand(time(0));
  clock_t timer;
  int derajat;

  cout << "Masukkan derajat polinom yang diinginkan : ";
  cin >> derajat;

  Polinom A(derajat), B(derajat);
  cout << "Polinom A(x) yang terbuat adalah:" << endl;
  cout << "A(x) = ";
  A.cetak_polinom();

  cout << "Polinom B(X) yang terbuat adalah:" << endl;
  cout << "B(x) = ";
  B.cetak_polinom();

  timer = clock();
  int operasi_sekarang = jumlah_operasi;

  Polinom C = hasil_kali_bf(A, B);
  cout << "Hasil kali bruteforce adalah:" << endl;
  cout << "A(x)B(x) = ";
  C.cetak_polinom();

  int operasi_setelah = jumlah_operasi;
  cout << "Terjadi sebanyak " << operasi_setelah - operasi_sekarang << " jumlah operasi kali dan tambah" << endl;
  cout << "Waktu penghitungan : " << (1000.0) * (clock() - timer) / CLOCKS_PER_SEC << " ms" << endl << endl;
  
  timer = clock();
  operasi_sekarang = jumlah_operasi;

  Polinom D = hasil_kali_dnc(A, B);
  cout << "Hasil kali Divide and Conquer adalah:\n";
  cout << "A(x)B(x) = ";
  D.cetak_polinom();

  operasi_setelah = jumlah_operasi;
  cout << "Terjadi sebanyak " << operasi_setelah - operasi_sekarang << " jumlah operasi kali dan tambah" << endl;
  cout << "Waktu penghitungan : " << (1000.0) * (clock() - timer) / CLOCKS_PER_SEC << " ms" << endl;   

  return 0;
}