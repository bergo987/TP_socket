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
#define BACKLOG 1 
#define MAXHOSTNAME 10

/* Nombres de requiêtes traitées par le programme */
#define MAXREQ 10

int main(argc,argv)
{
  int s ,t ; // descripteur de socket 

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

  sp = getservbyname("key", "tcp") ; 

  if (( sp == NULL )){
    printf("Pas de servie QUI sur ce système"); 
    exit(1); 
  }
  /* Recuperation du numéro de port serveur dans la structure sa */
  sa.sin_port = htons(sp->s_port) ; 

  /* Récuperation nom de la machine hote, ici localhost */
  gethostname (localhost, MAXHOSTNAME);
  /* Remplit la structure adresse sa */
  hptr = gethostbyname(localhost) ; 
  bcopy(hptr->h_addr,(char*)&sa.sin_addr,hptr->h_length) ; 
  sa.sin_family = AF_INET ; 
  /* Allocation d'un descripteur de socket */
  s = socket(AF_INET , SOCK_STREAM,0); 
  if (s <0 )

}