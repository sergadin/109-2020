#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#include <netdb.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>

#include "tdb_server.h"

//using namespace std;

int main(int argc, char *argv[])
{
    StudentsDB oSDB;

    int as, ms;
    int Res;
    int opt;
    struct sockaddr_in server;
    char buf[1024]; 
    char rec[1024]; 
    int i,j,k;

    as = socket(AF_INET, SOCK_STREAM, 0 ); 
    if(as < 0)
    {
        perror("socket");
        return 1;
    }

    server.sin_family = AF_INET; /* IP */
//    server.sin_addr.s_addr = INADDR_ANY; 
    server.sin_addr.s_addr = htonl(INADDR_ANY); 
    server.sin_port = htons(1234);

    opt = 1;
    if (setsockopt (as, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof (opt)) == -1) perror("setsockopt");
    Res=bind(as, (struct sockaddr *) &server, sizeof(server));
    if(Res < 0)
    {
        perror("bind");
        return 2;
    }

    Res=listen(as, 5);
    if(Res < 0)
    {
        perror("listener");
        return 3;
    }

    printf("\n");
    printf("\n 1-Read File");
    printf("\n 2-SaveFile");
    printf("\n 3-Print Base");
    printf("\n 4-Add Record");
    printf("\n 5-Delete Record");
    printf("\n 6-Find Record");
    printf("\n 7-Change Record");
    printf("\n 8-Exit");
    printf("\n");

    while( 1 ) {
        ms = accept( as, 0, 0 );
        bzero( buf, sizeof(buf));
//        read(ms, buf, sizeof(buf));
        recv(ms, buf, sizeof(buf), 0);
        printf("message is = %s\n", buf );
        if ( strcmp(buf, "1") == 0 )
        { 
          printf("FillIn\n");
          oSDB.Root=(TreeDataBase *)malloc(sizeof(TreeDataBase));
          oSDB.Root->LeftNode=0;
          oSDB.Root->RightNode=0;
          oSDB.Root->NodeNumber=0;
          oSDB.NodeCounter=200;
          oSDB.TreeLevel=0;
          if(oSDB.FillIn(oSDB.Root)!=0)return 1;
//          write(ms, "@Stop", 5 );
        }
        if ( strcmp(buf, "2") == 0 )
        {
          printf("SaveDB\n");
          unlink("students.tb");
          oSDB.SaveFile(oSDB.Root);
        } 
        if ( strcmp(buf, "3") == 0 )
        { 
          printf("PrintDB\n");
          oSDB.Print(oSDB.Root, ms);
          usleep(100000);
        }
        if(buf[0]=='4')
        {
          oSDB.NewStudent=(StudentsList *)malloc(sizeof(StudentsList));
          bzero(rec,sizeof(rec));
          j=0;k=0;
          for(i=3;i<=strlen(buf);i++)
          {
            if(buf[i]!=':')
            {
              rec[j]=buf[i];
              j++;
            }
            if(buf[i]==':')
            {
              if(k==0)
              {
                //oSDB.NewStudent->FIO=(char *)malloc(j+1);
   	        strcpy(oSDB.NewStudent->FIO,rec);
              }
              if(k==1)oSDB.NewStudent->Group=atoi(rec);
              if(k==2)oSDB.NewStudent->MiddleNumber=atoi(rec);
              bzero(rec,sizeof(rec));
              j=0;k++;
            }
          }
   	  printf("AddRecord: | %12s | %d | %d |\n",oSDB.NewStudent->FIO,oSDB.NewStudent->Group,oSDB.NewStudent->MiddleNumber);
          oSDB.AddRecord(oSDB.Root);
        }
        if ( buf[0]=='5' )
	{

          oSDB.DelRec=(StudentsList *)malloc(sizeof(StudentsList));
          bzero(rec,sizeof(rec));
          j=0;k=0;
          for(i=3;i<=strlen(buf);i++)
          {
            if(buf[i]!=':')
            {
              rec[j]=buf[i];
              j++;
            }
            if(buf[i]==':')
            {
              if(k==0)
              {
   	        strcpy(oSDB.DelRec->FIO,rec);
              }
              if(k==1)oSDB.DelRec->Group=atoi(rec);
              if(k==2)oSDB.DelRec->MiddleNumber=atoi(rec);
              bzero(rec,sizeof(rec));
              j=0;k++;
            }
          }
   	  printf("DeleteRecord: | %12s | %d | %d |\n",oSDB.DelRec->FIO,oSDB.DelRec->Group,oSDB.DelRec->MiddleNumber);
          oSDB.DeleteRecord(oSDB.Root);
          free(oSDB.DelRec);
        }
	if( buf[0]=='6' )
	{
          oSDB.FindRec=(StudentsList *)malloc(sizeof(StudentsList));
          bzero(rec,sizeof(rec));
          j=0;k=0;
          for(i=3;i<=strlen(buf);i++)
          {
            if(buf[i]!=':')
            {
              rec[j]=buf[i];
              j++;
            }
            if(buf[i]==':')
            {
              if(k==0)
              {
   	        strcpy(oSDB.FindRec->FIO,rec);
              }
              if(k==1)oSDB.FindRec->Group=atoi(rec);
              if(k==2)oSDB.FindRec->MiddleNumber=atoi(rec);
              bzero(rec,sizeof(rec));
              j=0;k++;
            }
          }
   	  printf("FindRecord: | %12s | %d | %d |\n",oSDB.FindRec->FIO,oSDB.FindRec->Group,oSDB.FindRec->MiddleNumber);
          oSDB.FindRecord(oSDB.Root,ms);
          free(oSDB.FindRec);
        }
	if( buf[0]=='7' )
	{
          oSDB.DelRec=(StudentsList *)malloc(sizeof(StudentsList));
          oSDB.NewStudent=(StudentsList *)malloc(sizeof(StudentsList));
          bzero(rec,sizeof(rec));
          j=0;k=0;
          for(i=4;i<=strlen(buf);i++)
          {
            if(buf[i]!=':')
            {
              rec[j]=buf[i];
              j++;
            }
            if(buf[i]==':')
            {
              if(k==0)
              {
   	        strcpy(oSDB.DelRec->FIO,rec);
              }
              if(k==1)oSDB.DelRec->Group=atoi(rec);
              if(k==2)oSDB.DelRec->MiddleNumber=atoi(rec);
              if(k==4)
              {
   	        strcpy(oSDB.NewStudent->FIO,rec);
              }
              if(k==5)oSDB.NewStudent->Group=atoi(rec);
              if(k==6)oSDB.NewStudent->MiddleNumber=atoi(rec);
              bzero(rec,sizeof(rec));
              j=0;k++;
            }
          }
          printf("ChangeRecord\n");
   	  printf("OldRecord: | %12s | %d | %d |\n",oSDB.DelRec->FIO,oSDB.DelRec->Group,oSDB.DelRec->MiddleNumber);
   	  printf("NewRecord: | %12s | %d | %d |\n",oSDB.NewStudent->FIO,oSDB.NewStudent->Group,oSDB.NewStudent->MiddleNumber);

          oSDB.ChangeRecord(oSDB.Root);
          free(oSDB.DelRec);
          free(oSDB.NewStudent);

        }

        usleep(10000);
//        write(ms, "@Stop", 5 );
        send(ms, "@Stop", 5, 0);
        close( ms );
        if ( strcmp(buf, "quit") == 0 ) break;
        if ( strcmp(buf, "8") == 0 ) break;
    }
    Res=close( as );
    if(Res < 0)
    {
        perror("close bind");
        return 4;
    }
    return 0;
}

