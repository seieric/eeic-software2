// CSVデータ読み込み・開放
#pragma once
typedef struct {
    char *name;     // Name
    double age;     // Age
    double gender;  // Gender (0: male, 1: female)
    double score;   // Admission Test Score
    double grade;   // High School Percentage
    char *city;     // City
    double status;  // Admission Status (0: rejected, 1: admitted)
} Sample;

Sample **load_data(const char *filename, int *data_size);
void free_data(int data_size, Sample **samples);
void shuffle_data(int data_size, Sample **samples);
void normalize_data(int data_size, Sample **samples);