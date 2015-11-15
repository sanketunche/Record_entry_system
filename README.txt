								  Record Entry System
						
Sanket S. Unche
MIS : 141503016
**********************************************************************************************************************************************

Record Entry System is specially designed to manage the Employee of data. While developing this application, utmost care is taken about security. The Log of activities and Trash for the data recovery is maintained. Record Entry System has following modules :

1. Login 
	When this application starts we have to login first. The Username and password are verified against the Authenticated Username and 
password stored in "config.txt" file. The application will accept only aunthenticated user.

2. Insert Data
	Module for inserting data into "emp_data.txt" file. The basic information like Id, Name, City and Salary is stored.

3. View Data 
	Module for Displaying data on terminal.

4. Administrative Activities
	This Module is specially designed for the administrative activities. To use this module Root login in needed. The password of Root is stored in "config.txt".

5.Log
	Log of Administrative activities are stored in "log.txt".

6. Trash
	Trash for data recovery is implemented. The Deleted data is stored in "trash.txt".
