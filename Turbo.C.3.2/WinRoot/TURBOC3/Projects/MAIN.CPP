#include<stdlib.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<fstream.h>
#include<string.h>
#include<dos.h>
#include<alloc.h>
#include<time.h>
#include<iomanip.h>
#include<graphics.h>
int flag=0;

//***************************** TIME FUNCTION *********************************
int time()
{//**************************declaring argument of time()**************************
time_t my_time=time(NULL);

//************************ctime used to give current time**************************
printf("%s",ctime(&my_time));
return 0;
}
//************************function to display ending*************************
void ending()
{  clrscr();
  int d=0,m;
  int x,y,i;
  initgraph(&d,&m,"c:\\turboc3\\bgi");
  x=getmaxx()/2;
  y=getmaxy()/2;
  for(i=40;i<200;i++)
   { delay(50);
     setcolor(i/10);
     arc(x,y,0,180,i-10);
   }
  cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"<<setw(45)<<" THANK YOU ";
  delay(2000);
  getch();
  exit(0);
}




//********************CLASS USED IN PROJECT*************************************

class product
{
int pno;
char name[50];
float price,qty,tax,dis;
public:

//**************************function for creating product**************************
void create_product()
{
 cout<<"\t\t\t\t";
cout<<"\n\t\t\t";
time();

cout<<"\nPlease Enter The Product No. of The Product "<<endl;
cin>>pno;
cout<<"\nPlease Enter The Name of The Product "<<endl;
gets(name);
cout<<"\nPlease Enter The Price of The Product "<<endl;
cin>>price;
cout<<"\nPlease Enter The Discount (%) "<<endl;
cin>>dis;
}

//**************************function for showing details of product*****************
void show_product()
{
 cout<<"\t\t\t\t";
cout<<"\n\t\t\t";
time();

cout<<"\nThe Product No. of The Product : "<<pno;
cout<<"\nThe Name of The Product : ";
puts(name);
cout<<"\nThe Price of The Product :\t "<<price;
cout<<"\nDiscount : "<<dis;
}

//**************************function returning product number**********************
int retpno()
{return pno;}

//**************************function returning  price of product*********************
float retprice()
{return price;}

//****************************function returning  name of product*******************
char* retname()
{return name;}

//*****************************function returning discount************************
int retdis()
{return dis;}

};

//*********************************class ends here*******************************



//****************global declaration for stream object, object************************

fstream fp;
product pr;


//**************************function to write in file*******************************
void write_product()
{
textcolor(CYAN);
textbackground(BLACK);
fp.open("Shop.dat",ios::out|ios::app);
pr.create_product();
fp.write((char*)&pr,sizeof(product));
fp.close();
cout<<"\n\nThe Product Has Been Created ";

textcolor(CYAN);
textbackground(BLACK);
getch();
}


//**********************function to read all records from file************************
void display_all()
{
clrscr();
cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
fp.open("Shop.dat",ios::in);
while(fp.read((char*)&pr,sizeof(product)))
{
textbackground(WHITE);
pr.show_product();
cout<<"\n\n====================================\n";
textbackground(WHITE);
getch();
}
textbackground(WHITE);
fp.close();
getch();
}
//**********************function to read specific record from file********************
void display_sp(int n)
{clrscr();
 cout<<"\t\t\t\t";
cout<<"\n\t\t\t";
time();

int flag=0;
fp.open("Shop.dat",ios::in);
while(fp.read((char*)&pr,sizeof(product)))
{
if(pr.retpno()==n)
{
clrscr();
pr.show_product();
flag=1;
}
}
fp.close();
if(flag==0)
cout<<"\n\nrecord not exist";
getch();
}


//************************function to modify record of file************************
void modify_product()
{
int no,found=0;
clrscr();

 cout<<"\t\t\t\t";
cout<<"\n\t\t\t";
time();

cout<<"\n\n\tTo Modify ";
cout<<"\n\n\tPlease Enter The Product No. of The Product";
cin>>no;

textcolor(CYAN);
textbackground(BLACK);
fp.open("Shop.dat",ios::in|ios::out);
while(fp.read((char*)&pr,sizeof(product)) && found==0)
{
if(pr.retpno()==no)
{
pr.show_product();
cout<<"\nPlease Enter The New Details of Product"<<endl;
pr.create_product();
int pos=-1*sizeof(pr);
fp.seekp(pos,ios::cur);
fp.write((char*)&pr,sizeof(product));
cout<<"\n\n\t Record Updated";
found=1;
}
}
fp.close();
if(found==0)
cout<<"\n\n Record Not Found ";

textcolor(CYAN);
textbackground(BLACK);
getch();
}


