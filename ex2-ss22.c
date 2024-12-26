#include <stdio.h>
#include <string.h>
typedef struct {
    char username[50];
    char password[50];
} Account;
Account accounts[100];
int accountCount = 0;
void readFile() {
    FILE *file = fopen("accounts.dat", "rb");
    if (file != NULL) {
        accountCount = fread(accounts, sizeof(Account), 100, file);
        fclose(file);
    } else {
        accountCount = 0;
    }
}
void writeFile() {
    FILE *file = fopen("accounts.dat", "wb");
    if (file != NULL) {
        fwrite(accounts, sizeof(Account), accountCount, file);
        fclose(file);
    }
}
int findAccount(const char *username) {
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].username, username) == 0) {
            return i;
        }
    }
    return -1;
}
void registerAccount() {
    if (accountCount >= 100) {
        printf("\nDanh sach tai khoan da day, khong the dang ky them.\n");
        return;
    }
    Account acc;
    char confirmPassword[50];
    printf("\nNhap tai khoan: ");
    scanf("%s", acc.username);
    if (findAccount(acc.username) != -1) {
        printf("\nTai khoan da ton tai. Vui long thu lai.\n");
        return;
    }
    printf("Nhap mat khau: ");
    scanf("%s", acc.password);
    printf("Xac nhan mat khau: ");
    scanf("%s", confirmPassword);
    if (strcmp(acc.password, confirmPassword) != 0) {
        printf("\nMat khau xac nhan khong khop. Vui long thu lai.\n");
        return;
    }
    accounts[accountCount++] = acc;
    writeFile();
    printf("\nDang ky tai khoan thanh cong.\n");
}
void login() {
    char username[50], password[50];
    printf("\nNhap tai khoan: ");
    scanf("%s", username);
    printf("Nhap mat khau: ");
    scanf("%s", password);
    int index = findAccount(username);
    if (index != -1 && strcmp(accounts[index].password, password) == 0) {
        printf("\nDang nhap thanh cong. Xin chao %s!\n", username);
    } else {
        printf("\nDang nhap that bai. Tai khoan hoac mat khau khong dung.\n");
    }
}
int main() {
    int choice;
    readFile();
    do {
        printf("\nMENU\n");
        printf("1. Dang nhap\n");
        printf("2. Dang ky\n");
        printf("3. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: login(); break;
            case 2: registerAccount(); break;
            case 3: printf("\nThoat chuong trinh.\n"); break;
            default: printf("\nLua chon khong hop le. Vui long thu lai.\n");
        }
    } while (choice != 3);
    return 0;
}

