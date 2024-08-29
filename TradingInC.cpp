#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<windows.h>
#include<vector>
#include<math.h>

#define SIZE 26
#define mH 39
#define mW 131

#define CYAN "\e[0;36m"
#define YELLOW "\e[0;33m"
#define PURPLE "\e[0;35m"
#define GREEN "\e[0;32m"
#define RED "\e[0;31m"

#define RESET "\e[0m"
 
char map[mH + 1][mW + 1];
char chart[1000][1000];
bool logged = true, colour;
int idx = 0, window = 0, page, globalHighest, globalClose, globalOpen, globalLowest;

void fullScreen(){
	keybd_event(VK_MENU, 0x38, 0, 0);
	keybd_event(VK_RETURN, 0x1c, 0, 0);
	keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
}

void cursorPosition(int y, int x){
	COORD cp;
	cp.Y = y;
	cp.X = x;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cp);
}

void frontLogo(){
	printf("______________  _______  _________  ________  ________ ___          ___    ___       _______  ___   ___                   _______\n");
	printf("|\\   _ \\  _   \\|\\  ___ \\|\\___   ___\\\\   __  \\|\\  _____\\\\  \\        |\\  \\  /  /|     /  ___  \\|\\  \\ |\\  \\                 /  ___  \\\n");
	printf("\\ \\  \\\\\\__\\ \\  \\ \\   __/\\|___ \\  \\_\\ \\  \\|\\  \\ \\  \\__/\\ \\  \\       \\ \\  \\/  / /    /__/|_/  /\\ \\  \\\\_\\  \\  ____________ /__/|_/  /|\n");
	printf(" \\ \\  \\\\|__| \\  \\ \\  \\_|/__  \\ \\  \\ \\ \\   __  \\ \\   __\\\\ \\  \\       \\ \\    / /     |__|//  / /\\ \\______  \\|\\____________\\__|//  / /\n");
	printf("  \\ \\  \\    \\ \\  \\ \\  \\_|\\ \\  \\ \\  \\ \\ \\  \\ \\  \\ \\  \\_| \\ \\  \\       /     \\/          /  /_/__\\|_____|\\  \\|____________|   /  /_/__\n");
	printf("   \\ \\__\\    \\ \\__\\ \\_______\\  \\ \\__\\ \\ \\__\\ \\__\\ \\__\\   \\ \\__\\     /  /\\   \\         |\\________\\     \\ \\__\\               |\\________\\\n");
	printf("    \\|__|     \\|__|\\|_______|   \\|__|  \\|__|\\|__|\\|__|    \\|__|    /__/ /\\ __\\         \\|_______|      \\|__|                \\|_______|\n");
	printf("                                                                  |__|/  \\|__|                                                                  \n");
	printf("\n");
}

void exitLogo(){
	system("cls");
	puts("                            ............:::::::::::...........");
	puts("                                  ......................");
	puts("                         .......::--==================---::.......");
	puts("                     .....:::--==+++*####%%%%%%%%####*++====--::.....");
	puts("                   ....::--==+*#%%%%%%%%%%%%%%#%%%%%%%%%%%#*+==---:.....");
	puts("                 ...::--=+*##%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#*+=---:....");
	puts("               ....:-=+*#%%%%%%%%%%%%%%%%#%%%%%%%%%%%%%%%%%%%%%%##*=---:....");
	puts("             ....:-=*#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%##%%%%%%%%%%%%%%#+=--:....");
	puts("           ....:-=*#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%####%%##%%%%%%%%%%%%#+--::...");
	puts("          ..:.:-+#%#%%%%%%%%%%%%%%%##%%%%%%%%###%#*+**%#**####%%%%%%%%%%#+--:...");
	puts("         ..:::=*%%%%%%%%%%%##%%%%%%**#%###%%#**#%*+=+=#*++**++#%%#%%%%%%%%*-:::...");
	puts("        ..:::+#%%%%%%%%%%%%########++#%***#**+++#+=---++--==-=*%%%%%%%%%%%%#=:::...");
	puts("       ..::-*#%%%%%%%%%%%%%*+**+*##==+*===*=+-=-+--:::=-:::-::*%%%%%%%%%%%%%#+:::..");
	puts("      ..:::+#%#%%%%%%%%%%%#+==+==++--=+:--=--:::-:...... ..:-=*%%%%%%%%%%%%%%#+:-:..");
	puts("      .:::+#%%%%%%%%%%%%%#*---=---=:::-.:.:.... ::--=+**#%%%%%%%%%%%%%%%%%%%%%#=:-...");
	puts("     ..:.=#%%%%%%%%%%%%%%#+::::...:   ..:-=+++*#%%###%%%%%%%%%%%%%%%%%%%%%%%%%%*-:-..");
	puts("     .:::*#%%%%%%%%%%%%%%*-...:--=+*##%%%%%%#++##%#**%%%%%%%%%###%%%#%%%%%%%%%%#+:-:..");
	puts("    ..:.=#%%%%%%%%%%%#%%%*::+***#%%%###%%%%%*==+*#+++%###%%%%%**#%%%%%%%%%%%%%%#*-:-..");
	puts("    ..:.+#%%%%%%%%%%%%%%%+-=*+=+*###**#%%%%%*-:==+===#*++%####++*%%%%%%%%%%%%%%%*-:-..");
	puts("    ..::+#%%%%%%%%%%%%%%%*--==-==**#++*####%+..::-:::+===#**++==+#%%%%%%%%%%%%%%#=:-:.");
	puts("    ...:+###############%*:.:-:--+=+==*#**#%*=--.. ..-:::+==-=:-=*###############=:::.");
	puts("    ...:+#################+..:..:--=:-=+==*#**#####*+=-:.:.:.:.:-=##############*=-::.");
	puts("    ...:=###################=-.  ..:..:-:-=+=+*###########*+=-...-*#############*--:..");
	puts("    .:.:-*######################*+=-:.....:-:-+***#############*-.+#############+:-:..");
	puts("     ::.-+*####################***#####*+=--:.=+++*****#***#****=-+############*=--:.");
	puts("     .:.:-********#************++************++===**+=+*+++*++==-:+*********#**+--:..");
	puts("      ..:-=*******%#***********+++*+++*+++++*+=---==--==-=-=----..+*********%#+---:.");
	puts("      .:.:-=*****#@@#******+++*===+===+==---+--:::--:::-:::-.:...+*********#@#=--:..");
	puts("       .:.--=+***%@@%*****+===+---=---=--:::-::...::.... . ..:-+**********#%%+=-:..");
	puts("        .:.--+*#%%@@@#****+----:::-.:.:.:...:.   ..::--==++++++++***#%****##+==:..");
	puts("         ...-=+#@@@@@%%*+*+:.::....   ...::--===+++++++++++++++*+++#@@%+#%*===:..");
	puts("          ...:==#%@@@@@*+%*  .:::--==+++++++++++++++++++++++++*@#++%@@%##+==-:..");
	puts("            ..:-=+%@@@#+%@@++++++++++++++*#+++++++++++*+++++++%@%#%%@@%+-==-..");
	puts("             ...:-=+%@@@@@@%++++++++++++*%@#++++++++++@%++++*%@@@@@@%#+==-:..");
	puts("               ..::-=+#%@@@@%+=+*@*====+#@@%*=======+%@@*+==*@@@@%%*+==-:..");
	puts("                 ..::--=+#%@%==+@@%+==+%@@@@*+++===+*%@@%+=#%@@%*+===-:..");
	puts("                   ...::--=+***#@@@*==*@@@@@@%#%+==*@@@@@##%#*+===-::..");
	puts("                     ....:-----+*#%%***%@@@@@%@@*==+%%%#*+====--::..");
	puts("                        ....::-------=++********+=====-------::..");
	puts("                             ....::---======--=====-----::...");
	puts("                                   ........::::........");
	puts("");
    printf("                    \"Inspired by passion, driven by purpose, together we\n");
    printf("                         shatter limits and redefine boundaries.\"\n");
    printf(PURPLE "\n                                        Meta Fi\n" RESET);
	printf(GREEN "                                Created with 24-2 Squad\n" RESET);
	printf(RESET "                                     Thank you 24-2 !\n");
}

