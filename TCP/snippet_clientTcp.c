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
#include <unistd.h>
#define BUFFSIZE 256



int main (int argc, char *argv[]){
int sd;
int len;
int s;

struct sockaddr_in sa;		/* Structure Internet sockaddr_in */
struct hostent *hptr ; 		/* Infos sur le serveur */
struct servent *sp;			/* Structure service Internet */
char *myname; 				/*pointeur sur le nom du programme*/
char buf[BUFFSIZE];
char *serveur ;        		/* Nom du serveur distant */
char *fin = "quit";

int port;			/* Pointeurs sur le serveur et l'utilisateur */ 
char user[BUFFSIZE];
myname = argv[0];

if (argc != 3) {
printf("Usage : %s serveur user\n", myname); exit(1);
}

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
bcopy((char *)hptr->h_addr, (char*)&sa.sin_addr, hptr->h_length);
/* Famille d'adresse : AF_INET ici */
sa.sin_family = hptr->h_addrtype;

/* Initialisation du numero du port */
sa.sin_port = htons(port);
char *ip_str = inet_ntoa(sa.sin_addr);
printf("%s : %d\n", ip_str, ntohs(sa.sin_port));


while(1){
	printf("calcul à effectuer?\n");
	int k = read(0, buf, BUFFSIZE);
	
	/*Condition de sortie du serveur*/
	if(strcmp(buf,fin)==0){
		exit(0);
	}

	/* Création de la socket client */
	if((s = socket (AF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket");
		exit(1);
	}

	/*Connexion au serveur, infos dans la structure adresse internet sa */
	if (connect(s, (struct sockaddr *)&sa, sizeof(sa)) < 0){
		perror("connect");
		exit(1);
	}
	printf("Connexion établie avec le serveur\n");

	/* Envoi de la requête */ 
	fflush(stdout);
	fflush(stdin);
	//*user = scanf("%[^\n]", buf);
	buf[k]='\0';
	printf("Envoi de la requête : %s\n", buf);
	write(s, buf, k);

	/* Lecture de la réponse */ 
	int n = read(s, buf, BUFFSIZE);
	buf[n]='\0';
	/* Affichage de la réponse */ 
	printf("Réponse : %s\n", buf); 
		
	close(s);
}

/* Fermeture de la connexion */
exit(0);
}

