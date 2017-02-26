#include <iostream.h>
#include <conio.h>
#include <string.h>
#include <fstream.h>
#include <process.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
//***************************************************************
//	CLASS NAME : menu
//	DETAILS    : IT CONTROLS OVER ALL FUNCTIONING OF PROJECT
//***************************************************************

class menu
{
public :
		void main_menu(void) ;
		char *sub_menu(void) ;
		void start(void) ;
private :
		void password();
		void admin_menu(void) ;
} ;


//**********************************************************
//	CLASS NAME : quiz
//	DETAILS    : IT CONTROLS OVER ALL THE FUNCTIONS
//                   RELATED TO QUIZ
//**********************************************************

class quiz
{
public :
		void play(char filename[13]) ;
		void add(char filename[13]) ;
		void deletion(char filename[13]) ;
		void modify(char filename[13]) ;
private :
		int autogen(char filename[13]);
		int retqno();
		void delete_record(char filename[13], int) ;
		void modify_record(char filename[13], int) ;
		void display_score(char name[20], int, int) ;
		int  recordno(char filename[13], int) ;
		int  record_count(char filename[13]) ;
		int  found_record(char filename[13], int) ;
		void display_record(char filename[13], int) ;
		int  ques_no ;
		char ques[60] ;
		char ans1[50] ;
		char ans2[50] ;
		char ans3[50] ;
		char sol ;
} ;
long si=sizeof(quiz);
//**********************************************************
//	CLASS NAME    : menu
//	FUNCTION NAME : start
//	DETAILS       : IT CREATES THE OPENING SCREEN
//**********************************************************
void menu::start()
{	cout<<"\nCOMPUTER QUIZ";
	cout<<"\nMADE BY:-";
	cout<<"\nDHRUV MONGIA";
	cout<<"\nSARTHAK BABBAR";
	cout<<"\nAKHIL SHARMA";
	getch();
	main_menu();
}
//**********************************************************
//	CLASS NAME    : menu
//	FUNCTION NAME : main_menu
//	DETAILS       : IT CREATES THE MAIN MENU TO CONTROL
//                   ALL THE FUNCTIONS
//**********************************************************

void menu::main_menu()
{       char filename[13]; quiz q; int option; char choice;
	clrscr();
	do
	{
		cout<<"\nMAIN MENU";
		cout<<"\n1.ADMIN";
		cout<<"\n2.PLAY";
		cout<<"\n3.QUIT";
		cout<<"\nEnter your choice: ";
		cin>>option;
		switch(option)
		{	case 1:  password(); admin_menu();               break;
			case 2:	 do{   strcpy(filename,sub_menu());
					q.play(filename);
				    } while(strcmp(filename,"null")==0); break;
			case 3:  exit(0);  break;
			default: cout<<"\nWrong choice! Please try again!";
				 getch();
				 main_menu();

		}
		cout<<"\nDo you want to continue(y/n)? ";
		cin>>choice;
	}while(choice=='y'||choice=='Y');
}
//*****************************************************
//	CLASS NAME    : menu
//	FUNCTION NAME : password
//	DETAILS       : IT CHECKS WHETHER THE USER HAS
//                      AUTHORIZED ACCESS OR NOT
//**********************************************************
void menu::password()
{	cout<<"\nEnter the password";
	char pass[3];
	for(int i=0; i<3; i++)
	{	pass[i]=getch();
		cout<<"*";
	}
	pass[i]='\0';
	if(strcmp(pass,"fas"))
	{	cout<<"\nHurray! You have the authorized access";
		return;
	}
	else
		cout<<"\nSorry! You donot have the authorized access";
	getch();
	exit(0);
}

//**********************************************************
//	CLASS NAME    : menu
//	FUNCTION NAME : sub_menu
//	DETAILS       : IT CREATES THE SUB MAIN MENU AND
//                      RETURN FILE NAME
//**********************************************************

char *menu::sub_menu(void)
{       clrscr();
	int option; char wrong[13];
	cout<<"\nSUB_MENU";
	cout<<"\n1.Computers";
	cout<<"\n2.Mathematics";
	cout<<"\n3.Science";
	cout<<"\n4.General";
	cout<<"\n5.Return";
	cout<<"\nEnter your choice: ";
	cin>>option;
	switch(option)
	{	case 1: return ("computer.dat"); break;
		case 2: return ("maths.dat"); break;
		case 3: return ("science.dat"); break;
		case 4: return ("general.dat"); break;
		case 5: return ("null"); break;
		default: cout<<"\nWrong choice! Please try again!";
			 getch();
			 strcpy(wrong,sub_menu());
	}
	return("null");

}