//************************function to delete record of file************************
void delete_product()
{
int no;
clrscr();
 cout<<"\t\t\t\t";
cout<<"\n\t\t\t";
time();

cout<<"\n\n\n\tDelete Record";
cout<<"\n\nPlease Enter The product no. of The Product You Want To Delete";
cin>>no;
fp.open("Shop.dat",ios::in|ios::out);
fstream fp2;
fp2.open("Temp.dat",ios::out);
fp.seekg(0,ios::beg);
while(fp.read((char*)&pr,sizeof(product)))
{
if(pr.retpno()!=no)
{
fp2.write((char*)&pr,sizeof(product));
}
}
fp2.close();
fp.close();
remove("Shop.dat");
rename("Temp.dat","Shop.dat");
cout<<"\n\n\tRecord Deleted ..";
getch();
}


//******************function to display all products price list************************
void menu()
{
clrscr();

 cout<<"\t\t\t\t";
cout<<"\n\t\t\t";
time();

fp.open("Shop.dat",ios::in);
if(!fp)
{
cout<<"ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create File";
cout<<"\n\n\n Program is closing ....";
getch();
exit(0);
}

cout<<"\n\n\t\tProduct MENU\n\n";
cout<<"====================================================\n";
cout<<"P.NO.\t\tNAME\t\t\tPRICE\n";
cout<<"====================================================\n";

while(fp.read((char*)&pr,sizeof(product)))
{
cout<<pr.retpno()<<"\t\t"<<pr.retname()<<"\t\t"<<pr.retprice()<<endl;
}
fp.close();
}


