#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definisi struct
typedef struct dokter {
    char nama[50];
    int maxShift;
    int shiftmingguan;
    char preferensi[10];
    int currShift;
} dokter;

typedef struct shift {
    dokter** dokter;
    int count_doc;
} shift;

typedef struct hari {
    shift* pagi;
    shift* siang;
    shift* malam;
} hari;

// Deklarasi Fungsi Print Jadwal Harian
void JadwalHarian(int tanggal, hari *jadwal){
    if(tanggal < 1 || tanggal > 30){
        printf("Tangga tidak ada!!\n");
        return;
    } 
    hari *data = &jadwal[tanggal-1]; 
    printf("============================================================\n");
    printf("             Jadwal Dokter Hari ke - %d      \n", tanggal);
    printf("============================================================\n");
    printf("Shift Pagi: \n");
    if(data->pagi->count_doc == 0){
        printf("Tidak ada dokter di jadwal\n");
    }else{
        for(int i = 0; i < data->pagi->count_doc; i++){
            printf("%d. %s\n", i+1, data->pagi->dokter[i]->nama);
        }
    }
    printf("Shift Siang: \n");
    if(data->siang->count_doc == 0){
        printf("Tidak ada dokter di jadwal\n");
    }else{
        for(int i = 0; i < data->siang->count_doc; i++){
            printf("%d. %s\n", i+1, data->siang->dokter[i]->nama);
        }
    }
    printf("Shift malam: \n");
    if(data->malam->count_doc == 0){
        printf("Tidak ada dokter di jadwal\n");
    }else{
        for(int i = 0; i < data->malam->count_doc; i++){
            printf("%d. %s\n", i+1, data->malam->dokter[i]->nama);
        }
    }
    printf("============================================================\n");
}

// Deklarasi Fungsi Untuk Print Jadwal Mingguan
void JadwalMingguan(int minggu, hari *jadwal){
    if(minggu < 1 || minggu > 4){
        printf("Minggu tidak tersedia");
        return;
    }
    printf("============================================================\n");
    printf("             Jadwal Dokter Minggu ke - %d      \n", minggu);
    printf("============================================================\n");

    int start = (minggu-1)*7;
    int end = start + 7;
    if (end > 30) end = 30;

    for(int i = start; i < end; i++){
        JadwalHarian(i+1, jadwal);
    }
}

// Deklarasi Fungsi Untuk Print Jadwal Bulanan
void JadwalBulanan(hari *jadwal){
    printf("============================================================\n");
    printf("                Jadwal Dokter Bulanan     \n");
    printf("============================================================\n");
    for(int i = 0; i < 30; i++){
        JadwalHarian(i+1, jadwal);
    }
}

// Fungsi untuk inisialisasi data dokter
dokter* initDokter(const char* nama, int maxShift, int shiftmingguan, const char* preferensi, int currShift) {
    dokter* d = (dokter*)malloc(sizeof(dokter));
    if (d == NULL) {
        printf("Error: Gagal alokasi memori untuk dokter!\n");
        return NULL;
    }
    strcpy(d->nama, nama);
    d->maxShift = maxShift;
    d->shiftmingguan = shiftmingguan;
    strcpy(d->preferensi, preferensi);
    d->currShift = currShift;
    return d;
}

