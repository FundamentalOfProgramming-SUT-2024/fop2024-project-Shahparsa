#include<ncurses.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<locale.h>
#include<unistd.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>

//403110506
//Mohammadparsa Shahmohammadi

typedef struct
{
    int x;
    int y;
} Pos;

typedef struct 
{
    char Mail[50];
    char Name[50];
    char Pass[50];
    int score;
    int gold;
    int tedad;//tedad bazi movafagh
    int HP;
    int diff;
    int color;
    int aslahe[5];
    int Dast;
    int tedadfood;
    int food[5];
    int food_time[5];
    int telesm[3];
    int Hunger;
    int Speed;
    int Strengh;
    int reg;
    int floor;
    Pos pos;
} Profile;

int otagh1 , otagh2 , otagh3 , otagh4 , otagh5;
int M;
int Dast = -1;
int Sword = 1;
Mix_Music *music = NULL;
int musicalan = 0;
int load = 0;

// COLS = 184 LINES = 45

char floor1[45][184];
int list1[100][5];
int didan1[45][184];
int value1[45][184];
int ghaza1[45][184];
char floor2[45][184];
int list2[100][5];
int didan2[45][184];
int value2[45][184];
int ghaza2[45][184];
char floor3[45][184];
int list3[100][5];
int didan3[45][184];
int value3[45][184];
int ghaza3[45][184];
char floor4[45][184];
int list4[100][5];
int didan4[45][184];
int value4[45][184];
int ghaza4[45][184];
char floor5[45][184];
int list5[100][5];
int didan5[45][184];
int value5[45][184];
int ghaza5[45][184];

int oftadeh1[45][184];
int oftadeh2[45][184];
int oftadeh3[45][184];
int oftadeh4[45][184];
int oftadeh5[45][184];

int joon1[45][184];
int joon2[45][184];
int joon3[45][184];
int joon4[45][184];
int joon5[45][184];

int donbal1[45][184];
int donbal2[45][184];
int donbal3[45][184];
int donbal4[45][184];
int donbal5[45][184];

int x1;
int y_1;
int x2;
int y_2;
int x3;
int y_3;
int x4;
int y_4;
int x5;
int y_5;

int bardashtan = 0;

time_t now , past_hunger , past_food , past_monster , past_enchant , past_heal;

void menu2(Profile *pl);
void user_menu(Profile *pl);
void play(Profile *pl);
void play2(Profile *pl);
int tabaghe_saz(Profile *pl , int list2[100][5] , int didan[LINES][COLS] , int value[LINES][COLS] , char bazi[LINES][COLS] , int vaz , Pos * noghte , int ghaza[LINES][COLS] , int joon[LINES][COLS] , int oftadeh[LINES][COLS]);
void Setting(Profile *pl);
void Aslahe(int otagh , int list[otagh][5] , char bazi[LINES][COLS] , int didan[LINES][COLS] , int oftadeh[LINES][COLS]);
void food(int otagh , int list[otagh][5] , char bazi[LINES][COLS] , int didan[LINES][COLS] , int ghaza[LINES][COLS]);
void monster(int otagh , int list[otagh][5] , char bazi[LINES][COLS] , int didan[LINES][COLS] , int joon[LINES][COLS] , Profile *pl);
void telesm(int otagh , int list[otagh][5] , char bazi[LINES][COLS] , int didan[LINES][COLS] , Profile *pl);

void board(){
    for (int x = 0; x < COLS; x++){
        mvprintw(0, x, "$");
        mvprintw(LINES - 1, x, "$");
    }
    for (int y = 0; y < LINES; y++){
        mvprintw(y, 0, "$");
        mvprintw(y, COLS - 1, "$");
    }
}

void rogue(){
    int z = COLS/2-10;
    mvprintw(11 , z , "ROGUE");
}

void menu(){
    board();
    rogue();
    int z = COLS/2 - 20;
    mvprintw(13 , z , "Press any key to continue...");
    getch();
}

int check_mail(char* Mail){
    int y = 0;
    int u = strlen(Mail);
    for(int i = 0 ; i < u ; i++){
        if(y == 0 && Mail[i] != '@'){y = 1;}
        else if(y == 1 && Mail[i] ==  '@'){y = 2;}
        else if(y == 2 && Mail[i] != '.'){y = 3;}
        else if(y == 3 && Mail[i] == '.'){y = 4;}
        else if(y == 4 && Mail[i] != '\n'){y = 5;}
    }
    return y;   
}

int check_pass(char * pass){
    int u = strlen(pass);
    int num = 0;
    int koochak = 0;
    int bozorg = 0;
    for(int i = 0 ; i < u ; i++){
        if(pass[i] >= '0' && pass[i] <= '9'){num = 1;}
        if(pass[i] >= 'a' && pass[i] <= 'z'){koochak = 1;}
        if(pass[i] >= 'A' && pass[i] <= 'Z'){bozorg = 1;}
    }
    int sum = num + koochak + bozorg;
    return sum;   
}

void ramz_tasadofy(char * pass){
    int u = rand() % 12;
    u += 7;
    int o = 0;
    int z;
    while(o < 3){
        for(int i = 0 ; i < u ; i++){
            z = rand() % 62;
            if(z >= 0 && z <= 25){
                pass[i] = z + 65;
            }else if(z >= 26 && z <= 51){
                pass[i] = z + 71;
            }else if(z >= 52 && z <= 61){
                pass[i] = z - 4;
            }
        }
        pass[u] = '\0';
        o = check_pass(pass);
    }
}

void pakkon(int y , int x , int tedad){
    for(int i = 0 ; i < tedad ; i++){
        mvprintw(y , x+i , " ");    
    }
}

int checkme(char * name){    
    FILE *ptr;
    ptr = fopen("Usernames.txt" , "r");
    char c[50];
    while(fgets(c , 50 , ptr) != NULL){
        int u = strlen(c);
        c[u-1] = '\0';
        if(!strcmp(name , c)){
            return 1;
        }
    }
    return 0;
}

int checkpass(char * pass , char * file){
    FILE *ptr;
    char copy[50];
    strcpy(copy , file);
    strcat(copy , ".txt");
    ptr = fopen(copy , "r");
    char c[50];
    fgets(c , 50 , ptr);
    fgets(c , 50 , ptr);
    int u = strlen(c);
    c[u-1] = '\0';
    if(!strcmp(pass , c)){
        return 1;
    }
    return 0;
}

int checkmail(char * mail , char * file){
    FILE *ptr;
    char copy[50];
    strcpy(copy , file);
    strcat(copy , ".txt");
    ptr = fopen(copy , "r");
    char c[50];
    fgets(c , 50 , ptr);
    int u = strlen(c);
    c[u-1] = '\0';
    if(!strcmp(mail , c)){
        return 1;
    }
    return 0;
}

void addme(char * name){
    FILE *ptr;
    FILE *temp;
    char c[50];
    ptr = fopen("Usernames.txt" , "r");
    temp = fopen("temp.txt" , "w");
    while(fgets( c , 50 , ptr) != NULL){
        fprintf(temp , "%s" , c);
    }
    fprintf(temp , "%s\n" , name);
    fclose(temp);
    remove("Usernames.txt");
    rename("temp.txt" , "Usernames.txt");
}

void New_player(Profile *pl){
    clear();
    board();
    int z = COLS/2-10;
    curs_set(true);
    init_pair(1 , COLOR_RED , COLOR_BLACK);
    init_pair(2 , COLOR_GREEN , COLOR_BLACK);
    mvprintw(2 , z , "Welcome to Rogue game!!!");
    mvprintw(3 , z , "Please give us information:   :)");
    mvprintw(4 , z , "Your name: ");
    move(5 , z);
    char name[50];
    getnstr(name , 50);
    while(checkme(name)){
        pakkon(5 , z , 50);
        attron(COLOR_PAIR(1));
        mvprintw(4 , z , "Your name: (Try another name)");
        attroff(COLOR_PAIR(1));
        move(5 , z);
        getnstr(name , 50);
    }
    attron(COLOR_PAIR(2));
    mvprintw(4 , z ,"Your name:                           " );
    attroff(COLOR_PAIR(2));
    strcpy(pl->Name , name);
    char tmp[50] = "Usernames";
    addme(name); 
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    mvprintw(6 , z , "Your mail: ");
    move(7 , z);
    char Mail[50];
    getnstr(Mail , 50);
    int y = check_mail(Mail);
    while(y < 5){
        pakkon(7 , z , 50);
        attron(COLOR_PAIR(1));  
        mvprintw(6 , z ,"Your mail was wrong (Try Again): " );
        attroff(COLOR_PAIR(1));
        move(7 , z);
        getnstr(Mail , 50);
        y = check_mail(Mail);
    }
    attron(COLOR_PAIR(2));
    mvprintw(6 , z ,"Your mail :                               " );
    attroff(COLOR_PAIR(2));
    strcpy(pl->Mail , Mail);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    mvprintw(8 , z , "Password : (If you need help type (Help!)");
    move(9 , z);
    char pass[50];
    getnstr(pass , 50);
    if(!strcmp(pass , "Help!")){
        char passjad[50]; 
        ramz_tasadofy(passjad);
        mvprintw(10 , z , "Random Password : %s" , passjad);
    }
    int sum = check_pass(pass);
    int u = strlen(pass);
    if(sum < 3){u = 0;}
    while(u < 7){
        pakkon(9 , z , 50);
        attron(COLOR_PAIR(1));  
        mvprintw(8 , z ,"Password was wrong: (If you need help type (Help!)" );
        attroff(COLOR_PAIR(1));
        move(9 , z);
        getnstr(pass , 50);
        if(!strcmp(pass , "Help!")){
            char passjad[50];
            ramz_tasadofy(passjad);
            mvprintw(10 , z , "Random Password : %s" , passjad);
        }
        sum = check_pass(pass);
        u = strlen(pass);
        if(sum < 3){u = 0;}
    }
    strcpy(pl->Pass , pass);
    pakkon(10 , z  ,50);
    attron(COLOR_PAIR(2));
    mvprintw(8 , z , "Password : (If you need help type (Help!)                                   ");
    attroff(COLOR_PAIR(2));

    mvprintw(11 , z , "Your profile has been created successfully.");
    mvprintw(12 , z , "Profile information:");
    mvprintw(13 , z , "Profile name : %s" , pl->Name);
    mvprintw(14 , z , "Profile mail : %s" , pl->Mail);
    mvprintw(15 , z , "Profile password : %s" , pl->Pass);
    char esm[50];
    strcpy(esm , name);
    strcat(esm , ".txt");
    FILE *ptr;
    ptr = fopen(esm , "w");
    pl->score = 0;
    pl->gold = 0;
    pl->tedad = 0;
    fprintf(ptr , "%s\n" , pl->Mail);
    fprintf(ptr , "%s\n" , pl->Pass);
    fprintf(ptr , "%d\n" , pl->score);
    fprintf(ptr , "%d\n" , pl->gold);
    fprintf(ptr , "%d\n" , pl->tedad);
    fclose(ptr);
    mvprintw(16 , z , "Press any key to continue...");
    curs_set(false);
    getch();
}

void Sign_in(Profile *pl){
    clear();
    board();
    int z = COLS/2-10;
    curs_set(true);
    init_pair(1 , COLOR_RED , COLOR_BLACK);
    init_pair(2 , COLOR_GREEN , COLOR_BLACK);
    mvprintw(2 , z , "Welcome back LEGEND!!!");
    mvprintw(3 , z , "Please give us information:   :)");
    mvprintw(4 , z , "Your name: ");
    move(5 , z);
    char name[50];
    getnstr(name , 50);
    while(!checkme(name)){
        pakkon(5 , z , 50);
        attron(COLOR_PAIR(1));
        mvprintw(4 , z , "Your name: (Wrong Name)");
        attroff(COLOR_PAIR(1));
        move(5 , z);
        getnstr(name , 50);
    }
    attron(COLOR_PAIR(2));
    mvprintw(4 , z ,"Your name:                           " );
    attroff(COLOR_PAIR(2));
    strcpy(pl->Name , name);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    mvprintw(6 , z , "Password : (If you need help type (Help!)");
    move(7 , z);
    char pass[50];
    getnstr(pass , 50);
    if(!strcmp(pass , "Help!")){
        pakkon(7 , z , 50);
        mvprintw(10 , z , "Give us your mail: ");
        move(11 , z);
        char Mail[50];
        getstr(Mail);
        while(!checkmail(Mail , name)){
            pakkon(11 , z , 50);
            attron(COLOR_PAIR(1));
            mvprintw(10 , z , "Your mail is wrong :( (Try again) : ");
            attroff(COLOR_PAIR(1));
            move(11 , z);
            getstr(Mail);
        }
        attron(COLOR_PAIR(2));
        mvprintw(10 , z , "Give us your mail:                                        ");
        attroff(COLOR_PAIR(2));
        char passpeida[50];
        char copy[50];
        strcpy(copy , name);
        strcat(copy , ".txt");
        FILE *ptr;
        ptr = fopen (copy , "r");
        fgets(passpeida , 50 , ptr);
        fgets(passpeida , 50 , ptr);
        int u = strlen(passpeida);
        passpeida[u-1] = '\0';
        mvprintw(12 , z , "Your password : %s" , passpeida);
    }
    while(!checkpass(pass , name)){
        pakkon(7 , z , 50);
        attron(COLOR_PAIR(1));  
        mvprintw(6 , z ,"Password was wrong: (If you need help type (Help!)" );
        attroff(COLOR_PAIR(1));
        move(7 , z);
        getnstr(pass , 50);
        if(!strcmp(pass , "Help!")){
            pakkon(7 , z , 50);
        pakkon(10 , z , 50);
        pakkon(11 , z , 50);
        pakkon(12 , z , 50);
            mvprintw(10 , z , "Give us your mail: ");
            move(11 , z);
            char Mail[50];
            getstr(Mail);
            while(!checkmail(Mail , name)){
                pakkon(11 , z , 50);
                attron(COLOR_PAIR(1));
                mvprintw(10 , z , "Your mail is wrong :( (Try again) : ");
                attroff(COLOR_PAIR(1));
                move(11 , z);
                getstr(Mail);
            }
            attron(COLOR_PAIR(2));
            mvprintw(10 , z , "Give us your mail:                                        ");
            attroff(COLOR_PAIR(2));
            char passpeida[50];
            char copy[50];
            strcpy(copy , name);
            strcat(copy , ".txt");
            FILE *ptr;
            ptr = fopen (copy , "r");
            fgets(passpeida , 50 , ptr);
            fgets(passpeida , 50 , ptr);
            int u = strlen(passpeida);
            passpeida[u-1] = '\0';
            mvprintw(12 , z , "Your password : %s" , passpeida);
        }
    }
    strcpy(pl->Pass , pass);
    pakkon(10 , z , 50);
    pakkon(11 , z , 50);
    pakkon(12 , z , 50);
    attron(COLOR_PAIR(2));
    mvprintw(6 , z , "Password : (If you need help type (Help!)                                   ");
    attroff(COLOR_PAIR(2));

    FILE *ptr;
    char copy[50];
    strcpy(copy , name);
    strcat(copy , ".txt");
    ptr = fopen(copy , "r");
    char c[50];
    fgets(c , 50 , ptr);
    int u = strlen(c);
    c[u-1] = '\0';
    strcpy(pl->Mail , c);
    fgets(c , 50 , ptr);
    fgets(c , 50 , ptr);
    int tool = strlen(c);
    tool--;
    int sum = 0;
    for(int i = 0 ; i < tool ; i++){
        sum += c[i] - '0';
        sum*=10;
    }
    sum /= 10;
    pl->score = sum;

    fgets(c , 50 , ptr);
    tool = strlen(c);
    tool--;
    sum = 0;
    for(int i = 0 ; i < tool ; i++){
        sum += c[i] - '0';
        sum*=10;
    }
    sum /= 10;
    pl->gold = sum;
    fgets(c , 50 , ptr);
    tool = strlen(c);
    tool--;
    sum = 0;
    for(int i = 0 ; i < tool ; i++){
        sum += c[i] - '0';
        sum*=10;
    }
    sum /= 10;
    pl->tedad = sum;
    mvprintw(10 , z , "Welcome back %s!!" , name);
    mvprintw(11 , z , "Press any key to continue...");
    curs_set(false);
    getch();
}

void profile_neshoon(Profile *pl){
    clear();
    board();
    int z = COLS/2;
    mvprintw(13 , z-10 , "Your profile :");
    mvprintw(15 , z-10 , "Account's name : %s" , pl->Name);
    mvprintw(17 , z-10 , "Account's mail : %s" , pl->Mail);
    mvprintw(19 , z-10 , "Account's pass : %s" , pl->Pass);
    mvprintw(21 , z-10 , "Account's score : %d" , pl->score);
    mvprintw(23 , z-10 , "Account's gold : %d" , pl->gold);
    mvprintw(25 , z-10 , "Account's games : %d" , pl->tedad);
    mvprintw(27 , z-10 , "Press any key to continue...");
    getch();
    menu2(pl);
}

int leadsaz(char leaderboard[100][50]){
    FILE *ptr;
    ptr = fopen("Usernames.txt" , "r");
    char c [50];
    int o = 0;
    while (fgets(c , 50 , ptr) != NULL){
        int u = strlen (c);
        c[u-1] = '\0';
        char copy[50];
        strcpy(copy , c);
        strcat(copy , ".txt");
        FILE *po;
        po = fopen(copy , "r");
        char score[50];
        fgets(score , 50 , po);
        fgets(score , 50 , po);
        fgets(score , 50 , po);
        strcpy(leaderboard[o] , c);
        o++;
        strcpy(leaderboard[o] , score);
        o++;
    }
    return o;
}

void leadchap(int i , char leaderboard2[100][50] , int o , Profile *pl){
    clear();
    board();
    init_pair(1 , COLOR_CYAN , COLOR_BLACK);
    init_pair(2 , COLOR_YELLOW , COLOR_BLACK);
    int z = COLS/2;
    mvprintw(13 , z-40 , "Leaderboard :");
    mvprintw(13 , z-10 , "Score:");
    mvprintw(13 , z , "Gold:");
    mvprintw(13 , z+10 , "Games:");
    int j = 2*i;
    int k = 0;
    int tedad = i;
    while(j < 2*i+10){
        if(j > o-1){
            break;
        }
        char c[50];
        char copy[50];
        strcpy(c , leaderboard2[j]);
        strcpy(copy , leaderboard2[j]);
        strcat(copy , ".txt");
        FILE *po;
        char score[50];
        char gold[50];
        po = fopen(copy , "r");
        fgets(score , 50 , po);
        fgets(score , 50 , po);
        fgets(score , 50 , po);
        fgets(score , 50 , po);
        strcpy(gold , score);
        fgets(score , 50 , po);
        if(j == 0 || j == 2 || j == 4){
            if(j == 0){
                mvprintw(15+k , z - 45 , "🥇");
            }else if(j == 2){
                mvprintw(15+k , z - 45 , "🥈");
            }else if(j == 4){
                mvprintw(15+k , z - 45 , "🥉");
            }
            attron(COLOR_PAIR(2));
            attron(A_UNDERLINE);
            mvprintw(15+k , z -42 , "%d" , tedad+1);
            mvprintw(15+k , z-40 , "%s (The GOAT)" , leaderboard2[j]);
            mvprintw(15+k , z -10 , "%s" , leaderboard2[j+1]);
            mvprintw(15+k , z , "%s" , gold);
            mvprintw(15+k , z +10 , "%s" , score);
            attroff(COLOR_PAIR(2));
            attroff(A_UNDERLINE);
        }else{
            mvprintw(15+k , z -42 , "%d" , tedad+1);
            mvprintw(15+k , z-40 , "%s" , leaderboard2[j]);
            mvprintw(15+k , z -10 , "%s" , leaderboard2[j+1]);
            mvprintw(15+k , z , "%s" , gold);
            mvprintw(15+k , z +10 , "%s" , score);
        }
        if(!strcmp(c , pl->Name)){
            attron(COLOR_PAIR(1));
            mvprintw(15+k , z -42 , "%d" , tedad+1);
            mvprintw(15+k , z-40 , "%s" , leaderboard2[j]);
            mvprintw(15+k , z -10 , "%s" , leaderboard2[j+1]);
            mvprintw(15+k , z , "%s" , gold);
            mvprintw(15+k , z +10 , "%s" , score);
            attroff(COLOR_PAIR(1));
        }
        k += 2;
        j += 2;
        tedad++;
        board();
    }
}

void sortkon(char lead[100][50] , char leadjad[100][50] , int o){
    int tedad= o/2;
    int jad[tedad];
    for(int i = 0 ; i < tedad ; i++){
        char addad[50];
        int l = i*2;
        strcpy(addad ,lead[l+1]);
        int tool = strlen(addad);
        tool--;
        int sum = 0;
        for(int p = 0 ; p < tool ;p++){
            sum += addad[p] - '0';
            sum*=10;
        }
        sum /= 10;
        jad[i] = sum;
    }
    int estefade[tedad];
    int list[tedad];
    for(int y = 0 ; y < tedad ; y++){estefade[y] = 0;}
    for(int j = 0 ; j < tedad ; j++){
        int u = -1;
        for(int i = 0 ; i < tedad ; i++){
            if(estefade[i] == 0){
                if(u == -1){ u = i;}
            if(jad[i] > jad[u]){u=i;}
            }  
        }
      list[j] = u;
      estefade[u] = 1;
   }
   for(int r = 0 ; r < tedad ; r++){
    int alan = list[r];
    alan *= 2;
    int w = r*2;
    strcpy(leadjad[w] , lead[alan]);
    strcpy(leadjad[w+1] , lead[alan+1]);
   }   
}

void Leaderboard(Profile *pl){
    clear();
    board();
    int z = COLS/2;
    char leaderboard[100][50];
    char leaderboard2[100][50];
    int tedad = leadsaz(leaderboard);
    sortkon(leaderboard , leaderboard2 , tedad);
    int vagh = tedad/2;
    int i = 0;
    leadchap(i , leaderboard2 , tedad , pl);
    while(1){
        int ch = getch();
        if(ch == KEY_UP){
            if(i < vagh-5){
                i++;
            }
        }else if(ch == KEY_DOWN){
            if(i > 0){
                i--;
            }
        }else{
            break;
        }
        leadchap(i , leaderboard2 , tedad , pl);
    }
    mvprintw(25 , z-10 , "Press any key to continue...");
    getch();
    menu2(pl);
}

void user_menu(Profile *pl){
    clear();
    board();
    int z = COLS/2;
    mvprintw(13, z-10, "Which one?");
    int vaz = 0;
    char *choice[] = {"New Player" , "Old Player" , "Guest"};
    while (1){
        for (int i = 0; i < 3; i++){
            if (vaz == i){
                attron(A_REVERSE);
            }
            mvprintw(15 + 2*i, z - 10, "%s", choice[i]);
            if (vaz == i){
                attroff(A_REVERSE);
            }
        }

        int ch = getch();
        if (ch == KEY_UP){
            if(vaz != 0){
                vaz --;
            }
        }else if(ch == KEY_DOWN){
            if(vaz != 2){
                vaz++;
            }
        }else if (ch == '\n'){
            break;
        }
    }
    if(vaz == 0){//New Player
        New_player( pl);
    }else if(vaz == 1){//Old PLayer
        Sign_in(pl);
    }else{//Guest
        strcpy(pl->Name , "???");
        strcpy(pl->Mail , "???");
        strcpy(pl->Pass , "???");
        pl->score = 0;
        pl->gold = 0;
        pl->tedad = 0;
    }
    menu2(pl);
}

int Otaghsaz(int otagh , int list[otagh][5] , int vaz , Pos * noghte){
    for(int i = 0 ; i < otagh ; i++){
        int x = rand()%(COLS-33);
        x += 10;
        int y = rand()%(LINES-33);
        y += 10;
        int tool = rand()%7;
        tool += 6;
        int arz = rand()%7;
        arz += 6;
        if(i == 0 && vaz != 0){
            x = noghte->x - 2;
            y = noghte->y - 2;
        }
        if(x + tool > COLS - 6){
            return 0;
        }
        if(y + arz > LINES - 6){
            return 0;
        }
        for(int j = 0 ; j < i ; j++){
            int f = x - list[j][0];
            int l = y - list[j][1];
            if(f > 0){
                if(l > 0){
                    if(f <= list[j][2] && l <= list[j][3]){
                        return 0;
                    }
                }else if(l == 0){
                    if(f <= list[j][2]){
                        return 0;
                    }
                }else if(l < 0){
                    l *= -1;
                    if(f <= list[j][2] && l <= arz){
                        return 0;
                    }
                }
            }else if(f == 0){
                if(l > 0){
                    if(l <= list[j][3]){
                        return 0;
                    }
                }else if(l == 0){
                    return 0;
                }else if(l < 0){
                    l *= -1;
                    if(l <= arz){
                        return 0;
                    }
                }
            }else if(f < 0){
                f *= -1;
                if(l > 0){
                    if(f <= tool && l <= list[j][3]){
                        return 0;
                    }
                }else if(l == 0){
                    if(f <= tool){
                        return 0;
                    }
                }else if(l < 0){
                    l *= -1;
                    if(f <= tool && l <= arz){
                        return 0;
                    }
                }
            }
        }
        list[i][0] = x;
        list[i][1] = y;
        list[i][2] = tool;
        list[i][3] = arz;
        int p = rand()%10;
        
        if(p < 6){//Regular room
            list[i][4] = 0;
        }else if(p == 6 || p == 7 || p == 10){//Nightmare room 
            list[i][4] = 1;
        }else if(p == 8 || p == 9){//Enchant room
            list[i][4] = 2;
        }
        if(vaz == 4 && i == otagh - 1){//Golden room
            list[i][4] = 3;
        }
    }
    return 1;
}

