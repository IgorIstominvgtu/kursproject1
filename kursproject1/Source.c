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
        printf("\nРезультирующая таблица:\n");
        printf("|   Гонщик           | Общее время | Место |\n");
    }
    else {
        printf("Исходная таблица соревнований:\n");
        printf("|   Гонщик           | время 1 круга | время 2 круга | время 3 круга |\n");
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
        racers[i].place = 1; // Начальное место
    }

    // Сортировка гонщиков по общему времени (пузырьковый метод)
    for (int i = 0; i < RACERS - 1; i++) {
        for (int j = i + 1; j < RACERS; j++) {
            if (racers[i].total_time > racers[j].total_time) {
                Racer temp = racers[i];
                racers[i] = racers[j];
                racers[j] = temp;
            }
        }
    }

    // Присваиваем места
    for (int i = 1; i < RACERS; i++) {
        racers[i].place = (racers[i].total_time == racers[i - 1].total_time) ? racers[i - 1].place : i + 1;
    }
}

// Функция поиска лучших гонщиков
void find_best(Racer racers[RACERS]) {
    printf("\nЛучший гонщик:\n");
    for (int i = 0; i < RACERS; i++) {
        if (racers[i].place == 1) {
            printf("%s с общим временем %d\n", racers[i].name, racers[i].total_time);
        }
    }
}

// Функция поиска худших гонщиков
void find_worst(Racer racers[RACERS]) {
    printf("\nХудший гонщик:\n");
    for (int i = RACERS - 1; i >= 0; i--) {
        if (racers[i].place == RACERS) {
            printf("%s с общим временем %d\n", racers[i].name, racers[i].total_time);
        }
    }
}

// Функция поиска гонщиков с общим временем больше n
void find_above_n(Racer racers[RACERS], int n) {
    printf("\nГонщики с общим временем больше %d:\n", n);
    for (int i = 0; i < RACERS; i++) {
        if (racers[i].total_time > n) {
            printf("%s с общим временем %d\n", racers[i].name, racers[i].total_time);
        }
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    srand(time(NULL));

    Racer racers[RACERS] = {
        {"Састре"}, {"Авермат"}, {"Грайпель"}, {"Мартин"}, {"Родригес"},
        {"Петакки"}, {"Фрейре"}, {"Кинтанана"}, {"Винокуров"}, {"Эванс"},
        {"Саган"}, {"Беттини"}, {"Кевендиш"}, {"Боннен"}, {"Жильбер"},
        {"Фрум"}, {"Контадор"}, {"Нибали"}, {"Вальверде"}, {"Канчеллара"}
    };

    for (int i = 0; i < RACERS; i++) {
        racers[i].times[0] = rand() % 20 + 10;
        racers[i].times[1] = rand() % 20 + 10;
        racers[i].times[2] = rand() % 20 + 10;
    }

    print_table(racers, 0);
    calculate_results(racers);
    print_table(racers, 1);

    // Поиск лучших гонщиков
    find_best(racers);

    // Поиск худших гонщиков
    find_worst(racers);

    // Поиск гонщиков с общим временем больше 60
    find_above_n(racers, 60);
}