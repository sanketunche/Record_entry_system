
/*****************************************************************************
 * Copyright (C) Sanket S. Unche sanketunche04@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/


#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include"record.h"
#include<unistd.h>
#include<pthread.h>
#include <time.h>

pthread_t tid;

#define KRED  "\x1B[31m"
#define RESET "\033[0m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"


void selectChoice();
void search();
void gerrewind(int);
void deleteEmp();
void getAdminChoice();
void forgotpwd();
void trash();
int tempty();
int fcopy();

/* Inserts data of Employee */ 

int insert(data *node){
	FILE *fp;
	FILE *fp1;
	int flag = 0;
	char temp[20];
	int i = 0;
	fp = fopen("emp_data.txt", "a+");
	if(fp == NULL){

		printf(KRED "Someething is going wrong...Please try after some time\n" RESET);
	}
	else{
		printf(KBLU "Enter the Data \n\nId\tName\tCity\tSalary\n" RESET );
		scanf("%s%s%s%s",node->id,node->name,node->city,node->salary);
		while(node->id[i] != '\0'){

			if(isdigit(node->id[i]))
				flag = 0;
			else{
				flag = 1;
				break;
			}
			i++;
		}
		i = 0;
		/*while(node->salary[i] != '\0'){
			if(isdigit(node->salary[i])){
				flag = 0;
			}
			else{
				flag = 1;
				break;
			}
		}*/
		if(flag == 1){
			printf(KRED "Sorry, Invalid ID or SALARY" RESET);
			flag = 0;
		}
		else{
			fp1 = fopen("emp_data.txt", "r");
			if(fp == NULL){
			}
			else{
				while(!feof(fp)){
					fscanf(fp, "%s\n",temp);
					if(strcmp(temp, node->id) == 0){
						flag = 1;
						break;
					}
				}
				if(flag == 1){
					printf(KRED "Duplicate record found...!\n" RESET);
				}
				else{
					fprintf(fp, "%s\t%s\t%s\t%s\n", node->id, node->name, node->city, node->salary);
					printf(KGRN "Record Inserted...\n" RESET);
				}
	//		fclose(fp);
			}
		}
	}
	fclose(fp);
	
}

/*  Displays the Data of Employee */

void showData(){
	FILE *fp;
	char ch;
	char key[1];
	char  id[20], salary[20];
	char name[20], city[20];
	system("clear");
	printf(KBLU "\t\t\t\t\t   DATA DISPLAY WIZARD\n\n" RESET);
	fp = fopen("emp_data.txt", "r");
	printf("\t\t\t\t\tID\tNAME\tCITY\tSALARY\n");
	if(fp == NULL){
		printf(KRED "Something is went wrong...\n" RESET);
	}	
	else{
		//printf(KYEL
		while(!feof(fp)){
			fscanf(fp, "%s\t%s\t%s\t%s\n",id, name, city, salary);
			printf("\t\t\t\t\t%s\t%s\t%s\t%s\n",id, name, city, salary);
		}
		
	}
	fclose(fp);
	printf(KBLU "\n\nPress Any Key to Continue...\n\n " RESET);
	ch = getchar();
}

/* This Function is for Selecting Files */

void selectChoice(){
	int choice;
	struct data *new_node;
	while(1){
		printf(KBLU "\t\t\t\t\t     Please Select Your Choice \n\t\t\t\t\t------------------------------------\n\n" RESET);
		printf(KWHT "\t\t\t\t\t1. Insert Data \n\t\t\t\t\t2. View Data\n\t\t\t\t\t3. Search for Record\n\t\t\t\t\t4. Go For Administration\n\t\t\t\t\t5. Exit\n\n" RESET);
		printf("\t\t\tGive your choice -> ");
		scanf("%d",&choice);
		switch(choice){
			case 1 :	
				new_node = (struct data*)malloc(sizeof(data));
				system("clear");
				insert(new_node);
				break;
			
			case 2 :
				showData();
				break;
			case 3 : 
				search();
				break;
			case 4 :getAdminChoice();
				break;
			case 5 :exit(0);
				break;
			default : printf(KRED "\n * Please Insert Valid Choide\n\n" RESET);
					break;

		}	
	}


}

/* Function for searching data */

