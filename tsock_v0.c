#include <sys/types.h>
/* constantes relatives aux domaines, types et protocoles */
#include <sys/socket.h>
/* constantes et structures propres au domaine UNIX */
#include <sys/un.h>
/* constantes et structures propres au domaine INTERNET */
#include <netinet/in.h>
/* structures retournées par les fonctions de gestion de la base de
données du réseau */
#include <netdb.h>
/* pour les entrées/sorties */
#include <stdio.h>
/* pour la gestion des erreurs */
#include <errno.h>
#include <stdlib.h>
/*pour getopt*/
#include <unistd.h>





/*---------------creation de fonction-----------------------*/
/* ----------------------déclaration de fonctions ----------------------------*/ 

//void construiremessage2(char *message, char motif, int lg, int i);
//void afficher_message(char *message, int lg);
void envoi_UDP(int port, int nb_message  , int lg_msg, char*dest);
void reception_UDP(int port, int nb_message , int lg_message);
void construire_message(char *message,char motif,int lg);
/*---Création du socket UDP et envoi et reception ---------*/

				      


/*--------------définition de fonction --------------------------------------------------*/
/*----------------fonction construction de message---------------------------------*/ 
void construire_message(char *message,char motif,int lg){
	int i ;
	for (i=0;i<lg;i++)
		message[i]=motif;
}
/*------------------fonction affichage  message ----------------------------------------*/ 
void afficher_message(char *message, int lg)

{
  	for (int i=0;i<lg;i++)
  	    printf("%c", *(message+i));
  	printf("]\n");
}

/*-----------------------fonction envoi sous protocole UDP -------------------------------*/ 

void envoi_UDP(int port ,int nb_mess , int lg_msg,char*dest)
{
	
  	int length_addr_dist;
  	length_addr_dist=sizeof(struct sockaddr_in);
 	 
  	int sock;
 	int sent;
  	struct sockaddr_in addr_distant;
  	struct hostent* hp;
  	char *message=malloc(sizeof(char)*lg_msg) ;

   	if((sock=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP))==-1) /* creation socket + test erreur ( -1 si le socket ne s'ouvre pas correctement) */
    {
      printf("pb création du socket\n");
      exit(1);
    }
  	memset((char*)&addr_distant,0,sizeof(addr_distant));
  	addr_distant.sin_family=AF_INET;  /*internet*/ 
  	addr_distant.sin_port=htons(port);  /*num de port */ 

  	if((hp=gethostbyname(dest))==NULL)
    {
      printf("Erreur du gesthostbyname _n");/*num de port */ 
      exit(1);
    }

  	memcpy((char*)&(addr_distant.sin_addr.s_addr), hp->h_addr, hp->h_length);

  	for (int i=1; i<=nb_mess ; i++)
    {
    	construire_message(message,'a',lg_msg);
      	printf("SOURCE : Envoi n°%d (%d) : [", i, lg_msg);
      	

      	if((sent=sendto(sock,message,lg_msg,0,(struct sockaddr*)&addr_distant,sizeof(addr_distant)))==-1)   
      	{
      		printf("Erreur sendto\n");
      		exit(1);
      	}
      	afficher_message(message,sent);
    }

  	if(close(sock)==-1) //fermeture du socket + test 
    {
      printf("Echec à la destruction du socket\n");
      exit(1);
    }
}
/*------------------------------------------Reception UDP-------------------------------------------*/


