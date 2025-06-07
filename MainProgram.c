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


// Fungsi 1 - Memproses File --------------------------------------------------------------------

void tambahDokter (dokter** daftar, int* jumlah, int* kapasitas, dokter dokterBaru){
    if (*jumlah >= *kapasitas){
        int newKapasitas;
        if (*kapasitas == 0){
            newKapasitas = 2;
        }
        else{
            newKapasitas = *kapasitas * 2;
        }
        dokter* temp = realloc(*daftar, newKapasitas*sizeof(dokter));
        
        if (temp == NULL){
            printf("Gagal mengalokasikan memori!\n");
            return;
        }
        
        *daftar = temp;
        *kapasitas = newKapasitas;
    }
    (*daftar)[*jumlah] = dokterBaru;
    (*jumlah)++;
}

void hapusDokter(dokter* daftar, int* jumlah, const char* namaTarget) {
    int index = -1;

    for (int i = 0; i < *jumlah; i++) {
        if (strcmp(daftar[i].nama, namaTarget) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Dokter dengan nama '%s' tidak ditemukan.\n", namaTarget);
        return;
    }

    for (int i = index; i < *jumlah - 1; i++) {
        daftar[i] = daftar[i + 1];
    }

    (*jumlah)--;
    printf("Dokter '%s' berhasil dihapus.\n", namaTarget);
}

void tampilkanDokter(dokter* daftar, int jumlah) {
    if (jumlah == 0) {
        printf("Belum ada data dokter.\n");
        return;
    }

    printf("\n=== Daftar Dokter ===\n");
    for (int i = 0; i < jumlah; i++) {
        printf("%d. %s - Maks %d shift/minggu - Preferensi: %s\n",
               i + 1,
               daftar[i].nama,
               daftar[i].maxShift,
               daftar[i].preferensi);
    }
}

void bacaFile(const char* namaFile, dokter** daftar, int* jumlah, int* kapasitas) {
    FILE* file = fopen(namaFile, "r");
    if (file == NULL) {
        printf("Gagal membuka file: %s\n", namaFile);
        return;
    }

    char baris[256];

    while (fgets(baris, sizeof(baris), file)) {
        dokter baru;
        baris[strcspn(baris, "\n")] = '\0';
        char* token = strtok(baris, ",");
        if (token != NULL) {
            strcpy(baru.nama, token);
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            baru.maxShift = atoi(token);
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            strcpy(baru.preferensi, token);
        }

        tambahDokter(daftar, jumlah, kapasitas, baru);
    }

    fclose(file);
    printf("Berhasil membaca data dari file '%s'.\n", namaFile);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////


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
  //////////////////////////////////////////////////////////////////////////////////////////////////////
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
        AssignDokter(&tempDaftar, jumlah_dokter);
    }

}





//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

// Main Program ----------------------------------------------------------------------------------------

int main(){
    
    int jumlahDokter = 0;
    int kapasitas = 0;
    
    int menu;
    do{
        printf("\n=== MENU ===\n");
        printf("1. Tambah Dokter\n");
        printf("2. Hapus Dokter\n");
        printf("3. Tampilkan Dokter\n");
        printf("4. Baca File CSV\n");
        printf("5. Assign Dokter\n");
        printf("0. Kembali\n");
        printf("Pilihan menu: ");
        scanf("%d", &menu);
        getchar();

        if (menu == 1){
            dokter baru;
            printf("Nama dokter: ");
            fgets(baru.nama, sizeof(baru.nama), stdin);
            baru.nama[strcspn(baru.nama, "\n")] = '\0';

            printf("Maksimal shift per minggu: ");
            scanf("%d", &baru.maxShift);
            getchar();

            printf("Preferensi shift (Pagi/Siang/Malam): ");
            fgets(baru.preferensi, sizeof(baru.preferensi), stdin);
            baru.preferensi[strcspn(baru.preferensi, "\n")] = '\0';

            tambahDokter(&daftarDokter, &jumlahDokter, &kapasitas, baru);
        }

        else if (menu == 2){
            char namaHapus[20];
            printf("Nama dokter yang ingin dihapus: ");
            fgets(namaHapus, sizeof(namaHapus), stdin);
            namaHapus[strcspn(namaHapus, "\n")] = '\0';
            hapusDokter(daftarDokter, &jumlahDokter, namaHapus);
        }

        else if (menu == 3){
            tampilkanDokter(daftarDokter, jumlahDokter);
        }

        else if (menu == 4){
            char namaFile[50];
            printf("Masukkan nama file CSV: ");
            scanf("%s", namaFile);
            getchar();
            bacaFile(namaFile, &daftarDokter, &jumlahDokter, &kapasitas);
        }

        else if (menu == 5){
            penjadwalan(&daftarDokter, &jumlahDokter);
        }

        else if (menu == 0){
            printf("Terima kasih!\n");
            break;
        }
        else{
            printf("Menu tidak tersedia!\n");
        }
    } while (menu != 0);
    free(daftarDokter);
    return 0;
}