int StudentsDB::FillIn(TreeDataBase *CurrentNode)
{
  TreeDataBase *NewNode;
  StudentsList *CurrentStudent,*NextStudent;
  FILE *Input;

  char ReadBuffer[256];
  char RecordBuffer[256];
  int i;

  if(NodeCounter<226)
  {
    if(CurrentNode->NodeNumber==0)
    {
      NodeCounter++;
      if(NodeCounter==213)NodeCounter=221;
      CurrentNode->NodeNumber=NodeCounter;

      if ((Input = fopen("students.tb", "rt"))== NULL)
      {
        fprintf(stderr, "Cannot open input file.\n");
        return 1;
      }

      CurrentNode->FirstStudent=CurrentStudent=(StudentsList *)malloc(sizeof(StudentsList));

      while(fgets(ReadBuffer,255,Input))
      {
        sprintf(RecordBuffer,"GROUP:%d",CurrentNode->NodeNumber);
        if(strstr(ReadBuffer,RecordBuffer)!=0)
        {
          strcpy(ReadBuffer,strstr(ReadBuffer,"FIO:")+4);
          for(i=0;i<=strlen(ReadBuffer);i++)
          {
            if(ReadBuffer[i]!=':')RecordBuffer[i]=ReadBuffer[i];
            if(ReadBuffer[i]==':')
            {
              RecordBuffer[i]='\0';break;
            }
          }
          //CurrentStudent->FIO=(char *)malloc(sizeof(RecordBuffer));
          strcpy(CurrentStudent->FIO,RecordBuffer);
          CurrentStudent->Group=CurrentNode->NodeNumber;

          strcpy(ReadBuffer,strstr(ReadBuffer,"MIDDLE:")+7);
          for(i=0;i<=strlen(ReadBuffer);i++)
          {
            if(ReadBuffer[i]!=';')RecordBuffer[i]=ReadBuffer[i];
            if(ReadBuffer[i]==';')
            {
              RecordBuffer[i]='\0';break;
            }
          }
          CurrentStudent->MiddleNumber=atoi(RecordBuffer);
          NextStudent=(StudentsList *)malloc(sizeof(StudentsList));
          CurrentStudent->NextPtr=NextStudent;
          CurrentStudent=NextStudent;
          CurrentStudent->Group=CurrentNode->NodeNumber;
          CurrentStudent->NextPtr=0;
        }
      }
      fclose(Input);
    }

    if(CurrentNode->LeftNode==0)
    {
      if(TreeLevel<4)
      {
        NewNode=(TreeDataBase *)malloc(sizeof(TreeDataBase));
        CurrentNode->LeftNode=NewNode;
        NewNode->LeftNode=0;
        NewNode->RightNode=0;
        NewNode->NodeNumber=0;
      }
      if(TreeLevel==4)
      {
        TreeLevel--;
        return 0;
      }
      TreeLevel++;
      FillIn(NewNode);
    }
    if(CurrentNode->RightNode==0)
    {
      if(TreeLevel<4)
      {
        NewNode=(TreeDataBase *)malloc(sizeof(TreeDataBase));
        CurrentNode->RightNode=NewNode;
        NewNode->LeftNode=0;
        NewNode->RightNode=0;
        NewNode->NodeNumber=0;
      }
      if(TreeLevel==4)
      {
        TreeLevel--;
        return 0;
      }
      TreeLevel++;
      FillIn(NewNode);
    }
  }
  TreeLevel--;

  return 0;
}

