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
  	// Fungsi untuk menambah mahasiswa baru 
}


void showAllStudents() {
	// Fungsi untuk menampilkan semua data mahasiswa
}


void findStudent() {
	// Fungsi untuk mencari mahasiswa berdasarkan nama
}


void deleteStudent() {
   // Fungsi untuk menghapus mahasiswa berdasarkan nama
}

// Fungsi utama
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
