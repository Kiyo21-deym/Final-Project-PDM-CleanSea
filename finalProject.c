#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct user {
    int id;
    char username[50];
    char email[100];
    char password[50];
    char domisili[100];
    char tanggal_bergabung[20];
    int level;
    int poin;
    float total_kg;
    int followers;
    int following;
} user;

void loginAccount(char email[], char password[]);
void requestResetPassword(char email[], char password[]);
void resetPassword(char password[], int resetCode);
int verifyResetCode(int resetCode);
void redeemPointsToCash(struct user *u, int redeemAmount);
void adminInputSampah(struct user *u);
void loadCollectionLocationsHistory();

void registerAccount(char username[], char email[], char password[], char confirmPassword[]) {

    if(strlen(username) == 0 || strlen(email) == 0 || strlen(password) == 0){
        printf("All fields are required. Please try again.\n");
        return;
    }

    if(strcmp(password, confirmPassword) != 0){
        printf("Passwords do not match. Please try again.\n");
        return;
    }

    printf("Registration successful!\n");
    loginAccount(email, password);

}

void loginAccount(char email[], char password[]) {
    char inputEmail[50], inputPassword[50];
    printf("\n== Account Login ==\n");

    while (1){
        int ask = 0;
        printf("Enter Email\t: ");
        scanf("%[^\n]", inputEmail);
        printf("Enter Password\t: ");
        scanf("%[^\n]", inputPassword);
        if (strcmp(inputEmail, email) == 0 && strcmp(inputPassword, password) == 0) {
            printf("Login successful!\n");
            break;
        } else {
            printf("Invalid username or password. Please try again.\n");
            ask++;
            if (ask >= 1){
                char choice;
                printf("Forgot Password? (y/n): ");
                scanf("%c", &choice);
                if (choice == 'y' || choice == 'Y') {
                    requestResetPassword(email, password);
                }
            }
        }
    }
}

void requestResetPassword(char email[], char password[]){

    char inputEmail[50];
    printf("\n== Request Password Reset ==\n");
    while(1){
        printf("Enter your registered email: ");
        scanf("%[^\n]", inputEmail);
        if(strcmp(inputEmail, email) == 0){
            break;
        }
        else {
            printf("Email not found. Please try again.\n");
        }
    }

    printf("Password reset link has been sent to your email: %s\n", email);
    srand(time(NULL));
    int resetCode = rand() % 999999 + 100000;
    printf("(In email) Your password reset code is: %d\n", resetCode);
    resetPassword(password, resetCode);
}

int verifyResetCode(int resetCode){
    int inutCode, valid = 0;
    printf("\n== Verify Reset Code ==\n");
    while (1){
        printf("Enter the password reset code: ");
        scanf("%d", &inutCode);
        if (inutCode == resetCode) {
            printf("Reset code verified successfully!\n");
            valid = 1;
            break;
        } else {
            printf("Invalid reset code. Please try again.\n");
        }
    }
    return valid;
}

void resetPassword(char password[], int resetCode){
    if (verifyResetCode(resetCode) == 1) {
        printf("\nYou can now reset your password.\n");
        while (1){
            char newPassword[50];
            printf("Enter New Password\t: ");
            scanf("%[^\n]", newPassword);
            if (newPassword[0] == '\0') {
                printf("Password cannot be empty. Please try again.\n");
            }
            else {
                strcpy(password, newPassword);
                printf("Password has been reset successfully!\n");
                break;
            }
        }
    }
}

void loadDashboard(struct user *u) {
    printf("\n=== DASHBOARD ===\n");
    printf("Username: %s\n", u->username);
    printf("Level: %d\n", u->level);
    printf("Total Waste Collected: %.2f Kg\n", u->total_kg);
    printf("Points: %d\n", u->poin);
    printf("Followers: %d | Following: %d\n", u->followers, u->following);
}

