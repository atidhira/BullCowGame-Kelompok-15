#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#define MAX_LIMIT 1000

int GameMenu();
void GamePlay();
void GameRules();
void BackToMenu();
void GetHiddenWord(int GameLevel, char* str);
int GetMaxTry(int GameLevel);
void PrintBullsAndCows(char HiddenWord[MAX_LIMIT], char GuessWord[MAX_LIMIT]);
bool CheckGuessValidity(char Guess[MAX_LIMIT], char HWord[MAX_LIMIT], int HWLength);
bool isIsogram(char Guess[MAX_LIMIT]);
bool isGameWon(char HiddenWord[MAX_LIMIT], char GuessWord[MAX_LIMIT]);
bool CheckInputIsInteger(char inpString[MAX_LIMIT]);
bool TryAgain();

//------------------------------------------------------------------------------------
int main()
{
    int Menu;
    do {
        system("cls");
        Menu = GameMenu();
        switch(Menu) {
            case 1:
                GamePlay();
                break;
            case 2:
                GameRules();
                break;
            case 3:
                printf("\nSee you!!!\n\n");
                break;
        }
    } while(Menu != 3);
    return 0;
}
//------------------------------------------------------------------------------------
int GameMenu() {
    printf("\nSelamat datang di Bulls and Cows Game!!!\n");
    printf("MENU :\n");
    printf("1. Play\n");
    printf("2. Rules\n");
    printf("3. Exit\n");
    char sMenu[MAX_LIMIT];
    int iMenu;
    bool bMenu;
    do {
        do {
            printf("\nPilih menu : ");
            fgets(sMenu, MAX_LIMIT, stdin);
            int size = strlen(sMenu);
            sMenu[size-1]='\0';
        } while(CheckInputIsInteger(sMenu));
        iMenu = atoi(sMenu);
        if(iMenu < 1 || iMenu > 3) {
            printf("Tolong pilih menu yang tersedia\n");
            bMenu = false;
        } else { bMenu = true;}
    } while(!bMenu);
    return iMenu;
}

void GamePlay() {
    char HiddenWord[MAX_LIMIT];
    char GuessWord[MAX_LIMIT];
    int GameLevel = 1;
    bool isGameLevelWon = true;
    // mulai looping level
    while(GameLevel <= 3 && isGameLevelWon) {
        int MaxTry = GetMaxTry(GameLevel);
        GetHiddenWord(GameLevel, HiddenWord);
        int HiddenWordLength = strlen(HiddenWord);

        system("cls");
        printf("GAME LEVEL = %i\n", GameLevel);
        printf("Bisakah kamu menebak %i huruf isogram yang aku pikirkan?\n", HiddenWordLength);
        // looping user memasukkan tebakan
        int CurrentTry;
        for(CurrentTry = 1; CurrentTry <= MaxTry + 1; CurrentTry++) {
            // jika current try melebihi max try maka permainan berakhir (LOSE)
            if(CurrentTry == MaxTry + 1) {
                printf("\nSayang sekali kamu kalah\n");
                isGameLevelWon = false;
                break;
            }
            // user memasukkan kata tebakan
            do {
                printf("\nPercobaan %i dari %i\n", CurrentTry, MaxTry);
                printf("Tebakanmu : ");
                fgets(GuessWord, MAX_LIMIT, stdin);
                int size = strlen(GuessWord);
                GuessWord[size-1]='\0';
                strlwr(GuessWord);
            } while(!CheckGuessValidity(GuessWord, HiddenWord, HiddenWordLength));
            // jika guess merupakan exit key
            if(strcmp(GuessWord, "-exit") == 0) {
                printf("\nGOOD BYE\n");
                isGameLevelWon = false;
                break;
            } else {
                // Mengecek berapa banyak bulls dan cows dari tebakan valid user
                PrintBullsAndCows(HiddenWord, GuessWord);
            }
            // Jika tebakan benar, masuk ke level selanjutnya
            if(isGameWon(HiddenWord, GuessWord)) {
                GameLevel++;
                isGameLevelWon = true;
                break;
            }
        }
    }
    if(isGameLevelWon) {
        printf("SELAMAT!!!\n");
        printf("Kamu melalui semua level\n");
    } else {
        printf("Semoga beruntung di lain hari\n");
    }
    BackToMenu();
}

void GetHiddenWord(int GameLevel, char* str) {
    srand(time(NULL));
    char hiddenWord1[5][MAX_LIMIT] = {"air", "eat", "ice", "red", "toy"};
    char hiddenWord2[5][MAX_LIMIT] = {"near", "love", "life", "rest", "rope"};
    char hiddenWord3[5][MAX_LIMIT] = {"plane", "stone", "crown", "smoke", "wrath"};
    int randomIndex = (rand() % 5);
    switch(GameLevel) {
        case 1:
            strcpy(str, hiddenWord1[randomIndex]);
            break;
        case 2:
            strcpy(str, hiddenWord2[randomIndex]);
            break;
        case 3:
            strcpy(str, hiddenWord3[randomIndex]);
            break;
    }
}