//************************function for payment of employee************************
void salary_cal()
{char post;
  int hour_sal;
float days,hours,overtime,salary;

clrscr();
cout<<"\t\t\t\t";
cout<<"\n\t\t\t";
time();

cout<<"\n\nWelcome to  the automated employee salary system\n";
delay(1000);

char *ptr2;
	 ptr2= (char *) calloc(10, sizeof(char));

	 cout<<"Enter password"<<endl;
	 cin>>ptr2;
	 delay(1000);
	 clrscr();
 cout<<"\t\t\t\t";
cout<<"\n\t\t\t";
time();

cout<<"\nVERIFYING ";
 for(int f=0;f<6;f++)
	 {cout<<".";
	  delay(500);
	 }
	if(strcmp("pay",ptr2)==0)
	{
	 cout<<"\nAccepted"<<endl;
	clrscr();
cout<<"\t\t\t\t";

time();
cout<<"enter post of employee\n";
cout<<"A.Manager\tB.Cashier\tC.Customer service\tD.Security Guard\n";
cin>>post;
switch(post)
{case 'A':hour_sal=600;
	 break;
case 'B':hour_sal=500;
	 break;
case 'C':hour_sal=400;
	 break;
case 'D':hour_sal=300;
	 break;
default:cout<<"invalid option\n";
	delay(1000);
	goto end;

}
cout<<"enter no of hours worked in a day\n";
cin>>hours;
cout<<"enter no of days worked\n";
cin>>days;
cout<<"enter total no of hours of overtime \n";
cin>>overtime;
salary=((overtime*1.5)+(hours*days))*hour_sal;
cout<<"salary is "<<salary<<endl;
cout<<"\nSalary transferred to employee bank account";
delay(3000);

end:
}
 else
{	  cout<<"Not Accepted"<<endl<<"User password incorrect"<<endl;
	 getch() ;
}
}
//********function to place order and generating bill for Products***********************
void place_order()
{textbackground(WHITE);
cout<<"\t\t\t\t";
cout<<"\n\t\t\t";
time();

textbackground(WHITE);
int order_arr[50],quan[50],c=0;
float amt,damt,total=0;
char ch='Y';
menu();
cout<<"\n============================";
cout<<"\n PLACE YOUR ORDER";
cout<<"\n============================\n";
textbackground(WHITE);
do{
textbackground(WHITE);
cout<<"\n\nEnter The Product No. Of The Product : ";
textbackground(WHITE);
cin>>order_arr[c];
textbackground(WHITE);
cout<<"\nQuantity in number : ";
textbackground(WHITE);
cin>>quan[c];
c++;
cout<<"\nDo You Want To Order Another Product ? (y/n)";
textbackground(WHITE);
cin>>ch;
textbackground(WHITE);
}while(ch=='y' ||ch=='Y');
cout<<"\n\nThank You For Placing The Order";getch();clrscr();
cout<<"\n \n********************************INVOICE************************\n";
cout<<"\nPr No.\tPr Name\tQuantity \tPrice \tAmount \tAmount after discount\n";
textbackground(WHITE);
for(int x=0;x<=c;x++)
{textbackground(WHITE);
fp.open("Shop.dat",ios::in);
fp.read((char*)&pr,sizeof(product));
while(!fp.eof())
{textbackground(WHITE);
if(pr.retpno()==order_arr[x])
{textbackground(WHITE);
amt=pr.retprice()*quan[x];
if(flag==1)
{damt=amt*0.5;
}
else
{textbackground(WHITE);
damt=amt-(amt*pr.retdis()/100);
}
textbackground(WHITE);
cout<<"\n"<<order_arr[x]<<"\t"<<pr.retname()
<<"\t"<<quan[x]<<"\t"<<pr.retprice()<<"\t"<<amt<<"\t\t"<<damt;
total+=damt;
}
fp.read((char*)&pr,sizeof(product));
}

fp.close();
}
textbackground(WHITE);
cout<<"\n\n\t\t\t\t\tTOTAL = "<<total<<endl;
textbackground(WHITE);

//***************************loyalty points calculation*****************************


float amount;
int points;

points=total/40;
 cout<<"Points earned:"<<points<<"\n\n";


//*******************************lottery checking*******************************
int ln=points*total+(random(100));
int i,a[10];
int lott;

for(i=0;i<10;i++)
{ a[i]=random(10000);
	if(ln==a[i])
	{flag=1;}
	else
	{flag=0;}
}
if(ln>0)
{textbackground(WHITE);
cout<<"your lottery number :"<<ln<<"\n";
}
else
{textbackground(WHITE);
cout<<"your lottery number :"<<ln*-1<<"\n";
}
if (flag==1)
{cout<<"lottery won,u get 50% discount\n";
}
else
{ cout<<"no lottery for u ,better luck next time\n";
 cout<<"lottery numbers were:\n";
lott=random(10000);
textbackground(WHITE);
for(i=0; i<10; i++)
{printf("%d\n",rand() % lott);
textbackground(WHITE);
}
}
textbackground(WHITE);
delay(3000);
clrscr();
textbackground(WHITE);

//*************************note calculation***********************************

cout<<"TOTAL AMOUNT EARNED WITH THIS TRANSACTION OF  "<<total<<endl;
int note[20];
note[0]=total/2000;
textbackground(WHITE);
cout<<"\n2000 rupee note=";
if(note[0]>=0)
{
cout<<note[0];
}
note[1]=total-(note[0]*2000);
note[2]=note[1]/1000;
cout<<"\n1000 rupee note=";
if(note[2]>=0)
{
cout<<note[2];
}
note[3]=note[1]-(note[2]*1000);
note[4]=note[3]/500;
cout<<"\n 500 rupee note=";
if(note[4]>=0)
{
cout<<note[4];
}
note[5]=note[3]-(note[4]*500);
note[6]=note[5]/200;
cout<<"\n 200 rupee note=";
if(note[6]>=0)
{
cout<<note[6];
}
note[7]=note[5]-(note[6]*200);
note[8]=note[7]/100;
cout<<"\n 100 rupee note=";
if(note[8]>=0)
{
cout<<note[8];
}
note[9]=note[7]-(note[8]*100);
textbackground(WHITE);
note[10]=note[9]/50;
cout<<"\n  50 rupee note=";
if(note[10]>=0)
{
cout<<note[10];
}

note[11]=note[9]-(note[10]*50);
note[12]=note[11]/20;
cout<<"\n  20 rupee note=";
if(note[12]>=0)
{
cout<<note[12];
}

note[13]=note[11]-(note[12]*20);
note[14]=note[13]/10;
cout<<"\n  10 rupee note=";
if(note[14]>=0)
{
cout<<note[14];
}

note[15]=note[13]-(note[14]*10);
note[16]=note[15]/5;
textbackground(WHITE);
cout<<"\n   5 rupee note=";
if(note[16]>=0)
{
cout<<note[16];
}


getch();
}