void displayGreeting(char username[]){
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    int hour = t->tm_hour;

    char greeting[50];
    if (hour >= 5 && hour < 11) {
        strcpy(greeting, "Good Morning");
    } else if (hour >= 11 && hour < 16) {
        strcpy(greeting, "Good Afternoon");
    } else if (hour >= 16 && hour < 19) {
        strcpy(greeting, "Good Evening");
    } else {
        strcpy(greeting, "Good Night");
    }

    printf("\n%s, %s!\n", greeting, username);
}

void displayUserStats(float total_kg, int poin, int level){
    printf("\n== User Statistics ==\n");
    printf("Total Waste Collected: %.2f Kg\n", total_kg);
    printf("Points: %d\n", poin);
    printf("Level: %d\n", level);

}

void displayLeaderboardPreview() {
    printf("\n=== TOP 3 LEADERBOARD ===\n");
    printf("1. AliceGreen - 50.5 Kg - 500 poin\n");
    printf("2. BobBlue - 45.2 Kg - 452 poin\n");
    printf("3. CharlieSea - 40.0 Kg - 400 poin\n");
    printf("\n[Lihat Semua]\n");
}

void loadUserProfile(struct user *u) {
    printf("\n=== USER PROFILE ===\n");
    printf("Username: %s\n", u->username);
    printf("Email: %s\n", u->email);
    printf("Level: %d\n", u->level);
    printf("Points: %d\n", u->poin);
    printf("Total Waste Collected: %.2f Kg\n", u->total_kg);
    printf("Followers: %d | Following: %d\n", u->followers, u->following);
}

