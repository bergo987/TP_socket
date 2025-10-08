#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <strings.h>

#define MAX_REQUEST 10
#define BUFF_SIZE 256

char* calculatrice (char cal[]){
    int nb = 0 ;
    char s_a[BUFF_SIZE];
    char s_b[BUFF_SIZE];
    float a; 
    float b;
    char op = '0';
    int m = 0 ; // longueur de a
    int j = -1 ; // indice de l'op
    int k = 0 ; // longueur de b
    int etat = 0 ; 
    float res = 0; 
    char* ret = malloc(BUFF_SIZE*sizeof(char)); 
    for(int i = 0 ; i < BUFF_SIZE&& cal[i]!='\0'; i ++ ){
        if ((cal[i]== '+'|| cal[i]== '-' || cal[i]== '*'||cal[i]== '/')&& op =='0'){
            op = cal[i]; 
            j = i ; 
        }
        else {
            if (j == -1 ){
                m +=1 ; 
                s_a[i] = cal[i];
            }
            else if (op!='0');{
                s_b[i-j-1] = cal[i];
                k += 1;
            }
        }
    }
    if((m != 0 && k != 0)&& (op != '0')){
        nb=3;
    }
    a = atof(s_a); 
    b = atof(s_b);
    if (nb == 3){
        printf("op = %c\t j = %d\n",op,j);
        printf("a = %f \t b = %f\n m = %d \t k = %d\n",a,b,m,k);

        if (op == '*'){
            res = a*b ;
            etat = 1;
            printf("res* = %f\n",res);  
        }
        if (op == '+'){
            res = a+b;
            etat = 1;
            printf("res+ = %f \n ",res);  
        }
        if (op == '-'){
            res = a - b;
            etat = 1; 
            printf("res- = %f \n ",res);  
        }
        if (op == '/'){
            res = a/b;
            etat = 1;
            printf("res/ = %f \n",res);
        }
        if (etat == 0 ){
            printf("on ne connait pas l'op\n");
            sprintf("on ne connait pas l'op\n", ret); 
        }
        else{
            sprintf("%.02f",ret,res); 

            printf("ret = %s \t strlen = %d \n ", ret,strlen(ret));
        }
    }
    
    else {
    printf("Erreur dans la requette\n"); 
    ret = "Erreur dans la requette";
    }
    return ret ;
}


int main(int argc,char *argv[])
{
    int sd;
    int port; 
    struct sockaddr_in sa; /* Numero de port du serveur */

    /* Structure Internet sockaddr_in */
    int newsd; /* Id de la socket entrante */
    struct sockaddr_in newsa; /* sockaddr_in de la connection entrante */
    int newsalength;
    int i;
    char buff[BUFF_SIZE];
    int n ; 
    char* res_calc = (char*)malloc(BUFF_SIZE*sizeof(char));
    /* verification du nombre d'arguments de la ligne de commande */
    if (argc != 2) {
        printf("pingserveurTCP. Erreur d'arguments\n");
        printf("Syntaxe : %% pingserveurTCP numero_port\n");
        exit(1);
    }
    /* Recuperation numero port passe en argument */
    port = atoi(argv[1]);

    /* Initialisation la structure sockaddr sa */
    /* Famille d'adresse : AF_INET = PF_INET */
    sa.sin_family = AF_INET;

    /* Initialisation du numero du port */
    sa.sin_port = htons(port);
    sa.sin_addr.s_addr = INADDR_ANY;

    /* Creation de la socket TCP */
    if((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Probleme lors de la creation de socket\n");
        exit(1);
    }
    /* Bind sur la socket */
    if(bind(sd, (struct sockaddr *)&sa, sizeof(sa)) == -1) {
        printf("Probleme avec le bind\n");
        exit(1);
    }
    /* Initialisation de la queue d'ecoute des requetes*/
    listen(sd, MAX_REQUEST);
    printf("Serveur TCP en ecoute...\n");
    i = 0;

    while(1) {
        /* newsalength contient la taille de la structure sa attendue */
        newsalength = sizeof(newsa) ;
        if((newsd = accept(sd, (struct sockaddr *)&newsa, &newsalength)) < 0 ) {
          printf("Erreur sur accept\n");
          exit(1);
        }
        /* Compteur nombre de connexion */
        i++;
        /* nom du client */ 
        printf("Connection No %d sur le port %d...\nDebut de la discussion\n", i, ntohs(newsa.sin_port));
		/*Début de la discussion avec le client N°i*/
		/*On écoute la connexion entrante*/
		n = read(newsd, buff, BUFF_SIZE);
		printf("Réponse n°%d : %s\n n= %d\n",i,buff,n);
        
		/*Traitement de la requête*/

        res_calc = calculatrice(buff);

        printf("resultat calculette = %s\n",res_calc);
		write(newsd, res_calc, strlen(res_calc));//envoi de la reponse
		printf("fin de l'envoi au client\n ");
        close(newsd);
        
    }
    /* Fermeture du serveur. Never reached */
    free(res_calc); 
    close(sd);
    printf("Fin du serveur. Bye...\n");
    exit(0);
}