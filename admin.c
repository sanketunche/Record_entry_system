
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

// File for doing Administrative task


		/******************************** Administrative Task*************************************************************/


void getAdminChoice(){
	int ch;
	while(1){
		printf("Please Select Your Option\n");
		printf("1. Delete Employee Data\n");
		printf("2. HR Mangement\n3. Purchasing Department\n4. Switch to Main Menu \n");
		scanf("%d",&ch);
		switch(ch){
			case 1:  deleteEmp();
				break;
			case 2: //HR Management
				break;
			case 3:  //Purchasing Department
				break;
			case 4 : selectChoice();
				break;
			default:
			break;
		}
	}
}
void deleteEmp(){
	FILE *fp, *fp1;
	int count = 0;
	int flag = 0;
	char ch;
	int line = 0;
	char tmp[20], key[20], tmp1[20], tmp2[20], tmp3[20], tmp4[20];
	printf("Enter the ID to be Deleted ");
	scanf("%s",key);
	fp = fopen("emp_data.txt", "r");
	// First of all getting the line number
	while(!feof(fp)){
		fscanf(fp, "%s\t%s\t%s\t%s\n",tmp1, tmp2, tmp3, tmp4);
		line++;
		if(strcmp(key, tmp1) == 0){
			printf("Line Number : %d \n",line);
			flag = 1;
			break;
		}

	}
	fclose(fp);
	if(flag == 0){
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
	fclose(fp);
	fclose(fp1);
}