struct trade{
	int value;
	int position;
	int profit;
	int loss;
	int reward;
	trade *next;
	trade *prev;
};

trade *createTrade(int Value, int Position, int Profit, int Loss, int Reward){
	trade *newTrade = (trade*)malloc(sizeof(trade));
	newTrade->value = Value;
	newTrade->position = Position;
	newTrade->profit = Profit;
	newTrade->loss = Loss;
	newTrade->reward = Reward;
	newTrade->next = NULL;
	newTrade->prev = NULL;
	return newTrade;
}

struct node{
	char name[100];
	char email[100];
	char password[100];
	int money;
	bool status;
	int green;
	int red;
	int white;
	node *next;
	trade *Head, *Tail, *Cur;
}*hashTable[SIZE] = {NULL};

node *createNode(const char *Name, const char *Email, const char *Password, int Money, bool Status, int Green, int Red, int White){
	node *newNode = (node*)malloc(sizeof(node));
	strcpy(newNode->name, Name);
	strcpy(newNode->email, Email);
	strcpy(newNode->password, Password);
	newNode->money = Money;
	newNode->status = Status;
	
	newNode->red = Red;
	newNode->green = Green;
	newNode->white = White;
	
	newNode->Head = NULL;
	newNode->Tail = NULL;
	newNode->next = NULL;
	return newNode;
}

int hashKey(const char *Name){
	int key = 0;
	int lenName = strlen(Name);
	for(int i = 0; i < lenName; i++){
		key += Name[i] - 'a' + 'a';
	}
	return key % SIZE;
}

void insertChaining(const char *Name, const char *Mail, const char *Pass, int Money, bool Status, int Green, int Red, int White){
	int key = hashKey(Name);
	if(!hashTable[key]){
		hashTable[key] = createNode(Name, Mail, Pass, Money, Status, Green, Red, White);	
	}else{
		node *cur = hashTable[key];
		while(cur->next != NULL){
			cur = cur->next;
		}
		cur->next = createNode(Name, Mail, Pass, Money, Status, Green, Red, White);
	}
}

void printChaining(){
	system("cls");
	for(int i = 0; i < SIZE; i++){
		if(hashTable[i]->name == NULL){
			printf("%d. -\n", i);
		}else{
			printf("%d. %s", i, hashTable[i]->name);
			node *cur = hashTable[i];
			while(cur->next != NULL){
				printf(" -> %s", cur->next->name);
				cur = cur->next;
			}
			printf("\n");
		}
	}
}

void pushHead(node *account, int Value, int Position, int Profit, int Loss, int Reward){
	if(account->Head == NULL && account->Tail == NULL){
		account->Head = account->Tail = createTrade(Value, Position, Profit, Loss, Reward);
	}else{
		trade *temp = createTrade(Value, Position, Profit, Loss, Reward);
		temp->next = account->Head;
		account->Head->prev = temp;
		account->Head = temp;
	}
}

void pushTail(node *account, int Value, int Position, int Profit, int Loss, int Reward){
	if(account->Head == NULL && account->Tail == NULL){
		account->Head = account->Tail = createTrade(Value, Position, Profit, Loss, Reward);
	}else{
		trade *temp = createTrade(Value, Position, Profit, Loss, Reward);
		temp->prev = account->Tail;
		account->Tail->next = temp;
		account->Tail = temp;
	}
}

