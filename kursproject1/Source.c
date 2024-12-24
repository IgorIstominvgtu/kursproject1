#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define RACERS 20

typedef struct {
    char name[20];
    int times[3];
    int total_time;
    int place;
} Racer;

void print_table(Racer racers[RACERS], int results) {
    if (results) {
        printf("\n�������������� �������:\n");
        printf("|   ������           | ����� ����� | ����� |\n");
    }
    else {
        printf("�������� ������� ������������:\n");
        printf("|   ������           | ����� 1 ����� | ����� 2 ����� | ����� 3 ����� |\n");
    }

    for (int n = 0; n < RACERS; n++) {
        if (results) {
            printf("|%18s |     %3d      |  %2d   |\n", racers[n].name, racers[n].total_time, racers[n].place);
        }
        else {
            printf("|%18s |      %3d      |     %3d      |     %3d      |\n", racers[n].name, racers[n].times[0], racers[n].times[1], racers[n].times[2]);
        }
    }
}

void calculate_results(Racer racers[RACERS]) {
    for (int i = 0; i < RACERS; i++) {
        racers[i].total_time = racers[i].times[0] + racers[i].times[1] + racers[i].times[2];
        racers[i].place = 1; // ��������� �����
    }

    // ���������� �������� �� ������ ������� (����������� �����)
    for (int i = 0; i < RACERS - 1; i++) {
        for (int j = i + 1; j < RACERS; j++) {
            if (racers[i].total_time > racers[j].total_time) {
                Racer temp = racers[i];
                racers[i] = racers[j];
                racers[j] = temp;
            }
        }
    }

    // ����������� �����
    for (int i = 1; i < RACERS; i++) {
        racers[i].place = (racers[i].total_time == racers[i - 1].total_time) ? racers[i - 1].place : i + 1;
    }
}

// ������� ������ ������ ��������
void find_best(Racer racers[RACERS]) {
    printf("\n������ ������:\n");
    for (int i = 0; i < RACERS; i++) {
        if (racers[i].place == 1) {
            printf("%s � ����� �������� %d\n", racers[i].name, racers[i].total_time);
        }
    }
}

// ������� ������ ������ ��������
void find_worst(Racer racers[RACERS]) {
    printf("\n������ ������:\n");
    for (int i = RACERS - 1; i >= 0; i--) {
        if (racers[i].place == RACERS) {
            printf("%s � ����� �������� %d\n", racers[i].name, racers[i].total_time);
        }
    }
}

// ������� ������ �������� � ����� �������� ������ n
void find_above_n(Racer racers[RACERS], int n) {
    printf("\n������� � ����� �������� ������ %d:\n", n);
    for (int i = 0; i < RACERS; i++) {
        if (racers[i].total_time > n) {
            printf("%s � ����� �������� %d\n", racers[i].name, racers[i].total_time);
        }
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    srand(time(NULL));

    Racer racers[RACERS] = {
        {"������"}, {"�������"}, {"��������"}, {"������"}, {"��������"},
        {"�������"}, {"������"}, {"���������"}, {"���������"}, {"�����"},
        {"�����"}, {"�������"}, {"��������"}, {"������"}, {"�������"},
        {"����"}, {"��������"}, {"������"}, {"���������"}, {"����������"}
    };

    for (int i = 0; i < RACERS; i++) {
        racers[i].times[0] = rand() % 20 + 10;
        racers[i].times[1] = rand() % 20 + 10;
        racers[i].times[2] = rand() % 20 + 10;
    }

    print_table(racers, 0);
    calculate_results(racers);
    print_table(racers, 1);

    // ����� ������ ��������
    find_best(racers);

    // ����� ������ ��������
    find_worst(racers);

    // ����� �������� � ����� �������� ������ 60
    find_above_n(racers, 60);
}