int StudentsDB::SaveFile(TreeDataBase *CurrentNode)
{
  int i;
  StudentsList *CurrentStudent;
  FILE *Input;

  if(CurrentNode->NodeNumber>200)
  {
    CurrentStudent=CurrentNode->FirstStudent;
    if ((Input = fopen("students.tb", "at"))== NULL)
    {
      fprintf(stderr, "Cannot open input file.\n");
      return 1;
    }
    for(i=0;i<=70;i++)
    {
      fprintf(Input,"%d:FIO:%s:GROUP:%d:MIDDLE:%d;\n",i+1,CurrentStudent->FIO,CurrentStudent->Group,CurrentStudent->MiddleNumber);
      CurrentStudent=CurrentStudent->NextPtr;
      if(CurrentStudent->NextPtr==0)break;
    }
    fclose(Input);
  }
  if(CurrentNode->LeftNode!=0)
  {
    SaveFile(CurrentNode->LeftNode);
  }
  else return 0;
  if(CurrentNode->RightNode!=0)
  {
    SaveFile(CurrentNode->RightNode);
  }
  else return 0;

  return 0;
}


void StudentsDB::Print(TreeDataBase *CurrentNode,int ms)
{
  int i;
  char Buff[255];
  StudentsList *CurrentStudent;

  if(CurrentNode->NodeNumber>200)
  {
    bzero( Buff, sizeof(Buff));
    sprintf(Buff,"GroupNumber: %d;\n",CurrentNode->NodeNumber);
//    write(ms, Buff, strlen(Buff) );
    send(ms, Buff, strlen(Buff), 0);
    CurrentStudent=CurrentNode->FirstStudent;
    for(i=0;i<=70;i++)
    {
      bzero( Buff, sizeof(Buff));
      sprintf(Buff,"| %12s | %d | %d |\n",CurrentStudent->FIO,CurrentStudent->Group,CurrentStudent->MiddleNumber);
//      write(ms, Buff, strlen(Buff) );
      send(ms, Buff, strlen(Buff), 0);
      CurrentStudent=CurrentStudent->NextPtr;
      if(CurrentStudent->NextPtr==0)break;
    }
  }
  if(CurrentNode->LeftNode!=0)
  {
    Print(CurrentNode->LeftNode,ms);
  }
  else return;
  if(CurrentNode->RightNode!=0)
  {
    Print(CurrentNode->RightNode,ms);
  }
  else return;

  return;
}


