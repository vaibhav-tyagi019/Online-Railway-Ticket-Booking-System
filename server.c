# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/file.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <strings.h>
# include <string.h>
# include <fcntl.h>
# include <pthread.h>
# include <sys/stat.h>  
  
     struct sockaddr_in server,client;
        int sd,sz,nsd,nar,nat,nab,naj;
        
        struct normal_user
        {
           int id;
           char password[80];
           char name[80];
        };
        
        struct train_info
          {
            int train_no;
            char train_name[80];
            char from[80];
            char destn[80];
            char reaching_time[80];
            char start_time[80];
            int no_of_tickets;
          };
        
        struct ticket_info
        {
           int id;
           int train_no;
           int seatNo;
           char trainName[80];
           char status[80];
        };
        
        struct agent_account
        {
           int id;
           char userName1[80];
           char password1[80];
           char userName2[80];
           char password2[80];
        };
        
        
  void normalLoginS();
  void newNormalAccountS();
  void normalUserOptionMenuS();
  void adminLoginS();
  void newTrainS();
  void searchTrainS();
  void modifyTrainS();
  void deleteTrainS();
  void searchNormalAccountS();
  void modifyNormalAccountS();
  void deleteNormalAccountS();
  void bookTicketS();
  void viewPreviousBookingS();
  void updateBookingS();
  void cancelBookingS();
  void newAgentAccountS();
  void deleteAgentAccountS();
  void modifyAgentAccountS();
  void searchAgentAccountS();
  void agentLoginS();
  void agentOptionMenuS();
  void agentBookTicketS();
  void agentViewPreviousBookingS();
  void agentUpdateBookingS();
  void agentCancelBookingS();
     
        
  void loginPageS()
  {
       int input;
       read(nsd, &input, sizeof(input));

       switch(input){

        case 1:
            
            normalLoginS();
            break;
        case 2:
            
            agentLoginS();
            break;
        case 3:
            
            adminLoginS();
            break;
        case 4:
            newNormalAccountS();
            break;
        case 5:
            newAgentAccountS();        
        default:
            close(nsd);
            exit(EXIT_SUCCESS);
    }
  }
  
  void adminLoginS()
  {
     int input,id;
     char pwd[80];
     
     read(nsd,&id,sizeof(int));
     read(nsd,pwd,sizeof(pwd));
     
     int output=0;
     if(id==0 && (strcmp(pwd,"admin")==0))
     output=1;
     
     write(nsd,&output,sizeof(int));
     
     if(output)
     {
     read(nsd,&input,sizeof(int));
     
     switch(input)
        {
           case 1:
                  newNormalAccountS();
                  break;
                  
           case 2:
                  deleteNormalAccountS();
                  break;
           
           case 3:
                  modifyNormalAccountS();
                  break; 
           
           case 4:
                  searchNormalAccountS();
                  break;
           
           case 5:
                  newTrainS();
                  break; 
           
           case 6:
                  deleteTrainS();
                  break;        
           case 7:
                  modifyTrainS();
                  break; 
           case 8:
                  searchTrainS();
                  break;  
                                    
           case 9:
                  newAgentAccountS();
                  break;
           
           case 10:
                  deleteAgentAccountS();
                  break;
           
           case 11:
                  modifyAgentAccountS();
                  break;
           
           case 12:
                  searchAgentAccountS();
                   break;                        
                      
           default:
                  loginPageS();
                                             
        }
      }
      else
        loginPageS();
  }
  
  void agentLoginS()
  {
     int id;
    char pwd[80];
    struct agent_account c;
    read(nsd,&id,sizeof(int));
    read(nsd,pwd,sizeof(pwd));
    
    int output=0;
    lseek(naj, 0, SEEK_SET);
    while(read(naj, &c, sizeof(struct agent_account)) > 0)
    {

        if(id == c.id && (strcmp(pwd, c.password1)==0))
        {
                
                output = 1;
                break;
         }
        
        else if(id==c.id && (strcmp(pwd,c.password2)==0))
        {
                output=2;
                break;
        } 
         
    }
    write(nsd, &output, sizeof(int));
    if(output==1)
    {
        char buff[80];
        strcpy(buff,c.userName1);
        write(nsd,buff,sizeof(buff));
        agentOptionMenuS(id);
    } 
    else if(output==2)
    {
       char buff[80];
        strcpy(buff,c.userName2);
        write(nsd,buff,sizeof(buff));
        agentOptionMenuS(id);
    }
    else
     loginPageS();
  }
  
  void agentOptionMenuS(int id)
  {
     int input;
     read(nsd,&input,sizeof(int));
     
     switch(input)
          {
             case 1:
                   agentBookTicketS(id);
                   break;
             
             case 2:
                   agentViewPreviousBookingS(id);
                   break;
             
             case 3:
                   agentUpdateBookingS(id);
                   break;
             
             case 4:
                   agentCancelBookingS(id);
                   break;
             
             default:
                      loginPageS();
                                                 
          }
  }
  
  void agentBookTicketS(int id)
  {
      
      struct flock lock;
      lock.l_type=F_WRLCK;
      lock.l_whence=SEEK_SET;
      lock.l_start=0;
      lock.l_len=0;
      fcntl(nat,F_SETLKW,&lock);
      fcntl(nab,F_SETLKW,&lock);
      struct train_info c;
       int a=1;
       lseek(nat,0,SEEK_SET);
       
       while( read(nat,&c,sizeof(struct train_info))>0)
       {
            write(nsd,&a,sizeof(int));
            write(nsd,&c,sizeof(struct train_info));
       }
       a=0;
       write(nsd,&a,sizeof(int));
       int count;
       read(nsd,&count,sizeof(int));
       if(count==0)
       {
        lock.l_type=F_UNLCK;
        fcntl(nat,F_SETLK,&lock);
        fcntl(nab,F_SETLK,&lock);
        loginPageS();
       }
       else
       {
       int train_no;
       read(nsd,&train_no,sizeof(int));
       lseek(nat,0,SEEK_SET);
       struct train_info c1;
       int flag=0;
       while( read(nat,&c1,sizeof(struct train_info))>0)
       {
            if(c1.train_no==train_no)
            {
              flag=1;
              break;
            }
       }
       
       write(nsd,&flag,sizeof(int));
       if(flag==0)
       {
        lock.l_type=F_UNLCK;
        fcntl(nat,F_SETLK,&lock);
        fcntl(nab,F_SETLK,&lock);
        loginPageS();
       }
       else
       {
       int output;
       if(c1.no_of_tickets<=0)
       {
         output=-2;
         write(nsd,&output,sizeof(int));
         lock.l_type=F_UNLCK;
         fcntl(nat,F_SETLK,&lock);
         fcntl(nab,F_SETLK,&lock);
         loginPageS();
       }
       else
       {
         lseek(nat,-1*sizeof(struct train_info),SEEK_CUR);
         //int no_of_ticket_booked=101-c1.no_of_tickets;
         c1.no_of_tickets--;
         write(nat,&c1,sizeof(struct train_info));
         
         lseek(nab,0,SEEK_SET);
         int max[101];
         memset(max,0,101);
         struct ticket_info e;
         while( read(nab,&e,sizeof(struct ticket_info))>0)
             {
                    if(e.train_no==train_no && strcmp(e.status,"CONFIRMED")==0)
                    max[e.seatNo]=1;
             }
             int i;
             for(i=1;i<=100;i++)
             {
                if(max[i]==0)
                break;
             }
         
         
         lseek(nab,0,SEEK_END);
         struct ticket_info d;
         d.id=id;
         d.train_no=c1.train_no;
         d.seatNo=i;
         strcpy(d.trainName,c1.train_name);
         strcpy(d.status,"CONFIRMED");
         output=write(nab,&d,sizeof(struct ticket_info));
         write(nsd,&output,sizeof(int));
         if(output!=-1)
         write(nsd,&i,sizeof(int));
         lock.l_type=F_UNLCK;
         fcntl(nat,F_SETLK,&lock);
         fcntl(nab,F_SETLK,&lock);
         loginPageS();
       }
       }
       }
  }
  
  
  void agentUpdateBookingS(int id)
  {
         struct flock lock;
         lock.l_type=F_WRLCK;
         lock.l_start=0;
         lock.l_whence=SEEK_SET;
         lock.l_len=0;
         fcntl(nab,F_SETLKW,&lock);
         int train_no;
         struct ticket_info c;
         read(nsd,&train_no,sizeof(int));
         lseek(nab,0,SEEK_SET);
         
         int old_seat;
         int new_seat;
         int output=0;
         while( read(nab,&c,sizeof(struct ticket_info))>0)
         {
           if(c.id==id && c.train_no==train_no)
           {
             output=1;
             break;
           }
         }
         write(nsd,&output,sizeof(int));
         if(output==0)
         {
           lock.l_type=F_UNLCK;
           fcntl(nab,F_SETLK,&lock);
           loginPageS();
         }
         else
         {
           //old_seat==c.seatNo;
           lseek(nab,0,SEEK_SET);
           int max[101];
           memset(max,0,101);
           
           while( read(nab,&c,sizeof(struct ticket_info))>0)
           {
                 if(c.train_no==train_no && c.id!=-1 && strcmp(c.status,"CONFIRMED")==0)
                 max[c.seatNo]=1;
           }
           int i;
           for(i=100;i>0;i--)
           {
               if(max[i]==0)
               break;
           }
           new_seat=i;
           lseek(nab,0,SEEK_SET);
           while( read(nab,&c,sizeof(struct ticket_info))>0)
          {
           if(c.id==id && c.train_no==train_no)
           {
             
             break;
           }
          }
          old_seat=c.seatNo;
          c.seatNo=new_seat;
          lseek(nab,-1*sizeof(struct ticket_info),SEEK_CUR);
          write(nab,&c,sizeof(struct ticket_info));
          write(nsd,&old_seat,sizeof(int));
          write(nsd,&new_seat,sizeof(int));
          lock.l_type=F_UNLCK;
          fcntl(nab,F_SETLK,&lock);
          loginPageS();
         }
  }
  
  
  void agentViewPreviousBookingS(int id)
  {
      struct flock lock;
      lock.l_type=F_RDLCK;
      lock.l_whence=SEEK_SET;
      lock.l_start=0;
      lock.l_len=0;
      
      fcntl(nab,F_SETLKW,&lock);
      
      
      struct ticket_info c;
       int output=1;
       lseek(nab,0,SEEK_SET);
       while( read(nab,&c,sizeof(struct ticket_info))>0)
       {
           write(nsd,&output,sizeof(int));
           write(nsd,&c,sizeof(struct ticket_info));
       }
       output=0;
       write(nsd,&output,sizeof(int));
       lock.l_type=F_UNLCK;
       fcntl(nab,F_SETLK,&lock);
       loginPageS(); 
  }
  
  void agentCancelBookingS(int id)
  {
      
      struct flock lock;
      lock.l_type=F_WRLCK;
      lock.l_whence=SEEK_SET;
      lock.l_start=0;
      lock.l_len=0;
      
      fcntl(nab,F_SETLKW,&lock);
      fcntl(nat,F_SETLKW,&lock);
      
      int train_no;
     read(nsd,&train_no,sizeof(int));
     lseek(nab,0,SEEK_SET);
     
     struct ticket_info c;
     int flag=0;
     while( read(nab,&c,sizeof(struct ticket_info))>0)
     {
         if(c.id==id && c.train_no==train_no && strcmp(c.status,"CONFIRMED")==0)
         {
           flag=1;
           break;
         }
     }
     
     write(nsd,&flag,sizeof(int));
     if(flag==0)
     {
       lock.l_type=F_UNLCK;
       fcntl(nab,F_SETLK,&lock);
       fcntl(nat,F_SETLK,&lock);
       loginPageS();
     }
     else
     {
        
        lseek(nab,-1*sizeof(struct ticket_info),SEEK_CUR);
        strcpy(c.status,"CANCELLED");
        write(nab,&c,sizeof(struct ticket_info));
        struct train_info d;
        lseek(nat,0,SEEK_SET);
        while ( read(nat,&d,sizeof(struct train_info))>0)
        {
           if(d.train_no==train_no)
            break;
        }
        lseek(nat,-1*sizeof(struct train_info),SEEK_CUR);
        d.no_of_tickets++;
        write(nat,&d,sizeof(struct train_info));
        lock.l_type=F_UNLCK;
        fcntl(nab,F_SETLK,&lock);
        fcntl(nat,F_SETLK,&lock);
        loginPageS();
     }
  }
  
  
  
  
  void newTrainS()
  {
     struct train_info c;
     
     read(nsd,&c.train_no,sizeof(int));
     read(nsd,c.train_name,sizeof(c.train_name));
     read(nsd,c.from,sizeof(c.from));
     read(nsd,c.destn,sizeof(c.destn));
     read(nsd,c.start_time,sizeof(c.start_time));
     read(nsd,c.reaching_time,sizeof(c.reaching_time));
     read(nsd,&c.no_of_tickets,sizeof(int));
     
     lseek(nat,0,SEEK_END);
     int a=write(nat,&c,sizeof(struct train_info));
     int output=0;
     if(a!=-1)
     output=1;
     write(nsd,&output,sizeof(int));
     
     loginPageS();
  }
  
  void modifyTrainS()
  {
    int train_no,output=0,input;
    struct train_info c;
    read(nsd,&train_no,sizeof(int));
    
    lseek(nat, 0, SEEK_SET);
    
    while(read(nat, &c, sizeof(struct train_info)) > 0)
    {

        if(train_no== c.train_no)
        {
                
                output = 1;
                break;
         }  
    }
    write(nsd, &output, sizeof(int));
    if(!output)
     loginPageS();
    else
    {
        read(nsd,&input,sizeof(int));
        
        switch(input)
        {
           case 1:
                   {
                     char buff[80];
                     read(nsd,buff,sizeof(buff));
                     strcpy(c.train_name,buff);
                     lseek(nat,-1*sizeof(struct train_info),SEEK_CUR);
                     int a=write(nat,&c,sizeof(struct train_info));
                     int output=0;
                     if(a!=-1)
                     output=1;
                     write(nsd,&output,sizeof(int));
                     break;  
                   } 
           case 2:
                   {
                     char buff[80];
                     read(nsd,buff,sizeof(buff));
                     strcpy(c.from,buff);
                     lseek(nat,-1*sizeof(struct train_info),SEEK_CUR);
                     int a=write(nat,&c,sizeof(struct train_info));
                     int output=0;
                     if(a!=-1)
                     output=1;
                     write(nsd,&output,sizeof(int));
                     break;  
                   } 
           case 3:
                   {
                     char buff[80];
                     read(nsd,buff,sizeof(buff));
                     strcpy(c.destn,buff);
                     lseek(nat,-1*sizeof(struct train_info),SEEK_CUR);
                     int a=write(nat,&c,sizeof(struct train_info));
                     int output=0;
                     if(a!=-1)
                     output=1;
                     write(nsd,&output,sizeof(int));
                     break;  
                   }  
           case 4:
                   {
                     char buff[80];
                     read(nsd,buff,sizeof(buff));
                     strcpy(c.start_time,buff);
                     lseek(nat,-1*sizeof(struct train_info),SEEK_CUR);
                     int a=write(nat,&c,sizeof(struct train_info));
                     int output=0;
                     if(a!=-1)
                     output=1;
                     write(nsd,&output,sizeof(int));
                     break; 
                   } 
           case 5:
                   {
                     char buff[80];
                     read(nsd,buff,sizeof(buff));
                     strcpy(c.reaching_time,buff);
                     lseek(nat,-1*sizeof(struct train_info),SEEK_CUR);
                     int a=write(nat,&c,sizeof(struct train_info));
                     int output=0;
                     if(a!=-1)
                     output=1;
                     write(nsd,&output,sizeof(int));
                     break; 
                   } 
           default:
                   loginPageS();
                                                                    
                   
        }
        loginPageS();
    } 
  }
  
  
  void deleteTrainS()
  {
    int train_no,output=0;
    read(nsd,&train_no,sizeof(int));
    struct train_info c;
    lseek(nat, 0, SEEK_SET);
    while(read(nat, &c, sizeof(struct train_info)) > 0)
    {

        if(train_no== c.train_no)
        {
                
                output = 1;
                break;
         }  
    }
    write(nsd, &output, sizeof(int));
    if(output)
    {
        c.train_no=-1;
        lseek(nat,-1*(sizeof(struct train_info)),SEEK_CUR);
        write(nat,&c,sizeof(struct train_info));
        loginPageS();
    } 
    else
     loginPageS();
  }
  
  
  void searchTrainS()
  {
    int train_no;
    struct train_info c;
    read(nsd,&train_no,sizeof(int));
    int output=0;
    lseek(nat, 0, SEEK_SET);
    while(read(nat, &c, sizeof(struct train_info)) > 0)
    {

        if(train_no== c.train_no)
        {
                
                output = 1;
                break;
         }  
    }
    write(nsd, &output, sizeof(int));
    if(output!=0)
    {
        write(nsd,&c,sizeof(struct train_info));
        loginPageS();
    } 
    else
     loginPageS();
    
  }
  
  
  void normalLoginS()
  {
    int id;
    char pwd[80];
    struct normal_user c;
    read(nsd,&id,sizeof(int));
    read(nsd,pwd,sizeof(pwd));
    
    int output=0;
    lseek(nar, 0, SEEK_SET);
    while(read(nar, &c, sizeof(struct normal_user)) > 0)
    {

        if(id == c.id && (strcmp(pwd, c.password)==0))
        {
                
                output = 1;
                break;
         }
                
            
        
    }
    write(nsd, &output, sizeof(int));
    if(output!=0)
    {
        char buff[80];
        strcpy(buff,c.name);
        write(nsd,buff,sizeof(buff));
        normalUserOptionMenuS(id);
    } 
    else
     loginPageS();
  }
  
   void normalUserOptionMenuS(int id)
   {
     int input;
     read(nsd,&input,sizeof(int));
     
     switch(input)
          {
             case 1:
                   bookTicketS(id);
                   break;
             
             case 2:
                   viewPreviousBookingS(id);
                   break;
             
             case 3:
                   updateBookingS(id);
                   break;
             
             case 4:
                   cancelBookingS(id);
                   break;
             
             default:
                      loginPageS();
                                                 
          }
   }
   
   void bookTicketS(int id)
   {
       struct flock lock;
       lock.l_type=F_WRLCK;
       lock.l_whence=SEEK_SET;
       lock.l_start=0;
       lock.l_len=0;
       fcntl(nat,F_SETLKW,&lock);
       fcntl(nab,F_SETLKW,&lock);
       struct train_info c;
       int a=1;
       lseek(nat,0,SEEK_SET);
       
       while( read(nat,&c,sizeof(struct train_info))>0)
       {
            write(nsd,&a,sizeof(int));
            write(nsd,&c,sizeof(struct train_info));
       }
       a=0;
       write(nsd,&a,sizeof(int));
       int count;
       read(nsd,&count,sizeof(int));
       if(count==0)
       {
       lock.l_type=F_UNLCK;
       fcntl(nat,F_SETLK,&lock);
       fcntl(nab,F_SETLK,&lock);
       loginPageS();
       }
       else
       {
       int train_no;
       read(nsd,&train_no,sizeof(int));
       lseek(nat,0,SEEK_SET);
       struct train_info c1;
       int flag=0;
       while( read(nat,&c1,sizeof(struct train_info))>0)
       {
            if(c1.train_no==train_no)
            {
              flag=1;
              break;
            }
       }
       
       write(nsd,&flag,sizeof(int));
       if(flag==0)
       {
        lock.l_type=F_UNLCK;
        fcntl(nat,F_SETLK,&lock);
        fcntl(nab,F_SETLK,&lock);
        loginPageS();
       }
       else
       {
       int output;
       if(c1.no_of_tickets<=0)
       {
         output=-2;
         write(nsd,&output,sizeof(int));
         lock.l_type=F_UNLCK;
         fcntl(nat,F_SETLK,&lock);
         fcntl(nab,F_SETLK,&lock);
         loginPageS();
       }
       else
       {
         lseek(nat,-1*sizeof(struct train_info),SEEK_CUR);
         //int no_of_ticket_booked=101-c1.no_of_tickets;
         c1.no_of_tickets--;
         write(nat,&c1,sizeof(struct train_info));
         
         lseek(nab,0,SEEK_SET);
         int max[101];
         memset(max,0,101);
         struct ticket_info e;
         while( read(nab,&e,sizeof(struct ticket_info))>0)
             {
                    if(e.id!=-1 && e.train_no==train_no && strcmp(e.status,"CONFIRMED")==0)
                    max[e.seatNo]=1;
             }
             int i;
             for(i=1;i<=100;i++)
             {
                if(max[i]==0)
                break;
             }
         
         
         lseek(nab,0,SEEK_END);
         struct ticket_info d;
         d.id=id;
         d.train_no=c1.train_no;
         d.seatNo=i;
         strcpy(d.trainName,c1.train_name);
         strcpy(d.status,"CONFIRMED");
         output=write(nab,&d,sizeof(struct ticket_info));
         write(nsd,&output,sizeof(int));
         if(output!=-1)
         write(nsd,&i,sizeof(int));
         lock.l_type=F_UNLCK;
         fcntl(nat,F_SETLK,&lock);
         fcntl(nab,F_SETLK,&lock);
         loginPageS();
       }
       }
       }
   }
   
   
   void updateBookingS(int id)
   {
         struct flock lock;
         lock.l_type=F_WRLCK;
         lock.l_whence=SEEK_SET;
         lock.l_len=0;
         lock.l_len=0;
         fcntl(nab,F_SETLKW,&lock);
         int train_no;
         struct ticket_info c;
         read(nsd,&train_no,sizeof(int));
         lseek(nab,0,SEEK_SET);
         
         int old_seat;
         int new_seat;
         int output=0;
         while( read(nab,&c,sizeof(struct ticket_info))>0)
         {
           if(c.id==id && c.train_no==train_no)
           {
             output=1;
             break;
           }
         }
         write(nsd,&output,sizeof(int));
         if(output==0)
         {
           lock.l_type=F_UNLCK;
           fcntl(nab,F_SETLK,&lock);
           loginPageS();
         }
         else
         {
           //old_seat==c.seatNo;
           lseek(nab,0,SEEK_SET);
           int max[101];
           memset(max,0,101);
           
           while( read(nab,&c,sizeof(struct ticket_info))>0)
           {
                 if(c.train_no==train_no && c.id!=-1 && strcmp(c.status,"CONFIRMED")==0)
                 max[c.seatNo]=1;
           }
           int i;
           for(i=100;i>0;i--)
           {
               if(max[i]==0)
               break;
           }
           new_seat=i;
           lseek(nab,0,SEEK_SET);
           while( read(nab,&c,sizeof(struct ticket_info))>0)
          {
           if(c.id==id && c.train_no==train_no)
           {
             
             break;
           }
          }
          old_seat=c.seatNo;
          c.seatNo=new_seat;
          lseek(nab,-1*sizeof(struct ticket_info),SEEK_CUR);
          write(nab,&c,sizeof(struct ticket_info));
          write(nsd,&old_seat,sizeof(int));
          write(nsd,&new_seat,sizeof(int));
          lock.l_type=F_UNLCK;
          fcntl(nab,F_SETLK,&lock);
          loginPageS();
         }
   }
   
   
   void newNormalAccountS()
   {
   
       struct normal_user cust;
       read(nsd, &cust, sizeof(struct normal_user));
       
       lseek(nar, 0, SEEK_END);
       int a=write(nar, &cust, sizeof(struct normal_user));
      
       int output=0;
       if(a!=-1)
       output=1;
       write(nsd,&output,sizeof(int));
       loginPageS();
    }
   
   
   void searchNormalAccountS()
   {
       int id,output=0;
       read(nsd,&id,sizeof(int));
       struct normal_user c;
       lseek(nar,0,SEEK_SET);
       while(read(nar,&c,sizeof(struct normal_user))>0)
       {
            if(c.id==id)
            {
              output=1;
              break;
            }
       }
       
       write(nsd,&output,sizeof(int));
       if(output)
       {
          write(nsd,&c,sizeof(struct normal_user));
          loginPageS();
       }
       else
        loginPageS();
   }
  
   void modifyNormalAccountS()
   {
       int id;
       read(nsd,&id,sizeof(int));
       
       struct normal_user c;
       int output=0;
       lseek(nar,0,SEEK_SET);
       while( read(nar,&c,sizeof(struct normal_user)) >0)
       {
             if(c.id==id)
             {
               output=1;
               break;
             }  
       }
       
       write(nsd,&output,sizeof(int));
       if(!output)
       {
        loginPageS();
       }
       else
       {
           int input;
           read(nsd,&input,sizeof(int));
           
           switch(input)
           {
              case 1:
                      {
                      char buff[80];
                      read(nsd,buff,sizeof(buff));
                      strcpy(c.name,buff);
                      lseek(nar,-1*sizeof(struct normal_user),SEEK_CUR);
                      int a=write(nar,&c,sizeof(struct normal_user));
                      int output=0;
                      if(a!=-1)
                      output=1;
                      write(nsd,&output,sizeof(int));
                      break; 
                      }
              case 2:
                      {
                      char buff[80];
                      read(nsd,buff,sizeof(buff));
                      strcpy(c.password,buff);
                      lseek(nar,-1*sizeof(struct normal_user),SEEK_CUR);
                      int a=write(nar,&c,sizeof(struct normal_user));
                      int output=0;
                      if(a!=-1)
                      output=1;
                      write(nsd,&output,sizeof(int));
                      break; 
                      }
              default: 
                      loginPageS();                        
           }
           loginPageS();
       }
   }
   
   void deleteNormalAccountS()
   {
         int id;
         read(nsd,&id,sizeof(int));
         
         struct normal_user c;
         int output=0;
         lseek(nar,0,SEEK_SET);
         while( read(nar,&c,sizeof(struct normal_user)) >0)
        {
             if(c.id==id)
             {
               output=1;
               break;
             }  
        }
       
       write(nsd,&output,sizeof(int));
       if(!output)
       {
        loginPageS();
       }
       else
       {
          c.id=-1;
          lseek(nar,-1*(sizeof(struct normal_user)),SEEK_CUR);
          int a=write(nar,&c,sizeof(struct normal_user));
          int output;
          if(a!=-1)
          output=1;
          write(nsd,&output,sizeof(int));
          loginPageS();
       }
         
   }
   
   void viewPreviousBookingS(int id)
   {
       struct ticket_info c;
       int output=1;
       lseek(nab,0,SEEK_SET);
       while( read(nab,&c,sizeof(struct ticket_info))>0)
       {
           write(nsd,&output,sizeof(int));
           write(nsd,&c,sizeof(struct ticket_info));
       }
       output=0;
       write(nsd,&output,sizeof(int));
       loginPageS(); 
   }
   
   void cancelBookingS(int id)
   {
      struct flock lock;
       lock.l_type=F_WRLCK;
       lock.l_whence=SEEK_SET;
       lock.l_start=0;
       lock.l_len=0;
       fcntl(nat,F_SETLKW,&lock);
       fcntl(nab,F_SETLKW,&lock);
     int train_no;
     read(nsd,&train_no,sizeof(int));
     lseek(nab,0,SEEK_SET);
     
     struct ticket_info c;
     int flag=0;
     while( read(nab,&c,sizeof(struct ticket_info))>0)
     {
         if(c.id==id && c.train_no==train_no && strcmp(c.status,"CONFIRMED")==0)
         {
           flag=1;
           break;
         }
     }
     
     write(nsd,&flag,sizeof(int));
     if(flag==0)
     {
       lock.l_type=F_UNLCK;
       fcntl(nat,F_SETLK,&lock);
       fcntl(nab,F_SETLK,&lock);
       loginPageS();
     }
     else
     {
        
        lseek(nab,-1*sizeof(struct ticket_info),SEEK_CUR);
        strcpy(c.status,"CANCELLED");
        write(nab,&c,sizeof(struct ticket_info));
        struct train_info d;
        lseek(nat,0,SEEK_SET);
        while ( read(nat,&d,sizeof(struct train_info))>0)
        {
           if(d.train_no==train_no)
            break;
        }
        lseek(nat,-1*sizeof(struct train_info),SEEK_CUR);
        d.no_of_tickets++;
        write(nat,&d,sizeof(struct train_info));
        lock.l_type=F_UNLCK;
        fcntl(nat,F_SETLK,&lock);
        fcntl(nab,F_SETLK,&lock);
        loginPageS();
     }
   }
   
   
   void newAgentAccountS()
   {
       struct agent_account c;
       read(nsd,&c,sizeof(struct agent_account));
       
       lseek(naj,0,SEEK_END);
       int a=write(naj,&c,sizeof(struct agent_account));
       
       write(nsd,&a,sizeof(int));
       loginPageS();
   }
   
   void deleteAgentAccountS()
   {
        int id;
         read(nsd,&id,sizeof(int));
         
         struct agent_account c;
         int output=0;
         lseek(naj,0,SEEK_SET);
         while( read(naj,&c,sizeof(struct agent_account)) >0)
        {
             if(c.id==id)
             {
               output=1;
               break;
             }  
        }
       
       write(nsd,&output,sizeof(int));
       if(!output)
       {
        loginPageS();
       }
       else
       {
          c.id=-1;
          lseek(naj,-1*(sizeof(struct agent_account)),SEEK_CUR);
          int a=write(naj,&c,sizeof(struct agent_account));
          int output;
          if(a!=-1)
          output=1;
          write(nsd,&output,sizeof(int));
          loginPageS();
       }
   }
   
   void modifyAgentAccountS()
   {
      int id;
       read(nsd,&id,sizeof(int));
       
       struct agent_account c;
       int output=0;
       lseek(naj,0,SEEK_SET);
       while( read(naj,&c,sizeof(struct agent_account)) >0)
       {
             if(c.id==id)
             {
               output=1;
               break;
             }  
       }
       
       write(nsd,&output,sizeof(int));
       if(!output)
       {
        loginPageS();
       }
       else
       {
           int input;
           read(nsd,&input,sizeof(int));
           
           switch(input)
           {
              case 1:
                      {
                      char buff[80];
                      read(nsd,buff,sizeof(buff));
                      strcpy(c.userName1,buff);
                      lseek(naj,-1*sizeof(struct agent_account),SEEK_CUR);
                      int a=write(naj,&c,sizeof(struct agent_account));
                      int output=0;
                      if(a!=-1)
                      output=1;
                      write(nsd,&output,sizeof(int));
                      break; 
                      }
              case 2:
                      {
                      char buff[80];
                      read(nsd,buff,sizeof(buff));
                      strcpy(c.password1,buff);
                      lseek(naj,-1*sizeof(struct agent_account),SEEK_CUR);
                      int a=write(naj,&c,sizeof(struct agent_account));
                      int output=0;
                      if(a!=-1)
                      output=1;
                      write(nsd,&output,sizeof(int));
                      break; 
                      }
             case 3:
                     {
                      char buff[80];
                      read(nsd,buff,sizeof(buff));
                      strcpy(c.userName2,buff);
                      lseek(naj,-1*sizeof(struct agent_account),SEEK_CUR);
                      int a=write(naj,&c,sizeof(struct agent_account));
                      int output=0;
                      if(a!=-1)
                      output=1;
                      write(nsd,&output,sizeof(int));
                      break; 
                      }
             case 4:
                     {
                      char buff[80];
                      read(nsd,buff,sizeof(buff));
                      strcpy(c.password2,buff);
                      lseek(naj,-1*sizeof(struct agent_account),SEEK_CUR);
                      int a=write(naj,&c,sizeof(struct agent_account));
                      int output=0;
                      if(a!=-1)
                      output=1;
                      write(nsd,&output,sizeof(int));
                      break; 
                      }              
              default: 
                      loginPageS();                        
           }
           loginPageS();
       }
   }
   
   
   
   void searchAgentAccountS()
   {
          int id,output=0;
       read(nsd,&id,sizeof(int));
       struct agent_account c;
       lseek(naj,0,SEEK_SET);
       while(read(naj,&c,sizeof(struct agent_account))>0)
       {
            if(c.id==id)
            {
              output=1;
              break;
            }
       }
       
       write(nsd,&output,sizeof(int));
       if(output)
       {
          write(nsd,&c,sizeof(struct agent_account));
          loginPageS();
       }
       else
        loginPageS();
   }
   
   
  int main(int argc, char *argv[])
  {
     
        nar=open("normal_accounts.txt",O_CREAT|O_RDWR,S_IRWXU);
        nat=open("train_info.txt",O_CREAT|O_RDWR,S_IRWXU);
        nab=open("ticket_info.txt",O_CREAT|O_RDWR,S_IRWXU);
        naj=open("agent_accounts.txt",O_CREAT|O_RDWR,S_IRWXU);
        sd=socket(AF_INET,SOCK_STREAM,0);
        server.sin_family=AF_INET;
        server.sin_addr.s_addr=INADDR_ANY;
        server.sin_port=htons(3737);
        
        bind(sd,(void *) (&server),sizeof(server));
        
        listen(sd,5);
        sz=sizeof(client);
        
        while(1)
        {
        nsd=accept(sd,(void *) (&client),&sz);
          if(!fork())
          {
             close(sd);
             loginPageS();
             exit(0);
          }
          else
              close(nsd);
        
        }
  }