void masirsaz(int mabda , int maghsad , int otagh , int list[otagh][5] , char bazi[LINES][COLS]){
    int x_markaz1 = list[mabda][0] + (list[mabda][2]/2);
    int y_markaz1 = list[mabda][1] + (list[mabda][3]/2);
    int x_markaz2 = list[maghsad][0] + (list[maghsad][2]/2);
    int y_markaz2 = list[maghsad][1] + (list[maghsad][3]/2);
    int x_alan = x_markaz1;
    int y_alan = y_markaz1;
    if(x_markaz1 <= x_markaz2){
        if(y_markaz1 <= y_markaz2){
            //paein o rast
             while(1){
                int chance = rand()%2;
                if(chance == 0){//(x,y) --> (x+1,y)
                    if(x_alan == x_markaz2){
                        y_alan++;
                    }else{
                        x_alan++;
                    }
                    if(bazi[y_alan][x_alan] == '.'){

                    }else if(bazi[y_alan][x_alan] == '|' || bazi[y_alan][x_alan] == '_'){
                        bazi[y_alan][x_alan] = '+';
                    }else if(bazi[y_alan][x_alan] == ' '){
                        bazi[y_alan][x_alan] = '#';
                    }
                    if(x_alan == x_markaz2 && y_alan == y_markaz2){break;}
                }else if(chance == 1){//(x,y) --> (x,y+1)
                    if(y_alan == y_markaz2){
                        x_alan++;
                    }else{
                        y_alan++;
                    }
                    if(bazi[y_alan][x_alan] == '.'){

                    }else if(bazi[y_alan][x_alan] == '|' || bazi[y_alan][x_alan] == '_'){
                        bazi[y_alan][x_alan] = '+';
                    }else if(bazi[y_alan][x_alan] == ' '){
                        bazi[y_alan][x_alan] = '#';
                    }
                    if(x_alan == x_markaz2 && y_alan == y_markaz2){break;}
                }
            }
        }else{
            //bala o rast
              while(1){
                int chance = rand()%2;
                if(chance == 0){//(x,y) --> (x+1,y)
                    if(x_alan == x_markaz2){
                        y_alan++;
                    }else{
                        x_alan++;
                    }
                    if(bazi[y_alan][x_alan] == '.'){

                    }else if(bazi[y_alan][x_alan] == '|' || bazi[y_alan][x_alan] == '_'){
                        bazi[y_alan][x_alan] = '+';
                    }else if(bazi[y_alan][x_alan] == ' '){
                        bazi[y_alan][x_alan] = '#';
                    }
                    if(x_alan == x_markaz2 && y_alan == y_markaz2){break;}
                }else if(chance == 1){//(x,y) --> (x,y-1)
                    if(y_alan == y_markaz2){
                        x_alan++;
                    }else{
                        y_alan--;
                    }
                    if(bazi[y_alan][x_alan] == '.'){

                    }else if(bazi[y_alan][x_alan] == '|' || bazi[y_alan][x_alan] == '_'){
                        bazi[y_alan][x_alan] = '+';
                    }else if(bazi[y_alan][x_alan] == ' '){
                        bazi[y_alan][x_alan] = '#';
                    }
                    if(x_alan == x_markaz2 && y_alan == y_markaz2){break;}
                }
            }
        }
    }else{
        if(y_markaz1 <= y_markaz2){
            //paein o chap
              while(1){
                int chance = rand()%2;
                if(chance == 0){//(x,y) --> (x-1,y)
                    if(x_alan == x_markaz2){
                        y_alan++;
                    }else{
                        x_alan--;
                    }
                    if(bazi[y_alan][x_alan] == '.'){

                    }else if(bazi[y_alan][x_alan] == '|' || bazi[y_alan][x_alan] == '_'){
                        bazi[y_alan][x_alan] = '+';
                    }else if(bazi[y_alan][x_alan] == ' '){
                        bazi[y_alan][x_alan] = '#';
                    }
                    if(x_alan == x_markaz2 && y_alan == y_markaz2){break;}
                }else if(chance == 1){//(x,y) --> (x,y+1)
                    if(y_alan == y_markaz2){
                        x_alan--;
                    }else{
                        y_alan++;
                    }
                    if(bazi[y_alan][x_alan] == '.'){

                    }else if(bazi[y_alan][x_alan] == '|' || bazi[y_alan][x_alan] == '_'){
                        bazi[y_alan][x_alan] = '+';
                    }else if(bazi[y_alan][x_alan] == ' '){
                        bazi[y_alan][x_alan] = '#';
                    }
                    if(x_alan == x_markaz2 && y_alan == y_markaz2){break;}
                }
            }
        }else{
            //bala o chap
              while(1){
                int chance = rand()%2;
                if(chance == 0){//(x,y) --> (x-1,y)
                    if(x_alan == x_markaz2){
                        y_alan--;
                    }else{
                        x_alan--;
                    }
                    if(bazi[y_alan][x_alan] == '.'){

                    }else if(bazi[y_alan][x_alan] == '|' || bazi[y_alan][x_alan] == '_'){
                        bazi[y_alan][x_alan] = '+';
                    }else if(bazi[y_alan][x_alan] == ' '){
                        bazi[y_alan][x_alan] = '#';
                    }
                    if(x_alan == x_markaz2 && y_alan == y_markaz2){break;}
                }else if(chance == 1){//(x,y) --> (x,y-1)
                    if(y_alan == y_markaz2){
                        x_alan--;
                    }else{
                        y_alan--;
                    }
                    if(bazi[y_alan][x_alan] == '.'){

                    }else if(bazi[y_alan][x_alan] == '|' || bazi[y_alan][x_alan] == '_'){
                        bazi[y_alan][x_alan] = '+';
                    }else if(bazi[y_alan][x_alan] == ' '){
                        bazi[y_alan][x_alan] = '#';
                    }
                    if(x_alan == x_markaz2 && y_alan == y_markaz2){break;}
                }
            }
        }
    }
}

void otaghzakhire(int otagh , int list[otagh][5] , char bazi[LINES][COLS] , int didan[LINES][COLS] , Pos * noghte , int vaz){
    for(int i = 0 ; i < otagh ; i++){
        for(int y = list[i][1] ; y <= list[i][1] + list[i][3] ; y++){
            bazi[y][list[i][0]] = '|';
            bazi[y][list[i][0]+list[i][2]] = '|';
            if(i == 0){
                didan[y][list[i][0]] = 1;
                didan[y][list[i][0]+list[i][2]] = 1;
            }
        }
        for(int x = list[i][0] ; x <= list[i][0] + list[i][2] ; x++){
            bazi[list[i][1]][x] = '_';
            bazi[list[i][1] + list[i][3]][x] = '_';
            if(i == 0){
                didan[list[i][1]][x] = 1;
                didan[list[i][1] + list[i][3]][x] = 1;
            }
        }
        bazi[list[i][1] + list[i][3]][list[i][0]] = '|';
        bazi[list[i][1] + list[i][3]][list[i][0]+list[i][2]] = '|';
        for(int x = list[i][0] + 1  ; x < list[i][0] + list[i][2] ; x++){
            for(int y = list[i][1] + 1 ; y < list[i][1] + list[i][3] ; y++){
                if(y == noghte->y && x == noghte->x && vaz != 0){
                    bazi[y][x] = '}';
                }else{
                    bazi[y][x] = '.';
                }
                if(i == 0){
                    didan[y][x] = 1;
                }
            }
        }
    }
}

void chapgar(Profile *pl , char bazi[LINES][COLS] , int didan[LINES][COLS] , int x , int y , int otagh , int list[otagh][5] , int ghaza[LINES][COLS]){
    init_pair(1 , COLOR_GREEN , COLOR_BLACK);
    init_pair(2 , COLOR_CYAN , COLOR_BLACK);
    init_pair(3 , COLOR_YELLOW , COLOR_BLACK);
    init_pair(4 , COLOR_BLUE , COLOR_BLACK);
    init_pair(5 , COLOR_BLACK , COLOR_WHITE);
    init_pair(6 , COLOR_RED , COLOR_BLACK);
    init_pair(7 , COLOR_MAGENTA , COLOR_BLACK);
    for(int i = 0 ; i < LINES ; i++){
        for(int j = 0 ; j < COLS ; j++){
            if(didan[i][j] == 1 || M == 1){
                if(i == y && j == x){
                    if(pl->color == 1){
                        mvprintw(i , j , "@");
                    }else if (pl->color == 2){
                        attron(COLOR_PAIR(6));
                        mvprintw(i , j , "@");
                        attroff(COLOR_PAIR(6));
                    }else if(pl->color == 3){
                        attron(COLOR_PAIR(2));
                        mvprintw(i , j , "@");
                        attroff(COLOR_PAIR(2));
                    }
                }else{
                    if(bazi[i][j] == '|' || bazi[i][j] == '_' || bazi[i][j] == '+' || bazi[i][j] == 'O'){
                        attron(COLOR_PAIR(2));
                        mvprintw(i , j , "%c" , bazi[i][j]);
                        attroff(COLOR_PAIR(2));
                    }else if(bazi[i][j] == '#'){
                        attron(COLOR_PAIR(1));
                        mvprintw(i , j , "%c" , bazi[i][j]);
                        attroff(COLOR_PAIR(1));    
                    }else if(bazi[i][j] == 'T'){
                        mvprintw(i , j , ".");
                    }else if(bazi[i][j] == 'G'){
                        attron(COLOR_PAIR(3));
                        mvprintw(i , j , "⛂");
                        attroff(COLOR_PAIR(3));
                    }else if(bazi[i][j] == 'g'){
                        attron(COLOR_PAIR(3));
                        mvprintw(i , j , "%c" , bazi[i][j]);
                        attroff(COLOR_PAIR(3));
                    }else if(bazi[i][j] == '}'){
                        attron(COLOR_PAIR(1));
                        mvprintw(i , j , ">");
                        attroff(COLOR_PAIR(1));
                    }else if(bazi[i][j] == 'D'){
                        attron(COLOR_PAIR(2));
                        mvprintw(i , j , "|");
                        attroff(COLOR_PAIR(2));
                    }else if(bazi[i][j] == 'U'){
                        attron(COLOR_PAIR(2));
                        mvprintw(i , j , "_");
                        attroff(COLOR_PAIR(2));
                    }else if(bazi[i][j] == '?'){
                        attron(COLOR_PAIR(2));
                        mvprintw(i , j , "?");
                        attroff(COLOR_PAIR(2));
                    }else if(bazi[i][j] == '0'){
                        mvprintw(i , j , "⚒");
                    }else if(bazi[i][j] == '1'){
                        mvprintw(i , j , "🗡");
                    }else if(bazi[i][j] == '2'){
                        mvprintw(i , j , "M");
                    }else if(bazi[i][j] == '3'){
                        mvprintw(i , j , "➳");
                    }else if(bazi[i][j] == '4'){
                        mvprintw(i , j , "⚔");
                    }else if(bazi[i][j] == 'f'){
                        if(ghaza[i][j] == 1 || ghaza[i][j] == 4){//regular food

                            mvprintw(i , j , "f");

                        }else if(ghaza[i][j] == 2 || ghaza[i][j] == 5){//strenghy food
                            attron(COLOR_PAIR(6));
                            mvprintw(i , j , "f");
                            attroff(COLOR_PAIR(6));
                        }else if(ghaza[i][j] == 3 || ghaza[i][j] == 6){//speedy food
                            attron(COLOR_PAIR(4));  
                            mvprintw(i , j , "f");
                            attroff(COLOR_PAIR(4));
                        }
                    }else if(bazi[i][j] == 'd'){
                        attron(COLOR_PAIR(6));
                        mvprintw(i , j , "D");
                        attroff(COLOR_PAIR(6));
                    }else if(bazi[i][j] == 'F'){
                        attron(COLOR_PAIR(6));
                        mvprintw(i , j , "F");
                        attroff(COLOR_PAIR(6));
                    }else if(bazi[i][j] == 't'){
                        attron(COLOR_PAIR(4));
                        mvprintw(i , j , "G");
                        attroff(COLOR_PAIR(4));
                    }else if(bazi[i][j] == 'S'){
                        attron(COLOR_PAIR(1));
                        mvprintw(i , j , "S");
                        attroff(COLOR_PAIR(1));
                    }else if(bazi[i][j] == 'u'){
                        mvprintw(i , j , "U");
                    }else if(bazi[i][j] == '6'){//Health
                        //attron(COLOR_PAIR(1));
                        mvprintw(i , j , "⚕");
                        //attroff(COLOR_PAIR(1));
                    }else if(bazi[i][j] == '5'){//Speed
                        //attron(COLOR_PAIR(4));
                        mvprintw(i , j , "⛷");
                        //attroff(COLOR_PAIR(4));
                    }else if(bazi[i][j] == ')'){//Damage
                        //attron(COLOR_PAIR(6));
                        mvprintw(i , j , "☠");
                        //attroff(COLOR_PAIR(6));
                    }else{
                        mvprintw(i , j , "%c" , bazi[i][j]);
                    }
                }
            }else{
                mvprintw(i , j , " ");
            }
        }
    }
    
    for(int k = 0 ; k < otagh ; k++){
        
        if(list[k][4] == 1){//Nightmare
            for(int i = list[k][0] ; i <= list[k][0] + list[k][2] ; i++){
                for(int j = list[k][1] ; j <= list[k][1] + list[k][3] ; j++){
                    if(didan[j][i] == 1 || M==1){
                        if(bazi[j][i] == '}'){
                            attron(COLOR_PAIR(1));
                            mvprintw(i , j , ">");
                            attroff(COLOR_PAIR(1));
                        }else if((bazi[j][i] == '|' || bazi[j][i] == '_' || bazi[j][i] == '+' || bazi[j][i] == 'O')){
                            attron(COLOR_PAIR(5));
                            mvprintw(j , i , "%c" , bazi[j][i]);
                            attroff(COLOR_PAIR(5)); 
                        }
                    }
                }
            }
        }else if(list[k][4] == 3){//Golden
            for(int i = list[k][0] ; i <= list[k][0] + list[k][2] ; i++){
                for(int j = list[k][1] ; j <= list[k][1] + list[k][3] ; j++){
                    if(didan[j][i] == 1 || M==1){
                        if(bazi[j][i] == '}'){
                            attron(COLOR_PAIR(1));
                            mvprintw(i , j , ">");
                            attroff(COLOR_PAIR(1));
                        }else if((bazi[j][i] == '|' || bazi[j][i] == '_' || bazi[j][i] == '+' || bazi[j][i] == 'O')){
                            attron(COLOR_PAIR(3));
                            mvprintw(j , i , "%c" , bazi[j][i]);
                            attroff(COLOR_PAIR(3)); 
                        }
                    }
                }
            }
        }
        else if(list[k][4] == 2){//Enchant 
              for(int i = list[k][0] ; i <= list[k][0] + list[k][2] ; i++){
                for(int j = list[k][1] ; j <= list[k][1] + list[k][3] ; j++){
                    if(didan[j][i] == 1 || M==1){
                        if(bazi[j][i] == '}'){
                            attron(COLOR_PAIR(1));
                            mvprintw(i , j , ">");
                            attroff(COLOR_PAIR(1));
                        }else if((bazi[j][i] == '|' || bazi[j][i] == '_' || bazi[j][i] == '+' || bazi[j][i] == 'O')){
                            attron(COLOR_PAIR(7));
                            mvprintw(j , i , "%c" , bazi[j][i]);
                            attroff(COLOR_PAIR(7)); 
                        }else if(bazi[j][i] == 'D'){
                            attron(COLOR_PAIR(7));
                            mvprintw(j , i , "|");
                            attroff(COLOR_PAIR(7));
                        }else if(bazi[j][i] == 'U'){
                            attron(COLOR_PAIR(7));
                            mvprintw(j , i , "_");
                            attroff(COLOR_PAIR(7));
                        }else if(bazi[j][i] == '?'){
                            attron(COLOR_PAIR(7));
                            mvprintw(j , i , "?");
                            attroff(COLOR_PAIR(7));
                        }
                    }
                }
            }
        }   
    }
    if(bazi[y][x] == '+' || bazi[y][x] == '#'){
        for(int i = 0 ; i < otagh ; i++){
            if(list[i][4] == 1){
                for(int j = list[i][0] ; j <= list[i][0] + list[i][2] ; j++){
                    for(int k = list[i][1] ; k <= list[i][1] + list[i][3] ; k++){
                        didan[k][j] = 0;        
                    }
                }
            }
        }
    }
    if(pl->color == 1){
        mvprintw(y , x , "@");
    }else if (pl->color == 2){
        attron(COLOR_PAIR(6));
        mvprintw(y , x , "@");
        attroff(COLOR_PAIR(6));
    }else if(pl->color == 3){
        attron(COLOR_PAIR(2));
        mvprintw(y , x , "@");
        attroff(COLOR_PAIR(2));
    }
}

void talegozar(int otagh , int list[otagh][5] , char bazi[LINES][COLS] , int didan[LINES][COLS] , int value[LINES][COLS]){
    for(int i = 0 ; i < otagh ; i++){
        int vaz = 0;
        if(list[i][4] == 1){
            vaz = -2;
        }
        int r = rand()%3;
        if(r == 0){
            while(vaz<2){
                int x_tale = rand()%(list[i][2] - 1);
                x_tale += list[i][0] + 1;
                int y_tale = rand()%(list[i][3] - 1);
                y_tale += list[i][1] + 1;
                if(bazi[y_tale][x_tale] == '.'){
                    bazi[y_tale][x_tale] = 'T';
                    value[y_tale][x_tale] = -1;
                    vaz++;
                }
            }
        }
    }
}

void pelegozar(int otagh , int list[otagh][5] , char bazi[LINES][COLS] , int didan[LINES][COLS] , Pos * noghte){
    int vaz  =  0;
    int i = otagh - 1;
    while(vaz == 0){
        int x_tale = rand()%(list[i][2] - 1);
        x_tale += list[i][0] + 1;
        int y_tale = rand()%(list[i][3] - 1);
        y_tale += list[i][1] + 1;
        if(bazi[y_tale][x_tale] == '.'){
            bazi[y_tale][x_tale] = '<';
            vaz++;
            noghte->x = x_tale;
            noghte->y = y_tale;
        }
    }
}

void sootoon(int otagh , int list[otagh][5] , char bazi[LINES][COLS] , int didan[LINES][COLS]){
    for(int i = 0 ; i < otagh ; i++){
        int x = list[i][0] + 2;
        int y = list[i][1] + 2;
        int tool = list[i][2] - 4 ;
        int arz = list[i][3] - 4 ;
        int r = rand()%2;
        for(int z = 0 ; z < r+1 ; z++){
            int x_soot , y_soot;
            do{
                x_soot = rand()%(tool);
                y_soot = rand()%(arz);
                x_soot += x;
                y_soot += y;
            }while(bazi[y_soot][x_soot] != '.');
            bazi[y_soot][x_soot] = 'O';
        }
    }
}

void gold(int otagh , int list[otagh][5] , char bazi[LINES][COLS] , int didan[LINES][COLS] , int value[LINES][COLS]){
    for(int i = 0 ; i < otagh ; i++){
        int r = rand()%5;
        if(list[i][4] == 3){//Golden room
            r += 8;
        }
        for(int p = 0 ; p < r ; p++){
            int vaz = 0;
            int k = rand()%20;
            if(list[i][4] == 3){
                k = rand()%10;
            }
            while(vaz == 0){
                int x_gold = rand()%(list[i][2] - 1);
                x_gold += list[i][0] + 1;
                int y_gold = rand()%(list[i][3] - 1);
                y_gold += list[i][1] + 1;
                if(bazi[y_gold][x_gold] == '.'){
                    if(k == 0){
                        bazi[y_gold][x_gold] = 'G';
                        int arz = rand()%10;
                        arz += 10;
                        value[y_gold][x_gold] = arz;
                    }else{
                        bazi[y_gold][x_gold] = 'g';
                        int arz = rand()%7;
                        arz += 1;
                        value[y_gold][x_gold] = arz;
                    }
                    vaz++;
                }
            }
        }
    }
}

Pos player(int otagh , int list[otagh][5] , char bazi[LINES][COLS] , int didan[LINES][COLS] , int value[LINES][COLS]){
    Pos pos;
    int vaz = 0;
    int k = rand()%20;
    while(vaz == 0){
        pos.x = rand()%(list[0][2] - 1);
        pos.x += list[0][0] + 1;
        pos.y = rand()%(list[0][3] - 1);
        pos.y += list[0][1] + 1;
        if(bazi[pos.y][pos.x] == '.'){
            vaz = 1;
        }
    }
    return pos;
}

int tabaghe_saz(Profile *pl , int list2[100][5] , int didan[LINES][COLS] , int value[LINES][COLS] , char bazi[LINES][COLS] , int vaz , Pos * noghte , int ghaza[LINES][COLS] , int joon[LINES][COLS] , int oftadeh[LINES][COLS]){
    for(int i = 0 ; i < LINES ; i++){
        for(int j = 0 ; j < COLS ; j++){
            didan[i][j] = 0;
            value[i][j] = 0;
            ghaza[i][j] = 0;
            bazi[i][j] = ' ';
            oftadeh[i][j] = 0;
        }
    }
    int otagh = 6;
    int r = rand()%5;
    otagh += r;
    int list[otagh][5];
    do{
    otagh = 6;
    int r = rand()%5;
    otagh += r;
    int list[otagh][5]; 
    }while(!Otaghsaz(otagh , list , vaz , noghte));
    list[0][4] = 0;
    otaghzakhire(otagh , list , bazi , didan , noghte , vaz);
    for(int i = 1 ; i < otagh ; i++){
        masirsaz(i-1 , i , otagh , list , bazi);
    }

    for(int i = 0 ; i < otagh ; i++){
        for(int j = 0 ; j < 5 ; j++){
            list2[i][j] = list[i][j];
        }
    }

    sootoon(otagh , list , bazi , didan);
    pelegozar(otagh , list , bazi , didan , noghte);
    talegozar(otagh , list , bazi , didan , value);
    gold(otagh , list , bazi , didan , value);
    Aslahe(otagh , list , bazi , didan , oftadeh);
    food(otagh , list , bazi , didan , ghaza);
    monster(otagh , list , bazi , didan , joon , pl);
    telesm(otagh , list , bazi , didan , pl);

    for(int k = 0 ; k < otagh ; k++){
        if(list[k][4] == 2){
            for(int y = list[k][1] ; y <= list[k][1] + list[k][3]; y++){
                if(bazi[y][list[k][0]] == '+'){//D dar amoodi
                    bazi[y][list[k][0]] = 'D';
                }
                if(bazi[y][list[k][0]+list[k][2]] == '+'){
                    bazi[y][list[k][0] + list[k][2]] = 'D';
                }
            }
            for(int x = list[k][0] ; x <= list[k][0] + list[k][2] ; x++){
                if(bazi[list[k][1]][x] == '+'){//U dar ofoghi
                    bazi[list[k][1]][x] = 'U';
                }
                if(bazi[list[k][1]+list[k][3]][x] == '+'){
                    bazi[list[k][1] + list[k][3]][x] = 'U';
                }
            }
        }
    }
    return otagh;
}

void roshankon(int x , int y , int didan[LINES][COLS] , char bazi[LINES][COLS]){
    didan[y][x] = 2;
    for(int p = 1 ; p < 6 ; p++){
        for(int i = p ; i > -1; i--){
            if(bazi[y+i][x+(p-i)] == '#' || bazi[y+i][x+(p-i)] == '+'){
                for(int k = 1 ; k > -1 ; k--){
                    int x_jad = x+(p-i);
                    int y_jad = y+i;
                    if(didan[y_jad+k][x_jad+(1-k)] == 2 ){
                        didan[y_jad][x_jad] = 2;
                    }
                    if(didan[y_jad-k][x_jad-(1-k)] == 2){
                        didan[y_jad][x_jad] = 2;
                    }
                }
            }
            if(bazi[y+i][x-(p-i)] == '#' || bazi[y+i][x-(p-i)] == '+'){
                for(int k = 1 ; k > -1 ; k--){
                    int x_jad = x-(p-i);
                    int y_jad = y+i;
                    if(didan[y_jad+k][x_jad+(1-k)] == 2 ){
                        didan[y_jad][x_jad] = 2;
                    }
                    if(didan[y_jad-k][x_jad-(1-k)] == 2){
                        didan[y_jad][x_jad] = 2;
                    }
                }
            }
            if(bazi[y-i][x+(p-i)] == '#' || bazi[y-i][x+(p-i)] == '+'){
                for(int k = 1 ; k > -1 ; k--){
                    int x_jad = x+(p-i);
                    int y_jad = y-i;
                    if(didan[y_jad+k][x_jad+(1-k)] == 2 ){
                        didan[y_jad][x_jad] = 2;
                    }
                    if(didan[y_jad-k][x_jad-(1-k)] == 2){
                        didan[y_jad][x_jad] = 2;
                    }
                }
            }
            if(bazi[y-i][x-(p-i)] == '#' || bazi[y-i][x-(p-i)] == '+'){
                for(int k = 1 ; k > -1 ; k--){
                    int x_jad = x-(p-i);
                    int y_jad = y-i;
                    if(didan[y_jad+k][x_jad+(1-k)] == 2 ){
                        didan[y_jad][x_jad] = 2;
                    }
                    if(didan[y_jad-k][x_jad-(1-k)] == 2){
                        didan[y_jad][x_jad] = 2;
                    }
                }
            }
        }
    }   
    for(int i = 5 ; i > -6 ; i--){
        for(int j = 5 ; j > -6 ; j--){
            if(didan[y+i][x+j] == 2){
                didan[y+i][x+j] = 1; 
            }
        }
    }
}

