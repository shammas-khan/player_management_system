#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Player {
    int playerId;
    char name[30];
    int jno;
    int matchPlayed;
    int wkt;
    int runs;
} Player;

void menu(Player**, int*, int*);
void addPlayer(Player**, int*, int*);
void removePlayer(Player*, int*);
void displayPlayers(Player*, int*);
void searchPlayer(Player*, int*);
void updatePlayer(Player*, int*);
void displayPlayer(Player);
void displayPlayerSorted(Player*,int*);
void sortPlayer(Player*,int ,int,int);

void main() {
    Player* playerList = (Player*)calloc(10, sizeof(Player));
    int playerCount = 0;
    int size = 10;

    //heardcore data
    playerList[0] = (Player){0,"virat kohli", 100, 18, 10, 5000}; (playerCount)++;
    playerList[1] = (Player){1,"rohit sharma", 90, 45, 30, 4500}; (playerCount)++;
    playerList[2] = (Player){2,"jasprit bumrah", 70, 1, 150, 256}; (playerCount)++;
    playerList[3] = (Player){3,"MSD", 150, 7, 0, 8000}; (playerCount)++;
    playerList[4] = (Player){4,"abraham benjamin de villiers", 100, 17, 0, 7000}; (playerCount)++;


    menu(&playerList, &playerCount, &size);
}

void menu(Player** playerList, int* playerCount, int* size) {
    char check;
    do {
        printf("\n\n\t\t\t\tCricket Player Management System\n");
        printf("Enter\n 1->Adding \n 2->removing \n 3->searching \n 4->updating \n 5->displaying \n 6->displaySortedPlayer \n 7->ending \n");
        printf("Enter your choice: ");
        scanf(" %c", &check);
        getchar();
        printf("\n");
        switch (check) {
            case '1':
                addPlayer(playerList, playerCount, size);
                break;
            case '2':
                removePlayer(*playerList, playerCount);
                break;
            case '3':
                searchPlayer(*playerList, playerCount);
                break;
            case '4':
                updatePlayer(*playerList, playerCount);
                break;
            case '5':
                displayPlayers(*playerList, playerCount);
                break;
            case '6':
                displayPlayerSorted(*playerList,playerCount);
                break;
            case '7':
                printf("\n\n\t\t\t\tThank you for using Cricket Player Management System\n");
                break;
            default:
                printf("Invalid Choice\n");
                printf("\n\n\t\t\t\tThank you for using Cricket Player Management System\n");
                getchar();
                break;
        }
    } while (check != '7');
}

void addPlayer(Player** playerList, int* playerCount, int* size) {
    int count = *playerCount;

    if (count >= (*size)) {
        *playerList = realloc(*playerList, (*size + 10) * sizeof(Player));
        (*size) += 10;
    }

    printf("Enter player name: ");
    fgets((*playerList)[count].name, sizeof((*playerList)[count].name), stdin);
    (*playerList)[count].name[strcspn((*playerList)[count].name, "\n")] = '\0';

    printf("Enter player jersey number: ");
    scanf("%d", &(*playerList)[count].jno);

    printf("Enter number of matches played: ");
    scanf("%d", &(*playerList)[count].matchPlayed);

    printf("Enter number of wickets taken: ");
    scanf("%d", &(*playerList)[count].wkt);

    printf("Enter number of runs scored: ");
    scanf("%d", &(*playerList)[count].runs);
    (*playerList)[count].playerId=count;

    if((*playerList)[count].runs<0 || (*playerList)[count].matchPlayed<0 || (*playerList)[count].wkt<0){
        printf("Invalid Input\n");
        getchar();
        addPlayer(playerList,playerCount,size);
        return;
    }

    (*playerCount)++;
}



void displayPlayers(Player* playerList, int* playerCount) {
    int count = *playerCount;
    printf("\nPlayer Details:\n\n");
    for (int i = 0; i < count; i++) {
        printf("Player Id:%d\n",playerList[i].playerId);
        printf("Name: %s\n", playerList[i].name);
        printf("Jersey Number: %d\n", playerList[i].jno);
        printf("Matches Played: %d\n", playerList[i].matchPlayed);
        printf("Wicket Taken: %d\n", playerList[i].wkt);
        printf("Run Scored: %d\n\n", playerList[i].runs);
    }
}

void removePlayer(Player* playerList, int* playerCount) {
    int id;
    printf("enter player id to remove :");
    scanf("%d",&id);

    int count=(*playerCount);

    for(int i=id;i<count-1;i++){
        playerList[i]=playerList[i+1];
        playerList[i].playerId=i;
    }
    if(id<count)
    (*playerCount)--;
}