// Fungsi untuk inisialisasi jadwal dengan kasus uji
hari* initJadwal() {
    hari* jadwal = (hari*)malloc(30 * sizeof(hari));
    if (jadwal == NULL) {
        printf("Error: Gagal alokasi memori untuk jadwal!\n");
        return NULL;
    }

    // Inisialisasi data dokter
    dokter* dokter1 = initDokter("Dr. Andi", 5, 2, "pagi", 3);
    dokter* dokter2 = initDokter("Dr. Budi", 4, 3, "siang", 2);
    dokter* dokter3 = initDokter("Dr. Cita", 5, 1, "malam", 1);
    
    if (dokter1 == NULL || dokter2 == NULL || dokter3 == NULL) {
        free(jadwal);
        return NULL;
    }

    // Inisialisasi jadwal untuk 30 hari
    for (int i = 0; i < 30; i++) {
        // Alokasi memori untuk shift
        jadwal[i].pagi = (shift*)malloc(sizeof(shift));
        jadwal[i].siang = (shift*)malloc(sizeof(shift));
        jadwal[i].malam = (shift*)malloc(sizeof(shift));
        
        if (jadwal[i].pagi == NULL || jadwal[i].siang == NULL || jadwal[i].malam == NULL) {
            printf("Error: Gagal alokasi memori untuk shift!\n");
            free(jadwal[i].pagi);
            free(jadwal[i].siang);
            free(jadwal[i].malam);
            free(jadwal);
            return NULL;
        }

        // Kasus uji: Hari 2-6 (normal), Hari 7 (shift kosong), Hari 8 (dokter NULL)
        if (i >= 1 && i <= 5) { // Normal: 2 dokter pagi, 1 siang, 1 malam
            // Shift Pagi
            jadwal[i].pagi->count_doc = 2;
            jadwal[i].pagi->dokter = (dokter**)malloc(2 * sizeof(dokter*));
            if (jadwal[i].pagi->dokter == NULL) {
                printf("Error: Gagal alokasi memori untuk dokter!\n");
                return NULL;
            }
            jadwal[i].pagi->dokter[0] = dokter1;
            jadwal[i].pagi->dokter[1] = dokter2;
            
            // Shift Siang
            jadwal[i].siang->count_doc = 1;
            jadwal[i].siang->dokter = (dokter**)malloc(1 * sizeof(dokter*));
            if (jadwal[i].siang->dokter == NULL) {
                printf("Error: Gagal alokasi memori untuk dokter!\n");
                return NULL;
            }
            jadwal[i].siang->dokter[0] = dokter2;
            
            // Shift Malam
            jadwal[i].malam->count_doc = 1;
            jadwal[i].malam->dokter = (dokter**)malloc(1 * sizeof(dokter*));
            if (jadwal[i].malam->dokter == NULL) {
                printf("Error: Gagal alokasi memori untuk dokter!\n");
                return NULL;
            }
            jadwal[i].malam->dokter[0] = dokter3;
        } else if (i == 6) { // Kasus: Shift kosong
            jadwal[i].pagi->count_doc = 0;
            jadwal[i].pagi->dokter = NULL;
            jadwal[i].siang->count_doc = 0;
            jadwal[i].siang->dokter = NULL;
            jadwal[i].malam->count_doc = 0;
            jadwal[i].malam->dokter = NULL;
        } else if (i == 7) { // Kasus: Beberapa dokter NULL
            jadwal[i].pagi->count_doc = 2;
            jadwal[i].pagi->dokter = (dokter**)malloc(2 * sizeof(dokter*));
            if (jadwal[i].pagi->dokter == NULL) {
                printf("Error: Gagal alokasi memori untuk dokter!\n");
                return NULL;
            }
            jadwal[i].pagi->dokter[0] = dokter1;
            jadwal[i].pagi->dokter[1] = NULL; // Simulasi data tidak valid
            
            jadwal[i].siang->count_doc = 1;
            jadwal[i].siang->dokter = (dokter**)malloc(1 * sizeof(dokter*));
            if (jadwal[i].siang->dokter == NULL) {
                printf("Error: Gagal alokasi memori untuk dokter!\n");
                return NULL;
            }
            jadwal[i].siang->dokter[0] = dokter2;
            
            jadwal[i].malam->count_doc = 1;
            jadwal[i].malam->dokter = (dokter**)malloc(1 * sizeof(dokter*));
            if (jadwal[i].malam->dokter == NULL) {
                printf("Error: Gagal alokasi memori untuk dokter!\n");
                return NULL;
            }
            jadwal[i].malam->dokter[0] = dokter3;
        } else { // Hari lain: kosong atau inisialisasi dasar
            jadwal[i].pagi->count_doc = 0;
            jadwal[i].pagi->dokter = NULL;
            jadwal[i].siang->count_doc = 0;
            jadwal[i].siang->dokter = NULL;
            jadwal[i].malam->count_doc = 0;
            jadwal[i].malam->dokter = NULL;
        }
    }
    return jadwal;
}