void search(){
	FILE *fp, *fp1;
	int ch, i;
	int count = 0;
	char tmp[20], key[20], tmp1[20], tmp2[20], tmp3[20], tmp4[20];
	fp = fopen("emp_data.txt", "r");
	fp1 = fopen("emp_data.txt", "r");
	system("clear");
	printf(KRED " Search Wizard\n\n" RESET);
	printf(KMAG "How do you want to search\n" RESET);
	printf("\t1. By Id\n\t2. By Name\n\t3. By City\n\t4. By Salary\n");
	scanf("%d",&ch);
	switch(ch){
		case 1 :
			printf("Enter the ID : ");
			scanf("%s",key);
			while(!feof(fp)){
				fscanf(fp,"%s", tmp);
				count++;
				if(strcmp(tmp, key) == 0){
					// Found Record
					/*fp1 = fopen("emp_data.txt", "r");
					for( i = 0; i <= count; i++){
						fscanf(fp1, "%s\t%s\t%s\t%s\n", tmp1, tmp2, tmp3, tmp4);}
					printf("ID : %s", tmp1);
					fclose(fp1);*/
					fp1 = fp;
					fscanf(fp1, "%s\t%s\t%s",tmp1, tmp2, tmp3);
					printf("ID is %s %s %s %s \n ", tmp, tmp1, tmp2, tmp3);
				}

			}
			fclose(fp);
		break;
		
		case 2 :
			printf("Enter the Name : ");
			scanf("%s",key);
			while(!feof(fp)){	
				fscanf(fp,"%s\t%s\t%s\t%s\n",tmp, tmp1, tmp2, tmp3);
				count++;
				if(strcmp(key, tmp1) == 0){
					/*fseek(fp1, -20L, SEEK_CUR);
					fscanf(fp1, "%s\t%s\t%s\t%s", tmp1, tmp2, tmp3, tmp4);
					printf("ID is %s %s %s %s \n ", tmp, tmp1, tmp2, tmp3);*/
					//fp1 = fopen("emp_data.txt", "r");
					/*rewind(fp1);
					for(i = 0;i < count; i++){
						fscanf(fp1, "%s\t%s\t%s\t%s\n",tmp1,tmp2,tmp3,tmp4);
					}
					printf("Data : %s %s %s %s ",tmp1, tmp2, tmp3, tmp4);
					//break;*/
					gerrewind(count);
					break;
				}
			}
			fclose(fp);
		break;
		case 3 :
			printf("Enter the City : ");
			scanf("%s",key);
			while(!feof(fp)){	
				fscanf(fp,"%s\t%s\t%s\t%s\n",tmp, tmp1, tmp2, tmp3);
				count++;
				if(strcmp(key, tmp2) == 0){
					/*fseek(fp1, -20L, SEEK_CUR);
					fscanf(fp1, "%s\t%s\t%s\t%s", tmp1, tmp2, tmp3, tmp4);
					printf("ID is %s %s %s %s \n ", tmp, tmp1, tmp2, tmp3);*/
					//fp1 = fopen("emp_data.txt", "r");
					/*rewind(fp1);
					for(i = 0;i < count; i++){
						fscanf(fp1, "%s\t%s\t%s\t%s\n",tmp1,tmp2,tmp3,tmp4);
					}
					printf("Data : %s %s %s %s ",tmp1, tmp2, tmp3, tmp4);
					//break;*/
					gerrewind(count);
					break;
				}
			}
			fclose(fp);
		break;
		case 4 :
			printf("Enter the Salary : ");
			scanf("%s",key);
			while(!feof(fp)){	
				fscanf(fp,"%s\t%s\t%s\t%s\n",tmp, tmp1, tmp2, tmp3);
				count++;
				if(strcmp(key, tmp2) == 0){
					/*fseek(fp1, -20L, SEEK_CUR);
					fscanf(fp1, "%s\t%s\t%s\t%s", tmp1, tmp2, tmp3, tmp4);
					printf("ID is %s %s %s %s \n ", tmp, tmp1, tmp2, tmp3);*/
					//fp1 = fopen("emp_data.txt", "r");
					/*rewind(fp1);
					for(i = 0;i < count; i++){
						fscanf(fp1, "%s\t%s\t%s\t%s\n",tmp1,tmp2,tmp3,tmp4);
					}
					printf("Data : %s %s %s %s ",tmp1, tmp2, tmp3, tmp4);
					//break;*/
					gerrewind(count);
					break;
				}
			}
			fclose(fp);
		break;
		default :
			printf(KRED "Please Enter Valid Choice \n" RESET);
			break;
	}
			
	
}
void gerrewind(int count){
	int i;
	FILE *fp1;
	char tmp1[20], tmp2[20], tmp3[20], tmp4[20];
	fp1 = fopen("emp_data.txt", "r");
	if(fp1 == NULL)
		printf(KRED "Some problem occured\n" RESET);
	else{
		for(i = 0; i < count; i++){
			fscanf(fp1, "%s\t%s\t%s\t%s\n", tmp1, tmp2, tmp3, tmp4);
		}
		printf(KYEL "Data : %s %s %s %s \n" RESET ,tmp1, tmp2, tmp3, tmp4);
		fclose(fp1);
	}
	
}

