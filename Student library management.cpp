#include<bits/stdc++.h>
using namespace std;
#define el "\n"
int res_book(int,int);		//To check whether any book a given book no. exists or not
bool res_student(int);	//To check whether the admission no. already exist or not



class book							//Class of books
{
	protected:
	int bookno;						//book no
	char bookname[50]; 				//book name
	char authorname[50]; 				//book author's name
	char publicationname[50];  				//publication name
	public:
		int quantity;
		void createbook()           //To enter data in data members of class book
		{
			int i;
			cout<<"\n\t\tEnter the details:-\n";
			cout<<"\n\t\tEnter Book's Name: ";
			char n[50];
			cin.getline(n,50);
			cin.getline(bookname,50);
			for(i=0;bookname[i]!='\0';i++)
			{
				if(bookname[i]>='a'&&bookname[i]<='z')
				bookname[i]-=32;
			}
			cout<<"\n\t\tEnter Author's Name: ";
			cin.getline(authorname,50);
			cout<<"\n\t\tEnter Publication Name: ";
			cin.getline(publicationname,50);
			cout<<"\n\t\tEnter Book's quantity: ";
			cin>>quantity;
		}


		void showbook()	  //To display the details of books
		{
		cout<<"\n\t\tBook No.: "<<bookno<<el;
		cout<<"\n\t\tBook Name: "<<bookname<<el;
		cout<<"\n\t\tBook's Author Name: "<<authorname<<el;
		cout<<"\n\t\tBook's Publication: "<<publicationname<<el;
		cout<<"\n\t\tBook's Quantity: "<<quantity<<el;
		}


		void showbooklist()			//To display book details in list form
		{
			cout<<"\n\t"<<bookno<<"\t\t"<<bookname<<"\t\t"<<authorname<<"\t\t"<<publicationname<<"\t\t"<<quantity;
		}


		void assignbookno(int x)       //bno assigned on the basis of no
		{						    //no. of objects in file
			bookno=10001;
			bookno+=x-1;
			label:           //loop
				bookno+=1;
				if(res_book(bookno,0))
				goto label;
		}
		void set_quantity()
		{
			quantity-=1;
		}
		int quant()
		{
			return quantity;
		}
		void reset_quantity()
		{
			quantity+=1;
		}
		int retbookno()
		{
			return bookno;
		}
};                               //End of class book/



//Class of Students/
class student
{
	protected:
		char stuname[25];					//Student name
		int bookstuissued;						//Book no. of book issued
		int flag;								//To veirfy book issued or not
	public:
		int admissionno;					//Admission No

		void createstu()	                //To enter values to all data members of class student
		{
		int i;
		label:
		system("CLS"); 						//clear screen
		cout<<"\n\t\tEnter the details:-\n";
		cout<<"\n\t\tEnter student's Admission no: ";
		cin>>admissionno;
		if(res_student(admissionno))
		{
			cout<<"\n\t\tRecord already exist with this admission no.";
			cout<<"\n\t\tEnter a different admission no.\n";
			system("PAUSE");
			goto label;
		}

		cout<<"\n\t\tEnter student's Name: ";
		char n[50];
		cin.getline(n,50);
		cin.getline(stuname,25);
			for(i=0;stuname[i]!='\0';i++)
			{
				if(stuname[i]>='a'&&stuname[i]<='z')
				stuname[i]-=32;
			}
			bookstuissued=0;
			flag=0;
		}


		void showstu()                           //Show details of Students
		{
		cout<<"\n\t\tStudent's Admission No.: "<<admissionno<<el;
		cout<<"\n\t\tStudent's Name: "<<stuname<<el;
		if(flag==1)
			{
			cout<<"\n\t\tBook Issued (Book no): "<<bookstuissued;
			}
		}


		void showstulist()                              // To display Student details in list form
		{
			cout<<"\n\t"<<admissionno<<"\t\t"<<stuname<<"\t\t"<<bookstuissued;
		}


