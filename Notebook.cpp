#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<math.h>   

#define MAX 50
#define Name_buf 25
#define Surname_buf 25
#define Obl_buf 50
#define City_buf 50
#define Street_buf 50
#define Home_buf 25
#define Apart_buf 25

const char* namefirst[7] = { "Ввод данных", "Вывод записей", "Редактирование записей", "Перемещение записей", "Удаление данных", "Выход", NULL };
const char* namesecond[10] = { "Имя", "Фамилия", "Номер телефона", "Почтовый индекс", "Область", "Город", "Улица", "Дом", "Квартира", NULL };

struct addr{
	char name[Name_buf];
	char surname[Surname_buf];
	long long telephone;
	int zip;
	char obl[Obl_buf];
	char city[City_buf];
	char street[Street_buf];
	char home[Home_buf] ;
	char apartment[Apart_buf];
} addr_list[MAX];

void init_list(void), enter(void), glav_menu(const char* name[]), menu(const char* name[]);
void deletee(void), del_mov(int del), list(void), moving(int x, int y);
int find_free(void), setmoving(void);


/* Инициализация списка. */
void init_list(void){

	register int t;
	for (t = 0; t < MAX; t++) addr_list[t].name[0] = '\0';

}

/* Ввод адреса в список. */
void enter(void){

	int slot;
	int tmp = 0;
	int zip = -1; long long tel = -1;
	char zip_buf[80], tel_buf[80];

	slot = find_free();
	if (slot == -1) {
		printf("\nСписок заполнен");
		return;
	}

	printf("\n  Введите данные: ");
	printf("\n %s: ", namesecond[tmp]); tmp++; gets_s(addr_list[slot].name); //ввод Имени
	if (addr_list[slot].name[0] == '\0') { addr_list[slot].name[0] = '-'; addr_list[slot].name[1] = '\0';}

	printf(" %s: ", namesecond[tmp]); tmp++; gets_s(addr_list[slot].surname); //ввод Фамилии
	if (addr_list[slot].surname[0] == '\0') { addr_list[slot].surname[0] = '-'; addr_list[slot].surname[1] = '\0'; }

	while ((tel < 89000000000 || tel > 89999999999) && tel != 0) { //ввод номера телефона
		printf(" %s: ", namesecond[tmp]); gets_s(tel_buf);
		int num_tel = strlen(tel_buf)-1;
		if (num_tel != -1) {
			for (int i = 0; i <= num_tel; i++) {
				tel += (tel_buf[i] - '0') * pow(10, num_tel - i);
			}
		}
		else tel = 0;
	}addr_list[slot].telephone = ++tel; tmp++;

	while ((zip < 100000 || zip > 999999) && zip != 0) { //ввод почтового индекса
		printf(" %s: ", namesecond[tmp]); gets_s(zip_buf);
		zip = atoi(zip_buf);
	}addr_list[slot].zip = zip; tmp++;

	printf(" %s: ", namesecond[tmp]); tmp++;  gets_s(addr_list[slot].obl); //ввод области
	if (addr_list[slot].obl[0] == '\0') { addr_list[slot].obl[0] = '-'; addr_list[slot].obl[1] = '\0'; }

	printf(" %s: ", namesecond[tmp]); tmp++;  gets_s(addr_list[slot].city); //ввод города
	if (addr_list[slot].city[0] == '\0') { addr_list[slot].city[0] = '-'; addr_list[slot].city[1] = '\0'; }

	printf(" %s: ", namesecond[tmp]); tmp++;  gets_s(addr_list[slot].street); //ввод улицы
	if (addr_list[slot].street[0] == '\0') {addr_list[slot].street[0] = '-'; addr_list[slot].street[1] = '\0';}

	printf(" %s: ", namesecond[tmp]); tmp++;  gets_s(addr_list[slot].home); //ввод дома
	if (addr_list[slot].home[0] == '\0') { addr_list[slot].home[0] = '-'; addr_list[slot].home[1] = '\0'; }

	printf(" %s: ", namesecond[tmp]); tmp++;  gets_s(addr_list[slot].apartment); //ввод квартиры
	if (addr_list[slot].apartment[0] == '\0') { addr_list[slot].apartment[0] = '-'; addr_list[slot].apartment[1] = '\0'; }

	printf("\n Ввод успешен!");
	Sleep(2500);
	system("cls");
}

