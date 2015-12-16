/* AUTOMATED ADMISSION SYSTEM */
#include<stdio.h>
#include<conio.h>

// SELF-REFERENSIAL STRUCTURES
typedef struct student * student;
struct student
{
	char name[20], fatherName[20], address[50], email[30];
	int catagory, centerChoice[3], marks[2];
	int roll, centerAlloted, rank, branchChoice[3], branchAlloted;
	student link;
} *LLstudent=NULL;

typedef struct center * center;
struct center
{
	char name[20], address[50];
	int id, capacity, occupied;
	center link;
} *LLcenter = NULL;

typedef struct branch * branch;
struct branch
{
	char name[20];
	int id, totalSeat, reserveSeat[4];
	branch link;
} *LLbranch = NULL;

// FUNCTION INITIALISATION
void loadFromFile();
void writeToFile();

void students();
void addNewStudent();
int studLogin();
void returnCandidate(int);
void councelling();

int adminLogin();
void administrator();
void addCenter();
void addBranch();
void allotCenter();
void allotSeat();
void assignRank();
void sortByRank();
void display();
void dispStudent();
void dispAllStud();
void dispCenter();
void dispBranch();

// MAIN
void main()
{
	int opnMain;
	clrscr();
	loadFromFile();
	do
	{	printf("\n1  STUDENT LOGIN");
		printf("\n2  ADMINISTRATOR LOGIN");
		printf("\n0  EXIT... ");
		scanf("%d", &opnMain);

		switch(opnMain)
		{
			case 1	: students();
				  break;
			case 2	: if(adminLogin() == 1)
					administrator();
		};
	} while(opnMain != 0);
	writeToFile();
}

// FILE FUNCTIONS
void loadFromFile()
{
	FILE* spStudent;
	FILE* spCenter;
	FILE* spBranch;

	spStudent = fopen("student.txt", "rb");	//Student

	if(spStudent != NULL)
	{
		student nodeStudent, nodeStudent1;
		int counter, length, next;
		do {
		nodeStudent = (student) malloc(sizeof(struct student));

		fread(&length, sizeof(int), 1, spStudent);
		fread(nodeStudent->name, sizeof(char), length, spStudent);
		nodeStudent->name[length] = '\0';
		fread(&length, sizeof(int), 1, spStudent);
		fread(nodeStudent->fatherName, sizeof(char), length, spStudent);
		nodeStudent->fatherName[length] ='\0';
		fread(&length, sizeof(int), 1, spStudent);
		fread(nodeStudent->address, sizeof(char), length, spStudent);
		nodeStudent->address[length] = '\0';
		fread(&length, sizeof(int), 1, spStudent);
		fread(nodeStudent->email, sizeof(char), length, spStudent);
		nodeStudent->email[length] = '\0';
		fread(&nodeStudent->catagory, sizeof(int), 1, spStudent);
		for(counter = 0; counter < 3; counter++)
			fread(&nodeStudent->centerChoice[counter], sizeof(int), 1, spStudent);
		for(counter = 0; counter < 2; counter++)
			fread(&nodeStudent->marks[counter], sizeof(int), 1, spStudent);
		fread(&nodeStudent->roll, sizeof(int), 1, spStudent);
		fread(&nodeStudent->centerAlloted, sizeof(int), 1, spStudent);
		fread(&nodeStudent->rank, sizeof(int), 1, spStudent);
		for(counter = 0; counter < 3; counter++)
			fread(&nodeStudent->branchChoice[counter], sizeof(int), 1, spStudent);
		fread(&nodeStudent->branchAlloted, sizeof(int), 1, spStudent);
		fread(&next, sizeof(int), 1, spStudent);
		nodeStudent->link = NULL;

		if(LLstudent == NULL)
			LLstudent = nodeStudent;
		else
		{
			for(nodeStudent1 = LLstudent; nodeStudent1->link != NULL; nodeStudent1 = nodeStudent1->link);
			nodeStudent1->link = nodeStudent;
		}
		} while(next == 1);
	}
	fclose(spStudent);

	spCenter = fopen("center.txt", "rb");	//Center
	if(spCenter != NULL)
	{
		center nodeCenter, nodeCenter1;
		int counter, length, next;
		do {
		nodeCenter = (center) malloc(sizeof(struct center));

		fread(&length, sizeof(int), 1, spCenter);
		fread(nodeCenter->name, sizeof(char), length, spCenter);
		nodeCenter->name[length] = '\0';
		fread(&length, sizeof(int), 1, spCenter);
		fread(nodeCenter->address, sizeof(char), length, spCenter);
		nodeCenter->address[length] = '\0';
		fread(&nodeCenter->id, sizeof(int), 1, spCenter);
		fread(&nodeCenter->capacity, sizeof(int), 1, spCenter);
		fread(&nodeCenter->occupied, sizeof(int), 1, spCenter);
		fread(&next, sizeof(int), 1, spCenter);
		nodeCenter->link = NULL;

		if(LLcenter == NULL)
			LLcenter = nodeCenter;
		else
		{
			for(nodeCenter1 = LLcenter; nodeCenter1->link != NULL; nodeCenter1 = nodeCenter1->link);
			nodeCenter1->link = nodeCenter;
		}
		} while(next == 1);
	}
	fclose(spCenter);

	spBranch = fopen("branch.txt", "rb");	//Branch
	if(spBranch != NULL)
	{
		branch nodeBranch, nodeBranch1;
		int counter, length, next;
		do {
		nodeBranch = (branch) malloc(sizeof(struct branch));

		fread(&length, sizeof(int), 1, spBranch);
		fread(nodeBranch->name, sizeof(char), length, spBranch);
		nodeBranch->name[length] = '\0';
		fread(&nodeBranch->id, sizeof(int), 1, spBranch);
		fread(&nodeBranch->totalSeat, sizeof(int), 1, spBranch);
		for(counter = 0; counter < 4; counter++)
			fread(&nodeBranch->reserveSeat[counter], sizeof(int), 1, spBranch);
		fread(&next, sizeof(int), 1, spBranch);
		nodeBranch->link = NULL;

		if(LLbranch == NULL)
			LLbranch = nodeBranch;
		else
		{
			for(nodeBranch1 = LLbranch; nodeBranch1->link != NULL; nodeBranch1 = nodeBranch1->link);
			nodeBranch1->link = nodeBranch;
		}
		} while(next == 1);
	}
	fclose(spBranch);
}