		void setflag(int x)			//To set token and assign bno a book no
		{
			bookstuissued=x;
			flag=1;
		}


		void resetflag()				//To reset token
		{
			bookstuissued=0;
			flag=0;
		}


		int retbookno()
		{
			return bookstuissued;
		}
};
//End of class Students/

















//To Write object of class book in file/
void write_book()
{
	book bk;
	ofstream outf("book1.bin",ios::app|ios::binary);
	outf.seekp(0,ios::end);
	int x=outf.tellp()/sizeof(book);
	bk.assignbookno(x);
	bk.createbook();
	bk.showbook();
	outf.write(reinterpret_cast<char *>(&bk),sizeof(book));
	cout<<"\n\t\tCONGRATS, RECORD ADDED SUCCESSFULLY!!";
	outf.close();
}


//To Write object of class student in file/
void write_student()
{
	student st;
	ofstream outf("student.bin",ios::app|ios::binary);
	outf.seekp(0,ios::end);
	st.createstu();
	st.showstu();
	outf.write(reinterpret_cast<char *>(&st),sizeof(student));
	cout<<"\n\t\tCONGRATS, RECORD ADDED SUCCESSFULLY!!";
	outf.close();
}

//To display Student records in list form/
void list_student()
{
	system("CLS");
	student st;
	ifstream intf("student.bin",ios::in|ios::binary);
	intf.seekg(0,ios::beg);
	if(!intf)
	cout<<"\n\t\tFILE NOT FOUND";
	else
	{
		cout<<"\n\t*Students Details*\n\n";
		cout<<"\n\tAdmission No:\tName: \tBook Issued:";
		while(intf.read(reinterpret_cast<char *>(&st),sizeof(student)))
		st.showstulist();
	}
	intf.close();
}



//To display book records in list form/
void list_book()
{
	book bk;
	ifstream intf("book1.bin",ios::in|ios::binary);
	intf.seekg(0,ios::beg);
	if(!intf)
	cout<<"\n\t\tFILE NOT FOUND";
	else
	{
		cout<<"\n\t*Books Details*\n\n";
		cout<<"\n\tBook No: \tName: \tAuthor's Name: \tPublication's Name:\tQuantity: ";
		while(intf.read(reinterpret_cast<char *>(&bk),sizeof(book)))
		bk.showbooklist();
	}
	intf.close();
}


//To search for a specific student/
void search_student(int x)
{
	student st;
	int cnt=0;
	ifstream intf("student.bin",ios::in|ios::binary);
	intf.seekg(0,ios::beg);
	if(!intf)
	cout<<"\n\t\tFILE NOT FOUND";
	else
	{
		while(intf.read(reinterpret_cast<char *>(&st),sizeof(student)))
		{
			if(st.admissionno==x)
			{
				cnt++;
				cout<<"\n\t\tFILE FOUND!!!!";
				st.showstu();
				break;
			}
		}
		if(cnt==0)
		cout<<"\n\t\tSORRY, NO SUCH RECORD EXIST";
	}
	intf.close();
}


//To search for a specific book/
void search_book(int x)
{
	book bk;
	int cnt=0;
	ifstream intf("book1.bin",ios::in|ios::binary);
	intf.seekg(0,ios::beg);
	if(!intf)
	cout<<"\n\t\tFILE NOT FOUND";
	else
	{
		while(intf.read(reinterpret_cast<char *>(&bk),sizeof(book)))
		{
			if(bk.retbookno()==x)
			{
				cnt++;
				cout<<"\n\t\tFILE FOUND!!!!";
				bk.showbook();
				break;
			}
		}
		if(cnt==0)
		cout<<"\n\t\tSORRY, NO SUCH RECORD EXIST";
	}
	intf.close();
}



