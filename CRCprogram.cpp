//cyclic redundancy check
#include <bits/stdc++.h>
#include <conio.h>
using namespace std;
int n,k;

string XOR(string data,string div,int i){
for(int k=i;k<i+div.length();k++)
{if(data[k]==div[k-i])
  data[k]='0';
 else
  data[k]='1';}
  //cout<<data<<endl;
  return data;
  }

//encoding
string encode(string data,string div){
  n= data.length(),k=div.length();
 for(int i=1;i<k;i++)
   data+='0';
 //cout << "Augmented Data is  "<<data<<endl<<endl;
 string rem=data;
 for(int i=0;i<n;i++)
  {if(rem[i]=='0')
    continue;
   else
    rem= XOR(rem,div,i);}
 cout<<endl;
  
 string code=XOR(data,rem.substr(n,k-1),n);
 

 return code;
 }


//decoding
int decode(string code,string div){
 n= code.length();
 k= div.length();
 for(int i=0;i<n-k+1;i++)
 {if(code[i]=='0')
    continue;
  else
   code= XOR(code,div,i) ;
 }
//cout<<"So,Final remainder is "<<code<<endl;
int zeroes=0,err=0;
for(int i=n-k;i<n;i++)
{if(code[i]=='0')
 zeroes++;}
 if(zeroes==k)
  cout<<"NO ERROR detected using CRC"<<endl;
 else
  {cout<<"ERROR detected using CRC"<<endl<<"DISCARD"<<endl;
   err=1;}
return err;

}

string error(string data,float p){

for(int i=0;i<data.length();i++)
{float r = ((float) rand() / (RAND_MAX));
if(r<p)
{if(data[i]=='0')
 data[i]='1';
 else
 data[i]='0';}
}
return data;
}

int main() {
//encoding
 string data,div="100000111",code;
 cout<<"Enter Data Stream"<<endl;
 cin >> data;

 cout<<"CRC-8 Divisor is "<<div<<endl;
   n= data.length(),k=div.length();


 float token=16.0,block=n/token;
 int a=n%(int)token;
 if(n%(int)token==0)
 {block-=0.5;
 a=token;}
 string arr[(int)ceil(block)];

 
 for(int i=1;i<=floor(block);i++)
 arr[i]=data.substr(a+token*(i-1),token);
 
 arr[0]=data.substr(0,a);
 int t=arr[0].length();
 for(int i=0;i<token-t;i++)
 arr[0]='0'+arr[0];
 
string codearr[(int)ceil(block)];

for(int i=0;i<=floor(block);i++)
{codearr[i]=encode(arr[i],div);
 cout<<token<<" bit Tokenized data "<<i+1 << " is   : "<<arr[i]<<endl;
 cout<<"CodeWord "<<i+1<<" at sender site is : "<< codearr[i]<< endl;
  cout<<endl;}

int hops;
float p;
cout<<"Enter no of hops in binary symmetric channel : (1 0r 2) ";
cin>>hops;
cout<<endl<<"Enter crossover probability for binary symmetric channel :";
cin>>p;
cout<<endl;
string errarr[(int)ceil(block)];
for(int i=0;i<=floor(block);i++)
  errarr[i]=codearr[i];
for(int i=0;i<hops;i++)
{for(int i=0;i<=floor(block);i++)
  errarr[i]=error(errarr[i],p);
 

 }
int errno;
for(int i=0;i<=floor(block);i++)
{cout<<"Code Word send     "<<i <<" is " <<codearr[i]<<endl;
 cout<<"Code Word recieved "<<i <<" is "<<errarr[i]<<endl;
 errno+=decode(errarr[i],div);
 cout<<endl;}

if(errno>0)
cout<<"Message is Discarded"<<endl;
else
{cout<<"NO Error in recieved data & Extracted Data from Code Word is "<<endl;
for(int i=0;i<=floor(block);i++)
 cout<<errarr[i].substr(0,token);
 cout<<endl;}

 cout<<data;
 cout<<" was our original data     ";

// code=encode(data,div);
 getch();
 
 }
 



