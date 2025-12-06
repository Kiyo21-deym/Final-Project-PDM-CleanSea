#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

// ==================== STRUKTUR DATA ====================

typedef struct {
    int id;
    char username[50];
    char email[100];
    char password_hash[256];
    char domisili[100];
    char tanggal_bergabung[20];
    int level;
    int poin;
    float total_kg;
    int followers;
    int following;
} User;

typedef struct {
    int id;
    int user_id;
    char jenis_sampah[50];
    float berat_sampah;
    char lokasi[100];
    char waktu[50];
    int poin_didapat;
    char status[20];
} DataSampah;

typedef struct {
    int id;
    char nama_lokasi[100];
    char kategori[50];
    char jenis_sampah_diterima[200];
    char jam_operasional[100];
    float latitude;
    float longitude;
    char prioritas[20];
} LokasiPengumpulan;

typedef struct {
    int id;
    int user_id;
    char isi_post[500];
    char waktu_post[50];
    int jumlah_komentar;
    int jumlah_rayakan;
} Post;

typedef struct {
    int id;
    char nama_badge[50];
    char deskripsi[200];
    int syarat_kg;
    int syarat_aksi;
} Badge;

// ==================== MODUL AUTENTIKASI ====================

void RegisterAccount(char username[], char email[], char password[], char confirm_password[]) {
    printf("\n=== REGISTRASI AKUN ===\n");
    
    if (strlen(username) == 0 || strlen(email) == 0 || strlen(password) == 0) {
        printf("Data tidak boleh kosong\n");
        return;
    }
    
    if (strcmp(password, confirm_password) != 0) {
        printf("Password tidak sama\n");
        return;
    }
    
    char password_hash[256];
    snprintf(password_hash, sizeof(password_hash), "HASH_%s", password);
    
    printf("Registrasi berhasil!\n");
    printf("Username: %s\n", username);
    printf("Email: %s\n", email);
}

void LoginAccount(char email[], char password[]) {
    printf("\n=== LOGIN AKUN ===\n");
    
    if (strlen(email) == 0 || strlen(password) == 0) {
        printf("Data tidak boleh kosong\n");
        return;
    }
    
    char password_hash_input[256];
    snprintf(password_hash_input, sizeof(password_hash_input), "HASH_%s", password);
    
    bool email_ditemukan = true;
    bool password_cocok = true;
    
    if (!email_ditemukan) {
        printf("Email tidak terdaftar\n");
        return;
    }
    
    if (!password_cocok) {
        printf("Password salah\n");
        return;
    }
    
    printf("Login berhasil!\n");
    printf("Session user aktif\n");
}

void RequestResetPassword(char email[]) {
    printf("\n=== REQUEST RESET PASSWORD ===\n");
    
    if (strlen(email) == 0) {
        printf("Email harus diisi\n");
        return;
    }
    
    bool email_terdaftar = true;
    if (!email_terdaftar) {
        printf("Email tidak terdaftar\n");
        return;
    }
    
    srand(time(NULL));
    int kode_verifikasi = 100000 + rand() % 900000;
    
    printf("Kode verifikasi telah dikirim ke email\n");
    printf("Kode: %d\n", kode_verifikasi);
}

void VerifyResetCode(char email[], int kode_input) {
    printf("\n=== VERIFIKASI KODE RESET ===\n");
    
    int kode_database = 123456;
    bool kode_expired = false;
    
    if (kode_input == kode_database && !kode_expired) {
        printf("Kode valid\n");
        printf("Silakan reset password Anda\n");
    } else {
        printf("Kode salah atau kedaluwarsa\n");
    }
}

void ResetPassword(char email[], char password_baru[], char confirm_password_baru[]) {
    printf("\n=== RESET PASSWORD ===\n");
    
    if (strcmp(password_baru, confirm_password_baru) != 0) {
        printf("Password tidak sama\n");
        return;
    }
    
    char password_hash_baru[256];
    snprintf(password_hash_baru, sizeof(password_hash_baru), "HASH_%s", password_baru);
    
    printf("Password berhasil diganti\n");
}

