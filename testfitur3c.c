#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Deklarasi Struct
typedef struct dokter{
    char nama[50];
    int maxShift;
    int shiftmingguan;
    char preferensi[10];
    int currShift;
}dokter;

typedef struct shift {
    dokter** dokter;
    int count_doc;
} shift;


typedef struct hari{
    shift* pagi;
    shift* siang;
    shift* malam;
}hari;

void hitung_pelanggaran_shift(dokter datadokter[], int total_dokter, hari* jadwal[], int total_hari) {
    int total_miss = 0; // dipindah ke luar loop agar akumulasi seluruh dokter

    for (int i = 0; i < total_dokter; i++) {
        int count = 0; // total shift untuk dokter ke-i
        int pref_match = 0; // shift sesuai preferensi

        for (int j = 0; j < total_hari; j++) {
            // Pagi
            for (int k = 0; k < jadwal[j]->pagi->count_doc; k++) {
                if (strcmp(datadokter[i].nama, jadwal[j]->pagi->dokter[k]->nama) == 0) {
                    count++;
                    if (strcmp(datadokter[i].preferensi, "pagi") == 0)
                        pref_match++;
                }
            }
            // Siang
            for (int k = 0; k < jadwal[j]->siang->count_doc; k++) {
                if (strcmp(datadokter[i].nama, jadwal[j]->siang->dokter[k]->nama) == 0) {
                    count++;
                    if (strcmp(datadokter[i].preferensi, "siang") == 0)
                        pref_match++;
                }
            }
            // Malam
            for (int k = 0; k < jadwal[j]->malam->count_doc; k++) {
                if (strcmp(datadokter[i].nama, jadwal[j]->malam->dokter[k]->nama) == 0) {
                    count++;
                    if (strcmp(datadokter[i].preferensi, "malam") == 0)
                        pref_match++;
                }
            }
        }

        int pref_miss = count - pref_match;
        printf("Dokter %s memiliki %d shift yang melanggar preferensi\n", datadokter[i].nama, pref_miss);
        total_miss += pref_miss; // akumulasi total pelanggaran dari semua dokter
    }

    printf("Total Pelanggaran Preferensi Shift: %d\n", total_miss);
}


int main (){
    dokter d1 = {"dr. Rina", 15, 5, "pagi", 0};
dokter d2 = {"dr. Budi", 10, 3, "malam", 0};

dokter datadokter[2] = {d1, d2};
int total_dokter = 2;

// Buat hari ke-1
hari* h1 = malloc(sizeof(hari));
h1->pagi = malloc(sizeof(shift));
h1->pagi->dokter = malloc(sizeof(dokter*) * 1);
h1->pagi->dokter[0] = &datadokter[1]; // dr. Budi disuruh shift pagi
h1->pagi->count_doc = 1;

h1->siang = malloc(sizeof(shift));
h1->siang->dokter = malloc(sizeof(dokter*) * 1);
h1->siang->dokter[0] = &datadokter[0]; // dr. Rina disuruh shift siang
h1->siang->count_doc = 1;

h1->malam = malloc(sizeof(shift));
h1->malam->dokter = NULL;
h1->malam->count_doc = 0;

hari* jadwal[1] = {h1};

hitung_pelanggaran_shift(datadokter, 2, jadwal, 1);

}






