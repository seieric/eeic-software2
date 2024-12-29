#pragma once
typedef struct {
    char *loc;    // location name
    double alt;   // altitude (km)
    double temp;  // temperature (centigrade)
} Sample;

Sample **load_data(const char *filename, int *data_size);