// File for doing Administrative task


		/******************************** Administrative Task*************************************************************/


void getAdminChoice(){
	int ch;
	time_t now;
	int flag;
	FILE *fp, *fp1;
	char pwd[20];
	char tmp[20], tmp1[20], tmp2[20];
	system("clear");
	 fp = fopen("config.txt", "r");
	//FILE *log = fopen("log.txt", "a+");
	if(fp == NULL){
		printf("Administration can not be done currenltly...\n");
		return;
	}	
	if(fp1 == NULL){
		printf("log failed");
	}
	printf(KRED " \n\t\t\t\t\t You are in the Administrative Zone \n" RESET);
	printf(KYEL "\t\t\t\t( Warning : The Log of Your Activities might be saved . ) \n\t\t\t\t\t---------------------------------------------------\n" RESET);
	printf("\n\n\t\t\t\t\t Enter the Master Password ->  ");
	scanf("%s",pwd);
	fscanf(fp, "%s\t%s\t%s",tmp1, tmp2, tmp);
	if(strcmp(tmp, pwd)){
		fp1 = fopen("log.txt","a+");
		printf(KRED "\t\t\t\t\t INVALID PASSWORD \n\n"RESET);
		now = time(&now);
		strcpy(tmp1,  ctime(&now));
		fprintf(fp1, " %s -> INVALID PASSWORD \n\n" ,tmp1);
		fclose(fp1);
		return;
	}
	fp1 = fopen("log.txt", "a+");
	if(fp1 == NULL){
		printf(KRED " Log failed..." RESET);
	}
	now = time(&now);
	strcpy(tmp1, ctime(&now));
	fprintf(fp1, " %s -> ROOT USER LOGGED IN\n\n" ,tmp1);
	fclose(fp1);
	system("clear");
	
	while(1){

		now = time(&now);
		strcpy(tmp1, ctime(&now));
		printf(KRED " \n\t\t\t\t\t You are in the Administrative Zone \n" RESET);
		printf(KYEL "\t\t\t\t( Warning : The Log of Your Activities might be saved . ) \n\t\t\t\t\t");
		printf(KBLU "Logged in as ROOT on  %s " RESET , tmp1);
		printf(KYEL "\t\t\t\t ---------------------------------------------------\n\n" RESET);
		printf("Please Select Your Option\n");
		printf("\t\t\t\t\t1. Delete Employee Data\n");
		printf("\t\t\t\t\t2. Employee Daily Record\n\t\t\t\t\t3. Display Log\n\t\t\t\t\t4. Change Password \n\t\t\t\t\t5. Go to Trash\n\t\t\t\t\t6. Switch to Main Menu \n\t\t\t\t\t-> ");
		scanf("%d",&ch);
		switch(ch){
			case 1:  deleteEmp();
				system("clear");
				flag = 1;
				break;
			case 2: //HR Management
				flag = 2;
				system("clear");
				break;
			case 3:  //Purchasing Department
				showlog();				
				//printf("\n Sorry, this function is not available currently..");
				flag = 3;
				//system("clear");
				break;
			case 4 :
				 system("clear");
				forgotpwd();
				 break;
			case 6 : system("clear");
				// call for forgot password
				selectChoice();
				break;
			case 5 : system("clear");
				 trash();
				 break;
			default:
					break;
		}
		// Here is the Code for Generating Logs
		
	}
}

/* Function for Displaying logs */

void showlog(){
	FILE *fp;
	char ch;
	
system("clear");
	printf(KBLU "\t\t\t\t\t   LOGS DISPLAY WIZARD\n\n" RESET);
	fp = fopen("log.txt", "r");
	if(fp == NULL){
		printf(KRED "Something is went wrong...\n" RESET);
	}	
	else{
		while((ch = fgetc(fp)) != EOF){
			printf("%c",ch);
		}
		
	}
	fclose(fp);
	printf(KBLU "\n\nPress Any Key to Continue...\n\n " RESET);
}

