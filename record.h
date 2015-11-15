
// Struture for Managing Basic data

typedef struct data{
	char id[20];
	char name[20];
	//int age;
	char city[20];
	char salary[20];
}data;

// Structure for managing employee daily data
typedef struct info{
	char id[20];
	time_t intime;
	time_t outtime;
	int hour;
	int totalsal;
}info;

int insert(data *);
void showData();
void getCount();