// ==================== MODUL HOME ====================

void LoadDashboard(int user_id) {
    printf("\n=== DASHBOARD ===\n");
    
    User user = {1, "JohnDoe", "john@mail.com", "", "Surabaya", 
                 "2024-01-15", 3, 250, 15.5, 10, 5};
    
    printf("Username: %s\n", user.username);
    printf("Level: %d\n", user.level);
    printf("Total Sampah: %.2f Kg\n", user.total_kg);
    printf("Poin: %d\n", user.poin);
    printf("Followers: %d | Following: %d\n", user.followers, user.following);
}

void DisplayGreeting(char username[]) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    int jam = t->tm_hour;
    
    char greeting[50];
    if (jam >= 5 && jam < 11) {
        strcpy(greeting, "Selamat pagi");
    } else if (jam >= 11 && jam < 16) {
        strcpy(greeting, "Selamat siang");
    } else if (jam >= 16 && jam < 19) {
        strcpy(greeting, "Selamat sore");
    } else {
        strcpy(greeting, "Selamat malam");
    }
    
    printf("\n%s, %s!\n", greeting, username);
}

void DisplayUserStats(float total_kg, int poin, int level) {
    printf("\n=== STATISTIK USER ===\n");
    printf("Total Sampah: %.2f Kg\n", total_kg);
    printf("Poin: %d\n", poin);
    printf("Level: %d\n", level);
}

void DisplayLeaderboardPreview(int user_id) {
    printf("\n=== TOP 3 LEADERBOARD ===\n");
    printf("1. AliceGreen - 50.5 Kg - 500 poin\n");
    printf("2. BobBlue - 45.2 Kg - 452 poin\n");
    printf("3. CharlieSea - 40.0 Kg - 400 poin\n");
    printf("\n[Lihat Semua]\n");
}

// ==================== MODUL PROFILE ====================

void LoadUserProfile(int user_id) {
    printf("\n=== PROFIL USER ===\n");
    
    User user = {1, "JohnDoe", "john@mail.com", "", "Surabaya", 
                 "2024-01-15", 3, 250, 15.5, 10, 5};
    
    printf("Username: %s\n", user.username);
    printf("Domisili: %s\n", user.domisili);
    printf("Bergabung: %s\n", user.tanggal_bergabung);
    printf("Status: Sea Saver Level %d\n", user.level);
    printf("Total Sampah: %.2f Kg\n", user.total_kg);
    printf("Poin: %d\n", user.poin);
    printf("Followers: %d | Following: %d\n", user.followers, user.following);
}

void TambahTeman(int user_id, int target_id) {
    printf("\n=== TAMBAH TEMAN ===\n");
    
    bool sudah_berteman = false;
    
    if (sudah_berteman) {
        printf("Sudah berteman\n");
    } else {
        printf("Berhasil berteman!\n");
    }
}

// ==================== MODUL TUKAR POIN ====================

void LoadRewardPage(int user_id) {
    printf("\n=== TUKAR POIN ===\n");
    printf("Poin Anda: 250\n\n");
    printf("Reward Tersedia:\n");
    printf("1. Voucher Shopee 50K (100 poin)\n");
    printf("2. Tas Ramah Lingkungan (150 poin)\n");
    printf("3. Saldo Dana Rp 20.000 (80 poin)\n");
}

void TukarPoinJadiUang(int user_id, int nominal_penarikan) {
    printf("\n=== TUKAR POIN KE UANG ===\n");
    
    int poin_user = 250;
    
    if (poin_user < nominal_penarikan) {
        printf("Poin tidak mencukupi\n");
        return;
    }
    
    poin_user -= nominal_penarikan;
    printf("Penukaran berhasil!\n");
    printf("Saldo bertambah Rp %d\n", nominal_penarikan * 250);
    printf("Poin tersisa: %d\n", poin_user);
}

