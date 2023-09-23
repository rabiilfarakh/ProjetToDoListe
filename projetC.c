#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Structure jour reste
typedef struct
{
    int id, nbrj;
} JourRest;

// Structure date
typedef struct
{
    int j, m, a;
} date;

// Structure de deadline
typedef struct
{
    int j, m, a;
} deadline;

// Structure d'une tâche
typedef struct
{
    int id;
    char title[100];
    char description[200];
    deadline ded;
    char status[20];
} tache;
int ID = 0;

//////////////////////////switch////////////////////////
void getStatut(int choix, char *statut)
{
    switch (choix)
    {
    case 1:
        strcpy(statut, "a realiser");
        break;
    case 2:
        strcpy(statut, "en cours");
        break;
    case 3:
        strcpy(statut, "finalisee");
        break;
    default:
        exit(0);
    }
}

void addtache(tache *taches, int *tailleTabTache)
{
    tache newtache;
    int choixStatut;
    printf("\tTache %d :\n", ID + 1);
    newtache.id = ID + 1;

    printf("\tTitre de la tache : ");
    getchar();
    gets(newtache.title);

    printf("\tDescription de la tache : ");
    gets(newtache.description);

    // Obtenir la date actuelle
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    do
    {
        printf("\tEntrer une date de deadline valide (JJ/MM/AAAA) : ");
        scanf("%d/%d/%d", &newtache.ded.j, &newtache.ded.m, &newtache.ded.a);
    } while (!(newtache.ded.a >= timeinfo->tm_year + 1900 && newtache.ded.m >= 1 && newtache.ded.m <= 12 && newtache.ded.j >= 1 && newtache.ded.j <= 31));

    do
    {
        printf("\tStatut de la tache (1: a realiser, 2: en cours, 3: finalisee) : ");
        scanf("%d", &choixStatut);
    } while (choixStatut < 1 || choixStatut > 3);

    getStatut(choixStatut, newtache.status);
    printf("Taille : %d\n", (*tailleTabTache));
    taches[*tailleTabTache] = newtache;
    (*tailleTabTache)++;
    ID++;

}
// Fonction pour ajouter plusieurs nouvelles tâches
void addtaches(tache *taches, int *tailleTabTache)
{
    int numtaches, i, choixStatut, p;

    printf("   Combien de taches souhaitez-vous ajouter ? : ");
    scanf("%d", &numtaches);
    p = (*tailleTabTache) + numtaches;
    for (i = (*tailleTabTache); i < p; i++)
    {
        tache newtache;
        newtache.id = ID + 1;

        printf("\tTache %d :\n", i + 1);
        printf("\tTitre de la tache : ");
        getchar();
        gets(newtache.title);

        printf("\tDescription de la tache : ");
        gets(newtache.description);

        // Obtenir la date actuelle
        time_t rawtime;
        struct tm *timeinfo;
        time(&rawtime);
        timeinfo = localtime(&rawtime);

        do
        {
            printf("\tEntrer une date de deadline valide (JJ/MM/AAAA) : ");
            scanf("%d/%d/%d", &newtache.ded.j, &newtache.ded.m, &newtache.ded.a);
        } while (!(newtache.ded.a >= timeinfo->tm_year + 1900 && newtache.ded.m >= 1 && newtache.ded.m <= 12 && newtache.ded.j >= 1 && newtache.ded.j <= 31));

        do
        {
            printf("\tStatut de la tache (1: a realiser, 2: en cours, 3: finalisee) : ");
            scanf("%d", &choixStatut);
        } while (choixStatut < 1 || choixStatut > 3);

        getStatut(choixStatut, newtache.status);

        taches[*tailleTabTache] = newtache;
        (*tailleTabTache)++;
        ID++;
    }
}

// Trier par ordre alphabetique
void trieAlphabetique(tache *taches, int *tailleTabTache)
{
    tache t;
    int i, k = 1;

    while (k == 1)
    {
        k = 0;
        for (i = 0; i < *tailleTabTache - 1; i++)
        {
            if (strcmp(taches[i].title, taches[i + 1].title) == 1)
            {
                t = taches[i];
                taches[i] = taches[i + 1];
                taches[i + 1] = t;
                k = 1;
            }
        }
    }
}