void displayPlayer(Player searchedPlayer){
    printf("\nPlayer Id:%d\n",searchedPlayer.playerId);
    printf("Name: %s\n", searchedPlayer.name);
    printf("Jersey Number: %d\n", searchedPlayer.jno);
    printf("Matches Played: %d\n", searchedPlayer.matchPlayed);
    printf("Wicket Taken: %d\n", searchedPlayer.wkt);
    printf("Run Scored: %d\n\n", searchedPlayer.runs);
}
void searchPlayer(Player* playerList, int* playerCount) {
    int choice;
    printf("search player by:");
    printf("\n1->id\n2->name\n");
    printf("enter your choice:");
    scanf("%d",&choice);
    getchar();
    int isSearch=0;
    if(choice==1){
        int id;
        printf("enter id of player:");
        scanf("%d",&id);
        if(id<(*playerCount)){
            if(!isSearch){
                printf("\nSearched Player Are:\n\n");
                isSearch=1;
            }
            displayPlayer(playerList[id]);
        }
        
    }
    else{
        char name[30];
        printf("\nenter string to search:");
        
        fgets(name,sizeof(name),stdin);
        name[strcspn(name, "\n")] = 0;//    name[strcspn(name, "\n")] = '\0'; strcspn(string,string) return index of second string


    
        for(int i=0;i<(*playerCount);i++){
           char copy[30];
           strcpy(copy,playerList[i].name);
           char* search=strstr(strlwr(copy),strlwr(name));
           if(search){
            if(!isSearch){
                printf("\nSearched Player Are:\n\n");
                isSearch=1;
            }
            displayPlayer(playerList[i]);
           }
        }
    }
    
    if(!isSearch){
        printf("\nNo Player Found\n");
    }
}

void updatePlayer(Player* playerList, int* playerCount) {
    int id;
    printf("enter player id for updating details:");
    scanf("%d",&id);
    if(id>=(*playerCount)){
        printf("no such player exist");
        return;
    }

    char ch;
    printf("enter y/n to update matchPlayed:");
    getchar();
    scanf("%c",&ch);
    if(ch=='y'){
        int temp;
        printf("how many matches to add:");
        scanf("%d",&temp);
        playerList[id].matchPlayed+=temp;
    }

    printf("enter y/n to update wicket taken:");
    getchar();
    scanf("%c",&ch);
    if(ch=='y'){
        int temp;
        printf("how many wickets to add:");
        scanf("%d",&temp);
        playerList[id].wkt+=temp;
    }

    printf("enter y/n to update run score:");
    getchar();
    scanf("%c",&ch);
    if(ch=='y'){
        int temp;
        printf("how many runs to add:");
        scanf("%d",&temp);
        playerList[id].runs+=temp;
    }
}

void sortPlayerAndDisplay(Player* playerList,int count,int choice,int asc){
    //create copy
    Player copy[count];
    for(int i=0;i<count;i++){
        copy[i]=playerList[i];
    }
    for(int i=0;i<count-1;i++){
        for(int j=i+1;j<count;j++){
            if(choice==1 && copy[i].runs>copy[j].runs){
                Player temp=copy[i];
                copy[i]=copy[j];
                copy[j]=temp;
            }
            else if(choice==2 && copy[i].wkt>copy[j].wkt){
                Player temp=copy[i];
                copy[i]=copy[j];
                copy[j]=temp;
            }
        }

    }

    if(asc){
        for(int i=0;i<count;i++){
            printf("\nPlayer Id:%d\n",copy[i].playerId);
            printf("Name: %s\n", copy[i].name);
            printf("Jersey Number: %d\n", copy[i].jno);
            printf("Matches Played: %d\n", copy[i].matchPlayed);
            printf("Wicket Taken: %d\n", copy[i].wkt);
            printf("Run Scored: %d\n\n",copy[i].runs);
        }
    }
    else{
        for(int i=count-1;i>=0;i--){
            printf("\nPlayer Id:%d\n",copy[i].playerId);
            printf("Name: %s\n", copy[i].name);
            printf("Jersey Number: %d\n", copy[i].jno);
            printf("Matches Played: %d\n", copy[i].matchPlayed);
            printf("Wicket Taken: %d\n", copy[i].wkt);
            printf("Run Scored: %d\n\n", copy[i].runs);
        }
    }
}

void displayPlayerSorted(Player* playerList,int* playerCount){
    int count=*playerCount;
    int choice;
    printf("Display Player By:\n");
    printf("1->Runs\n");
    printf("2->wickets\n");
    printf("enter your choice:");
    scanf("%d",&choice);

    int asc;
    printf("Enter 1 for Display in Ascending And 0 for Decending:");
    scanf("%d",&asc);

    sortPlayerAndDisplay(playerList,count,choice,asc);
    
}
