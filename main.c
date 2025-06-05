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

float calculateFinalScore(Course c) {
    float kehadiranScore = ((float)c.kehadiran / 14.0f) * 100.0f * 0.10f;
    float tugasScore = ((c.tugas1 + c.tugas2 + c.tugas3) / 3.0f) * 0.20f;
    return kehadiranScore + c.quiz * 0.20f + c.uts * 0.30f + c.uas * 0.30f + tugasScore;
}

void assignGrade(Course *c) {
    float score = c->finalScore;
    if (score >= 85) strcpy(c->grade, "A");
    else if (score >= 80) strcpy(c->grade, "A-");
    else if (score >= 75) strcpy(c->grade, "B+");
    else if (score >= 70) strcpy(c->grade, "B");
    else if (score >= 65) strcpy(c->grade, "B-");
    else if (score >= 60) strcpy(c->grade, "C+");
    else if (score >= 55) strcpy(c->grade, "C");
    else if (score >= 40) strcpy(c->grade, "D");
    else strcpy(c->grade, "E");

    if (strcmp(c->grade, "D") == 0 || strcmp(c->grade, "E") == 0)
        strcpy(c->status, "Tidak LULUS");
    else
        strcpy(c->status, "LULUS");
}

float gradeToPoint(const char *grade) {
    if (strcmp(grade, "A") == 0) return 4.0;
    if (strcmp(grade, "A-") == 0) return 3.7;
    if (strcmp(grade, "B+") == 0) return 3.3;
    if (strcmp(grade, "B") == 0) return 3.0;
    if (strcmp(grade, "B-") == 0) return 2.7;
    if (strcmp(grade, "C+") == 0) return 2.3;
    if (strcmp(grade, "C") == 0) return 2.0;
    if (strcmp(grade, "D") == 0) return 1.0;
    return 0.0;

void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("Database penuh. Tidak bisa menambah mahasiswa baru.\n");
        return;
    }

    Student newStudent;
    int totalSKS = 0;

    printf("Masukkan nama mahasiswa: ");
    getchar();
    fgets(newStudent.name, NAME_LENGTH, stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = '\0';

    printf("Masukkan NPM mahasiswa: ");
    fgets(newStudent.npm, NPM_LENGTH, stdin);
    newStudent.npm[strcspn(newStudent.npm, "\n")] = '\0';

    printf("Masukkan usia mahasiswa: ");
    scanf("%d", &newStudent.age);

    printf("Pilih mata kuliah (minimal 20 SKS, maksimal 24 SKS):\n");
    for (int i = 0; i < MAX_COURSES; i++) {
        printf("%d. %s (%d SKS)\n", i + 1, courseList[i], courseSKS[i]);
    }

    newStudent.courseCount = 0;
    while (totalSKS < 20 || totalSKS > 24) {
        totalSKS = 0;
        newStudent.courseCount = 0;
        printf("Masukkan jumlah mata kuliah yang diambil: ");
        int jumlah;
        scanf("%d", &jumlah);
        getchar();

        for (int i = 0; i < jumlah; i++) {
            int pilih;
            printf("Pilih nomor mata kuliah ke-%d: ", i + 1);
            scanf("%d", &pilih);
            getchar();
            if (pilih < 1 || pilih > MAX_COURSES) {
                printf("Pilihan tidak valid.\n");
                i--;
                continue;
            }
            newStudent.courses[i].index = pilih - 1;
            totalSKS += courseSKS[pilih - 1];
            newStudent.courseCount++;
        }
        if (totalSKS < 20 || totalSKS > 24) {
            printf("Total SKS saat ini %d, harus antara 20 hingga 24. Ulangi input.\n", totalSKS);
        }
    }

    for (int i = 0; i < newStudent.courseCount; i++) {
        printf("\n--- %s ---\n", courseList[newStudent.courses[i].index]);
        printf("Masukkan jumlah kehadiran (maks 14): ");
        scanf("%d", &newStudent.courses[i].kehadiran);
        printf("Masukkan nilai Quiz: ");
        scanf("%f", &newStudent.courses[i].quiz);
        printf("Masukkan nilai UTS: ");
        scanf("%f", &newStudent.courses[i].uts);
        printf("Masukkan nilai UAS: ");
        scanf("%f", &newStudent.courses[i].uas);
        printf("Masukkan nilai Tugas 1: ");
        scanf("%f", &newStudent.courses[i].tugas1);
        printf("Masukkan nilai Tugas 2: ");
        scanf("%f", &newStudent.courses[i].tugas2);
        printf("Masukkan nilai Tugas 3: ");
        scanf("%f", &newStudent.courses[i].tugas3);

        newStudent.courses[i].finalScore = calculateFinalScore(newStudent.courses[i]);
        assignGrade(&newStudent.courses[i]);
    }

    students[studentCount++] = newStudent;
    printf("Mahasiswa berhasil ditambahkan.\n\n");
}

