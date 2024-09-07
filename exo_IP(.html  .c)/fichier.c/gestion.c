#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../fichier.h/gestion.h"

int main() 
{
    head();
    get_data();
    return 0;
}

void head() 
{
    printf("Content-Type: text/html\n\n");
    printf("<html><head><meta charset=\"UTF-8\" /><title>IP</title></head><body>");
}

char *compare_ip(int premier_byte, int deuxieme_byte, int troisieme_byte, int quatrieme_byte) 
{
    static char classe[20];
    if (premier_byte < 0 || premier_byte > 255 || 
        deuxieme_byte < 0 || deuxieme_byte > 255 || 
        troisieme_byte < 0 || troisieme_byte > 255 || 
        quatrieme_byte < 0 || quatrieme_byte > 255) 
    {
        strcpy(classe, "IP Invalide");
    } 
    else if (premier_byte >= 0 && premier_byte <= 127) 
    {
        strcpy(classe, "class A");
    } 
    else if (premier_byte >= 128 && premier_byte <= 191) 
    {
        strcpy(classe, "class B");
    } 
    else if (premier_byte >= 192 && premier_byte <= 223) 
    {
        strcpy(classe, "class C");
    } 
    else if (premier_byte >= 224 && premier_byte <= 239) 
    {
        strcpy(classe, "class D");
    } 
    else if (premier_byte >= 240 && premier_byte <= 255) 
    {
        strcpy(classe, "class E");
    } 
    else 
    {
        strcpy(classe, "IP Invalide");
    }
    return classe;
}

char *msr_par_defaut(int premier_byte, int deuxieme_byte, int troisieme_byte, int quatrieme_byte) 
{
    static char msr[20];
    char *classe = compare_ip(premier_byte, deuxieme_byte, troisieme_byte, quatrieme_byte);
    if (strcmp(classe, "class A") == 0) 
    {
        strcpy(msr, "255.0.0.0");
    } 
    else if (strcmp(classe, "class B") == 0) 
    {
        strcpy(msr, "255.255.0.0");
    } 
    else if (strcmp(classe, "class C") == 0) 
    {
        strcpy(msr, "255.255.255.0");
    } 
    else 
    {
        strcpy(msr, "Inconnu");
    }
    return msr;
}

void gestion_reseau(int premier_byte, int deuxieme_byte, int troisieme_byte, int quatrieme_byte) 
{
    char add_res[MAX_CHAR];
    char *classe = compare_ip(premier_byte, deuxieme_byte, troisieme_byte, quatrieme_byte);

    if (strcmp(classe, "class A") == 0) 
    {
        strcpy(add_res, "Réseau A");
    } 
    else if (strcmp(classe, "class B") == 0) 
    {
        strcpy(add_res, "Réseau B");
    } 
    else if (strcmp(classe, "class C") == 0) 
    {
        strcpy(add_res, "Réseau C");
    } 
    else 
    {
        strcpy(add_res, "Classe non prise en charge");
        printf("<p>%s</p>", add_res);
    }
}

void calcul_adresses(int premier_byte, int deuxieme_byte, int troisieme_byte, int quatrieme_byte, const char *msr, char *reseau, char *broadcast) 
{
    int msr_parts[4];
    int ip_parts[4] = {premier_byte, deuxieme_byte, troisieme_byte, quatrieme_byte};
    int reseau_parts[4], broadcast_parts[4];

    // Convertir le masque de sous-réseau en entiers
    sscanf(msr, "%d.%d.%d.%d", &msr_parts[0], &msr_parts[1], &msr_parts[2], &msr_parts[3]);

    // Calculer l'adresse réseau
    for (int i = 0; i < 4; i++) 
    {
        reseau_parts[i] = ip_parts[i] & msr_parts[i];
    }

    // Calculer l'adresse de diffusion
    for (int i = 0; i < 4; i++) 
    {
        broadcast_parts[i] = ip_parts[i] | (~msr_parts[i] & 255);
    }

    // Formater les adresses en chaînes de caractères
    sprintf(reseau, "%d.%d.%d.%d", reseau_parts[0], reseau_parts[1], reseau_parts[2], reseau_parts[3]);
    sprintf(broadcast, "%d.%d.%d.%d", broadcast_parts[0], broadcast_parts[1], broadcast_parts[2], broadcast_parts[3]);
}

void get_data() {
    char *data = getenv("QUERY_STRING");
    if (data == NULL) 
    {
        printf("<p>Erreur lors de l'analyse des données.</p>");
        printf("<button><a href=\"index.html\">Réessayer</a></button>");
        printf("</body></html>");
        exit(1);
    }

    char msr[MAX_CHAR];
    char *classe;
    int premier_byte, deuxieme_byte, troisieme_byte, quatrieme_byte;
    char reseau[MAX_CHAR];
    char broadcast[MAX_CHAR];

    // Analyse des données de la requête GET
    int ip_string = sscanf(data, "IP=%d.%d.%d.%d&MSR=%s", &premier_byte, &deuxieme_byte, &troisieme_byte, &quatrieme_byte, msr);

    if (ip_string == 5) 
    {
        char *msr_default = msr_par_defaut(premier_byte, deuxieme_byte, troisieme_byte, quatrieme_byte);
        if (strcmp(msr, msr_default) != 0) 
        {
            printf("<p>Masque de sous-réseau inconnu</p>");
            printf("<button><a href=\"index.html\">Réessayer</a></button>");
            printf("</body></html>");
            exit(1);
        } 
        else 
        {
            classe = compare_ip(premier_byte, deuxieme_byte, troisieme_byte, quatrieme_byte);
            calcul_adresses(premier_byte, deuxieme_byte, troisieme_byte, quatrieme_byte, msr, reseau, broadcast);

            // Affichage dans un tableau HTML
            printf("<table border=\"1\">");
            printf("<tr><td><strong>IP</strong></td><td><strong>MSR</strong></td></tr>");
            printf("<tr><td>%d.%d.%d.%d</td><td>%s</td></tr>", premier_byte, deuxieme_byte, troisieme_byte, quatrieme_byte, msr);
            printf("</table>");

            printf("<table border=\"1\">");
            printf("<tr><td><strong>Type</strong></td><td><strong>Adresse</strong></td></tr>");
            printf("<tr><td>Adresse Réseau</td><td>%s</td></tr>", reseau);
            printf("<tr><td>Adresse de Diffusion</td><td>%s</td></tr>", broadcast);
            printf("</table>");
            
            printf("<p><strong>Classe:</strong> %s</p>", classe);
            
            gestion_reseau(premier_byte, deuxieme_byte, troisieme_byte, quatrieme_byte);
        }
    } 
    else 
    {
        printf("<p>Adresse IP invalide</p>");
        printf("<button><a href=\"index.html\">Réessayer</a></button>");
    }

    printf("</body></html>");
}