int koodoom(int x , int y , int otagh , int list[otagh][5]){
    for(int i = 0 ; i < otagh ; i++){
        int x_alan = list[i][0];
        int y_alan = list[i][1];
        int tool = list[i][2];
        int arz = list[i][3];
        if(x >= x_alan && x <= x_alan+tool){
            if(y >= y_alan && y <= y_alan+arz){
                if(list[i][4] == 1){
                    return i;
                }else{
                    return i;
                }
            }
        }
    }
    return 20;
}

void roshangar(int otagh , int list[otagh][5] , int num , int didan[LINES][COLS] , int x , int y , char bazi[LINES][COLS]){
    if(list[num][4] == 1){//Nightmare room
        int x_alan = list[num][0];
        int y_alan = list[num][1];
        int tool = list[num][2];
        int arz = list[num][3];
        for(int i = x_alan ; i <= x_alan + tool ; i++){
            for(int j = y_alan ; j <= y_alan + arz ; j++){
                didan[j][i] = 0;
            }
        }
        for(int i = x - 2 ; i < x + 3 ; i++){
           for(int j = y - 2 ; j < y + 3 ; j++){
                if(bazi[j][i] != '#'){
                    didan[j][i] = 1;
                }
           } 
        }
    }else{
        int x_alan = list[num][0];
        int y_alan = list[num][1];
        int tool = list[num][2];
        int arz = list[num][3];
        for(int i = x_alan ; i <= x_alan + tool ; i++){
            for(int j = y_alan ; j <= y_alan + arz ; j++){
                didan[j][i] = 1;
            }
        }
    }
}

void harekat_monster(Profile *pl , int otagh , int list[otagh][5] , int joon[LINES][COLS] , char bazi[LINES][COLS] , int donbal[LINES][COLS]){
    int ja = koodoom(pl->pos.x , pl->pos.y , otagh , list);
    init_pair(12 , COLOR_RED , COLOR_BLACK);
    attron(COLOR_PAIR(12));
    if(ja == 20){

    }else{
        int x_alan = list[ja][0];
        int y_alan = list[ja][1];
        int tool = list[ja][2];
        int arz = list[ja][3];
        for(int i = x_alan ; i <= x_alan + tool ; i++){
            for(int j = y_alan ; j <= y_alan + arz ; j++){
                if(bazi[j][i] == 'd'){
                    if((i+1 == pl->pos.x || i-1 == pl->pos.x) && j == pl->pos.y){
                        pl->HP--;
                        timeout(-1);
                        mvprintw(2  , 5 , "You have been hit by Daemon! Press any key to continue..."); 
                        getch();
                    }else if((j+1 == pl->pos.y || j-1 == pl->pos.y) && i == pl->pos.x){
                        pl->HP--;
                        timeout(-1);
                        mvprintw(2  , 5 , "You have been hit by Daemon! Press any key to continue..."); 
                        getch();
                    }
                }else if(bazi[j][i] == 'F'){
                    if((i+1 == pl->pos.x || i-1 == pl->pos.x) && j == pl->pos.y){
                        pl->HP --;
                        timeout(-1);
                        mvprintw(2  , 5 , "You have been hit by Fire Breathing Monster! Press any key to continue..."); 
                        getch();
                    }else if((j+1 == pl->pos.y || j-1 == pl->pos.y) && i == pl->pos.x){
                        pl->HP --;
                        timeout(-1);
                        mvprintw(2  , 5 , "You have been hit by Fire Breathing Monster! Press any key to continue..."); 
                        getch();
                    }
                }else if(bazi[j][i] == 't' && donbal[j][i] == 0){
                    if((i+1 == pl->pos.x || i-1 == pl->pos.x) && j == pl->pos.y){
                        donbal[j][i] = 5;
                    }else if((j+1 == pl->pos.y || j-1 == pl->pos.y) && i == pl->pos.x){
                        donbal[j][i] = 5;
                    }
                }else if(bazi[j][i] == 't' && donbal[j][i] > 0){//
                    if(((i+1 == pl->pos.x || i-1 == pl->pos.x) && j == pl->pos.y) || ((j+1 == pl->pos.y || j-1 == pl->pos.y) && i == pl->pos.x)){
                        pl->HP --;
                        timeout(-1);
                        mvprintw(2  , 5 , "You have been hit by Giant! Press any key to continue...");
                        getch();
                        donbal[j][i]--; 
                    }else{
                        int x_khoob = -2;
                        int y_khoob = -2;
                        for(int x = -1 ; x < 2 ; x++){
                            for(int y = -1 ; y < 2 ; y++){
                                if((x == 0 && y == 0) || (x == 1 && y == 1) || (x == 1 && y == -1) || (x == -1 && y == 1) || (x == -1 && y == -1)){
                                
                                }else{
                                    if(bazi[j+y][i+x] == '.'){
                                        if(x_khoob == -2 && y_khoob == -2){
                                            x_khoob = x;
                                            y_khoob = y;
                                        }else{
                                            int f_1 = (i+x) - pl->pos.x;
                                            int f_2 = (j+y) - pl->pos.y;
                                            int f_3 = (i+x_khoob) - pl->pos.x;
                                            int f_4 = (j+y_khoob) - pl->pos.y;
                                            if(f_1 < 0){
                                                f_1 *= -1;
                                            }
                                            if(f_2 < 0){
                                                f_2 *= -1;
                                            }
                                            if(f_3 < 0){
                                                f_3 *= -1;
                                            }
                                            if(f_4 < 0){
                                                f_4 *= -1;
                                            }
                                            if(f_1 + f_2 < f_3 + f_4){
                                                x_khoob = x;
                                                y_khoob = y;
                                            }
                                        }
                                    }
                                }    
                            }
                        }
                        if(y_khoob == -2 && x_khoob == -2){
                            donbal[j][i]--;
                        }else{
                            bazi[j][i] = '.';
                            bazi[j+y_khoob][i+x_khoob] = '9';
                            donbal[j+y_khoob][i+x_khoob] = donbal[j][i];
                            donbal[j+y_khoob][i+x_khoob]--;
                            donbal[j][i] = 0;
                            joon[j+y_khoob][i+x_khoob] = joon[j][i];
                            joon[j][i] = 0;
                        }
                    }
                }else if(bazi[j][i] == 'S'){// 
                    if((i+1 == pl->pos.x || i == pl->pos.x || i-1 == pl->pos.x) && (j-1 == pl->pos.y || j == pl->pos.y || j+1 == pl->pos.y)){
                        pl->HP --;
                        timeout(-1);
                        mvprintw(2  , 5 , "You have been hit by Snake! Press any key to continue..."); 
                        getch();
                    }else{
                        int x_khoob = -2;
                        int y_khoob = -2;
                        for(int x = -1 ; x < 2 ; x++){
                            for(int y = -1 ; y < 2 ; y++){
                                if(x == 0 && y == 0){
                                
                                }else{
                                    if(bazi[j+y][i+x] == '.'){
                                        if(x_khoob == -2 && y_khoob == -2){
                                            x_khoob = x;
                                            y_khoob = y;
                                        }else{
                                            int f_1 = (i+x) - pl->pos.x;
                                            int f_2 = (j+y) - pl->pos.y;
                                            int f_3 = (i+x_khoob) - pl->pos.x;
                                            int f_4 = (j+y_khoob) - pl->pos.y;
                                            if(f_1 < 0){
                                                f_1 *= -1;
                                            }
                                            if(f_2 < 0){
                                                f_2 *= -1;
                                            }
                                            if(f_3 < 0){
                                                f_3 *= -1;
                                            }
                                            if(f_4 < 0){
                                                f_4 *= -1;
                                            }
                                            if(f_1 + f_2 < f_3 + f_4){
                                                x_khoob = x;
                                                y_khoob = y;
                                            }
                                        }
                                    }
                                }    
                            }
                        }
                        if(y_khoob == -2 && x_khoob == -2){
                        }else{
                            bazi[j][i] = '.';
                            bazi[j+y_khoob][i+x_khoob] = '8';
                            joon[j+y_khoob][i+x_khoob] = joon[j][i];
                            joon[j][i] = 0;
                        }
                    }
                }else if(bazi[j][i] == 'u' && donbal[j][i] == 0){
                    if((i+1 == pl->pos.x || i-1 == pl->pos.x) && j == pl->pos.y){
                        donbal[j][i] = 5;
                    }else if((j+1 == pl->pos.y || j-1 == pl->pos.y) && i == pl->pos.x){
                        donbal[j][i] = 5;
                    }
                }else if(bazi[j][i] == 'u' && donbal[j][i] > 0){//
                    if(((i+1 == pl->pos.x || i-1 == pl->pos.x) && j == pl->pos.y) || ((j+1 == pl->pos.y || j-1 == pl->pos.y) && i == pl->pos.x)){
                        pl->HP --;
                        timeout(-1);
                        mvprintw(2  , 5 , "You have been hit by Undeed! Press any key to continue...");
                        getch();
                        donbal[j][i]--; 
                    }else{
                        int x_khoob = -2;
                        int y_khoob = -2;
                        for(int x = -1 ; x < 2 ; x++){
                            for(int y = -1 ; y < 2 ; y++){
                                if((x == 0 && y == 0) || (x == 1 && y == 1) || (x == 1 && y == -1) || (x == -1 && y == 1) || (x == -1 && y == -1)){
                                
                                }else{
                                    if(bazi[j+y][i+x] == '.'){
                                        if(x_khoob == -2 && y_khoob == -2){
                                            x_khoob = x;
                                            y_khoob = y;
                                        }else{
                                            int f_1 = (i+x) - pl->pos.x;
                                            int f_2 = (j+y) - pl->pos.y;
                                            int f_3 = (i+x_khoob) - pl->pos.x;
                                            int f_4 = (j+y_khoob) - pl->pos.y;
                                            if(f_1 < 0){
                                                f_1 *= -1;
                                            }
                                            if(f_2 < 0){
                                                f_2 *= -1;
                                            }
                                            if(f_3 < 0){
                                                f_3 *= -1;
                                            }
                                            if(f_4 < 0){
                                                f_4 *= -1;
                                            }
                                            if(f_1 + f_2 < f_3 + f_4){
                                                x_khoob = x;
                                                y_khoob = y;
                                            }
                                        }
                                    }
                                }    
                            }
                        }
                        if(y_khoob == -2 && x_khoob == -2){
                            donbal[j][i]--;
                        }else{
                            bazi[j][i] = '.';
                            bazi[j+y_khoob][i+x_khoob] = '7';
                            donbal[j+y_khoob][i+x_khoob] = donbal[j][i];
                            donbal[j+y_khoob][i+x_khoob]--;
                            donbal[j][i] = 0;
                            joon[j+y_khoob][i+x_khoob] = joon[j][i];
                            joon[j][i] = 0;
                        }
                    }
                }
            }
        }
    attroff(COLOR_PAIR(12));
        for(int i = x_alan ; i <= x_alan + tool ; i++){
            for(int j = y_alan ; j <= y_alan + arz ; j++){
                if(bazi[j][i] == '9'){
                    bazi[j][i] = 't';
                }
                if(bazi[j][i] == '8'){
                    bazi[j][i] = 'S';
                }
                if(bazi[j][i] == '7'){
                    bazi[j][i] = 'u';
                }
            }   
        }
    }
}

void check_monster(Profile *pl , int otagh , int list[otagh][5] , int joon[LINES][COLS] , char bazi[LINES][COLS] , int donbal[LINES][COLS]){
    if(difftime(now , past_monster) >= 2){
        time(&past_monster);
        harekat_monster(pl , otagh , list , joon , bazi , donbal);
    }
}

Pos harekat_edame(Profile *pl, int x , int y , char c ,int otagh , int list[otagh][5] , char bazi[LINES][COLS] , int didan[LINES][COLS] , int value[LINES][COLS] , int ghaza[LINES][COLS] , int oftadeh[LINES][COLS]){
    Pos next;
    init_pair(6 , COLOR_RED , COLOR_BLACK);
    if(bazi[y][x] == '#'){
        next.x = x;
        next.y = y;
        roshankon(x , y , didan , bazi);
    }else if(bazi[y][x] == '+' || bazi[y][x] == '?'){
        next.x = x;
        next.y = y;
        if(c == '#'){
            int number = koodoom(x , y , otagh , list);
            roshangar(otagh , list , number , didan , x , y , bazi);
        }else{
            roshankon(x , y , didan , bazi);
        }
    }else if(bazi[y][x] == 'G' || bazi[y][x] == 'g'){
        next.x = x;
        next.y = y;
        int number = koodoom(x , y , otagh , list);
        if(number < 0){
            roshangar(otagh , list , number , didan , x , y , bazi);
            value[y][x] = 0;
        }else{
            roshangar(otagh , list , number , didan , x , y , bazi);
        }
        bazi[y][x] = '.';
    }else if(bazi[y][x] == '<'){
        next.x = -1;
        next.y = -1;
    }else if(bazi[y][x] == '}'){//estefade shode
        next.x = -2;
        next.y = -2;
    }else if(bazi[y][x] == '.'){
        next.x = x;
        next.y = y;
        int number = koodoom(x , y , otagh , list);
        if(number < 0){
            roshangar(otagh , list , number , didan , x , y , bazi);
        }else{
            roshangar(otagh , list , number , didan , x , y , bazi);
        }
    }else if(bazi[y][x] == 'T'){
        bazi[y][x] = '^';
        next.x = x;
        next.y = y;
        int number = koodoom(x , y , otagh , list);
        if(number < 0){
            roshangar(otagh , list , number , didan , x , y , bazi);
        }else{
            roshangar(otagh , list , number , didan , x , y , bazi);
        }
    }else if(bazi[y][x] == '^'){
        next.x = x;
        next.y = y;
        int number = koodoom(x , y , otagh , list);
        if(number < 0){
            roshangar(otagh , list , number , didan , x , y , bazi);
        }else{
            roshangar(otagh , list , number , didan , x , y , bazi);
        }
    }else if(bazi[y][x] == 'D' || bazi[y][x] == 'U'){
        bazi[y][x] = '?';
        next.x = x;
        next.y = y;
        int number = koodoom(x , y , otagh , list);
        if(number < 0){
            roshangar(otagh , list , number , didan , x , y , bazi);
        }else{
            roshangar(otagh , list , number , didan , x , y , bazi);
        }
    }else if(bazi[y][x] == '0' || bazi[y][x] == '1' || bazi[y][x] == '2' || bazi[y][x] == '3' || bazi[y][x] == '4'){//aslahe
        next.x = x;
        next.y = y;
        if(bazi[y][x] == '0'){//Mace
            pl->aslahe[0]++;
        }else if(bazi[y][x] == '1'){//Dagger
            pl->aslahe[1] += oftadeh[y][x];
            oftadeh[y][x] = 0;
        }else if(bazi[y][x] == '2'){//Magic Wand
            pl->aslahe[2] += oftadeh[y][x];
            oftadeh[y][x] = 0;
        }else if(bazi[y][x] == '3'){//Normal Arrow
            pl->aslahe[3] += oftadeh[y][x];
            oftadeh[y][x] = 0;
        }else if(bazi[y][x] == '4'){//Sword
            pl->aslahe[4]++;
        }
        bazi[y][x] = '.';
        int number = koodoom(x , y , otagh , list);
        if(number < 0){
            roshangar(otagh , list , number , didan , x , y , bazi);
        }else{
            roshangar(otagh , list , number , didan , x , y , bazi);
        }

    }else if(bazi[y][x] == 'f'){
        next.x = x;
        next.y = y;
        if(ghaza[y][x] == 1){
            if(pl->tedadfood < 5){
                pl->food[pl->tedadfood] = 1;
                pl->tedadfood++;
                bazi[y][x] = '.';
            }else{
            }
        }else if(ghaza[y][x] == 2){
            if(pl->tedadfood < 5){
                pl->food[pl->tedadfood] = 2;
                pl->tedadfood++;
                bazi[y][x] = '.';
            }else{
            }
        }else if(ghaza[y][x] == 3){
            if(pl->tedadfood < 5){
                pl->food[pl->tedadfood] = 3;
                pl->tedadfood++;
                bazi[y][x] = '.';
            }else{
            }
        }else if(ghaza[y][x] == 4 || ghaza[y][x] == 5 || ghaza[y][x] == 6){
            bazi[y][x] = '.';
        }
        int number = koodoom(x , y , otagh , list);
        if(number < 0){
            roshangar(otagh , list , number , didan , x , y , bazi);
        }else{
            roshangar(otagh , list , number , didan , x , y , bazi);
        }
    }else if(bazi[y][x] == '6'){
        pl->telesm[0]++;
        next.x = x;
        next.y = y;
        bazi[y][x] = '.';
    }else if(bazi[y][x] == '5'){
        pl->telesm[1]++;
        next.x = x;
        next.y = y;
        bazi[y][x] = '.';
    }else if(bazi[y][x] == ')'){
        pl->telesm[2]++;
        next.x = x;
        next.y = y;
        bazi[y][x] = '.';
    }
    return next; 
}

Pos harekat(Profile *pl , int otagh , int list[otagh][5] , char bazi[LINES][COLS] , int didan[LINES][COLS] , int value[LINES][COLS] , int vaz , int ghaza[LINES][COLS] , int oftadeh[LINES][COLS]){
    Pos next;
    int x = pl->pos.x;
    int y = pl->pos.y;
    char c = bazi[y][x];
    if(vaz == 0){//U
        if(pl->Speed > 0){
            y -= 2;
            pl->Speed--;
            if(bazi[y][x] == 'O' || bazi[y][x] == '|' || bazi[y][x] == '_' || bazi[y][x] == ' ' || bazi[y][x] == 'd' || bazi[y][x] == 'F' || bazi[y][x] == 't' || bazi[y][x] == 'S' || bazi[y][x] == 'u' || bazi[y][x] == ' '){
                y++;
            }
            if(bazi[y][x] == 'O' || bazi[y][x] == '|' || bazi[y][x] == '_' || bazi[y][x] == ' ' || bazi[y][x] == 'd' || bazi[y][x] == 'F' || bazi[y][x] == 't' || bazi[y][x] == 'S' || bazi[y][x] == 'u'){
            next.x = pl->pos.x;
            next.y = pl->pos.y;
            }else{
                next = harekat_edame(pl ,x , y, c , otagh , list , bazi , didan , value , ghaza , oftadeh);
            }
        }else{
            y--;
            if(bazi[y][x] == 'O' || bazi[y][x] == '|' || bazi[y][x] == '_' || bazi[y][x] == ' ' || bazi[y][x] == 'd' || bazi[y][x] == 'F' || bazi[y][x] == 't' || bazi[y][x] == 'S' || bazi[y][x] == 'u'){
                next.x = pl->pos.x;
                next.y = pl->pos.y;
            }else{
                next = harekat_edame(pl ,x , y, c , otagh , list , bazi , didan , value , ghaza , oftadeh);
            }
        }
    }else if(vaz == 1){//D
        if(pl->Speed > 0){
            y += 2;
            pl->Speed--;
            if(bazi[y][x] == 'O' || bazi[y][x] == '|' || bazi[y][x] == '_' || bazi[y][x] == ' ' || bazi[y][x] == 'd' || bazi[y][x] == 'F' || bazi[y][x] == 't' || bazi[y][x] == 'S' || bazi[y][x] == 'u' || bazi[y][x] == ' '){
                y--;
            }
            if(bazi[y][x] == 'O' || bazi[y][x] == '|' || bazi[y][x] == '_' || bazi[y][x] == ' ' || bazi[y][x] == 'd' || bazi[y][x] == 'F' || bazi[y][x] == 't' || bazi[y][x] == 'S' || bazi[y][x] == 'u'){
                next.x = pl->pos.x;
                next.y = pl->pos.y;
            }else{
                next = harekat_edame(pl ,x , y, c , otagh , list , bazi , didan , value , ghaza , oftadeh);
            }
        }else{
            y++;
            if(bazi[y][x] == 'O' || bazi[y][x] == '|' || bazi[y][x] == '_' || bazi[y][x] == ' ' || bazi[y][x] == 'd' || bazi[y][x] == 'F' || bazi[y][x] == 't' || bazi[y][x] == 'S' || bazi[y][x] == 'u'){
                next.x = pl->pos.x;
                next.y = pl->pos.y;
            }else{
                next = harekat_edame(pl ,x , y, c , otagh , list , bazi , didan , value , ghaza , oftadeh);
            }
        }
    }else if(vaz == 2){//R
        if(pl->Speed > 0){
            x += 2;
            pl->Speed--;
            if(bazi[y][x] == 'O' || bazi[y][x] == '|' || bazi[y][x] == '_' || bazi[y][x] == ' ' || bazi[y][x] == 'd' || bazi[y][x] == 'F' || bazi[y][x] == 't' || bazi[y][x] == 'S' || bazi[y][x] == 'u' || bazi[y][x] == ' '){
                x--;
            }
            if(bazi[y][x] == 'O' || bazi[y][x] == '|' || bazi[y][x] == '_' || bazi[y][x] == ' ' || bazi[y][x] == 'd' || bazi[y][x] == 'F' || bazi[y][x] == 't' || bazi[y][x] == 'S' || bazi[y][x] == 'u'){
                next.x = pl->pos.x;
                next.y = pl->pos.y;
            }else{
                next = harekat_edame(pl ,x , y, c , otagh , list , bazi , didan , value , ghaza , oftadeh);
            }
        }else{
            x++;
            if(bazi[y][x] == 'O' || bazi[y][x] == '|' || bazi[y][x] == '_' || bazi[y][x] == ' ' || bazi[y][x] == 'd' || bazi[y][x] == 'F' || bazi[y][x] == 't' || bazi[y][x] == 'S' || bazi[y][x] == 'u'){
                next.x = pl->pos.x;
                next.y = pl->pos.y;
            }else{
                next = harekat_edame(pl ,x , y, c , otagh , list , bazi , didan , value , ghaza , oftadeh);
            }
        }
    }else if(vaz == 3){//L
        if(pl->Speed > 0){
            x -= 2;
            pl->Speed--;
            if(bazi[y][x] == 'O' || bazi[y][x] == '|' || bazi[y][x] == '_' || bazi[y][x] == ' ' || bazi[y][x] == 'd' || bazi[y][x] == 'F' || bazi[y][x] == 't' || bazi[y][x] == 'S' || bazi[y][x] == 'u' || bazi[y][x] == ' '){
                x++;
            }
            if(bazi[y][x] == 'O' || bazi[y][x] == '|' || bazi[y][x] == '_' || bazi[y][x] == ' ' || bazi[y][x] == 'd' || bazi[y][x] == 'F' || bazi[y][x] == 't' || bazi[y][x] == 'S' || bazi[y][x] == 'u'){
                next.x = pl->pos.x;
                next.y = pl->pos.y;
            }else{
                next = harekat_edame(pl ,x , y, c , otagh , list , bazi , didan , value , ghaza , oftadeh);
            }
        }else{
            x--;
            if(bazi[y][x] == 'O' || bazi[y][x] == '|' || bazi[y][x] == '_' || bazi[y][x] == ' ' || bazi[y][x] == 'd' || bazi[y][x] == 'F' || bazi[y][x] == 't' || bazi[y][x] == 'S' || bazi[y][x] == 'u'){
                next.x = pl->pos.x;
                next.y = pl->pos.y;
            }else{
                next = harekat_edame(pl ,x , y, c , otagh , list , bazi , didan , value , ghaza , oftadeh);
            }
        }
    }else if(vaz == 4){//UR
        if(pl->Speed > 0){
            x += 2;
            y -= 2;
            pl->Speed--;
            if(bazi[y][x] == 'O' || bazi[y][x] == '|' || bazi[y][x] == '_' || bazi[y][x] == ' ' || bazi[y][x] == 'd' || bazi[y][x] == 'F' || bazi[y][x] == 't' || bazi[y][x] == 'S' || bazi[y][x] == 'u' || bazi[y][x] == ' '){
                x--;
                y++;
            }
            if(bazi[y][x] == 'O' || bazi[y][x] == '|' || bazi[y][x] == '_' || bazi[y][x] == ' ' || bazi[y][x] == 'd' || bazi[y][x] == 'F' || bazi[y][x] == 't' || bazi[y][x] == 'S' || bazi[y][x] == 'u'){
                next.x = pl->pos.x;
                next.y = pl->pos.y;
            }else{
                next = harekat_edame(pl ,x , y, c , otagh , list , bazi , didan , value , ghaza , oftadeh);
            }
        }else{
            x++;
            y--;
            if(bazi[y][x] == 'O' || bazi[y][x] == '|' || bazi[y][x] == '_' || bazi[y][x] == ' ' || bazi[y][x] == 'd' || bazi[y][x] == 'F' || bazi[y][x] == 't' || bazi[y][x] == 'S' || bazi[y][x] == 'u'){
                next.x = pl->pos.x;
                next.y = pl->pos.y;
            }else{
                next = harekat_edame(pl ,x , y, c , otagh , list , bazi , didan , value , ghaza , oftadeh);
            }
        }
    }else if(vaz == 5){//UL
        if(pl->Speed > 0){
            x -= 2;
            y -= 2;
            pl->Speed--;
            if(bazi[y][x] == 'O' || bazi[y][x] == '|' || bazi[y][x] == '_' || bazi[y][x] == ' ' || bazi[y][x] == 'd' || bazi[y][x] == 'F' || bazi[y][x] == 't' || bazi[y][x] == 'S' || bazi[y][x] == 'u' || bazi[y][x] == ' '){
                x++;
                y++;
            }
            if(bazi[y][x] == 'O' || bazi[y][x] == '|' || bazi[y][x] == '_' || bazi[y][x] == ' ' || bazi[y][x] == 'd' || bazi[y][x] == 'F' || bazi[y][x] == 't' || bazi[y][x] == 'S' || bazi[y][x] == 'u'){
                next.x = pl->pos.x;
                next.y = pl->pos.y;
            }else{
                next = harekat_edame(pl ,x , y, c , otagh , list , bazi , didan , value , ghaza , oftadeh);
            }
        }else{
            x--;
            y--;
            if(bazi[y][x] == 'O' || bazi[y][x] == '|' || bazi[y][x] == '_' || bazi[y][x] == ' ' || bazi[y][x] == 'd' || bazi[y][x] == 'F' || bazi[y][x] == 't' || bazi[y][x] == 'S' || bazi[y][x] == 'u'){
                next.x = pl->pos.x;
                next.y = pl->pos.y;
            }else{
                next = harekat_edame(pl ,x , y, c , otagh , list , bazi , didan , value , ghaza , oftadeh);
            }
        }
    }else if(vaz == 6){//DR
        if(pl->Speed > 0){
            x += 2;
            y += 2;
            pl->Speed--;
            if(bazi[y][x] == 'O' || bazi[y][x] == '|' || bazi[y][x] == '_' || bazi[y][x] == ' ' || bazi[y][x] == 'd' || bazi[y][x] == 'F' || bazi[y][x] == 't' || bazi[y][x] == 'S' || bazi[y][x] == 'u' || bazi[y][x] == ' '){
                x--;
                y--;
            }
            if(bazi[y][x] == 'O' || bazi[y][x] == '|' || bazi[y][x] == '_' || bazi[y][x] == ' ' || bazi[y][x] == 'd' || bazi[y][x] == 'F' || bazi[y][x] == 't' || bazi[y][x] == 'S' || bazi[y][x] == 'u'){
                next.x = pl->pos.x;
                next.y = pl->pos.y;
            }else{
                next = harekat_edame(pl ,x , y, c , otagh , list , bazi , didan , value , ghaza , oftadeh);
            }
        }else{
            x++;
            y++;
            if(bazi[y][x] == 'O' || bazi[y][x] == '|' || bazi[y][x] == '_' || bazi[y][x] == ' ' || bazi[y][x] == 'd' || bazi[y][x] == 'F' || bazi[y][x] == 't' || bazi[y][x] == 'S' || bazi[y][x] == 'u'){
                next.x = pl->pos.x;
                next.y = pl->pos.y;
            }else{
                next = harekat_edame(pl ,x , y, c , otagh , list , bazi , didan , value , ghaza , oftadeh);
            }
        }
    }else if(vaz == 7){//DL
        if(pl->Speed > 0){
            x -= 2;
            y += 2;
            pl->Speed--;
            if(bazi[y][x] == 'O' || bazi[y][x] == '|' || bazi[y][x] == '_' || bazi[y][x] == ' ' || bazi[y][x] == 'd' || bazi[y][x] == 'F' || bazi[y][x] == 't' || bazi[y][x] == 'S' || bazi[y][x] == 'u' || bazi[y][x] == ' '){
                x++;
                y--;
            }
            if(bazi[y][x] == 'O' || bazi[y][x] == '|' || bazi[y][x] == '_' || bazi[y][x] == ' ' || bazi[y][x] == 'd' || bazi[y][x] == 'F' || bazi[y][x] == 't' || bazi[y][x] == 'S' || bazi[y][x] == 'u'){
                next.x = pl->pos.x;
                next.y = pl->pos.y;
            }else{
                next = harekat_edame(pl ,x , y, c , otagh , list , bazi , didan , value , ghaza , oftadeh);
            }
        }else{
            x--;
            y++;
            if(bazi[y][x] == 'O' || bazi[y][x] == '|' || bazi[y][x] == '_' || bazi[y][x] == ' ' || bazi[y][x] == 'd' || bazi[y][x] == 'F' || bazi[y][x] == 't' || bazi[y][x] == 'S' || bazi[y][x] == 'u'){
                next.x = pl->pos.x;
                next.y = pl->pos.y;
            }else{
                next = harekat_edame(pl ,x , y, c , otagh , list , bazi , didan , value , ghaza , oftadeh);
            }
        }
    }
    return next;
}