void pushMid(node *account, int Value, int Position, int Profit, int Loss, int Reward){
	if(account->Head == NULL){
		account->Head = account->Tail = createTrade(Value, Position, Profit, Loss, Reward);
	}else if(Reward > account->Head->reward){
		pushHead(account, Value, Position, Profit, Loss, Reward);
	}else if(Reward < account->Tail->reward){
		pushTail(account, Value, Position, Profit, Loss, Reward);
	}else{
		trade *cur = account->Head;
		trade *temp = createTrade(Value, Position, Profit, Loss, Reward);
		while(cur && Reward > cur->next->reward){
			cur = cur->next;
		}
		cur->next->prev = temp;
		temp->next = cur->next;
		
		temp->prev = cur;
		cur->next = temp;
	}
}

struct stick{
	int highestPrice;
	int closePrice;
	int openPrice;
	int lowestPrice;
	int index;
	bool profit;
	stick *next;
	stick *prev;
}*headStick = NULL, *tailStick = NULL;

stick *createStick(int HP, int CP, int OP, int LP, int Index, bool Profit){
	stick *newStick = (stick*)malloc(sizeof(stick));
	newStick->highestPrice = HP;
	newStick->closePrice = CP;
	newStick->openPrice = OP;
	newStick->lowestPrice = LP;
	newStick->index = Index;
	newStick->profit = Profit;
	newStick->next = NULL;
	newStick->prev = NULL;
	return newStick;
}

void pushStickTail(int hP, int cP, int oP, int lP, int index, bool profit){
	if(headStick == NULL && tailStick == NULL){
		headStick = tailStick = createStick(hP, cP, oP, lP, index, profit);
	}else{
		stick *cur = tailStick;
		cur->next = createStick(hP, cP, oP, lP, index, profit);
		cur->next->prev = tailStick;
		tailStick = cur->next;
	}
}

void readTable(){
	FILE *fp = fopen("user.txt", "r");
	int currency;
	char user[100], mail[100], pass[100];
	while(!feof(fp)){
		fscanf(fp, "%[^#]#%[^#]#%[^#]#%d\n", user, mail, pass, &currency);
		insertChaining(user, mail, pass, currency, false, 0, 0, 0);
	}
	fclose(fp);
}

void updateFile(){
	FILE *fp = fopen("user.txt", "w");
	for(int i = 0; i < SIZE; i++){
		node* cur = hashTable[i];
		while(cur){
			fprintf(fp, "%s#%s#%s#%d\n",cur->name, cur->email, cur->password, cur->money);
			cur = cur->next;
		}
	}
	fclose(fp);
}

void initMap(){
	for(int i = 0; i < mH; i++){
		for(int j = 0; j < mW; j++){
			if(i == 0 || i == mH - 1 || i == mH - 5){
				map[i][j] = 205;
			}else if(j == 0 || j == mW - 1 || j == mW - 7){
				if(j == 124 && i > mH - 5){
					map[i][j] = ' ';
				}else{
					map[i][j] = 186;
				}
			}else if(j == 107 || j == 39){
				if(i > mH - 5){
					map[i][j] = 186;
				}else{
					map[i][j] = ' ';
				}
			}else{
				map[i][j] = ' ';
			}
		}
	}
	map[34][130] = 185;
	map[0][130] = 187;
	map[34][130] = 185;
	map[38][130] = 188;
	map[38][0] = 200;
	map[0][0] = 201;
	map[38][107] = map[38][39] = map[34][124] = 202;
	map[34][107] = map[34][39] = map[0][124] = 203;
	map[34][0] = 204;
}

void initChart(){
	for(int i = 0;i < 1000; i++){
		for(int j = 0; j < 1000; j++){
			chart[i][j] = '-';
		}
	}
}

void printChart(){
    int index;
    bool profit;
    for(int i = 0; i < 33; i++){
    	stick *cur = headStick;
    	for(int l = 0; l < window; l++){
    		cur = cur->next;
		}
    	cursorPosition(1 + i, 1);
        for(int j = window; j < window + 123; j++){
            if(cur){
                index = cur->index;
                profit = cur->profit;
            }else{
                index = profit = -1;
            }

            if(j == index && !profit && chart[i][j] != '-'){
                printf(RED "%c" RESET, chart[i][j]); 
            }else if(j == index && profit && chart[i][j] != '-'){
                printf(GREEN "%c" RESET, chart[i][j]); 
            }else{
                printf(RESET "%c", chart[i][j]); 
                Sleep(0.5);
            }
            if(cur){
            	cur = cur->next;	
			}
        }
        printf("\n");
    }
}

void printLine(node *account){
	stick *cur;
	if(account->status){
		cursorPosition(account->green + 1, 1);
		cur = headStick;
		for(int i = 0; i < 123; i++){
			if(chart[account->green][i] == '-'){
				printf(GREEN "%c", chart[account->green][i]);
			}else if(cur->index == i && cur->profit && chart[account->green][i] != '-'){
				printf(GREEN "%c", chart[account->green][i]);
			}else if(cur->index == i && !cur->profit && chart[account->green][i] != '-'){
				printf(RED "%c", chart[account->green][i]);
			}
			if(cur){
				cur = cur->next;
			}
		}
		
		cursorPosition(account->red + 1, 1);
		cur = headStick;
		for(int i = 0; i < 123; i++){
			if(chart[account->red][i] == '-'){
				printf(RED "%c", chart[account->red][i]);
			}else if(cur->index == i && cur->profit && chart[account->red][i] != '-'){
				printf(GREEN "%c", chart[account->red][i]);
			}else if(cur->index == i && !cur->profit && chart[account->red][i] != '-'){
				printf(RED "%c", chart[account->red][i]);
			}
			if(cur){
				cur = cur->next;
			}
		}
		
		cursorPosition(account->white + 1, 1);
		cur = headStick;
		for(int i = 0; i < 123; i++){
			if(chart[account->white][i] == '-'){
				printf(YELLOW "%c", chart[account->white][i]);
			}else if(cur->index == i && cur->profit && chart[account->white][i] != '-'){
				printf(GREEN "%c", chart[account->white][i]);
			}else if(cur->index == i && !cur->profit && chart[account->white][i] != '-'){
				printf(RED "%c", chart[account->white][i]);
			}
			if(cur){
				cur = cur->next;
			}
		}
	}
	printf(RESET);
}

