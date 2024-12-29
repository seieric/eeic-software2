#pragma once
typedef struct {
    char *loc;    // location name
    double alt;   // altitude (km)
    double temp;  // temperature (centigrade)
} Sample;

int load_data(const char *filename, Sample **samples);