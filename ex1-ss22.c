#include <stdio.h>
typedef struct {
    int id;
    char name[100];
    int age;
} SinhVien;
SinhVien students[100];
int studentCount = 0;
void readFile() {
    FILE *file = fopen("students.dat", "rb");
    if (file != NULL) {
        studentCount = fread(students, sizeof(SinhVien), 100, file);
        fclose(file);
    } else {
        studentCount = 0;
    }
}
void writeFile() {
    FILE *file = fopen("students.dat", "wb");
    if (file != NULL) {
        fwrite(students, sizeof(SinhVien), studentCount, file);
        fclose(file);
    }
}
void printStudents() {
    printf("\nDanh sach sinh vien:\n");
    for (int i = 0; i < studentCount; i++) {
        printf("ID: %d, Name: %s, Age: %d\n", students[i].id, students[i].name, students[i].age);
    }
}
void addStudent() {
    if (studentCount >= 100) {
        printf("\nKhong the them sinh vien, danh sach day.\n");
        return;
    }
    SinhVien sv;
    printf("\nNhap ID: ");
    scanf("%d", &sv.id);
    getchar();
    printf("Nhap ten: ");
    fgets(sv.name, sizeof(sv.name), stdin);
    for (int i = 0; sv.name[i] != '\0'; i++) {
        if (sv.name[i] == '\n') {
            sv.name[i] = '\0';
            break;
        }
    }
    printf("Nhap tuoi: ");
    scanf("%d", &sv.age);
    students[studentCount++] = sv;
    writeFile();
    printf("\nThem sinh vien thanh cong.\n");
}
void editStudent() {
    int id;
    printf("\nNhap ID sinh vien can sua: ");
    scanf("%d", &id);
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            printf("Nhap ten moi: ");
            getchar();
            fgets(students[i].name, sizeof(students[i].name), stdin);
            for (int j = 0; students[i].name[j] != '\0'; j++) {
                if (students[i].name[j] == '\n') {
                    students[i].name[j] = '\0';
                    break;
                }
            }
            printf("Nhap tuoi moi: ");
            scanf("%d", &students[i].age);
            writeFile();
            printf("\nSua thong tin thanh cong.\n");
            return;
        }
    }
    printf("\nKhong tim thay sinh vien voi ID da nhap.\n");
}
void deleteStudent() {
    int id;
    printf("\nNhap ID sinh vien can xoa: ");
    scanf("%d", &id);
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--;
            writeFile();
            printf("\nXoa sinh vien thanh cong.\n");
            return;
        }
    }
    printf("\nKhong tim thay sinh vien voi ID da nhap.\n");
}

void searchStudent() {
    int id;
    printf("\nNhap ID sinh vien can tim: ");
    scanf("%d", &id);
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            printf("ID: %d, Name: %s, Age: %d\n", students[i].id, students[i].name, students[i].age);
            return;
        }
    }
    printf("\nKhong tim thay sinh vien voi ID da nhap.\n");
}
void sortStudents() {
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = i + 1; j < studentCount; j++) {
            if (students[i].id > students[j].id) {
                SinhVien temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    writeFile();
    printf("\nSap xep danh sach thanh cong.\n");
}
int main() {
    int choice;
    readFile();
    do {
        printf("\nMENU\n");
        printf("1. In danh sach sinh vien\n");
        printf("2. Them sinh vien\n");
        printf("3. Sua thong tin sinh vien\n");
        printf("4. Xoa sinh vien\n");
        printf("5. Tim kiem sinh vien\n");
        printf("6. Sap xep danh sach sinh vien\n");
        printf("7. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
			printStudents();
			 break;
            case 2: 
			addStudent();
			 break;
            case 3: 
			editStudent();
			 break;
            case 4: 
			deleteStudent();
			 break;
            case 5: 
			searchStudent();
			 break;
            case 6: 
			sortStudents();
			 break;
            case 7: 
			printf("\nThoat chuong trinh.\n");
			 break;
            default: 
			printf("\nLua chon khong hop le.\n");
        }
    } while (choice != 7);

    return 0;
}