void writeToFile()
{
	if(LLstudent != NULL)	// Student
	{
		FILE* spStudent;
		student nodeStudent;
		int length, counter, next;
		spStudent = fopen("student.txt", "wb");

		for(nodeStudent = LLstudent; nodeStudent; nodeStudent = nodeStudent->link)
		{
			length = strlen(nodeStudent->name);
			fwrite(&length, sizeof(int), 1, spStudent);
			fwrite(nodeStudent->name, sizeof(char), length, spStudent);
			length = strlen(nodeStudent->fatherName);
			fwrite(&length, sizeof(int), 1, spStudent);
			fwrite(nodeStudent->fatherName, sizeof(char), length, spStudent);
			length = strlen(nodeStudent->address);
			fwrite(&length, sizeof(int), 1, spStudent);
			fwrite(nodeStudent->address, sizeof(char), length, spStudent);
			length = strlen(nodeStudent->email);
			fwrite(&length, sizeof(int), 1, spStudent);
			fwrite(nodeStudent->email, sizeof(char), length, spStudent);
			fwrite(&nodeStudent->catagory, sizeof(int), 1, spStudent);
			for(counter = 0; counter < 3; counter++)
				fwrite(&nodeStudent->centerChoice[counter], sizeof(int), 1, spStudent);
			for(counter = 0; counter < 2; counter++)
				fwrite(&nodeStudent->marks[counter], sizeof(int), 1, spStudent);
			fwrite(&nodeStudent->roll, sizeof(int), 1, spStudent);
			fwrite(&nodeStudent->centerAlloted, sizeof(int), 1, spStudent);
			fwrite(&nodeStudent->rank, sizeof(int), 1, spStudent);
			for(counter = 0; counter < 3; counter++)
				fwrite(&nodeStudent->branchChoice[counter], sizeof(int), 1, spStudent);
			fwrite(&nodeStudent->branchAlloted, sizeof(int), 1, spStudent);
			next = (nodeStudent->link == NULL) ? 0 : 1;
			fwrite(&next, sizeof(int), 1, spStudent);
		}
		fclose(spStudent);
	}

	if(LLcenter != NULL)	// Center
	{
		FILE* spCenter;
		center nodeCenter;
		int length, next;
		spCenter = fopen("center.txt", "wb");

		for(nodeCenter = LLcenter; nodeCenter; nodeCenter = nodeCenter->link)
		{
			length = strlen(nodeCenter->name);
			fwrite(&length, sizeof(int), 1, spCenter);
			fwrite(nodeCenter->name, sizeof(char), length, spCenter);
			length = strlen(nodeCenter->address);
			fwrite(&length, sizeof(int), 1, spCenter);
			fwrite(nodeCenter->address, sizeof(char), length, spCenter);
			fwrite(&nodeCenter->id, sizeof(int), 1, spCenter);
			fwrite(&nodeCenter->capacity, sizeof(int), 1, spCenter);
			fwrite(&nodeCenter->occupied, sizeof(int), 1, spCenter);
			next = (nodeCenter->link == NULL) ? 0 : 1;
			fwrite(&next, sizeof(int), 1, spCenter);
		}
		fclose(spCenter);
	}

	if(LLbranch != NULL) // Branch
	{
		FILE* spBranch;
		branch nodeBranch;
		int length, counter, next;
		spBranch = fopen("branch.txt", "wb");

		for(nodeBranch = LLbranch; nodeBranch; nodeBranch = nodeBranch->link)
		{
			length = strlen(nodeBranch->name);
			fwrite(&length, sizeof(int), 1, spBranch);
			fwrite(nodeBranch->name, sizeof(char), length, spBranch);
			fwrite(&nodeBranch->id, sizeof(int), 1, spBranch);
			fwrite(&nodeBranch->totalSeat, sizeof(int), 1, spBranch);
			for(counter = 0; counter < 4; counter++)
				fwrite(&nodeBranch->reserveSeat[counter], sizeof(int), 1, spBranch);
			next = (nodeBranch->link == NULL) ? 0 : 1;
			fwrite(&next, sizeof(int), 1, spBranch);
		}
		fclose(spBranch);
	}
}