// Trie par deadline
void TriaDeadline(tache *taches, int *tailleTabTache)
{
    tache t;
    int i, k = 1;

    while (k == 1)
    {
        k = 0;
        for (i = 0; i < *tailleTabTache - 1; i++)
        {
            if (taches[i].ded.a > taches[i + 1].ded.a)
            {
                t = taches[i];
                taches[i] = taches[i + 1];
                taches[i + 1] = t;
                k = 1;
            }
            else if (taches[i].ded.a == taches[i + 1].ded.a && taches[i].ded.m > taches[i + 1].ded.m)
            {
                t = taches[i];
                taches[i] = taches[i + 1];
                taches[i + 1] = t;
                k = 1;
            }
            else if (taches[i].ded.a == taches[i + 1].ded.a && taches[i].ded.m == taches[i + 1].ded.m && taches[i].ded.j > taches[i + 1].ded.j)
            {
                t = taches[i];
                taches[i] = taches[i + 1];
                taches[i + 1] = t;
                k = 1;
            }
        }
    }
}

// Fonction qui affiche les taches dont le deadline est supérieur ou égal à 3 jours
void afficheSup3(tache *taches, int tailleTabTache)
{
    int i;

    // Obtenir la date actuelle
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    for (i = 0; i < tailleTabTache; i++)
    {
        // Comparer les années, les mois et les jours pour vérifier si la deadline est supérieure ou égale à 3 jours
        if (taches[i].ded.a == timeinfo->tm_year + 1900 && taches[i].ded.m == timeinfo->tm_mon + 1 && taches[i].ded.j - timeinfo->tm_mday <= 3 && taches[i].ded.j - timeinfo->tm_mday > 0)
        {
            printf("%d\t%s\t%s\t%d/%d/%d\t%s\n", taches[i].id, taches[i].title, taches[i].description, taches[i].ded.j, taches[i].ded.m, taches[i].ded.a, taches[i].status);
        }
    }
}

// Fonctio qui modifie la description d'une tache
void modifierDescription(tache *taches, int tailleTabTache, tache x)
{
    int i,j=-1;
    for (i = 0; i < tailleTabTache; i++)
    {
        if (taches[i].id == x.id)
            j=i;
    }
    if(j!=-1){
        strcpy(taches[j].description, x.description);
        printf("la description est modifiee avec succee\n");
        
    }
    else
        printf("Id introuvable\n");
}

// Fonction qui modifier le statut d’une tache
void modifierStatut(tache *taches, int tailleTabTache, tache x)
{
    int i, choix,j=-1;
    for (i = 0; i < tailleTabTache; i++)
    {
        if (taches[i].id == x.id)
            j=i;
    }
    if(j!=-1){
        do{
            printf("(1. a realiser / 2. en cours / 3. finalisee)\n");
            scanf("%d", &choix);
        }while (!(choix != 1 || choix != 2 || choix != 3));
            getStatut(choix, taches[j].status);
            printf("la statut est modifiee avec succee\n");
    }else
        printf("Id introuvable\n");
}

// Fonction qui modifier le deadline d’une tache
void modifierDeadline(tache *taches, int tailleTabTache, tache x)
{
    int i,j=-1;
    for (i = 0; i < tailleTabTache; i++)
    {
        if (taches[i].id == x.id)
            j=i;
    }
    if(j!=-1){
        taches[j].ded.a = x.ded.a;
        taches[j].ded.m = x.ded.m;
        taches[j].ded.j = x.ded.j;
        printf("deadline est modifiee avec succee\n");
        }
}

// Fonction qui supprime une tache
void supprimerTache(tache *taches, int *tailleTabTache, int idASupprimer)
{
    int i,choix,j=-1;
    tache x;
    for (i = 0; i < *tailleTabTache; i++)
    {
        if (taches[i].id == idASupprimer)
        {
            j=i;
        }
        
    }
    if(j!=-1){
        do{
            printf("   ( 0.abondonner   1.supprimer ) \n");
            scanf("%d",&choix);
            if(choix==1){
                x=taches[j];
                taches[j]=taches[*tailleTabTache-1];
                taches[*tailleTabTache-1]=x;
                (*tailleTabTache)--;
                printf("Tache avec ID %d supprimee.\n", idASupprimer);
                }
            }while(choix!=0 && choix!=1);
        }else
           printf("ID %d n'existe pas.\n", idASupprimer);

    
}

