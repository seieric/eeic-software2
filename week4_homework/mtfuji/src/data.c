#include "data.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUF_SIZE 1000

int load_data(const char *filename, Sample **samples) {
    FILE *fp;
    if ((fp = fopen(filename, "r")) == NULL) return 0;

    char buf[BUF_SIZE];

    int data_size = 0;
    char c;
    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') ++data_size;
    }
    fseek(fp, 0L, SEEK_SET);

    samples = (Sample **)malloc(data_size * sizeof(Sample *));

    int data_id = 0;
    while (fgets(buf, BUF_SIZE, fp) != NULL && data_id < data_size) {
        Sample *sample = (Sample *)malloc(sizeof(Sample));
        char *loc = (char *)malloc(100 * sizeof(char));

        if (sscanf(buf, "%[^,],%lf ,%lf \n", loc, &(sample->alt),
                   &(sample->temp)) != 3) {
            free(loc);
            free(sample);
            continue;
        }

        sample->loc = loc;
        samples[data_id] = sample;
        ++data_id;
    }

    fclose(fp);

    return data_id;
}