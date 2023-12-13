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

const char* namefirst[7] = { "���� ������", "����� �������", "�������������� �������", "����������� �������", "�������� ������", "�����", NULL };
const char* namesecond[10] = { "���", "�������", "����� ��������", "�������� ������", "�������", "�����", "�����", "���", "��������", NULL };

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


/* ������������� ������. */
void init_list(void){

	register int t;
	for (t = 0; t < MAX; t++) addr_list[t].name[0] = '\0';

}

/* ���� ������ � ������. */
void enter(void){

	int slot;
	int tmp = 0;
	int zip = -1; long long tel = -1;
	char zip_buf[80], tel_buf[80];

	slot = find_free();
	if (slot == -1) {
		printf("\n������ ��������");
		return;
	}

	printf("\n  ������� ������: ");
	printf("\n %s: ", namesecond[tmp]); tmp++; gets_s(addr_list[slot].name); //���� �����
	if (addr_list[slot].name[0] == '\0') { addr_list[slot].name[0] = '-'; addr_list[slot].name[1] = '\0';}

	printf(" %s: ", namesecond[tmp]); tmp++; gets_s(addr_list[slot].surname); //���� �������
	if (addr_list[slot].surname[0] == '\0') { addr_list[slot].surname[0] = '-'; addr_list[slot].surname[1] = '\0'; }

	while ((tel < 89000000000 || tel > 89999999999) && tel != 0) { //���� ������ ��������
		printf(" %s: ", namesecond[tmp]); gets_s(tel_buf);
		int num_tel = strlen(tel_buf)-1;
		if (num_tel != -1) {
			for (int i = 0; i <= num_tel; i++) {
				tel += (tel_buf[i] - '0') * pow(10, num_tel - i);
			}
		}
		else tel = 0;
	}addr_list[slot].telephone = ++tel; tmp++;

	while ((zip < 100000 || zip > 999999) && zip != 0) { //���� ��������� �������
		printf(" %s: ", namesecond[tmp]); gets_s(zip_buf);
		zip = atoi(zip_buf);
	}addr_list[slot].zip = zip; tmp++;

	printf(" %s: ", namesecond[tmp]); tmp++;  gets_s(addr_list[slot].obl); //���� �������
	if (addr_list[slot].obl[0] == '\0') { addr_list[slot].obl[0] = '-'; addr_list[slot].obl[1] = '\0'; }

	printf(" %s: ", namesecond[tmp]); tmp++;  gets_s(addr_list[slot].city); //���� ������
	if (addr_list[slot].city[0] == '\0') { addr_list[slot].city[0] = '-'; addr_list[slot].city[1] = '\0'; }

	printf(" %s: ", namesecond[tmp]); tmp++;  gets_s(addr_list[slot].street); //���� �����
	if (addr_list[slot].street[0] == '\0') {addr_list[slot].street[0] = '-'; addr_list[slot].street[1] = '\0';}

	printf(" %s: ", namesecond[tmp]); tmp++;  gets_s(addr_list[slot].home); //���� ����
	if (addr_list[slot].home[0] == '\0') { addr_list[slot].home[0] = '-'; addr_list[slot].home[1] = '\0'; }

	printf(" %s: ", namesecond[tmp]); tmp++;  gets_s(addr_list[slot].apartment); //���� ��������
	if (addr_list[slot].apartment[0] == '\0') { addr_list[slot].apartment[0] = '-'; addr_list[slot].apartment[1] = '\0'; }

	printf("\n ���� �������!");
	Sleep(2500);
	system("cls");
}

/* ����� ��������� ���������. */
int find_free(void){

	register int t;
	for (t = 0; addr_list[t].name[0] && t < MAX; t++);

	if (t == MAX) return -1; /* ��������� �������� ��� */
	return t;
}

/* ����� ������ �� �����. */
void list(void){

	system("cls");
	register int t;
	int tmp;
	printf("\n ����� ������:");
	for (t = 0; t < MAX; ++t) {
		if (addr_list[t].name[0])
		{
			tmp = 0;
			printf("\n\n ����� � ������: %d", t);
			printf("\n %s: %s ", namesecond[tmp], addr_list[t].name); tmp++;//����� �����
			printf("%s: %s", namesecond[tmp], addr_list[t].surname); tmp++; //����� �������

			if (addr_list[t].telephone != 1)								//����� ������ ��������
				printf("\n %s: %lld", namesecond[tmp], addr_list[t].telephone);
			else printf("\n %s: - ", namesecond[tmp]);
			tmp++;

			if (addr_list[t].zip != 0)										//����� ��������� �������
				printf("\n %s: %d", namesecond[tmp], addr_list[t].zip);
			else printf("\n %s: - ", namesecond[tmp]);
			tmp++;

			printf(" %s: %s ", namesecond[tmp], addr_list[t].obl); tmp++;	//����� �������
			printf(" %s: %s ", namesecond[tmp], addr_list[t].city); tmp++;	//����� ������
			printf(" %s: %s ", namesecond[tmp], addr_list[t].street); tmp++;//����� �����
			printf(" %s: %s ", namesecond[tmp], addr_list[t].home); tmp++;	//����� ����
			printf(" %s: %s ", namesecond[tmp], addr_list[t].apartment);	//����� ��������

		}
	}
	printf("\n");
}

/* ��������� ��������, ���������� ����. */
void menu(const char* name[])
{
	const char** tmp = name;
	int i = 1;
	while (*tmp) printf("\n%d %s", i++, *tmp++);
}