// STUDENT FUNCTIONS
void students()
{
	int opnStud, candidateID;
	clrscr();
	do
	{	printf("\n1  REGISTER NEW CANDIDATE");
		printf("\n2  LOGIN RETURN CANDIDATE");
		printf("\n3  APPEAR COUNCELLING");
		printf("\n0  Return to previous menu... ");
		scanf("%d", &opnStud);

		switch(opnStud)
		{
			case 1	: addNewStudent();
				  break;
			case 2	: candidateID = studLogin();
				  if(candidateID != 0)
					returnCandidate(candidateID);
				  break;
			case 3	: candidateID = studLogin();
				  if(candidateID != 0)
					councelling(candidateID);
				  break;
			case 0	: clrscr();
		};
	} while(opnStud != 0);
}

void addNewStudent()
{
	student nodeStudent, nodeStudent2;
	center nodeCenter;
	int counter;
	nodeStudent = (student) malloc(sizeof(struct student));

	fflush(stdin);
	printf("Candidate Name\t: ");
	gets(nodeStudent->name);
	printf("Father's Name\t: ");
	gets(nodeStudent->fatherName);
	printf("Address\t\t: ");
	gets(nodeStudent->address);
	printf("E-mail\t\t: ");
	gets(nodeStudent->email);
	printf("Catagory (0-General, 1-SC, 2-ST, 3-OBC)\t: ");
	scanf("%d", &nodeStudent->catagory);
	for(nodeCenter = LLcenter; nodeCenter; nodeCenter = nodeCenter->link)
		printf("%d\t%s\t%s\n", nodeCenter->id, nodeCenter->name, nodeCenter->address);
	printf("Center Choice (choose 3 from above)\t: ");
	for(counter = 0; counter < 3; counter++)
		scanf("%d", &nodeStudent->centerChoice[counter]);
	printf("10th Marks percent\t: ");
	scanf("%d", &nodeStudent->marks[0]);
	printf("12th Marks percent\t: ");
	scanf("%d", &nodeStudent->marks[1]);
	nodeStudent->centerAlloted = 0;
	for(counter = 0; counter < 3; counter++)
		nodeStudent->branchChoice[counter] = 0;
	nodeStudent->branchAlloted = 0;
	nodeStudent->rank = 0;
	nodeStudent->link = NULL;

	if(nodeStudent->marks[1] < 60)
		printf("Your 12th marks is less then 60%. You do not qualify.");
	else
	{
		if(LLstudent == NULL)
		{
			nodeStudent->roll = 901;
			LLstudent = nodeStudent;
		}
		else
		{
			for(nodeStudent2 = LLstudent; nodeStudent2->link != NULL; nodeStudent2 = nodeStudent2->link);
			nodeStudent->roll = (nodeStudent2->roll)+1;
			nodeStudent2->link = nodeStudent;
		}
		printf("You have been successfully registered. Your roll no is %d.", nodeStudent->roll);
	}
	getch();
	clrscr();
}