void Aslahe(int otagh , int list[otagh][5] , char bazi[LINES][COLS] , int didan[LINES][COLS] , int oftadeh[LINES][COLS]){
    for(int i = 0 ; i < otagh ; i++){
        int r = rand()%4;
        r++;
        int vaz = 0;
        while(vaz == 0){
            int x_asl = rand()%(list[i][2] - 1);
            x_asl += list[i][0] + 1;
            int y_asl = rand()%(list[i][3] - 1);
            y_asl += list[i][1] + 1;
            if(bazi[y_asl][x_asl] == '.'){
                if(r == 0){//Mace
                    bazi[y_asl][x_asl] = '0';
                }else if(r == 1){//Dagger
                    bazi[y_asl][x_asl] = '1';
                    oftadeh[y_asl][x_asl] = 10;
                }else if(r == 2){//Magic wand
                    bazi[y_asl][x_asl] = '2';
                    oftadeh[y_asl][x_asl] = 8;
                }else if(r == 3){//Normal Arrow
                    bazi[y_asl][x_asl] = '3';
                    oftadeh[y_asl][x_asl] = 20;
                }else if(r == 4){//Sword
                    if(Sword == 1){
                        bazi[y_asl][x_asl] = '4';
                        Sword--;
                    }else{
                        bazi[y_asl][x_asl] = '3';
                    }
                }
                vaz++;
            }
        }   
    }
}

int Menuaslahe(Profile *pl){
    clear();
    board();
    init_pair(1 , COLOR_GREEN , COLOR_BLACK);
    init_pair(1 , COLOR_RED , COLOR_BLACK);
    attron(COLOR_PAIR(1));
    mvprintw(10 , 25 , "Choose your weapon :");
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(2));
    mvprintw(13 , 45 , "Name:");
    mvprintw(13 , 65 , "Type:");
    mvprintw(13 , 85 , "Damage:");
    mvprintw(13 , 105 , "Range:");
    mvprintw(13 , 125 , "Quantity:");
    attroff(COLOR_PAIR(2));
    char *choice[] = {"Mace" , "Dagger" , "Magic wand" , "Normal Arrow" , "Sword" , "No Weapon"};
    int vaz = Dast;
    if(vaz == -1){vaz = 5;}
    while (1){
        for (int i = 0; i < 6; i++){
            if (vaz == i){
                attron(A_REVERSE);
            }
            mvprintw(17 + 2*i, 45 , "%s", choice[i]);
            if(i == 0){
                mvprintw(17 + 2*i , 65 , "Short-Range");
                mvprintw(17 + 2*i , 85 , "5");
                mvprintw(17 + 2*i , 105 , "1");
                mvprintw(17 + 2*i , 125 , "%d" , pl->aslahe[0]);
            }else if(i == 1){
                mvprintw(17 + 2*i , 65 , "Long-Range");
                mvprintw(17 + 2*i , 85 , "12");
                mvprintw(17 + 2*i , 105 , "5");
                mvprintw(17 + 2*i , 125 , "%d" , pl->aslahe[1]);
            }else if(i == 2){
                mvprintw(17 + 2*i , 65 , "Long-Range");
                mvprintw(17 + 2*i , 85 , "15");
                mvprintw(17 + 2*i , 105 , "10");
                mvprintw(17 + 2*i , 125 , "%d" , pl->aslahe[2]);
            }else if(i == 3){
                mvprintw(17 + 2*i , 65 , "Long-Range");
                mvprintw(17 + 2*i , 85 , "5");
                mvprintw(17 + 2*i , 105 , "5");
                mvprintw(17 + 2*i , 125 , "%d" , pl->aslahe[3]);
            }else if(i == 4){
                mvprintw(17 + 2*i , 65 , "Short-Range");
                mvprintw(17 + 2*i , 85 , "10");
                mvprintw(17 + 2*i , 105 , "1");
                mvprintw(17 + 2*i , 125 , "%d" , pl->aslahe[4]);
            }else{
            }
            if (vaz == i){
                attroff(A_REVERSE);
            }
        }
        int ch = getch();
        if (ch == KEY_UP){
            if(vaz != 0){
                vaz --;
            }
        }else if(ch == KEY_DOWN){
            if(vaz != 5){
                vaz++;
            }
        }else if (ch == '\n'){
            break;
        }
    }
    if(vaz == 0){//Mace
        if(pl->aslahe[0] == 0){
            return -1;
        }
        return 0;
    }else if(vaz == 1){//Dagger
        if(pl->aslahe[1] == 0){
            return -1;
        }
        return 1;
    }else if(vaz == 2){//Magic Wand
        if(pl->aslahe[2] == 0){
            return -1;
        }
        return 2;
    }else if(vaz == 3){//Normal Arrow
        if(pl->aslahe[3] == 0){
            return -1;
        }
        return 3;
    }else if(vaz == 4){//Sword
        if(pl->aslahe[4] == 0){
            return -1;
        }
        return 4;
    }else if(vaz == 5){//No Weapon
        return -1;
    }
}

void food(int otagh , int list[otagh][5] , char bazi[LINES][COLS] , int didan[LINES][COLS] , int ghaza[LINES][COLS]){
    for(int i = 0 ; i < otagh ; i++){
        int tedad = 3;
        while(tedad > 0){
            int r = rand()%6;
            int x_food = rand()%(list[i][2] - 1);
            x_food += list[i][0] + 1;
            int y_food = rand()%(list[i][3] - 1);
            y_food += list[i][1] + 1;
            if(bazi[y_food][x_food] == '.'){
                if(list[i][4] != 1){
                    if(r > 0 && r < 5){//Regular food
                        ghaza[y_food][x_food] = 1;
                    }else if(r == 5){//Strenghy food
                        ghaza[y_food][x_food] = 2;
                    }else{//Speedy food
                        ghaza[y_food][x_food] = 3;
                    }
                    bazi[y_food][x_food] = 'f';      
                    tedad --;
                }else{
                    if(r > 0 && r < 5){//Regular food
                        ghaza[y_food][x_food] = 4;
                    }else if(r == 5){//Strenghy food
                        ghaza[y_food][x_food] = 5;
                    }else{//Speedy food
                        ghaza[y_food][x_food] = 6;
                    }
                    bazi[y_food][x_food] = 'f';      
                    tedad --;
                }
            }
        }
    }
}

int Menufood(Profile *pl){
    clear();
    board();
    init_pair(1 , COLOR_BLUE , COLOR_BLACK);
    init_pair(2 , COLOR_RED , COLOR_BLACK);
    init_pair(3 , COLOR_GREEN , COLOR_BLACK);
    attron(COLOR_PAIR(1));
    mvprintw(10 , 25 , "Choose your food :");
    attroff(COLOR_PAIR(1));
    int vaz = pl->tedadfood;
    while (1){
        for (int i = 0; i < 5; i++){
            if (vaz == i){
                attron(A_REVERSE);
            }
            if(pl->food[i] == 1){
                attron(COLOR_PAIR(3));
                mvprintw(17 + 2*i, 45 , "Regular Food");
                attroff(COLOR_PAIR(3));
            }else if(pl->food[i] == 2){
                attron(COLOR_PAIR(2));
                mvprintw(17 + 2*i, 45 , "Strenghy Food");
                attroff(COLOR_PAIR(2));
            }else if(pl->food[i] == 3){
                attron(COLOR_PAIR(1));
                mvprintw(17 + 2*i, 45 , "Speedy Food");
                attroff(COLOR_PAIR(1));
            }else if(pl->food[i] == 4){//rotten
                mvprintw(17+ 2*i , 45 , "Regular Food");
            }else{
                mvprintw(17 + 2*i , 45 , "Empty");
            }
            if (vaz == i){
                attroff(A_REVERSE);
            }
        }
        int ch = getch();
        if (ch == KEY_UP){
            if(vaz != 0){
                vaz --;
            }
        }else if(ch == KEY_DOWN){
            if(vaz != 4){
                vaz++;
        }
        }else if (ch == '\n'){
            break;
        }
    }
    if(pl->food[vaz] == 1){//regular 
        pl->food[vaz] = 0;
        pl->food_time[vaz] = 0;
        int i = vaz;
        while(i < 4){
            pl->food[i] = pl->food[i+1];
            pl->food_time[i]  = pl->food_time[i+1]; 
            i++;
        }
        pl->food[4] = 0;
        pl->food_time[4] = 0;
        pl->tedadfood--;
        pl->Hunger += 2;
        if(pl->Hunger > 10){
            pl->Hunger = 10;
            pl->HP += 1;
        }
    }else if(pl->food[vaz] == 2){//strenghy
        pl->food[vaz] = 0;
        pl->food_time[vaz] = 0;
        int i = vaz;
        while(i < 4){
            pl->food[i] = pl->food[i+1];
            pl->food_time[i]  = pl->food_time[i+1]; 
            i++;
        }
        pl->food[4] = 0;
        pl->food_time[4] = 0;
        pl->tedadfood--;
        pl->Hunger += 2;
        if(pl->Hunger > 10){
            pl->Hunger = 10;
            pl->HP += 1;
        }
        pl->Strengh = 10;
    }else if(pl->food[vaz] == 3){//speedy
        pl->food[vaz] = 0;
        pl->food_time[vaz] = 0;
        int i = vaz;
        while(i < 4){
            pl->food[i] = pl->food[i+1];
            pl->food_time[i]  = pl->food_time[i+1]; 
            i++;
        }
        pl->food[4] = 0;
        pl->food_time[4] = 0;
        pl->tedadfood--;
        pl->Hunger += 2;
        if(pl->Hunger > 10){
            pl->Hunger = 10;
            pl->HP += 1;
        }
        pl->Speed = 10;
    }else if(pl->food[vaz] == 4){//rotten
        pl->food[vaz] = 0;
        pl->food_time[vaz] = 0;
        int i = vaz;
        while(i < 4){
            pl->food[i] = pl->food[i+1];
            pl->food_time[i]  = pl->food_time[i+1]; 
            i++;
        }
        pl->food[4] = 0;
        pl->food_time[4] = 0;
        pl->tedadfood--;
        pl->Hunger += 2;
        if(pl->Hunger > 10){
            pl->Hunger = 10;
        }
        pl->HP -= 1;
    }else{//empty

    }
}

void monster(int otagh , int list[otagh][5] , char bazi[LINES][COLS] , int didan[LINES][COLS] ,  int joon[LINES][COLS] , Profile *pl){
    for(int i = 0 ; i < otagh ; i++){
        int tedad = pl->diff;
        while(tedad > 0){//4-3-3-2-2-2
            int r = rand()%15;
            int x_monster = rand()%(list[i][2] - 1);
            x_monster += list[i][0] + 1;
            int y_monster = rand()%(list[i][3] - 1);
            y_monster += list[i][1] + 1;
            if(bazi[y_monster][x_monster] == '.'){
                if(r > -1 && r < 5){//Deamon
                    bazi[y_monster][x_monster] = 'd';
                    joon[y_monster][x_monster] = 5;
                }else if(r >= 5 && r < 8){//Fire Breathing Monster
                    bazi[y_monster][x_monster] = 'F';
                    joon[y_monster][x_monster] = 10;
                }else if(r >= 8 && r < 11){//Giant
                    bazi[y_monster][x_monster] = 't';
                    joon[y_monster][x_monster] = 15;
                }else if(r >= 11 && r < 13){//Snake
                    bazi[y_monster][x_monster] = 'S';
                    joon[y_monster][x_monster] = 20;
                }else if(r >= 13 && r < 15){//Undeed
                    bazi[y_monster][x_monster] = 'u';
                    joon[y_monster][x_monster] = 30;
                }
                tedad--;
            }
        }
    }
}

void Menutelesm(Profile *pl){
    clear();
    board();
    init_pair(60 , COLOR_BLUE , COLOR_BLACK);
    init_pair(61 , COLOR_RED , COLOR_BLACK);
    init_pair(62 , COLOR_GREEN , COLOR_BLACK);
    attron(COLOR_PAIR(61));
    mvprintw(10 , 25 , "Choose your Spell :");
    attroff(COLOR_PAIR(61));
    attron(COLOR_PAIR(62));
    mvprintw(13 , 45 , "Name:");
    mvprintw(13 , 65 , "Quantity:");
    attroff(COLOR_PAIR(62));
    char *choice[] = {"Health Spell" , "Speed Spell" , "Damage strengh" , "No Spell"};
    int vaz = 0;
    while (1){
        for (int i = 0; i < 4; i++){
            if (vaz == i){
                attron(A_REVERSE);
            }
            if(i == 0){
                attron(COLOR_PAIR(62));
                mvprintw(17 + 2*i, 45 , "%s", choice[i]);
                mvprintw(17 + 2*i , 65 , "%d" , pl->telesm[0]);
                attroff(COLOR_PAIR(62));
            }
            if(i == 1){
                attron(COLOR_PAIR(60));
                mvprintw(17 + 2*i, 45 , "%s", choice[i]);
                mvprintw(17 + 2*i , 65 , "%d" , pl->telesm[1]);
                attroff(COLOR_PAIR(60));
            }
            if(i == 2){
                attron(COLOR_PAIR(61));
                mvprintw(17 + 2*i, 45 , "%s", choice[i]);
                mvprintw(17 + 2*i , 65 , "%d" , pl->telesm[2]);
                attroff(COLOR_PAIR(61));
            }
            if(i == 3){
                mvprintw(17 + 2*i, 45 , "%s", choice[i]);
            }
            if (vaz == i){
                attroff(A_REVERSE);
            }
        }
        int ch = getch();
        if (ch == KEY_UP){
            if(vaz != 0){
                vaz --;
            }
        }else if(ch == KEY_DOWN){
            if(vaz != 3){
                vaz++;
            }
        }else if (ch == '\n'){
            break;
        }
    }
    if(vaz == 0){//HealthSpell
        if(pl->telesm[0] == 0){
            
        }else{
            pl->reg = 10;
            pl->telesm[0]--;
        }
    }else if(vaz == 2){//StrenghSpell
        if(pl->telesm[2] == 0){
            
        }else{
            pl->Strengh = 10;
            pl->telesm[2]--;
        }
    }else if(vaz == 1){//SpeedSpell
        if(pl->telesm[1] == 0){
            
        }else{
            pl->Speed = 10;
            pl->telesm[1]--;
        }
    }else if(vaz == 3){//NoSpell

    }
}

void telesm(int otagh , int list[otagh][5] , char bazi[LINES][COLS] , int didan[LINES][COLS] , Profile *pl){
    for(int i = 0 ; i < otagh ; i++){
        if(list[i][4] == 2){
            int tedad = 3;
            while(tedad > 0){
                int x_telesm = rand()%(list[i][2] - 1);
                x_telesm += list[i][0] + 1;
                int y_telesm = rand()%(list[i][3] - 1);
                y_telesm += list[i][1] + 1;
                if(bazi[y_telesm][x_telesm] == '.'){
                    int s = rand()%3;
                    if(s == 0){//Health
                        bazi[y_telesm][x_telesm] = '6';
                    }else if(s == 1){//Speed
                        bazi[y_telesm][x_telesm] = '5';
                    }else{//Damage 
                        bazi[y_telesm][x_telesm] = ')';
                    }
                    tedad--;
                }
            }
        }
    }
} 

void check_hunger(Profile *pl){
    if(difftime(now , past_hunger) >= 20){
        time(&past_hunger);
        if(pl->Hunger == 0){
            pl->HP--;
        }else{
            pl->Hunger--;    
        }
    }
}

void check_food(Profile *pl){
    if(difftime(now , past_food) >= 60){
        for(int i = 0 ; i < pl->tedadfood ; i++){
            if(pl->food_time[i] == 1){
                pl->food_time[i] = 0;
                if(pl->food[i] == 1){
                    pl->food[i] = 4;
                }else if(pl->food[i] == 2 || pl->food[i] == 3){
                    pl->food[i] = 1;
                }
            }else{
                pl->food_time[i] = 1;
            }
        }
        time(&past_food);
    }
}

void sedaavazkon(int i){
    Mix_HaltMusic();
    Mix_FreeMusic(music);
    music = NULL;
    if(i == 0){//regular room
        if(musicalan == 0){
            //
        }else if(musicalan == 1){
            music = Mix_LoadMUS("Hitman.mp3");
            Mix_PlayMusic(music , -1);
        }else if(musicalan == 2){
            music = Mix_LoadMUS("Elden.mp3");
            Mix_PlayMusic(music , -1);
        }
    }else if(i == 1){//nightmare
        music = Mix_LoadMUS("nightmare.mp3");
        Mix_PlayMusic(music , -1);
    }else if(i == 2){//ench
        music = Mix_LoadMUS("enchant.mp3");
        Mix_PlayMusic(music , -1);
    }else if(i == 3){//golden
        music = Mix_LoadMUS("bomb.mp3");
        Mix_PlayMusic(music , -1);
    }else if(i == 20){//masir
        if(musicalan == 0){
            //
        }else if(musicalan == 1){
            music = Mix_LoadMUS("Hitman.mp3");
            Mix_PlayMusic(music , -1);
        }else if(musicalan == 2){
            music = Mix_LoadMUS("Elden.mp3");
            Mix_PlayMusic(music , -1);
        }
    }
}

void atraf(Profile *pl , int otagh , int list[otagh][5] , char bazi[LINES][COLS] , int donbal[LINES][COLS]){
    int ja = koodoom(pl->pos.x , pl->pos.y , otagh , list);
    if(ja == 20){

    }else{
        for(int i = -1 ; i < 2 ; i++){
            for(int j = -1 ; j < 2 ; j++){
                if(bazi[pl->pos.y + i][pl->pos.y + j] == 'u' || bazi[pl->pos.y + i][pl->pos.y + j] == 't'){
                    if(donbal[pl->pos.y + i][pl->pos.y + j] == 0){
                        donbal[pl->pos.y + i][pl->pos.y + j] = 5;
                    }
                }
            }
        }
    }
}

void check_ench(Profile *pl){
    if(difftime(now , past_enchant) >= 10){
        pl->HP--;
        time(&past_enchant);
    }
}

void check_heal(Profile *pl){
    if(difftime(now , past_heal) >= 10){
        time(&past_heal);
        if(pl->Hunger == 10){
            pl->HP++;
            if(pl->reg > 0){
                pl->reg --;
                pl->HP++;
            }
        }
    } 
}

