#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 250

void head();
void get_data();
char *compare_ip(int premier_byte, int deuxieme_byte, int troisieme_byte, int quatrieme_byte);
char *msr_par_defaut(int premier_byte, int deuxieme_byte, int troisieme_byte, int quatrieme_byte);
void gestion_reseau(int premier_byte, int deuxieme_byte, int troisieme_byte, int quatrieme_byte);
void calcul_adresses(int premier_byte, int deuxieme_byte, int troisieme_byte, int quatrieme_byte, const char *msr, char *reseau, char *broadcast);