// Fonction qui cherche une tache par sont id
int rechercheTache(tache *taches, int tailleTabTache, tache x)
{
    int i,choix;
    do{
        printf("     (1.recherche par Id    2.recherche par Titre)\n");
        scanf("%d",&choix);
    }while(choix!=1 && choix!=2);

    if(choix==1){
        printf("entrer votre Id: ");
        scanf("%d",&x.id);
        for (i = 0; i < tailleTabTache; i++)
        {
            if (taches[i].id == x.id)
            {
                return 1;
            }
        }
    return 0;
    }else if(choix==2){
        printf("entrer votre Title: ");
        getchar();
        gets(x.title);
        for (i = 0; i < tailleTabTache; i++)
        {
            if (strcmp(taches[i].title,x.title)==0)
            {
                return 1;
            }
        }
    return 0;       
    }
}

// Fonction qui cherche une tache par sont titre
int rechercheTitre(tache *taches, int tailleTabTache, char *titre)
{
    int i;
    for (i = 0; i < tailleTabTache; i++)
    {
        if (strcmp(titre, taches[i].title) == 0)
        {
            return 1;
        }
    }
    return 0;
}

// Afficher le nombre total des taches
int nbrTaches(int tailleTabTache)
{
    return tailleTabTache;
}

// Afficher le nombre de tâches complètes et incomplètes
void nbrTacheComInco(int tailleTabTache, tache *taches)
{
    int i;
    int complete = 0, incomplete = 0;

    for (i = 0; i < tailleTabTache; i++)
    {
        if (strcmp(taches[i].status, "a realiser")==0 || strcmp(taches[i].status, "en cours") == 0)
            incomplete++;
        if (strcmp(taches[i].status, "finalisee") == 0)
            complete++;
    }

    printf("Le nombre de taches completes est %d\n", complete);
    printf("Le nombre de teches incompletes est %d\n", incomplete);

}

// Afficher le nombre de jours restants jusqu'au délai de chaque tâche
void calculerNombreDeJoursRestants(tache *taches, JourRest *t, int tailleTabTache)
{
    int i;

    // Obtenir la date actuelle
    time_t now;
    struct tm *timeinfo;
    time(&now);
    timeinfo = localtime(&now);

    for (i = 0; i < tailleTabTache; i++)
    {
        t[i].id = taches[i].id;

        // Calculer le nombre de jours restants pour la tâche actuelle
        struct tm deadline;
        deadline.tm_year = taches[i].ded.a - 1900;
        deadline.tm_mon = taches[i].ded.m - 1;
        deadline.tm_mday = taches[i].ded.j;
        deadline.tm_hour = 0;
        deadline.tm_min = 0;
        deadline.tm_sec = 0;

        time_t deadlineTime = mktime(&deadline);
        double diff = difftime(deadlineTime, now);

        t[i].nbrj = (int)(diff / (60 * 60 * 24));
    }
}

// Fonction pour afficher toutes les tâches
void afficherTachesTableau(tache *taches, int tailleTabTache)
{
    int i;

    printf("\t-----------------------------------------------------------------------------------------\n");
    printf("\t| ID |    Titre de la tache   |    Description      |      Deadline      |    Statut     |\n");
    printf("\t-----------------------------------------------------------------------------------------\n");

    for (i = 0; i < tailleTabTache; i++)
    {
        printf("\t| %2d |", taches[i].id);

        // Afficher le titre
        if (strlen(taches[i].title) > 0)
        {
            printf(" %-20s   |", taches[i].title);
        }
        else
        {
            printf(" %-20s   |", "---");
        }

        // Afficher la description
        if (strlen(taches[i].description) > 0)
        {
            printf(" %-20s|", taches[i].description);
        }
        else
        {
            printf(" %-20s|", "---");
        }

        // Afficher la deadline
        printf(" %02d/%02d/%04d         |", taches[i].ded.j, taches[i].ded.m, taches[i].ded.a);

        // Afficher le statut
        if (strlen(taches[i].status) > 0)
        {
            printf(" %-10s    |\n", taches[i].status);
        }
        else
        {
            printf(" %-10s    |n", "---");
        }

        printf("\t------------------------------------------------------------------------------------------\n");
    }
}

