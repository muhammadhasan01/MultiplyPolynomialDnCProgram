#ifndef _POLINOM_HPP_
#define _POLINOM_HPP_

#include <bits/stdc++.h>

using namespace std;

int jumlah_operasi = 0;

class Polinom {
  protected:
  int derajat;
  deque<int> polinom;
  
  public:
  Polinom() {
    derajat = -1;
    polinom.clear();
  }

  Polinom(int n) {
    derajat = n;
    polinom.resize(n + 1);
    for (int i = 0; i <= derajat; i++) {
      polinom[i] = rand() % 200 - 100;
    }
  }

  Polinom(const Polinom& p) {
    polinom = p.polinom;
    derajat = p.derajat;
  }

  Polinom(const Polinom& p, int s, int e) {
    derajat = e - s;
    polinom.resize(e - s + 1);
    for (int i = s, j = 0; i <= e; i++, j++) {
      polinom[j] = p.polinom[i];
    }
  }

  Polinom(const deque<int>& p) {
    polinom = p;
    derajat = (int) polinom.size() - 1;
  }

  Polinom& operator=(const Polinom& p) {
    polinom = p.polinom;
    derajat = p.derajat;
    return *this;
  }

  void add(int x) {
    derajat++;
    polinom.push_back(x);
  }

  void cetak_polinom() {
    if (derajat == 0) {
      cout << polinom[0] << endl;
      return;
    }

    for (int i = 0; i <= derajat; i++) {
      if (polinom[i] == 0) continue;
      if (i == 0) {
        cout << polinom[i] << " ";
        continue;
      }
      if (polinom[i] > 0) {
        if (i > 0) cout << "+ ";
        cout << polinom[i] << "x^" << i << " ";
      } else if (i == 0) {
        cout << polinom[i] << " ";
      } else {
        cout << "- " << -polinom[i] << "x^" << i << " ";
      }
    }
    cout << endl << endl;
  }

  friend Polinom operator+(const Polinom& p1, const Polinom& p2) {
    Polinom result;
    result.derajat = max(p1.derajat, p2.derajat);
    result.polinom.resize(result.derajat + 1);
    for (int i = 0; i <= result.derajat; i++) {
      int c_1 = (i <= p1.derajat ? p1.polinom[i] : 0);
      int c_2 = (i <= p2.derajat ? p2.polinom[i] : 0);
      result.polinom[i] = c_1 + c_2;
    }
    while (result.derajat >= 0 && result.polinom.back() == 0) {
      result.derajat--;
      result.polinom.pop_back();
    }
    return result;
  }
  
  friend Polinom operator-(const Polinom& p1, const Polinom& p2) {
   Polinom result;
    result.derajat = max(p1.derajat, p2.derajat);
    result.polinom.resize(result.derajat + 1);
    for (int i = 0; i <= result.derajat; i++) {
      int c_1 = (i <= p1.derajat ? p1.polinom[i] : 0);
      int c_2 = (i <= p2.derajat ? p2.polinom[i] : 0);
      result.polinom[i] = c_1 - c_2;
    }
    while (result.derajat >= 0 && result.polinom.back() == 0) {
      result.derajat--;
      result.polinom.pop_back();
    }
    return result;
  }

  friend Polinom kali_x_pangkat(Polinom &p, int n) {
    p.derajat += n;
    for (int i = 0; i < n; i++) p.polinom.push_front(0);
    jumlah_operasi += n + 1;
    return p;
  }

  friend Polinom hasil_kali_bf(Polinom p1, Polinom p2) {
    Polinom hasil_polinom;
    deque<int> hasil;
    int derajat = p1.derajat;
    int hasil_derajat = p1.derajat + p2.derajat;
    jumlah_operasi += 2;

    for (int i = 0; i <= p1.derajat + p2.derajat; i++) {
      hasil.push_back(0);
      jumlah_operasi++;
    }

    for (int i = 0; i <= p1.derajat; i++) {
      for (int j = 0; j <= p2.derajat; j++) {
        hasil[i + j] += (p1.polinom[i] * p2.polinom[j]);
        jumlah_operasi += 2;
      }
    }

    hasil_polinom.derajat = p1.derajat + p2.derajat;
    jumlah_operasi++;
    for (int i = 0; i <= p1.derajat + p2.derajat; i++) {
      hasil_polinom.polinom.push_back(hasil[i]);
      jumlah_operasi++;
    }

    return hasil_polinom;
  }

  friend Polinom hasil_kali_dnc(const Polinom &p1, const Polinom &p2) {
    if (p1.derajat == 0) {
      jumlah_operasi++;
      deque<int> dq(1, p1.polinom[0] * p2.polinom[0]);
      return Polinom(dq);
    }
    int len = p1.derajat;
    int mid = (len + 1) / 2;
    int m = len / 2 - (len % 2 == 0);
    jumlah_operasi += 4;

    Polinom A0 = Polinom(p1, 0, m); 
    Polinom A1 = Polinom(p1, m + 1, len);
    Polinom B0 = Polinom(p2, 0, m);
    Polinom B1 = Polinom(p2, m + 1, len);

    Polinom Y = hasil_kali_dnc(A0 + A1, B0 + B1);
    Polinom U = hasil_kali_dnc(A0, B0);
    Polinom Z = hasil_kali_dnc(A1, B1);
    Polinom T = Y - U - Z;

    return U + kali_x_pangkat(T, mid) + kali_x_pangkat(Z, 2 * mid);
  }
};

#endif