/* Function for deleting employe data */

void deleteEmp(){
	FILE *fp, *fp1, *trash;
	FILE *log;
	char tt[20];
	time_t now;
	int count = 0, i;
	int flag = 0;
	char ch;
	int line = 0;
	char tmp[20], key[20], tmp1[20], tmp2[20], tmp3[20], tmp4[20];
	printf("Enter the ID to be Deleted ");
	scanf("%s",key);
	fp = fopen("emp_data.txt", "r");
	trash = fopen("trash.txt", "a+");
	// First of all getting the line number
	while(!feof(fp)){
		fscanf(fp, "%s\t%s\t%s\t%s\n",tmp1, tmp2, tmp3, tmp4);
		line++;
		if(strcmp(key, tmp1) == 0){
			printf(KGRN " \nData is matched and will be Deleted Shortly...\n" RESET);
			fprintf(trash,"%s\t%s\t%s\t%s\n", tmp1, tmp2, tmp3, tmp4);
			fclose(trash);
			flag = 1;
			break;
		}

	}
	fclose(fp);
	if(flag == 0){
		now = time(&now);
		strcpy(tt, ctime(&now));
		log = fopen("log.txt", "a+");
		if(log == NULL)
			printf("Log Failed");
		fprintf(log, " %s -> DELETE ATTEMPTED BUT GOT FAILURE\n\n",tt);
		fclose(log);
		printf("\n\nSorry no Data found with this ID...\n\n");
		return;
	}
	fp1 = fopen("temp.txt", "w");
	//rewind(fp);
	fp = fopen("emp_data.txt", "r");
	while(!feof(fp)){
		fscanf(fp, "%s\t%s\t%s\t%s\n",tmp1, tmp2, tmp3, tmp4);
		count++;
		if(count == line){
			// Do Nothing
		}	
		else{
			fprintf(fp1, "%s\t%s\t%s\t%s\n", tmp1, tmp2, tmp3, tmp4);
			
		}
	}
	fclose(fp);
	fclose(fp1);
	fp1 = fopen("temp.txt", "r");
	fp = fopen("emp_data.txt", "w");
	while(!feof(fp1)){
		fscanf(fp1, "%s\t%s\t%s\t%s\n",tmp1, tmp2, tmp3, tmp4);
		fprintf(fp, "%s\t%s\t%s\t%s\n", tmp1, tmp2, tmp3, tmp4);
	}
	now = time(&now);
	strcpy(tt, ctime(&now));
	log = fopen("log.txt", "a+");
	if(log == NULL)
		printf("Log failed ");
	fprintf(log, " %s -> DELETED RECORD OF ID : %s SUCCESSFULLY\n\n", tt, key);
	fclose(log);
	fclose(fp);
	fclose(fp1);
	ask:
	printf("\n\n Do You want to Continue...(Y/N) ");
	scanf("%s", tmp1);
	if(strcmp(tmp1, "Y"))
		exit(0);
	else
		return;
		
}

/* Function for changing password */

void forgotpwd(){
	FILE *fp, *fp1, *log;
	char temp1[20], key[20], temp2[20], temp3[20];
	int i, count;
	fp = fopen("config.txt", "r+");
	fscanf(fp, "%s\t%s\t%s", temp1, temp2, temp3);
	printf("Enter the OLD Password ");
	scanf("%s", key);
	if(strcmp(key, temp3)){
		printf("INVALID ATTEMPT\n ");
		return;
	}
	//Password is matched
	fclose(fp);
	printf("\nEnter the New Password ");
	scanf("%s", temp3);
	fp = fopen("config.txt", "w");
	fprintf(fp, "%s\t%s\t%s", temp1, temp2, temp3);
	fclose(fp);
	printf("Password Changed Successfully...\n\n");
}

/* Function for trash Management */