int StudentsDB::AddRecord(TreeDataBase *CurrentNode)
{
  int i;
  StudentsList *CurrentStudent;

  if(CurrentNode->NodeNumber>200)
  {
    CurrentStudent=CurrentNode->FirstStudent;
    for(i=0;i<=70;i++)
    {
      if(CurrentStudent->NextPtr==0)
      {
        if(CurrentStudent->Group==NewStudent->Group)
        {
          strcpy(CurrentStudent->FIO,NewStudent->FIO);
          CurrentStudent->Group=NewStudent->Group;
          CurrentStudent->MiddleNumber=NewStudent->MiddleNumber;
          CurrentStudent->NextPtr=NewStudent=(StudentsList *)malloc(sizeof(StudentsList));
          CurrentStudent=NewStudent;
          CurrentStudent->Group=CurrentNode->NodeNumber;
          CurrentStudent->NextPtr=0;
        }
        break;
      }
      CurrentStudent=CurrentStudent->NextPtr;
    }
  }
  if(CurrentNode->LeftNode!=0)
  {
    AddRecord(CurrentNode->LeftNode);
  }
  else return 0;
  if(CurrentNode->RightNode!=0)
  {
    AddRecord(CurrentNode->RightNode);
  }
  else return 0;

  return 0;
}

void StudentsDB::DeleteRecord(TreeDataBase *CurrentNode)
{
  int i;
  StudentsList *PrevStudent,*CurrentStudent;

  if(CurrentNode->NodeNumber==DelRec->Group)
  {
    CurrentStudent=CurrentNode->FirstStudent;
    for(i=0;i<=70;i++)
    {
      if(strcmp(CurrentStudent->FIO,DelRec->FIO)==0&&CurrentStudent->MiddleNumber==DelRec->MiddleNumber)
      {
printf("Deleting: | %12s | %d | %d |\n",CurrentStudent->FIO,CurrentStudent->Group,CurrentStudent->MiddleNumber);
        if(i==0)
        {
          CurrentNode->FirstStudent=CurrentStudent->NextPtr;
          free(CurrentStudent);
          CurrentStudent=CurrentNode->FirstStudent;
        }
        if(i>0)
        {
          PrevStudent->NextPtr=CurrentStudent->NextPtr;
          free(CurrentStudent);
          CurrentStudent=PrevStudent;
        }
      }
      PrevStudent=CurrentStudent;
      CurrentStudent=CurrentStudent->NextPtr;
      if(CurrentStudent->NextPtr==0)break;
    }
  }
  if(CurrentNode->LeftNode!=0)
  {
    DeleteRecord(CurrentNode->LeftNode);
  }
  else return;
  if(CurrentNode->RightNode!=0)
  {
    DeleteRecord(CurrentNode->RightNode);
  }
  else return;

  return;
}

void StudentsDB::FindRecord(TreeDataBase *CurrentNode,int ms)
{
  int i;
  char Buff[255];
  StudentsList *CurrentStudent;

  if(CurrentNode->NodeNumber==FindRec->Group)
  {
    CurrentStudent=CurrentNode->FirstStudent;
    for(i=0;i<=70;i++)
    {
      if(strcmp(CurrentStudent->FIO,FindRec->FIO)==0&&CurrentStudent->MiddleNumber==FindRec->MiddleNumber)
      {
       	sprintf(Buff,"Find Result: | %12s | %d | %d |\n",CurrentStudent->FIO,CurrentStudent->Group,CurrentStudent->MiddleNumber);
        send(ms, Buff, strlen(Buff), 0);
      }
      CurrentStudent=CurrentStudent->NextPtr;
      if(CurrentStudent->NextPtr==0)break;
    }
  }
  if(CurrentNode->LeftNode!=0)
  {
    FindRecord(CurrentNode->LeftNode,ms);
  }
  else return;
  if(CurrentNode->RightNode!=0)
  {
    FindRecord(CurrentNode->RightNode,ms);
  }
  else return;

  return;
}

void StudentsDB::ChangeRecord(TreeDataBase *CurrentNode)
{
  char Buffer[100];
  int i,Key;
  StudentsList *CurrentStudent;

  if(CurrentNode->NodeNumber==DelRec->Group)
  {
    CurrentStudent=CurrentNode->FirstStudent;
    for(i=0;i<=70;i++)
    {
      if(strcmp(CurrentStudent->FIO,DelRec->FIO)==0&&CurrentStudent->MiddleNumber==DelRec->MiddleNumber)
      {
printf("Changing: | %12s | %d | %d |\n",CurrentStudent->FIO,CurrentStudent->Group,CurrentStudent->MiddleNumber);
        strcpy(CurrentStudent->FIO,NewStudent->FIO);
        CurrentStudent->Group=NewStudent->Group;
        CurrentStudent->MiddleNumber=NewStudent->MiddleNumber;
      }
      CurrentStudent=CurrentStudent->NextPtr;
      if(CurrentStudent->NextPtr==0)break;
    }
  }
  if(CurrentNode->LeftNode!=0)
  {
    ChangeRecord(CurrentNode->LeftNode);
  }
  else return;
  if(CurrentNode->RightNode!=0)
  {
    ChangeRecord(CurrentNode->RightNode);
  }
  else return;

  return;
}