//**********************************************************
//	CLASS NAME    : menu
//	FUNCTION NAME : admin_menu
//	DETAILS       : IT CREATES THE ADMIN MAIN MENU
//			FOR ADDING,DELETTING AND MODIFYING
//			QUESTIONS
//**********************************************************
void menu::admin_menu()
{       clrscr(); quiz q; char filename[13];
	int option;
	cout<<"\nADMIN-MENU";
	cout<<"\n1.DELETE";
	cout<<"\n2.MODIFY";
	cout<<"\n3.ADD";
	cout<<"\n4.RETURN";
	cout<<"\nEnter your choice";
	cin>>option;
	switch(option)
	{	case 1: q.deletion(sub_menu())  ; break;
		case 2: q.modify(sub_menu())	; break;
		case 3: q.add(sub_menu());      ; break;
		case 4: return;
		default: cout<<"\nWrong choice! Please try again!";
			 getch();
			 admin_menu();
	}
	return;

}
int quiz::retqno()
{	return ques_no;
}
int quiz::autogen(char filename[13])
{       int r;
	fstream file;
	file.open(filename,ios::in|ios::out|ios::binary);
	if(file.fail())
	{	cerr<<"\nThe file cannot be opened";
		getch(); exit(1);
	}
	file.seekg(0,ios::end);
	long n=file.tellg();
	if(n==0)
		r=1;
	else
	{       file.seekg(-si,ios::end);
		file.read((char*)this,si);
		r=retqno();
		r++;
	}
	file.close();
	return r;
}
//**********************************************************
//	CLASS NAME    : quiz
//	FUNCTION NAME : record_count
//	DETAILS       : IT RETURNS THE NO. OF RECORD IN THE
//                   GIVEN FILE
//**********************************************************

int  quiz :: record_count(char filename[13])
{
   fstream file ;
   if(file.fail())
   {	cerr<<"\nThe file cannot be opened";
	getch(); exit(1);
   }
   file.open(filename, ios::in|ios::binary) ;
   file.seekg(0,ios::end) ;
   int t=file.tellg();
   long n=t/si;
   file.close();
   return n;
}
void quiz :: add(char filename[13])
{

   int valid ;
   char ch ;
   do
   {
	ques_no=autogen(filename) ;
	clrscr() ;
	cout <<"\nquestion # " <<ques_no ;
	cout <<"\nquestion : " ;
	do
	{
		valid = 1 ;
		gets(ques) ;
		if (strlen(ques) > 159 || strlen(ques) == 0)
		{
			valid = 0 ;
			cout <<"\nLENGTH SHOULD NOT BE BLANK OR GREATER THAN 159" ;
			cout<<"\nRetype the question please! "<<endl;

		}
	} while ( !valid ) ;
	cout <<"\nanswer 1 : " ;
	do
	{

		valid = 1;
		gets(ans1) ;
		if (strlen(ans1) > 49)
		{
			valid = 0 ;
			cout <<"\nLENGTH SHOULD NOT GREATER THAN 49" ;
			cout<<"\nRetype the answer please! "<<endl;
		}
	} while ( !valid ) ;
	cout <<"\nanswer 2 : " ;
	do
	{

		valid = 1;
		gets(ans2) ;
		if (strlen(ans2) > 49)
		{
			valid = 0 ;
			cout <<"\nLENGTH SHOULD NOT GREATER THAN 49" ;
			cout<<"\nRetype the answer please! "<<endl;
		}
	} while ( !valid ) ;
	cout <<"\nanswer 3 : " ;
	do
	{

		valid = 1;
		gets(ans3) ;
		if (strlen(ans3) > 49)
		{
			valid = 0 ;
			cout <<"\nLENGTH SHOULD NOT GREATER THAN 49" ;
			cout<<"\nRetype the answer please! "<<endl;
		}
	} while ( !valid ) ;
	cout <<"\nsolution : " ;
	do
	{
		valid = 1 ;
		sol = getche() ;
		if (sol != '1' && sol != '2' && sol != '3')
		{	valid = 0 ;
			cout<<"\nPlease enter the solution again! "<<endl;

		}
	} while ( !valid ) ;



	cout <<"\nDo you want to save the record (y/n) : " ;
	do
	{       valid=1;
		ch = getche() ;
		ch = toupper(ch) ;
		if (ch != 'Y' && ch != 'N')
		{	valid = 0 ;
			cout<<"\nPlease enter your choice again! "<<endl;
		}
	} while ( !valid ) ;
	if (ch == 'Y')
	{

		fstream file ;
		file.open(filename, ios::app|ios::binary ) ;
		if(file.fail())
		{	cerr<<"\nThe file cannot be opened";
			getch(); exit(1);
		}
		file.write((char *) this, si) ;
		file.close() ;
	}

	cout <<"\nDo you want to add more questions (y/n) : " ;
	do
	{

		valid = 1 ;
		ch = getche() ;
		ch = toupper(ch) ;

		if (ch != 'Y' && ch != 'N')
		{	valid = 0 ;
			cout<<"\nPlease enter your choice again!"<<endl;
		}

	} while ( !valid ) ;
   } while (ch == 'Y') ;
}
void  quiz :: delete_record(char filename[13] , int t_ques_no)
{	fstream file;
	file.open(filename,ios::in|ios::binary);
	if(file.fail())
	{	cout<<"\nThe file cannot be opened";
		getch(); exit(1);
	}
	fstream temp;
	temp.open("temp.dat",ios::out|ios::binary);
	if(temp.fail())
	{	cout<<"\nThe file cannot be opened";
		getch(); exit(1);
	}
	while(file.read((char*)this,si))
	{	if(ques_no != t_ques_no)
			temp.write( (char*)this , si );
	}
	file.close(); temp.close();
	remove (filename);
	rename("temp.dat",filename);
}
//**********************************************************
//	CLASS NAME    : quiz
//	FUNCTION NAME : display_record
//	DETAILS       : IT DISPLAY THE RECORD FOR THE GIVEN
//                   QUESTION NO. FROM THE GIVEN FILE
//**********************************************************