void printMap(){
	for(int i = 0; i < mH; i++){
		for(int j = 0; j < mW; j++){
			printf("%c", map[i][j]);
		}
		printf("\n");
	}
}

void printNum(){
	int num = 330;
	for(int i = 0; i < 33; i++){
		cursorPosition(1 + i, 126);
		printf("%d", num);
		num -= 10;
	}
}

int printBottomLeft(node *account){
	int opt;
	cursorPosition(35, 2);
	printf(GREEN "Welcome To METAFI, " CYAN "%s" RESET, account->name);
	cursorPosition(36, 2);
	printf("1. New Day");
	cursorPosition(37, 2);
	printf("2. Previous");
	cursorPosition(36, 15);
	printf("3. Next");
	cursorPosition(37, 15);
	printf("4. Long");
	cursorPosition(36, 24);
	printf("5. Short");
	cursorPosition(37, 24);
	printf("6. Logout");
	cursorPosition(37, 34);
	printf(YELLOW ">> " RESET);

	cursorPosition(37, 37);
	opt = 0;
	scanf("%d", &opt); getchar();
	return opt;
}

void printBottomRight(node *account){
	cursorPosition(35, 44);
	printf("Value	:");
	cursorPosition(36, 44);
	printf("Position	:");
	cursorPosition(35, 69);
	printf("TP	:");
	cursorPosition(36, 69);
	printf("SL	:");
		
	cursorPosition(36, 109);
	printf("$%d", account->money);
}

int lowestPrice(int bottom){
	int lP = rand() % 33;
	int chanceLine = rand() % 100 + 1;
	if(chanceLine <= 30){
		lP = bottom;
	}else{
		while(lP >= bottom + 4 || lP <= bottom){
			lP = bottom + (rand() % 4) + 1;
			if(lP >= 32){
				lP = 32;
			}
		}
	}
	return lP;
}

int blockPrice(int bot){
	int block = rand() % 33;
	int chanceBlock = rand() % 100 + 1;
	if(chanceBlock <= 10){
		block = bot;
	}else{
		while(block <= bot - 6 || block >= bot){
			block = rand() % 33 + 1;
		}
	}
	return block;
}

int highestPrice(int top){
	int hP = rand() % 33;
	int chanceLine = rand() % 100 + 1;
	if(chanceLine <= 30){
		hP = top;
	}else{
		while(hP >= top || hP <= top - 5){
			hP = top - (rand() % 4) + 1;
			if(hP <= 0){
				hP = 0;
			}
		}
	}
	return hP;
}

void loopTrue(int high, int close, int open, int low){
	for(int i = close; i <= open; i++){
		chart[i][idx] = 219;
	}
	for(int i = high; i < close; i++){
		chart[i][idx] = 179;
	}
	for(int i = open + 1; i <= low; i++){
		chart[i][idx] = 179;
	}
}

void loopFalse(int high, int open, int close, int low){
	for(int i = open; i <= close; i++){
		chart[i][idx] = 219;
	}
	for(int i = high; i	 < open; i++){
		chart[i][idx] = 179;
	}
	for(int i = close + 1; i <= low; i++){
		chart[i][idx] = 179;
	}
}

void firstCandle(){
	int hP, oP, cP, lP;
	colour = rand() % 2;
	
	oP = rand() % 33;
	cP = rand() % 33;
	
	if(colour){
		if(oP <= 0){
			hP = oP;
			cP = oP;
			lP = lowestPrice(oP);
		}else if(oP >= 32){
			lP = oP;
			cP = blockPrice(oP);
			hP = highestPrice(cP);
		}else{
			cP = blockPrice(oP);
			hP = highestPrice(cP);
			lP = lowestPrice(oP);
		}
		loopTrue(hP, cP, oP, lP);
		pushStickTail(hP, cP, oP, lP, idx, colour);
	}else{
		if(cP <= 0){
			hP = cP;
			oP = cP;
			lP = lowestPrice(cP);
		}else if(cP >= 32){
			lP = cP;
			oP = blockPrice(cP);
			hP = highestPrice(oP);
		}else{
			oP = blockPrice(cP);
			hP = highestPrice(oP);
			lP = lowestPrice(cP);
		}
		loopFalse(hP, oP, cP, lP);
		pushStickTail(hP, cP, oP, lP, idx, colour);
	}
	idx++;
}

void otherCandle(){
	int close, open, high, low;
	int chanceBlock, chanceProfit;
	int stickHigh;
	int stickLow;
	colour = false;
	
	stick *cur = tailStick;
	open = cur->closePrice;
	
	chanceBlock = rand() % 100 + 1;
	chanceProfit = rand() % 100 + 1;
	if(chanceBlock <= 10){
		close = open;
	}else{
		if(chanceProfit <= 50){
			close = open - (rand() % 6) + 1;
			if(close <= 0){
				close = 0;
			}
			colour = true;
		}else{
			close = open + (rand() % 6) + 1;
			if(close >= 32){
				close = 32;
			}
			colour = false;
		}
	}
	
	stickHigh = rand() % 100 + 1;
	if(close < open){
		if(stickHigh <= 30){
			high = close;
		}else{
			high = close - rand() % 4 + 1;
			if(high <= 0){
				high = 0;
			}
		}
	}else{
		if(stickHigh <= 30){
			high = open;
		}else{
			high = open - rand() % 4 + 1;
			if(high <= 0){
				high = 0;
			}
		}
	}
	
	stickLow = rand() % 100 + 1;
	if(close < open){
		if(stickLow <= 30){
			low = open;
		}else{
			low = open + rand() % 4 + 1;
		}
	}else{
		if(stickLow <= 30){
			low = close;
		}else{
			low = close + rand() % 4 + 1;
		}
	}

	pushStickTail(high, close, open, low, idx, colour);
	if(colour){
		loopTrue(high, close, open, low);
	}else{
		loopFalse(high, open, close, low);
	}
	globalHighest = high;
	globalOpen = open;
	globalClose = close;
	globalLowest = low;
	idx++;
}

