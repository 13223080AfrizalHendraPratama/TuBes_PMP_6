#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Konstanta

#define JUMLAH_HARI 30
#define SHIFT_PER_HARI 3
#define JUMLAH_SHIFT_PER_MINGGU 21
#define MAKS_DOKTER_PER_SHIFT 3

// Deklarasi Variabel Data ------------------------------------------------------------------------

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

void bacaFile(const char* namaFile, dokter** daftar, int* jumlah, int* kapasitas, int* berhasilmembaca) {
    FILE* file = fopen(namaFile, "r");
    if (file == NULL) {
        printf("Gagal membuka file: %s\n", namaFile);
        berhasilmembaca = 0;
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
    *berhasilmembaca = 1;

    fclose(file);
    printf("Berhasil membaca data dari file '%s'.\n", namaFile);
}


// Fungsi 2 - Assign Jadwal Dokter --------------------------------------------------------------------

// Fungsi menyalin daftar dokter
dokter* salinDaftarDokter(dokter* sumber, int jumlah) {
    dokter* temp = malloc(sizeof(dokter) * jumlah);
    for (int i = 0; i < jumlah; i++) {
        temp[i] = sumber[i]; 
    }
    return temp;
}

// Menghitung total shift yang bisa diisi semua dokter
int HitungJumlahShift(dokter* daftardokter, int jumlah){
    int totalDokter = 0;
    for (int i = 0; i < jumlah; i++) {
        totalDokter += daftardokter[i].maxShift;
    }
    return totalDokter;
}

// Reset shift mingguan ke 0 di awal minggu
void resetMingguan(dokter* daftardokter_, int jumlah) {
    for (int i = 0; i < jumlah; i++) {
        daftardokter_[i].shiftmingguan = 0;
    }
}

// Urutkan dokter berdasarkan jumlah shift yang sudah diambil
void merge(dokter* arr, int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = 0;
    int n = right - left + 1;

    dokter* temp = malloc(sizeof(dokter) * n);

    while (i <= mid && j <= right) {
        if (arr[i].currShift > arr[j].currShift) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (i = left, k = 0; i <= right; i++, k++) {
        arr[i] = temp[k];
    }

    free(temp);
}

void mergesort(dokter* arr, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergesort(arr, left, mid);
        mergesort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}


// Menugaskan dokter ke shift sesuai preferensi dan memastikan apakah ada yang kosong atau tidak
// Format input : array of struct daftarDokterPerShift_ , struct daftardokter_ , int jenis shift (0,1,2) , int jumlah_dokter, int totalshift tersedia
void AssignDokter(shift* daftarDokterPerShift_, dokter *daftardokter_, int jenisShift, int* jumlah_dokter, int totalShifttersedia){

}


// Fungsi utama penjadwalan
void penjadwalan(dokter* daftardokter_, int* jumlah_dokter, hari** jadwal_){

    // Deklarasi dan menyalin data dokter
    dokter* tempDaftar = salinDaftarDokter(daftardokter_, *jumlah_dokter);
    int jumlah_shift = HitungJumlahShift(tempDaftar, *jumlah_dokter);

    // kondisi apabila tidak memenuhi shift
    if ( jumlah_shift < JUMLAH_SHIFT_PER_MINGGU){
        printf("Jumlah shift tidak cukup. Tambahkan dokter atau naikkan shift maksimal.\n");
        free(tempDaftar);
        return;
    }

    // Declare memory array jadwal
    for (int hariKe = 0; hariKe < JUMLAH_HARI; hariKe++) {
        if (jadwal_[hariKe] == NULL) {
            jadwal_[hariKe] = malloc(sizeof(hari));
        }
    }

    // Loop setiap minggu untuk assign dokter -> Jadwal
    for (int hariKe = 0; hariKe < JUMLAH_HARI; hariKe++) {
        // Kondisi ketika sudah loop 1 minggu (7 hari)
        if (hariKe % 7 == 0) {
            resetMingguan(tempDaftar, *jumlah_dokter);
        }
        mergesort(tempDaftar, 0, *jumlah_dokter);

        // Deklarasi Dnynamic Array 
        jadwal_[hariKe]->pagi = malloc(sizeof(shift));
        jadwal_[hariKe]->siang = malloc(sizeof(shift));
        jadwal_[hariKe]->malam = malloc(sizeof(shift));

        jadwal_[hariKe]->pagi->dokter = malloc(sizeof(dokter*) * MAKS_DOKTER_PER_SHIFT);
        jadwal_[hariKe]->siang->dokter = malloc(sizeof(dokter*) * MAKS_DOKTER_PER_SHIFT);
        jadwal_[hariKe]->malam->dokter = malloc(sizeof(dokter*) * MAKS_DOKTER_PER_SHIFT);

        // Panggil Fungsi Assign Dokter
        AssignDokter(jadwal_[hariKe]->pagi, tempDaftar, 0, jumlah_dokter, jumlah_shift); // 
        AssignDokter(jadwal_[hariKe]->siang, tempDaftar, 1, jumlah_dokter, jumlah_shift); // 
        AssignDokter(jadwal_[hariKe]->malam, tempDaftar, 2, jumlah_dokter, jumlah_shift); //
    }
    free(tempDaftar);
}


void tampilkanJadwal(hari** jadwal_, int jumlah_hari) {
    const char* namaShift[] = {"Pagi", "Siang", "Malam"};

    for (int h = 0; h < jumlah_hari; h++) {
        printf("Hari ke-%d:\n", h + 1);

        shift* daftarShift[] = {
            jadwal_[h]->pagi,
            jadwal_[h]->siang,
            jadwal_[h]->malam
        };

        for (int s = 0; s < 3; s++) {
            printf("  Shift %s:\n", namaShift[s]);
            if (daftarShift[s] == NULL || daftarShift[s]->count_doc == 0) {
                printf("    Tidak ada dokter.\n");
            } else {
                for (int i = 0; i < daftarShift[s]->count_doc; i++) {
                    printf("    - %s\n", daftarShift[s]->dokter[i]->nama);
                }
            }
        }
        printf("\n");
    }
}




// Main Program ----------------------------------------------------------------------------------------

int main(){
    
    int jumlahDokter = 0;
    int kapasitas = 0;
    
    int menu;

    printf("\n");
    printf("============================================================\n");
    printf("  _______                        _   _                       \n");
    printf(" |__   __|                      | \\ | |                      \n");
    printf("    | | __ _ _ __  _ __   __ _  |  \\| | __ _ _ __ ___   __ _ \n");
    printf("    | |/ _` | '_ \\| '_ \\ / _` | | . ` |/ _` | '_ ` _ \\ / _` |\n");
    printf("    | | (_| | | | | |_) | (_| | | |\\  | (_| | | | | | | (_| |\n");
    printf("    |_|\\__,_|_| |_| .__/ \\__,_| |_| \\_|\\__,_|_| |_| |_|\\__,_|\n");
    printf("                  | |                                        \n");
    printf("                  |_|                                        \n");
    printf("\n");
    printf("           >>>  SISTEM PENJADWALAN DOKTER  <<<              \n");
    printf("           >>>  By Kelompok 6              <<<              \n");
    printf("============================================================\n");

    int berhasilmembaca = 0;
    while(berhasilmembaca == 0){
        char namaFile[50];
        printf("Masukkan nama file CSV: ");
        scanf("%s", namaFile);
        getchar();
        bacaFile(namaFile, &daftarDokter, &jumlahDokter, &kapasitas, &berhasilmembaca);
        if (berhasilmembaca == 1){
            do{
                printf("============================================================\n");
                printf("               Silahkan Pilih Menu Yang Tersedia   \n");
                printf("============================================================\n");
                printf("");
                printf("======================== MENU =============================\n");
                printf("1. Tambah Dokter\n");
                printf("2. Hapus Dokter\n");
                printf("3. Tampilkan Dokter\n");
                printf("4. Assign Dokter\n");
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
                    penjadwalan(daftarDokter, &jumlahDokter, jadwal);
                    tampilkanJadwal(jadwal, 30);
                }

                else if (menu == 0){
                    printf("Terima kasih!\n");
                    break;
                }
                else{
                    printf("Menu tidak tersedia!\n");
                }
            } while (menu != 0);
            break;
        }
    }
    free(daftarDokter);
    return 0;
}