void quiz :: display_record(char filename[13], int t_ques_no)
{
   fstream file ;
   file.open(filename, ios::in|ios::binary) ;
   if(file.fail())
   {	cerr<<"\nThe file cannot be opened";
	getch(); exit(1);
   }
   file.seekg(0,ios::beg) ;
   while (file.read((char *) this, si))
   {
	if (t_ques_no == ques_no)
	{
		cout <<"\nquestion # " <<t_ques_no ;
		cout <<"\nquestion : " <<ques ;
		cout <<"\nanswer 1 : " <<ans1 ;
		cout <<"\nanswer 2 : " <<ans2 ;
		cout <<"\nanswer 3 : " <<ans3 ;
		break ;
	}
   }
   file.close() ;
}
//**********************************************************
//	CLASS NAME    : quiz
//	FUNCTION NAME : found_record
//	DETAILS       : IT SEARCH THE GIVEN RECORDS IN THE
//                   GIVEN FILE AND RETURN 0 IF NOT FOUND
//**********************************************************

int  quiz :: found_record(char filename[13], int t_ques_no)
{
   fstream file ;
   file.open(filename, ios::in|ios::binary) ;
   if(file.fail())
   {	cerr<<"\nThe file cannot be opened";
	getch(); exit(1);
   }
   file.seekg(0,ios::beg) ;
   int found=0 ;
   while (file.read((char *) this, si))
   {
	if (t_ques_no == ques_no)
	{
		found++ ;
		break ;
	}
   }
   file.close() ;
   return found ;
}
//**********************************************************
//	CLASS NAME    : quiz
//	FUNCTION NAME : deletion
//	DETAILS       : IT GIVE THE QUESTION NO. TO DELETE
//                   RECORD FROM THE GIVEN FILE
//**********************************************************

void quiz :: deletion(char filename[13])
{	int t_ques_no=0; char choice;
	cout<<"\nEnter the question number to be deleted: ";
	cin>>t_ques_no;
	if (t_ques_no == '0')
	return ;
	if (!found_record(filename,t_ques_no))
	{
		cout <<"\nQuestion not found" ;
		cout <<"\nPress any key to continue..." ;
		getch() ;
		return ;
	}
	clrscr();
	display_record(filename,t_ques_no) ;
	cout<<"\nDo you want to delete this record(y/n)";
	cin>>choice;
	choice=toupper(choice);
	if(choice=='Y')
	{	cout<<"\nWait.....";
		delete_record(filename,t_ques_no);
		cout<<"\nThis record has been deleted";
		cout<<"\nPress any key to continue...";
		getch();
	}
}
//**********************************************************
//	CLASS NAME    : quiz
//	FUNCTION NAME : modify_record
//	DETAILS       : IT MODIFY THE RECORD FOR THE GIVEN
//                      QUESTION NO. FROM THE GIVEN FILE
//**********************************************************