int studLogin()
{
	int candidateID = 0, roll;
	char email[25];
	student nodeStudent;

	printf("\nEnter roll number\t: ");
	scanf("%d", &roll);
	for(nodeStudent = LLstudent; nodeStudent->roll != roll && nodeStudent; nodeStudent = nodeStudent->link);
	if(nodeStudent == NULL)
		printf("You are not yet registered");
	else
	{
		fflush(stdin);
		printf("Enter e-mail for confirmation\t: ");
		gets(email);
		if(strcmp(email, nodeStudent->email) == 0)
		{
			candidateID = roll;
			printf("Login Successful");
		}
		else
			printf("The email you have entered does not match.");
	}
	getch();
	clrscr();
	return candidateID;
}

void returnCandidate(int candidateID)
{
	student nodeStudent;
	center nodeCenter;
	branch nodeBranch;

	for(nodeStudent = LLstudent; nodeStudent->roll != candidateID; nodeStudent = nodeStudent->link);
	printf("\n%d\t%s", nodeStudent->roll, nodeStudent->name);
	if(nodeStudent->centerAlloted != 0)
	{
		for(nodeCenter = LLcenter; nodeCenter->id != nodeStudent->centerAlloted; nodeCenter = nodeCenter->link);
		printf("\nThe center alloted to you is\t:\t%s, ", nodeCenter->name);
		printf("\nCenter Address\t\t\t:\t%s, ", nodeCenter->address);
	}
	if(nodeStudent->rank != 0)
		printf("\nYour rank is\t\t\t:\t%d", nodeStudent->rank);
	if(nodeStudent->branchAlloted != 0)
	{
		for(nodeBranch = LLbranch; nodeBranch->id != nodeStudent->branchAlloted; nodeBranch = nodeBranch->link);
		printf("\nThe branch alloted to you is\t:\t%s", nodeBranch->name);
	}
	getch();
	clrscr();
}

void councelling(int candidateID)
{
	student nodeStudent;

	for(nodeStudent = LLstudent; nodeStudent->roll != candidateID; nodeStudent = nodeStudent->link);
	printf("\n%d\t%s", nodeStudent->roll, nodeStudent->name);
	if(nodeStudent->rank != 0)
	{
		int counter;
		branch nodeBranch;
		for(nodeBranch = LLbranch; nodeBranch; nodeBranch = nodeBranch->link)
			printf("\n%d\t%s", nodeBranch->id, nodeBranch->name);
		printf("\nChoose branch of your choice (any 3 from above, according to priority): ");
		for(counter = 0; counter < 3; counter++)
			scanf("%d", &nodeStudent->branchChoice[counter]);
	}
	else
		printf("\nYou are not elligible for councelling.");
	getch();
	clrscr();
}

// ADMINISTRATOR FUNCTIONS
#define password "password"
int adminLogin()
{
	char inputChar, passwordEntered[10];
	int passPosition,loginFail = 0;

	fflush(stdin);
	printf("Enter password to login as administrator : ");

	for(passPosition = 0, inputChar = getch(); inputChar != '\r' && passPosition < 10; inputChar = getch())
	{
		if((inputChar >= 48 && inputChar <= 57) || (inputChar >= 65 && inputChar <= 90) || (inputChar >= 97 && inputChar <= 122))
		{
			passwordEntered[passPosition] = inputChar;
			passPosition++;
			putc('*', stdout);
		}
	}
	passwordEntered[passPosition] = '\0';

	if(strcmp(passwordEntered, password) == 0)
	{
		loginFail = 1;
		printf("\nLogin Successful");
	}
	else
		printf("\nYou have entered an invalid password.");
	getch();
	clrscr();
	return loginFail;
}