/* �������������� ������. */
void edit(void)
{
	system("cls"); list();
	register int slot = MAX;
	char s[80];
	int sun;
	int zip = -1; long long tel = 0;
	char zip_buf[80], tel_buf[80];

	while (slot < 0 || slot >= MAX) {
		printf("\n ������� �, � ������� ����� ������ ���������: ");
		gets_s(s);
		slot = atoi(s);
	}
	menu(namesecond);
	printf("\n �������� �����, � ������� ����� ������ ���������:");
	scanf_s("%d", &sun); sun--;
	while (getchar() != '\n');
	switch (sun)
	{
	case 1: addr_list[slot].name[0] = '\0'; printf("\n %s: ", namesecond[sun]); gets_s(addr_list[slot].name); //�������������� �����
		if (addr_list[slot].name[0] == '\0') { addr_list[slot].name[0] = '-'; addr_list[slot].name[1] = '\0'; }
		break;
	case 2: addr_list[slot].surname[0] = '\0'; printf("\n %s: ", namesecond[sun]); gets_s(addr_list[slot].surname); //�������������� �������
		if (addr_list[slot].surname[0] == '\0') { addr_list[slot].surname[0] = '-'; addr_list[slot].surname[1] = '\0'; }
		break;
	case 3: addr_list[slot].telephone = 0; //�������������� ������ ��������
		while ((tel < 89000000000 || tel > 89999999999) && tel != -1) { 
		printf(" %s: ", namesecond[sun]); gets_s(tel_buf);
		int num_tel = strlen(tel_buf) - 1;
		if (num_tel != -1) {
			for (int i = 0; i <= num_tel; i++) {
				tel += (tel_buf[i] - '0') * pow(10, num_tel - i);}}
		else tel = -1;
		} addr_list[slot].telephone = ++tel;
		break;
	case 4: addr_list[slot].zip = 0; //�������������� ��������� �������
		while ((zip < 100000 || zip > 999999) && zip != 0) {
			printf(" %s: ", namesecond[slot]); gets_s(zip_buf);
			zip = atoi(zip_buf);
		}addr_list[slot].zip = zip;
		break;
	case 5: addr_list[slot].obl[0] = '\0'; printf("\n %s: ", namesecond[sun]); gets_s(addr_list[slot].obl); //�������������� �������
		if (addr_list[slot].obl[0] == '\0') { addr_list[slot].obl[0] = '-'; addr_list[slot].obl[1] = '\0'; }
		break;
	case 6: addr_list[slot].city[0] = '\0'; printf("\n %s: ", namesecond[sun]); gets_s(addr_list[slot].city); //�������������� ������
		if (addr_list[slot].city[0] == '\0') { addr_list[slot].city[0] = '-'; addr_list[slot].city[1] = '\0'; }
		break;
	case 7: addr_list[slot].street[0] = '\0'; printf("\n %s: ", namesecond[sun]); gets_s(addr_list[slot].street); //�������������� �����
		if (addr_list[slot].street[0] == '\0') { addr_list[slot].street[0] = '-'; addr_list[slot].street[1] = '\0'; }
		break;
	case 8: addr_list[slot].home[0] = '\0'; printf("\n %s: ", namesecond[sun]); gets_s(addr_list[slot].home); //�������������� ����
		if (addr_list[slot].home[0] == '\0') { addr_list[slot].home[0] = '-'; addr_list[slot].home[1] = '\0'; }
		break;
	case 9: addr_list[slot].apartment[0] = '\0'; printf("\n %s: ", namesecond[sun]); gets_s(addr_list[slot].apartment); //�������������� ��������
		if (addr_list[slot].apartment[0] == '\0') { addr_list[slot].apartment[0] = '-'; addr_list[slot].apartment[1] = '\0'; }
		break;
	default: system("cls"); printf("\n �������� ��������!!! ��������� �������! \n"); break;
	}

	printf("\n �������!\n");
	Sleep(2500);
	system("cls");
}

/* ����������� ������. */
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

/* ��������� ������ ��� �����������. */
int setmoving(void){

	register int slot = MAX;
	char s[80];

	while (slot < 0 || slot >= MAX) {
		printf(" ������� � ������, ������� ����������: ");
		gets_s(s);
		slot = atoi(s);
	}
	return slot;
}

/* ��������� ������ ��� �����������, ����� �������� */
void del_mov(int del)
{
	int no_del = del; no_del++;
	while (no_del < MAX && addr_list[no_del].name[0] != '\0') {
	moving(del, no_del);
	del++; no_del++;
	}
}

/* �������� ������. */
void deletee(void){

	system("cls"); list();
	register int slot = MAX;
	char s[80];

	while (slot < 0 || slot >= MAX) {
		printf("\n ������� � ��� ��������: ");
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
		printf("\n �������� ������� ���������!");
	}
	else printf("\n ���������� �������. ������ �����!");

	del_mov(slot);
	Sleep(2500);
	system("cls");
}

/* ��������� ��������, �������� ����. */
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
	SetConsoleCP(1251); // ���� � ������� � ��������� 1251
	SetConsoleOutputCP(1251); // ����� �� ������� � ��������� 1251.

	init_list(); /* ������������� ������� �������� */

	while (1)
	{
		printf("_____________________________________________________________________________ \n\n ����:");
		glav_menu(namefirst);
		printf("\n\n �������� ����� ����:");
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
				printf("\n �������!\n");
			break;
		case 5: deletee();
			break;
		case 0: exit(0);
		default: system("cls"); printf("\n �������� ��������!!! ��������� �������! \n"); break;
		}
	}

	return 0;
}