void firstData(){
	firstCandle();
	for(int i = 1; i < 20; i++){
		otherCandle();
	}
}

void nextPage(){
	window++;
	page++;
	if(window >= 123){
		window = 123;
	}
	if(page >= 123){
		page = 123;
	}
}

void prevPage(){
	window--;
	page--;
	if(window <= 0){
		window = 0;
	}
	if(page <= 0){
		page = 0;
	}
}

void resetMessage(int y, int x){
	cursorPosition(y, x);
	for(int i = 0; i < 50; i++){
		printf(" ");
	}
}

void buyStick(node *acc){
	if(acc->status){
		cursorPosition(37, 44);
		printf(RED "A Position Already Open, Please Wait! Enter to continue" RESET); getchar();
		cursorPosition(37, 44);
		printf("                                                       ");
		return;
	}
	
	int value, position, takeProfit, stopLoss;
	bool checkMoney;
	do{
		cursorPosition(35, 58);
		checkMoney = true;
		scanf("%d", &value); getchar();
		if(value < 10 || value > acc->money) checkMoney = false;
		if(!checkMoney){
			cursorPosition(37, 44);
			printf(RED "The Value Must Between 10 and %d" RESET, acc->money);
			cursorPosition(35, 58);
			printf("          ");
		}
	}while(!checkMoney);
	resetMessage(37, 44);
	
	bool checkPosition, checkMultiple;
	do{
		cursorPosition(36, 58);
		checkPosition = true;
		checkMultiple = true;
		scanf("%d", &position); getchar();
		if(position % 10 != 0) checkMultiple = false;
		if(position < 20 || position > 320) checkPosition = false;
		if(!checkPosition){
			cursorPosition(37, 44);
			printf(RED "Position Must Between 20 and 320!" RESET); 
			cursorPosition(36, 58);
			printf("          ");
			continue;
		}
		if(!checkMultiple){
			cursorPosition(37, 44);
			printf(RED "Input is not in Multiple of 10!  " RESET);
			cursorPosition(36, 58);
			printf("          ");
			continue;
		}
	}while(!checkPosition || !checkMultiple);
	resetMessage(37, 44);
	
	bool tpHigher, tpMultiple, tpPosition;
	do{
		cursorPosition(35, 74);
		tpHigher = true;
		tpMultiple = true;
		tpPosition = true;
		scanf("%d", &takeProfit); getchar();
		if(takeProfit % 10 != 0) tpMultiple = false;
		if(takeProfit <= position) tpHigher = false;
		if(takeProfit < 10 || takeProfit > 330) tpPosition = false;
		
		if(!tpPosition){
			cursorPosition(37, 44);
			printf(RED "Take Profit Is Invalid!                        " RESET);
			cursorPosition(35, 74);
			printf("     ");
			continue;
		}
		if(!tpMultiple){
			cursorPosition(37, 44);
			printf(RED "Input is not in Multiple of 10!                " RESET);
			cursorPosition(35, 74);
			printf("     ");
			continue;
		}
		if(!tpHigher){
			cursorPosition(37, 44);
			printf(RED "Take Profit Should Be Higher Than The Position!" RESET);
			cursorPosition(35, 74);
			printf("     ");
			continue;
		}		
	}while(!tpMultiple || !tpHigher || !tpPosition);
	resetMessage(37, 44);
	
	bool slPosition, slMultiple, slLower;
	do{
		cursorPosition(36, 74);
		slPosition = true;
		slMultiple = true;
		slLower = true;
		scanf("%d", &stopLoss); getchar();
		if(stopLoss >= position) slLower = false;
		if(stopLoss % 10 != 0) slMultiple = false;
		if(stopLoss < 10 || stopLoss > 330) slPosition = false;
		
		if(!slPosition){
			cursorPosition(37, 44);
			printf(RED "Stop Loss Is Invalid!                       " RESET);
			cursorPosition(36, 74);
			printf("     ");
			continue;
		}
		if(!slLower){
			cursorPosition(37, 44);
			printf(RED "Stop Loss Should Be Lower Than The Position!" RESET);
			cursorPosition(36, 74);
			printf("     ");
			continue;
		}
		if(!slMultiple){
			cursorPosition(37, 44);
			printf(RED "Input is not in Multiple of 10!             " RESET);
			cursorPosition(36, 74);
			printf("     ");
			continue;
		}
	}while(!slPosition || !slMultiple || ! slLower);
	resetMessage(37, 44);
	acc->status = true;
	acc->Cur = createTrade(value, position, takeProfit, stopLoss, 0);
	
	acc->green = 33;
	while(takeProfit > 0){
		acc->green--;
		takeProfit -= 10;
	}

	acc->white = 33;
	while(position >0){
		acc->white--;
		position -= 10;
	}

	acc->red = 33;
	while(stopLoss > 0){
		acc->red--;
		stopLoss -= 10;
	}
}

