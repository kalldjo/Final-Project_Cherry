#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LENGTH 50
#define NPM_LENGTH 15
#define MAX_COURSES 8
#define COURSE_NAME_LENGTH 100

const char *courseList[MAX_COURSES] = {
    "Aljabar Linear",
    "MPKT",
    "Rangkaian Listrik",
    "Pengantar Desain Teknik",
    "Pemrograman Dasar",
    "Fisika Mekanika",
    "Profesionalisme dan Etika dalam Teknologi",
    "Kewirausahaan dalam TI"
};

const int courseSKS[MAX_COURSES] = {4, 6, 2, 2, 3, 3, 2, 2};

typedef struct {
    int index; 
    int kehadiran; 
    float uts, uas, quiz, tugas1, tugas2, tugas3;
    float finalScore;
    char grade[3];
    char status[15];
} Course;

typedef struct {
    char name[NAME_LENGTH];
    char npm[NPM_LENGTH];
    int age;
    int courseCount;
    Course courses[MAX_COURSES];
} Student;

Student students[MAX_STUDENTS];
int studentCount = 0;


void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("Database penuh. Tidak bisa menambah mahasiswa baru.\n");
        return;
    }

    Student newStudent;

    printf("Masukkan nama mahasiswa: ");
    getchar(); 
    fgets(newStudent.name, NAME_LENGTH, stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = '\0';

    printf("Masukkan NPM mahasiswa: ");
    fgets(newStudent.npm, NPM_LENGTH, stdin);
    newStudent.npm[strcspn(newStudent.npm, "\n")] = '\0';

    printf("Masukkan usia mahasiswa: ");
    scanf("%d", &newStudent.age);

    printf("Masukkan grade mahasiswa (A/B/C/D/F): ");
    getchar(); 
    scanf("%c", &newStudent.grade);

    printf("Masukkan jumlah mata kuliah (maks %d): ", MAX_COURSES);
    scanf("%d", &newStudent.courseCount);
    getchar(); 

    if (newStudent.courseCount > MAX_COURSES) {
        printf("Maksimal hanya bisa mengambil %d mata kuliah. Dibatasi ke %d.\n", MAX_COURSES, MAX_COURSES);
        newStudent.courseCount = MAX_COURSES;
    }

    for (int i = 0; i < newStudent.courseCount; i++) {
        printf("Masukkan nama mata kuliah ke-%d: ", i + 1);
        fgets(newStudent.courses[i], COURSE_NAME_LENGTH, stdin);
        newStudent.courses[i][strcspn(newStudent.courses[i], "\n")] = '\0';
    }

    students[studentCount] = newStudent;
    studentCount++;

    printf("Mahasiswa berhasil ditambahkan.\n\n");
}



void showAllStudents() {
    if (studentCount == 0) {
        printf("Belum ada data mahasiswa.\n\n");
        return;
    }

    printf("Daftar Mahasiswa:\n");
    for (int i = 0; i < studentCount; i++){
        printf("Nama: %s, NPM: %s, Usia: %d, Grade: %c\n", 
        students[i].name, students[i].npm, students[i].age, students[i].grade);
        printf("  Mata kuliah (%d):\n", students[i].courseCount);
        for (int j = 0; j < students[i].courseCount; j++) {
            printf("    - %s\n", students[i].courses[j]);
        }
    }
    printf("\n");
}



void findStudent() {
	char name[NAME_LENGTH];
    printf("Masukkan nama mahasiswa yang dicari: ");
    getchar(); 
    fgets(name, NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = '\0';  

    int found = 0;
    int i;
    for (i = 0; i < studentCount; i++) {
        if (strcmp(students[i].name, name) == 0) {
            printf("Nama: %s, Usia: %d, Grade: %c\n", students[i].name, students[i].age, students[i].grade);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Mahasiswa dengan nama %s tidak ditemukan.\n\n", name);
    } else {
        printf("\n");
    }
}



void deleteStudent() {
   char name[NAME_LENGTH];
    printf("Masukkan nama mahasiswa yang ingin dihapus: ");
    getchar(); 
    fgets(name, NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = '\0';

    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].name, name) == 0) {
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--;
            found = 1;
            printf("Mahasiswa %s berhasil dihapus.\n\n", name);
            break;
        }
    }

    if (!found) {
        printf("Mahasiswa dengan nama %s tidak ditemukan.\n\n", name);
    }
}


int main() {
    int choice;
    do {
        printf("===== Sistem Manajemen Mahasiswa =====\n");
        printf("1. Tambah Mahasiswa\n");
        printf("2. Lihat Semua Mahasiswa\n");
        printf("3. Cari Mahasiswa\n");
        printf("4. Hapus Mahasiswa\n");
        printf("5. Edit Mahasiswa\n");
        printf("6. Keluar\n");
        printf("Pilih opsi: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: showAllStudents(); break;
            case 3: findStudent(); break;
            case 4: deleteStudent(); break;
            case 5: editStudent(); break;
            case 6: printf("Keluar dari program.\n"); break;
            default: printf("Pilihan tidak valid.\n");
        }
    } while (choice != 6);
      
    return 0;
}