//To modify the book records/
void modify_book(int x)
{
	book bk;
	int cnt=0;
	fstream intf("book1.bin",ios::in|ios::out|ios::ate|ios::binary);
	intf.seekg(0,ios::beg);
	if(!intf)
	cout<<"\n\t\tFILE NOT FOUND";
	else
	{
		while(intf.read(reinterpret_cast<char *>(&bk),sizeof(book)))
		{
			if(bk.retbookno()==x)
			{
				cnt++;
				bk.createbook();
				bk.showbook();
				intf.seekp(intf.tellp()-sizeof(book));
				intf.write(reinterpret_cast<char *>(&bk),sizeof(book));
				cout<<"\n\t\tCONGRATS, RECORD UPDATED";
				break;
			}
		}
		if(cnt==0)
		cout<<"\n\t\tSORRY, NO SUCH RECORD EXIST";
	}
	intf.close();
}


//To modify the student records/
void modify_student(int x)
{
	student st;
	int cnt=0;
	fstream intf("student.bin",ios::in|ios::out|ios::ate|ios::binary);
	intf.seekg(0,ios::beg);
	if(!intf)
	cout<<"\n\t\tFILE NOT FOUND";
	else
	{
		while(intf.read(reinterpret_cast<char *>(&st),sizeof(student)))
		{
			if(st.admissionno==x)
			{
				cnt++;
				st.createstu();
				st.showstu();
				intf.seekp(intf.tellp()-sizeof(student));
				intf.write(reinterpret_cast<char *>(&st),sizeof(student));
				cout<<"\n\t\tCONGRATS, RECORD UPDATED";
				break;
			}
		}
		if(cnt==0)
		cout<<"\n\t\tSORRY, NO SUCH RECORD EXIST";
	}
	intf.close();
}


//To delete a specific student record/
void delete_student(int x)
{
	student st;
	int cnt=0;
	ifstream intf("student.bin",ios::in|ios::binary);
	intf.seekg(0,ios::beg);
	if(!intf)
	cout<<"\n\t\tFILE NOT FOUND";
	else
	{
		ofstream outf("temp.bin",ios::app|ios::binary);
		while(intf.read(reinterpret_cast<char *>(&st),sizeof(student)))
		{
			if(st.admissionno==x)
			cnt++;
			else
			outf.write(reinterpret_cast<char *>(&st),sizeof(student));
		}
		intf.close();
		outf.close();
		if(cnt==0)
		{
			remove("temp.bin");
			cout<<"\n\t\tSORRY, NO SUCH RECORD EXIST";
		}
		else
		{
			remove("student.bin");
			rename("temp.bin","student.bin");
			cout<<"\n\t\tCONGRATS, RECORD DELETED SUCCESSFULLY";
		}
	}
}





//To delete a specific book record/
void delete_book(int x)
{
	book bk;
	int cnt=0;
	ifstream intf("book1.bin",ios::in|ios::binary);
	intf.seekg(0,ios::beg);
	if(!intf)
	cout<<"\n\t\tFILE NOT FOUND";
	else
	{
		ofstream outf("temp1.bin",ios::app|ios::binary);
		while(intf.read(reinterpret_cast<char *>(&bk),sizeof(book)))
		{
			if(bk.retbookno()==x)
			cnt++;
			else
			outf.write(reinterpret_cast<char *>(&bk),sizeof(book));
		}
		intf.close();
		outf.close();
		if(cnt==0)
		{
			remove("temp1.bin");
			cout<<"\n\t\tSORRY, NO SUCH RECORD EXIST";
		}
		else
		{
			remove("book1.bin");
			rename("temp1.bin","book1.bin");
			cout<<"\n\t\tCONGRATS, RECORD DELETED SUCCESSFULLY";
		}
	}
}



