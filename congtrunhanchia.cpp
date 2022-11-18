#include <iostream>
#include <string.h>
#include <stdio.h>
#include<fstream>
using namespace std;
#define MAXLEN 1000

 
struct SNL
{
	char sign;
	char len;
	char num[MAXLEN];
};

void InitSNL(SNL &n);
void str2snl(char*str, SNL &n);
void scanSNL(SNL &n);
void printSNL(SNL &n);
int cmpu(SNL &a, SNL &b);
int cmp(SNL &a, SNL &b);
void addu(SNL &s, SNL &a, SNL &b);
void add(SNL &s, SNL &a, SNL &b);
void subu(SNL &s, SNL &a, SNL &b);
void sub(SNL &s, SNL &a, SNL &b);
void mul(SNL &r, SNL &a, SNL &b);
void div(SNL &r, SNL a, SNL b);

// khoi tao so nguyen lon
void InitSNL(SNL &n)
{
	for(int i=0;i<MAXLEN;i++) n.num[i]=0;
	n.len=0;
	n.sign=1;
}

// chuyen chuoi thanh so
void str2snl(char *str, SNL &n)
{
	int i;
	if(str[0]=='-')
	{
		n.sign=-1;
		str++; // bo qua ki tu dau
	}
	else
		n.sign=1;
	while (str[0] == '0') ++str; // Bo qua ki tu 0
	n.len=strlen(str); // so ki tu cua so nguyen lon
	for(i=0;i<n.len;i++) //chuyen tung ki tu thanh so
		n.num[i]=str[n.len-i-1]-'0'; //chu y: chu so hang don vi dau mang
}

int cmpu(SNL &a, SNL &b) //so sanh tri tuyet doi 2 so nguyen lon a va b
{
	if(a.len>b.len) //so nao dai hon thi lon hon
		return 1;
	else if(a.len<b.len)
		return -1;
	else // khi 2 so co chieu dai bang nhau
	{
		int len=a.len-1;
		while(len>=0) // lan luot so sanh tung chu so
		{
			
			if(a.num[len]>b.num[len])
				return 1;
			else if(a.num[len]<b.num[len])
				return -1;
			else
				len--;
		}
	}
	return 0;
}

int cmp(SNL &a, SNL &b) // so sanh 2 so nguyen lon
{
	if(a.sign*b.sign<0) 
	 	if (a.sign <0) return -1; else return 1;
    if (a.sign * b.sign >0)
        return a.sign * cmpu(a,b);
}

void scanSNL(SNL &n) // doc 1 so hang tu tep input
{
	char *t=new char[MAXLEN];
	cin>>t;
	str2snl(t,n);
	delete[]t;
}

/*void nhap(ifstream &in,SNL &n) 
{
	char *t=new char[MAXLEN];
	in>>t;
	str2snl(t,n);
	delete[]t;
}*/


/*void infile(ofstream &input, SNL &n) 
{	
	if(n.sign<0) input<<"-";
	if(n.len>0)
		for(int i=n.len-1;i>=0;i--) input<<(int)n.num[i];
	else
		input<<0;
	input<<endl;
	
}*/
void printSNL(SNL &n) // xuat ra mot so nguyen lon o tep output
{
	if(n.sign<0) cout<<"-";
	if(n.len>0)
		for(int i=n.len-1;i>=0;i--) cout<<(int)n.num[i];
	else
		cout<<0;
}

void addu(SNL &s, SNL &a, SNL &b) // cong hai so nguyen lon khong dau
{
	InitSNL(s);
	s.len=a.len>b.len?a.len:b.len; // do dai ban dau cua tong
	char m=0;
	for(int i=0;i<s.len;i++)
	{
		s.num[i]=a.num[i]+b.num[i]+m;
		if(s.num[i]>9)
		{
			s.num[i]-=10;
			m=1;
		}
		else
			m=0;
	}
	if(m)
	{
		s.num[s.len]=1;
		s.len++;
	}
}

void add(SNL &s, SNL &a, SNL &b) // cong 2 so nguyen lon co dau
{
	if(a.sign*b.sign>0) //neu a va b cung dau 
	{
		addu(s,a,b);
		s.sign=a.sign; //dau cua tong nhu dau cua moi so hang
	}
	else // neu a va b khac dau 
	{
		int t=cmpu(a,b); // so sanh 2 so a va b
		if(t==1) //a>b thi dau cua tong nhu dau cua a
		{
			subu(s,a,b);
			s.sign=a.sign;
		}
		else if(t==-1) //b>a thi dau cua tong nhu dau cua b
		{
			subu(s,b,a);
			s.sign=b.sign;
		}
		else InitSNL(s); // tong bang 0
	}
}

