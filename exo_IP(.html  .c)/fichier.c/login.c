#include "../fichier.h/login.h"

int main() {
    char *query_string = getenv("QUERY_STRING");
    FILE *base_de_donne = fopen("donne.txt", "r");  
    int check = 0;

    afficher_entete_html();

    if (base_de_donne == NULL) {
        printf("<h1>Erreur: impossible d'ouvrir le fichier de données.</h1>");
    } else if (query_string == NULL) {
        printf("<h1>Erreur: QUERY_STRING non défini.</h1>");
    } else {
        check = verifier_login(query_string, base_de_donne);
    }

    afficher_message_login(check);

    if (base_de_donne != NULL) {
        fclose(base_de_donne);
    }

    return 0;
}

void afficher_entete_html() {
    printf("Content-type: text/html\n\n");
    printf("<html><head><style>"
           "body {background: url(../img/bg.png); background-size: cover; background-position: center; background-attachment: fixed; background-repeat:no-repeat; display: flex; align-items:center; justify-content: center; min-height: 100vh;padding: 0 20px;}"
           ".container { max-width: 600px; margin: 0 auto; padding: 20px; backdrop-filter: blur(30px); border-radius: 8px; box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); border: 3px solid rgba(255,255,255,0.3);}"
           "h1 { text-align: center; border-radius: 30px; background: rgba(0, 245, 245, 0.507); margin: 10px; padding: 10px 10px;}"
           ".form-title a{ text-decoration: none; font-size:30px; padding: 10px 20px; color: #fff; background: rgba(20, 175, 0, 0.699); border-radius: 20px; cursor: pointer;transition: .2s;}.form-title:hover{ opacity: 0.80;}"
           ".form-title { text-align: center; margin-top: 30px;}" 
           "</style></head><body>");
    printf("<div class='container'>");
}

void afficher_message_login(int check) {
    if (check == 0) {
        printf("<h1>Login invalide</h1>"); 
        printf("<div class='form-title'>"
               "<a href='login.html' class='inputs btn'>Ressayer</a></div>");  
    } else {
        printf("<h1>Login valide</h1>"); 
        printf("<div class='form-title'>"
               "<a href='adresse.html' class='inputs btn'>Continuer</a></div>");  
    }
    printf("</div></body></html>");
}

int verifier_login(char *query_string, FILE *base_de_donne) {
    char ligne[100];
    while (fgets(ligne, sizeof(ligne), base_de_donne)) {
        // Supprime le saut de ligne de la fin de la ligne, s'il y en a un
        ligne[strcspn(ligne, "\n")] = 0;
        if (strcmp(query_string, ligne) == 0) {
            return 1;
        }
    }
    return 0;
}
