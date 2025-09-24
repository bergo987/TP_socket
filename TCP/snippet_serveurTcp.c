#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#define BUFFSIZE 256

  /* Taille de la file d'attente  initialisé par listen*/
#define BACKLOG 10
#define MAXHOSTNAME 64

/* Nombres de requiêtes traitées par le programme */
#define MAXREQ 10

int main(int argc,char **argv)
{
  int s ,t ; // descripteur de socket 
  int count_req; 
  int i ; 

  void quiest();
  struct sockaddr_in sa;	/* Structure Internet sockaddr_in */
  struct hostent *hptr; 	/* Infos sur le serveur */
  struct servent *sp ; /* Structure service internet */
  int port;        		/* Numero de port du serveur */
  int newsd;			/* Id de la socket entrante */
  struct sockaddr_in newsa;	/* sockaddr_in de la connection entrante */
  int newsalength;
  struct hostent *newhptr; 	/* Infos sur le client suivant /etc/hosts */

  port = atoi(argv[1]);

  /* Initialisation la structure sockaddr sa */
  /* Famille d'adresse : AF_INET = PF_INET */
  sa.sin_family = AF_INET;

  /* Initialisation du numero du port */
  sa.sin_port = htons(port);
  sa.sin_addr.s_addr = INADDR_ANY;

  char localhost[MAXHOSTNAME]; 
  /* Recuperation du numéro de port serveur dans la structure sa */
  sa.sin_port = htons(port) ; 

  /* création de la socket */
  s = socket(AF_INET , SOCK_STREAM,0); 
  if (s <0 ){
    perror("Serveur : problème lors de la création socket"); 
    exit (1); 
  }

  /* Lien socket avec adresse IP et Port */
  if(bind(s,&sa, sizeof(sa))<0){
    printf("Serveur : problème bind \n"); 
    exit(1); 
  }
  listen(s,BACKLOG); 
  printf("Serveur TCP en écoute\n");

  for (count_req = 0 ; count_req <= MAXREQ ; count_req++){
    /* Attend une requête sur la primitive accept */
    i = sizeof(newsa); 
    newsalength = sizeof(newsa) ;
    newsd = accept(s, &newsa, &newsalength);
    if(newsd < 0){
      printf("Erreur sur accept\n");
      exit(1);
    }

    printf("Connection N° %d sur le port %d...\n", i, ntohs(newsa.sin_port));
    printf("Requête n° %d\n", count_req); 
    sleep(10);
    /* Traitement de la requête*/
    quiest();
    close(t); 
  }
  /* Fermeture de la socket reserve  */
  close(s); 
  printf("fin de service pour %s\n", localhost);
  exit(0); 
}

void quiest(){ /* Traitement de la requête */
  printf("Je suis trop fort\n");

}