void sellStick(node *acc){
	if(acc->status){
		cursorPosition(37, 44);
		printf(RED "A Position Already Open, Please Wait! Enter to continue" RESET); getchar();
		cursorPosition(37, 44);
		printf("                                                       ");
		return;
	}
	
	int value, position, takeProfit, stopLoss;
	bool checkMoney;
	do{
		cursorPosition(35, 58);
		checkMoney = true;
		scanf("%d", &value); getchar();
		if(value < 10 || value > acc->money) checkMoney = false;
		if(!checkMoney){
			cursorPosition(37, 44);
			printf(RED "The Value Must Between 10 and %d" RESET, acc->money);
			cursorPosition(35, 58);
			printf("          ");
		}
	}while(!checkMoney);
	resetMessage(37, 44);
	
	bool checkPosition, checkMultiple;
	do{
		cursorPosition(36, 58);
		checkPosition = true;
		checkMultiple = true;
		scanf("%d", &position); getchar();
		if(position % 10 != 0) checkMultiple = false;
		if(position < 20 || position > 320) checkPosition = false;
		if(!checkPosition){
			cursorPosition(37, 44);
			printf(RED "Position Must Between 20 and 320!" RESET); 
			cursorPosition(36, 58);
			printf("          ");
			continue;
		}
		if(!checkMultiple){
			cursorPosition(37, 44);
			printf(RED "Input is not in Multiple of 10!  " RESET);
			cursorPosition(36, 58);
			printf("          ");
			continue;
		}
	}while(!checkPosition || !checkMultiple);
	resetMessage(37, 44);
	
	bool tplower, tpMultiple, tpPosition;
	do{
		cursorPosition(35, 74);
		tplower = true;
		tpMultiple = true;
		tpPosition = true;
		scanf("%d", &takeProfit); getchar();
		if(takeProfit % 10 != 0) tpMultiple = false;
		if(takeProfit >= position) tplower = false;
		if(takeProfit < 10 || takeProfit > 330) tpPosition = false;
		
		if(!tpPosition){
			cursorPosition(37, 44);
			printf(RED "Take Profit Is Invalid!                        " RESET);
			cursorPosition(35, 74);
			printf("     ");
			continue;
		}
		if(!tpMultiple){
			cursorPosition(37, 44);
			printf(RED "Input is not in Multiple of 10!                " RESET);
			cursorPosition(35, 74);
			printf("     ");
			continue;
		}
		if(!tplower){
			cursorPosition(37, 44);
			printf(RED "Take Profit Should Be Lower Than The Position! " RESET);
			cursorPosition(35, 74);
			printf("     ");
			continue;
		}		
	}while(!tpMultiple || !tplower || !tpPosition);
	resetMessage(37, 44);
	
	bool slPosition, slMultiple, slHigher;
	do{
		cursorPosition(36, 74);
		slPosition = true;
		slMultiple = true;
		slHigher = true;
		scanf("%d", &stopLoss); getchar();
		if(stopLoss <= position) slHigher = false;
		if(stopLoss % 10 != 0) slMultiple = false;
		if(stopLoss < 10 || stopLoss > 330) slPosition = false;
		
		if(!slPosition){
			cursorPosition(37, 44);
			printf(RED "Stop Loss Is Invalid!                        " RESET);
			cursorPosition(36, 74);
			printf("     ");
			continue;
		}
		if(!slHigher){
			cursorPosition(37, 44);
			printf(RED "Stop Loss Should Be Higher Than The Position!" RESET);
			cursorPosition(36, 74);
			printf("     ");
			continue;
		}
		if(!slMultiple){
			cursorPosition(37, 44);
			printf(RED "Input is not in Multiple of 10!              " RESET);
			cursorPosition(36, 74);
			printf("     ");
			continue;
		}
	}while(!slPosition || !slMultiple || ! slHigher);
	resetMessage(37, 44);
	acc->status = true;
	acc->Cur = createTrade(value, position, takeProfit, stopLoss, 0);
	
	acc->green = 33;
	while(takeProfit > 10){
		acc->green--;
		takeProfit -= 10;
	}
	
	acc->white = 33;
	while(position >0){
		acc->white--;
		position -= 10;
	}
	
	acc->red = 33;
	while(stopLoss > 10){
		acc->red--;
		stopLoss -= 10;
	}
	
	acc->Cur->value = value;
	acc->Cur->position = position;
	acc->Cur->profit = takeProfit;
	acc->Cur->loss = stopLoss;
}

void checkTradeStatus(node *account){
	stick *cur = tailStick;
	if(account->status){
		if(colour && cur->closePrice >= account->Cur->position){
			account->Cur->reward = (account->Cur->value * (cur->closePrice - account->Cur->position)) / 100;
			account->money += account->Cur->reward;
			pushHead(account, account->Cur->value, account->Cur->position, account->Cur->profit, account->Cur->loss, account->Cur->reward);
			account->status = false;
		}else if(!colour && cur->closePrice >= account->Cur->position){
			account->Cur->reward = (account->Cur->value * -1 * (cur->closePrice - account->Cur->position)) / 100;
			account->money += account->Cur->reward;
			pushHead(account, account->Cur->value, account->Cur->position, account->Cur->profit, account->Cur->loss, account->Cur->reward);
			account->status = false;
		}else if(colour){
			account->Cur->reward = (account->Cur->value * (cur->closePrice - account->Cur->position)) / 100;
			account->money += account->Cur->reward;
			pushHead(account, account->Cur->value, account->Cur->position, account->Cur->profit, account->Cur->loss, account->Cur->reward);
		}else if(!colour){
			account->Cur->reward = (account->Cur->value * -1 * (cur->closePrice - account->Cur->position)) / 100;
			account->money += account->Cur->reward;
			pushHead(account, account->Cur->value, account->Cur->position, account->Cur->profit, account->Cur->loss, account->Cur->reward);
		}
	}
}

void startTrading(node *account){
	int opt;
	window = 0;
	page = idx;
	logged = true;
	while(logged){
		do{
			cursorPosition(0, 0);
			printMap();
			printChart();
			printNum();
			printLine(account);
			printBottomRight(account);
			opt = printBottomLeft(account);
			if(account->money <= 0){
				account->money = 0;
			}
			cursorPosition(40, 0);
	    }while(opt < 1 || opt > 6);
	    if(opt == 1){
	    	if(account->money <= 0){
				cursorPosition(37, 44);
				printf(RED "You Can't Trade Anymore! Enter To Continue..." RESET); getchar();
				logged = false;
				break;
			}
	    	page++;
    		if(page > 123){
    			nextPage();
    			page = 123;
			}
    		otherCandle();
    		checkTradeStatus(account);
		}else if(opt == 2){
    		prevPage();
		}else if(opt == 3){
	    	nextPage();
		}else if(opt == 4){
	    	if(account->money <= 0){
				cursorPosition(37, 44);
				printf(RED "You Can't Trade Anymore! Enter To Continue..." RESET); getchar();
				logged = false;
				break;
			}
	    	buyStick(account);
		}else if(opt == 5){
	    	if(account->money <= 0){
				cursorPosition(37, 44);
				printf(RED "You Can't Trade Anymore! Enter To Continue..." RESET); getchar();
				logged = false;
				break;
			}
    		sellStick(account);
		}else if(opt == 6){
			logged = false;
			updateFile();
		}
	}
}

