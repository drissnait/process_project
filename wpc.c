#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define TAILLE_MESSAGE 256


void func(){	
	//int client=getpid();
	//printf("PID client : %d\n", getpid());
	//int producteur=fork();
	/*int producteur,travailleur1,travailleur2,travailleur3,collecteur;
	producteur=fork();	
	travailleur1=fork();
	travailleur2=fork();
	travailleur3=fork();
	collecteur=fork();
	if (producteur==0 && getppid()==client){
		printf("pid producteur =%d, ppid=%d\n",getpid(), getppid());	
	}
	
	else if (travailleur1==0 && getppid()==client){
		printf("pid travailleur 1=%d, ppid=%d\n",getpid(), getppid());	
	}

	else if (travailleur2==0 && getppid()==client){
		printf("pid travailleur 2=%d, ppid=%d\n",getpid(), getppid());	
	}
	else if (travailleur3==0 && getppid()==client){
		printf("pid travailleur 3=%d, ppid=%d\n",getpid(), getppid());	
	}
	else if (collecteur==0 && getppid()==client){
		printf("pid collecteur =%d, ppid=%d\n",getpid(), getppid());	
	}	*/

	

	/*else if (getpid()==client){
		printf("pid client =%d, ppid=%d\n",getpid(), getppid());		
		wait(&producteur);		
		wait(&travailleur1);
		wait(&travailleur2);
		wait(&travailleur3);
		wait(&collecteur);
			
	}*/
	
	/*if (getpid()!=v && getppid()==v){
		printf("Fils 1 : %d mon pere est : %d\n", getpid(),getppid());
		l=100;
		printf("Après modification de l : l=%d, k=%d\n", l,k);
	}
	fork();
	if(getppid()==v){
		printf("Fils 2  %d mon pere est : %d\n", getpid(), getppid());
		k=200;
		printf("Après modification de k : l=%d, k=%d\n", l,k);
	}*/

}


