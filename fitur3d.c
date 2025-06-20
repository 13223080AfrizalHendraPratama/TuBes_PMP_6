#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define MAX_MINGGU 5
#define MAX_HARI 7


const char* nama_hari[MAX_HARI] = {"Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu", "Minggu"};


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

hari kalendar[MAX_MINGGU][MAX_HARI];
void writecsv(hari *jadwal){
    FILE *file = fopen("jadwal.csv", "w");
    if(!file){
        printf("Gagal membuka file.\n");
        return;
    }

    // Header hari
    for(int i = 0; i < MAX_HARI; i++){
        fprintf(file, "%s", nama_hari[i]);
        if(i < MAX_HARI - 1){
            fprintf(file, ",");
        }
    }
    fprintf(file, "\n");

    //isi kalendar
    int tanggal = 0;
    for(int minggu = 0; minggu < MAX_MINGGU; minggu++){
        for(int day = 0; day < MAX_HARI; day++){
            if(tanggal >= 30){
                fprintf(file, "\"\"");
            } else{
                hari *h = &jadwal[tanggal];
                
                fprintf(file, "\"%d\nPagi: ", tanggal + 1);
                if(h->pagi && h->pagi->count_doc > 0){
                    for(int i = 0; i < h->pagi->count_doc; i++){
                        fprintf(file, "%s", h->pagi->dokter[i]->nama);
                        if(i < h->pagi->count_doc - 1){
                            fprintf(file, ", ");
                        }
                    }
                } else {
                    fprintf(file, "-");
                }
                
                fprintf(file, "\nSiang: ");                
                if(h->siang && h->siang->count_doc > 0){
                    for(int i = 0; i < h->siang->count_doc; i++){
                        fprintf(file, "%s", h->siang->dokter[i]->nama);
                        if(i < h->siang->count_doc - 1){
                            fprintf(file, ", ");
                        }
                    }
                } else {
                    fprintf(file, "-");
                }

                fprintf(file, "\nMalam:");

                if(h->malam && h->malam->count_doc > 0){
                    for(int i = 0; i < h->malam->count_doc; i++){
                        fprintf(file, "%s", h->malam->dokter[i]->nama);
                        if(i < h->malam->count_doc - 1){
                            fprintf(file, ", ");
                        }
                    }
                } else {
                    fprintf(file, "-");
                }
                fprintf(file, "\"");
                tanggal++;
            }
            if(day < MAX_HARI - 1){
                fprintf(file, ",");
            }
        }
    fprintf(file, "\n");
    }
    fclose(file);
    printf("✅ File jadwal.csv berhasil dibuat.\n");
}


