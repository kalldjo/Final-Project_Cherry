#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LENGTH 50
#define NPM_LENGTH 15
#define MAX_COURSES 3
#define COURSE_NAME_LENGTH 50

// struct untuk menyimpan informasi mahasiswa
typedef struct {
    char name[NAME_LENGTH];
    char npm[NPM_LENGTH];
    int age;
    char grade;
    int courseCount;
    char courses[MAX_COURSES][COURSE_NAME_LENGTH];
} Student;

// deklarasi array untuk menyimpan data mahasiswa
Student students[MAX_STUDENTS];
int studentCount = 0;


void addStudent() {
  	// Fungsi untuk menambah mahasiswa baru 
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
	// Fungsi untuk mencari mahasiswa berdasarkan nama
}


void deleteStudent() {
   // Fungsi untuk menghapus mahasiswa berdasarkan nama
}


int main() {
    int choice;
    int running = 1;

    while (running) {
        printf("===== Sistem Manajemen Mahasiswa =====\n");
        printf("1. Tambah Mahasiswa\n");
        printf("2. Lihat Semua Mahasiswa\n");
        printf("3. Cari Mahasiswa\n");
        printf("4. Hapus Mahasiswa\n");
        printf("5. Keluar\n");
        printf("Pilih opsi: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                showAllStudents();
                break;
            case 3:
                findStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                printf("Keluar dari program.\n");
                running = 0;
                break;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n\n");
        }
    }

    return 0;
}