void subu(SNL &r, SNL &a, SNL &b) //tru 2 so nguyen lon khong dau
{
	InitSNL(r); // khoi tri hieu a-b
	r.len=a.len>b.len?a.len:b.len; //do dai cua hieu
	int m=0;
	for(int i=0;i<r.len;i++)
	{
		if(a.num[i]<b.num[i]+m)
		{
			r.num[i]=10+a.num[i]-b.num[i]-m;
			m=1;
		}
		else
		{
			r.num[i]=a.num[i]-b.num[i]-m;
			m=0;
		}
	}while(r.num[r.len-1]==0) r.len--; //bo cac so 0 vo nghia o cuoi mang
}

void sub(SNL &r, SNL &a, SNL &b) //tru 2 so nguyen lon co dau:( a-b=a+(-b)) 
{
	b.sign=-b.sign;
	add(r,a,b);
	b.sign=-b.sign;
}

void mul(SNL &r, SNL &a, SNL &b) //nhan 2 so nguyen lon 
{
	InitSNL(r);
	for(int i=0;i<b.len;i++)
		for(int j=0;j<b.num[i];j++)
			for(int k=0;k<a.len;k++)
			{
				r.num[k+i]+=a.num[k];
				if(r.num[k+i]>9)
				{
					r.num[k+i]-=10;
					r.num[k+i+1]++;
				}
			}
			r.len=a.len+b.len;
			while(r.num[r.len-1]==0) r.len--;
			r.sign=a.sign*b.sign;
}

void div(SNL &r,SNL &du, SNL a, SNL b) //tim thuong a/b 
{
	InitSNL(r);
	r.sign=a.sign*b.sign;
	r.len=a.len-b.len+1;
	if(a.len>=b.len)
	{
		int blen=b.len;
		int i;
		if(a.len>b.len)
		{
			i=a.len-1;
			int x=a.len-b.len;
			while(i>=0)
			{
				if(i>=x)
					b.num[i]=b.num[i-x];
				else 
					b.num[i]=0;
				i--;
			}
		}
		b.len=a.len;
		SNL d;
		i=1;
		while(b.len>=blen)
		{
			while(cmpu(a,b)>-1)
			{
				subu(d,a,b);
				r.num[r.len-i]++;
				a=d;
			}
			b.len--;
			i++;
			for(int k=0;k<b.len;k++) b.num[k]=b.num[k+1];	
			b.num[b.len]=0;	
		}
		du=a;
		while(r.num[r.len-1]==0) r.len--;
		
	}
	else
	{
		du=a;
	}	 
}




int main()
{
	SNL a,b,c,d;
	InitSNL(a);
	InitSNL(b);
	InitSNL(c);
	InitSNL(d);

	/*ifstream in("input.txt") ;
	nhap(in,a); 
	nhap(in,b);
	char h;
	in>>h;

	ofstream input("output.txt");*/

	scanSNL(a);
	scanSNL(b);
	
	cout<<"\n 1.cong"
		<<"\n 2.tru"
		<<"\n 3.nhan"
		<<"\n 4.chia \n\n";
	int k;
	cin>>k;
	switch(k)
    {
    	case 1:add(c,a,b);cout<<"a + b =";printSNL(c);cout<<endl;break;
    	case 2:sub(c,a,b);cout<<"a - b =";printSNL(c);cout<<endl;break;
    	case 3:mul(c,a,b);cout<<"a * b =";printSNL(c);cout<<endl;break;
    	case 4:div(c,d,a,b);cout<<"a / b =";printSNL(c);cout<<" du ";printSNL(d);cout<<endl;break;
    	
         
    }
/*	switch(h)
    {
    	case '+':add(c,a,b);infile(input,c);printSNL(a);cout<<" + ";printSNL(b);cout<<" = ";printSNL(c);cout<<endl;break;
    	case '-':sub(c,a,b);infile(input,c);printSNL(a);cout<<" - ";printSNL(b);cout<<" = ";printSNL(c);cout<<endl;break;
    	case '*':mul(c,a,b);infile(input,c);printSNL(a);cout<<" * ";printSNL(b);cout<<" = ";printSNL(c);cout<<endl;break;
    	case '/':div(c,d,a,b);infile(input,c);input<<"du ";infile(input,d);printSNL(a);cout<<" / ";printSNL(b);cout<<" = ";printSNL(c);cout<<" du ";printSNL(d);cout<<endl;break;
    	default :input << "Khong hop le";
         
    }*/
		
	return 0;	
}

