#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fnmatch.h>

typedef enum { 
    SOURCE, 
    USINE, 
    STOCKAGE, 
    JONCTION,
    RACCORDEMENT,
    USAGER
}Type;

typedef struct{
    Type type;
    char ID_Usine[51];
    char amont[51];
    char aval[51];
    int VolumeVersAval;
    float PourcentageFuite;
}Trancon;

typedef struct{
	char ID[51];
	int capacite_max;
	int captage;
}Usine;

int main()
{
    printf("Hello World");

    return 0;
}


//Vérifier sur un noeud de l'arbre est une feuille
bool estFeuille(pArbre a){
	if( a == NULL ){
		printf("Arbre vide !\n");
		return 0;
	}
	if( a->Fgauche == NULL && a->Fdroit == NULL ){
		return 1; // Vrai si l'arbre est une feuille
	}
	else{
		return 0; // Faux
	}
}

// Vérifier si le fils droit d'un noeud existe
bool existeFilsDroit(pArbre a){
	if( a == NULL ){
		printf("Erreur !\n");
		exit(1);
	}
	else if( a->Fdroit == NULL ){
		return 0; // Faux si l'arbre n'a pas de fils droit
	}
	else{
		return 1; // Vrai
	}
}

// Vérifier si le fils gauche d'un noeud existe
bool existeFilsGauche(pArbre a){
	if( a == NULL ){
		printf("Erreur !\n");
		exit(1);
	}
	else if( a->Fgauche == NULL ){
		return 0; // Faux si l'arbre n'a pas de fils gauche
	}
	else{
		return 1; // Vrai
	}
}




//==================================== AVL =============================================
                 
//-----------------CONSTRUCTION D'UN AVL-------------------------------

// Structure d'un noeud d'un AVL
typedef struct _arbre{
	Usine usine; // elmt : Element ; contenu du noeud
	struct _arbre* Fgauche;
	struct _arbre* Fdroit;
	int equilibre; //
}Arbre;  

typedef Arbre* pArbre;

// Déclaration et initialisation d'un noeud
pArbre creerArbre(Usine e){
	pArbre p = malloc(sizeof(Arbre));
	if(p == NULL){
		printf("Erreur d'allocation de mémoire.\n");
		exit(1);
	}
	p->usine = e;
	p->Fgauche = NULL;
	p->Fdroit = NULL;
	p->equilibre = 0; // Le noeud n'a pas de fils : son équilibre est à 0
	
	return p;
}

//-----------------EQUILIBRAGE D'UN AVL------------------------------------

// Insertion
pArbre insertionABR(pArbre a, Usine e){
	if(a == NULL){
		return creerArbre(e);
	}
	else if(strcmp(a->usine.ID,e.ID) > 0){
		a->Fgauche = insertionABR(a->Fgauche, e);
	}
	else if(strcmp(a->usine.ID,e.ID) < 0){
		a->Fdroit = insertionABR(a->Fdroit, e);
	}
	
	return a;
}

// Rééquilibrage 
pArbre insertionAVL(pArbre a, Usine e, int* h){
	if(a == NULL){
		*h = 1;
		return creerArbre(e);
	}
	else if(strcmp(a->usine.ID,e.ID) > 0){
		a->Fgauche = insertionAVL(a->Fgauche, e, h);
		*h = -*h;
	}
	else if(strcmp(a->usine.ID,e.ID) < 0){
		a->Fdroit = insertionAVL(a->Fdroit, e, h);
	}
	else{
		*h = 0;
		return a;
	}
	if(*h != 0){
		a->equilibre = a->equilibre + *h;
		a = equilibrerAVL(a);
		if(a->equilibre == 0){
			*h = 0;
		}
		else{
			*h = 1;
		}
	}
	
	return a;
}