void zarbeh(Profile *pl , int range , int taraf , char bazi[LINES][COLS] , int joon[LINES][COLS] , int donbal[LINES][COLS] , int oftadeh[LINES][COLS]){
    init_pair(70 , COLOR_RED , COLOR_BLACK);
    attron(COLOR_PAIR(70));
    if(pl->Dast == 0){//Mace
        for(int i = -1 ; i < 2 ; i++){
            for(int j = -1 ; j < 2 ; j++){
                char c = bazi[pl->pos.y+ i][pl->pos.x + j]; 
                if(c == 'd' || c == 'F' || c == 't' || c == 'S' || c == 'u'){
                    timeout(-1);
                    int o = 1;
                    if(pl->Strengh > 0){
                        o++;
                    }
                    if(joon[pl->pos.y+ i][pl->pos.x + j] <= 5 * o){
                        joon[pl->pos.y+ i][pl->pos.x + j] = 0;
                        bazi[pl->pos.y+ i][pl->pos.x + j] = '.';
                        mvprintw(2 , 5 , "You have killed a Monster!");
                        donbal[pl->pos.y+ i][pl->pos.x + j] = 0;
                    }else{
                        joon[pl->pos.y+ i][pl->pos.x + j] -= 5 * o;
                        mvprintw(2 , 5 , "You have hit a Monster!");
                    }
                    getch();
                    timeout(0);
                }
            }
        }
    }else if(pl->Dast == 1){//Dagger
        int y = pl->pos.y;
        int x = pl->pos.x; 
        for(int i = 1 ; i <= range ; i++){
            if(taraf == 0){//U
                y--;
                char c = bazi[y][x]; 
                if(c == 'd' || c == 'F' || c == 't' || c == 'S' || c == 'u'){
                    timeout(-1);
                    int o = 1;
                    if(pl->Strengh > 0){
                        o++;
                    }
                    if(joon[y][x] <= 12 * o){
                        joon[y][x] = 0;
                        bazi[y][x] = '.';
                        mvprintw(2 , 5 , "You have killed a Monster!");
                        donbal[y][x] = 0;
                    }else{
                        joon[y][x] -= 12 * o;
                        mvprintw(2 , 5 , "You have hit a Monster!");
                    }
                    pl->aslahe[1]--;
                    i = range+1;
                    getch();
                    timeout(0);
                }else if(c == '.'){
                    if(i == range){
                        pl->aslahe[1]--;
                        bazi[y][x] = '1';
                        oftadeh[y][x] = 1;
                    }
                }else{
                    if(i == 1){

                    }else{
                        pl->aslahe[1]--;
                        bazi[y+1][x] = '1';
                        oftadeh[y+1][x] = 1;
                    }
                    i = range+1;
                }
            }else if(taraf == 1){//D
                y++;
                char c = bazi[y][x]; 
                if(c == 'd' || c == 'F' || c == 't' || c == 'S' || c == 'u'){
                    timeout(-1);
                    int o = 1;
                    if(pl->Strengh > 0){
                        o++;
                    }
                    if(joon[y][x] <= 12 * o){
                        joon[y][x] = 0;
                        bazi[y][x] = '.';
                        mvprintw(2 , 5 , "You have killed a Monster!");
                        donbal[y][x] = 0;
                    }else{
                        joon[y][x] -= 12 * o;
                        mvprintw(2 , 5 , "You have hit a Monster!");
                    }
                    pl->aslahe[1]--;
                    i = range+1;
                    getch();
                    timeout(0);
                }else if(c == '.'){
                    if(i == range){
                        pl->aslahe[1]--;
                        bazi[y][x] = '1';
                        oftadeh[y][x] = 1;
                    }
                }else{
                    if(i == 1){

                    }else{
                        pl->aslahe[1]--;
                        bazi[y-1][x] = '1';
                        oftadeh[y-1][x] = 1;
                    }
                    i = range+1;
                }
            }else if(taraf == 2){//R
                x++;
                char c = bazi[y][x]; 
                if(c == 'd' || c == 'F' || c == 't' || c == 'S' || c == 'u'){
                    timeout(-1);
                    int o = 1;
                    if(pl->Strengh > 0){
                        o++;
                    }
                    if(joon[y][x] <= 12 * o){
                        joon[y][x] = 0;
                        bazi[y][x] = '.';
                        mvprintw(2 , 5 , "You have killed a Monster!");
                        donbal[y][x] = 0;
                    }else{
                        joon[y][x] -= 12 * o;
                        mvprintw(2 , 5 , "You have hit a Monster!");
                    }
                    pl->aslahe[1]--;
                    i = range+1;
                    getch();
                    timeout(0);
                }else if(c == '.'){
                    if(i == range){
                        pl->aslahe[1]--;
                        bazi[y][x] = '1';
                        oftadeh[y][x] = 1;
                    }
                }else{
                    if(i == 1){

                    }else{
                        pl->aslahe[1]--;
                        bazi[y][x-1] = '1';
                        oftadeh[y][x-1] = 1;
                    }
                    i = range+1;
                }
            }else if(taraf == 3){//L
                x--;
                char c = bazi[y][x]; 
                if(c == 'd' || c == 'F' || c == 't' || c == 'S' || c == 'u'){
                    timeout(-1);
                    int o = 1;
                    if(pl->Strengh > 0){
                        o++;
                    }
                    if(joon[y][x] <= 12 * o){
                        joon[y][x] = 0;
                        bazi[y][x] = '.';
                        mvprintw(2 , 5 , "You have killed a Monster!");
                        donbal[y][x] = 0;
                    }else{
                        joon[y][x] -= 12 * o;
                        mvprintw(2 , 5 , "You have hit a Monster!");
                    }
                    pl->aslahe[1]--;
                    i = range+1;
                    getch();
                    timeout(0);
                }else if(c == '.'){
                    if(i == range){
                        pl->aslahe[1]--;
                        bazi[y][x] = '1';
                        oftadeh[y][x] = 1;
                    }
                }else{
                    if(i == 1){

                    }else{
                        pl->aslahe[1]--;
                        bazi[y][x+1] = '1';
                        oftadeh[y][x+1] = 1;
                    }
                    i = range+1;
                }
            }
        }
    }else if(pl->Dast == 2){//Magic Wand
        int y = pl->pos.y;
        int x = pl->pos.x; 
        for(int i = 1 ; i <= range ; i++){
            if(taraf == 0){//U
                y--;
                char c = bazi[y][x]; 
                if(c == 'd' || c == 'F' || c == 't' || c == 'S' || c == 'u'){
                    timeout(-1);
                    int o = 1;
                    if(pl->Strengh > 0){
                        o++;
                    }
                    if(joon[y][x] <= 15 * o){
                        joon[y][x] = 0;
                        bazi[y][x] = '.';
                        mvprintw(2 , 5 , "You have killed a Monster!");
                        donbal[y][x] = 0;
                    }else{
                        joon[y][x] -= 15 * o;
                        mvprintw(2 , 5 , "You have hit a Monster!");
                        donbal[y][x] = 0;
                    }
                    pl->aslahe[2]--;
                    i = range+1;
                    getch();
                    timeout(0);
                }else if(c == '.'){
                    if(i == range){
                        pl->aslahe[2]--;
                        bazi[y][x] = '2';
                        oftadeh[y][x] = 1;
                    }
                }else{
                    if(i == 1){

                    }else{
                        pl->aslahe[2]--;
                        bazi[y+1][x] = '2';
                        oftadeh[y+1][x] = 1;
                    }
                    i = range+1;
                }
            }else if(taraf == 1){//D
                y++;
                char c = bazi[y][x]; 
                if(c == 'd' || c == 'F' || c == 't' || c == 'S' || c == 'u'){
                    timeout(-1);
                    int o = 1;
                    if(pl->Strengh > 0){
                        o++;
                    }
                    if(joon[y][x] <= 15 * o){
                        joon[y][x] = 0;
                        bazi[y][x] = '.';
                        mvprintw(2 , 5 , "You have killed a Monster!");
                        donbal[y][x] = 0;
                    }else{
                        joon[y][x] -= 15 * o;
                        mvprintw(2 , 5 , "You have hit a Monster!");
                        donbal[y][x] = 0;
                    }
                    pl->aslahe[2]--;
                    i = range+1;
                    getch();
                    timeout(0);
                }else if(c == '.'){
                    if(i == range){
                        pl->aslahe[2]--;
                        bazi[y][x] = '2';
                        oftadeh[y][x] = 1;
                    }
                }else{
                    if(i == 1){

                    }else{
                        pl->aslahe[2]--;
                        bazi[y-1][x] = '2';
                        oftadeh[y-1][x] = 1;
                    }
                    i = range+1;
                }
            }else if(taraf == 2){//R
                x++;
                char c = bazi[y][x]; 
                if(c == 'd' || c == 'F' || c == 't' || c == 'S' || c == 'u'){
                    timeout(-1);
                    int o = 1;
                    if(pl->Strengh > 0){
                        o++;
                    }
                    if(joon[y][x] <= 15 * o){
                        joon[y][x] = 0;
                        bazi[y][x] = '.';
                        mvprintw(2 , 5 , "You have killed a Monster!");
                        donbal[y][x] = 0;
                    }else{
                        joon[y][x] -= 15 * o;
                        mvprintw(2 , 5 , "You have hit a Monster!");
                        donbal[y][x] = 0;
                    }
                    pl->aslahe[2]--;
                    i = range+1;
                    getch();
                    timeout(0);
                }else if(c == '.'){
                    if(i == range){
                        pl->aslahe[2]--;
                        bazi[y][x] = '2';
                        oftadeh[y][x] = 1;
                    }
                }else{
                    if(i == 1){

                    }else{
                        pl->aslahe[2]--;
                        bazi[y][x-1] = '2';
                        oftadeh[y][x-1] = 1;
                    }
                    i = range+1;
                }
            }else if(taraf == 3){//L
                x--;
                char c = bazi[y][x]; 
                if(c == 'd' || c == 'F' || c == 't' || c == 'S' || c == 'u'){
                    timeout(-1);
                    int o = 1;
                    if(pl->Strengh > 0){
                        o++;
                    }
                    if(joon[y][x] <= 15 * o){
                        joon[y][x] = 0;
                        bazi[y][x] = '.';
                        mvprintw(2 , 5 , "You have killed a Monster!");
                        donbal[y][x] = 0;
                    }else{
                        joon[y][x] -= 15 * o;
                        mvprintw(2 , 5 , "You have hit a Monster!");
                        donbal[y][x] = 0;
                    }
                    pl->aslahe[2]--;
                    i = range+1;
                    getch();
                    timeout(0);
                }else if(c == '.'){
                    if(i == range){
                        pl->aslahe[2]--;
                        bazi[y][x] = '2';
                        oftadeh[y][x] = 1;
                    }
                }else{
                    if(i == 1){

                    }else{
                        pl->aslahe[2]--;
                        bazi[y][x+1] = '2';
                        oftadeh[y][x+1] = 1;
                    }
                    i = range+1;
                }
            }
        }
    }else if(pl->Dast == 3){//Normal Arrow
        int y = pl->pos.y;
        int x = pl->pos.x; 
        for(int i = 1 ; i <= range ; i++){
            if(taraf == 0){//U
                y--;
                char c = bazi[y][x]; 
                if(c == 'd' || c == 'F' || c == 't' || c == 'S' || c == 'u'){
                    timeout(-1);
                    int o = 1;
                    if(pl->Strengh > 0){
                        o++;
                    }
                    if(joon[y][x] <= 5 * o){
                        joon[y][x] = 0;
                        bazi[y][x] = '.';
                        mvprintw(2 , 5 , "You have killed a Monster!");
                        donbal[y][x] = 0;
                    }else{
                        joon[y][x] -= 5 * o;
                        mvprintw(2 , 5 , "You have hit a Monster!");
                    }
                    pl->aslahe[3]--;
                    i = range+1;
                    getch();
                    timeout(0);
                }else if(c == '.'){
                    if(i == range){
                        pl->aslahe[3]--;
                        bazi[y][x] = '3';
                        oftadeh[y][x] = 1;
                    }
                }else{
                    if(i == 1){

                    }else{
                        pl->aslahe[3]--;
                        bazi[y+1][x] = '3';
                        oftadeh[y+1][x] = 1;
                    }
                    i = range+1;
                }
            }else if(taraf == 1){//D
                y++;
                char c = bazi[y][x]; 
                if(c == 'd' || c == 'F' || c == 't' || c == 'S' || c == 'u'){
                    timeout(-1);
                    int o = 1;
                    if(pl->Strengh > 0){
                        o++;
                    }
                    if(joon[y][x] <= 5 * o){
                        joon[y][x] = 0;
                        bazi[y][x] = '.';
                        mvprintw(2 , 5 , "You have killed a Monster!");
                        donbal[y][x] = 0;
                    }else{
                        joon[y][x] -= 5 * o;
                        mvprintw(2 , 5 , "You have hit a Monster!");
                    }
                    pl->aslahe[3]--;
                    i = range+1;
                    getch();
                    timeout(0);
                }else if(c == '.'){
                    if(i == range){
                        pl->aslahe[3]--;
                        bazi[y][x] = '3';
                        oftadeh[y][x] = 1;
                    }
                }else{
                    if(i == 1){

                    }else{
                        pl->aslahe[3]--;
                        bazi[y-1][x] = '3';
                        oftadeh[y-1][x] = 1;
                    }
                    i = range+1;
                }
            }else if(taraf == 2){//R
                x++;
                char c = bazi[y][x]; 
                if(c == 'd' || c == 'F' || c == 't' || c == 'S' || c == 'u'){
                    timeout(-1);
                    int o = 1;
                    if(pl->Strengh > 0){
                        o++;
                    }
                    if(joon[y][x] <= 5 * o){
                        joon[y][x] = 0;
                        bazi[y][x] = '.';
                        mvprintw(2 , 5 , "You have killed a Monster!");
                        donbal[y][x] = 0;
                    }else{
                        joon[y][x] -= 5 * o;
                        mvprintw(2 , 5 , "You have hit a Monster!");
                    }
                    pl->aslahe[3]--;
                    i = range+1;
                    getch();
                    timeout(0);
                }else if(c == '.'){
                    if(i == range){
                        pl->aslahe[3]--;
                        bazi[y][x] = '3';
                        oftadeh[y][x] = 1;
                    }
                }else{
                    if(i == 1){

                    }else{
                        pl->aslahe[3]--;
                        bazi[y][x-1] = '3';
                        oftadeh[y][x-1] = 1;
                    }
                    i = range+1;
                }
            }else if(taraf == 3){//L
                x--;
                char c = bazi[y][x]; 
                if(c == 'd' || c == 'F' || c == 't' || c == 'S' || c == 'u'){
                    timeout(-1);
                    int o = 1;
                    if(pl->Strengh > 0){
                        o++;
                    }
                    if(joon[y][x] <= 5 * o){
                        joon[y][x] = 0;
                        bazi[y][x] = '.';
                        mvprintw(2 , 5 , "You have killed a Monster!");
                        donbal[y][x] = 0;
                    }else{
                        joon[y][x] -= 5 * o;
                        mvprintw(2 , 5 , "You have hit a Monster!");
                    }
                    pl->aslahe[1]--;
                    i = range+1;
                    getch();
                    timeout(0);
                }else if(c == '.'){
                    if(i == range){
                        pl->aslahe[3]--;
                        bazi[y][x] = '3';
                        oftadeh[y][x] = 1;
                    }
                }else{
                    if(i == 1){

                    }else{
                        pl->aslahe[3]--;
                        bazi[y][x+1] = '3';
                        oftadeh[y][x+1] = 1;
                    }
                    i = range+1;
                }
            }
        }
    }else if(pl->Dast == 4){//Sword
        for(int i = -1 ; i < 2 ; i++){
            for(int j = -1 ; j < 2 ; j++){
                char c = bazi[pl->pos.y+ i][pl->pos.x + j]; 
                if(c == 'd' || c == 'F' || c == 't' || c == 'S' || c == 'u'){
                    timeout(-1);
                    int o = 1;
                    if(pl->Strengh > 0){
                        o++;
                        pl->Strengh--;
                    }
                    if(joon[pl->pos.y+ i][pl->pos.x + j] <= 10 * o){
                        joon[pl->pos.y+ i][pl->pos.x + j] = 0;
                        bazi[pl->pos.y+ i][pl->pos.x + j] = '.';
                        mvprintw(2 , 5 , "You have killed a Monster!");
                        donbal[pl->pos.y+ i][pl->pos.x + j] = 0;
                    }else{
                        joon[pl->pos.y+ i][pl->pos.x + j] -= 10 * o;
                        mvprintw(2 , 5 , "You have hit a Monster!");
                    }
                    getch();
                    timeout(0);
                }
            }
        }
    }
    attroff(COLOR_PAIR(70));
}

void Musicmenu(Profile *pl){
    clear();
    board();
    int z = COLS/2;
    mvprintw(13 , z-10 , "Choose your Music :");
    char *choice[] = {"No Music (default)" , "Hitman" , "Elden Ring"};
    int vaz = 0;
    while (1){
        for (int i = 0; i < 3; i++){
            if (vaz == i){
                attron(A_REVERSE);
            }
            mvprintw(15 + 2*i, z - 10, "%s", choice[i]);
            if (vaz == i){
                attroff(A_REVERSE);
            }
        }
        int ch = getch();
        if (ch == KEY_UP){
            if(vaz != 0){
                vaz --;
            }
        }else if(ch == KEY_DOWN){
            if(vaz != 2){
                vaz++;
            }
        }else if (ch == '\n'){
            break;
        }
    }
    if(vaz == 0){//No Music
        Mix_HaltMusic();
        Mix_FreeMusic(music);
        music = NULL;
        musicalan = 0;
    }else if(vaz == 1){//Hitman
        music = Mix_LoadMUS("Hitman.mp3");
        Mix_PlayMusic(music , -1);
        musicalan = 1;
    }else if(vaz == 2){//Elden ring
        music = Mix_LoadMUS("Elden.mp3");
        Mix_PlayMusic(music , -1);
        musicalan = 2;
    }
    Setting(pl);
}

void Save(Profile *pl){
    FILE * p;
    char path[1000];
    strcpy(path , pl->Name);
    strcat(path , "save.txt");
    p = fopen(path , "w");
    fprintf(p , "%d\n" , pl->score);
    fprintf(p , "%d\n" , pl->gold);
    fprintf(p , "%d\n" , pl->tedad);
    fprintf(p , "%d\n" , pl->HP);
    fprintf(p , "%d\n" , pl->diff);
    fprintf(p , "%d\n" , pl->color);
    for(int i = 0 ; i < 5 ; i++){
        fprintf(p , "%d\n" , pl->aslahe[i]);    
    }
    fprintf(p , "%d\n" , pl->Dast);
    fprintf(p , "%d\n" , pl->tedadfood);
    for(int i = 0 ; i < 5 ; i++){
        fprintf(p , "%d\n" , pl->food[i]);    
    }
    for(int i = 0 ; i < 5 ; i++){
        fprintf(p , "%d\n" , pl->food_time[i]);    
    }
    for(int i = 0 ; i < 3 ; i++){
        fprintf(p , "%d\n" , pl->telesm[i]);    
    }
    fprintf(p , "%d\n" , pl->Hunger);
    fprintf(p , "%d\n" , pl->Speed);
    fprintf(p , "%d\n" , pl->Strengh);
    fprintf(p , "%d\n" , pl->reg);
    fprintf(p , "%d\n" , pl->floor);
    fprintf(p , "%d\n" , pl->pos.x);
    fprintf(p , "%d\n" , pl->pos.y);
    fprintf(p , "%d\n" , otagh1);
    fprintf(p , "%d\n" , otagh2);
    fprintf(p , "%d\n" , otagh3);
    fprintf(p , "%d\n" , otagh4);
    fprintf(p , "%d\n" , otagh5);
    fprintf(p , "%d\n" , x1);
    fprintf(p , "%d\n" , x2);
    fprintf(p , "%d\n" , x3);
    fprintf(p , "%d\n" , x4);
    fprintf(p , "%d\n" , x5);
    fprintf(p , "%d\n" , y_1);
    fprintf(p , "%d\n" , y_2);
    fprintf(p , "%d\n" , y_3);
    fprintf(p , "%d\n" , y_4);
    fprintf(p , "%d\n" , y_5);
    // COLS = 184 LINES = 45
    for(int i = 0 ; i < 45 ; i++){
        for(int j = 0 ; j < 184 ; j++){
            fprintf(p , "%c\n" , floor1[i][j]);
        }
    }
    for(int i = 0 ; i < 100 ; i++){
        for(int j = 0 ; j < 5 ; j++){
            fprintf(p , "%d\n" , list1[i][j]);
        }
    }
    for(int i = 0 ; i < 45 ; i++){
        for(int j = 0 ; j < 184 ; j++){
            fprintf(p , "%d\n" , didan1[i][j]);
        }
    }
    for(int i = 0 ; i < 45 ; i++){
        for(int j = 0 ; j < 184 ; j++){
            fprintf(p , "%d\n" , value1[i][j]);
        }
    }
    for(int i = 0 ; i < 45 ; i++){
        for(int j = 0 ; j < 184 ; j++){
            fprintf(p , "%d\n" , ghaza1[i][j]);
        }
    }
    for(int i = 0 ; i < 45 ; i++){
        for(int j = 0 ; j < 184 ; j++){
            fprintf(p , "%d\n" , oftadeh1[i][j]);
        }
    }
    for(int i = 0 ; i < 45 ; i++){
        for(int j = 0 ; j < 184 ; j++){
            fprintf(p , "%d\n" , joon1[i][j]);
        }
    }
    for(int i = 0 ; i < 45 ; i++){
        for(int j = 0 ; j < 184 ; j++){
            fprintf(p , "%d\n" , donbal1[i][j]);
        }
    }
    for(int i = 0 ; i < 45 ; i++){
        for(int j = 0 ; j < 184 ; j++){
            fprintf(p , "%c\n" , floor2[i][j]);
        }
    }
    for(int i = 0 ; i < 100 ; i++){
        for(int j = 0 ; j < 5 ; j++){
            fprintf(p , "%d\n" , list2[i][j]);
        }
    }
    for(int i = 0 ; i < 45 ; i++){
        for(int j = 0 ; j < 184 ; j++){
            fprintf(p , "%d\n" , didan2[i][j]);
        }
    }
    for(int i = 0 ; i < 45 ; i++){
        for(int j = 0 ; j < 184 ; j++){
            fprintf(p , "%d\n" , value2[i][j]);
        }
    }
    for(int i = 0 ; i < 45 ; i++){
        for(int j = 0 ; j < 184 ; j++){
            fprintf(p , "%d\n" , ghaza2[i][j]);
        }
    }
    for(int i = 0 ; i < 45 ; i++){
        for(int j = 0 ; j < 184 ; j++){
            fprintf(p , "%d\n" , oftadeh2[i][j]);
        }
    }
    for(int i = 0 ; i < 45 ; i++){
        for(int j = 0 ; j < 184 ; j++){
            fprintf(p , "%d\n" , joon2[i][j]);
        }
    }
    for(int i = 0 ; i < 45 ; i++){
        for(int j = 0 ; j < 184 ; j++){
            fprintf(p , "%d\n" , donbal2[i][j]);
        }
    }
    for(int i = 0 ; i < 45 ; i++){
        for(int j = 0 ; j < 184 ; j++){
            fprintf(p , "%c\n" , floor3[i][j]);
        }
    }
    for(int i = 0 ; i < 100 ; i++){
        for(int j = 0 ; j < 5 ; j++){
            fprintf(p , "%d\n" , list3[i][j]);
        }
    }
    for(int i = 0 ; i < 45 ; i++){
        for(int j = 0 ; j < 184 ; j++){
            fprintf(p , "%d\n" , didan3[i][j]);
        }
    }
    for(int i = 0 ; i < 45 ; i++){
        for(int j = 0 ; j < 184 ; j++){
            fprintf(p , "%d\n" , value3[i][j]);
        }
    }
    for(int i = 0 ; i < 45 ; i++){
        for(int j = 0 ; j < 184 ; j++){
            fprintf(p , "%d\n" , ghaza3[i][j]);
        }
    }
    for(int i = 0 ; i < 45 ; i++){
        for(int j = 0 ; j < 184 ; j++){
            fprintf(p , "%d\n" , oftadeh3[i][j]);
        }
    }
    for(int i = 0 ; i < 45 ; i++){
        for(int j = 0 ; j < 184 ; j++){
            fprintf(p , "%d\n" , joon3[i][j]);
        }
    }
    for(int i = 0 ; i < 45 ; i++){
        for(int j = 0 ; j < 184 ; j++){
            fprintf(p , "%d\n" , donbal3[i][j]);
        }
    }
    for(int i = 0 ; i < 45 ; i++){
        for(int j = 0 ; j < 184 ; j++){
            fprintf(p , "%c\n" , floor4[i][j]);
        }
    }
    for(int i = 0 ; i < 100 ; i++){
        for(int j = 0 ; j < 5 ; j++){
            fprintf(p , "%d\n" , list4[i][j]);
        }
    }
    for(int i = 0 ; i < 45 ; i++){
        for(int j = 0 ; j < 184 ; j++){
            fprintf(p , "%d\n" , didan4[i][j]);
        }
    }
    for(int i = 0 ; i < 45 ; i++){
        for(int j = 0 ; j < 184 ; j++){
            fprintf(p , "%d\n" , value4[i][j]);
        }
    }
    for(int i = 0 ; i < 45 ; i++){
        for(int j = 0 ; j < 184 ; j++){
            fprintf(p , "%d\n" , ghaza4[i][j]);
        }
    }
    for(int i = 0 ; i < 45 ; i++){
        for(int j = 0 ; j < 184 ; j++){
            fprintf(p , "%d\n" , oftadeh4[i][j]);
        }
    }
    for(int i = 0 ; i < 45 ; i++){
        for(int j = 0 ; j < 184 ; j++){
            fprintf(p , "%d\n" , joon4[i][j]);
        }
    }
    for(int i = 0 ; i < 45 ; i++){
        for(int j = 0 ; j < 184 ; j++){
            fprintf(p , "%d\n" , donbal4[i][j]);
        }
    }
    for(int i = 0 ; i < 45 ; i++){
        for(int j = 0 ; j < 184 ; j++){
            fprintf(p , "%c\n" , floor5[i][j]);
        }
    }
    for(int i = 0 ; i < 100 ; i++){
        for(int j = 0 ; j < 5 ; j++){
            fprintf(p , "%d\n" , list5[i][j]);
        }
    }
    for(int i = 0 ; i < 45 ; i++){
        for(int j = 0 ; j < 184 ; j++){
            fprintf(p , "%d\n" , didan5[i][j]);
        }
    }
    for(int i = 0 ; i < 45 ; i++){
        for(int j = 0 ; j < 184 ; j++){
            fprintf(p , "%d\n" , value5[i][j]);
        }
    }
    for(int i = 0 ; i < 45 ; i++){
        for(int j = 0 ; j < 184 ; j++){
            fprintf(p , "%d\n" , ghaza5[i][j]);
        }
    }
    for(int i = 0 ; i < 45 ; i++){
        for(int j = 0 ; j < 184 ; j++){
            fprintf(p , "%d\n" , oftadeh5[i][j]);
        }
    }
    for(int i = 0 ; i < 45 ; i++){
        for(int j = 0 ; j < 184 ; j++){
            fprintf(p , "%d\n" , joon5[i][j]);
        }
    }
    for(int i = 0 ; i < 45 ; i++){
        for(int j = 0 ; j < 184 ; j++){
            fprintf(p , "%d\n" , donbal5[i][j]);
        }
    }
    fclose(p);
}

