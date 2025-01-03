#include "data.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 1000
#define STR_SIZE 25

Sample **load_data(const char *filename, int *data_size) {
    FILE *fp;
    if ((fp = fopen(filename, "r")) == NULL) return 0;

    char buf[BUF_SIZE];

    int num_rows = 0;
    char c;
    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') ++num_rows;
    }

    fseek(fp, 0L, SEEK_SET);
    // 見出し列の分を減らす
    --num_rows;

    Sample **samples = (Sample **)malloc(num_rows * sizeof(Sample *));

    *data_size = 0;
    while (fgets(buf, BUF_SIZE, fp) != NULL && *data_size < num_rows) {
        Sample *sample = (Sample *)malloc(sizeof(Sample));
        char *name = (char *)malloc(STR_SIZE * sizeof(char));
        char *city = (char *)malloc(STR_SIZE * sizeof(char));
        char gender[STR_SIZE], status[STR_SIZE];

        bool is_error = false;

        if (sscanf(buf, "%[^,],%lf ,%[^,],%lf ,%lf ,%[^,],%[^\n]\n", name,
                   &(sample->age), gender, &(sample->score), &(sample->grade),
                   city, status) < 5) {
            printf("skipping: incomplete data\n");
            is_error = true;
        };

        sample->name = name;
        sample->city = city;

        // 性別
        if (strcmp(gender, "Male") == 0) {
            sample->gender = 0;
        } else if (strcmp(gender, "Female") == 0) {
            sample->gender = 1;
        } else {
            printf("skipping: invalid gender\n");
            is_error = true;
        }

        // 合否
        if (strcmp(status, "Rejected") == 0) {
            sample->status = 0;
        } else if (strcmp(status, "Accepted") == 0) {
            sample->status = 1;
        } else {
            printf("skipping: invalid admission status\n");
            is_error = true;
        }

        // 年齢
        if (sample->age < 0) {
            printf("skipping: invalid age\n");
            is_error = true;
        }

        if (is_error) {
            free(sample);
            free(name);
            free(city);
            continue;
        }

        samples[*data_size] = sample;
        ++*data_size;
    }

    fclose(fp);

    return samples;
}

void free_data(int data_size, Sample **samples) {
    for (int i = 0; i < data_size; ++i) {
        free(samples[i]->name);
        free(samples[i]->city);
        free(samples[i]);
    }
    free(samples);
}

void shuffle_data(int data_size, Sample **samples) {
    for (int i = 0; i < data_size; ++i) {
        int j = rand() % data_size;
        Sample *tmp = samples[i];
        samples[i] = samples[j];
        samples[j] = tmp;
    }
}