#include <stdio.h>

typedef struct student {
  int id;
  char name[100];
  int age;
  double height;
  double weight;
} Student;

typedef struct tagged_student1 {
  int id;
  char name[100];
  int age;
  double height;
  double weight;
  char tag;
} TStudent1;

typedef struct tagged_student2 {
  char tag;
  int id;
  char name[100];
  int age;
  double height;
  double weight;
} TStudent2;

int main(int argc, char** argv) {
  Student s_begin;
  Student s1;
  TStudent1 s2;
  TStudent2 s3;
  TStudent2 s_end;

  /* 以下に各構造体の先頭アドレスを表示するプログラムを書く */
  /* Hint: printf で %p フォーマットを指定する*/
  /* 逆順に表示（s_end, s3, s2, s1, s_begin の順）*/

  printf("%p %p %p %p %p\n", &s_end, &s3, &s2, &s1, &s_begin);

  /* 以下には各構造体のサイズをsizeof演算子で計算し、表示する */
  /* printf 表示には%zu を用いる*/

  printf("%zu %zu %zu %zu %zu\n", sizeof(s_end), sizeof(s3), sizeof(s2),
         sizeof(s1), sizeof(s_begin));

  printf("[s_end]\n");
  printf(
      "tag(char): %p, id(int): %p, name(char *): %p, age(int): %p, "
      "height(double): %p, weight(double): %p\n",
      &s_end.tag, &s_end.id, &s_end.name, &s_end.age, &s_end.height,
      &s_end.weight);

  printf("[s3]\n");
  printf(
      "tag(char): %p, id(int): %p, name(char *): %p, age(int): %p, "
      "height(double): %p, weight(double): %p\n",
      &s3.tag, &s3.id, &s3.name, &s3.age, &s3.height, &s3.weight);

  printf("[s2]\n");
  printf(
      "tag(char): %p, id(int): %p, name(char *): %p, age(int): %p, "
      "height(double): %p, weight(double): %p\n",
      &s2.tag, &s2.id, &s2.name, &s2.age, &s2.height, &s2.weight);

  printf("[s1]\n");
  printf(
      "id(int): %p, name(char *): %p, age(int): %p, height(double): %p, "
      "weight(double): %p\n",
      &s1.id, &s1.name, &s1.age, &s1.height, &s1.weight);

  printf("[s_begin]\n");
  printf(
      "id(int): %p, name(char *): %p, age(int): %p, "
      "height(double): %p, weight(double): %p\n",
      &s_begin.id, &s_begin.name, &s_begin.age, &s_begin.height,
      &s_begin.weight);

  return 0;
}