//To search whether a specific student record exists or not
bool res_student(int x)
{
	student st;
	int cnt=0,f=0;
	ifstream intf("student.bin",ios::in|ios::binary);
	intf.seekg(0,ios::beg);
	if(!intf)
	f=1;
	else
	{
		while(intf.read(reinterpret_cast<char *>(&st),sizeof(student)))
		{
			if(st.admissionno==x)
			{
				cnt++;
				break;
			}
		}
		if(cnt==0)
		f=1;
	}
	intf.close();
	if(f)
	return 0;
	else
	return 1;
}


//To search a specific book and return true or false/
int res_book(int x,int z)
{
	book bk;
	int cnt=0,f=1;
	fstream intf("book1.bin",ios::in|ios::out|ios::ate|ios::binary);
	intf.seekg(0,ios::beg);
	if(!intf)
	f=0;
	else
	{
		while(intf.read(reinterpret_cast<char *>(&bk),sizeof(book)))
		{
			if(bk.retbookno()==x)
			{
				cnt++;
				if(z==1)
				{
					bk.showbook();

					if(bk.quant()>0)
					{
						bk.set_quantity();
						intf.seekp(intf.tellp()-sizeof(book));
						intf.write(reinterpret_cast<char *>(&bk),sizeof(book));
					}
					else
					f=2;
				}
				else if(z==2)
				{
					bk.showbook();
					bk.reset_quantity();
					intf.seekp(intf.tellp()-sizeof(book));
					intf.write(reinterpret_cast<char *>(&bk),sizeof(book));
				}
				break;
			}
		}
		if(cnt==0)
		f=0;
	}
	intf.close();
	return f;
}


//To issue books/
void book_issue()
{
	int sn,bn;
	system("CLS");
	cout<<"\n\n\t\t*BOOK ISSUE MENU**";
	cout<<"\n\n\t\tPLEASE ENTER THE STUDENT ADMISSION NUMBER:";
	cin>>sn;
	int cnt=0;
	student st;
	fstream outf("student.bin",ios::in|ios::out|ios::ate|ios::binary);
	outf.seekg(0,ios::beg);
	if(!outf)
	cout<<"\n\t\tFILE NOT FOUND\n";
	else
	{
		while(outf.read(reinterpret_cast<char *>(&st),sizeof(student)))
		{
			if(st.admissionno==sn)
			{
				cnt++;
				list_book();
				cout<<"\n\n\t\tEnter the book no.:";
				cin>>bn;
				cout<<"\n";
				int flag=res_book(bn,1);
				if(flag==1)
				{
					st.setflag(bn);
					outf.seekp(outf.tellp()-sizeof(student));
					outf.write(reinterpret_cast<char *>(&st),sizeof(student));
					cout<<"\n\t\tBook Issued";
					cout<<"\n\t\tIMP:  Please write the current date in backside of the book and";
					cout<<"\n\t\t      it should be submitted within 15 days to avoid fine";
					cout<<"\n\t\t      The fine is Rs. 1 for each day after the completion of 15 days\n";
					break;
				}
				else if(flag==2)
				{
					cout<<"\n\t\tTHE BOOK IS OUT OF STOCK!!!";
					break;
				}
				else
				{
					cout<<"\n\t\tSORRY, NO SUCH RECORD FOUND\n";
					break;
				}
			}
		}
		if(cnt==0)
		cout<<"\n\t\tSORRY, NO SUCH RECORD FOUND\n";
	}
	outf.close();
}