void historyTrading(node *account){
	trade* cur = account->Head;
	if(cur == NULL){
		puts("No Trade History\nPress Enter To Continue"); getchar();
		return;
	}
	printf("Username: %s\n", account->name);
	printf("----------------------------------------------\n");
	int num = 1;
	while(cur){
		printf("No: %d\n", num);
		printf("Value			: %d\n", cur->value);
		printf("Position		: %d\n", cur->position);
		printf("Take Profit		: %d\n", cur->profit);
		printf("Stop Loss		: %d\n", cur->loss);
		if(cur->reward < 0){
			printf("Reward			: " RED "%d\n" RESET, cur->reward);
		}else if(cur->reward >= 0){
			printf("Reward			: " GREEN "%d\n" RESET, cur->reward);
		}
		puts("");
		cur = cur->next;
		num++;
	}
	printf("Press Enter To Continue..."); getchar();
}

void guideMenu(){
	system("cls");
	puts(CYAN "What Is Forex?" RESET);
	puts("\"Forex\", short for foreign exchange, is a global decentralized marketplace for trading currencies.");
	puts("In forex trading, participants buy one currency by selling another currency simultaneously, with the aim of profiting from fluctuations in exchange rates.");
	puts("It is one of the largest and most liquid financial markets in the world, operating 24 hours a day, five days a week.");
	puts("");
	puts(YELLOW "What Is Candle Stick?" RESET);
	puts("\"Canlde Stick\" in charts are a type of financial chart used to represent price movements in trading markets, including forex.");
	puts("They visually display the open, high, low, and close prices for a specific period.");
	puts("if the close price is higher than the open price, the candle color will be green");
	puts("then if the close price is less than the open price, the candle color will be red.");
	puts("shadow or tick is the highest and the lowest price of a candle.");
	puts("");
	puts(PURPLE "What Is Position?" RESET);
	puts("\"Position\" in forex trading refers to where we want to enter the market at certain price point");
	puts("");
	puts(GREEN "What Is Long?" RESET);
	puts("\"Long\" in forex trading refers to a trading position where a trader buys a currency pair");
	puts("with the expectation that its value will increase over time.");
	puts("");
	puts(RED "What Is Short?" RESET);
	puts("\"Short\" in forex trading refers to a trading position where a trader sells a currency pair");
	puts("with the expectation that its value will decrease over time.");
	puts("");
	puts(GREEN "What is Take Profit?" RESET);
	puts("\"Take Profit\" in forex trading refers to where we will leave the market at the specified price point");
	puts("our position will automatically closed after the market price hit our take profit price");
	puts("");
	puts(RED "What Is Stop Loss?" RESET);
	puts("");
	puts("\"Stop Loss\" in forex trading refers to where we will leave the market at the specified price point");
	puts("it's used to make sure that we don't loss all of our money and many more");
	puts("same like take profit, our position will automatically closed after the market price hit our take profit price");
	puts("");
	puts("Press Enter To Continue..."); getchar();
}

void tradingMenu(node *account){
	int opt;
	logged = true;
	do{
		do{
			system("cls");
			puts("MetaFi - User's Menu");
			puts("---------------------");
			puts("1. Start Trade");
			puts("2. Trade History");
			puts("3. Guide");
			puts("4. Log Out");
			printf(">> ");
			scanf("%d", &opt); getchar();
		}while(opt < 1 || opt > 4);
		system("cls");
		if(opt == 1){
			startTrading(account);
		}else if(opt == 2){
			historyTrading(account);
		}else if(opt == 3){
			guideMenu();
		}else if(opt == 4){
			logged = false;
			updateFile();
		}
	}while(logged);
}

bool validationAccount(const char *Username, const char *Email, const char *Password, int Separator){
	int money;
	char user[100], mail[100], pass[100];
	FILE *fp = fopen("user.txt", "r");
	while(!feof(fp)){
		fscanf(fp, "%[^#]#%[^#]#%[^#]#%d\n", &user, &mail, &pass, &money);
		if(Separator == 1){
			if(strcmp(user, Username) == 0) return false;
		}else if(Separator == 2){
			if(strcmp(mail, Email) == 0) return false;
		}
	}
	fclose(fp);
	return true;
}

void addRegisteredAccount(const char *Username, const char *Email, const char *Password, int Currency){
	FILE *fp = fopen("user.txt", "a");
	fprintf(fp, "%s#%s#%s#%d\n", Username, Email, Password, Currency);
	fclose(fp);
}

bool tableAccount(const char *Email, const char *Password){
	for(int i = 0; i < SIZE; i++){
		node *cur = hashTable[i];
		while(cur){
			if(strcmp(cur->email, Email) == 0 && strcmp(cur->password, Password) == 0){
				tradingMenu(cur); return true;
			}
			cur = cur->next;
		}
	}
	return false;
}

void loginAccount(){
	int lenPassword = 0;
	char email[100], password[100], pass;
	do{
		system("cls");
		printf("Email (0 to Exit) : ");
		scanf("%[^\n]", email); getchar();
		if(strcmp(email, "0") == 0) return;
		
		system("cls");
		printf("Password (0 to Exit) : ");
		while((pass = _getch()) != 13){
			if(pass == 8){
				if(lenPassword > 0){
					lenPassword--;
					printf("\b \b");
				}
			}else{
				password[lenPassword] = pass;
				lenPassword++;
				printf("*");
			}
		}
		password[lenPassword] = '\0';
		if(strcmp(password, "0") == 0) return;
		if(!tableAccount(email, password)){
			printf(RED "\nEmail or Password Is Invalid!\n" RESET "Press Enter To Continue..."); getchar();
		}
	}while(!strcmp(email, "0") || !(strcmp(password, "0")));
}

