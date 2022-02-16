


void EmetteurBAL(int port, char* dest, int nb_message, int lg_msg, int nBAL)
{
    //Déclarations
    int sock;
    struct sockaddr_in addr_distant ;
    int lg_addr_distant=sizeof(addr_distant);
    struct hostent *hp;
    char motif;
    char * message=malloc(lg_msg*sizeof(char));
    int envoi=-1;
    int lg_pdu=50;
    int lg_recv;
    char*pdu=malloc(lg_pdu*sizeof(char));

//---------------------------------------
//--------Etablissement connexion--------
//---------------------------------------
    printf("            SOURCE : Emission de lettres pour la BAL n°%d\n",nBAL);
    printf("____________________________________________________________________\n\n");

    sprintf(pdu,"0 %d %d %d",nBAL, nb_message,lg_msg);

    //Création socket
    if((sock=socket(AF_INET,SOCK_STREAM,0))==-1)
    {
        printf("Erreur à l'ouverture du Socket Stream");
        exit(1);
    }
    //Construction adresse socket distant
    memset((char*)&addr_distant,0,sizeof(addr_distant));
    addr_distant.sin_family=AF_INET;  //Internet
    addr_distant.sin_port=port;       //Numéro de Port

    //Affectation IP
    if((hp=gethostbyname(dest))==NULL)
    {
        printf("Erreur de requête IP.\n");
        exit(1);
    }

    memcpy((char*)&(addr_distant.sin_addr.s_addr), hp->h_addr , hp->h_length);

    //Demande de connexion

    if (connect(sock,(struct sockaddr *)&addr_distant,sizeof(addr_distant))==-1)
    {
        printf("Erreur lors de la connexion, en attente de la tentative suivante \n");
        exit(1);
    }
//-----------------------------------------
//----------------Envoi PDU----------------
//-----------------------------------------

    if ((envoi=write(sock,pdu,lg_pdu))==-1)
    {
        printf("Echec de l'envoi du PDU Emetteur (fonction write en défaut)\n");
        exit(1);
    }
    //-----------------------------------------
//----------TRANSFERT DE DONNEES-----------
//-----------------------------------------



    for (int i=1; i<=nb_message;i++)
    {
        printf("SOURCE : lettre n°%d (%d) [", i,lg_msg);

        //Création du message
        construire_message2(message,motif,lg_msg,i);
        printbuffer2(nBAL,message);
        afficher_message(message,lg_msg);

        //Envoi du message

        if ((envoi=write(sock,message,(lg_msg)/*,0,(struct sockaddr*)&addr_distant,lg_addr_distant)*/))==-1)
        {
            printf("Echec de l'envoi du message (fonction write en défaut)\n");
            exit(1);
        }

    }



    //Fermeture connexion

    if(shutdown(sock,2)==-1)
    {
        printf("Erreur à la fermeture de la connexion TCP \n");
        exit(1);
    }

    //Fermeture Socket
    if (close(sock)==-1)
    {
        printf("Echec de la fermeture du socket distant");
        exit(1);
    }

    free(message);
    free(pdu);
    printf("Envoi effectué avec succès\n");
}

