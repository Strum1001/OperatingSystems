#include <iostream>
using namespace std;
#include <cstdlib>

//This is a simulation of an operating system context switching between different proces

int r1 = 0;
int r2 = 0;
int r3 = 0;
int r4 = 0;
int w1 = 0;
int w2 = 0;
int w3 = 0;
int a, b, c, d, e, f, g;
bool key, lock= false;
int countsema = 3;
int binsema = 1;
int cs2count = 0, ws2 = 0;
int reader1();
int reader2();
int reader3();
int reader4();
int writer1();
int writer2();
int writer3();

void panic();
void wait(int *, int *);
void signal(int *);
void swap(bool *, bool *);
void countr();

main()
{

int pid;

for(int i =0; i<1000000; i++)
{
	panic();
	pid = rand()%7;
	switch(pid)
	{
		case 0: reader1(); break;
		case 1: reader2(); break;
		case 2: reader3(); break;
		case 3: reader4(); break;
		case 4: writer1(); break;
		case 5: writer2(); break;
		case 6: writer3(); break;

	}
}
}

void panic()
{
	if(binsema <=0 && countsema <= 2)
		cout<<"PANIC ALERT! WRITER AND READER IN CRITICAL SECTION"<<endl;
	if(ws2>0 && cs2count >0)
		cout<<"PANIC ALERT! WRITER AND READER IN CS2"<<endl;
	if(cs2count>3)
		cout<<"PANIC ALERT! MORE THAN 3 READERS IN CS2"<<endl;
}

void wait(int *checkthis, int *proc)
{
	if(checkthis == &countsema)
	{
		if(countsema >0 && binsema >0)
		{
			countsema -=1;
			*proc +=1;
		}
	}
	else if(checkthis == &binsema)
		if(binsema ==1 && countsema ==3)
		{			
			*proc+=1;
			binsema-=1;
		}


}

void signal(int *r)
{
	*r= *r+1;
}

void swap(bool *a, bool* b)
{
	bool temp = *a;
	*a = *b;
	*b = temp;
}

void countr()
{
	cout<< "There are "<<3-countsema<<" readers in the critical section"<<endl<<
	"There are "<<1- binsema<<" writers in the Critical section"<<endl;
}