/* Поиск свободной структуры. */
int find_free(void){

	register int t;
	for (t = 0; addr_list[t].name[0] && t < MAX; t++);

	if (t == MAX) return -1; /* свободных структур нет */
	return t;
}

/* Вывод списка на экран. */
void list(void){

	system("cls");
	register int t;
	int tmp;
	printf("\n Вывод списка:");
	for (t = 0; t < MAX; ++t) {
		if (addr_list[t].name[0])
		{
			tmp = 0;
			printf("\n\n Номер в списке: %d", t);
			printf("\n %s: %s ", namesecond[tmp], addr_list[t].name); tmp++;//Вывод имени
			printf("%s: %s", namesecond[tmp], addr_list[t].surname); tmp++; //Вывод фамилии

			if (addr_list[t].telephone != 1)								//Вывод номера телефона
				printf("\n %s: %lld", namesecond[tmp], addr_list[t].telephone);
			else printf("\n %s: - ", namesecond[tmp]);
			tmp++;

			if (addr_list[t].zip != 0)										//Вывод почтового индекса
				printf("\n %s: %d", namesecond[tmp], addr_list[t].zip);
			else printf("\n %s: - ", namesecond[tmp]);
			tmp++;

			printf(" %s: %s ", namesecond[tmp], addr_list[t].obl); tmp++;	//Вывод области
			printf(" %s: %s ", namesecond[tmp], addr_list[t].city); tmp++;	//Вывод города
			printf(" %s: %s ", namesecond[tmp], addr_list[t].street); tmp++;//Вывод улицы
			printf(" %s: %s ", namesecond[tmp], addr_list[t].home); tmp++;	//Вывод дома
			printf(" %s: %s ", namesecond[tmp], addr_list[t].apartment);	//Вывод квартиры

		}
	}
	printf("\n");
}

/* Получения значения, выбранного меню. */
void menu(const char* name[])
{
	const char** tmp = name;
	int i = 1;
	while (*tmp) printf("\n%d %s", i++, *tmp++);
}

