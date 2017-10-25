#include <iostream>
using namespace std;
#include <cstdlib> 

main()
{
      int num = 50;
      int reference[num], framecount=0, listcount =0, pagefault = 0;
      bool hit = false;
      for(int r = 0; r<num; r++)
              reference[r] = rand()%10;
      int x = rand()%7+1;
      int frame[x];
      for(int r = 0; r<x; r++)
              frame[r] = 0;
      while(listcount<num)
      {
                 for(int r = 0; r<x; r++)
                 {
                         if(frame[r] == reference[listcount])
                                     hit = true;
                 }
                 if(hit ==false)
                 {
                        frame[framecount] = reference[listcount];
                        framecount= (framecount+1)%x;
                         pagefault++;
                   }
                
                 
                 hit = false;
                 listcount++;
      }
cout<<"With "<<x<<" frames, there were "<<pagefault<<" page faults"<<endl;
system("pause");
}