int main(int argc, char* argv[0])
{
	pid_t child_pid, wpid;
	int status;
	//func();
	int stat;
	int client=getpid();
	int tailleMax=7;
	pid_t tabTravailleurs[tailleMax];
	tabTravailleurs[0]=0;
	tabTravailleurs[1]=0;
	tabTravailleurs[2]=0;
	tabTravailleurs[3]=0;
	tabTravailleurs[4]=0;
	tabTravailleurs[5]=0;
	tabTravailleurs[6]=0;
	tabTravailleurs[7]=0;
	int tabPere[7];
	char resCommande[1000];
	int nbrProcessus=atoi(argv[2]);
	pid_t producteur, collecteur, fils_test;
	pid_t producteur_pid, collecteur_pid, fils_pid;
	printf("client = %d\n", getpid());

	int descripteurTubeProducteurFils[2];
	int descripteurTubeFilsCollecteur[2];


	char messageEcrire[TAILLE_MESSAGE];
	char messageLire[TAILLE_MESSAGE];
	int tess=3;

	if (nbrProcessus<2){
		printf("AVERTISSEMENT : Vous avez saisi un nombre de processus inférieure à 2, donc nous allons mettre en place le nombre de processus minimum = 2\n");
		nbrProcessus=2;	
	}
	else if(nbrProcessus>8){
		printf("ERREUR : Vous avez saisi un nombre de processus supérieure à 8\n");
		return 0;	
	}


	
	if (pipe(descripteurTubeProducteurFils)!=0){
		printf("Erreur création du tube");
		return EXIT_FAILURE;
	}
	if (pipe(descripteurTubeFilsCollecteur)!=0){
		printf("Erreur création du tube");
		return EXIT_FAILURE;
	}

	producteur=fork();
	//////////////////////////////////PRODUCTEUR////////////////////////////////////////
	if(producteur==0){
		//printf("Le producteur est first firsrt %d \n",producteur); 
		printf("je suis le producteur %d\n",getpid());
		producteur_pid=getpid();
		
		close(descripteurTubeProducteurFils[0]);

		//sprintf(messageEcrire, "Bonjour fils je suis le producteur");

		printf("Nous sommes dans le producteur (pid = %d).\nIl envoie le message suivant au fils : \"%s\".\n\n\n", getpid(), argv[4]);

		write(descripteurTubeProducteurFils[1], argv[4], TAILLE_MESSAGE);
		printf ("\n\n finfin, %d\n\n",getpid());
		//wait(NULL);	
		return 0;
	}
	


	if(getpid()==client){ 
		fils_test=fork();	
	}


///////////////////////////////////////////////////////FILS //////////////////////////////////////////

	if (fils_test==0){
		fils_pid=getpid();
		printf("\n\n je suis le nouveau fils mon pid est %d\n\n",fils_pid);	
		close(descripteurTubeProducteurFils[1]);	
		read(descripteurTubeProducteurFils[0], messageLire, TAILLE_MESSAGE);
        	printf("Nous sommes dans le fils (pid = %d).\nIl a reçu le message suivant du producteur : \"%s\".\n\n\n", getpid(), messageLire);

		//printf("Le fils va envoyer le résultat de la commande");
		close(descripteurTubeFilsCollecteur[0]);
		/*sprintf(messageEcrire, "Bonjour collecteur je suis le fils");
		printf("Nous sommes dans le fils (pid = %d).\nIl envoie le message suivant au collecteur : \"%s\".\n\n\n", getpid(), messageEcrire);
		tess=0;
		printf("tes ======> %d\n\n", tess);

		write(descripteurTubeFilsCollecteur[1], messageEcrire, TAILLE_MESSAGE);*/
		FILE *fpipe;
		char command[100];
		sprintf(command,"wc -%s %s",argv[1],messageLire);
		system(command);
		char c = 0;

		if (0 == (fpipe = (FILE*)popen(command, "r")))
		{
			perror("popen() failed.");
			exit(1);
		}
		int i=0;
		while (fread(&c, sizeof c, 1, fpipe))
		{
			resCommande[i]=c;
			printf("%c", c);
			i++;
		}
		//printf("\n on affiche le resultat qu'on va envoyer au père : %s",resCommande);
		pclose(fpipe);
	
		printf("on affiche ce qu'on va transmettre ---------- : %s\n\n", resCommande);


		/*if (strcmp(resCommande,"")==0){
			resCommande[0]="d";		
		}*/


		printf("Nous sommes dans le fils (pid = %d).\nIl envoie le message suivant au collecteur (resultat de la commande): \"%s\".\n\n\n", getpid(), resCommande);
		//write(descripteurTube2[1], messageEcrire, TAILLE_MESSAGE);
		write(descripteurTubeFilsCollecteur[1], resCommande, TAILLE_MESSAGE);
		printf ("\n\n finfin, %d\n\n",getpid());
		//wait(NULL);
		return 0;
	}


	tess=0;
	if(getpid()==client ){
		collecteur=fork();
	}
	

////////////////////////////////////COLLECTEUR////////////////////////////////////////////////
	if (collecteur==0){
		printf("On est dans le collecteur %d\n",getpid());
		collecteur_pid=getpid();
		
		close(descripteurTubeFilsCollecteur[1]);	
		read(descripteurTubeFilsCollecteur[0], messageLire, TAILLE_MESSAGE);
        	printf("Nous sommes dans le collecteur (pid = %d).\nIl a reçu le message suivant du fils : \"%s\".\n\n\n", getpid(), messageLire);
		printf("tes ======> %d\n\n", tess);
		printf ("\n\n finfin, %d\n\n",getpid());
		return 0;	
	}
	


	
	int fils;
	for(int i = 1; i<nbrProcessus; i++){
	    if (getpid() == client){
		tabTravailleurs[i] = fork();

	    }				
	
	}

	for (int i=0;i<nbrProcessus;i++){
		if(getpid()==tabTravailleurs[i]){
			printf("-----yes\n\n");

		return 0;		
		}	
	}	

	if (getpid()==client){	
		//printf("\n\n\n les processus travailleurs crées : \n\n");
		for(int i =0;i<nbrProcessus;i++){
			
			//printf("%d\n",tabTravailleurs[i]);	
			wait(&tabTravailleurs[i]);	
		}
	//printf("producteur : %d\n",producteur);
	//printf("collecteur : %d\n",collecteur);
	/*printf("type de comptage est : %s\n", argv[1]);
	char commande[100];
	sprintf(commande,"ls -%s",argv[1]);
	int nbr_ligne=atoi(argv[3]);
	printf("Nombre de ligne : %d\n", nbr_ligne);
	system(commande);*/
	wait(&collecteur_pid);
	wait(&fils_pid);
	wait(&producteur_pid);
	printf ("\n\n finfin client, %d\n\n",getpid());
	return 0;
	}	
	//wait(NULL);
	
	/*if(getpid()==client){		
		for(int i =0;i<8;i++){
			printf("%d,        %d\n",tabTravailleurs[i],tabPere[i]);	
			//wait(&tabTravailleurs[i]);	
		}
	}*/
	
	
	/*//int res = system("wc -m test.txt");	
	int client=getpid();	
	printf("je suis le pere, mon pid est %d\n", getpid());	*/

	/*pid_t pid_producteur;
	pid_t travailleur1;
	pid_t travailleur2;
	pid_t travailleur3;	*/
	
	//fork();	

	//pid_producteur = fork();
	//travailleur1=fork();
	//travailleur2=fork();
	//travailleur3=fork();


	/*if ( getppid()==client){
		printf("on est dans le producteur, le pid est : %d , le pid de mon pere est : %d\n", getpid(), getppid());	
	}*/
	/*else if (travailleur1==0 && getppid()==client){
		printf("on est dans le travailleur1, le pid est : %d \n", getpid());	
	}*/
	/*else if (travailleur2==0 && getppid()==client){
		printf("on est dans le travailleur2, le pid est : %d \n", getpid());	
	}
	else if (travailleur3==0 && getppid()==client){
		printf("on est dans le travailleur3, le pid est : %d \n", getpid());	
	}*/

}