int main()
{
    tache
        x;
    int tailleTabTache = 0, id, i;
    int choix, complete, incomplete;
    char *titre = malloc(50);
    tache taches[100];

    JourRest *t = (JourRest *)malloc(tailleTabTache * sizeof(JourRest));

    while (1)
    {
        printf("#############################################################################\n");
        printf("Menu :\n");
        printf("1.  Ajouter une nouvelle tache\n");
        printf("2.  Ajouter plusieurs taches\n");
        printf("3.  Trier par ordre alphabetique\n");
        printf("4.  Trier par deadline\n");
        printf("5.  Afficher la liste de toutes les taches\n");
        printf("6.  Affiche les taches dont le deadline sup ou egale a 3 jours\n");
        printf("7.  Modifie le description d'une tache\n");
        printf("8.  Modifie le statut d'une tache\n");
        printf("9.  Modifie le deadline d'une tache\n");
        printf("10. Supprimer une tache\n");
        printf("11. Recherche une tache \n");
        printf("12. Afficher le nombre total des taches\n");
        printf("13. Afficher le nombre de taches completes et incompletes\n");
        printf("14. Afficher le nombre de jours restants jusqu au delai de chaque tache\n");
        printf("0. Quitter\n");
        printf("#############################################################################\n");
        printf("Choisissez une option : ");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            // taches = (tache *)realloc(taches, (tailleTabTache + 1) * sizeof(tache));
            addtache(taches, &tailleTabTache);
            break;
        case 2:
            // taches = (tache *)realloc(taches, (tailleTabTache + 1) * sizeof(tache));
            addtaches(taches, &tailleTabTache);
            break;
        case 3:
            trieAlphabetique(taches, &tailleTabTache);
            break;
        case 4:
            TriaDeadline(taches, &tailleTabTache);
            break;
        case 5:
            afficherTachesTableau(taches, tailleTabTache);
            system("pause");
            break;
        case 6:
            afficheSup3(taches, tailleTabTache);
            system("pause");
            break;
        case 7:
            printf("entrer votre id: ");
            scanf("%d", &x.id);
            printf("entrer la nouvelle description: ");
            getchar();
            gets(x.description);
            modifierDescription(taches, tailleTabTache, x);
            system("pause");
            break;
        case 8:
            printf("entrer votre id: ");
            scanf("%d", &x.id);

            modifierStatut(taches, tailleTabTache, x);
            system("pause");
            break;
        case 9:
            printf("entrer votre id: ");
            scanf("%d", &x.id);

            do{
            printf("entrer le nouveau deadline (jj/MM/AA): ");
            scanf("%d/%d/%d", &x.ded.j, &x.ded.m, &x.ded.a);
            
            }while(x.ded.a<2023);
            modifierDeadline(taches, tailleTabTache, x);
            system("pause");
            break;
        case 10:
            printf("entrer votre id: ");
            scanf("%d", &id);
            supprimerTache(taches, &tailleTabTache, id);
            system("pause");
            break;
        case 11:

            if (rechercheTache(taches, tailleTabTache, x) == 0){
                printf("tache n existe pas \n", x.id);
                system("pause");
            }
            else{
                printf("tache trouvee avec succee\n", x.id);
                system("pause");
            }

            break;
        case 12:
            printf("le nombre de taches est %d", nbrTaches(tailleTabTache));
            system("pause");
            break;
        case 13:
            nbrTacheComInco(tailleTabTache, taches);
            system("pause");
            break;
        case 14:
            t = (JourRest *)realloc(t, tailleTabTache * sizeof(JourRest));
            calculerNombreDeJoursRestants(taches, t, tailleTabTache);
            printf("-----------------------------------\n");
            printf("ID\t| Nombre de jours restants |\n");
            printf("-----------------------------------\n");

            for (i = 0; i < tailleTabTache; i++)
            {
                // Affiche les données sous forme de tableau
                printf("%d\t| %d                       |\n", t[i].id, t[i].nbrj);
            }
            printf("-----------------------------------\n");
            system("pause");
            break;
        case 0:
            return 0;
        }
    }

    return 0;
}