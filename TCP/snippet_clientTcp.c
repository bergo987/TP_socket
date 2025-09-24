#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>

int sd;
struct sockaddr_in sa;		/* Structure Internet sockaddr_in */
struct hostent *hptr ; 		/* Infos sur le serveur */

char *serveur ;        		/* Nom du serveur distant */
int port;


/* Recuperation nom du serveur */
serveur = argv[1];

/* Recuperation numero de port */
port = atoi(argv[2]);

/* Recuperation des infos sur le serveur dans /etc/hosts pour par DNS */
if((hptr = gethostbyname(serveur)) == NULL) 
{
	printf("Probleme de recuperation d'infos sur le serveur\n");
	exit(1);
}

/* Initialisation la structure sockaddr sa avec les infos  formattees : */
/* bcopy(void *source, void *destination, size_t taille); 		*/
bcopy((char *)hptr->h_addr, (char*)&sa.sin_addr, hptr->h_length);
/* Famille d'adresse : AF_INET ici */
sa.sin_family = hptr->h_addrtype;

if ((sp = getservbyname("key","tcp")) == NULL){
	printf("%s : Pas de service QUI sur ce système \n", myname);
	exit(1);
}

/* Initialisation du numero du port */
sa.sin_port = htons(port);
char *ip_str = inet_ntoa(sa.sin_addr);
printf("%s : %d\n", ip_str, ntohs(sa.sin_port));
	