void showAllStudents() {
    if (studentCount == 0) {
        printf("Belum ada data mahasiswa.\n\n");
        return;
    }

    for (int i = 0; i < studentCount; i++) {
        printf("========================================================\n");
        printf("Nama: %s\nNPM: %s\nUsia: %d\n", students[i].name, students[i].npm, students[i].age);

        float totalNilai = 0.0;
        int totalSKS = 0;
        printf("%-3s %-40s %-4s %-6s %-10s %-8s\n", "No", "Mata Kuliah", "SKS", "Grade", "Status", "Final");
        for (int j = 0; j < students[i].courseCount; j++) {
            Course c = students[i].courses[j];
            int idx = c.index;
            printf("%-3d %-40s %-4d %-6s %-10s %-8.2f\n", j + 1, courseList[idx], courseSKS[idx], c.grade, c.status, c.finalScore);
            totalNilai += gradeToPoint(c.grade) * courseSKS[idx];
            totalSKS += courseSKS[idx];
        }
        float ipk = totalSKS > 0 ? totalNilai / totalSKS : 0.0;
        printf("IPK: %.2f\n", ipk);
        printf("========================================================\n\n");
    }
}

void findStudent() {
    char name[NAME_LENGTH];
    printf("Masukkan nama mahasiswa yang dicari: ");
    getchar();
    fgets(name, NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = '\0';

    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].name, name) == 0) {
            printf("Ditemukan:\n");
            printf("Nama: %s, NPM: %s, Usia: %d\n", students[i].name, students[i].npm, students[i].age);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Mahasiswa tidak ditemukan.\n\n");
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
            printf("Mahasiswa berhasil dihapus.\n\n");
            break;
        }
    }
    if (!found) {
        printf("Mahasiswa tidak ditemukan.\n\n");
    }
}