void loadRewardPage(struct user *u) {
    printf("\n=== REDEEM POINTS ===\n");
    printf("Your Points: %d\n\n", u->poin);
    printf("Available Rewards:\n");
    printf("1. Shopee Voucher 50K (100 points)\n");
    printf("2. Eco-friendly Bag (150 points)\n");
    printf("3. Dana Balance Rp 20.000,00 (80 points)\n");
    printf("=================================\n");
    printf("Select an option to redeem or 0 to exit: ");
    int userChoice;
    scanf("%d", &userChoice);
    switch (userChoice) {
        case 1:
            printf("Redeemed Shopee Voucher 50K!\n");
            u->poin -= 100;
            break;
        case 2:
            printf("Redeemed Eco-friendly Bag!\n");
            u->poin -= 150;
            break;
        case 3:
            redeemPointsToCash(u, 80);
            break;
        case 0:
            printf("Exiting reward page.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
    }
}

void redeemPointsToCash(struct user *u, int redeemAmount) {
    printf("\n=== REDEEM POINTS TO CASH ===\n");

    if (u->poin < redeemAmount) {
        printf("Insufficient points\n");
        return;
    }

    u->poin -= redeemAmount;
    printf("Redemption successful!\n");
    printf("Balance increased by Rp20.000,00\n");
    printf("Remaining Points: %d\n", u->poin);
}

void adminScanQRCodeForSampah(char qr_data[], struct user *u) {
    printf("\n=== SCAN QR CODE ===\n");
    
    bool is_admin = true;
    
    if (!is_admin) {
        printf("Akses ditolak - hanya admin\n");
        return;
    }
    
    printf("QR Code berhasil di-scan\n");
    printf("User: %s\n", u->username);
    printf("Level: %d\n", u->level);
    printf("Total Sampah: %.2f Kg\n", u->total_kg);
    printf("Total Poin: %d\n", u->poin);
    printf("\nLanjutkan ke input data sampah...\n");

    adminInputSampah(u);
}

void adminInputSampah(struct user *u) {
    printf("\n=== INPUT DATA SAMPAH ===\n");
    
    int user_id; char jenis_sampah[100]; float berat_sampah; char lokasi[100];

    printf("Input data for User ID: %d\n", u->id);
    while(1){
        printf("[Kaca, Plastik, Kertas, Elektronik, Logam, Minyak Jelantah]\n");
        printf("Tuliskan Jenis Sampah sesuai pilihan di atas.\n");
        printf("Jenis Sampah: ");
        scanf("%[^\n]", jenis_sampah);
        if(strcmp(jenis_sampah, "Kaca") == 0){
            printf("Berat Sampah (Kg): ");
            scanf("%f", &berat_sampah);
            break;
        }
        else if(strcmp(jenis_sampah, "Plastik") == 0){
            printf("Berat Sampah (Kg): ");
            scanf("%f", &berat_sampah);
            break;
        }
        else if(strcmp(jenis_sampah, "Kertas") == 0){
            printf("Berat Sampah (Kg): ");
            scanf("%f", &berat_sampah);
            break;
        }
        else if(strcmp(jenis_sampah, "Elektronik") == 0){
            printf("Berat Sampah (Kg): ");
            scanf("%f", &berat_sampah);
            break;
        }
        else if(strcmp(jenis_sampah, "Logam") == 0){
            printf("Berat Sampah (Kg): ");
            scanf("%f", &berat_sampah);
            break;
        }
        else if(strcmp(jenis_sampah, "Minyak Jelantah") == 0){
            printf("Berat Sampah (Kg): ");
            scanf("%f", &berat_sampah);
            break;
        }
        else {
            printf("Jenis sampah tidak dikenali. Silakan coba lagi.\n");
            continue;
        }
    }
    printf("Lokasi Pengumpulan: ");
    scanf("%[^\n]", lokasi);

    int poin_didapat = 0;
    if(strcmp(jenis_sampah, "Kaca") == 0){
        poin_didapat = (int)(berat_sampah * 10);
    }
    else if(strcmp(jenis_sampah, "Plastik") == 0){
        poin_didapat = (int)(berat_sampah * 70);
    }
    else if(strcmp(jenis_sampah, "Kertas") == 0){
        poin_didapat = (int)(berat_sampah * 30);
    }
    else if(strcmp(jenis_sampah, "Elektronik") == 0){
        poin_didapat = (int)(berat_sampah * 100);
    }
    else if(strcmp(jenis_sampah, "Logam") == 0){
        poin_didapat = (int)(berat_sampah * 150);
    }
    else if(strcmp(jenis_sampah, "Minyak Jelantah") == 0){
        poin_didapat = (int)(berat_sampah * 20);
    }
    
    printf("\nData sampah berhasil direkam\n");
    printf("Jenis: %s\n", jenis_sampah);
    printf("Berat: %.2f Kg\n", berat_sampah);
    printf("Lokasi: %s\n", lokasi);
    printf("Poin diperoleh: %d\n", poin_didapat);

    FILE *fp = fopen("riwayat_sampah.txt", "w");
    if (fp != NULL) {
        fprintf(fp, "\"%s\" - %.2f Kg - \"%s\" - %d poin\n", jenis_sampah, berat_sampah, lokasi, poin_didapat);
        fclose(fp);
    } else {
        printf("Error saving waste record.\n");
    }
}

void OutputSampah(int user_id) {
    printf("\n=== RIWAYAT SAMPAH ===\n");
    FILE *fp = fopen("riwayat_sampah.txt", "r");
    char line[256];
    int num = 0;
    while(fgets(line, sizeof(line), fp) != NULL){
        printf("%d. ", num++);
        int poin_didapat; char jenis_sampah[50]; float berat_sampah; char lokasi[100];
        fscanf("\"%[^\"]\" - %f Kg - \"%[^\"]\" - %d poin\n", jenis_sampah, &berat_sampah, lokasi, &poin_didapat);
        printf("%-10s - %-10.2f Kg - %-10s - %d poin\n", jenis_sampah, berat_sampah, lokasi, poin_didapat);
    }
}

void loadCollectionLocations(struct user *u) {
    printf("\n=== COLLECTION LOCATIONS ===\n");
    printf("1. Lokasi A - Sampah Organik, Anorganik - 08:00-16:00\n");
    printf("2. Lokasi B - Sampah Elektronik - 09:00-17:00\n");
    printf("3. Lokasi C - Sampah Plastik, Kertas - 10:00-18:00\n");
    printf("=================================\n");
}

void loadCollectionLocationsHistory() {
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

void checkBadge(struct user *u) {
    printf("\n=== CEK BADGE ===\n");
    
    if (u->total_kg >= 3) {
        printf("Level 3 'Sea Saver' tercapai!\n");
    }
    printf("Badge '10 Aksi Peduli' diperoleh!\n");
}

void LoadLeaderboard(char filter_periode[]) {
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

void loadCommunity() {
    printf("\n=== KOMUNITAS ===\n");
    
    printf("\nAliceGreen - 2 jam lalu\n");
    printf("Berhasil mengumpulkan 5kg sampah di Pantai Kenjeran!\n");
    printf("12 komentar | 45 rayakan\n");
    
    printf("\nBobBlue - 5 jam lalu\n");
    printf("Level Up! Sekarang Sea Saver Level 5\n");
    printf("8 komentar | 30 rayakan\n");
}

void calculateMonthlyProgress(float total_kg_bulan_ini, float target_bulan_ini) {
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

void loadHelpMenu() {
    printf("\n=== BANTUAN ===\n");
    printf("1. FAQ\n");
    printf("2. Chat dengan CS\n");
    printf("3. Email Support\n");
    printf("4. Tutorial Video\n");
    printf("5. Syarat & Ketentuan\n");
    printf("6. Keamanan & Privasi\n");
}

void loadFAQ() {
    printf("\n=== FAQ ===\n");
    printf("\n1. Bagaimana cara mengumpulkan sampah?\n");
    printf("   Jawab: Kunjungi lokasi pengumpulan terdekat...\n");
    
    printf("\n2. Bagaimana cara menukar poin?\n");
    printf("   Jawab: Masuk ke menu Tukar Poin...\n");
    
    printf("\n3. Apa itu level dan badge?\n");
    printf("   Jawab: Level dan badge adalah pencapaian...\n");
}

int main(){

    int userChoice;

    printf("=================================\n");
    printf("            CLEAN SEA            \n");
    printf("    Waste Collection Management  \n");
    printf("=================================\n\n");

    printf("=================================\n");
    printf("   Welcome to Clean Sea System   \n");
    printf("=================================\n");
    printf("Menu:\n");
    printf("1. Register Account\n");
    printf("2. Login Account\n");
    printf("3. Dashboard\n");
    printf("4. Profile\n");
    printf("5. Redeem Points\n");
    printf("6. Record Waste\n");
    printf("7. Collection Locations\n");
    printf("8. Activity History\n");
    printf("9. Leaderboard\n");
    printf("10. Community\n");
    printf("11. Achievements\n");
    printf("12. Help\n");
    printf("0. Exit\n");
    printf("=================================\n");
    
    user user; char confirmPassword[100];
    
    do{
        printf("Choose an option (1-12): ");
        scanf("%d", &userChoice);

        switch (userChoice){
            case 1:
                printf("\n== Register Account ==\n");
                printf("Enter Username\t: ");
                scanf("%[^\n]", user.username);
                printf("Enter Email\t: ");
                scanf("%s", user.email);
                printf("Enter Password\t: ");
                scanf("%[^\n]", user.password);
                printf("Confirm Password\t: ");
                scanf("%[^\n]", confirmPassword);
                registerAccount(user.username, user.email, user.password, confirmPassword);
                break;
            case 2:
                loginAccount(user.email, user.password);
                break;
            case 3:
                displayGreeting(user.username);
                loadDashboard(&user);
                displayLeaderboardPreview();
                break;
            case 4:
                loadUserProfile(&user);
                break;
            case 5:
                loadRewardPage(&user);
                break;
            case 6: // on going for poin systems
                adminScanQRCodeForSampah("QR_DATA_SAMPLE", &user);
                break;
            case 7:
                loadCollectionLocations(&user);
                break;
            case 8:
                loadCollectionLocationsHistory();
                checkBadge(&user);
                break;
            case 9:
                LoadLeaderboard("BULAN INI");
                break;
            case 10:
                loadCommunity();
                break;
            case 11:
                calculateMonthlyProgress(8.5, 10.0);
                UpdateUserLevel(15.5);
                break;
            case 12:
                loadHelpMenu();
                loadFAQ();
                break;
            case 0:
                printf("Exiting the program. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
        if(userChoice != 0){
            printf("\nPress Enter to continue...");
            getchar();
        } 
    } while(userChoice != 0);

    return 0;
}