void trash(){
	FILE *trash, *fp;
	char tmp1[20], tmp2[20], tmp3[20], tmp4[20], t[20];
	time_t now;
	int count = 0;
	int ch, flag;
	char c;
	trash = fopen("trash.txt", "r+");
	if(trash == NULL){
		printf("Something went wrong...");
		return;
	}
	now = time(&now);
	strcpy(t, ctime(&now));
	printf(KRED " \n\t\t\t\t\t\t\t Trash \n" RESET);
	printf(KYEL "\t\t\t\t( Warning : The Log of Your Activities might be saved . ) \n\t\t\t\t\t");
	printf(KBLU "Logged in as ROOT on  %s " RESET , t);
	printf(KYEL "\t\t\t\t ------------------------------------------------------\n\n" RESET);
	printf("\n\t\t\t\t\t\tTrash Contains Following Data \n\n");
	printf( "\t\t\t\t\t\tID\tNAME\tCITY\tSALARY\n");
	while(!feof(trash)){
		fscanf(trash, "%s\t%s\t%s\t%s\n", tmp1, tmp2, tmp3, tmp4);
		printf(KWHT "\t\t\t\t\t\t%s\t%s\t%s\t%s\n" RESET, tmp1, tmp2, tmp3, tmp4);
		if(tmp1)
			count++;
	}
	//count = count -1;
	printf(KYEL "\n\n\t\t\t\t\t\t No. of Records Found -> %d \n\n"RESET ,count);
	fclose(trash);
	printf(KYEL "\t\t\t\t ------------------------------------------------------\n\n" RESET);
	printf("\t\t\t\t You can Do Following Operations on Trash\n");
	printf(KWHT "\t\t\t\t\t1. Restore Trash Data\n\t\t\t\t\t2. Emptry Trash\n\t\t\t\t\t-> ");
	scanf("%d",&ch);
	flag = 0;
	switch(ch){
		case 1 :	
			flag = fcopy();
		/*	if(flag == 0)
				printf(KRED " Data failure Occured\n" RESET);
			else
				printf("Data Restored Successfully...\n");

			break;*/
		case 2 : 
			flag = tempty();
			/*if(flag == 0){
				printf(KRED "Data Failure Occured..." RESET);
			}
			else{
				printf(KGRN "Yeahhh...!\nTrash is Empty Now...\n" RESET);
				return;
			}*/
			//break;
			break;

		 default :
				printf("Please Enter Valid choice");
				break;
		
	}
}

/* Restore data from trash */

int fcopy(){
	FILE *fp, *trash;
	char t[20], tmp1[20], tmp2[20], tmp3[20], tmp4[20];
	time_t now;
	fp = fopen("emp_data.txt", "a+");
	if(fp == NULL){
		printf(KRED "\nCant Restore Data Right Now \n");
		return 0;
	}
	trash = fopen("trash.txt", "r");
	if(trash == NULL){
		printf(KRED "\nCant Restore Data Right Now\n");
		return 0;
	}
	while(!feof(trash)){
		now = time(&now);
		strcpy(t, ctime(&now));
		fscanf(trash, "%s\t%s\t%s\t%s\n", tmp1, tmp2, tmp3, tmp4);
		//fprintf(fp, "Restored Data on %s ->", t);
		fprintf(fp, "%s\t%s\t%s\t%s\n", tmp1, tmp2, tmp3, tmp4);
	}
	main();
	fclose(fp);
	fclose(trash);
	return 1;
}

int tempty(){
	/*FILE *fp;
/	system("rm trash.txt");
//	system("touch trash.txt");
	fp = fopen("trash.txt", "w+");
	fclose(fp);
	return 1;
*/
}

/** Thread for time */





int main(){
	char uname[20], password[20], uname1[20], password1[20];
	FILE *fp;
	int choice, i, err;
	//display();
	system("clear");
	printf("\n\n\n");
	system("setterm -bold on");
	printf(KGRN "\n\n\t\t\t\t\tWelcome to the Record Entry System\n\n" RESET);
	system("setterm -bold off");
	for(i = 0; i < 140; i++){
		printf("-");	
	}
	printf("\n\n\t\t\t\t\tPlease LogIn to Continue\n\t\t\t\t\tUsername : ");
	scanf("%s",uname);
	printf("\t\t\t\t\tPassword : ");
	scanf("%s",password);
	printf("\n\n");
	fp = fopen("config.txt","r");
	if(fp == NULL){
		printf("...Something is Going Wrong ..PLease try after some time\n");
	}
	else{
		fscanf(fp, "%s\t", uname1);
		fscanf(fp, "%s", password1);
		if(strcmp(uname,uname1) == 0 && strcmp(password,password1) == 0){
			system("clear");
			printf("\nLogged In...\n\n");
			//printf("\t\t\t\t\t____________________\n\n");
			fclose(fp);
			selectChoice();
		}
		else{
			fclose(fp);
			system("clear");
			printf("Sorry threre is Some Problem\n ");
			
		}
	}
	return 0;
}