void reception_UDP(int port, int nb_message, int lg_message)
{

  int sock;
  struct sockaddr_in addr_local,addr_distant;
  int recv;
  int lg_dist;
  char *message=malloc(sizeof(char)*lg_message) ;

  if((sock=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP))==-1) /*creation du socket*/ 
    {
      printf("Erreur à la création du socket\n");
      exit(1);
    }
  
  	memset((char*)&addr_local,0,sizeof(addr_local));         /*reset de addr_local*/ 
 	addr_local.sin_family=AF_INET;              //attribution des différents attributs de addr_local
  	addr_local.sin_port=port;
  	addr_local.sin_addr.s_addr=INADDR_ANY;     //par defaut n'imp quelle machine 

	
  	if ((bind(sock,(struct sockaddr*)&addr_local, sizeof(addr_local)))==-1) //bind de la réception 
    {
      	printf("Echec du Bind\n");
      	exit(1);
    }
	


  	lg_dist=sizeof(addr_distant);

    int i=1;
    while(recv!=0)
    {
        recv=recvfrom(sock,message,lg_message,0,(struct sockaddr*)&addr_distant,&lg_dist);
        if (recv==-1) // prcess de réception recvfrom natif à l'API socket, + test 
        {
            printf("Erreur receive from\n");
            exit(1);
        }

        if (recv!=0)
        {
	  printf("PUITS : Réception n°%d (%d) : [",i,lg_message);  //mise en forme 
            afficher_message(message,recv);
        }
        if (i==nb_message)
        {
            recv=0;
            printf("On a atteint le nombre de messages à recevoir\n");
        }

        i++;
    }
  
   if(close(sock)==-1) 
    {
      printf("Echec à la destruction du socket\n");
      exit(1);
    }
}



void main (int argc, char **argv)
{
/* ---------------------------declaration des paramètre--------------------------------------- */ 
	int c;
	extern char *optarg;
	extern int optind;
	int nb_message = -1; /* Nb de messages à envoyer ou à recevoir, par défaut : 10 en émission, infini en réception */
	int source = -1 ; /* 0=puits, 1=source */
	char *dest ;
	int port ;
	int tcp=1 ; /* -ici si tcp=1 on est en tcp et si tcp=0 on est en udp ------- par defaut en tcp */ 
	int lg =30; /* longueur du message par défaut */ 
	
/*-----------------------------------------------Debut--------------------------------*/ 
	while ((c = getopt(argc, argv, "pn:su")) != -1) {
		switch (c) {
		case 'p':
			if (source == 1) {
				printf("Warning :\n On ne peut être source et puits en même temps, Please enlever une des deux options -s ou -p\n\n");
				exit(1);
			}
			source = 0;
			break;

		case 's':
			if (source == 0) {
				printf("Warning :\n On ne peut être source et puits en même temps, Please enlever une des deux options -s ou -p\n\n");
				exit(1) ;
			}
			source = 1;
			break;
			
		case 'u':
			tcp=0;
			printf("l'envoi se fait via udp");
			break;
				       
		case 'n':
			nb_message = atoi(optarg);
			break;

		default:
			printf("usage: ./tsock [-p|-s][-n ##]\n");
			break;
		}
	}

	if (source == -1) {
		printf("usage: ./tsock [-p|-s][-n ##]\n");
		exit(1) ;
	}
	

	if (source == 1){
		printf("on est dans le source\n");
	}
	else
		printf("on est dans le puits\n");
	
	if (tcp==1)
            printf("Protocole de transport : TCP | ");
      
        else
            printf("Protocole de transport : UDP | ");
				       
	if (nb_message != -1) {
		if (source == 1)
			printf("nb de tampons à envoyer : %d\n", nb_message);
		else
			printf("nb de tampons à recevoir : %d\n", nb_message);
	} else {
		if (source == 1) {
			nb_message = 10 ;
			printf("nb de tampons à envoyer = 10 par défaut\n");
		} else
		printf("nb de tampons à envoyer = infini\n");

	}

	dest=argv[argc-2];
	printf("le nom de la machine est: %s \n",dest);
        port=atoi(argv[argc-1]);
	printf("le numéro de port est : %d \n ",port);
    

/*------------------------Envoi du message en UDP ----------------------------------*/

				       
if (source==1 & tcp ==0){
       envoi_UDP(port,nb_message,lg,dest);
 }
/*------------------------Reception UDP---------------------*/
 else if (source==0 & tcp==0) {
    reception_UDP(port,nb_message,lg);
 }
 
}