void ziba(char *c){
    int u = strlen(c);
    while(c[u-1] == '\r' || c[u-1] == '\n'){
        u--;
        c[u] = '\0'; 
    }
}

int chabenam(char c[300]){
    int sum = 0;
    int u = strlen(c);
    for(int i = 0 ; i < u ; i++){
        sum *= 10;
        sum += (c[i] - '0');
    }
    return sum;
}

int loadkon(Profile *pl){
    FILE * p;
    char path[1000];
    strcpy(path , pl->Name);
    strcat(path , "save.txt");
    p = fopen(path , "r");
    if(p == NULL){
        return -1;
    }else{
        char c[300];
        fgets(c , 300 , p);
        ziba(c);
        pl->score = chabenam(c);
        fgets(c , 300 , p);
        ziba(c);
        pl->gold = chabenam(c);
        fgets(c , 300 , p);
        ziba(c);
        pl->tedad = chabenam(c);
        fgets(c , 300 , p);
        ziba(c);
        pl->HP = chabenam(c);
        fgets(c , 300 , p);
        ziba(c);
        pl->diff = chabenam(c);
        fgets(c , 300 , p);
        ziba(c);
        pl->color = chabenam(c);
        for(int i = 0 ; i < 5 ; i++){
            fgets(c , 300 , p);
            ziba(c);
            pl->aslahe[i] = chabenam(c);    
        }
        fgets(c , 300 , p);
        ziba(c);
        pl->Dast = chabenam(c);
        fgets(c , 300 , p);
        ziba(c);
        pl->tedadfood = chabenam(c);
        for(int i = 0 ; i < 5 ; i++){
            fgets(c , 300 , p);
            ziba(c);
            pl->food[i] = chabenam(c);    
        }
        for(int i = 0 ; i < 5 ; i++){
            fgets(c , 300 , p);
            ziba(c);
            pl->food_time[i] = chabenam(c);    
        }
        for(int i = 0 ; i < 3 ; i++){
            fgets(c , 300 , p);
            ziba(c);
            pl->telesm[i] = chabenam(c);    
        }
        fgets(c , 300 , p);
        ziba(c);
        pl->Hunger = chabenam(c);
        fgets(c , 300 , p);
        ziba(c);
        pl->Speed = chabenam(c);
        fgets(c , 300 , p);
        ziba(c);
        pl->Strengh = chabenam(c);
        fgets(c , 300 , p);
        ziba(c);
        pl->reg = chabenam(c);
        fgets(c , 300 , p);
        ziba(c);
        pl->floor = chabenam(c);
        fgets(c , 300 , p);
        ziba(c);
        pl->pos.x = chabenam(c);
        fgets(c , 300 , p);
        ziba(c);
        pl->pos.y = chabenam(c);
        fgets(c , 300 , p);
        ziba(c);
        otagh1 = chabenam(c);
        fgets(c , 300 , p);
        ziba(c);
        otagh2 = chabenam(c);
        fgets(c , 300 , p);
        ziba(c);
        otagh3 = chabenam(c);
        fgets(c , 300 , p);
        ziba(c);
        otagh4 = chabenam(c);
        fgets(c , 300 , p);
        ziba(c);
        otagh5 = chabenam(c);
        fgets(c , 300 , p);
        ziba(c);
        x1 = chabenam(c);
        fgets(c , 300 , p);
        ziba(c);
        x2 = chabenam(c);
        fgets(c , 300 , p);
        ziba(c);
        x3 = chabenam(c);
        fgets(c , 300 , p);
        ziba(c);
        x4 = chabenam(c);
        fgets(c , 300 , p);
        ziba(c);
        x5 = chabenam(c);
        fgets(c , 300 , p);
        ziba(c);
        y_1 = chabenam(c);
        fgets(c , 300 , p);
        ziba(c);
        y_2 = chabenam(c);
        fgets(c , 300 , p);
        ziba(c);
        y_3 = chabenam(c);
        fgets(c , 300 , p);
        ziba(c);
        y_4 = chabenam(c);
        fgets(c , 300 , p);
        ziba(c);
        y_5 = chabenam(c);
        // COLS = 184 LINES = 45
        for(int i = 0 ; i < 45 ; i++){
            for(int j = 0 ; j < 184 ; j++){
                fgets(c , 300 , p);
                ziba(c);
                floor1[i][j] = c[0];
            }
        }
        for(int i = 0 ; i < 100 ; i++){
            for(int j = 0 ; j < 5 ; j++){
                fgets(c , 300 , p);
                ziba(c);
                list1[i][j] = chabenam(c);
            }
        }
        for(int i = 0 ; i < 45 ; i++){
            for(int j = 0 ; j < 184 ; j++){
                fgets(c , 300 , p);
                ziba(c);
                didan1[i][j] = chabenam(c);
            }
        }
        for(int i = 0 ; i < 45 ; i++){
            for(int j = 0 ; j < 184 ; j++){
                fgets(c , 300 , p);
                ziba(c);
                value1[i][j] = chabenam(c);
            }
        }
        for(int i = 0 ; i < 45 ; i++){
            for(int j = 0 ; j < 184 ; j++){
                fgets(c , 300 , p);
                ziba(c);
                ghaza1[i][j] = chabenam(c);
            }
        }
        for(int i = 0 ; i < 45 ; i++){
            for(int j = 0 ; j < 184 ; j++){
                fgets(c , 300 , p);
                ziba(c);
                oftadeh1[i][j] = chabenam(c);
            }
        }
        for(int i = 0 ; i < 45 ; i++){
            for(int j = 0 ; j < 184 ; j++){
                fgets(c , 300 , p);
                ziba(c);
                joon1[i][j] = chabenam(c);
            }
        }
        for(int i = 0 ; i < 45 ; i++){
            for(int j = 0 ; j < 184 ; j++){
                fgets(c , 300 , p);
                ziba(c);
                donbal1[i][j] = chabenam(c);
            }
        }
        for(int i = 0 ; i < 45 ; i++){
            for(int j = 0 ; j < 184 ; j++){
                fgets(c , 300 , p);
                ziba(c);
                floor2[i][j] = c[0];
            }
        }
        for(int i = 0 ; i < 100 ; i++){
            for(int j = 0 ; j < 5 ; j++){
                fgets(c , 300 , p);
                ziba(c);
                list2[i][j] = chabenam(c);
            }
        }
        for(int i = 0 ; i < 45 ; i++){
            for(int j = 0 ; j < 184 ; j++){
                fgets(c , 300 , p);
                ziba(c);
                didan2[i][j] = chabenam(c);
            }
        }
        for(int i = 0 ; i < 45 ; i++){
            for(int j = 0 ; j < 184 ; j++){
                fgets(c , 300 , p);
                ziba(c);
                value2[i][j] = chabenam(c);
            }
        }
        for(int i = 0 ; i < 45 ; i++){
            for(int j = 0 ; j < 184 ; j++){
                fgets(c , 300 , p);
                ziba(c);
                ghaza2[i][j] = chabenam(c);
            }
        }
        for(int i = 0 ; i < 45 ; i++){
            for(int j = 0 ; j < 184 ; j++){
                fgets(c , 300 , p);
                ziba(c);
                oftadeh2[i][j] = chabenam(c);
            }
        }
        for(int i = 0 ; i < 45 ; i++){
            for(int j = 0 ; j < 184 ; j++){
                fgets(c , 300 , p);
                ziba(c);
                joon2[i][j] = chabenam(c);
            }
        }
        for(int i = 0 ; i < 45 ; i++){
            for(int j = 0 ; j < 184 ; j++){
                fgets(c , 300 , p);
                ziba(c);
                donbal2[i][j] = chabenam(c);
            }
        }
        for(int i = 0 ; i < 45 ; i++){
            for(int j = 0 ; j < 184 ; j++){
                fgets(c , 300 , p);
                ziba(c);
                floor3[i][j] = c[0];
            }
        }
        for(int i = 0 ; i < 100 ; i++){
            for(int j = 0 ; j < 5 ; j++){
                fgets(c , 300 , p);
                ziba(c);
                list3[i][j] = chabenam(c);
            }
        }
        for(int i = 0 ; i < 45 ; i++){
            for(int j = 0 ; j < 184 ; j++){
                fgets(c , 300 , p);
                ziba(c);
                didan3[i][j] = chabenam(c);
            }
        }
        for(int i = 0 ; i < 45 ; i++){
            for(int j = 0 ; j < 184 ; j++){
                fgets(c , 300 , p);
                ziba(c);
                value3[i][j] = chabenam(c);
            }
        }
        for(int i = 0 ; i < 45 ; i++){
            for(int j = 0 ; j < 184 ; j++){
                fgets(c , 300 , p);
                ziba(c);
                ghaza3[i][j] = chabenam(c);
            }
        }
        for(int i = 0 ; i < 45 ; i++){
            for(int j = 0 ; j < 184 ; j++){
                fgets(c , 300 , p);
                ziba(c);
                oftadeh3[i][j] = chabenam(c);
            }
        }
        for(int i = 0 ; i < 45 ; i++){
            for(int j = 0 ; j < 184 ; j++){
                fgets(c , 300 , p);
                ziba(c);
                joon3[i][j] = chabenam(c);
            }
        }
        for(int i = 0 ; i < 45 ; i++){
            for(int j = 0 ; j < 184 ; j++){
                fgets(c , 300 , p);
                ziba(c);
                donbal3[i][j] = chabenam(c);
            }
        }
        for(int i = 0 ; i < 45 ; i++){
            for(int j = 0 ; j < 184 ; j++){
                fgets(c , 300 , p);
                ziba(c);
                floor4[i][j] = c[0];
            }
        }
        for(int i = 0 ; i < 100 ; i++){
            for(int j = 0 ; j < 5 ; j++){
                fgets(c , 300 , p);
                ziba(c);
                list4[i][j] = chabenam(c);
            }
        }
        for(int i = 0 ; i < 45 ; i++){
            for(int j = 0 ; j < 184 ; j++){
                fgets(c , 300 , p);
                ziba(c);
                didan4[i][j] = chabenam(c);
            }
        }
        for(int i = 0 ; i < 45 ; i++){
            for(int j = 0 ; j < 184 ; j++){
                fgets(c , 300 , p);
                ziba(c);
                value4[i][j] = chabenam(c);
            }
        }
        for(int i = 0 ; i < 45 ; i++){
            for(int j = 0 ; j < 184 ; j++){
                fgets(c , 300 , p);
                ziba(c);
                ghaza4[i][j] = chabenam(c);
            }
        }
        for(int i = 0 ; i < 45 ; i++){
            for(int j = 0 ; j < 184 ; j++){
                fgets(c , 300 , p);
                ziba(c);
                oftadeh4[i][j] = chabenam(c);
            }
        }
        for(int i = 0 ; i < 45 ; i++){
            for(int j = 0 ; j < 184 ; j++){
                fgets(c , 300 , p);
                ziba(c);
                joon4[i][j] = chabenam(c);
            }
        }
        for(int i = 0 ; i < 45 ; i++){
            for(int j = 0 ; j < 184 ; j++){
                fgets(c , 300 , p);
                ziba(c);
                donbal4[i][j] = chabenam(c);
            }
        }
        for(int i = 0 ; i < 45 ; i++){
            for(int j = 0 ; j < 184 ; j++){
                fgets(c , 300 , p);
                ziba(c);
                floor5[i][j] = c[0];
            }
        }
        for(int i = 0 ; i < 100 ; i++){
            for(int j = 0 ; j < 5 ; j++){
                fgets(c , 300 , p);
                ziba(c);
                list5[i][j] = chabenam(c);
            }
        }
        for(int i = 0 ; i < 45 ; i++){
            for(int j = 0 ; j < 184 ; j++){
                fgets(c , 300 , p);
                ziba(c);
                didan5[i][j] = chabenam(c);
            }
        }
        for(int i = 0 ; i < 45 ; i++){
            for(int j = 0 ; j < 184 ; j++){
                fgets(c , 300 , p);
                ziba(c);
                value5[i][j] = chabenam(c);
            }
        }
        for(int i = 0 ; i < 45 ; i++){
            for(int j = 0 ; j < 184 ; j++){
                fgets(c , 300 , p);
                ziba(c);
                ghaza5[i][j] = chabenam(c);
            }
        }
        for(int i = 0 ; i < 45 ; i++){
            for(int j = 0 ; j < 184 ; j++){
                fgets(c , 300 , p);
                ziba(c);
                oftadeh5[i][j] = chabenam(c);
            }
        }
        for(int i = 0 ; i < 45 ; i++){
            for(int j = 0 ; j < 184 ; j++){
                fgets(c , 300 , p);
                ziba(c);
                joon5[i][j] = chabenam(c);
            }
        }
        for(int i = 0 ; i < 45 ; i++){
            for(int j = 0 ; j < 184 ; j++){
                fgets(c , 300 , p);
                ziba(c);
                donbal5[i][j] = chabenam(c);
            }
        }
        return 1;
    }
}

int play_tabaghe1(int otagh , int list[otagh][5] , char floor[LINES][COLS] , int didan[LINES][COLS] , Profile *pl , int value[LINES][COLS] , int ghaza[LINES][COLS] , int joon[LINES][COLS] , int donbal[LINES][COLS] , int oftadeh[LINES][COLS]){
    int ch;
    init_pair(1 , COLOR_RED , COLOR_BLACK);
    init_pair(101 , COLOR_BLACK , COLOR_WHITE);
    init_pair(102 , COLOR_MAGENTA , COLOR_BLACK);
    init_pair(103 , COLOR_YELLOW , COLOR_BLACK);

    int ghabl = 0;
    pl->floor = 1;
    do{
        chapgar(pl , floor , didan , pl->pos.x , pl->pos.y , otagh , list , ghaza);
        attron(COLOR_PAIR(1));
        mvprintw(1 , 5 , "Floor number 1");
        if(pl->Dast > -1){
            if(pl->aslahe[pl->Dast] < 1){
                pl->Dast = -1;
            }
        }
        if(koodoom(pl->pos.x , pl->pos.y , otagh , list) == 20){
            mvprintw(0 , 25 , "Path");
        }else {
            if(list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 0){
                mvprintw(0 , 25 , "Regular Room");
            }else if(list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 1){
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(101));
                mvprintw(0 , 25 , "Nightmare Room");
                attroff(COLOR_PAIR(101));
                attron(COLOR_PAIR(1));
            }else if(list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 2){
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(102));
                mvprintw(0 , 25 , "Enchant Room");
                attroff(COLOR_PAIR(102));
                attron(COLOR_PAIR(1));
            }else if(list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 3){
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(103));
                mvprintw( 0 , 25 , "Golden room");
                attroff(COLOR_PAIR(103));
                attron(COLOR_PAIR(1));
            }
        }
        if(pl->Dast == 0){
            mvprintw(1 , 25 , "Weapon : Mace");
        }else if(pl->Dast == 1){
            mvprintw(1 , 25 , "Weapon : Dagger");
        }else if(pl->Dast == 2){
            mvprintw(1 , 25 , "Weapon : Magic Wand");
        }else if(pl->Dast == 3){
            mvprintw(1 , 25 , "Weapon : Normal Arrow");
        }else if(pl->Dast == 4){
            mvprintw(1 , 25 , "Weapon : Sword");
        }else if(pl->Dast == -1){
            mvprintw(1 , 25 , "Weapon : No Weapon");
        }
        if(pl->tedadfood >= 5){
            mvprintw(0 , 5 , "Backpack : Full");
        }else{
            mvprintw(0 , 5 , "Backpack : Empty");
        }
        mvprintw(LINES - 3 , 5 , "Press E to exit...");
        mvprintw(LINES - 3 , 35 , "Press ` to change weapon...");
        mvprintw(LINES - 3 , 75 , "Press 1 to eat food...");
        mvprintw(LINES - 3 , 115 , "Press 2 to use spell...");
        attroff(COLOR_PAIR(1));
        mvprintw(LINES - 5 , 5 , "GOLD : %d" , pl->gold);
        mvprintw(LINES - 5 , 20 , "SCORE : %d" , pl->score);
        if(pl->HP > 21){pl->HP = 21;}
        mvprintw(LINES - 5 , 35 , "HP : %d/21" , pl->HP);
        mvprintw(LINES - 5 , 50 , "Hunger : ");
        for(int i = 0 ; i < 10 ; i++){
            attron(COLOR_PAIR(1));
            if(i < pl->Hunger){
                mvprintw(LINES - 5 , 60 + 2*i , "█");
            }else{
                mvprintw(LINES - 5 , 60 + 2*i , "━");
            }
            attroff(COLOR_PAIR(1));
        }
        timeout(0);
        ch = getch();
        int ha;
        if(ch == 'j' || ch == KEY_UP){//U
            ha = 0;
        }else if(ch == 'k' || ch == KEY_DOWN){//D
            ha = 1;
        }else if(ch == 'l' || ch == KEY_LEFT){//L
            ha = 3;
        }else if(ch == 'h' || ch == KEY_RIGHT){//R
            ha = 2;
        }else if(ch == 'y'){//UL
            ha = 5;
        }else if(ch == 'u'){//UR
            ha = 4;
        }else if(ch == 'n'){//DR
            ha = 6;
        }else if(ch == 'b'){//DL
            ha = 7;
        }else if(ch == 'q'){
            if(M == 1){
                M = 0;
            }else{
                M = 1;
            }
        }else if(ch == '`'){
            pl->Dast = Menuaslahe(pl);
        }else if(ch == '1'){
            Menufood(pl);
        }else if(ch == '2'){
            Menutelesm(pl);
        }else if(ch == ' '){
            if(pl->Dast == 0){//Mace
                zarbeh(pl , 0 , 4 , floor ,  joon , donbal , oftadeh);
            }else if(pl->Dast == 1){//Dagger
                timeout(-1);
                int p;
                p = getch();
                int meow;
                if(p == 'j' || p == KEY_UP){//U
                    meow = 0;
                }else if(p == 'k' || p == KEY_DOWN){//D
                    meow = 1;
                }else if(p == 'l' || p == KEY_LEFT){//L
                    meow = 3;
                }else if(p == 'h' || p == KEY_RIGHT){//R
                    meow = 2;
                }   
                zarbeh(pl , 5  , meow , floor ,  joon , donbal , oftadeh);
            }else if(pl->Dast == 2){//Magic Wand
                timeout(-1);
                int p;
                p = getch();
                int meow;
                if(p == 'j' || p == KEY_UP){//U
                    meow = 0;
                }else if(p == 'k' || p == KEY_DOWN){//D
                    meow = 1;
                }else if(p == 'l' || p == KEY_LEFT){//L
                    meow = 3;
                }else if(p == 'h' || p == KEY_RIGHT){//R
                    meow = 2;
                } 
                zarbeh(pl , 10 , meow , floor ,  joon , donbal , oftadeh);
            }else if(pl->Dast == 3){//Normal Arrow
                timeout(-1);
                int p;
                p = getch();
                int meow;
                if(p == 'j' || p == KEY_UP){//U
                    meow = 0;
                }else if(p == 'k' || p == KEY_DOWN){//D
                    meow = 1;
                }else if(p == 'l' || p == KEY_LEFT){//L
                    meow = 3;
                }else if(p == 'h' || p == KEY_RIGHT){//R
                    meow = 2;
                } 
                zarbeh(pl , 5 , meow , floor ,  joon , donbal , oftadeh);
            }else if(pl->Dast == 4){//Sword
                zarbeh(pl , 0 , 4 , floor ,  joon , donbal , oftadeh);
            }else if(pl->Dast == -1){//No Weapon
                
            }
        }else if(ch == -1){
            //time ham ro check konam;
            time(&now);
            check_hunger(pl);
            check_food(pl);
            check_monster(pl , otagh , list , joon , floor , donbal);
            check_heal(pl);
            if(koodoom(pl->pos.x , pl->pos.y , otagh , list) == 20){

            }else{
                if((ghabl == 20 || list[ghabl][4] != 2) && list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 2){
                    time(&past_enchant);
                    ghabl = koodoom(pl->pos.x , pl->pos.y , otagh , list);
                }
                if(list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 2){
                    check_ench(pl);
                }
            }
            if(pl->HP <= 0){
                return 20;
            }
            continue;
        }
        if(ch != 'q' && ch != '`' && ch != '1' && ch != '2' && ch != ' ' && ch != 'e'){
            pl->pos = harekat(pl , otagh , list , floor , didan , value , ha , ghaza , oftadeh);
            if(pl->Strengh > 0){pl->Strengh--;}
            if(pl->pos.x == -1 && pl->pos.y == -1){
                return 1;
            }else if(pl->pos.x == -2 && pl->pos.y == -2){
                return 1;
            }else{
                if(value[pl->pos.y][pl->pos.x] >= 0){
                    pl->score += pl->diff * value[pl->pos.y][pl->pos.x];
                    pl->gold += value[pl->pos.y][pl->pos.x];
                    value[pl->pos.y][pl->pos.x] = 0;
                }else{
                    pl->HP --;
                    timeout(-1);
                    mvprintw(2 , 5 , "Watch out for TRAP!!! Press any key to continue...");
                    getch();
                }
            }
            if(koodoom(pl->pos.x , pl->pos.y , otagh , list) == 20){

            }else{
                if((ghabl == 20 || list[ghabl][4] != 2) && list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 2){
                    sedaavazkon(2);
                }
                if((ghabl == 20 || list[ghabl][4] != 1) && list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 1){
                    sedaavazkon(1);
                }
                if((ghabl == 20 || list[ghabl][4] != 3) && list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 3){
                    sedaavazkon(3);
                }
                if((ghabl == 20 || list[ghabl][4] != 0) && list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 0){
                    sedaavazkon(0);
                }  
            }
            atraf(pl , otagh , list , floor , donbal);
            ghabl = koodoom(pl->pos.x , pl->pos.y , otagh , list);
        }
        if(pl->HP <= 0){
            return 20;
        }
    }while(ch != 'e');
    return 0;
}