void administrator()
{
	int opnAdmin;
	clrscr();
	do
	{	printf("\n1  ADD A CENTER");
		printf("\n2  ADD A BRANCH");
		printf("\n3  ALLOT CENTER");
		printf("\n4  ASSIGN RANK TO CANDIDATES");
		printf("\n5  ALLOT SEAT");
		printf("\n6  DISPLAY INFORMATION");
		printf("\n0  Return to previous menu... ");
		scanf("%d", &opnAdmin);

		switch(opnAdmin)
		{
			case 1	: addCenter();
				  break;
			case 2	: addBranch();
				  break;
			case 3	: allotCenter();
				  break;
			case 4	: assignRank();
				  break;
			case 5	: allotSeat();
				  break;
			case 6	: display();
				  break;
			case 0	: clrscr();
		};
	} while(opnAdmin != 0);
}

void addCenter()
{
	center nodeCenter;
	nodeCenter = (center) malloc(sizeof(struct center));

	fflush(stdin);
	printf("Enter Center name\t:\t");
	gets(nodeCenter->name);
	printf("Enter Center address\t:\t");
	gets(nodeCenter->address);
	printf("Enter capacity\t\t:\t");
	scanf("%d", &nodeCenter->capacity);
	nodeCenter->occupied = 0;
	nodeCenter->link = NULL;

	if(LLcenter == NULL)
	{
		nodeCenter->id = 1;
		LLcenter = nodeCenter;
	}
	else
	{
		center nodeCenter2;
		for(nodeCenter2 = LLcenter; nodeCenter2->link != NULL; nodeCenter2 = nodeCenter2->link);
		nodeCenter->id = (nodeCenter2->id)+1;
		nodeCenter2->link = nodeCenter;
	}
	clrscr();
}

#define reserve1 0.17
#define reserve2 0.17
#define reserve3 0.16
void addBranch()
{
	branch nodeBranch;
	nodeBranch = (branch) malloc(sizeof(struct branch));

	fflush(stdin);
	printf("\nEnter Branch name\t:\t");
	gets(nodeBranch->name);
	printf("\nEnter total seats\t:\t");
	scanf("%d", &nodeBranch->totalSeat);
	nodeBranch->reserveSeat[1] = (int) (reserve1 * nodeBranch->totalSeat);
	nodeBranch->reserveSeat[2] = (int) (reserve2 * nodeBranch->totalSeat);
	nodeBranch->reserveSeat[3] = (int) (reserve3 * nodeBranch->totalSeat);
	nodeBranch->reserveSeat[0] = nodeBranch->totalSeat - (nodeBranch->reserveSeat[1] + nodeBranch->reserveSeat[2] + nodeBranch->reserveSeat[3]);
	nodeBranch->link = NULL;

	if(LLbranch == NULL)
	{
		nodeBranch->id = 1;
		LLbranch = nodeBranch;
	}
	else
	{
		branch nodeBranch2;
		for(nodeBranch2 = LLbranch; nodeBranch2->link != NULL; nodeBranch2 = nodeBranch2->link);
		nodeBranch->id = (nodeBranch2->id)+1;
		nodeBranch2->link = nodeBranch;
	}
	clrscr();
}

void allotCenter()
{
	student nodeStudent;
	center nodeCenter;
	int flagAllot = 0, flagNotAllot = 0, counterChoice;

	for(nodeStudent = LLstudent; nodeStudent ; nodeStudent = nodeStudent->link, flagAllot = 0)
	{
		for(counterChoice = 0; (flagAllot == 0) && (counterChoice < 3); counterChoice++)
		{
			for(nodeCenter = LLcenter; nodeCenter->id != nodeStudent->centerChoice[counterChoice]; nodeCenter = nodeCenter->link);
			if(nodeCenter->occupied < nodeCenter->capacity)
			{
				nodeStudent->centerAlloted = nodeCenter->id;
				(nodeCenter->occupied)++;
				flagAllot = 1;
			}
		}
		if(flagAllot == 0 && counterChoice == 3)
			flagNotAllot = 1;
	}

	if(flagNotAllot == 1)	//Allot remaining students
	{
		for(nodeStudent = LLstudent; nodeStudent ; nodeStudent = nodeStudent->link)
		{
			if(nodeStudent->centerAlloted == 0)
			{
				for(nodeCenter = LLcenter; !(nodeCenter->occupied < nodeCenter->capacity) || nodeCenter; nodeCenter = nodeCenter->link);
				nodeStudent->centerAlloted = nodeCenter->id;
				(nodeCenter->occupied)++;
			}
		}
	}
}

