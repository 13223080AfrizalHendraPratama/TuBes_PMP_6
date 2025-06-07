#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define JUMLAH_HARI 30
#define SHIFT_PER_HARI 3
#define JUMLAH_SHIFT_PER_MINGGU 21

// Deklarasi Variabel Data ------------------------------------------------------------------------

typedef struct dokter{
    char nama[50];
    int maxShift;
    int shiftmingguan;
    char preferensi[10];
    int currShift;
}dokter;

typedef struct shift{
    dokter* dokter;
    int count_doc; // hitung dokter yang ada di shift
}shift;


typedef struct hari{
    shift* pagi;
    shift* siang;
    shift* malam;
}hari;


// Deklarasi Variabel Global Data

hari* jadwal[30];
dokter* daftarDokter = NULL;

// Fungsi 2 - Assign Jadwal Dokter --------------------------------------------------------------------

dokter* salinDaftarDokter(dokter* sumber, int jumlah) {
    dokter* temp = malloc(sizeof(dokter) * jumlah);
    for (int i = 0; i < jumlah; i++) {
        temp[i] = sumber[i]; 
    }
    return temp;
}

int HitungJumlahShift(dokter* daftardokter, int jumlah){
    int totalDokter = 0;
    for (int i = 0; i < jumlah; i++) {
        totalDokter += daftardokter[i].maxShift;
    }
    return totalDokter;
}

void resetMingguan(dokter* daftardokter_, int jumlah) {
    for (int i = 0; i < jumlah; i++) {
        daftardokter_[i].shiftmingguan = daftarDokter[i].maxShift;
    }
}

void bubbleSortDokter(dokter *daftardokter_, int jumlah) {
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            if (daftardokter_[j].currShift > daftardokter_[j + 1].currShift) {
                dokter temp = daftardokter_[j];
                daftardokter_[j] = daftardokter_[j + 1];
                daftardokter_[j + 1] = temp;
            }
        }
    }
}

void AssignDokter(){


}

void penjadwalan(dokter* daftar, int* jumlah_dokter){
    dokter* tempDaftar = salinDaftarDokter(daftarDokter, jumlah_dokter); // Salin Data agar tidak berubah

    if (HitungJumlahShift(&tempDaftar, jumlah_dokter) < JUMLAH_SHIFT_PER_MINGGU){
        printf("Jumlah shift tidak cukup. Tambahkan dokter atau naikkan shift maksimal.\n");
        return;
    }

    for (int hariKe = 0; hariKe < JUMLAH_HARI; hariKe++) {
        if (hariKe % 7 == 0) {
            resetMingguan(&tempDaftar, jumlah_dokter);
        }
        bubbleSortDokter(&tempDaftar, jumlah_dokter);
    }

}


