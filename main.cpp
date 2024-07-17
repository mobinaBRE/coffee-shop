#include <iostream>
#include <string.h>
#include <fstream>
#include <cstdlib>
using namespace std;
struct pack {
	int price;
	string name;
};
class Order {
	private:
		int sum;
	public:
		pack s[15];
		Order() {
			sum=0;
			s[0].name="Espresso";
			s[0].price=55000;
			s[1].name="Latte";
			s[1].price=67000;
			s[2].name="BlackTea";
			s[2].price=35000;
			s[3].name="HotChocolate";
			s[3].price=77000;
			s[4].name="Mocha";
			s[4].price=75000;
			s[5].name="Coppuccino";
			s[5].price=66000;
			s[6].name="ChocolateMilk";
			s[6].price=70000;
			s[7].name="Lemonade";
			s[7].price=89000;
			s[8].name="ChocolateShake";
			s[8].price=103000;
			s[9].name="VanillaShake";
			s[9].price=95000;
			s[10].name="CaramelShake";
			s[10].price=95000;
			s[11].name="IcedLatte";
			s[11].price=98000;
			s[12].name="IcedCoffee";
			s[12].price=83000;
			s[13].name="ChocolateCake";
			s[13].price=45000;
			s[14].name="CarrotCake";
			s[14].price=35000;
		}
		void addOrder(string name1,int n) {
			for(int i=0; i<15; i++) {
				if(s[i].name==name1) {
					sum+=(s[i].price)*n;
					break;
				}
			}
		}
		void changePrice(string name1,int newPrice) {
			for(int i=0; i<15; i++) {
				if(s[i].name==name1) {
					s[i].price=newPrice;
					break;
				}
			}
		}
		void menu() {
			for(int i=0; i<15; i++) {
				cout<<s[i].name<<" : "<<s[i].price<<"\n";
			}
		}
		int getsum() {
			return sum;
		}
};
class date {
	private:
		int year,month,day;
	public:
		date() { }
		void getDate() {
			cout<<"enter today's date :\n year:";
			cin>>year;
			cout<<" month:";
			cin>>month;
			cout<<" day:";
			cin>>day;
		}
		string printDate() {
			string dmy,stryear,strmonth,strday;
			stryear=to_string(year);
			strmonth=to_string(month);
			strday=to_string(day);
			dmy=strday+"/"+strmonth+"/"+stryear;
			return dmy;
		}

};
void updateLine(string  filename,const string &productname,int n,int f) {
	ifstream file(filename);
	ofstream temp("temp.txt");
	if(!file || !temp) {
		cout<<"error opening (file)";
		return;
	}
	string line;
	string num;
	bool foundkey=false;
	while(getline(file,line)) {
		if(foundkey) {
			int number;
			if(f==1) {
				num=line;
				number=atoi(num.c_str());
				number-=n;
			} else {
				number=n;
			}
			temp<<number<<"\n";
			foundkey=false;
		} else {
			temp<<line<<"\n";
		}
		if(line==productname) {
			foundkey=true;
		}
	}
	file.close();
	temp.close();
	ifstream temp1("temp.txt");
	ofstream file1(filename);
	while(getline(temp1,line)) {
		file1<<line<<"\n";
	}
	temp.close();
	file.close();
}
void check(string  filename) {
	ifstream file(filename);
	if(!file) {
		cout<<"error opening (file)";
		return;
	}
	int i=0,number;
	string line;
	Order m;
	while(getline(file,line)) {
		i++;
		if(i%2==0) {
			string numstr=line;
			number=atoi(numstr.c_str());
			if(number<20) {
				cout<<m.s[i/2].name<<" : less than 20.\n";
			}
		}
	}
}
int main() {
	fstream file1("inventory.txt",ios::in | ios::out|ios::app);
	if(!file1) {
		cout<<"error opening file \n";
		return 0;
	}
	fstream file2("orders.txt",ios::in | ios::out|ios::app);
	if(!file2) {
		cout<<"error opening file \n";
		return 0;
	}
	int option,totalAmount=0;
	date today;
	today.getDate();
	file2<<"date:"<<today.printDate()<<"\n";
menu:
	check("inventory.txt");
	cout<<"witch one?\n 1)submit a new order\n 2)change the price\n";
	cout<<" 3)print the inventory\n 4)print orders report\n 5)enter new inventory\n";
	cout<<" 6)exit \n : ";
	cin>>option;
	Order newOrder;
	string name,number,change,line3,line4;
	switch(option) {
		case 1:
			int n,item;
			cout<<"name :";
			cin>>name;
			cout<<"number :";
			cin>>number;
			file2<<"name:"<<name<<" number:"<<number<<",orders:";
			for(int i=0; i<15; i++) {
				cout<<i+1<<")"<<newOrder.s[i].name<<"="<<newOrder.s[i].price<<"\n";
			}
			do {
				cout<<"number of orders:";
				cin>>n;
				if(n!=0) {
					cout<<"witch one? ";
					cin>>item;
					newOrder.addOrder(newOrder.s[item-1].name,n);
					updateLine("inventory.txt",newOrder.s[item-1].name,n,1);
					file2<<newOrder.s[item-1].name<<"("<<n<<")="<<n*(newOrder.s[item-1].price)<<",";
					string word;
					int line=0;
					while(file1>>word) {
						line++;
						if(word==newOrder.s[item-1].name)
							break;
					}
				} else {
					file2<<"\n"<<newOrder.getsum()<<"\n";
					cout<<"amount of orders : "<<newOrder.getsum()<<"\n";
					totalAmount+=newOrder.getsum();
				}
			} while(n!=0);
			break;
		case 2:
			int newprice;

			cout<<"witch one do you want to change ? ";
			cin>>change;
			cout<<"enter new price : ";
			cin>>newprice;
			newOrder.changePrice(change,newprice);
			break;
		case 3:
			while(getline(file1,line3)) {
				cout<<line3<<"\n";
			}
			break;
		case 4:
			while(getline(file2,line4)) {

				cout<<line4<<"\n";
			}
			break;
		case 5:
			int newinven;
			cout<<"enter new inventory :\n";
			for(int i=0; i<15; i++) {
				cout<<newOrder.s[i].name<<" : ";
				cin>>newinven;
				updateLine("inventory.txt",newOrder.s[i].name,newinven,2);
			}
			break;
		case 6:
			if(totalAmount!=0){
				file2<<"daily amount : "<<totalAmount<<"\n";
				cout<<"total amount :"<<totalAmount<<"\n";
			}
				
			return 1;
	}
	goto menu;
	return 0;
}