int play_tabaghe2(int otagh , int list[otagh][5] , char floor[LINES][COLS] , int didan[LINES][COLS] , Profile *pl , int value[LINES][COLS] , int ghaza[LINES][COLS] , int joon[LINES][COLS] , int donbal[LINES][COLS] , int oftadeh[LINES][COLS]){
    int ch;
    init_pair(1 , COLOR_RED , COLOR_BLACK);
    init_pair(101 , COLOR_BLACK , COLOR_WHITE);
    init_pair(102 , COLOR_MAGENTA , COLOR_BLACK);
    init_pair(103 , COLOR_YELLOW , COLOR_BLACK);
    int ghabl = 0;
    pl->floor = 2;
    do{
        chapgar(pl , floor , didan , pl->pos.x , pl->pos.y , otagh , list , ghaza);
        attron(COLOR_PAIR(1));
        mvprintw(1 , 5 , "Floor number 2");
        if(pl->Dast > -1){
            if(pl->aslahe[pl->Dast] < 1){
                pl->Dast = -1;
            }
        }
        if(koodoom(pl->pos.x , pl->pos.y , otagh , list) == 20){
            mvprintw(0 , 25 , "Path");
        }else {
            if(list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 0){
                mvprintw(0 , 25 , "Regular Room");
            }else if(list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 1){
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(101));
                mvprintw(0 , 25 , "Nightmare Room");
                attroff(COLOR_PAIR(101));
                attron(COLOR_PAIR(1));
            }else if(list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 2){
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(102));
                mvprintw(0 , 25 , "Enchant Room");
                attroff(COLOR_PAIR(102));
                attron(COLOR_PAIR(1));
            }else if(list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 3){
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(103));
                mvprintw( 0 , 25 , "Golden room");
                attroff(COLOR_PAIR(103));
                attron(COLOR_PAIR(1));
            }
        }
        if(pl->Dast == 0){
            mvprintw(1 , 25 , "Weapon : Mace");
        }else if(pl->Dast == 1){
            mvprintw(1 , 25 , "Weapon : Dagger");
        }else if(pl->Dast == 2){
            mvprintw(1 , 25 , "Weapon : Magic Wand");
        }else if(pl->Dast == 3){
            mvprintw(1 , 25 , "Weapon : Normal Arrow");
        }else if(pl->Dast == 4){
            mvprintw(1 , 25 , "Weapon : Sword");
        }else if(pl->Dast == -1){
            mvprintw(1 , 25 , "Weapon : No Weapon");
        }
        if(pl->tedadfood >= 5){
            mvprintw(0 , 5 , "Backpack : Full");
        }else{
            mvprintw(0 , 5 , "Backpack : Empty");
        }
        mvprintw(LINES - 3 , 5 , "Press E to exit...");
        mvprintw(LINES - 3 , 35 , "Press ` to change weapon...");
        mvprintw(LINES - 3 , 75 , "Press 1 to eat food...");
        mvprintw(LINES - 3 , 115 , "Press 2 to use spell...");
        attroff(COLOR_PAIR(1));
        mvprintw(LINES - 5 , 5 , "GOLD : %d" , pl->gold);
        mvprintw(LINES - 5 , 20 , "SCORE : %d" , pl->score);
        if(pl->HP > 21){pl->HP = 21;}
        mvprintw(LINES - 5 , 35 , "HP : %d/21" , pl->HP);
        mvprintw(LINES - 5 , 50 , "Hunger : ");
        for(int i = 0 ; i < 10 ; i++){
                attron(COLOR_PAIR(1));
            if(i < pl->Hunger){
                mvprintw(LINES - 5 , 60 + 2*i , "█");
            }else{
                mvprintw(LINES - 5 , 60 + 2*i , "━");
            }
            attroff(COLOR_PAIR(1));
        }
        timeout(0);
        ch = getch();
        int ha;
        if(ch == 'j' || ch == KEY_UP){//U
            ha = 0;
        }else if(ch == 'k' || ch == KEY_DOWN){//D
            ha = 1;
        }else if(ch == 'l' || ch == KEY_LEFT){//L
            ha = 3;
        }else if(ch == 'h' || ch == KEY_RIGHT){//R
            ha = 2;
        }else if(ch == 'y'){//UL
            ha = 5;
        }else if(ch == 'u'){//UR
            ha = 4;
        }else if(ch == 'n'){//DR
            ha = 6;
        }else if(ch == 'b'){//DL
            ha = 7;
        }else if(ch == 'q'){
            if(M == 1){
                M = 0;
            }else{
                M = 1;
            }
        }else if(ch == '`'){
            pl->Dast = Menuaslahe(pl);
        }else if(ch == '1'){
            Menufood(pl);
        }else if(ch == '2'){
            Menutelesm(pl);
        }else if(ch == ' '){
            if(pl->Dast == 0){//Mace
                zarbeh(pl , 0 , 4 , floor ,  joon , donbal , oftadeh);
            }else if(pl->Dast == 1){//Dagger
                timeout(-1);
                int p;
                p = getch();
                int meow;
                if(p == 'j' || p == KEY_UP){//U
                    meow = 0;
                }else if(p == 'k' || p == KEY_DOWN){//D
                    meow = 1;
                }else if(p == 'l' || p == KEY_LEFT){//L
                    meow = 3;
                }else if(p == 'h' || p == KEY_RIGHT){//R
                    meow = 2;
                }   
                zarbeh(pl , 5  , meow , floor ,  joon , donbal , oftadeh);
            }else if(pl->Dast == 2){//Magic Wand
                timeout(-1);
                int p;
                p = getch();
                int meow;
                if(p == 'j' || p == KEY_UP){//U
                    meow = 0;
                }else if(p == 'k' || p == KEY_DOWN){//D
                    meow = 1;
                }else if(p == 'l' || p == KEY_LEFT){//L
                    meow = 3;
                }else if(p == 'h' || p == KEY_RIGHT){//R
                    meow = 2;
                } 
                zarbeh(pl , 10 , meow , floor ,  joon , donbal , oftadeh);
            }else if(pl->Dast == 3){//Normal Arrow
                timeout(-1);
                int p;
                p = getch();
                int meow;
                if(p == 'j' || p == KEY_UP){//U
                    meow = 0;
                }else if(p == 'k' || p == KEY_DOWN){//D
                    meow = 1;
                }else if(p == 'l' || p == KEY_LEFT){//L
                    meow = 3;
                }else if(p == 'h' || p == KEY_RIGHT){//R
                    meow = 2;
                } 
                zarbeh(pl , 5 , meow , floor ,  joon , donbal , oftadeh);
            }else if(pl->Dast == 4){//Sword
                zarbeh(pl , 0 , 4 , floor ,  joon , donbal , oftadeh);
            }else if(pl->Dast == -1){//No Weapon
                
            }
        }else if(ch == -1){
            //time ham ro check konam;
            time(&now);
            check_hunger(pl);
            check_food(pl);
            check_monster(pl , otagh , list , joon , floor , donbal);
            check_heal(pl);
            if(koodoom(pl->pos.x , pl->pos.y , otagh , list) == 20){

            }else{
                if((ghabl == 20 || list[ghabl][4] != 2) && list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 2){
                    time(&past_enchant);
                    ghabl = koodoom(pl->pos.x , pl->pos.y , otagh , list);
                }
                if(list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 2){
                    check_ench(pl);
                }
            }
            continue;
        }
        if(ch != 'q' && ch != '`' && ch != '1' && ch != '2' && ch != ' ' && ch != 'e'){
            pl->pos = harekat(pl , otagh , list , floor , didan , value , ha , ghaza , oftadeh);
            if(pl->Strengh > 0){pl->Strengh--;}
            if(pl->pos.x == -1 && pl->pos.y == -1){
                return 3;
            }else if(pl->pos.x == -2 && pl->pos.y == -2){
                return 2;
            }else{
                if(value[pl->pos.y][pl->pos.x] >= 0){
                    pl->score += pl->diff * value[pl->pos.y][pl->pos.x];
                    pl->gold += value[pl->pos.y][pl->pos.x];
                    value[pl->pos.y][pl->pos.x] = 0;
                }else{
                    pl->HP --;
                    timeout(-1);
                    mvprintw(2 , 5 , "Watch out for TRAP!!! Press any key to continue...");
                    getch();
                }
            }
            if(koodoom(pl->pos.x , pl->pos.y , otagh , list) == 20){

            }else{
                if((ghabl == 20 || list[ghabl][4] != 2) && list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 2){
                    sedaavazkon(2);
                }
                if((ghabl == 20 || list[ghabl][4] != 1) && list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 1){
                    sedaavazkon(1);
                }
                if((ghabl == 20 || list[ghabl][4] != 3) && list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 3){
                    sedaavazkon(3);
                }
                if((ghabl == 20 || list[ghabl][4] != 0) && list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 0){
                    sedaavazkon(0);
                }  
            }
            atraf(pl , otagh , list , floor , donbal);
            ghabl = koodoom(pl->pos.x , pl->pos.y , otagh , list);
        }
        if(pl->HP <= 0){
            return 20;
        }
    }while(ch != 'e');
    return 0;
}

int play_tabaghe3(int otagh , int list[otagh][5] , char floor[LINES][COLS] , int didan[LINES][COLS] , Profile *pl , int value[LINES][COLS] , int ghaza[LINES][COLS] , int joon[LINES][COLS] , int donbal[LINES][COLS] , int oftadeh[LINES][COLS]){
    int ch;
    init_pair(1 , COLOR_RED , COLOR_BLACK);
    init_pair(101 , COLOR_BLACK , COLOR_WHITE);
    init_pair(102 , COLOR_MAGENTA , COLOR_BLACK);
    init_pair(103 , COLOR_YELLOW , COLOR_BLACK);
    int ghabl = 0;
    pl->floor = 3;
    do{
        chapgar(pl , floor , didan , pl->pos.x , pl->pos.y , otagh , list , ghaza);
        attron(COLOR_PAIR(1));
        mvprintw(1 , 5 , "Floor number 3");
        if(pl->Dast > -1){
            if(pl->aslahe[pl->Dast] < 1){
                pl->Dast = -1;
            }
        }
        if(koodoom(pl->pos.x , pl->pos.y , otagh , list) == 20){
            mvprintw(0 , 25 , "Path");
        }else {
            if(list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 0){
                mvprintw(0 , 25 , "Regular Room");
            }else if(list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 1){
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(101));
                mvprintw(0 , 25 , "Nightmare Room");
                attroff(COLOR_PAIR(101));
                attron(COLOR_PAIR(1));
            }else if(list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 2){
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(102));
                mvprintw(0 , 25 , "Enchant Room");
                attroff(COLOR_PAIR(102));
                attron(COLOR_PAIR(1));
            }else if(list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 3){
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(103));
                mvprintw( 0 , 25 , "Golden room");
                attroff(COLOR_PAIR(103));
                attron(COLOR_PAIR(1));
            }
        }
        if(pl->Dast == 0){
            mvprintw(1 , 25 , "Weapon : Mace");
        }else if(pl->Dast == 1){
            mvprintw(1 , 25 , "Weapon : Dagger");
        }else if(pl->Dast == 2){
            mvprintw(1 , 25 , "Weapon : Magic Wand");
        }else if(pl->Dast == 3){
            mvprintw(1 , 25 , "Weapon : Normal Arrow");
        }else if(pl->Dast == 4){
            mvprintw(1 , 25 , "Weapon : Sword");
        }else if(pl->Dast == -1){
            mvprintw(1 , 25 , "Weapon : No Weapon");
        }
        if(pl->tedadfood >= 5){
            mvprintw(0 , 5 , "Backpack : Full");
        }else{
            mvprintw(0 , 5 , "Backpack : Empty");
        }
        mvprintw(LINES - 3 , 5 , "Press E to exit...");
        mvprintw(LINES - 3 , 35 , "Press ` to change weapon...");
        mvprintw(LINES - 3 , 75 , "Press 1 to eat food...");
        mvprintw(LINES - 3 , 115 , "Press 2 to use spell...");
        attroff(COLOR_PAIR(1));
        mvprintw(LINES - 5 , 5 , "GOLD : %d" , pl->gold);
        mvprintw(LINES - 5 , 20 , "SCORE : %d" , pl->score);
        if(pl->HP > 21){pl->HP = 21;}
        mvprintw(LINES - 5 , 35 , "HP : %d/21" , pl->HP);
        mvprintw(LINES - 5 , 50 , "Hunger : ");
        for(int i = 0 ; i < 10 ; i++){
                attron(COLOR_PAIR(1));
            if(i < pl->Hunger){
                mvprintw(LINES - 5 , 60 + 2*i , "█");
            }else{
                mvprintw(LINES - 5 , 60 + 2*i , "━");
            }
            attroff(COLOR_PAIR(1));
        }
        timeout(0);        
        ch = getch();
        int ha;
        if(ch == 'j' || ch == KEY_UP){//U
            ha = 0;
        }else if(ch == 'k' || ch == KEY_DOWN){//D
            ha = 1;
        }else if(ch == 'l' || ch == KEY_LEFT){//L
            ha = 3;
        }else if(ch == 'h' || ch == KEY_RIGHT){//R
            ha = 2;
        }else if(ch == 'y'){//UL
            ha = 5;
        }else if(ch == 'u'){//UR
            ha = 4;
        }else if(ch == 'n'){//DR
            ha = 6;
        }else if(ch == 'b'){//DL
            ha = 7;
        }else if(ch == 'q'){
            if(M == 1){
                M = 0;
            }else{
                M = 1;
            }
        }else if(ch == '`'){
            pl->Dast = Menuaslahe(pl);
        }else if(ch == '1'){
            Menufood(pl);
        }else if(ch == '2'){
            Menutelesm(pl);
        }else if(ch == ' '){
            if(pl->Dast == 0){//Mace
                zarbeh(pl , 0 , 4 , floor ,  joon , donbal , oftadeh);
            }else if(pl->Dast == 1){//Dagger
                timeout(-1);
                int p;
                p = getch();
                int meow;
                if(p == 'j' || p == KEY_UP){//U
                    meow = 0;
                }else if(p == 'k' || p == KEY_DOWN){//D
                    meow = 1;
                }else if(p == 'l' || p == KEY_LEFT){//L
                    meow = 3;
                }else if(p == 'h' || p == KEY_RIGHT){//R
                    meow = 2;
                }   
                zarbeh(pl , 5  , meow , floor ,  joon , donbal , oftadeh);
            }else if(pl->Dast == 2){//Magic Wand
                timeout(-1);
                int p;
                p = getch();
                int meow;
                if(p == 'j' || p == KEY_UP){//U
                    meow = 0;
                }else if(p == 'k' || p == KEY_DOWN){//D
                    meow = 1;
                }else if(p == 'l' || p == KEY_LEFT){//L
                    meow = 3;
                }else if(p == 'h' || p == KEY_RIGHT){//R
                    meow = 2;
                } 
                zarbeh(pl , 10 , meow , floor ,  joon , donbal , oftadeh);
            }else if(pl->Dast == 3){//Normal Arrow
                timeout(-1);
                int p;
                p = getch();
                int meow;
                if(p == 'j' || p == KEY_UP){//U
                    meow = 0;
                }else if(p == 'k' || p == KEY_DOWN){//D
                    meow = 1;
                }else if(p == 'l' || p == KEY_LEFT){//L
                    meow = 3;
                }else if(p == 'h' || p == KEY_RIGHT){//R
                    meow = 2;
                } 
                zarbeh(pl , 5 , meow , floor ,  joon , donbal , oftadeh);
            }else if(pl->Dast == 4){//Sword
                zarbeh(pl , 0 , 4 , floor ,  joon , donbal , oftadeh);
            }else if(pl->Dast == -1){//No Weapon
                
            }
        }else if(ch == -1){
            //time ham ro check konam;
            time(&now);
            check_hunger(pl);
            check_food(pl);
            check_monster(pl , otagh , list , joon , floor , donbal);
            check_heal(pl);
            if(koodoom(pl->pos.x , pl->pos.y , otagh , list) == 20){

            }else{
                if((ghabl == 20 || list[ghabl][4] != 2) && list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 2){
                    time(&past_enchant);
                    ghabl = koodoom(pl->pos.x , pl->pos.y , otagh , list);
                }
                if(list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 2){
                    check_ench(pl);
                }
            }
            if(pl->HP <= 0){
                return 20;
            }
            continue;
        }
        if(ch != 'q' && ch != '`' && ch != '1' && ch != '2' && ch != ' ' && ch != 'e'){
            pl->pos = harekat(pl , otagh , list , floor , didan , value , ha , ghaza , oftadeh);
            if(pl->Strengh > 0){pl->Strengh--;}
            if(pl->pos.x == -1 && pl->pos.y == -1){
                return 5;
            }else if(pl->pos.x == -2 && pl->pos.y == -2){
                return 4;
            }else{
                if(value[pl->pos.y][pl->pos.x] >= 0){
                    pl->score += pl->diff * value[pl->pos.y][pl->pos.x];
                    pl->gold += value[pl->pos.y][pl->pos.x];
                    value[pl->pos.y][pl->pos.x] = 0;
                }else{
                    pl->HP --;
                    timeout(-1);
                    mvprintw(2 , 5 , "Watch out for TRAP!!! Press any key to continue...");
                    getch();
                }
            }
            if(koodoom(pl->pos.x , pl->pos.y , otagh , list) == 20){

            }else{
                if((ghabl == 20 || list[ghabl][4] != 2) && list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 2){
                    sedaavazkon(2);
                }
                if((ghabl == 20 || list[ghabl][4] != 1) && list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 1){
                    sedaavazkon(1);
                }
                if((ghabl == 20 || list[ghabl][4] != 3) && list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 3){
                    sedaavazkon(3);
                }
                if((ghabl == 20 || list[ghabl][4] != 0) && list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 0){
                    sedaavazkon(0);
                }  
            }
            atraf(pl , otagh , list , floor , donbal);
            ghabl = koodoom(pl->pos.x , pl->pos.y , otagh , list);
        }
        if(pl->HP <= 0){
            return 20;
        }
    }while(ch != 'e');
    return 0;
}

int play_tabaghe4(int otagh , int list[otagh][5] , char floor[LINES][COLS] , int didan[LINES][COLS] , Profile *pl , int value[LINES][COLS] , int ghaza[LINES][COLS] , int joon[LINES][COLS] , int donbal[LINES][COLS] , int oftadeh[LINES][COLS]){
    int ch;
    init_pair(1 , COLOR_RED , COLOR_BLACK);
    init_pair(101 , COLOR_BLACK , COLOR_WHITE);
    init_pair(102 , COLOR_MAGENTA , COLOR_BLACK);
    init_pair(103 , COLOR_YELLOW , COLOR_BLACK);
    int ghabl = 0;
    pl->floor = 4;
    do{
        chapgar(pl , floor , didan , pl->pos.x , pl->pos.y , otagh , list , ghaza);
        attron(COLOR_PAIR(1));
        mvprintw(1 , 5 , "Floor number 4");
        if(pl->Dast > -1){
            if(pl->aslahe[pl->Dast] < 1){
                pl->Dast = -1;
            }
        }
        if(koodoom(pl->pos.x , pl->pos.y , otagh , list) == 20){
            mvprintw(0 , 25 , "Path");
        }else {
            if(list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 0){
                mvprintw(0 , 25 , "Regular Room");
            }else if(list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 1){
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(101));
                mvprintw(0 , 25 , "Nightmare Room");
                attroff(COLOR_PAIR(101));
                attron(COLOR_PAIR(1));
            }else if(list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 2){
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(102));
                mvprintw(0 , 25 , "Enchant Room");
                attroff(COLOR_PAIR(102));
                attron(COLOR_PAIR(1));
            }else if(list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 3){
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(103));
                mvprintw( 0 , 25 , "Golden room");
                attroff(COLOR_PAIR(103));
                attron(COLOR_PAIR(1));
            }
        }
        if(pl->Dast == 0){
            mvprintw(1 , 25 , "Weapon : Mace");
        }else if(pl->Dast == 1){
            mvprintw(1 , 25 , "Weapon : Dagger");
        }else if(pl->Dast == 2){
            mvprintw(1 , 25 , "Weapon : Magic Wand");
        }else if(pl->Dast == 3){
            mvprintw(1 , 25 , "Weapon : Normal Arrow");
        }else if(pl->Dast == 4){
            mvprintw(1 , 25 , "Weapon : Sword");
        }else if(pl->Dast == -1){
            mvprintw(1 , 25 , "Weapon : No Weapon");
        }
        if(pl->tedadfood >= 5){
            mvprintw(0 , 5 , "Backpack : Full");
        }else{
            mvprintw(0 , 5 , "Backpack : Empty");
        }
        mvprintw(LINES - 3 , 5 , "Press E to exit...");
        mvprintw(LINES - 3 , 35 , "Press ` to change weapon...");
        mvprintw(LINES - 3 , 75 , "Press 1 to eat food...");
        mvprintw(LINES - 3 , 115 , "Press 2 to use spell...");
        attroff(COLOR_PAIR(1));
        mvprintw(LINES - 5 , 5 , "GOLD : %d" , pl->gold);
        mvprintw(LINES - 5 , 20 , "SCORE : %d" , pl->score);
        if(pl->HP > 21){pl->HP = 21;}
        mvprintw(LINES - 5 , 35 , "HP : %d/21" , pl->HP);
        mvprintw(LINES - 5 , 50 , "Hunger : ");
        for(int i = 0 ; i < 10 ; i++){
                attron(COLOR_PAIR(1));
            if(i < pl->Hunger){
                mvprintw(LINES - 5 , 60 + 2*i , "█");
            }else{
                mvprintw(LINES - 5 , 60 + 2*i , "━");
            }
            attroff(COLOR_PAIR(1));
        }
        timeout(0);        
        ch = getch();
        int ha;
        if(ch == 'j' || ch == KEY_UP){//U
            ha = 0;
        }else if(ch == 'k' || ch == KEY_DOWN){//D
            ha = 1;
        }else if(ch == 'l' || ch == KEY_LEFT){//L
            ha = 3;
        }else if(ch == 'h' || ch == KEY_RIGHT){//R
            ha = 2;
        }else if(ch == 'y'){//UL
            ha = 5;
        }else if(ch == 'u'){//UR
            ha = 4;
        }else if(ch == 'n'){//DR
            ha = 6;
        }else if(ch == 'b'){//DL
            ha = 7;
        }else if(ch == 'q'){
            if(M == 1){
                M = 0;
            }else{
                M = 1;
            }
        }else if(ch == '`'){
            pl->Dast = Menuaslahe(pl);
        }else if(ch == '1'){
            Menufood(pl);
        }else if(ch == '2'){
            Menutelesm(pl);
        }else if(ch == ' '){
            if(pl->Dast == 0){//Mace
                zarbeh(pl , 0 , 4 , floor ,  joon , donbal , oftadeh);
            }else if(pl->Dast == 1){//Dagger
                timeout(-1);
                int p;
                p = getch();
                int meow;
                if(p == 'j' || p == KEY_UP){//U
                    meow = 0;
                }else if(p == 'k' || p == KEY_DOWN){//D
                    meow = 1;
                }else if(p == 'l' || p == KEY_LEFT){//L
                    meow = 3;
                }else if(p == 'h' || p == KEY_RIGHT){//R
                    meow = 2;
                }   
                zarbeh(pl , 5  , meow , floor ,  joon , donbal , oftadeh);
            }else if(pl->Dast == 2){//Magic Wand
                timeout(-1);
                int p;
                p = getch();
                int meow;
                if(p == 'j' || p == KEY_UP){//U
                    meow = 0;
                }else if(p == 'k' || p == KEY_DOWN){//D
                    meow = 1;
                }else if(p == 'l' || p == KEY_LEFT){//L
                    meow = 3;
                }else if(p == 'h' || p == KEY_RIGHT){//R
                    meow = 2;
                } 
                zarbeh(pl , 10 , meow , floor ,  joon , donbal , oftadeh);
            }else if(pl->Dast == 3){//Normal Arrow
                timeout(-1);
                int p;
                p = getch();
                int meow;
                if(p == 'j' || p == KEY_UP){//U
                    meow = 0;
                }else if(p == 'k' || p == KEY_DOWN){//D
                    meow = 1;
                }else if(p == 'l' || p == KEY_LEFT){//L
                    meow = 3;
                }else if(p == 'h' || p == KEY_RIGHT){//R
                    meow = 2;
                } 
                zarbeh(pl , 5 , meow , floor ,  joon , donbal , oftadeh);
            }else if(pl->Dast == 4){//Sword
                zarbeh(pl , 0 , 4 , floor ,  joon , donbal , oftadeh);
            }else if(pl->Dast == -1){//No Weapon
                
            }
        }else if(ch == -1){
            //time ham ro check konam;
            time(&now);
            check_hunger(pl);
            check_food(pl);
            check_monster(pl , otagh , list , joon , floor , donbal);
            check_heal(pl);
            if(koodoom(pl->pos.x , pl->pos.y , otagh , list) == 20){

            }else{
                if((ghabl == 20 || list[ghabl][4] != 2) && list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 2){
                    time(&past_enchant);
                    ghabl = koodoom(pl->pos.x , pl->pos.y , otagh , list);
                }
                if(list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 2){
                    check_ench(pl);
                }
            }
            if(pl->HP <= 0){
                return 20;
            }
            continue;
        }
        if(ch != 'q' && ch != '`' && ch != '1' && ch != '2' && ch != ' ' && ch != 'e'){
            pl->pos = harekat(pl , otagh , list , floor , didan , value , ha , ghaza , oftadeh);
            if(pl->Strengh > 0){pl->Strengh--;}
            if(pl->pos.x == -1 && pl->pos.y == -1){
                return 6;
            }else if(pl->pos.x == -2 && pl->pos.y == -2){
                return 7;
            }else{
                if(value[pl->pos.y][pl->pos.x] >= 0){
                    pl->score += pl->diff * value[pl->pos.y][pl->pos.x];
                    pl->gold += value[pl->pos.y][pl->pos.x];
                    value[pl->pos.y][pl->pos.x] = 0;
                }else{
                    pl->HP --;
                    timeout(-1);
                    mvprintw(2 , 5 , "Watch out for TRAP!!! Press any key to continue...");
                    getch();
                }
            }
            if(koodoom(pl->pos.x , pl->pos.y , otagh , list) == 20){

            }else{
                if((ghabl == 20 || list[ghabl][4] != 2) && list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 2){
                    sedaavazkon(2);
                }
                if((ghabl == 20 || list[ghabl][4] != 1) && list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 1){
                    sedaavazkon(1);
                }
                if((ghabl == 20 || list[ghabl][4] != 3) && list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 3){
                    sedaavazkon(3);
                }
                if((ghabl == 20 || list[ghabl][4] != 0) && list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 0){
                    sedaavazkon(0);
                }  
            }
            atraf(pl , otagh , list , floor , donbal);
            ghabl = koodoom(pl->pos.x , pl->pos.y , otagh , list);
        }
        if(pl->HP <= 0){
            return 20;
        }
    }while(ch != 'e');
    return 0;
}

