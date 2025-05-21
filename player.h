#ifndef PLAYER_H
#define PLAYER_H

#define Max_Player 1000
#define Max_Len 100

typedef struct {
    char country[Max_Len];
    char name[Max_Len];
    char club[Max_Len];
    char league[Max_Len];
    char position[Max_Len];
    int matches_played;
    int goals;
    int assists;
    int minutes_played;
    float xG;
    float ratings; // Ensure this is a float
} Player;

int loadPlayerFromCSV(const char *filename, Player players[], int *count);
void printPlayerData(Player players[], int count);
void searchPlayers(Player players[], int count);
void filterPlayers(Player players[], int count);
void sortFunction(Player players[], int count);
void viewPlayers(Player players[], int count);
void addPlayer(const char *filename, Player players[], int *count);
void deletePlayer(const char *filename, Player players[], int *count);
void updatePlayer(const char *filename, Player players[], int *count);
#endif // PLAYER_H