void editStudent() {
    char name[NAME_LENGTH];
    printf("Masukkan nama mahasiswa yang ingin diedit: ");
    getchar();
    fgets(name, NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = '\0';

    Student *studentToEdit = NULL; 
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].name, name) == 0) {
            studentToEdit = &students[i];
            break;
        }
    }

    if (studentToEdit == NULL) {
        printf("Mahasiswa tidak ditemukan.\n\n");
        return;
    }

    printf("Editing data untuk mahasiswa: %s\n", studentToEdit->name);

    printf("Masukkan nama baru (tekan enter untuk tidak mengubah): ");
    char newName[NAME_LENGTH];
    fgets(newName, NAME_LENGTH, stdin);
    newName[strcspn(newName, "\n")] = '\0';
    if (strlen(newName) > 0) {
        strcpy(studentToEdit->name, newName);
    }

    printf("Masukkan NPM baru (tekan enter untuk tidak mengubah): ");
    char newNpm[NPM_LENGTH];
    fgets(newNpm, NPM_LENGTH, stdin);
    newNpm[strcspn(newNpm, "\n")] = '\0';
    if (strlen(newNpm) > 0) {
        strcpy(studentToEdit->npm, newNpm);
    }


    printf("Masukkan usia baru (tekan enter untuk tidak mengubah): ");
    int newAge;
    int result = scanf("%d", &newAge);
    if (result == 1) {
        studentToEdit->age = newAge;
    }
    getchar(); 

    printf("Ingin mengedit nilai mata kuliah? (y/n): ");
    char editCoursesChoice;
    scanf("%c", &editCoursesChoice);
    getchar();
    if (editCoursesChoice == 'y' || editCoursesChoice == 'Y') {
        for (int i = 0; i < studentToEdit->courseCount; i++) {
            Course *c = &studentToEdit->courses[i]; 
            int idx = c->index;

            printf("\n--- %s ---\n", courseList[idx]);

            printf("Jumlah kehadiran saat ini: %d (maks 14)\n", c->kehadiran);
            printf("Masukkan kehadiran baru (tekan enter untuk tidak mengubah): ");
            char buff[10];
            fgets(buff, sizeof(buff), stdin);
            if (buff[0] != '\n') {
                int val = atoi(buff);
                if (val >= 0 && val <= 14) {
                    c->kehadiran = val;
                } else {
                    printf("Input kehadiran tidak valid, nilai tidak diubah.\n");
                }
            }

            printf("Nilai Quiz saat ini: %.2f\n", c->quiz);
            printf("Masukkan nilai Quiz baru (tekan enter untuk tidak mengubah): ");
            fgets(buff, sizeof(buff), stdin);
            if (buff[0] != '\n') {
                float val = atof(buff);
                if (val >= 0 && val <= 100) {
                    c->quiz = val;
                } else {
                    printf("Input nilai Quiz tidak valid, nilai tidak diubah.\n");
                }
            }

            printf("Nilai UTS saat ini: %.2f\n", c->uts);
            printf("Masukkan nilai UTS baru (tekan enter untuk tidak mengubah): ");
            fgets(buff, sizeof(buff), stdin);
            if (buff[0] != '\n') {
                float val = atof(buff);
                if (val >= 0 && val <= 100) {
                    c->uts = val;
                } else {
                    printf("Input nilai UTS tidak valid, nilai tidak diubah.\n");
                }
            }

            printf("Nilai UAS saat ini: %.2f\n", c->uas);
            printf("Masukkan nilai UAS baru (tekan enter untuk tidak mengubah): ");
            fgets(buff, sizeof(buff), stdin);
            if (buff[0] != '\n') {
                float val = atof(buff);
                if (val >= 0 && val <= 100) {
                    c->uas = val;
                } else {
                    printf("Input nilai UAS tidak valid, nilai tidak diubah.\n");
                }
            }

            printf("Nilai Tugas 1 saat ini: %.2f\n", c->tugas1);
            printf("Masukkan nilai Tugas 1 baru (tekan enter untuk tidak mengubah): ");
            fgets(buff, sizeof(buff), stdin);
            if (buff[0] != '\n') {
                float val = atof(buff);
                if (val >= 0 && val <= 100) {
                    c->tugas1 = val;
                } else {
                    printf("Input nilai Tugas 1 tidak valid, nilai tidak diubah.\n");
                }
            }

            printf("Nilai Tugas 2 saat ini: %.2f\n", c->tugas2);
            printf("Masukkan nilai Tugas 2 baru (tekan enter untuk tidak mengubah): ");
            fgets(buff, sizeof(buff), stdin);
            if (buff[0] != '\n') {
                float val = atof(buff);
                if (val >= 0 && val <= 100) {
                    c->tugas2 = val;
                } else {
                    printf("Input nilai Tugas 2 tidak valid, nilai tidak diubah.\n");
                }
            }

            printf("Nilai Tugas 3 saat ini: %.2f\n", c->tugas3);
            printf("Masukkan nilai Tugas 3 baru (tekan enter untuk tidak mengubah): ");
            fgets(buff, sizeof(buff), stdin);
            if (buff[0] != '\n') {
                float val = atof(buff);
                if (val >= 0 && val <= 100) {
                    c->tugas3 = val;
                } else {
                    printf("Input nilai Tugas 3 tidak valid, nilai tidak diubah.\n");
                }
            }
	
            c->finalScore = calculateFinalScore(*c);
            assignGrade(c);
        }
    }
    printf("Data mahasiswa berhasil diperbarui.\n\n");
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
