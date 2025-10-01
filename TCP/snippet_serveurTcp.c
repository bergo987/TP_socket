#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define MAX_REQUEST 10

main(argc,argv)
int argc ;
char *argv[] ;
{
    int sd;
    int port; 
    struct sockaddr_in sa; /* Numero de port du serveur */

    /* Structure Internet sockaddr_in */
    int newsd; /* Id de la socket entrante */
    struct sockaddr_in newsa; /* sockaddr_in de la connection entrante */
    int newsalength;
    int i;

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
    printf("Serveur pingTCP en ecoute...\n");
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
        printf("Connection No %d sur le port %d...\n", i, ntohs(newsa.sin_port));
        /* Tempo pour pouvoir faire un netstat... */
        printf("Ça marche on attend 10sec et on le vire\n");
        sleep(10);
        close(newsd);
    }
    /* Fermeture du serveur. Never reached */
    close(sd);
    printf("Fin du serveur. Bye...\n");
    exit(0);
}