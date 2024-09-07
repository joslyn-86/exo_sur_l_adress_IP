#include "../fichier.h/sign_up.h"

int main() {
    char *query_string = getenv("QUERY_STRING");

    afficher_entete_html();

    if (query_string != NULL) {
        enregistrer_donnees(query_string);
        afficher_message_inscription();
    } else {
        printf("<h1>Erreur: QUERY_STRING non défini.</h1>");
        printf("</div></body></html>");
    }

    return 0;
}

void afficher_entete_html() {
    printf("Content-type: text/html\n\n");
    printf("<html><head><style>"
           "body {background: url(../css/bg.png);  background-size: cover;    background-position: center;    background-attachment: fixed;    background-repeat:no-repeat;   display: flex;    align-items:center; justify-content: center; min-height: 100vh;padding: 0 20px;}"
           ".container { max-width: 600px; margin: 0 auto; padding: 20px;   backdrop-filter: blur(30px); border-radius: 8px; box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); border: 3px solid rgba(255,255,255,0.3);}"
           "h1 { text-align: center; border-radius: 30px; background: rgba(0, 245, 245, 0.507);  margin: 10px; padding: 10px 10px;}"
           ".form-title a{ text-decoration: none; font-size:30px;   padding: 10px 20px; color: #fff; background: rgba(20, 175, 0, 0.699); border-radius: 20px; cursor: pointer;transition: .2s;}.form-title:hover{ opacity: 0.80;}"
           ".form-title { text-align: center; margin-top: 30px;}" 
           "</style></head><body>");
    printf("<div class='container'>");
}

void enregistrer_donnees(char *query_string) {
    FILE *data = fopen("donne.txt", "a");
    if (data != NULL) {
        fprintf(data, "%s\n", query_string);
        fclose(data);
    } else {
        printf("<h1>Erreur: impossible d'ouvrir le fichier de données.</h1>");
    }
}

void afficher_message_inscription() {
    printf("<h1>Inscription valide</h1>"); 
    printf("<div class='form-title'>"
           "<a href='login.html'class='inputs btn'>s'identifier</a></div>");  
    printf("</div></body></html>");
}