/* Редактирование данных. */
void edit(void)
{
	system("cls"); list();
	register int slot = MAX;
	char s[80];
	int sun;
	int zip = -1; long long tel = 0;
	char zip_buf[80], tel_buf[80];

	while (slot < 0 || slot >= MAX) {
		printf("\n Введите №, в который нужно внести изменения: ");
		gets_s(s);
		slot = atoi(s);
	}
	menu(namesecond);
	printf("\n Выберите пункт, в который нужно внести изменения:");
	scanf_s("%d", &sun); sun--;
	while (getchar() != '\n');
	switch (sun)
	{
	case 1: addr_list[slot].name[0] = '\0'; printf("\n %s: ", namesecond[sun]); gets_s(addr_list[slot].name); //редактирование имени
		if (addr_list[slot].name[0] == '\0') { addr_list[slot].name[0] = '-'; addr_list[slot].name[1] = '\0'; }
		break;
	case 2: addr_list[slot].surname[0] = '\0'; printf("\n %s: ", namesecond[sun]); gets_s(addr_list[slot].surname); //редактирование фамилии
		if (addr_list[slot].surname[0] == '\0') { addr_list[slot].surname[0] = '-'; addr_list[slot].surname[1] = '\0'; }
		break;
	case 3: addr_list[slot].telephone = 0; //редактирование номера телефона
		while ((tel < 89000000000 || tel > 89999999999) && tel != -1) { 
		printf(" %s: ", namesecond[sun]); gets_s(tel_buf);
		int num_tel = strlen(tel_buf) - 1;
		if (num_tel != -1) {
			for (int i = 0; i <= num_tel; i++) {
				tel += (tel_buf[i] - '0') * pow(10, num_tel - i);}}
		else tel = -1;
		} addr_list[slot].telephone = ++tel;
		break;
	case 4: addr_list[slot].zip = 0; //редактирование почтового индекса
		while ((zip < 100000 || zip > 999999) && zip != 0) {
			printf(" %s: ", namesecond[slot]); gets_s(zip_buf);
			zip = atoi(zip_buf);
		}addr_list[slot].zip = zip;
		break;
	case 5: addr_list[slot].obl[0] = '\0'; printf("\n %s: ", namesecond[sun]); gets_s(addr_list[slot].obl); //редактирование области
		if (addr_list[slot].obl[0] == '\0') { addr_list[slot].obl[0] = '-'; addr_list[slot].obl[1] = '\0'; }
		break;
	case 6: addr_list[slot].city[0] = '\0'; printf("\n %s: ", namesecond[sun]); gets_s(addr_list[slot].city); //редактирование города
		if (addr_list[slot].city[0] == '\0') { addr_list[slot].city[0] = '-'; addr_list[slot].city[1] = '\0'; }
		break;
	case 7: addr_list[slot].street[0] = '\0'; printf("\n %s: ", namesecond[sun]); gets_s(addr_list[slot].street); //редактирование улицы
		if (addr_list[slot].street[0] == '\0') { addr_list[slot].street[0] = '-'; addr_list[slot].street[1] = '\0'; }
		break;
	case 8: addr_list[slot].home[0] = '\0'; printf("\n %s: ", namesecond[sun]); gets_s(addr_list[slot].home); //редактирование дома
		if (addr_list[slot].home[0] == '\0') { addr_list[slot].home[0] = '-'; addr_list[slot].home[1] = '\0'; }
		break;
	case 9: addr_list[slot].apartment[0] = '\0'; printf("\n %s: ", namesecond[sun]); gets_s(addr_list[slot].apartment); //редактирование квартиры
		if (addr_list[slot].apartment[0] == '\0') { addr_list[slot].apartment[0] = '-'; addr_list[slot].apartment[1] = '\0'; }
		break;
	default: system("cls"); printf("\n Неверное значение!!! Повторите попытку! \n"); break;
	}

	printf("\n Успешно!\n");
	Sleep(2500);
	system("cls");
}

/* Перемещение данных. */
void moving(int x, int y){

	struct tmpStrukt {
		char name[Name_buf];
		char surname[Surname_buf];
		long long telephone;
		int zip;
		char obl[Obl_buf];
		char city[City_buf];
		char street[Street_buf];
		char home[Home_buf];
		char apartment[Apart_buf];
	}tmp;

	memcpy(tmp.name, addr_list[x].name, sizeof(tmp.name));
	memcpy(tmp.surname, addr_list[x].surname, sizeof(tmp.surname));
	tmp.telephone = addr_list[x].telephone;
	tmp.zip = addr_list[x].zip;
	memcpy(tmp.obl, addr_list[x].obl, sizeof(tmp.obl));
	memcpy(tmp.city, addr_list[x].city, sizeof(tmp.city));
	memcpy(tmp.street, addr_list[x].street, sizeof(tmp.street));
	memcpy(tmp.home, addr_list[x].home, sizeof(tmp.home));
	memcpy(tmp.apartment, addr_list[x].apartment, sizeof(tmp.apartment));

	memcpy(addr_list[x].name, addr_list[y].name, sizeof(addr_list[x].name));
	memcpy(addr_list[x].surname, addr_list[y].surname, sizeof(addr_list[x].surname));
	addr_list[x].telephone = addr_list[y].telephone;
	addr_list[x].zip = addr_list[y].zip;
	memcpy(addr_list[x].obl, addr_list[y].obl, sizeof(addr_list[x].obl));
	memcpy(addr_list[x].city, addr_list[y].city, sizeof(addr_list[x].city));
	memcpy(addr_list[x].street, addr_list[y].street, sizeof(addr_list[x].street));
	memcpy(addr_list[x].home, addr_list[y].home, sizeof(addr_list[x].home));
	memcpy(addr_list[x].apartment, addr_list[y].apartment, sizeof(addr_list[x].apartment));


	memcpy(addr_list[y].name, tmp.name, sizeof(addr_list[y].name));
	memcpy(addr_list[y].surname, tmp.surname, sizeof(addr_list[y].surname));
	addr_list[y].telephone = tmp.telephone;
	addr_list[y].zip = tmp.zip;
	memcpy(addr_list[y].obl, tmp.obl, sizeof(addr_list[y].obl));
	memcpy(addr_list[y].city, tmp.city, sizeof(addr_list[y].city));
	memcpy(addr_list[y].street, tmp.street, sizeof(addr_list[y].street));
	memcpy(addr_list[y].home, tmp.home, sizeof(addr_list[y].home));
	memcpy(addr_list[y].apartment, tmp.apartment, sizeof(addr_list[y].apartment));

}