int reader1()
{
	switch(r1)
	{
		case 0:  cout<<"Reader 1 started"<<endl; r1++;   return 0;
		case 1:  a = 0;  r1++; return 0;
		case 2: if(a < 50) r1++; else r1= r1+2; return 0;
		case 3: r1--;++a; return 0;
		case 4: cout<<"Reader 1 about to enter critical section"<<endl; r1++; return 0;
		case 5: wait(&countsema, &r1); return 0;
		case 6: a = 30; r1++; return 0;
		case 7: if(a>0) r1++; else r1+=2; return 0;
		case 8: cout<<"R1 in CS "<<endl; a--; r1--; return 0;
		case 9: countr(); r1++; return 0;
		case 10: signal(&countsema); r1++; return 0;
		case 11: cout<<"R1 in NCS"<<endl; r1++; return 0;
		case 12: a= 0; r1++; return 0;
		case 13: if(a <30) r1++; else r1+=2; return 0;
		case 14: a++; r1--; return 0;
		case 15: cout<<"R1 trying to enter 2nd CS"<<endl; r1++; return 0;
		case 16: key =true; r1++; return 0;
		case 17: if(key== true) if(cs2count>2||ws2>=1) swap(&lock, &key); else {cs2count++; r1++;} return 0;
		case 18: cout<<"R1 in 2nd CS"<<endl; r1++; return 0;
		case 19: cout<<"There are "<<cs2count<< " readers in 2nd cs"<<endl<<"And "<<ws2<<" writers"<<endl; r1++; return 0;
		case 20: a = 0; r1++; return 0;
		case 21: if(a<50) r1++; else r1+=2; return 0;
		case 22: a++; r1--; return 0;
		case 23: cs2count-=1; r1++; return 0;
		case 24: if(cs2count==0) lock =false; r1++; return 0;
		case 25: cout<<"R1 in NCS"<<endl; r1++; return 0;
		
	}

}
int reader2()
{
	switch(r2)
	{
		case 0:  cout<<"Reader 2 started"<<endl; r2++;   return 0;
		case 1:  b = 0;  r2++; return 0;
		case 2: if(b < 50) r2++; else r2= r2+2; return 0;
		case 3: r2--;b++; return 0;
		case 4: cout<<"Reader 2 about to enter critical section"<<endl; r2++; return 0;
		case 5: wait(&countsema, &r2); return 0;
		case 6: b = 30; r2++; return 0;
		case 7: if(b>0) r2++; else r2+=2; return 0;
		case 8: cout<<"R2 in CS "<<endl; b--; r2--; return 0;
		case 9: countr(); r2++; return 0;
		case 10: signal(&countsema); r2++; return 0;
		case 11: cout<<"R2 in NCS"<<endl; r2++; return 0;
		case 12: b= 0; r2++; return 0;
		case 13: if(b <30) r2++; else r2+=2; return 0;
		case 14: b++; r2--; return 0;
		case 15: cout<<"R2 trying to enter 2nd CS"<<endl; r2++; return 0;
		case 16: key =true; r2++; return 0;
		case 17: if(key== true) if(cs2count>2||ws2>=1) swap(&lock, &key); else {cs2count++; r2++;} return 0;
		case 18: cout<<"R2 in 2nd CS"<<endl; r2++; return 0;
		case 19: cout<<"There are "<<cs2count<< " readers in 2nd cs"<<endl<<"And "<<ws2<<" writers"<<endl; r2++; return 0;
		case 20: b = 0; r2++; return 0;
		case 21: if(b<50) r2++; else r2+=2; return 0;
		case 22: b++; r2--; return 0;
		case 23: cs2count-=1; r2++; return 0;
		case 24: if(cs2count==0) lock =false; r2++; return 0;
		case 25: cout<<"R2 in NCS"<<endl; r2++; return 0;
	}
}
int reader3()
{
	switch(r3)
	{
	case 0:  cout<<"Reader 3 started"<<endl; r3++;   return 0;
		case 1:  c = 0;  r3++; return 0;
		case 2: if(c < 50) r3++; else r3= r3+2; return 0;
		case 3: ++c;r3--; return 0;
		case 4: cout<<"Reader 3 about to enter critical section"<<endl; r3++; return 0;
		case 5: wait(&countsema, &r3); return 0;
		case 6: c = 30; r3++; return 0;
		case 7: if(c>0) r3++; else r3+=2; return 0;
		case 8: cout<<"R3 in CS "<<endl; c--; r3--; return 0;
		case 9: countr(); r3++; return 0;
		case 10: signal(&countsema); r3++; return 0;
		case 11: cout<<"R3 in NCS"<<endl; r3++; return 0;
		case 12: c= 0; r3++; return 0;
		case 13: if(c <30) r3++; else r3+=2; return 0;
		case 14: c++; r3--; return 0;
		case 15: cout<<"R3 trying to enter 2nd CS"<<endl; r3++; return 0;
		case 16: key =true; r3++; return 0;
		case 17: if(key== true ) if(cs2count>2||ws2>=1) swap(&lock, &key); else {cs2count++; r3++;} return 0;
		case 18: cout<<"R3 in 2nd CS"<<endl; r3++; return 0;
		case 19: cout<<"There are "<<cs2count<< " readers in 2nd cs"<<endl<<"And "<<ws2<<" writers"<<endl; r3++; return 0;
		case 20: c = 0; r3++; return 0;
		case 21: if(c<50) r3++; else r3+=2; return 0;
		case 22: c++; r3--; return 0;
		case 23: cs2count-=1; r3++; return 0;
		case 24: if(cs2count==0) lock =false; r3++; return 0;
		case 25: cout<<"R3 in NCS"<<endl; r3++; return 0;
	}
}
int reader4()
{
	switch(r4)
	{
		case 0:  cout<<"Reader 4 started"<<endl; r4++;   return 0;
		case 1:  d = 0;  r4++; return 0;
		case 2: if(d < 50) r4++; else r4= r4+2; return 0;
		case 3: ++d; r4--; return 0;
		case 4: cout<<"Reader 4 about to enter critical section"<<endl; r4++; return 0;
		case 5: wait(&countsema, &r4); return 0;
		case 6: d = 30; r4++; return 0;
		case 7: if(d>0) r4++; else r4+=2; return 0;
		case 8: cout<<"R4 in CS "<<endl; d--; r4--; return 0;
		case 9: countr(); r4++; return 0;
		case 10: signal(&countsema); r4++; return 0;
		case 11: cout<<"R4 in NCS"<<endl; r4++; return 0;
		case 12: d= 0; r4++; return 0;
		case 13: if(d <30) r4++; else r4+=2; return 0;
		case 14: d++; r4--; return 0;
		case 15: cout<<"R4 trying to enter 2nd CS"<<endl; r4++; return 0;
		case 16: key =true; r4++; return 0;
		case 17: if(key== true) if(cs2count>2||ws2>=1) swap(&lock, &key); else {cs2count++; r4++;} return 0;
		case 18: cout<<"R4 in 2nd CS"<<endl; r4++; return 0;
		case 19: cout<<"There are "<<cs2count<< " readers in 2nd cs"<<endl<<"And "<<ws2<<" writers"<<endl; r4++; return 0;
		case 20: d = 0; r4++; return 0;
		case 21: if(d<50) r4++; else r4+=2; return 0;
		case 22: d++; r4--; return 0;
		case 23: cs2count-=1; r4++; return 0;
		case 24: if(cs2count==0) lock =false; r4++; return 0;
		case 25: cout<<"R4 in NCS"<<endl; r4++; return 0;
	}
}
int writer1()
{
	switch(w1)
	{
		case 0: cout<<"Writer 1 started"<<endl; w1++; return 0;
		case 1: cout<<"Writer 1 about to enter CS"<<endl; w1++; return 0;
		case 2: wait(&binsema, &w1); return 0;
		case 3: cout<<"W1 in CS"<<endl; w1++; return 0;
		case 4: e = 40; w1++; return 0;
		case 5: if(e>0) w1++; else w1+=3; return 0;
		case 6: cout<<"w1 in CS"<<endl;w1++; return 0;
		case 7: e--; w1-=2; return 0;
		case 8: countr(); w1++; return 0;
		case 9: cout<<"W1 leaving CS"<<endl; w1++; return 0;
		case 10: signal(&binsema); w1++; return 0;
		case 11: e =0; w1++; return 0;
		case 12: if(e<30) w1++; else w1+=2; return 0;
		case 13: e++; w1--; return 0;
		case 14: cout<<"W1 trying to enter second CS"<<endl; w1++; return 0;
		case 15: key =true; w1++; return 0;
		case 16: if(key ==true) swap(&lock, &key); else {ws2++; w1++; }return 0;
		case 17: cout<<"W1 in second CS"<<endl; w1++; return 0;
		case 18: cout<<"There are "<<cs2count<< " readers in 2nd cs"<<endl<<"And "<<ws2<<" writers"<<endl; w1++; return 0;
		case 19: e = 50; w1++; return 0;
		case 20: if(e >0) w1++; else w1+=2; return 0;
		case 21: e--; w1--; return 0;
		case 22: cout<<"W1 leaving 2nd CS"<<endl; w1++; return 0;
		case 23: ws2--; w1++; return 0;
		case 24: lock = false; w1++; return 0;
		case 25: cout<<"W1 in NCS"<<endl; w1++; return 0;
	
	}
}
int writer2()
{
	switch(w2)
	{
		case 0: cout<<"Writer 2 started"<<endl; w2++; return 0;
		case 1: cout<<"Writer 2 about to enter CS"<<endl; w2++; return 0;
		case 2: wait(&binsema, &w2); return 0;
		case 3: cout<<"W2 in CS"<<endl; w2++; return 0;
		case 4: f = 40; w2++; return 0;
		case 5: if(f>0) w2++; else w2+=2; return 0;
		case 6: f--; w2--; return 0;
		case 7: countr(); w2++; return 0;
		case 8: cout<<"W2 leaving CS"<<endl; w2++; return 0;
		case 9: signal(&binsema); w2++; return 0;
		case 10: f =0; w2++; return 0;
		case 11: if(f<30) w2++; else w2+=2; return 0;
		case 12: f++; w2--; return 0;
		case 13: cout<<"W2 trying to enter second CS"<<endl; w2++; return 0;
		case 14: key =true; w2++; return 0;
		case 15: if(key ==true) swap(&lock, &key); else{ws2++; w2++; } return 0;
		case 16: cout<<"W2 in second CS"<<endl; w2++; return 0;
		case 17: cout<<"There are "<<cs2count<< " readers in 2nd cs"<<endl<<"And "<<ws2<<" writers"<<endl; w2++; return 0;
		case 18: f = 50; w2++; return 0;
		case 19: if(f >0) w2++; else w2+=2; return 0;
		case 20: f--; w2--; return 0;
		case 21: cout<<"W2 leaving 2nd CS"<<endl; w2++; return 0;
		case 22: ws2--; w2++; return 0;
		case 23: lock = false; w2++; return 0;
		case 24: cout<<"W2 in NCS"<<endl; w2++; return 0;
	}
}
int writer3()
{
	switch(w3)
	{
		case 0: cout<<"Writer 3 started"<<endl; w3++; return 0;
		case 1: cout<<"Writer 3 about to enter CS"<<endl; w3++; return 0;
		case 2: wait(&binsema, &w3); return 0;
		case 3: cout<<"W3 in CS"<<endl; w3++; return 0;
		case 4: g = 40; w3++; return 0;
		case 5: if(g>0) w3++; else w3+=2; return 0;
		case 6: g--; w3--; return 0;
		case 7: countr(); w3++; return 0;
		case 8: cout<<"W3 leaving CS"<<endl; w3++; return 0;
		case 9: signal(&binsema); w3++; return 0;
		case 10: g =0; w3++; return 0;
		case 11: if(g<30) w3++; else w3+=2; return 0;
		case 12: g++; w3--; return 0;
		case 13: cout<<"W3 trying to enter second CS"<<endl; w3++; return 0;
		case 14: key =true; w3++; return 0;
		case 15: if(key ==true) swap(&lock, &key); else {ws2++; w3++; } return 0;
		case 16: cout<<"W3 in second CS"<<endl; w3++; return 0;
		case 17: cout<<"There are "<<cs2count<< " readers in 2nd cs"<<endl<<"And "<<ws2<<" writers"<<endl; w3++; return 0;
		case 18: g= 50; w3++; return 0;
		case 19: if(g >0) w3++; else w3+=2; return 0;
		case 20: g--; w3--; return 0;
		case 21: cout<<"W3 leaving 2nd CS"<<endl; w3++; return 0;
		case 22: ws2--; w3++; return 0;
		case 23: lock = false; w3++; return 0;
		case 24: cout<<"W3 in NCS"<<endl; w3++; return 0;
	}
}