void TukarPoinBarang(int user_id, int barang_id) {
    printf("\n=== TUKAR POIN BARANG ===\n");
    
    int poin_user = 250;
    int harga_poin_barang = 150;
    
    if (poin_user < harga_poin_barang) {
        printf("Poin tidak mencukupi\n");
        return;
    }
    
    poin_user -= harga_poin_barang;
    
    printf("Penukaran berhasil!\n");
    printf("Pilih layanan pengiriman:\n");
    printf("1. Diantar ke rumah\n");
    printf("2. Diambil di lokasi\n");
}

// ==================== MODUL CATAT SAMPAH ====================

void AdminScanQRCodeForSampah(int admin_id, char qr_data[]) {
    printf("\n=== SCAN QR CODE ===\n");
    
    bool is_admin = true;
    
    if (!is_admin) {
        printf("Akses ditolak - hanya admin\n");
        return;
    }
    
    int user_id = 1;
    
    printf("QR Code berhasil di-scan\n");
    printf("User: JohnDoe\n");
    printf("Level: 3\n");
    printf("Total Sampah: 15.5 Kg\n");
    printf("Total Poin: 250\n");
    printf("\nLanjut ke form input sampah...\n");
}

void AdminInputSampah(int admin_id, int user_id, char jenis_sampah[], float berat_sampah, char lokasi[]) {
    printf("\n=== INPUT DATA SAMPAH ===\n");
    
    bool is_admin = true;
    if (!is_admin) {
        printf("Akses ditolak - hanya admin\n");
        return;
    }
    
    int poin_didapat = (int)(berat_sampah * 10);
    
    printf("Data sampah berhasil direkam\n");
    printf("Jenis: %s\n", jenis_sampah);
    printf("Berat: %.2f Kg\n", berat_sampah);
    printf("Lokasi: %s\n", lokasi);
    printf("Poin diperoleh: %d\n", poin_didapat);
}

void OutputSampah(int user_id) {
    printf("\n=== RIWAYAT SAMPAH ===\n");
    printf("1. Plastik - 2.5 Kg - Pantai Kenjeran - 25 poin\n");
    printf("2. Botol - 1.2 Kg - Bank Sampah A - 12 poin\n");
    printf("3. Kertas - 3.0 Kg - Pantai Ria - 30 poin\n");
}

// ==================== MODUL LOKASI PENGUMPULAN ====================

float HitungJarak(float lat1, float lon1, float lat2, float lon2) {
    float dx = lat2 - lat1;
    float dy = lon2 - lon1;
    float jarak = sqrt(dx*dx + dy*dy) * 111.0;
    return jarak;
}

void LoadLokasiPengumpulan(int user_id) {
    printf("\n=== LOKASI PENGUMPULAN ===\n");
    
    LokasiPengumpulan lokasi[] = {
        {1, "Pantai Kenjeran", "Pantai", "Plastik, Botol, Kaleng", 
         "08:00 - 17:00", -7.2384, 112.7925, "Sedang"},
        {2, "Bank Sampah Surabaya", "Bank Sampah", "Semua jenis sampah", 
         "07:00 - 16:00", -7.2575, 112.7521, "Rendah"},
        {3, "Pantai Ria", "Pantai", "Plastik, Botol", 
         "06:00 - 18:00", -7.2289, 112.7844, "Tinggi"}
    };
    
    float user_lat = -7.2504;
    float user_lon = 112.7688;
    
    for (int i = 0; i < 3; i++) {
        float jarak = HitungJarak(user_lat, user_lon, lokasi[i].latitude, lokasi[i].longitude);
        printf("\n%d. %s\n", i+1, lokasi[i].nama_lokasi);
        printf("   Kategori: %s\n", lokasi[i].kategori);
        printf("   Jarak: %.2f km\n", jarak);
        printf("   Jam: %s\n", lokasi[i].jam_operasional);
        printf("   Prioritas: %s\n", lokasi[i].prioritas);
    }
}

// ==================== MODUL AKTIVITAS ====================

