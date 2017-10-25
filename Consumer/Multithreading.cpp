#include <iostream>
#include <windows.h>
#include <cstdlib>
using namespace std;



int in= 0;
int out = 0;
DWORD WINAPI consumer(LPVOID);
DWORD WINAPI producer(LPVOID);
HANDLE hthread[2];
DWORD id[2];
DWORD waiter;
static int count = 0;
static int limit;
static int buffersize;
DWORD WINAPI producer(LPVOID buf)
{
	int *buffer = (int *)buf;
	int in = 0;
	while(limit>=0)
	{
		while(count==buffersize);

		buffer[in] =rand() % 100 + 1;
		cout<<"Producer put in "<<buffer[in]<<endl;
		in = (in + 1) % buffersize;
		count++;
		limit--;

	}
	return 0;
}
DWORD WINAPI consumer(LPVOID buf)
{
int *buffer = (int *)buf;
int out = 0;

while(limit>=0)
{
while (count==0)
; // do nothing -- nothing to consume
// remove an item from the buffer

cout<< "consumer took out "<<buffer[out]<<endl;
count--;
limit--;
out = (out + 1) % buffersize;
}
return 0;

}

main()
{

	
	
	cout<<"Enter buffer size"<<endl;

	cin>>buffersize;
	int buffer[buffersize];
	cout<<"Enter counter limit"<<endl;
	cin>>limit;
	hthread[0] = CreateThread(NULL,0,producer,(LPVOID)buffer,NULL,&id[0]);
	hthread[1] = CreateThread(NULL,0,consumer,(LPVOID)buffer,NULL,&id[1]);
	
	waiter = WaitForMultipleObjects(2, hthread, TRUE, INFINITE); 
}
