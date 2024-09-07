#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void verify_ip(int octet1, int octet2, int octet3, int octet4, int masque);
char* to_binary(int octet);
int binary_to_decimal(const char* binary_str);
char* msr(int masque);
void print_msr(int masque);
int nb_hote(int masque);
void calculate_network_address(int octet1, int octet2, int octet3, int octet4, int masque);
void calculate_broadcast_address(int octet1, int octet2, int octet3, int octet4, int masque);
void gestion_ip();