/* Получение номера для перемещения. */
int setmoving(void){

	register int slot = MAX;
	char s[80];

	while (slot < 0 || slot >= MAX) {
		printf(" Введите № записи, которую перемещаем: ");
		gets_s(s);
		slot = atoi(s);
	}
	return slot;
}

/* Получение номера для перемещения, после удаления */
void del_mov(int del)
{
	int no_del = del; no_del++;
	while (no_del < MAX && addr_list[no_del].name[0] != '\0') {
	moving(del, no_del);
	del++; no_del++;
	}
}

/* Удаление данных. */
void deletee(void){

	system("cls"); list();
	register int slot = MAX;
	char s[80];

	while (slot < 0 || slot >= MAX) {
		printf("\n Введите № для удаления: ");
		gets_s(s);
		slot = atoi(s);
	}

	if (addr_list[slot].name[0] != '\0') {
		addr_list[slot].name[0] = '\0';
		addr_list[slot].surname[0] = '\0';
		addr_list[slot].telephone = 0;
		addr_list[slot].zip = 0;
		addr_list[slot].obl[0] = '\0';
		addr_list[slot].city[0] = '\0';
		addr_list[slot].street[0] = '\0';
		addr_list[slot].home[0] = '\0';
		addr_list[slot].apartment[0] = '\0';
		printf("\n Удаление успешно выполнено!");
	}
	else printf("\n Невозможно удалить. Запись пуста!");

	del_mov(slot);
	Sleep(2500);
	system("cls");
}

/* Получение значения, главного меню. */
void glav_menu(const char* name[]){

	const char** tmp = name;
	const char** exit= name;
	int i = 1, kol_vo = 0;
	while (*exit) { *exit++;} exit--;
	while (*tmp != *exit) {
		printf("\n%d %s", i++, *tmp++);
	}
	printf("\n0 %s", *exit);
}

int main(void){

	int sun, movX, movY;
	SetConsoleCP(1251); // Ввод с консоли в кодировке 1251
	SetConsoleOutputCP(1251); // Вывод на консоль в кодировке 1251.

	init_list(); /* инициализация массива структур */

	while (1)
	{
		printf("_____________________________________________________________________________ \n\n Меню:");
		glav_menu(namefirst);
		printf("\n\n Выберите пункт меню:");
		scanf_s("%d", &sun);
		while (getchar() != '\n');

		switch (sun)
		{
		case 1: enter();
			break;
		case 2: list();
			break;
		case 3: edit();
			break;
		case 4: system("cls"); list();
				movX = setmoving();
				movY = setmoving();
				moving(movX, movY); 	
				printf("\n Успешно!\n");
			break;
		case 5: deletee();
			break;
		case 0: exit(0);
		default: system("cls"); printf("\n Неверное значение!!! Повторите попытку! \n"); break;
		}
	}

	return 0;
}