//******************************INTRODUCTION FUNCTION****************************
void intro()
{
clrscr();
cout<<"\t\t\t\t";
cout<<"\n\t\t\t";
time();
cout<<"\n\n\n\t\t\tSUPER MARKET MANAGEMENT SYSTEM\n\n\n";
delay(1000);
cout<<"\n\n\n\tMADE BY : SHIVAM BHATT";
delay(1000);
cout<<"\n\t\n Press ENTER to continue";
delay(3000);
clrscr();
cout<<"\t\t\t\t";
cout<<"\n\t\t\t";
time();
delay(2000);
getch();

}


//*************************ADMINSTRATOR MENU FUNCTION***********************
void admin_menu()
{
   clrscr();
   cout<<"\t\t\t\t";
cout<<"\n\t\t\t";
time();

	 int l;
	 char *ptr1;
	 ptr1= (char *) calloc(10, sizeof(char));

	 cout<<"Enter password"<<endl;
	 cin>>ptr1;
	 delay(1000);
	 clrscr();
 cout<<"\t\t\t\t";
cout<<"\n\t\t\t";
time();

cout<<"\nVERIFYING ";
 for(int f=0;f<6;f++)
	 {cout<<".";
	  delay(500);
	 }
	if(strcmp("stark",ptr1)==0)
	{
	 cout<<"\nAccepted"<<endl;
	 textcolor(WHITE);
	textbackground(RED);
clrscr();
cout<<"\t\t\t\t";
cout<<"\n\t\t\t";
time();
char ch2;
cout<<"\n\n\n\tADMIN MENU";
cout<<"\n\n\t1.CREATE PRODUCT";
cout<<"\n\n\t2.DISPLAY ALL PRODUCTS";
cout<<"\n\n\t3.QUERY ";
cout<<"\n\n\t4.MODIFY PRODUCT";
cout<<"\n\n\t5.DELETE PRODUCT";
cout<<"\n\n\t6.VIEW PRODUCT MENU";
cout<<"\n\n\t7.EMPLOYEE SALARY";
cout<<"\n\n\t8.BACK TO MAIN MENU";
cout<<"\n\n\tPlease Enter Your Choice (1-8) ";
ch2=getche();
textcolor(CYAN);
textbackground(BLACK);
switch(ch2)

{
case '1': clrscr();

write_product();
break;
case '2': display_all();break;
case '3':int num;
cout<<"Hello ,We are at your service\n";
clrscr();
cout<<"\n\n\tFor Any Queries \n";
cout<<"Please Enter The Product No. ";
cin>>num;
display_sp(num);
break;
case '4': modify_product();break;
case '5': delete_product();break;
case '6': menu();
getch();break;
case '7': salary_cal();break;
case '8': break;
default:cout<<"\a";admin_menu();
}
} else
	  cout<<"Not Accepted"<<endl<<"User password incorrect"<<endl;
	 getch() ;

}
//******************THE MAIN FUNCTION OF PROGRAM*****************************
void main()
{ char ch;

textcolor(YELLOW);
textbackground(BLACK);
intro();

do
{textcolor(BLUE);
textbackground(WHITE);
clrscr();
cout<<"\t\t\t\t";
cout<<"\n\t\t\t";
time();
cout<<"\n\n\n\tMAIN MENU";
cout<<"\n\n\t01. CUSTOMER";
cout<<"\n\n\t02. ADMINISTRATOR";
cout<<"\n\n\t03. EXIT";
cout<<"\n\n\tPlease Select Your Option (1-3) ";

ch=getche();
textcolor(RED);
switch(ch)
{
case '1': clrscr();
place_order();
textbackground(WHITE);
getch();
break;
case '2': admin_menu();
break;
case '3':ending();
exit(0);
default :cout<<"\a";
}
}while(ch!='3');
}