void assignRank()
{
	student nodeStudent;

	for(nodeStudent = LLstudent; nodeStudent ; nodeStudent = nodeStudent->link)
	{
		printf("Enter Rank for %s\t%d\t:\t", nodeStudent->name, nodeStudent->roll);
		scanf("%d", &nodeStudent->rank);
	}
	clrscr();
}

void allotSeat()
{
	student nodeStudent;
	branch nodeBranch;
	int counterChoice, flagAllot = 0;

	sortByRank();

	for(nodeStudent = LLstudent; nodeStudent ; nodeStudent = nodeStudent->link, flagAllot = 0)
	{
		if(nodeStudent->branchChoice[0] != 0) {
		for(counterChoice = 0; (flagAllot == 0) && (counterChoice < 3); counterChoice++)
		{
			for(nodeBranch = LLbranch; nodeBranch->id != nodeStudent->branchChoice[counterChoice]; nodeBranch = nodeBranch->link);
			if(nodeBranch->reserveSeat[nodeStudent->catagory] > 0)
			{
				nodeStudent->branchAlloted = nodeBranch->id;
				(nodeBranch->reserveSeat[nodeStudent->catagory])--;
				flagAllot = 1;
			}
		}
		}
	}
}

void sortByRank()
{
	int noOfCandidate, counter1, counter2;
	student nodeStudent1, nodeStudent2, nodeStudent3;

	for(nodeStudent1 = LLstudent, noOfCandidate = 1; nodeStudent1->link != NULL ; nodeStudent1 = nodeStudent1->link, noOfCandidate++);

	for(counter1 = 0; counter1 < noOfCandidate; counter1++)
	{
		if(LLstudent->rank > (LLstudent->link)->rank)
		{
			nodeStudent2 = LLstudent->link;
			LLstudent->link = nodeStudent2->link;
			nodeStudent2->link = LLstudent;
			LLstudent = nodeStudent2;
		}
		for(counter2 = 2, nodeStudent1 = LLstudent, nodeStudent2 = nodeStudent1->link, nodeStudent3 = nodeStudent2->link; counter2 < (noOfCandidate - counter1); counter2++)
		{
			if(nodeStudent2->rank > nodeStudent3->rank)	//Swap nodes
			{
				nodeStudent2->link = nodeStudent3->link;
				nodeStudent3->link = nodeStudent2;
				nodeStudent1->link = nodeStudent3;

				nodeStudent1 = nodeStudent1->link;
				nodeStudent3 = nodeStudent2->link;
			}
			else
			{
				nodeStudent1 = nodeStudent2;
				nodeStudent2 = nodeStudent3;
				nodeStudent3 = nodeStudent3->link;
			}
		}
	}
}

void display()
{
	int opnDisp;
	clrscr();
	do
	{
		printf("\n1  DISPLAY SPECIFIC STUDENT INFORMATION.");
		printf("\n2  DISPLAY ALL STUDENT INFORMATION");
		printf("\n3  DISPLAY CENTER INFORMATION");
		printf("\n4  DISPLAY BRANCH INFORMATION");
		printf("\n0  Back to previous menu... ");
		scanf("%d", &opnDisp);

		switch(opnDisp)
		{
			case 1	: dispStudent();
				  break;
			case 2	: dispAllStud();
				  break;
			case 3	: dispCenter();
				  break;
			case 4	: dispBranch();
				  break;
			case 0	: clrscr();
		};
	} while(opnDisp != 0);
}

