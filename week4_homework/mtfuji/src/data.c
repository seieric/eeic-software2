#include "data.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUF_SIZE 1000
#define LOC_SIZE 25

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

    Sample **samples = (Sample **)malloc(num_rows * sizeof(Sample *));

    *data_size = 0;
    while (fgets(buf, BUF_SIZE, fp) != NULL && *data_size < num_rows) {
        Sample *sample = (Sample *)malloc(sizeof(Sample));
        char *loc = (char *)malloc(LOC_SIZE * sizeof(char));

        if (sscanf(buf, "%[^,],%lf ,%lf \n", loc, &(sample->alt),
                   &(sample->temp)) != 3) {
            free(loc);
            free(sample);
            continue;
        }

        sample->loc = loc;
        samples[*data_size] = sample;
        ++*data_size;
    }

    fclose(fp);

    return samples;
}