#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LENGTH 50
#define NPM_LENGTH 15
#define MAX_COURSES 3
#define COURSE_NAME_LENGTH 50

// Struktur data untuk menyimpan informasi mahasiswa
typedef struct {
    char name[NAME_LENGTH];
    char npm[NPM_LENGTH];
    int age;
    char grade;
    int courseCount;
    char courses[MAX_COURSES][COURSE_NAME_LENGTH];
} Student;

// Deklarasi array untuk menyimpan data mahasiswa
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