void LoadRiwayatPengumpulanSampah(int user_id) {
    printf("\n=== RIWAYAT PENGUMPULAN SAMPAH ===\n");
    printf("\n2024-12-05 10:30\n");
    printf("   Pantai Kenjeran\n");
    printf("   Plastik - 2.5 Kg\n");
    printf("   +25 poin\n");
    
    printf("\n2024-12-03 14:15\n");
    printf("   Bank Sampah A\n");
    printf("   Botol - 1.2 Kg\n");
    printf("   +12 poin\n");
    printf("   Badge: 10 Aksi Peduli\n");
}

void CekBadge(int user_id, float total_kg, int total_aksi) {
    printf("\n=== CEK BADGE ===\n");
    
    if (total_kg >= 3) {
        printf("Level 3 'Sea Saver' tercapai!\n");
    }
    
    if (total_aksi >= 10) {
        printf("Badge '10 Aksi Peduli' diperoleh!\n");
    }
}

// ==================== MODUL PERINGKAT ====================

void LoadLeaderboard(int user_id, char filter_periode[]) {
    printf("\n=== LEADERBOARD %s ===\n", filter_periode);
    
    printf("\nTOP 3:\n");
    printf("1. AliceGreen - 50.5 Kg - 505 poin\n");
    printf("2. BobBlue - 45.2 Kg - 452 poin\n");
    printf("3. CharlieSea - 40.0 Kg - 400 poin\n");
    
    printf("\nSTATISTIK:\n");
    printf("Total Peserta: 150\n");
    printf("Total Sampah: 1,250 Kg\n");
    printf("Sisa Waktu: 7 hari\n");
    
    printf("\nPERINGKAT ANDA:\n");
    printf("Ranking: 15\n");
    printf("JohnDoe - 15.5 Kg - 155 poin\n");
}

// ==================== MODUL KOMUNITAS ====================

void LoadCommunity(int user_id) {
    printf("\n=== KOMUNITAS ===\n");
    
    printf("\nAliceGreen - 2 jam lalu\n");
    printf("Berhasil mengumpulkan 5kg sampah di Pantai Kenjeran!\n");
    printf("12 komentar | 45 rayakan\n");
    
    printf("\nBobBlue - 5 jam lalu\n");
    printf("Level Up! Sekarang Sea Saver Level 5\n");
    printf("8 komentar | 30 rayakan\n");
}

void AddComment(int user_id, int post_id, char isi_komentar[]) {
    printf("\n=== TAMBAH KOMENTAR ===\n");
    
    if (strlen(isi_komentar) == 0) {
        printf("Komentar tidak boleh kosong\n");
        return;
    }
    
    printf("Komentar terkirim!\n");
    printf("\"%s\"\n", isi_komentar);
}

void CelebratePost(int user_id, int post_id) {
    printf("Post dirayakan!\n");
}

// ==================== MODUL PENCAPAIAN ====================

void CalculateMonthlyProgress(float total_kg_bulan_ini, float target_bulan_ini) {
    printf("\n=== PROGRESS BULANAN ===\n");
    
    float progress = (total_kg_bulan_ini / target_bulan_ini) * 100;
    
    printf("Target: %.2f Kg\n", target_bulan_ini);
    printf("Tercapai: %.2f Kg\n", total_kg_bulan_ini);
    printf("Progress: %.1f%%\n", progress);
    
    printf("[");
    int bars = (int)(progress / 5);
    for (int i = 0; i < 20; i++) {
        if (i < bars) printf("=");
        else printf(" ");
    }
    printf("]\n");
}

void UpdateUserLevel(float total_kg_user) {
    int level = 1;
    
    if (total_kg_user >= 3) level = 3;
    if (total_kg_user >= 10) level = 4;
    if (total_kg_user >= 25) level = 5;
    
    printf("\n=== UPDATE LEVEL ===\n");
    printf("Total Sampah: %.2f Kg\n", total_kg_user);
    printf("Level Anda: %d\n", level);
}

// ==================== MODUL BANTUAN ====================

void LoadHelpMenu() {
    printf("\n=== BANTUAN ===\n");
    printf("1. FAQ\n");
    printf("2. Chat dengan CS\n");
    printf("3. Email Support\n");
    printf("4. Tutorial Video\n");
    printf("5. Syarat & Ketentuan\n");
    printf("6. Keamanan & Privasi\n");
}