// Suppression
pArbre suppressionAVL(pArbre a, Usine e, int* h){
	pArbre p1;
	if(a == NULL){
		*h = 0;
		return a;
	}
	else if(strcmp(a->usine.ID,e.ID) < 0){  // parcours pour trouver le noeud
		a->Fdroit = suppressionAVL(a->Fdroit, e);
	}
	else if(strcmp(a->usine.ID,e.ID) > 0){
		a->Fgauche = suppressionAVL(a->Fgauche, e);
		*h = -*h;
	}
	else if(existeFilsDroit(a)){  // si il y a un fils droit...
		a->Fdroit = suppMinAVL(a->Fdroit, h, &a->usine); //... on cherche le minimum dedans
	}
	else{
		p1 = a; // le noeud n'a qu'un fils gauche ou aucun fils
		a = a->Fgauche; // échange avec le fils gauche et suppression
		free(p1);
		*h = -1;
		return a;
	}
	if(*h != 0){
		a->equilibre = a->equilibre + *h;
		a = equilibrerAVL(a); 
		if(a->equilibre == 0){
			*h = -1;
		}
		else{ 
			*h = 0;
		}
	}
	
	return a;
}

pArbre suppMinAVL(pArbre a, int* h, Usine* e){  // s'il n'y a plus de fils gauche...
	pArbre p1;                               //... alors on a trouvé la plus petite valeur de l'arbre
	if(a->Fgauche == NULL){
		*e = a->usine;
		*h = -1;
		p1 = a;
		a = a->Fdroit;                       // on remplace le noeud actuel par le fils droit...
		free(p1);                            // ... et on libère la mémoire du noeud
		return a;
	}
	else{
		a->Fgauche = suppMinAVL(a->Fgauche, h, e); // appel récursif sur le sous-arbre de gauche
		*h = -*h;
	}
	if(*h != 0){
		a->equilibre = a->equilibre + *h;     // mise à jour du facteur d'équilibrage 
		a = equilibrerAVL(a);
		if(a->equilibre == 0){
			*h = -1;
		}
		else{
			*h = 0;
		}
	}
	
	return a;
}

pArbre equilibrerAVL(pArbre a){
	if(a->equilibre >= 2){
		if(a->Fdroit>= 0){
			return rotationGauche(a);
		}
		else {
			return doubleRotationGauche(a);
		}
	}
	else if(a->equilibre <= -2){
		if(a->Fgauche <= 0){
			return rotationDroite(a);
		}
		else{
			return doubleRotationDroite(a);
		}
	}
	return a;
}


pArbre doubleRotationGauche(pArbre a){
	a->Fdroit = rotationDroite(a->Fdroit);
	return rotationGauche(a);
}


pArbre doubleRotationDroite(pArbre a){
	a->Fgauche = rotationGauche(a->Fgauche);
	return rotationDroite(a);
}


pArbre rotationGauche(pArbre a){
	pArbre pivot = malloc(sizeof(Arbre));
	if(pivot == NULL){
		printf("erreur allocation mémoire\n");
		exit(1);
	}
	int eq_a = a->equilibre;
    int eq_p = pivot->equilibre;*
	a->equilibre = eq_a - max(eq_p,0)-1;
	pivot->equilibre = min(eq_a-2,eq_a+eq_p-2,eq_p-1);
	a =pivot;
    return a;
}

pArbre rotationDroite(pArbre a){
	pArbre pivot = malloc(sizeof(Arbre));
	if(pivot == NULL){
		printf("erreur allocation mémoire\n");
		exit(1);
	}
	int eq_a = a->equilibre;
    int eq_p = pivot->equilibre;*
	a->equilibre = eq_a - min(eq_p,0)+1;
	pivot->equilibre = max(eq_a+2,eq_a+eq_p+2,eq_p+1);
	a =pivot;
    return a;
}


pArbre Traitement(pArbre a){
	char buffer[80];
	int colonne = 0;
	char* parterne= "-;*;-;*;-";
	Usine e;
	int h;
	pArbre temp;
	while(fscanf(stdin, "%[^\n]", buffer ) != 0){
		if(fnmatch(buffer,paterne)==0){
			sscanf(buffer,"-;%s;-;%d;-",&(e.ID) &(e.capacite_max));
			e.captage = 0;
			insertionAVL(pArbre,e,&h);
		}
		
	}
}









pArbre recupUsine (){
	
}









pArbre creerUsineTemporaire(){
	int colonne = 0;
	if()

	pArbre dataUsine = malloc(sizeof(Arbre));
	if(dataUsine == NULL){
		printf("Erreur d'allocation de mémoire.\n");
		exit(1);
	}

	// FILE* file = tmpfile(); => pas vraiment utile ici 
	

}
