void quiz :: modify_record(char filename[13], int t_ques_no)
{
   int valid, modified=0 ;
   char ch ;
   cout <<"\nQUESTION # " <<t_ques_no ;
   cout <<"\nQUESTION : " ;
   cout <<"Change (y/n)  " ;
   do
   {
	valid = 1 ;
	ch = getche() ;
	ch = toupper(ch) ;
	if (ch != 'Y' && ch != 'N')
	{
		valid = 0 ;
	}
   } while (!valid) ;

   valid = 0 ;
   while (!valid && ch == 'Y')
   {
	modified = 1 ;
	valid = 1 ;
	gets(ques) ;
	if (strlen(ques) >159 || strlen(ques) == 0)
	{
		valid = 0 ;
		cout <<"\nLENGTH SHOULD NOT BLANK OR GREATER THAN 159" ;
		cout <<"\nPress any key to continue..." ;
		getch() ;

	}
   }
   cout <<"\nANSWER 1 : " ;
   cout <<"Change (y/n)  " ;
   do
   {

	valid = 1 ;
	ch = getche() ;
	ch = toupper(ch) ;
	if (ch != 'Y' && ch != 'N')
	{
		valid = 0 ;
	}
   } while (!valid) ;
   valid = 0 ;
   while (!valid && ch == 'Y')
   {
	modified = 1 ;
	valid = 1 ;
	gets(ans1) ;
	if (strlen(ans1) > 49)
	{
		valid = 0 ;
		cout <<"\nLENGTH SHOULD NOT GREATER THAN 49" ;
		cout <<"\nPress any key to continue..." ;
		getch() ;
	}
   }
   cout <<"\nANSWER 2 : " ;
   cout <<"Change (y/n)  " ;
   do
   {

	valid = 1 ;
	ch = getche() ;
	ch = toupper(ch) ;
	if (ch != 'Y' && ch != 'N')
	{
		valid = 0 ;
	}
   } while (!valid) ;
   valid = 0 ;
   while (!valid && ch == 'Y')
   {
	modified = 1 ;
	valid = 1 ;
	gets(ans2) ;
	if (strlen(ans2) > 49)
	{
		valid = 0 ;
		cout <<"\nLENGTH SHOULD NOT GREATER THAN 49" ;
		cout <<"\nPress any key to continue..." ;
		getch() ;
	}
   }
   cout <<"\nANSWER 3 : " ;
   cout <<"Change (y/n)  " ;
   do
   {

	valid = 1 ;
	ch = getche() ;
	ch = toupper(ch) ;
	if (ch != 'Y' && ch != 'N')
	{
		valid = 0 ;
	}
   } while (!valid) ;
   valid = 0 ;
   while (!valid && ch == 'Y')
   {
	modified = 1 ;
	valid = 1 ;
	gets(ans3) ;
	if (strlen(ans3) > 49)
	{
		valid = 0 ;
		cout <<"\nLENGTH SHOULD NOT GREATER THAN 49" ;
		cout <<"\nPress any key to continue..." ;
		getch() ;
	}
   }

   if (!modified)
	return ;
   cout <<"\nSOLUTION : " ;
   do
   {

	valid = 1 ;
	sol = getche() ;
	if (sol != '1' && sol != '2' && sol != '3')
	{
		valid = 0 ;
	}
   } while (!valid) ;
   cout <<"\nDo you want to save the record (y/n)  : " ;
   do
   {
	valid = 1 ;
	ch = getche() ;
	ch = toupper(ch) ;
	if (ch != 'Y' && ch != 'N')

		valid = 0 ;
   } while ( !valid ) ;
   if (ch == 'N')
	return ;
   fstream file ;
   file.open(filename, ios::out | ios::ate|ios::binary) ;
   if(file.fail())
   {	cerr<<"\nThe file cannot be opened";
	getch(); exit(1);
   }
   int recno ;
   recno = t_ques_no ;
   int location ;
   location = (recno-1) * si ;
   file.seekp(location) ;
   file.write((char *) this, si) ;
   file.close() ;
   clrscr() ;
   cout <<"\nRecord Modified" ;
   cout <<"\nPress any key to continue..." ;
   getch() ;
}


//**********************************************************
//	CLASS NAME    : quiz
//	FUNCTION NAME : modify
//	DETAILS       : IT GIVE THE QUESTION NO. TO MODIFY
//                      RECORD FROM THE GIVEN FILE
//**********************************************************