void LoadFAQ() {
    printf("\n=== FAQ ===\n");
    printf("\n1. Bagaimana cara mengumpulkan sampah?\n");
    printf("   Jawab: Kunjungi lokasi pengumpulan terdekat...\n");
    
    printf("\n2. Bagaimana cara menukar poin?\n");
    printf("   Jawab: Masuk ke menu Tukar Poin...\n");
    
    printf("\n3. Apa itu level dan badge?\n");
    printf("   Jawab: Level dan badge adalah pencapaian...\n");
}

// ==================== MAIN PROGRAM ====================

void tampilkanMenu() {
    printf("\n");
    printf("====================================\n");
    printf("     CLEANSEA - SISTEM MENU         \n");
    printf("====================================\n");
    printf("1.  Registrasi\n");
    printf("2.  Login\n");
    printf("3.  Dashboard\n");
    printf("4.  Profile\n");
    printf("5.  Tukar Poin\n");
    printf("6.  Catat Sampah\n");
    printf("7.  Lokasi Pengumpulan\n");
    printf("8.  Riwayat Aktivitas\n");
    printf("9.  Leaderboard\n");
    printf("10. Komunitas\n");
    printf("11. Pencapaian\n");
    printf("12. Bantuan\n");
    printf("0.  Keluar\n");
    printf("====================================\n");
}

int main() {
    int pilihan;
    
    printf("====================================\n");
    printf("         CLEANSEA SYSTEM            \n");
    printf("   Aplikasi Pengumpulan Sampah      \n");
    printf("====================================\n");
    
    do {
        tampilkanMenu();
        printf("Pilih menu: ");
        scanf("%d", &pilihan);
        getchar();
        
        switch(pilihan) {
            case 1: {
                char user[50], email[100], pass[50], conf[50];
                printf("\nUsername: "); fgets(user, 50, stdin); user[strcspn(user, "\n")] = 0;
                printf("Email: "); fgets(email, 100, stdin); email[strcspn(email, "\n")] = 0;
                printf("Password: "); fgets(pass, 50, stdin); pass[strcspn(pass, "\n")] = 0;
                printf("Konfirmasi Password: "); fgets(conf, 50, stdin); conf[strcspn(conf, "\n")] = 0;
                RegisterAccount(user, email, pass, conf);
                break;
            }
            case 2: {
                char email[100], pass[50];
                printf("\nEmail: "); fgets(email, 100, stdin); email[strcspn(email, "\n")] = 0;
                printf("Password: "); fgets(pass, 50, stdin); pass[strcspn(pass, "\n")] = 0;
                LoginAccount(email, pass);
                break;
            }
            case 3:
                DisplayGreeting("JohnDoe");
                LoadDashboard(1);
                DisplayLeaderboardPreview(1);
                break;
            case 4:
                LoadUserProfile(1);
                break;
            case 5:
                LoadRewardPage(1);
                break;
            case 6:
                AdminScanQRCodeForSampah(1, "QR12345");
                AdminInputSampah(1, 1, "Plastik", 2.5, "Pantai Kenjeran");
                break;
            case 7:
                LoadLokasiPengumpulan(1);
                break;
            case 8:
                LoadRiwayatPengumpulanSampah(1);
                CekBadge(1, 15.5, 12);
                break;
            case 9:
                LoadLeaderboard(1, "MINGGU INI");
                break;
            case 10:
                LoadCommunity(1);
                break;
            case 11:
                CalculateMonthlyProgress(8.5, 10.0);
                UpdateUserLevel(15.5);
                break;
            case 12:
                LoadHelpMenu();
                LoadFAQ();
                break;
            case 0:
                printf("\nTerima kasih telah menggunakan CleanSea!\n");
                break;
            default:
                printf("\nPilihan tidak valid!\n");
        }
        
        if (pilihan != 0) {
            printf("\nTekan Enter untuk melanjutkan...");
            getchar();
        }
        
    } while(pilihan != 0);
    
    return 0;
}