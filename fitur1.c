#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dokter{
    char nama[50];
    int maxShift;
    char preferensi[10];
    int currShift;
}dokter;

void tambahDokter(dokter** daftar, int* jumlah, int* kapasitas, dokter dokterBaru){
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

int main(){
    dokter* daftarDokter = NULL;
    int jumlahDokter = 0;
    int kapasitas = 0;
    
    int menu;
    do{
        printf("\n=== MENU ===\n");
        printf("1. Tambah Dokter\n");
        printf("2. Hapus Dokter\n");
        printf("3. Tampilkan Dokter\n");
        printf("4. Baca File CSV\n");
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

        else if (menu == 0){
            printf("Terima kasih!\n");
        }
        else{
            printf("Menu tidak tersedia!\n");
        }
    } while (menu != 0);
    free(daftarDokter);
    return 0;
}