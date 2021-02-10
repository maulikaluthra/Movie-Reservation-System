#include<fstream.h>
#include<process.h>
#include<string.h>
#include<stdio.h>
#include<conio.h>

void admin();
void user();
void eibin();
void append();
void deleterec();
void show();
void book();
void search();
void seating(int n);
void dispseat();
void getseat(int nos);
void create();
int getpass(char p[]);


class seat
{public:
 int sno;
 char stat[5];
 seat()
 {strcpy(stat,"A");}
 };

class movie
{ public:
   char mname[10];
   char time[9];
   float price;
   char CR[6];
   char lang[8];
   char dur[8];
   char disc[10];

 movie()
 {  strcpy(disc,"disc15");  }

  void getdet()
  {   cout << "Enter the details as follows\n";
		cout << "Movie name: ";
		  gets(mname);
		cout << "Language: ";
		  gets(lang);
		cout << "Censor rating: ";
		  gets(CR);
		cout << "Price: ";
		  cin >> price;
		cout << "Duration: ";
		  gets(dur);
		cout << "Time: ";
		  gets(time);
  }

  void dispdet()
  { 	cout << mname <<'\t'<< CR <<'\t'<< lang <<'\t';
	cout << price <<'\t'<< time <<'\t'<< dur << '\n';
  }
};

void main()
{
cout<<"***************************************************\n";
cout<<"                     WELCOME                       \n";
cout<<"***************************************************\n";
cout<<"\nEnter 1 to login as Admin. \n";
cout<<"Enter 2 to continue as User. \n";
cout<<"\nYour choice : ";
int ch;
cin>>ch;
switch(ch)
  { case 1: admin();
            break;
    case 2: user();
	       break;
    default: cout<<"\nWRONG INPUT! \n";
  }
}

void admin()                 
{ cout<<"***************************************\n";
  cout<<"               ADMIN MODE              \n";
  cout<<"***************************************\n\n";
  char id[10]="admin101";
  char pass[10];
  puts(id);
  cout << "Enter the password : ";
	if (getpass(pass)==0)
		cout << "\nWrong password!\n";
  else
 {  int n;
    char ch;
    do
      {  cout<<endl;
	    cout << "\nEnter your choice: ";
	    cout << "\n1. Create File.";
	    cout << "\n2. Append File ";
	    cout << "\n3. Delete a movie ";
	    cout << "\n4. Exit ";
	    cout << "\nYour choice: ";
	    cin >> n;

	switch(n)
	  {case 1: { eibin();  //FxN to enter m into bin file
		        break; }
	   case 2: { append();
		        break; }
	   case 3: { deleterec();
		        break; }
	   case 4: { exit(0);
		        break; }
	   default : cout << "\n INVALID INPUT!!\n";
	  }

    show(); //fxn
    cout << "Do you wish to continue in Admin Mode ( Y/N              )?";
    cin >> ch;
    }   while (ch=='y'||ch=='Y');
  }
}

void eibin()
{ofstream f("movie.dat",ios::binary);
 movie m;
 char c;
 do
 { m.getdet();
   f.write((char*)&m, sizeof(m));
   cout<<"\nDo you want to add another movie (Y/N)? ";
   cin>>c;
  }  
 while(c=='y'||c=='Y');
 f.close();
}

void append()
{ movie M;
  char ch;
  ofstream file("movie.dat", ios::binary | ios::app);
  do {
   cout << "\nEnter the data to be appended \n";
   M.getdet();
   file.write((char*)&M,sizeof(M));
   cout << "\nDo you want to continue appending (Y/N)? : ";
   cin >> ch;  }
  while (ch=='y'||ch=='Y');
  file.close();
}

void deleterec()
{ movie m;
  char name[20];
  ifstream file("movie.dat", ios::binary|ios::beg);
  ofstream file1("temp.dat", ios::binary);
  cout << "\nEnter the name of the movie which is to be
             deleted : ";
  gets(name);
  file.read((char*)&m, sizeof(m));
  do {
	 if(strcmpi(name,m.mname)!=0)
	     file1.write((char*)&m,sizeof(m));
	 file.read((char*)&m, sizeof(m));
     } 
  while(!file.eof());
  file.close();
  file1.close();
  remove("movie.dat");
  rename("temp.dat","movie.dat");
}

int getpass( char p[])
{ char password[10]="12345";
  int i;
  for (i=0; i<strlen(password); i++)
	 { p[i]=getch();
	   cout << "*";
	 }
  p[i]='\0';
  if (strcmp(p,password)==0)
      return 1;
  else
      return 0;
}


