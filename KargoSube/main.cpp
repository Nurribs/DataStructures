#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#define musterisayisi 120

using namespace std;

struct Musteri {
	int islemSure;
	int id;
};

Musteri musteriBilgi() {
	Musteri musteri{};
	int num;
	num = (int)musteri.id;
	musteri.islemSure = (rand() % 271) + 30;
	return musteri;
}

struct Dugum {
	int veri;
	Dugum* sonraki;
};

struct ListKuyruk {
	Dugum* bas = NULL;
	Dugum* dugum = new Dugum;
	int kuyrukboyutu = 0;

	void kapat() {
		Dugum* p;
		while (bas != NULL)
		{
			p = bas->sonraki;
			delete bas;
			bas = p;
		}
	}

	void ekle(int islemsure) {
		dugum->veri = islemsure;
		dugum->sonraki = bas;
		bas = dugum;
	}

	int cikar() {
		Musteri musteri;
		Dugum* ustdugum;
		int gecici;
		ustdugum = bas;
		bas = bas->sonraki;
		gecici = ustdugum->veri;
		delete ustdugum;
		kuyrugaEkle(gecici);
		return gecici;
	}

	void kuyrugaEkle(int islemsure) {
		Dugum* yeni = new Dugum;
		yeni->veri = islemsure;
		if (kuyrukboyutu == 0)
		{
			yeni->sonraki = NULL;
		}
		else {
			yeni->sonraki = dugum;
		}
		dugum = yeni;
		kuyrukboyutu++;
	}

	void kuyruktanCikar() {
		int toplamSure = 0;
		Musteri musteri{};
		cout << "LISTE ILE OLUSTURULAN KUYRUK: " << endl;
		if (kuyrukboyutu > 0)
		{
			Dugum* ptr = dugum;
			for (int i = 1; i <= kuyrukboyutu; i++)
			{
				ptr = ptr->sonraki;
				toplamSure += ptr->veri;
			cout << i << ". musterinin islem suresi " << ptr->veri << " saniyedir. Toplam islem suresi: " << toplamSure << endl << endl;
			}
			ptr->sonraki = NULL;
			kuyrukboyutu--;
		}
		else
		{
			cout << "kuyruk zaten bos!" << endl;
		}
	}
};

struct DiziKuyruk {
	int musteriler[musterisayisi];
	int bas,son;

	DiziKuyruk() {
		bas = -1;
		son = -1;
	}

	bool bosmu() {
		return bas == -1;
	}

	bool dolumu() {
		return son == musterisayisi - 1;
	}

	void kuyrugaekle(int islemsure) {
		if (dolumu()) {
			cout << "Kuyruk dolu" << endl;
			return;
		}
		else if (bosmu()) {
			bas = 0;
			son = 0;
		}
		else {
			son++;
		}
		musteriler[son] = islemsure;
	}

	int kuyruktancikar() {
		if (bosmu()) {
			cout << "Kuyruk bos" << endl;
			return -1;
		}
		int data = musteriler[bas];
		if (bas == son) {
			bas = -1;
			son = -1;
		}
		else {
			bas++;
		}
		return data;
	}

	void yazdir() {
		cout << "DIZI ILE OLUSTURULAN KUYRUK: " << endl;
		Musteri musteri{};
		int toplamsure = 0;
		musteri.id = 1;

		for (int i = musterisayisi-1; i >=0; i--) {
			toplamsure += musteriler[i];
			cout << musteri.id++ << ". musterinin islem suresi " << musteriler[i] << " saniyedir. Toplam islem suresi: " << toplamsure << endl << endl;
		}
		int temp;
		musteri.id = 1;

		for (int i = 0; i < musterisayisi; i++) {
			for (int j = i + 1; j < musterisayisi; j++) {
				if (musteriler[i] > musteriler[j]) {
					temp = musteriler[i];
					musteriler[i] = musteriler[j];
					musteriler[j] = temp;
				}
			}
		}
		toplamsure = 0;
		cout << "MUSTERILERIN ISLEM SURESINE GORE SIRALAMASI:   "<<endl<<endl;
		for (int i = 0; i <musterisayisi; i++) {
			toplamsure += musteriler[i];
			cout << musteri.id++ << ". musterinin islem suresi " << musteriler[i] << " saniyedir. Toplam islem suresi: " << toplamsure << endl << endl;
		}
	}
};

int main(int argc, char* argv[]) {

     srand(time(NULL));

	 int N = 120;

	float toplamSure = 0;
	float ortalamaSure = 0;

    ListKuyruk y1;
	DiziKuyruk y2;

	for (int i = 0; i <N; i++) {
		    Musteri musteri= musteriBilgi();
            toplamSure+=musteri.islemSure;
			musteri.id = i + musteri.id;
		    y1.ekle(musteri.islemSure);
			y1.kuyrugaEkle(musteri.islemSure);
			y2.kuyrugaekle(musteri.islemSure);

	}
      y1.kuyruktanCikar();
      y1.kapat();
      y2.yazdir();

	  ortalamaSure = toplamSure / N;
	  cout << "Gecen Ortalama Islem Suresi: " << ortalamaSure << endl;
	  cout << endl;

	return EXIT_SUCCESS;
}

