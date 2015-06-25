// uncomment this if you are using windows/borland compiler
// #include <conio.h>
// #include <iostream.h>
// #include <stdlib.h>
// #include <stdio.h>

// remove this if you are using windows/borland compiler
#include<iostream>
#include <string.h>

typedef class Activity
{
    public:
        char Id[5];
    float durasi;
    int Est;
    int Lst;
    int Eet;
    int Let;
    struct Activity *Successors[100];
    // Predecessors adalah pendahulunya
    struct Activity *Predecessors[100];
}aktifitas;

int na,kritis;
aktifitas *List[100],*check,*check2, *activity;

void GetActivities();
void WalkListAhead();
void WalkListAback();
void CriticalPath();

int CheckActivity(char id[5], int i)
{
    for(int j = 0; j < i; j++)
    {
        if(strcmp(List[j]->Id,id) == 0)
            check=List[j];
   }
   return NULL;
}

int GetIndex(aktifitas *aux, int i)
{
	for(int j = 0; j < i; j++)
    {
        if(aux->Id==List[j]->Id)
      	    return j;
    }
   return 0;
}

int SetSuccessors(aktifitas *activity)
{
   int k=0;
   while (activity->Successors[k]!= NULL){
      k++;
   }
   return k;
}

// remove this if you are using windows/borland compiler
using namespace std;

int main ()
{
    char Key;
    do {
        List[0] = NULL;
        GetActivities();
        WalkListAhead();
        WalkListAback();
        CriticalPath();
        cout<<" lagi? y\\n: ";
        cin>>Key;
    } while(Key == 'y' || Key == 'Y');
}

void GetActivities()
{
    do {
        cout<<" Tugas Riset Operasi";
        cout<<"\n Inputkan banyaknya aktivitas: ";
        cin>>na;
        if(na < 2 )
            cout<<"\n Banyaknya activity harus lebih dari atau sama dengan 2.\n\n";
    } while(na < 2);

   for(int i = 0; i < na; i++)
   {
       activity = new (class Activity);
       activity->Predecessors[0]=NULL;
       activity->Successors[0]=NULL;
       cout<<"\n            Aktivitas "<<(i+1)<<"\n";
       cout<<"\n                     ID: ";
       cin>>activity->Id;
       cout<<"                 Durasi: ";
       cin>>activity->durasi;
       int np;
       cout<<"    Banyaknya pendahulu: ";
       cin>>np;
       List[i] = activity;
       if(np != 0) {
           char id[5];
           for(int j = 0; j < np; j++)
           {
               cout<<"    #"<<(j+1)<<"     pendahulu ID: ";
               cin>>id;
               activity->Predecessors[j] = new (class Activity);
               aktifitas *aux;
               aux =new (class Activity);
               int hasil;
               CheckActivity(id, i);
               if(check != NULL) {
                   activity->Predecessors[j] = check;
                   hasil = GetIndex(check, i);
                   int k = SetSuccessors(List[hasil]);
                   List[hasil]->Successors[k] = activity;
                } else {
                    cout<<"\n tidak cocok coba lagi.\n\n";
                    j--;
                }
            }
       } else {
           activity->Predecessors[0]=NULL;
       }

    }
}

void WalkListAhead()
{
    for(int i = 0; i < na; i++)
    {
        if(List[i]->Predecessors[0]==NULL) {
            List[i]->Est=0;
            List[i]->Eet=List[i]->durasi;
        } else {
            int k=0;
            List[i]->Est=0;
            while (List[i]->Predecessors[k]!=NULL) {
                if(List[i]->Est < List[i]->Predecessors[k]->Eet)
                    List[i]->Est = List[i]->Predecessors[k]->Eet;
                // cout<<List[i]->Est<<" "<<List[i]->Predecessors[k]->Eet<<endl;
                k++;
            }
            List[i]->Eet = List[i]->Est + List[i]->durasi;
        }
    }
}

void WalkListAback()
{
    int i;
    int max=List[0]->Eet;
    for(i=1;i<na;i++)
    {
        if(List[i]->Eet>max)
            max=List[i]->Eet;
    }
    kritis=max;
    int k=na-1;
    for(int i=k; i>=0; i--)
    {
        if(List[i]->Successors[0]!=NULL) {
            int k=0;
            List[i]->Let=List[i]->Successors[0]->Lst;
            while (List[i]->Successors[k]!=NULL) {
                if(List[i]->Let > List[i]->Successors[k]->Lst)
                    List[i]->Let = List[i]->Successors[k]->Lst;
                k++;
            }
            List[i]->Lst = List[i]->Let-List[i]->durasi;
        } else {
                List[i]->Let=max;
         List[i]->Lst=max-List[i]->durasi;
      }
   }
}

void CriticalPath()
{
    for(int i=0; i<na;i++)
    {
        cout<<"\n           Node "<<i<<" = "<<List[i]->Id;
        cout<<"\n           durasi "<<List[i]->durasi;
        cout<<"\n           ES = "<<List[i]->Est;
        cout<<"\n           EF = "<<List[i]->Eet;
        cout<<"\n           LS = "<<List[i]->Lst;
        cout<<"\n           LF = "<<List[i]->Let<<endl<<endl;
    }
    cout<<"\n          aktivitas kritis: ";
    cout<<endl;
    for(int i=0;i<na;i++)
    {
        if((List[i]->Eet - List[i]->Let) == 0 && (List[i]->Est - List[i]->Lst)== 0)
            cout<<"\t\t"<<List[i]->Id<<endl;
    }
    cout<<"\n\n         Total durasi: {0}\t\t"<<kritis;
}