//To deposit books/
void book_deposit()
{
	int sn,bn;
	system("CLS");
	cout<<"\n\n\t\t**BOOK DEPOSIT MENU**";
	cout<<"\n\n\t\tPLEASE ENTER THE STUDENT'S ADMISSION NUMBER: ";
	cin>>sn;
	int cnt=0;
	student st;
	fstream outf("student.bin",ios::in|ios::out|ios::ate|ios::binary);
	outf.seekg(0,ios::beg);
	if(!outf)
	cout<<"\n\t\tFILE NOT FOUND\n";
	else
	{
		while(outf.read(reinterpret_cast<char *>(&st),sizeof(student)))
		{
			if(st.admissionno==sn)
			{
				cnt++;
				bn=st.retbookno();
				bool flag=res_book(bn,2);
				if(flag)
				{
					st.resetflag();
					outf.seekp(outf.tellp()-sizeof(student));
					outf.write(reinterpret_cast<char *>(&st),sizeof(student));
					int days;
					cout<<"\n\t\tNUMBER OF DAYS IN WHICH BOOKS IS DEPOSITED:";
					cin>>days;
					if(days>15)
					{
						int fine=(days-15)*1;
						cout<<"\n\n\t\tFine: "<<fine<<el;
					}
					cout<<"\n\t\tCONGRATS, BOOK DEPOSITED SUCCESSFULLY\n";
					break;
				}
				else
				{
					cout<<"\n\t\tSORRY, NO SUCH RECORD EXIST\n";
					break;
				}
			}
		}
		if(cnt==0)
		cout<<"\n\t\tSORRY, NO SUCH RECORD FOUND\n";
	}
	outf.close();
}

//Function that has features of Admin Menu/
void admin_menu()
{
label:
	system("PAUSE");
	system("CLS");
	int opt;
	cout<<"\n\n\n\t\t\t**YOU ARE NOW IN ADMIN MENU**";
    cout<<"\n\n\t1.\tTO CREATE STUDENT RECORD";
    cout<<"\n\n\t2.\tTO DISPLAY ALL STUDENTS RECORD";
    cout<<"\n\n\t3.\tTO DISPLAY SPECIFIC STUDENT RECORD ";
    cout<<"\n\n\t4.\tTO MODIFY ANY STUDENT RECORD";
    cout<<"\n\n\t5.\tTO DELETE STUDENT RECORD";
    cout<<"\n\n\t6.\tTO CREATE BOOK ";
    cout<<"\n\n\t7.\tTO DISPLAY ALL BOOKS ";
    cout<<"\n\n\t8.\tTO DISPLAY SPECIFIC BOOK ";
    cout<<"\n\n\t9.\tTO MODIFY BOOK ";
    cout<<"\n\n\t10.\tTO DELETE BOOK ";
    cout<<"\n\n\t11.\tTO BACK TO MAIN MENU";
    cout<<"\n\n\tPlease Enter Your Choice (1-11): ";
    cin>>opt;
    if(opt==1)
    {
    	system("CLS");
    	write_student();
    	cout<<el;
    	goto label;
	}
	else if(opt==2)
	{
		system("CLS");
    	list_student();
    	cout<<el;
    	goto label;
	}
	else if(opt==3)
	{
		system("CLS");
		int ad;
		cout<<"\n\n\n\t\tPLEASE ENTER THE STUDENT ADMISSION NUMBER:";
		cin>>ad;
		search_student(ad);
		cout<<el;
		goto label;
	}
	else if(opt==4)
	{
		system("CLS");
		int ad;
		cout<<"\n\n\n\t\tPLEASE ENTER THE STUDENT ADMISSION NUMBER:";
		cin>>ad;
		modify_student(ad);
		cout<<el;
		goto label;
	}
	else if(opt==5)
	{
		system("CLS");
		int ad;
		cout<<"\n\n\n\t\tPLEASE ENTER THE STUDENT ADMISSION NUMBER:";
		cin>>ad;
		delete_student(ad);
		cout<<el;
		goto label;
	}
	else if(opt==6)
    {
    	system("CLS");
    	write_book();
    	cout<<el;
    	goto label;
	}
	else if(opt==7)
	{
		system("CLS");
    	list_book();
    	cout<<el;
    	goto label;
	}
	else if(opt==8)
	{
		system("CLS");
		int ad;
		cout<<"\n\n\n\t\tPLEASE ENTER THE BOOK NUMBER TO SEARCH";
		cin>>ad;
		search_book(ad);
		cout<<el;
		goto label;
	}
	else if(opt==9)
	{
		system("CLS");
		int ad;
		cout<<"\n\n\n\t\tPLEASE ENTER THE BOOK NUMBER TO MODIFY";
		cin>>ad;
		modify_book(ad);
		cout<<el;
		goto label;
	}
	else if(opt==10)
	{
		system("CLS");
		int ad;
		cout<<"\n\n\n\t\tPLEASE ENTER THE BOOK NUMBER TO DELETE";
		cin>>ad;
		delete_book(ad);
		cout<<el;
		goto label;
	}
	else if(opt==11)
	return ;
	else
	{
		cout<<"\n\t\tEnter you choice: ";
		cout<<el;
		goto label;
	}
}



