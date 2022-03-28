# anka







































Projet de programmation C orientée réseaux

Binôme : ANKASOUBAI Abdelmajid & HOUSNI Lamiaa
Groupe : 3AE C


Bonjour, bienvenue sur ce programme d'échanges basé sur les protocoles TCP et UDP.
Avec ce programme vous pourrez utiliser ces protocoles sous différentes formes :

De manière classique, avec un puits (-p) qui reçoit les informations d’une source (-s) 
Avec une nouvelle fonctionnalité de serveur de Boîte aux Lettres 

La fonctionnalité qui sera lancée au démarrage du programme sera celle classique.




Lancement de tsock 




Pour lancer le programme, ouvrez un terminal dans le répertoire de travail, puis tapez la commande :                             gcc tsock_v02.c -o tsock

Cela compilera le fichier tsock_v02.c. Vous pourrez ensuite lancer vos différents programmes. 





Usage classique





Protocole TCP : 

Il est nécessaire d'activer le puits en premier et en lui attribuant un numéro de port. 

Exemple : Je veux recevoir depuis l'hôte local sur le port 5555 en protocole TCP 
Commande à utiliser :
 ./tsock -p 5555

Seulement après avoir activé notre puits, on peut lancer notre source en lui attribuant l'IP destinataire et le numéro de port ou l'on veut envoyer nos informations.

Exemple : Je veux envoyer à destination de l'hôte local sur le port 5555 en protocole TCP
Commande à utiliser :
./tsock -s localhost 5555


Protocole UDP : 
                                            
Il est nécessaire d'activer le puits en premier et en lui attribuant un numéro de port. 

Exemple : Je veux recevoir depuis l'hôte local sur le port 5555 en protocole UDP
Commande à utiliser :
 ./tsock -p -u 5555

Seulement après avoir activé notre puits, on peut lancer notre source en lui attribuant l'IP destinataire et le numéro de port ou l'on veut envoyer nos informations.

Exemple : Je veux envoyer à destination de l'hôte local sur le port 5555 en protocole UDP
Commande à utiliser :
./tsock -s -u localhost 5555

Liste des options
 
        -n : permet de fixer le nombre de messages à envoyer (par défaut : 10)
        -l : permet de fixer la longueur des messages à envoyer (par défaut 30)
        -u : permet d'utiliser le protocole UDP car TCP est utilisé par défaut
Pour l'usage classique, il est important que l'utilisateur du puits, paramètre correctement la longueur des messages à recevoir pour pouvoir les recevoir correctement, sinon, la longueur par défaut sera de 30 caractères.



Usage BAL





                                                ===========================
                                                LANCEMENT D'UN SERVEUR BAL
                                                ===========================

Ici on peut lancer un serveur de Boîtes aux lettres sur une adresse IP et un port donné. Ce serveur se comporte comme une boucle infinie qui stocke les messages entrants dans des Boîtes aux lettres et les délivre par la suite après requête d'un récepteur.
 
Pour lancer notre serveur BAL, il faut utiliser l'option -b du programme et lui attribuer un port d'écoute.

Exemple :  je veux lancer un serveur BAL sur le port 5555 :
Commande à utiliser :
 ./tsock -b 5555


                                                ======================
                                                EMISSION DES MESSAGES
                                                ======================

Pour envoyer une ou plusieurs lettres,  à un boite aux lettres, il faut utiliser l'option -e# du programme avec # le numéro de Boîte aux lettres destinataire, ainsi que fournir l'adresse IP du serveur, et le port d'écoute.

Exemple : je veux envoyer des messages à la BAL n°5 sur la machine srv-tp04, sur le port 5555
Commande à utiliser :
                                               ./tsock -e5 srv-tp04 9000
 
NB : si vous ne précisez pas le numéro de BAL cela enverra par défaut sur la BAL n°0. 

Options disponibles pour l'émetteur :

    -n# : fixe le nombre de message à émettre avec # le nombre de messages
    -l# : fixe la longueur des messages à émettre avec # la longueur des messages pour cet envoi.
    

                                                ========================
                                                RÉCEPTION DES MESSAGES
                                                ========================
  
Pour récupérer les lettres d'une boîte aux lettres le principe est le même :
Exemple : Je veux récupérer les lettres de la BAL n°5 sur la machine srv-tp04 et sur le port 5555 :
Commande à utiliser :
                                                 ./tsock -r5 srv-tp04 5555
 
Vous ne pouvez ici que récupérer l'ensemble des lettres disponibles dans une des Boîtes aux lettres.
Les options -n et -l ne sont donc pas utilisables.





                                                ========================
                                                    Commentaires générales 
                                                ========================

L’explication du rôle de chaque fonction est détaillée dans le code en commentaires, vous trouverez aussi deux fonctions en commentaire ( Vide et Ajoute BAL) on les a utilisées pour remédier au problème  de segmentation mais ils ne sont plus nécessaires pour faire tourner le programme.

La version finale est distinguée par le commentaire (c'est la version finale ) sur le github 
