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

//Deklarasai Fungsi Print Jadwal Harian
void JadwalHarian(int tanggal, hari *jadwal){
    if(tanggal < 1 || tanggal > 30){
        printf("Tangga tidak ada!!");
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
    for(int i = 0; i < 30; i++){
        printf("============================================================\n");
        printf("                Jadwal Dokter Bulanan     \n");
        printf("============================================================\n");
        JadwalHarian(i+1, jadwal);
    }
}


void InformasiShift();
void InformasiPelanggaran();
void WriteJadwal();

int main(){
    int menu;
    int on = 1;
    hari jadwal[30];
    
    while(on){
        printf("============================================================\n");
        printf("               Silahkan Pilih Menu Yang Tersedia   \n");
        printf("============================================================\n");
        printf("");
        printf("======================== MENU =============================\n");
        printf("");
        printf("1. Tampilkan jadwal\n");
        printf("2. Informasi shift dokter\n");
        printf("3. Informasi pelanggaran shift\n");
        printf("4. Write jadwal ke file\n");
        printf("5. Keluar\n");
        printf("Pilihan menu: ");
        scanf("%d", &menu);
        getchar();

        if (menu == 1){
            int pilih_jadwal;
            printf("============================================================\n");
            printf("          Silahkan Pilih Jadwal Yang Ingin Ditampilkan   \n");
            printf("============================================================\n");
            printf("");
            printf("======================== MENU =============================\n");
            printf("");
            printf("1. Jadwal harian\n");
            printf("2. Jadwal mingguan\n");
            printf("3. Jadwal bulanan\n");
            printf("Pilihan menu: ");
            scanf("%d", &jadwal);
            getchar();

            if (pilih_jadwal == 1){
                int tanggal;
                printf("Pilih tanggal (1-30): ");
                scanf("%d", &tanggal);
                JadwalHarian(tanggal, jadwal);
            }
            else if (pilih_jadwal == 2){
                int minggu;
                printf("Pilih minggu (1-4): ");
                scanf("%d", &minggu);
                JadwalMingguan(minggu, jadwal);
            }
            else if (pilih_jadwal == 3){
                JadwalBulanan(jadwal);
            }
        }
        
        else if (menu == 2){
            InformasiShift();
        }

        else if (menu == 3){
            InformasiPelanggaran();
        }

        else if (menu == 4){
            WriteJadwal();
        }

        else if (menu == 5){
            on = 0;
        }
    }

    return 0;
}