// Fungsi untuk membersihkan memori
void cleanupJadwal(hari* jadwal, dokter* d1, dokter* d2, dokter* d3) {
    if (jadwal == NULL) return;
    
    for (int i = 0; i < 30; i++) {
        if (jadwal[i].pagi != NULL) {
            if (jadwal[i].pagi->dokter != NULL) free(jadwal[i].pagi->dokter);
            free(jadwal[i].pagi);
        }
        if (jadwal[i].siang != NULL) {
            if (jadwal[i].siang->dokter != NULL) free(jadwal[i].siang->dokter);
            free(jadwal[i].siang);
        }
        if (jadwal[i].malam != NULL) {
            if (jadwal[i].malam->dokter != NULL) free(jadwal[i].malam->dokter);
            free(jadwal[i].malam);
        }
    }
    free(jadwal);
    free(d1);
    free(d2);
    free(d3);
}

// Fungsi pengujian
void testJadwal() {
    printf("===== Mulai Pengujian Fungsi Jadwal =====\n\n");
    
    // Inisialisasi jadwal
    hari* jadwal = initJadwal();
    if (jadwal == NULL) {
        printf("Gagal inisialisasi jadwal untuk pengujian!\n");
        return;
    }
    
    // Ambil referensi dokter untuk cleanup
    dokter* dokter1 = jadwal[1].pagi->dokter ? jadwal[1].pagi->dokter[0] : NULL;
    dokter* dokter2 = jadwal[1].pagi->dokter ? jadwal[1].pagi->dokter[1] : NULL;
    dokter* dokter3 = jadwal[1].malam->dokter ? jadwal[1].malam->dokter[0] : NULL;
    
    // Test Case 1: JadwalHarian - Tanggal valid (normal)
    printf("Test Case 1: JadwalHarian - Tanggal valid (Hari 2)\n");
    JadwalHarian(2, jadwal);
    printf("\n");
    
    // Test Case 2: JadwalHarian - Tanggal tidak valid (terlalu rendah)
    printf("Test Case 2: JadwalHarian - Tanggal tidak valid (Hari 1)\n");
    JadwalHarian(1, jadwal);
    printf("\n");
    
    // Test Case 3: JadwalHarian - Tanggal tidak valid (terlalu tinggi)
    printf("Test Case 3: JadwalHarian - Tanggal tidak valid (Hari 31)\n");
    JadwalHarian(31, jadwal);
    printf("\n");
    
    // Test Case 4: JadwalHarian - Shift kosong
    printf("Test Case 4: JadwalHarian - Shift kosong (Hari 7)\n");
    JadwalHarian(7, jadwal);
    printf("\n");
    
    // Test Case 5: JadwalMingguan - Minggu valid
    printf("Test Case 5: JadwalMingguan - Minggu valid (Minggu 2)\n");
    JadwalMingguan(2, jadwal);
    printf("\n");
    
    // Test Case 6: JadwalMingguan - Minggu tidak valid (terlalu rendah)
    printf("Test Case 6: JadwalMingguan - Minggu tidak valid (Minggu 1)\n");
    JadwalMingguan(1, jadwal);
    printf("\n");
    
    // Test Case 7: JadwalMingguan - Minggu tidak valid (terlalu tinggi)
    printf("Test Case 7: JadwalMingguan - Minggu tidak valid (Minggu 5)\n");
    JadwalMingguan(5, jadwal);
    printf("\n");
    
    // Test Case 8: JadwalBulanan - Seluruh jadwal
    printf("Test Case 8: JadwalBulanan - Seluruh 30 hari\n");
    JadwalBulanan(jadwal);
    printf("\n");
    
    // Bersihkan memori
    cleanupJadwal(jadwal, dokter1, dokter2, dokter3);
    printf("===== Selesai Pengujian Fungsi Jadwal =====\n");
}

int main() {
    testJadwal();
    return 0;
}