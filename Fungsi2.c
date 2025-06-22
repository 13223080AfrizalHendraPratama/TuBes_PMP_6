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
    dokter dokter[1000];
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
        if (arr[i].currShift < arr[j].currShift) {
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
void AssignDokter(shift *daftarDokterPerShift_, dokter *daftardokter_, int jenisShift, int* jumlah_dokter, int* totalShifttersedia){
    int i;
    char preferensi[10];
    
    if (jenisShift == 0){
        strcpy(preferensi, "Pagi");
    }
    else if (jenisShift == 1){
        strcpy(preferensi,"Siang");
    }
    else if (jenisShift == 2){
        strcpy(preferensi, "Malam");
    }
    
    for(i=0;i<*jumlah_dokter;i++){
        if (strcmp(daftardokter_[i].preferensi, preferensi) == 0 && daftardokter_[i].shiftmingguan < daftardokter_[i].maxShift){
            daftarDokterPerShift_->dokter[daftarDokterPerShift_->count_doc] = daftardokter_[i];
            daftarDokterPerShift_->count_doc += 1;
            (*totalShifttersedia)--;
            daftardokter_[i].shiftmingguan++;
            daftardokter_[i].currShift++;
            break;
        }
    }
}

// Mengisi apabila ada shift yang kosong oleh dotkter dari preferensi manapun
void checkshift(shift* shiftkosong, dokter *daftardokter_, int* jumlah_dokter, int* totalShifttersedia){
    int i,j;
    if (shiftkosong->count_doc == 0){
        for(j=0;j<*jumlah_dokter;j++){
            if (daftardokter_[j].shiftmingguan < daftardokter_[j].maxShift){
                shiftkosong->dokter[shiftkosong->count_doc] = daftardokter_[j];
                shiftkosong->count_doc++;
                (*totalShifttersedia)--;
                daftardokter_[j].shiftmingguan++;
                daftardokter_[j].currShift++;
                break;
                }
            }
        }
    }

// Memastikan semua dokter ter-assign pada satu minggu
int checkdokter(dokter *daftardokter_, int* jumlah_dokter, hari** jadwal_,int hariKe, int* totalShifttersedia ){
    int i;
    int hari1 = hariKe - 6;
    int hari2 = hariKe - 6;
    int hari3 = hariKe - 6;

    for (i=0;i<*jumlah_dokter;i++){
        if (daftardokter_[i].shiftmingguan == 0){
            if (strcmp(daftardokter_[i].preferensi, "Pagi")==0){
                jadwal_[hari1]->pagi->dokter[jadwal_[hari1]->pagi->count_doc] = daftardokter_[i];
                jadwal_[hari1]->pagi->count_doc++;
                (*totalShifttersedia)--;
                daftardokter_[i].shiftmingguan++;
                daftardokter_[i].currShift++;
                hari1++;

                if (hari1 > hariKe){
                    hari1 = hariKe - 6; 
                }
            } 
            else if  (strcmp(daftardokter_[i].preferensi, "Siang")==0){
                jadwal_[hari2]->siang->dokter[jadwal_[hari2]->siang->count_doc] = daftardokter_[i];
                jadwal_[hari2]->siang->count_doc++;
                (*totalShifttersedia)--;
                daftardokter_[i].shiftmingguan++;
                daftardokter_[i].currShift++;
                hari2++;
        
                if (hari2 > hariKe){
                    hari2 = hariKe - 6; 
                }  
            } 
            else if  (strcmp(daftardokter_[i].preferensi, "Malam")==0){
                jadwal_[hari3]->malam->dokter[jadwal_[hari3]->malam->count_doc] = daftardokter_[i];
                jadwal_[hari3]->malam->count_doc++;
                (*totalShifttersedia)--;
                daftardokter_[i].shiftmingguan++;
                daftardokter_[i].currShift++;  
                hari3++;

                if (hari3 > hariKe){
                    hari3 = hariKe - 6; 
                }
            } 
        }
    }
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
        mergesort(tempDaftar, 0, *jumlah_dokter-1);
        // Deklarasi Dnynamic Array 
        jadwal_[hariKe]->pagi = malloc(sizeof(shift));
        jadwal_[hariKe]->siang = malloc(sizeof(shift));
        jadwal_[hariKe]->malam = malloc(sizeof(shift));

        jadwal_[hariKe]->pagi->count_doc = 0;
        jadwal_[hariKe]->siang->count_doc = 0;
        jadwal_[hariKe]->malam->count_doc = 0;

        // Panggil Fungsi Assign Dokter
        AssignDokter(jadwal_[hariKe]->pagi, tempDaftar, 0, jumlah_dokter, &jumlah_shift); // 
        AssignDokter(jadwal_[hariKe]->siang, tempDaftar, 1, jumlah_dokter, &jumlah_shift); // 
        AssignDokter(jadwal_[hariKe]->malam, tempDaftar, 2, jumlah_dokter, &jumlah_shift); //
    
        // Kondisi ketika sudah loop 1 minggu (7 hari)
        if ((hariKe+1) % 7 == 0) {
            int i;
            int hari = hariKe - 6;
            for (i=hari; i<hariKe+1; i++){
                checkshift(jadwal_[i]->pagi, tempDaftar, jumlah_dokter, &jumlah_shift);
                checkshift(jadwal_[i]->siang, tempDaftar, jumlah_dokter, &jumlah_shift);
                checkshift(jadwal_[i]->malam, tempDaftar, jumlah_dokter, &jumlah_shift);
            }
            checkdokter(tempDaftar, jumlah_dokter, jadwal_, hariKe, &jumlah_shift);
            resetMingguan(tempDaftar, *jumlah_dokter);
        }

        else if ((hariKe+1)%30 == 0){
            int i;
            int hari = hariKe - 1;
            for (i=hari; i<hariKe+1; i++){
                checkshift(jadwal_[i]->pagi, tempDaftar, jumlah_dokter, &jumlah_shift);
                checkshift(jadwal_[i]->siang, tempDaftar, jumlah_dokter, &jumlah_shift);
                checkshift(jadwal_[i]->malam, tempDaftar, jumlah_dokter, &jumlah_shift);
            }
            checkdokter(tempDaftar, jumlah_dokter, jadwal_, hariKe, &jumlah_shift);
            resetMingguan(tempDaftar, *jumlah_dokter);
        }
    }
    free(tempDaftar);
}