void user()
{cout<<"****************************************************\n";
 cout<<"                      USER MODE                   \n";
cout<<"****************************************************\n";
 show();
 int c;
 char ch;
 do{
   cout << "\n1. Book tickets \n" << "2. Search \n" << "3.
              Exit \n";
   cin>>c;
   switch(c)
     {case 1 : { book();  break;   }
      case 2 : { search(); break;  }
      case 3 : { exit(0);  break;  }

      default:cout<<"\nINVALID INPUT! \n";
     }
   cout<<"\nDo you wish to continue in User Mode (Y/N)? : ";
   cin>>ch;
   } 
  while (ch=='Y'||ch=='y');
}

void book()
{char ch;
 do{
   int nosr;
   float totp=0;
   char promo[10];
   char movname[50];
   movie m;
   float pr=0;
   cout << "\nEnter the name of the movie:  ";
   gets(movname);
   cout << "\nEnter the number of seats required:  ";
   cin >> nosr;
   seating(nosr);

   ifstream file("movie.dat",ios::binary);
   file.read((char*)&m, sizeof(m));
   int f=0;
   do
      {if(strcmpi(m.mname,movname)==0)
	   {pr=m.price;
	    f++;
	    break; }
       else
	   file.read((char*)&m, sizeof(m));
      } while(!(file.eof())||f==0);

   file.close();
  if(f==0)
    { cout<<"\nMovie Not Found! \n";
    }
  else
    { char p;
      cout<<"\nDo you have a promo coupon? (Y/N) :";
      cin>>p;

      if (p=='y'||p=='Y')
	{cout<<"\nEnter Promo Code:  ";
	 gets(promo);
	 if(strcmp(promo,"disc15")==0)
	   {totp=nosr*pr*0.85;
	    cout<<"\nPromo Code Applied! \n";  }
	 else
	    {cout<<"\nInvalid coupon! \n";
	     totp=nosr*pr; }
	}
      else totp=nosr*pr;
      cout<<endl;
  cout<<"\nTicket Booked Successfully!\n";

  cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
cout<<"                      TICKET                     \n" ;
cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  m.dispdet();
  cout<<"\n\nNumber of seats booked: "<<nosr<<endl;
  cout<<"\nBilling Amount: "<<totp<<endl<<endl;
    }
  cout<<"\nDo you wish to book more tickets? (Y/N) :";
  cin>>ch;
 }while(ch=='y'||ch=='Y');
}

void search()
{ ifstream file("movie.dat", ios::binary|ios::beg);
  movie M;
  char name[25],ch;
  do{
   cout << "\nEnter the movie name you want to search for   ";
   gets(name);
   int f=0;
   file.read((char*)&M,sizeof(M));
    do {  if (strcmp(name,M.mname)==0)
	       { M.dispdet();
		     f++;}
	  file.read((char*)&M,sizeof(M));
       } 
    while (!file.eof());
    if(f==0)
       cout<<"\nMovie Not Found!\n";
    cout << "\nDo you want to search again (Y/N)? ";
    cin >> ch;
    file.close();
  } 
 while (ch=='Y'||ch=='y');
}

void show()
{ movie M;
  ifstream file("movie.dat", ios::binary);
  file.read((char*)&M,sizeof(M));
  cout << "Name" <<'\t'<<"Rating"<<' '<<"Language"<<' ';
  cout << "Price" <<'\t'<< "Time" <<'\t'<< "Duration" << '\n';
  do
  { M.dispdet();
    file.read((char*)&M,sizeof(M));
  }	while(!file.eof());
  file.close();
}

void seating(int n)
{ create();
  dispseat();
  getseat(n);
}

void create()
{ofstream f("Seat.dat",ios::binary );
  seat s;
  for (int i=1;i<=25;i++)
	{s.sno=i;
	 f.write((char*)&s,sizeof(s));
	}
f.close();
}

void dispseat()

{ ifstream f("Seat.dat",ios::binary);
  seat s;
  cout << "--------------------------------------------------------------------------\n";
  for (int i=1;i<=5;i++)
  {	for (int j=1;j<=5;j++)
	{	 f.read((char*)&s,sizeof(s));
		 cout << s.sno <<" - " << s.stat << "	 |    ";
	 }
	cout << "\n--------------------------------------------------------------------------";
	cout << endl    ;
	}
	cout << "A -> Available \t N -> Not Available \n";
  f.close();
}

void getseat(int nos)
{ int snum[10];
  seat s;
  for (int i=1; i<=nos; i++)
   {cout<<"Seat Number : ";
    cin >> snum[i];          //user[i]=seat no
    fstream f("seat.dat",ios::binary|ios::in|ios::out);
    f.read((char*)&s,sizeof(s));
    do{
	  if(snum[i]==s.sno)
	    if (strcmp(s.stat, "A")==0)
		  {  strcpy(s.stat,"N");
		     long int ptr = f.tellg();
		     f.seekp(ptr-sizeof(s));
		     f.write((char*)&s,sizeof(s));
		  }
	    else
	       cout << snum[i] << " is unavailable. Please choose another seat.";
      f.read((char*)&s,sizeof(s));
      } 
    while(!f.eof());
    f.close();
   } 
}
