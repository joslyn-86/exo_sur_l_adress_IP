#include "../fichier.h/adresse.h"

int main() {
    char *query_string = getenv("QUERY_STRING");
    char adresse_ip[16];
    char decoded_ip[16];
    int octet1, octet2, octet3, octet4;
    char classe[2];

    if (query_string == NULL) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body><h1>Erreur</h1><p>Pas de données reçues.</p></body></html>");
        return 1;
    }

    sscanf(query_string, "adresse-ip=%15s", adresse_ip);
    decoder_adresse_ip(adresse_ip, decoded_ip);

    int resultat = extraire_octets(decoded_ip, &octet1, &octet2, &octet3, &octet4);
    int valide = (resultat == 4) && verifier_adresse_ip(octet1, octet2, octet3, octet4);

    if (valide) {
        connaitre_classe_ip(octet1, classe);
    }

    afficher_resultat(valide, decoded_ip, classe);
    return 0;
}

void decoder_adresse_ip(char *adresse_ip, char *decoded_ip) {
    int j = 0;
    for (int i = 0; adresse_ip[i] != '\0'; i++) {
        if (adresse_ip[i] == '%') {
            int value;
            sscanf(&adresse_ip[i + 1], "%2x", &value);
            decoded_ip[j++] = (char)value;
            i += 2;
        } else {
            decoded_ip[j++] = adresse_ip[i];
        }
    }
    decoded_ip[j] = '\0';
}

void afficher_resultat(int valide, char *decoded_ip, char *classe) {
    printf("Content-Type: text/html\n\n");
    printf("<html><head><style>"
           "body {background: url(../css/bg.png);  background-size: cover;    background-position: center;    background-attachment: fixed;    background-repeat:no-repeat;   display: flex;    align-items:center; justify-content: center; min-height: 100vh;padding: 0 20px;}"
            ".container { max-width: 600px; margin: 0 auto; padding: 20px;   backdrop-filter: blur(30px); border-radius: 8px; box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); border: 3px solid rgba(255,255,255,0.3);}"
            "h1 { text-align: center; border-radius: 30px; background: rgba(0, 245, 245, 0.507);  margin: 10px; padding: 10px 10px;}"
           "p { font-size: 30px; border-radius: 30px; background-color: rgba(29, 26, 26, 0.726); margin-top: 50px; padding: 20px 20px}"
           ".error { color: red; }"
           ".success { color: green; }"
           "</style></head><body>");
    printf("<div class='container'>");
    if (valide) {
        printf("<h1>Classe de l'adresse IP</h1>");
        printf("<p class='success'>adresse IP %s classe %s</p>", decoded_ip, classe);
    } else {
        printf("<h1>Erreur</h1>");
        printf("<p class='error'>adresse IP incorrecte</p>");
    }
    printf("</div></body></html>");
}

void connaitre_classe_ip(int octet1, char *classe) {
    if (octet1 <= 127) {
        classe[0] = 'A';
    } else if (octet1 <= 191) {
        classe[0] = 'B';
    } else if (octet1 <= 223) {
        classe[0] = 'C';
    } else if (octet1 <= 239) {
        classe[0] = 'D';
    } else {
        classe[0] = 'E';
    }
    classe[1] = '\0';
}

int extraire_octets(char *adresse_ip, int *octet1, int *octet2, int *octet3, int *octet4) {
    return sscanf(adresse_ip, "%d.%d.%d.%d", octet1, octet2, octet3, octet4);
}

int verifier_adresse_ip(int octet1, int octet2, int octet3, int octet4) {
    return (octet1 >= 0 && octet1 <= 255 &&
            octet2 >= 0 && octet2 <= 255 &&
            octet3 >= 0 && octet3 <= 255 &&
            octet4 >= 0 && octet4 <= 255);
}
