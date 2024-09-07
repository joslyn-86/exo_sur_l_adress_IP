#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void connaitre_classe_ip(int octet1, char *classe);
int extraire_octets(char *adresse_ip, int *octet1, int *octet2, int *octet3, int *octet4);
int verifier_adresse_ip(int octet1, int octet2, int octet3, int octet4);
void decoder_adresse_ip(char *adresse_ip, char *decoded_ip);
void afficher_resultat(int valide, char *decoded_ip, char *classe);
