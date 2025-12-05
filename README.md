# Projet-MI-4-G
- differentes structures pour chaque etapes
- (liste chaines pour le traitement de l'eau) ?
- grand AVL
- des arbres pour les fuites
- calcul des fuites suivant les données (20% des eaux traités)
- histogramme en format PNG (a la fin)
- deroulement : 
source -> usine -> stockage -> jonction -> raccordement -> usager



//==================================== AVL =============================================

// AVL <=> Arbre binaire de recherche automatiquement équilibré ("auto-équilibré"), il reste équilibré après opération

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

//-------------OPERATION SUR UN ARBRE BINAIRE-------------------------

//Vérifier sur un noeud de l'arbre est une feuille
bool estFeuille(pArbre a);

// Vérifier si le fils droit d'un noeud existe
bool existeFilsDroit(pArbre a);

// Vérifier si le fils gauche d'un noeud existe
bool existeFilsGauche(pArbre a);
                 

//-----------------CONSTRUCTION D'UN AVL-------------------------------

// Structure d'un noeud d'un AVL
typedef struct _arbre{
	int valeur; // elmt : Element ; contenu du noeud
	struct _arbre* Fgauche;
	struct _arbre* Fdroit;
	int equilibre; //
}Arbre;  

typedef Arbre* pArbre;

// Déclaration et initialisation d'un noeud
pArbre creerArbre(int v){
	pArbre p = malloc(sizeof(Arbre));
	if(p == NULL){
		printf("Erreur d'allocation de mémoire.\n");
		exit(1);
	}
	p->valeur = v;
	p->Fgauche = NULL;
	p->Fdroit = NULL;
	p->equilibre = 0; // Le noeud n'a pas de fils : son équilibre est à 0
	
	return p;
}

//------------------OPERATIONS--------------------------------------------

// Opération de recherche
pArbre recherche(pArbre a, int v){
	if(a == NULL){
		return NULL;
	}
	else if(a->valeur == v){
		return a;
	}
	else if(v < a->valeur){
		return recherche(a->Fgauche, v);
	}
	else{
		return recherche(a->Fdroit, v);
	}
}

//-----------------EQUILIBRAGE D'UN AVL------------------------------------

// Insertion
pArbre insertionABR(pArbre a, int v){
	if(a == NULL){
		return creerArbre(v);
	}
	else if(v < a->valeur){
		a->Fgauche = insertionABR(a->Fgauche, v);
	}
	else if(v > a->valeur){
		a->Fdroit = insertionABR(a->Fdroit, v);
	}
	
	return a;
}

// Rééquilibrage 
pArbre insertionAVL(pArbre a, int v, int* h){
	if(a == NULL){
		*h = 1;
		return creerArbre(v);
	}
	else if(v < a->valeur){
		a->Fgauche = insertionAVL(a->Fgauche, v, h);
		*h = -*h;
	}
	else if(v > a->valeur){
		a->Fdroit = insertionAVL(a->Fdroit, v, h);
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
pArbre suppressionAVL(pArbre a, int v, int* h){
	pArbre p1;
	if(a == NULL){
		*h = 0;
		return a;
	}
	else if(v > a->valeur){  // parcours pour trouver le noeud
		a->Fdroit = suppressionAVL(a->Fdroit, v);
	}
	else if(v < a->valeur){
		a->Fgauche = suppressionAVL(a->Fgauche, v);
		*h = -*h;
	}
	else if(existeFilsDroit(a)){  // si il y a un fils droit...
		a->Fdroit = suppMinAVL(a->Fdroit, h, &a->valeur); //... on cherche le minimum dedans
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

pArbre suppMinAVL(Arbre a, int* h, int* v){  // s'il n'y a plus de fils gauche...
	pArbre p1;                               //... alors on a trouvé la plus petite valeur de l'arbre
	if(a->Fgauche == NULL){
		*v = a->valeur;
		*h = -1;
		p1 = a;
		a = a->Fdroit;                       // on remplace le noeud actuel par le fils droit...
		free(p1);                            // ... et on libère la mémoire du noeud
		return a;
	}
	else{
		a->Fgauche = suppMinAVL(a->Fgauche, h, v); // appel récursif sur le sous-arbre de gauche
		*h = -*h;
	}
	if(*h != 0){
		a->quilibre = a->equilibre + *h;     // mise à jour du facteur d'équilibrage 
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

















		 
	
	
	
	
	
	
	
	
	
	
	
	
	