void quiz :: modify(char filename[13])
{

   clrscr() ;
   int valid ;
   int t_ques_no=0, t;
   char ch ;
   cout <<"\nEnter question no. to be modify  : " ;
   do
   {
	cin>>t_ques_no ;
   } while (t_ques_no==0);
   if (!found_record(filename,t_ques_no))
   {
	cout <<"\nquestion not found" ;
	cout <<"\nPress any key to continue..." ;
	getch() ;
	return ;
   }
   clrscr() ;
   display_record(filename,t_ques_no) ;
   cout <<"\nDo you want to modify this Record (y/n) : " ;
   do
   {
	valid = 1 ;
	ch = getche() ;
	ch = toupper(ch) ;
	if (ch != 'Y' && ch != 'N')
		valid = 0 ;
   } while (!valid ) ;
   if (ch == 'N')
	return ;
   modify_record(filename,t_ques_no) ;
}
//**********************************************************
//	CLASS NAME    : quiz
//	FUNCTION NAME : display_score
//	DETAILS       : IT DISPLAY THE SCORE FOR THE GIVEN
//                      PLAYER'S NAME
//**********************************************************


void quiz :: display_score(char name[20], int played, int correct)
{
   clrscr() ;

   cout<<"\nS C O R E   B O A R D";
   cout <<"\nPlayer's Name : " <<name ;
   cout <<"\nquestions Attempted : " <<played ;
   cout <<"\nCorrect answer      : " <<correct ;
   cout <<"\nWrong answer        : " <<played-correct ;
   int score ;
   score = correct * 10 ;
   cout <<"\nScore  : " <<score ;
   int tplayed ;
   tplayed = played * 10 ;
   float percentage ;
   percentage = ((score*100)/tplayed) ;

   cout <<"\nPercentage : " <<percentage ;
   getch() ;
}


//**********************************************************
//	CLASS NAME    : quiz
//	FUNCTION NAME : play
//	DETAILS       : IT CREATES SCREEN FOR PLAYING QUIZ
//                      TO THE PLAYER FOR THE GIVEN FILE NAME
//                      AND KEEP SCORE.
//**********************************************************


void quiz :: play(char filename[13])
{
   clrscr() ;
   int valid ;
   char name[20] ;
   cout <<"\nEnter your name : " ;
   do
   {
	valid = 1 ;
	gets(name) ;
	if (name[0] == '0')
		return ;
	if (strlen(name) > 18)
	{
		valid = 0 ;
		cout <<"\nLENGTH SHOULD NOT GREATER THAN 18" ;
		cout <<"\nPress any key to continue..." ;
		getch() ;
	}
   } while ( !valid ) ;
   char t_sol, ch ;
   int  correct=0, played=0 ;
   fstream file ;
   file.open(filename,ios::in|ios::binary) ;
   if(file.fail())
   {	cerr<<"\nThe file cannot be opened";
	getch(); exit(1);
   }
   file.seekg(0,ios::beg) ;
   while (file.read((char *) this, si))
   {
	clrscr() ;
	cout <<"\nSCORE:" <<correct*10 ;
	valid = 1 ;

	cout <<"\nquestion # " <<ques_no ;

	cout <<"\nquestion : " <<ques ;

	cout <<"\nanswer 1 : " <<ans1 ;

	cout <<"\nanswer 2 : " <<ans2 ;

	cout <<"\nanswer 3 : " <<ans3 ;

	cout <<"\nEnter correct solution : " ;

	do
	{       valid=1;
		t_sol = getche() ;
		if (t_sol == 27)
		{
			if (played)
				display_score(name,played,correct) ;
			return ;
		}
		if (t_sol != '1' && t_sol != '2' && t_sol != '3')

			valid = 0 ;


	} while (!valid) ;
	played++ ;
	if (t_sol != sol)
	{

		cout <<"\nwrong answer" ;

		cout <<"\nCorrect answer : " <<sol ;
		getch();
	}
	else
	{
		correct++ ;
		cout <<"\nGOOD ! CORRECT ANSWER" ;

		cout <<"\nSCORE:" <<correct*10 ;

		ch = getch() ;
	}
	if (ch == 27)
	{
		display_score(name,played,correct) ;
		return ;
	}
   }

   cout <<"\nNo more questions available" ;
   getch() ;
   if (!played)
	return ;
   display_score(name,played,correct) ;
}


//**********************************************************
//	FUNCTION NAME : main
//	DETAILS       : IT CALLS THE START FUNCTION AND
//                   MENU FUNCTION.
//**********************************************************

void main()
{	menu m;
	m.start();
}





