#include "../fichier.h/ip_cidr.h"

int main() 
{
    gestion_ip();
    return 0;
}

char* to_binary(int octet) 
{
    int i;
    char* binary_str = (char*)malloc(9);
    binary_str[8] = '\0';

    for (i = 7; i >= 0; i--) 
    {
        binary_str[i] = (octet % 2) ? '1' : '0';
        octet /= 2;
    }

    return binary_str;
}

int binary_to_decimal(const char* binary_str) 
{
    int decimal = 0;
    int length = strlen(binary_str);
    int i;

    for (i = 0; i < length; i++) 
    {
        if (binary_str[i] == '1') 
        {
            decimal += pow(2, length - i - 1);
        }
    }

    return decimal;
}

void verify_ip(int octet1, int octet2, int octet3, int octet4, int masque) 
{
    if (octet1 < 0 || octet1 > 255 || octet2 < 0 || octet2 > 255 ||
        octet3 < 0 || octet3 > 255 || octet4 < 0 || octet4 > 255 ||
        masque < 0 || masque > 32) 
    {
        printf("\n\tAdresse IP invalide !");
        exit(1);
    }
}

char* msr(int masque) 
{
    char *result = (char *)malloc(40 * sizeof(char)); 
    char temp[33];
    int i;
    for (i = 0; i < 32; i++) 
    {
        temp[i] = (i < masque) ? '1' : '0'; 
    }
    temp[32] = '\0';

    snprintf(result, 40, "%.*s.%.*s.%.*s.%.*s",
            8, temp, 8, temp + 8, 8, temp + 16,
            8, temp + 24);

    return result;
}


void print_msr(int masque)
{
    char *resultat = msr(masque);
    char octet1_msr[9], octet2_msr[9], octet3_msr[9], octet4_msr[9];

    sscanf(resultat, "%8[^.].%8[^.].%8[^.].%8s", octet1_msr, octet2_msr, octet3_msr, octet4_msr);
    printf("%d.%d.%d.%d\n",
            binary_to_decimal(octet1_msr),
            binary_to_decimal(octet2_msr),
            binary_to_decimal(octet3_msr),
            binary_to_decimal(octet4_msr));
    free(resultat);
}

int nb_hote(int masque) 
{
    if (masque < 0 || masque > 32) 
    {
        fprintf(stderr, "Masque de sous-réseau invalide.\n");
        exit(1);
    }
    int bits_hotes = 32 - masque;
    int nb_total = (int)pow(2, bits_hotes) - 2;

    return nb_total;
}

void calculate_network_address(int octet1, int octet2, int octet3, int octet4, int masque) 
{
    int mask[4];
    int ip[4] = {octet1, octet2, octet3, octet4};
    int mask_bits = masque;
    int i;

    for (i = 0; i < 4; i++) 
    {
        if (mask_bits >= 8) 
        {
            mask[i] = 255;
            mask_bits -= 8;
        } 
        else 
        {
            mask[i] = (255 << (8 - mask_bits)) & 255;
            mask_bits = 0;
        }
    }

    printf("Adresse réseau : %d.%d.%d.%d\n",
           ip[0] & mask[0],
           ip[1] & mask[1],
           ip[2] & mask[2],
           ip[3] & mask[3]);
}

void calculate_broadcast_address(int octet1, int octet2, int octet3, int octet4, int masque) 
{
    int mask[4];
    int ip[4] = {octet1, octet2, octet3, octet4};
    int mask_bits = masque;
    int i;

    for (i = 0; i < 4; i++) 
    {
        if (mask_bits >= 8) 
        {
            mask[i] = 255;
            mask_bits -= 8;
        } 
        else 
        {
            mask[i] = (255 << (8 - mask_bits)) & 255;
            mask_bits = 0;
        }
    }

    int inverse_mask[4];
    for (i = 0; i < 4; i++) 
    {
        inverse_mask[i] = ~mask[i] & 255;
    }

    printf("Adresse de diffusion : %d.%d.%d.%d\n",
           ip[0] | inverse_mask[0],
           ip[1] | inverse_mask[1],
           ip[2] | inverse_mask[2],
           ip[3] | inverse_mask[3]);
}

void gestion_ip() 
{
    int octet1, octet2, octet3, octet4, masque;
    int nb_pc;
    char temp[32];

    printf("Entrez l'adresse IP : (ex : X.X.X.X / X)\n\t");
    if (scanf("%31s", temp) != 1) 
    {
        printf("Erreur de lecture de l'adresse IP\n");
        exit(1);
    }

    if (sscanf(temp, "%d.%d.%d.%d/%d", &octet1, &octet2, &octet3, &octet4, &masque) != 5) 
    {
        printf("Erreur de format de l'adresse IP/CIDR\n");
        exit(1);
    }

    verify_ip(octet1, octet2, octet3, octet4, masque);

    printf("Masque de Sous-Réseau : ");
    print_msr(masque);

    calculate_network_address(octet1, octet2, octet3, octet4, masque);
    calculate_broadcast_address(octet1, octet2, octet3, octet4, masque);

    nb_pc = nb_hote(masque);
    printf("Nombre de PC : %d\n", nb_pc);
}
