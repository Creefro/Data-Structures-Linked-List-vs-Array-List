// Linked List vs Array List.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>

struct ArrayList {
    int* bas; //dizinin baþlangýç adresini tutar
    void olustur(); //baþlangýç için gereken tanýmlarý içerir
    void ekle(int, int);//deðer ve sýra numarasý alarak ekleme yapar
    void guncelle(int, int);//deðer ve sýra numarasý alarak günceller
    void sil(int);//sýra numarasý alarak silme yapar
    void yazdir();//liste içeriðini ekrana yazar
    void bosalt();//listenin bellek alanlarýný iade eder
    int sayac;//liste kaç eleman olduðunu tutar
};

void ArrayList::olustur() {
    bas = new int;
    sayac = 0;
}
void ArrayList::ekle(int siraNo, int deger) {
    for (int i = sayac; i > siraNo; i--) {
        bas[i] = bas[i - 1];
    }
    bas[siraNo] = deger;
    sayac++;
}
void ArrayList::guncelle(int siraNo, int deger) {
    bas[siraNo] = deger;
}
void ArrayList::sil(int siraNo) {

    for (int i = siraNo; i < sayac; i++) {
        bas[i] = bas[i + 1];
    }
    //bas[sayac - 1] = 0;
    sayac--;
}
void ArrayList::bosalt() {
    delete[] bas;
}
void ArrayList::yazdir() {
    for (int i = 0; i < sayac; i++)
    {
        std::cout << bas[i] << "\n";
    }
}

struct Node {
    int deger; //düðümün sayýsal deðeri
    Node* sonraki;//sonraki düðüme iþaretçi
};

struct LinkedList {
    Node* bas; //listeninbaþlangýç adresini tutar
    void olustur(); //baþlangýç için gereken tanýmlarý içerir
    void ekle(int, int);//deðer ve sýra numarasý alarak ekleme yapar
    void guncelle(int, int);//deðer ve sýra numarasý alarak günceller
    void sil(int);//sýra numarasý alarak silme yapar
    void yazdir();//liste içeriðini ekrana yazar
    void bosalt();//listenin bellek alanlarýný iade eder
    int sayac;//liste kaç eleman olduðunu tutar
};

void LinkedList::olustur() {
    bas = NULL;
    sayac = 0;
}
void LinkedList::yazdir() {
    Node* tara;
    tara = bas;
    if (!tara) {
        std::cout << "Liste bos!!!" << std::endl;
        return;
    }
    while (tara) {
        std::cout << tara->deger << " ";
        tara = tara->sonraki;
    }
    std::cout << std::endl;
}
void LinkedList::sil(int siraNo) {
    Node* tara;
    Node* arka;
    int cter = 1;
    tara = bas;
    if (siraNo <= 0) {
        std::cout << "Bu indexte eleman yok\n";
        return;
    }
    if (siraNo == 1) {
        bas = bas->sonraki;
        delete tara;
        sayac--;
        return;
    }

    while ((tara != NULL) && (cter < siraNo)) {
        arka = tara;
        tara = tara->sonraki;
        cter++;
    }
    if (cter < siraNo) {
        std::cout << "Silinecek kayit bulnamadi\n";
    }
    else {
        arka->sonraki = tara->sonraki;
        delete tara;
        sayac--;
    }
}
void LinkedList::bosalt() {
    Node* p;
    while (bas) {
        p = bas;
        bas = bas->sonraki;
        delete p;
    }
    sayac = 0;
}
void LinkedList::guncelle(int siraNo, int deger) {
    Node* tara;
    Node* n = new Node();
    n->deger = deger;
    int cter = 1;
    tara = bas;
    while (tara && (sayac < siraNo + 1)) {
        sayac++;
        tara = tara->sonraki;
    }
    if (tara) {
        n->sonraki = tara->sonraki;
        *tara = *n;
    }
    else {
        std::cout << "Hata\n";
    }
}
void LinkedList::ekle(int siraNo, int deger) {
    Node* n = new Node();
    n->deger = deger;
    if (bas == NULL) {
        bas = n;
        sayac++;
        return;
    }
    sayac = 0;
    Node* tara;
    tara = bas;
    while (tara) {
        sayac++;
        tara = tara->sonraki;
    }
    tara = bas;
    if (sayac < siraNo) {
        std::cout << "Sira numarasi liste boyutunu asiyor!\n";
    }
    else {
        for (int i = 0; i < siraNo - 1;i++) {
            tara = tara->sonraki;
        }
        n->sonraki = tara->sonraki;
        tara->sonraki = n;
        sayac++;
    }
}

int main()
{
    int iteration = 1000;

    LinkedList* linkedList = new LinkedList();
    linkedList->olustur();

    int i;
    for (i = 0; i < iteration; i++)
    {
        linkedList->ekle(i, i);
    }


    std::cout << i << " elemanli bir listede:\n";
    std::cout << "LinkedList ile basa ";

    auto begin = std::chrono::high_resolution_clock::now();

    linkedList->ekle(0, 95);

    auto end = std::chrono::high_resolution_clock::now();



    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout << "ekleme suresi =>  " << elapsed.count() << "  mikro-saniye" << std::endl;

    ArrayList* arrayList = new ArrayList();
    linkedList->olustur();

    int j;
    for (j = 0; j < iteration; j++)
    {
        arrayList->ekle(i, i);
    }

    std::cout << j << " elemanli bir listede:\n";
    std::cout << "ArrayList ile basa ";

    auto begin1 = std::chrono::high_resolution_clock::now();

    arrayList->ekle(0, 95);

    auto end1 = std::chrono::high_resolution_clock::now();



    auto elapsed1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1);
    std::cout << "ekleme suresi =>  " << elapsed1.count() << "  mikro-saniye" << std::endl;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