//Checks for correct password/

bool passwords()
{
	int i=0;
	char ch,st[21],ch1[21]={"Anushka"};
	cout<<"\n\n\t\tPlease Enter the Password : ";
	while(1)            
    {
    	ch=getch();
    	if(ch==13) //enter
    	{
        	st[i]='\0';
        	break;
    	}
    	else if(ch==8&&i>0)
    	{
        	i--;
        	cout<<"\b \b";
    	}
    	else 
    	{
    		cout<<ch;
    		st[i]=ch;
    		i++;
    	}
    }
    for(i=0;st[i]==ch1[i]&&st[i]!='\0'&&ch1[i]!='\0';i++);
    if(st[i]=='\0'&&ch1[i]=='\0')
    return 1;
    else
    return 0;
}

//Main function
int main()
{
	
	cout<<"\n\n\t\t\t""""""""""""""""""""""""""""""""""""""""""";
	cout<<"\n\t\t\t\t------------------------------------------";
	cout<<"\n\t\t\t\t WELCOME TO";
	cout<<"\n\t\t\t\t SOFTWARE FOR LIBRARY MAINTENANCE";
	cout<<"\n\t\t\t\t------------------------------------------";
	cout<<"\n\t\t\t\t""""""""""""""""""""""""""""""""""""""""""";
	bool a=passwords();
	if(!a)
	{
		for(int i=0;i<2;i++)
		{
			cout<<"\n\n\nYOU HAVE ENTERED WRONG PASSWORD";
			cout<<"\n\nONLY "<<2-i<<" ATTEMPTS LEFT";
			if(passwords())
			goto label;
			if(i==1)
			{
				cout<<"\n\n\n\t\t\t YOUR ALL PASSWORD ATTEMPTS ARE FAILED........";
				cout<<"\n\n\t\t\t SORR, YOU CANNOT LOGIN NOW";
				exit(0);
			}
		}
	}
	label:
		cout<<"\n\n";
	label1:
		system("PAUSE");
		system("CLS");
		int opt;
		cout<<"\n\n\t\t\t-**-**-**-**-**-**--**-**-**-**-**-**-**--**-**-**-**-**-**-**-";
		cout<<"\n\t\t\t\tSOFTWARE FOR LIBRARY MAINTENANCE";
		cout<<"\n\t\t\t-**-**-**-**-**-**-**-**-**-**-**-**-**-**--**-**-**-**-**-**-**-";
		cout<<"\n\n\t\t\tPlease select your choice";
		cout<<"\n\t\t\t1.\tTO ISSUE BOOK";
		cout<<"\n\t\t\t2.\tTO DEPOSIT BOOK";
		cout<<"\n\t\t\t3.\tADMIN MENU";
		cout<<"\n\t\t\t4.\tTO EXIT";
		cout<<"\n\n Choose your option: ";
		cin>>opt;
		if(opt==1)
		{
			system("CLS");
			book_issue();
			goto label1;
		}
		else if(opt==2)
		{
			system("CLS");
			book_deposit();
			goto label1;
		}
		else if(opt==3)
		{
			admin_menu();
			goto label1;
		}
		else if(opt==4)
		exit(0);
		else
		{
			cout<<"\n\t\tPLEASE ENTER YOUR CORRECT OPTION";
			goto label1;
		}
}