void registerAccount(){
	bool checkUser, dotCom, checkPassword, checkLen, checkAlnum, checkDomain, checkTag, checkSpace, checkLenPass, Alpha, Numer, Alnum;
	int lenName, lenEmail, atTag, space, lenPassword;
	char username[100], email[100], password[100], pass;
	do{
		system("cls");
		checkUser = true;
		printf("Username (0 to Exit) : ");
		scanf("%[^\n]", username); getchar();
		lenName = strlen(username);
		if(strcmp(username, "0") == 0) return;
		for(int i = 0; i < lenName; i++){
			if(!isalnum(username[i])) checkUser = false;
		}
		if(!checkUser){
			printf(RED "Username Only Contain Letter Or Number\n" RESET "Press Enter To Continue..."); getchar(); continue;
		}
		if(lenName > 20){
			printf(RED "Username Length Must Between 1 - 20 Characters!\n" RESET "Press Enter To Continue..."); getchar(); continue;
		}
		if(!validationAccount(username, "", "", 1)){
			printf(RED "Username Already Taken!\n" RESET "Press Enter To Continue..."); getchar(); continue;
		}
	}while(!checkUser || !validationAccount(username, "", "", 1) || lenName > 20);
	
	do{
		system("cls");
		checkLen = true, checkAlnum = true, dotCom = true, checkDomain = true, checkSpace = true, checkTag = false, atTag = 0, space = 0;
		printf("Email (0 To Exit) : ");
		scanf("%[^\n]", email); getchar();
		lenEmail = strlen(email);
		if(strcmp(email, "0") == 0) return;
		for(int i = 0; i < lenEmail; i++){
			if(lenEmail < 6 || lenEmail > 36) checkLen = false;
			if(email[i] == '@') atTag++;
			if(email[i] == ' ') space++;
			if(email[i] == '@' && !isalnum(email[i + 1])) checkDomain = false;
		}
		
		if(atTag == 1) checkTag = true;
		if(space >= 1) checkSpace = false;
		if(space >= 1) checkSpace = false;
		if(!isalnum(email[0])) checkAlnum = false;
		if(email[lenEmail - 4] != '.' && email[lenEmail - 3] != 'c'  && email[lenEmail - 2] != 'o' && email[lenEmail - 1] != 'm') dotCom = false;
		
		if(!checkTag){
			printf(RED "Email Only Consist Of One '@'!\n" RESET "Press Enter To Continue..."); getchar(); continue;
		}
		if(!checkAlnum){
			printf(RED "Email Must Be Started With Character!\n" RESET "Press Enter To Continue..."); getchar(); continue;
		}
		if(!dotCom){
			printf(RED "Email Must Be Ended With \".com\"!\n" RESET "Press Enter To Continue..."); getchar(); continue;
		}
		if(!checkDomain){
			printf(RED "Email Must Have Domain!\n" RESET "Press Enter To Continue..."); getchar(); continue;
		}
		if(!checkSpace){
			printf(RED "Email Cannot Have White Space!\n" RESET "Press Enter To Continue..."); getchar(); continue;
		}
		if(!validationAccount("", email, "", 2)){
			printf(RED "Email Already Taken!\n" RESET "Press Enter To Continue..."); getchar(); continue;
		}
		if(!checkLen){
			printf(RED "Email is Invalid\n" RESET "Press Enter To Continue..."); getchar(); continue;
		}
	}while(!checkTag || !checkAlnum || !dotCom || !checkDomain || !checkSpace || !checkLen || !validationAccount("", email, "", 2));
	
	do{
		system("cls");
		checkLenPass = true, Alpha = false, Numer = false, Alnum = true;
		lenPassword = 0;
		printf("Password (0 To Exit) : ");
		while((pass = _getch()) != 13){
			if(pass == 8){
				if(lenPassword > 0){
					lenPassword--;
					printf("\b \b");
				}
			}else{
				password[lenPassword] = pass;	
				lenPassword++;
				printf("*");
			}
		}
		password[lenPassword] = '\0';
		if(strcmp(password, "0") == 0) return;
		if(lenPassword < 8 || lenPassword > 36) checkLenPass = false;
		for(int i = 0; i < lenPassword; i++){
			if(isalpha(password[i])) Alpha = true;
			if(isdigit(password[i])) Numer = true;
			if(!isalnum(password[i])) Alnum = false;
		}
		if(!checkLenPass){
			printf(RED "\nPassword Length Must Between 8 - 36 Characters!\n" RESET "Press Enter To Continue..."); getchar(); continue;
		}
		if(!Alnum || !Alpha || !Numer){
			printf(RED "\nNo Space And Contains at Least 1 Character and 1 Number With No Symbol!\n" RESET "Press Enter To Continue..."); getchar(); continue;
		}
	}while(!Alnum || !Alpha || !Numer || !checkLenPass);
	insertChaining(username, email, password, 10000, false, 0, 0, 0);
	addRegisteredAccount(username, email, password, 10000);
}

void menu(){
	int opt;
	do{
		do{
			system("cls");
			frontLogo();
			puts("                     1. Log In To Trade");
			puts("                     2. Register Account");
			puts("                     3. Exit Application");
			printf("                     >> ");
			scanf("%d", &opt); getchar();
		}while(opt < 1 || opt > 3);
		if(opt == 1){
			loginAccount();
		}else if(opt == 2){
			registerAccount();
		}
	}while(opt != 3);
	exitLogo();
}

int main(){
	srand(time(0));
	readTable();
	fullScreen();
	initMap();
	initChart();
	firstData();
	menu();
	return 0;
}