void dispStudent()
{
	int roll, counter;
	student nodeStudent;
	center nodeCenter;
	branch nodeBranch;

	printf("\nEnter roll no. of student to view details\t:\t");
	scanf("%d", &roll);

	for(nodeStudent = LLstudent; (nodeStudent->roll != roll) && nodeStudent; nodeStudent = nodeStudent->link);
	if(nodeStudent != NULL) {
	printf("\nName\t\t:\t%s", nodeStudent->name);
	printf("\nFather's Name\t:\t%s", nodeStudent->fatherName);
	printf("\nAddress\t\t:\t%s", nodeStudent->address);
	printf("\nE-mail\t\t:\t%s", nodeStudent->email);
	printf("\nCatagory\t:\t");
	if(nodeStudent->catagory == 0)
		printf("General");
	else if(nodeStudent->catagory == 1)
		printf("SC");
	else if(nodeStudent->catagory == 2)
		printf("ST");
	else if(nodeStudent->catagory == 3)
		printf("OBC");
	printf("\nCenter Choice\t:\t");
	for(counter = 0; counter<3; counter++)
	{
		if(nodeStudent->centerChoice[counter] != 0)
		{
			for(nodeCenter = LLcenter; nodeCenter->id != nodeStudent->centerChoice[counter]; nodeCenter = nodeCenter->link);
			printf("%s, ", nodeCenter->name);
		}
	}
	printf("\nMarks 10th/12th\t:\t%d/%d", nodeStudent->marks[0], nodeStudent->marks[1]);
	printf("\nRoll NO.\t:\t%d", nodeStudent->roll);
	if(nodeStudent->centerAlloted != 0)
	{	for(nodeCenter = LLcenter; nodeCenter->id != nodeStudent->centerAlloted; nodeCenter = nodeCenter->link);
		printf("\nCenter Alloted\t:\t%s", nodeCenter->name);
	}
	if(nodeStudent->rank != 0)
		printf("\nRank\t\t:\t%d", nodeStudent->rank);
	printf("\nBranch Choice\t:\t");
	for(counter = 0; counter < 3; counter++)
	{
		if(nodeStudent->branchChoice[counter] != 0)
		{
			for(nodeBranch = LLbranch; nodeBranch->id != nodeStudent->branchChoice[counter]; nodeBranch = nodeBranch->link);
			printf("%s, ", nodeBranch->name);
		}
	}
	if(nodeStudent->branchAlloted != 0)
	{
		for(nodeBranch = LLbranch; nodeBranch->id != nodeStudent->branchAlloted; nodeBranch = nodeBranch->link);
		printf("\nBranch Alloted\t:\t%s", nodeBranch->name);
	}
	}
	getch();
	clrscr();
}

void dispAllStud()
{
	student nodeStudent;
	center nodeCenter;
	branch nodeBranch;

	printf("\nROLL\tNAME\t\t\tRANK\tCENTER\tBRANCH\n");
	for(nodeStudent = LLstudent; nodeStudent; nodeStudent = nodeStudent->link)
	{
		printf("\n%d\t%s\t", nodeStudent->roll, nodeStudent->name);
		if(strlen(nodeStudent->name) < 10)
			printf("\t\t");
		else if(strlen(nodeStudent->name) < 16)
			printf("\t");
		if(nodeStudent->rank != 0)
			printf("%d", nodeStudent->rank);
		if(nodeStudent->centerAlloted != 0)
		{	for(nodeCenter = LLcenter; nodeCenter->id != nodeStudent->centerAlloted; nodeCenter = nodeCenter->link);
			printf("\t%s", nodeCenter->name);
		}
		if(nodeStudent->branchAlloted != 0)
		{
			for(nodeBranch = LLbranch; nodeBranch->id != nodeStudent->branchAlloted; nodeBranch = nodeBranch->link);
			printf("\t%s", nodeBranch->name);
		}
	}
	getch();
	clrscr();
}

void dispCenter()
{
	center nodeCenter;

	printf("\nID\tNAME\tCAPACITY\tOCCUPIED\n");
	for(nodeCenter = LLcenter; nodeCenter; nodeCenter = nodeCenter->link)
		printf("\n%d\t%s\t%d\t\t%d", nodeCenter->id, nodeCenter->name, nodeCenter->capacity, nodeCenter->occupied);
	getch();
	clrscr();
}

void dispBranch()
{
	branch nodeBranch;

	printf("\nID\tNAME\tCAPACITY\tOCCUPIED\n");
	for(nodeBranch = LLbranch; nodeBranch; nodeBranch = nodeBranch->link)
		printf("\n%d\t%s\t%d\t\t%d", nodeBranch->id, nodeBranch->name, nodeBranch->totalSeat, nodeBranch->totalSeat - (nodeBranch->reserveSeat[0] + nodeBranch->reserveSeat[1] + nodeBranch->reserveSeat[2] + nodeBranch->reserveSeat[3]));
	getch();
	clrscr();
}