int GetMaxTry(int GameLevel) {
    int MaxTry;
     switch(GameLevel) {
        case 1:
            MaxTry = 5;
            break;
        case 2:
            MaxTry = 6;
            break;
        case 3:
            MaxTry = 7;
            break;
    }
    return MaxTry;
}

void PrintBullsAndCows(char HiddenWord[MAX_LIMIT], char GuessWord[MAX_LIMIT]) {
    int bullscount = 0;
    int cowscount = 0;
    int length = strlen(HiddenWord);
    int GIndex, HWIndex;
    for(GIndex = 0; GIndex < length; GIndex++) {
        for(HWIndex = 0; HWIndex < length; HWIndex++) {
            if(GuessWord[GIndex] == HiddenWord[GIndex]) {
                bullscount++;
                break;
            } else if(GuessWord[GIndex] == HiddenWord[HWIndex]) {
                cowscount++;
            }
        }
    }
    printf("BULLS : %i   COWS : %i\n", bullscount, cowscount);
}

void GameRules() {
    system("cls");
    printf("Game Rules :\n");
    printf("1. Kata tebakan merupakan isogram yg berasal dari bahasa inggris\n");
    printf("2. Tebakan boleh dalam huruf kecil / besar\n");
    printf("3. Tidak boleh ada huruf yg berulang\n");
    printf("4. Bulls = Huruf benar, posisi benar\n");
    printf("5. Cows  = Huruf benar, posisi salah\n\n");
    BackToMenu();
}

bool CheckGuessValidity(char Guess[MAX_LIMIT], char HWord[MAX_LIMIT], int HWLength) {
    if(strcmp(Guess, "-help") == 0) {
        printf("Panjang kata = %i \n", HWLength);
        printf("Bulls = Huruf benar, posisi benar\n");
        printf("Cows  = Huruf benar, posisi salah\n");
        return false;
    } else if(strcmp(Guess, "-exit") == 0) {
        return true;
    } else if(strcmp(Guess, "-hint") == 0) {
        printf("Kata yang aku pikirkan : %s\n", HWord);
        return false;
    } else if(strlen(Guess) != HWLength) {
        printf("ERROR : Tolong masukkan %i huruf kata\n", HWLength);
        return false;
    } else if(!isIsogram(Guess)){
        printf("ERROR : Tebakanmu mengandung huruf yang diulang\n");
        return false;
    } else {
        return true;
    }
}

bool isIsogram(char Guess[MAX_LIMIT]) {
    int GLength = strlen(Guess);
    int index;
    for(index = 0; index < GLength; index++) {
    	int index2;
        for(index2 = index + 1; index2 < GLength; index2++) {
            if(Guess[index] == Guess[index2]) {
                return false;
            }
        }
    }
    return true;
}

bool isGameWon(char HiddenWord[MAX_LIMIT], char GuessWord[MAX_LIMIT]) {
    if(strcmp(HiddenWord, GuessWord) == 0) {
        char respons[MAX_LIMIT];
        bool bRespons;
        printf("YOU WIN!!!\n");
        do {
            printf("SIAP UNTUK LEVEL BERIKUTNYA (Y)? ");
            fgets(respons, MAX_LIMIT, stdin);
            if(respons[0] == 'y' || respons[0] == 'Y') {
                bRespons = true;
            } else {
                bRespons = false;
            }
        } while(!bRespons);
        return true;
    } else {
        return false;
    }
}

bool CheckInputIsInteger(char inpStr[MAX_LIMIT]) {
	int count;
    for(count = 0; count < strlen(inpStr); count++) {
        if(inpStr[count] != '0' && inpStr[count] != '1' &&
           inpStr[count] != '2' && inpStr[count] != '3' &&
           inpStr[count] != '4' && inpStr[count] != '5' &&
           inpStr[count] != '6' && inpStr[count] != '7' &&
           inpStr[count] != '8' && inpStr[count] != '9') {
            printf("ERROR : Tolong hanya masukkan angka\n");
            return true;
        }
    }
    return false;
}

void BackToMenu() {
    char respons[MAX_LIMIT];
    bool bRespons;
    do {
        printf("Kembali ke menu (Y)? ");
        fgets(respons, MAX_LIMIT, stdin);
        if(respons[0] == 'y' || respons[0] == 'Y') {
            bRespons = true;
        } else {
            bRespons = false;
        }
    } while(!bRespons);
}
