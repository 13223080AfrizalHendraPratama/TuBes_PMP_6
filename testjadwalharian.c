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

//Deklarasai Fungsi 
void JadwalHarian(int tanggal, hari *jadwal){
    if(tanggal <= 1 && tanggal >= 30){
        printf("Tangga tidak ada!!");
        return;
    } 
    hari *data = &jadwal[tanggal-1]; 
    printf("============================================================\n");
    printf("             Daftar Dokter Hari ke - %d      \n", tanggal);
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

int main(){
hari jadwal[30];
    
    // Deklarasi array untuk data dokter (contoh sederhana)
    int jumlahDokter = 3; // Misal ada 3 dokter
    dokter daftarDokter[3]; // Array statis untuk dokter
    
    // Inisialisasi data dokter (contoh)
    strcpy(daftarDokter[0].nama, "Dr. Andi");
    daftarDokter[0].maxShift = 5;
    daftarDokter[0].shiftmingguan = 2;
    strcpy(daftarDokter[0].preferensi, "pagi");
    daftarDokter[0].currShift = 1;
    
    strcpy(daftarDokter[1].nama, "Dr. Budi");
    daftarDokter[1].maxShift = 4;
    daftarDokter[1].shiftmingguan = 3;
    strcpy(daftarDokter[1].preferensi, "siang");
    daftarDokter[1].currShift = 2;
    
    strcpy(daftarDokter[2].nama, "Dr. Cita");
    daftarDokter[2].maxShift = 5;
    daftarDokter[2].shiftmingguan = 1;
    strcpy(daftarDokter[2].preferensi, "malam");
    daftarDokter[2].currShift = 1;
    
    // Inisialisasi jadwal untuk 30 hari
    for (int i = 0; i < 30; i++) {
        // Alokasi memori untuk setiap shift (pagi, siang, malam)
        jadwal[i].pagi = (shift*)malloc(sizeof(shift));
        jadwal[i].siang = (shift*)malloc(sizeof(shift));
        jadwal[i].malam = (shift*)malloc(sizeof(shift));
        
        // Validasi alokasi memori
        if (jadwal[i].pagi == NULL || jadwal[i].siang == NULL || jadwal[i].malam == NULL) {
            printf("Error: Gagal alokasi memori untuk shift!\n");
            return 1;
        }
        
        // Contoh: Inisialisasi shift pagi, siang, malam (misal 2 dokter di pagi, 1 di siang, 1 di malam)
        // Shift Pagi
        jadwal[i].pagi->count_doc = 2; // 2 dokter di shift pagi
        jadwal[i].pagi->dokter = (dokter**)malloc(2 * sizeof(dokter*));
        if (jadwal[i].pagi->dokter == NULL) {
            printf("Error: Gagal alokasi memori untuk dokter!\n");
            return 1;
        }
        jadwal[i].pagi->dokter[0] = &daftarDokter[0]; // Dr. Andi
        jadwal[i].pagi->dokter[1] = &daftarDokter[1]; // Dr. Budi
        
        // Shift Siang
        jadwal[i].siang->count_doc = 1; // 1 dokter di shift siang
        jadwal[i].siang->dokter = (dokter**)malloc(1 * sizeof(dokter*));
        if (jadwal[i].siang->dokter == NULL) {
            printf("Error: Gagal alokasi memori untuk dokter!\n");
            return 1;
        }
        jadwal[i].siang->dokter[0] = &daftarDokter[1]; // Dr. Budi
        
        // Shift Malam
        jadwal[i].malam->count_doc = 1; // 1 dokter di shift malam
        jadwal[i].malam->dokter = (dokter**)malloc(1 * sizeof(dokter*));
        if (jadwal[i].malam->dokter == NULL) {
            printf("Error: Gagal alokasi memori untuk dokter!\n");
            return 1;
        }
        jadwal[i].malam->dokter[0] = &daftarDokter[2]; // Dr. Cita
    }
    
    // Panggil fungsi JadwalHarian untuk hari ke-6 (indeks 5)
    JadwalHarian(5, jadwal);
    
    // Bebaskan memori
    for (int i = 0; i < 30; i++) {
        // Bebaskan array dokter di setiap shift
        free(jadwal[i].pagi->dokter);
        free(jadwal[i].siang->dokter);
        free(jadwal[i].malam->dokter);
        // Bebaskan struct shift
        free(jadwal[i].pagi);
        free(jadwal[i].siang);
        free(jadwal[i].malam);
    }
    
    return 0;
}
