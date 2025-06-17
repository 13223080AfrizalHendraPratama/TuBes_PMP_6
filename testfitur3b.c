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

void hitung_shift_per_dokter(dokter datadokter[], int total_dokter, hari* jadwal[], int total_hari) {
    for (int i = 0; i < total_dokter; i++) {
        int count = 0; // total shift untuk dokter ke-i
        int pref_match = 0; // total shift yang sesuai preferensi

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
        int pref_miss=count-pref_match;
        printf("Dokter %s menjalani %d shift (preferensi cocok: %d shift)\n", datadokter[i].nama, count, pref_miss);
    }
}

int main (){
    
}