int play_tabaghe5(int otagh , int list[otagh][5] , char floor[LINES][COLS] , int didan[LINES][COLS] , Profile *pl , int value[LINES][COLS] , int ghaza[LINES][COLS] , int joon[LINES][COLS] , int donbal[LINES][COLS] , int oftadeh[LINES][COLS]){
    int ch;
    init_pair(1 , COLOR_RED , COLOR_BLACK);
    init_pair(101 , COLOR_BLACK , COLOR_WHITE);
    init_pair(102 , COLOR_MAGENTA , COLOR_BLACK);
    init_pair(103 , COLOR_YELLOW , COLOR_BLACK);
    int ghabl = 0;
    pl->floor = 5;
    do{
        chapgar(pl , floor , didan , pl->pos.x , pl->pos.y , otagh , list , ghaza);
        attron(COLOR_PAIR(1));
        mvprintw(1 , 5 , "Floor number 5");
        if(pl->Dast > -1){
            if(pl->aslahe[pl->Dast] < 1){
                pl->Dast = -1;
            }
        }
        if(koodoom(pl->pos.x , pl->pos.y , otagh , list) == 20){
            mvprintw(0 , 25 , "Path");
        }else {
            if(list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 0){
                mvprintw(0 , 25 , "Regular Room");
            }else if(list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 1){
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(101));
                mvprintw(0 , 25 , "Nightmare Room");
                attroff(COLOR_PAIR(101));
                attron(COLOR_PAIR(1));
            }else if(list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 2){
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(102));
                mvprintw(0 , 25 , "Enchant Room");
                attroff(COLOR_PAIR(102));
                attron(COLOR_PAIR(1));
            }else if(list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 3){
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(103));
                mvprintw( 0 , 25 , "Golden room");
                attroff(COLOR_PAIR(103));
                attron(COLOR_PAIR(1));
            }
        }
        if(pl->Dast == 0){
            mvprintw(1 , 25 , "Weapon : Mace");
        }else if(pl->Dast == 1){
            mvprintw(1 , 25 , "Weapon : Dagger");
        }else if(pl->Dast == 2){
            mvprintw(1 , 25 , "Weapon : Magic Wand");
        }else if(pl->Dast == 3){
            mvprintw(1 , 25 , "Weapon : Normal Arrow");
        }else if(pl->Dast == 4){
            mvprintw(1 , 25 , "Weapon : Sword");
        }else if(pl->Dast == -1){
            mvprintw(1 , 25 , "Weapon : No Weapon");
        }
        if(pl->tedadfood >= 5){
            mvprintw(0 , 5 , "Backpack : Full");
        }else{
            mvprintw(0 , 5 , "Backpack : Empty");
        }
        mvprintw(LINES - 3 , 5 , "Press E to exit...");
        mvprintw(LINES - 3 , 35 , "Press ` to change weapon...");
        mvprintw(LINES - 3 , 75 , "Press 1 to eat food...");
        mvprintw(LINES - 3 , 115 , "Press 2 to use spell...");
        attroff(COLOR_PAIR(1));
        mvprintw(LINES - 5 , 5 , "GOLD : %d" , pl->gold);
        mvprintw(LINES - 5 , 20 , "SCORE : %d" , pl->score);
        if(pl->HP > 21){pl->HP = 21;}
        mvprintw(LINES - 5 , 35 , "HP : %d/21" , pl->HP);   
        mvprintw(LINES - 5 , 50 , "Hunger : ");
        for(int i = 0 ; i < 10 ; i++){
            attron(COLOR_PAIR(1));
            if(i < pl->Hunger){
                mvprintw(LINES - 5 , 60 + 2*i , "█");
            }else{
                mvprintw(LINES - 5 , 60 + 2*i , "━");
            }
            attroff(COLOR_PAIR(1));
        }       
        timeout(0); 
        ch = getch();
        int ha;
        if(ch == 'j' || ch == KEY_UP){//U
            ha = 0;
        }else if(ch == 'k' || ch == KEY_DOWN){//D
            ha = 1;
        }else if(ch == 'l' || ch == KEY_LEFT){//L
            ha = 3;
        }else if(ch == 'h' || ch == KEY_RIGHT){//R
            ha = 2;
        }else if(ch == 'y'){//UL
            ha = 5;
        }else if(ch == 'u'){//UR
            ha = 4;
        }else if(ch == 'n'){//DR
            ha = 6;
        }else if(ch == 'b'){//DL
            ha = 7;
        }else if(ch == 'q'){
            if(M == 1){
                M = 0;
            }else{
                M = 1;
            }
        }else if(ch == '`'){
            pl->Dast = Menuaslahe(pl);
        }else if(ch == '1'){
            Menufood(pl);
        }else if(ch == '2'){
            Menutelesm(pl);
        }else if(ch == ' '){
            if(pl->Dast == 0){//Mace
                zarbeh(pl , 0 , 4 , floor ,  joon , donbal , oftadeh);
            }else if(pl->Dast == 1){//Dagger
                timeout(-1);
                int p;
                p = getch();
                int meow;
                if(p == 'j' || p == KEY_UP){//U
                    meow = 0;
                }else if(p == 'k' || p == KEY_DOWN){//D
                    meow = 1;
                }else if(p == 'l' || p == KEY_LEFT){//L
                    meow = 3;
                }else if(p == 'h' || p == KEY_RIGHT){//R
                    meow = 2;
                }   
                zarbeh(pl , 5  , meow , floor ,  joon , donbal , oftadeh);
            }else if(pl->Dast == 2){//Magic Wand
                timeout(-1);
                int p;
                p = getch();
                int meow;
                if(p == 'j' || p == KEY_UP){//U
                    meow = 0;
                }else if(p == 'k' || p == KEY_DOWN){//D
                    meow = 1;
                }else if(p == 'l' || p == KEY_LEFT){//L
                    meow = 3;
                }else if(p == 'h' || p == KEY_RIGHT){//R
                    meow = 2;
                } 
                zarbeh(pl , 10 , meow , floor ,  joon , donbal , oftadeh);
            }else if(pl->Dast == 3){//Normal Arrow
                timeout(-1);
                int p;
                p = getch();
                int meow;
                if(p == 'j' || p == KEY_UP){//U
                    meow = 0;
                }else if(p == 'k' || p == KEY_DOWN){//D
                    meow = 1;
                }else if(p == 'l' || p == KEY_LEFT){//L
                    meow = 3;
                }else if(p == 'h' || p == KEY_RIGHT){//R
                    meow = 2;
                } 
                zarbeh(pl , 5 , meow , floor ,  joon , donbal , oftadeh);
            }else if(pl->Dast == 4){//Sword
                zarbeh(pl , 0 , 4 , floor ,  joon , donbal , oftadeh);
            }else if(pl->Dast == -1){//No Weapon
                
            }
        }else if(ch == -1){
            //time ham ro check konam;
            time(&now);
            check_hunger(pl);
            check_food(pl);
            check_monster(pl , otagh , list , joon , floor , donbal);
            check_heal(pl);
            if(koodoom(pl->pos.x , pl->pos.y , otagh , list) == 20){

            }else{
                if((ghabl == 20 || list[ghabl][4] != 2) && list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 2){
                    time(&past_enchant);
                    ghabl = koodoom(pl->pos.x , pl->pos.y , otagh , list);
                }
                if(list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 2){
                    check_ench(pl);
                }
            }
            if(pl->HP <= 0){
                return 20;
            }
            continue;
        }
        if(ch != 'q' && ch != '`' && ch != '1' && ch != '2' && ch != ' ' && ch != 'e'){
            pl->pos = harekat(pl , otagh , list , floor , didan , value , ha , ghaza , oftadeh);
            if(pl->Strengh > 0){pl->Strengh--;}
            if(pl->pos.x == -1 && pl->pos.y == -1){
                return 9;
            }else if(pl->pos.x == -2 && pl->pos.y == -2){
                return 8;
            }else{
                if(value[pl->pos.y][pl->pos.x] >= 0){
                    pl->score += pl->diff * value[pl->pos.y][pl->pos.x];
                    pl->gold += value[pl->pos.y][pl->pos.x];
                    value[pl->pos.y][pl->pos.x] = 0;
                }else{
                    pl->HP--;
                    timeout(-1);
                    mvprintw(2 , 5 , "Watch out for TRAP!!! Press any key to continue...");
                    getch();
                }
            }
            if(koodoom(pl->pos.x , pl->pos.y , otagh , list) == 20){

            }else{
                if((ghabl == 20 || list[ghabl][4] != 2) && list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 2){
                    sedaavazkon(2);
                }
                if((ghabl == 20 || list[ghabl][4] != 1) && list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 1){
                    sedaavazkon(1);
                }
                if((ghabl == 20 || list[ghabl][4] != 3) && list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 3){
                    sedaavazkon(3);
                }
                if((ghabl == 20 || list[ghabl][4] != 0) && list[koodoom(pl->pos.x , pl->pos.y , otagh , list)][4] == 0){
                    sedaavazkon(0);
                }  
            }
            atraf(pl , otagh , list , floor , donbal);
            ghabl = koodoom(pl->pos.x , pl->pos.y , otagh , list);
        }
        if(pl->HP <= 0){
            return 20;
        }
    }while(ch != 'e');
    return 0;
}

void bordan(Profile *pl){
    clear();
    board();
    init_pair(30 , COLOR_YELLOW , COLOR_BLACK);
    attron(COLOR_PAIR(30));
    mvprintw(LINES/2 , COLS/2 , "You Win the game...");
    attroff(COLOR_PAIR(30));
    mvprintw(LINES/2 + 2 , COLS/2 , "Youe score is %d" , pl->score);
    mvprintw(LINES/2 + 4 , COLS/2 , "You have gathered %d gold" , pl->gold);
    FILE * p;
    char path[1000];
    strcpy(path , pl->Name);
    strcat(path , ".txt");
    p = fopen(path , "w");
    fprintf(p , "%s\n" , pl->Mail);
    fprintf(p , "%s\n" , pl->Pass);
    fprintf(p , "%d\n" , pl->gold);
    fprintf(p , "%d\n" , pl->score);
    pl->tedad++;
    fprintf(p , "%d\n" , pl->tedad);
    fclose(p);
    getch();
}

void play2(Profile *pl){  
    clear();
    board();
    noecho();
    int vaz ;
    Pos* pele1 = (Pos*)malloc(sizeof(Pos) * 1);
    Pos* pele2 = (Pos*)malloc(sizeof(Pos) * 1);
    Pos* pele3 = (Pos*)malloc(sizeof(Pos) * 1);
    Pos* pele4 = (Pos*)malloc(sizeof(Pos) * 1);
    Pos* pele5 = (Pos*)malloc(sizeof(Pos) * 1);
    Pos* noghte = (Pos*)malloc(sizeof(Pos) * 1);
    pele1->x = x1;
    pele1->y = y_1;
    pele2->x = x2;
    pele2->y = y_2;
    pele3->x = x3;
    pele3->y = y_3;
    pele4->x = x4;
    pele4->y = y_4;
    pele5->x = x5;
    pele5->y = y_5;
    if(pl->floor == 1){
        vaz = 10 ;
        pl->pos = player(otagh1 , list1 , floor1 , didan1 , value1);
    }
    if(pl->floor == 2){vaz = 1;}
    if(pl->floor == 3){vaz = 3;}
    if(pl->floor == 4){vaz = 5;}
    if(pl->floor == 5){vaz = 6;}
    pl->HP = 1000000;
    do{
        clear();
        board();
        time(&past_hunger);
        time(&past_food);
        time(&past_monster);
        time(&past_enchant);
        time(&past_heal);
        if(vaz == 1){
            pl->pos = *pele1;
            vaz = play_tabaghe2(otagh2 , list2 , floor2 , didan2 , pl , value2 , ghaza2 , joon2 , donbal2 , oftadeh2);
            for(int i = 0 ; i < LINES ; i++){
                for(int j = 0 ; j < COLS ; j++){
                    donbal2[i][j] = 0;
                }
            }
        }else if(vaz == 2){
            pl->pos = *pele1;
            vaz = play_tabaghe1(otagh1 , list1 , floor1 , didan1 , pl , value1 , ghaza1 , joon1 , donbal1 , oftadeh1);
            for(int i = 0 ; i < LINES ; i++){
                for(int j = 0 ; j < COLS ; j++){
                    donbal1[i][j] = 0;
                }
            }
        }else if(vaz == 3){
            pl->pos = *pele2;
            vaz = play_tabaghe3(otagh3 , list3 , floor3 , didan3 , pl , value3 , ghaza3 , joon3 , donbal3 , oftadeh3);
            for(int i = 0 ; i < LINES ; i++){
                for(int j = 0 ; j < COLS ; j++){
                    donbal3[i][j] = 0;
                }
            }
        }else if(vaz == 4){
            pl->pos = *pele2;
            vaz = play_tabaghe2(otagh2 , list2 , floor2 , didan2 , pl , value2 , ghaza2 , joon2 , donbal2 , oftadeh2);
            for(int i = 0 ; i < LINES ; i++){
                for(int j = 0 ; j < COLS ; j++){
                    donbal2[i][j] = 0;
                }
            }
        }else if(vaz == 5){
            pl->pos = *pele3;
            vaz = play_tabaghe4(otagh4 , list4 , floor4 , didan4 , pl , value4 , ghaza4 , joon4 , donbal4 , oftadeh4);
            for(int i = 0 ; i < LINES ; i++){
                for(int j = 0 ; j < COLS ; j++){
                    donbal4[i][j] = 0;
                }
            }
        }else if(vaz == 6){
            pl->pos = *pele4;
            vaz = play_tabaghe5(otagh5 , list5 , floor5 , didan5 , pl , value5 , ghaza5 , joon5 , donbal5 , oftadeh5);
            for(int i = 0 ; i < LINES ; i++){
                for(int j = 0 ; j < COLS ; j++){
                    donbal5[i][j] = 0;
                }
            }
            if(vaz == 9){
                timeout(-1);
                bordan(pl);
                getch();
                break;
            }
        }else if(vaz == 7){
            pl->pos = *pele3;
            vaz = play_tabaghe3(otagh3 , list3 , floor3 , didan3 , pl , value3 , ghaza3 , joon3 , donbal3 , oftadeh3);
            for(int i = 0 ; i < LINES ; i++){
                for(int j = 0 ; j < COLS ; j++){
                    donbal3[i][j] = 0;
                }
            }
        }else if(vaz == 8){
            pl->pos = *pele4;
            vaz = play_tabaghe4(otagh4 , list4 , floor4 , didan4 , pl , value4 , ghaza4 , joon4 , donbal4 , oftadeh4);
            for(int i = 0 ; i < LINES ; i++){
                for(int j = 0 ; j < COLS ; j++){
                    donbal4[i][j] = 0;
                }
            }
        }else if(vaz == 9){
            bordan(pl);
            break;
        }else if(vaz == 10){
            vaz = play_tabaghe1(otagh1 , list1 , floor1 , didan1 , pl , value1 , ghaza1 , joon1 , donbal1 , oftadeh1);
            for(int i = 0 ; i < LINES ; i++){
                for(int j = 0 ; j < COLS ; j++){
                    donbal1[i][j] = 0;
                }
            }
        }
    }while(vaz != 0 && vaz != 20);
    if(vaz == 20){
        clear();
        board();
        init_pair(1 , COLOR_RED , COLOR_BLACK);
        attron(COLOR_PAIR(1));
        mvprintw(LINES/2 , COLS/2 , "You lost the game...");
        attroff(COLOR_PAIR(1));
    }
    if(vaz == 0){
        Save(pl);
        getch();
    }
    getch();
}

void play(Profile *pl){
    clear();
    board();
    noecho();
    int ch;
    int vaz;
    Pos* pele1 = (Pos*)malloc(sizeof(Pos) * 1);
    Pos* pele2 = (Pos*)malloc(sizeof(Pos) * 1);
    Pos* pele3 = (Pos*)malloc(sizeof(Pos) * 1);
    Pos* pele4 = (Pos*)malloc(sizeof(Pos) * 1);
    Pos* pele5 = (Pos*)malloc(sizeof(Pos) * 1);
    Pos* noghte = (Pos*)malloc(sizeof(Pos) * 1);
    noghte->x = 0;
    noghte->y = 0;
    int otagh1 = tabaghe_saz(pl , list1 , didan1 , value1 , floor1 , 0 , noghte , ghaza1 , joon1 , oftadeh1);
    *pele1 = *noghte;
    int otagh2 = tabaghe_saz(pl , list2 , didan2 , value2 , floor2 , 1 , noghte , ghaza2 , joon2 , oftadeh2);
    *pele2 = *noghte;
    int otagh3 = tabaghe_saz(pl , list3 , didan3 , value3 , floor3 , 2 , noghte , ghaza3 , joon3 , oftadeh3);
    *pele3 = *noghte;
    int otagh4 = tabaghe_saz(pl , list4 , didan4 , value4 , floor4 , 3 , noghte , ghaza4 , joon4 , oftadeh4);
    *pele4 = *noghte;
    int otagh5 = tabaghe_saz(pl , list5 , didan5 , value5 , floor5 , 4 , noghte , ghaza5 , joon5 , oftadeh5);
    *pele5 = *noghte;
    pl->pos = player(otagh1 , list1 , floor1 , didan1 , value1);
    pl->HP = 21;
    vaz = 10;
    x1 = pele1->x;
    x2 = pele2->x;
    x3 = pele3->x;
    x4 = pele4->x;
    x5 = pele5->x;
    y_1 = pele1->y;
    y_2 = pele2->y;
    y_3 = pele3->y;
    y_4 = pele4->y;
    y_5 = pele5->y;
    do{
        clear();
        board();
        time(&past_hunger);
        time(&past_food);
        time(&past_monster);
        time(&past_enchant);
        time(&past_heal);
        if(vaz == 1){
            pl->pos = *pele1;
            vaz = play_tabaghe2(otagh2 , list2 , floor2 , didan2 , pl , value2 , ghaza2 , joon2 , donbal2 , oftadeh2);
            for(int i = 0 ; i < LINES ; i++){
                for(int j = 0 ; j < COLS ; j++){
                    donbal2[i][j] = 0;
                }
            }
        }else if(vaz == 2){
            pl->pos = *pele1;
            vaz = play_tabaghe1(otagh1 , list1 , floor1 , didan1 , pl , value1 , ghaza1 , joon1 , donbal1 , oftadeh1);
            for(int i = 0 ; i < LINES ; i++){
                for(int j = 0 ; j < COLS ; j++){
                    donbal1[i][j] = 0;
                }
            }
        }else if(vaz == 3){
            pl->pos = *pele2;
            vaz = play_tabaghe3(otagh3 , list3 , floor3 , didan3 , pl , value3 , ghaza3 , joon3 , donbal3 , oftadeh3);
            for(int i = 0 ; i < LINES ; i++){
                for(int j = 0 ; j < COLS ; j++){
                    donbal3[i][j] = 0;
                }
            }
        }else if(vaz == 4){
            pl->pos = *pele2;
            vaz = play_tabaghe2(otagh2 , list2 , floor2 , didan2 , pl , value2 , ghaza2 , joon2 , donbal2 , oftadeh2);
            for(int i = 0 ; i < LINES ; i++){
                for(int j = 0 ; j < COLS ; j++){
                    donbal2[i][j] = 0;
                }
            }
        }else if(vaz == 5){
            pl->pos = *pele3;
            vaz = play_tabaghe4(otagh4 , list4 , floor4 , didan4 , pl , value4 , ghaza4 , joon4 , donbal4 , oftadeh4);
            for(int i = 0 ; i < LINES ; i++){
                for(int j = 0 ; j < COLS ; j++){
                    donbal4[i][j] = 0;
                }
            }
        }else if(vaz == 6){
            pl->pos = *pele4;
            vaz = play_tabaghe5(otagh5 , list5 , floor5 , didan5 , pl , value5 , ghaza5 , joon5 , donbal5 , oftadeh5);
            for(int i = 0 ; i < LINES ; i++){
                for(int j = 0 ; j < COLS ; j++){
                    donbal5[i][j] = 0;
                }
            }
            if(vaz == 9){
                timeout(-1);
                bordan(pl);
                getch();
                break;
            }
        }else if(vaz == 7){
            pl->pos = *pele3;
            vaz = play_tabaghe3(otagh3 , list3 , floor3 , didan3 , pl , value3 , ghaza3 , joon3 , donbal3 , oftadeh3);
            for(int i = 0 ; i < LINES ; i++){
                for(int j = 0 ; j < COLS ; j++){
                    donbal3[i][j] = 0;
                }
            }
        }else if(vaz == 8){
            pl->pos = *pele4;
            vaz = play_tabaghe4(otagh4 , list4 , floor4 , didan4 , pl , value4 , ghaza4 , joon4 , donbal4 , oftadeh4);
            for(int i = 0 ; i < LINES ; i++){
                for(int j = 0 ; j < COLS ; j++){
                    donbal4[i][j] = 0;
                }
            }
        }else if(vaz == 9){
            bordan(pl);
            break;
        }else if(vaz == 10){
            vaz = play_tabaghe1(otagh1 , list1 , floor1 , didan1 , pl , value1 , ghaza1 , joon1 , donbal1 , oftadeh1);
            for(int i = 0 ; i < LINES ; i++){
                for(int j = 0 ; j < COLS ; j++){
                    donbal1[i][j] = 0;
                }
            }
        }
    }while(vaz != 0 && vaz != 20);
    if(vaz == 20){
        clear();
        board();
        init_pair(1 , COLOR_RED , COLOR_BLACK);
        attron(COLOR_PAIR(1));
        mvprintw(LINES/2 , COLS/2 , "You lost the game...");
        attroff(COLOR_PAIR(1));
    }
    if(vaz == 0){
        Save(pl);
        getch();
    }
    getch();
}

void Difficulty(Profile *pl){
    clear();
    board();
    int z = COLS/2;
    mvprintw(13 , z-10 , "Settings :");
    char *choice[] = {"Begginer" , "Normal (difault)" , "Hard"};
    int vaz = 0;
    while (1){
        for (int i = 0; i < 3; i++){
            if (vaz == i){
                attron(A_REVERSE);
            }
            mvprintw(15 + 2*i, z - 10, "%s", choice[i]);
            if (vaz == i){
                attroff(A_REVERSE);
            }
        }
        int ch = getch();
        if (ch == KEY_UP){
            if(vaz != 0){
                vaz --;
            }
        }else if(ch == KEY_DOWN){
            if(vaz != 2){
                vaz++;
            }
        }else if (ch == '\n'){
            break;
        }
    }
    if(vaz == 0){//Beginner
        pl->diff = 1;
    }else if(vaz == 1){//Normal
        pl->diff = 2;
    }else if(vaz == 2){//Hard
        pl->diff = 3;
    }
    Setting(pl);
}

void Color(Profile *pl){
    clear();
    board();
    int z = COLS/2;
    mvprintw(13 , z-10 , "Colors :");
    char *choice[] = {"White (diffault)" , "Red" , "Cyan"};
    int vaz = 0;
    while (1){
        for (int i = 0; i < 3; i++){
            if (vaz == i){
                attron(A_REVERSE);
            }
            mvprintw(15 + 2*i, z - 10, "%s", choice[i]);
            if (vaz == i){
                attroff(A_REVERSE);
            }
        }
        int ch = getch();
        if (ch == KEY_UP){
            if(vaz != 0){
                vaz --;
            }
        }else if(ch == KEY_DOWN){
            if(vaz != 2){
                vaz++;
            }
        }else if (ch == '\n'){
            break;
        }
    }
    if(vaz == 0){//white
        pl->color = 1;
    }else if(vaz == 1){//res
        pl->color = 2;
    }else if(vaz == 2){//cyan
        pl->color = 3;
    }
    Setting(pl);
}

void Setting(Profile *pl){
    clear();
    board();
    int z = COLS/2;
    mvprintw(13 , z-10 , "Settings :");
    char *choice[] = {"Difficulty" , "Hero's color" , "Music" , "Back to menu"};
    int vaz = 0;
    while (1){
        for (int i = 0; i < 4; i++){
            if (vaz == i){
                attron(A_REVERSE);
            }
            mvprintw(15 + 2*i, z - 10, "%s", choice[i]);
            if (vaz == i){
                attroff(A_REVERSE);
            }
        }
        int ch = getch();
        if (ch == KEY_UP){
            if(vaz != 0){
                vaz --;
            }
        }else if(ch == KEY_DOWN){
            if(vaz != 3){
                vaz++;
            }
        }else if (ch == '\n'){
            break;
        }
    }
    if(vaz == 0){//Difficulty
        Difficulty(pl);
    }else if(vaz == 1){//Color
        Color(pl);
    }else if(vaz == 2){//Music
        Musicmenu(pl);
    }else if(vaz == 3){
        menu2(pl);
    }
}

void menu2(Profile *pl){
    clear();
    board();
    int z = COLS/2;
    mvprintw(13 , z-10 , "Menu :");
    char *choice[] = {"Play" , "Load past game" , "leaderboard" , "Profile" , "Settings" , "Sign out"};
    int vaz = 0;
    while (1){
        for (int i = 0; i < 6; i++){
            if (vaz == i){
                attron(A_REVERSE);
            }
            mvprintw(15 + 2*i, z - 10, "%s", choice[i]);
            if (vaz == i){
                attroff(A_REVERSE);
            }
        }
        int ch = getch();
        if (ch == KEY_UP){
            if(vaz != 0){
                vaz --;
            }
        }else if(ch == KEY_DOWN){
            if(vaz != 5){
                vaz++;
            }
        }else if (ch == '\n'){
            break;
        }
    }
    if(vaz == 0){//Play
        play(pl);
    }else if(vaz == 1){//Load past game
        int i = loadkon(pl);
        if(i == -1){
            menu2(pl);
        }else{
            play2(pl);
        }
    }else if(vaz == 2){//Leaderboard
        Leaderboard(pl);
    }else if(vaz == 3){//Profile
        profile_neshoon(pl);
    }else if(vaz == 4){//Settings
        Setting(pl);
    }else if(vaz == 5){
        user_menu(pl);
    }
}

int main(){
    Profile pl;
    pl.diff = 2;
    pl.color = 1;
    pl.Dast = -1;
    pl.tedadfood = 0;
    pl.Hunger = 10;
    pl.aslahe[0] = 1;
    pl.aslahe[1] = 0;
    pl.aslahe[2] = 0;
    pl.aslahe[3] = 0;
    pl.aslahe[4] = 0;
    pl.telesm[0] = 0;
    pl.telesm[1] = 0;
    pl.telesm[2] = 0;
    pl.food[0] = 0;
    pl.food[1] = 0;
    pl.food[2] = 0;
    pl.food[3] = 0;
    pl.food[4] = 0;
    pl.Strengh = 0;
    pl.reg = 0;
    pl.Speed = 0;
    pl.floor = 1;
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY , MIX_DEFAULT_FORMAT , MIX_DEFAULT_CHANNELS , 4096);
    SDL_Init(SDL_INIT_AUDIO);
    musicalan = 0;
    setlocale(LC_ALL, "");
    initscr();
    start_color();
    srand(time(0));
    keypad(stdscr, TRUE);
    curs_set(false);
    menu();
    user_menu(&pl);
    endwin();
    return 0;
}