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

          struct sockaddr_in server;
          int sd,nar,nat,nab,naj;
          
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
        
     void normalLogin();
     void newNormalAccount();
     void normalUserOptionMenu();
     void adminLogin();
     void newTrain();
     void searchTrain();
     void deleteTrain();
     void modifyTrain();
     void searchNormalAccount();
     void modifyNormalAccount();
     void deleteNormalAccount();
     void bookTicket();
     void viewPreviousBooking();
     void updateBooking();
     void cancelBooking();
     void newAgentAccount();
     void deleteAgentAccount();
     void modifyAgentAccount();
     void searchAgentAccount();
     void agentLogin();
     void agentOptionMenu();
     void agentBookTicket();
     void agentViewPreviousBooking();
     void agentUpdateBooking();
     void agentCancelBooking();
     
     
    void loginPage()
    {
    printf("\n ===== Welcome to Online Railway Ticket Booking System ===== \n");
    printf(" Press (1) for Normal Account Login \n");
    printf(" Press (2) for Agent Account Login \n");
    printf(" Press (3) for Administrator Login \n");
    printf(" Press (4) to Create New Normal Account \n");
    printf(" Press (5) to Create New Agent Account \n");
    printf(" Press Any Other Key to go out of the system \n");

    int input;
    scanf("%d", &input);
    
    write(sd, &input, sizeof(int));
    

    switch(input){

        case 1:
            printf("\n Normal Account Login.. \n");
            normalLogin();
            break;
        case 2:
            printf("\n Agent Account Login.. \n");
            agentLogin();
            break;
        case 3:
            printf("\n Administrator Login.. \n");
            adminLogin();
            break;
        case 4:
            printf("\n Creating New Normal Account...\n");
            newNormalAccount();
            break;
        case 5:
            printf("\n Creating New Agent Account...\n");
            newAgentAccount();
            break;        
        default:
            close(sd);
            exit(EXIT_SUCCESS);
    }
}
    
    void adminLogin()
    {
        
        int id,output;
        char pwd[80];
        printf("Enter ID:\n");
        scanf("%d",&id);
        printf("Enter Password:\n");
        scanf("%s",pwd);
        write(sd,&id,sizeof(int));
        write(sd,pwd,sizeof(pwd));
        
        read(sd,&output,sizeof(int));
        
        if(!output)
        {
          printf("Wrong ID or Password\n");
          char h[5];
          printf("Press any key to go back to Login Page\n");
          scanf("%s",h);
          loginPage();
        }
        
        else
        {
        printf("======= Welcome Administrator!!!! =======\n");
        printf(" Press (1) to Add New Normal User Account\n");
        printf(" Press (2) to Delete Normal User Account\n");
        printf(" Press (3) to Modify Normal User Account\n");
        printf(" Press (4) to Search Normal User Account\n");
        printf(" Press (5) to Add New Train Details\n");
        printf(" Press (6) to Delete Train Details\n");
        printf(" Press (7) to Modify Train Details\n");
        printf(" Press (8) to Search for Train Details\n");
        printf(" Press (9) to Add New Agent Account\n");
        printf(" Press (10) to Delete Agent Account\n");
        printf(" Press (11) to Modify Agent Account\n");
        printf(" Press (12) to Search Agent Account\n");
        printf(" Press any other key to go back to Login Page\n");
        
        int input;
        scanf("%d",&input);
        
        write(sd,&input,sizeof(int));
        
        switch(input)
        {
           case 1:
                  newNormalAccount();
                  break;
                  
           case 2:
                  deleteNormalAccount();
                  break;
           
           case 3:
                  modifyNormalAccount();
                  break; 
           
           case 4:
                  searchNormalAccount();
                  break;
           
           case 5:
                  newTrain();
                  break; 
           
           case 6:
                  deleteTrain();
                  break;        
           case 7:
                  modifyTrain();
                  break; 
           case 8:
                  searchTrain();
                  break;          
           case 9:
                  newAgentAccount();
                  break; 
           case 10:
                  deleteAgentAccount();
                  break;
           
           case 11:
                  modifyAgentAccount();
                   break;
           
           case 12:
                   searchAgentAccount();
                   break;             
           default:
                  system("clear");
                  loginPage();
                                             
        }
        
        }
        
    }
    
    void agentLogin()
    {
       int id;
       char pwd[80];
       printf("Enter user id:\n");
       scanf("%d",&id);
       printf("Enter password:\n");
       scanf("%s",pwd);
       write(sd,&id,sizeof(int));
       write(sd,pwd,sizeof(pwd));
       int response;
       read(sd,&response,sizeof(int));
       if(!response)
       {
          printf("Incorrect ID or Password\n");
          loginPage();
       }
       else 
       {
          char buff[80];
          printf("================Welcome ");
          read(sd,buff,sizeof(buff));
          printf("%s==============\n",buff);
          agentOptionMenu(id);
       }
       
    }
    
    
    void agentOptionMenu(int id)
    {
          printf("Press (1) to Book Ticket\n");
          printf("Press (2) to View Previous Bookings\n");
          printf("Press (3) to Update Booking\n");
          printf("Press (4) to Cancel Booking\n");
          printf("Press any other key to go back to Login Page\n");
          int input;
          scanf("%d",&input);
          write(sd,&input,sizeof(int));
          
          switch(input)
          {
             case 1:
                   agentBookTicket(id);
                   break;
             
             case 2:
                   agentViewPreviousBooking(id);
                   break;
             
             case 3:
                   agentUpdateBooking(id);
                   break;
             
             case 4:
                   agentCancelBooking(id);
                   break;
             
             default:
                      loginPage();
                                                  
          }
    }
    
    void agentBookTicket(int id)
    {
       struct train_info c;
         int a,count=0;
         printf("Train No\t\t Train Name\t\t Starting Location\t\t Destination Location\t\t Start Time\t\t Reaching Time\t\t No of Tickets Available\n");
printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
         while( read(sd,&a,sizeof(int)) && a!=0 )
         {
           read(sd,&c,sizeof(struct train_info));
           
           if(c.train_no!=0 && c.train_no!=-1)
           { 
             count++;
           printf("%d\t\t %s\t\t %s\t\t\t %s\t\t\t %s\t\t\t %s\t\t\t %d\n",c.train_no,c.train_name,c.from,c.destn,c.start_time,c.reaching_time,c.no_of_tickets);   
         }
         }
         write(sd,&count,sizeof(int));
         if(count==0)
         {
          printf("No train exists\n");
          loginPage();
         }
         else
         {
         int train_no;
         printf("Enter Train No to book ticket\n");
         scanf("%d",&train_no);
         write(sd,&train_no,sizeof(int));
         int flag;
         read(sd,&flag,sizeof(int));
         if(flag==0)
         {
           printf("No such train exists\n");
           loginPage();
         }
         else
         {
         int output;
         read(sd,&output,sizeof(int));
         if(output==-2)
         {
          printf("No Tickets are available!!!\n");
          loginPage();
         }
         else if(output==-1)
         {
             printf("Some error occurred while booking ticket,please try again later\n");
             loginPage();
         }
         else
         {
             int seat_no;
             read(sd,&seat_no,sizeof(int));
             printf("Ticket Booked Successfully\n");
             printf("Seat No is : %d\n",seat_no);
             loginPage();
         }
    }
    }
    }
    
    void agentViewPreviousBooking(int id)
    {
         int output;
           struct ticket_info c;
           int count=0;
           printf("Train No\t\t\t Train Name\t\t\t Seat No\t\t\t Status\n");
           printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
           while( read(sd,&output,sizeof(int)) && output!=0)
           {
                read(sd,&c,sizeof(struct ticket_info));
                if(c.id==id )
                {
                  count++;
                  printf("%d\t\t\t %s\t\t\t %d\t\t\t %s\n",c.train_no,c.trainName,c.seatNo,c.status);
                }
           }
           if(count==0)
           printf("====================== No Record Exists ==================\n");
           loginPage();
    }
    
    void agentCancelBooking(int id)
    {
        int train_no;
          printf("Enter Train No to cancel booked ticket\n");
          scanf("%d",&train_no);
          write(sd,&train_no,sizeof(int));
          int flag;
          read(sd,&flag,sizeof(int));
          if(flag==0)
          {
             printf("No booking exists in Train No: %d\n",train_no);
             loginPage();
          }
          else
          {
             printf("Ticket Cancelled Successfully\n");
             
             loginPage();
          }
    }
    
    void agentUpdateBooking(int id)
    {
         int train_no;
      printf("Enter Train No to update booking\n");
      scanf("%d",&train_no);
      write(sd,&train_no,sizeof(int));
      int output;
      read(sd,&output,sizeof(int));
      if(output==0)
      {
       printf("No booking exists in train no: %d\n",train_no);
       loginPage();
      }
      else
      {
        int old_seat,new_seat;
        read(sd,&old_seat,sizeof(int));
        read(sd,&new_seat,sizeof(int));
        printf("The seat No is updated from %d to %d\n",old_seat,new_seat);
        loginPage();
      }
    }
    
    
    void newTrain()
    {
       int train_no;
       char train_name[80],startLoc[80],endLoc[80],startTime[80],reachTime[80];
       printf("Enter Train No:\n");
       
       scanf("%d",&train_no);
       
       //fflush(stdin);
       getchar();
       printf("Enter Train Name:\n");
       
       scanf("%[^\n]s",train_name);
       //fflush(stdin);
       getchar();
       //gets(train_name);
       printf("Enter Train Starting Location:\n");
       
       scanf("%[^\n]s",startLoc);
       //fflush(stdin);
       getchar();
       //gets(startLoc);
       printf("Enter Train Destination Location:\n");
       
       scanf("%[^\n]s",endLoc);
       //fflush(stdin);
       getchar();
       //gets(endLoc);
       printf("Enter Start Time for Train:\n");
       
       scanf("%[^\n]s",startTime);
       //fflush(stdin);
       
       //gets(startTime);
       printf("Enter Reaching Time for Train:\n");
       getchar();
       scanf("%[^\n]s",reachTime);
       fflush(stdin);
       
       //gets(reachTime);
       
       
       int no_of_tickets=100;
       write(sd,&train_no,sizeof(int));
       write(sd,train_name,sizeof(train_name));
       write(sd,startLoc,sizeof(startLoc));
       write(sd,endLoc,sizeof(endLoc));
       write(sd,startTime,sizeof(startTime));
       write(sd,reachTime,sizeof(reachTime));
       write(sd,&no_of_tickets,sizeof(int));
       
       int output;
       
       read(sd,&output,sizeof(int));
       
       if(output)
       {
          printf("Train Information Added Successfully!!!\n");
          loginPage();
       }
       else
       {
         printf("Some error occurred while adding train info, please try again later!!\n");
         loginPage();
       }
    }
    
    void modifyTrain()
    {
      int input,train_no;
      printf("Enter No of Train to be modified\n");
      scanf("%d",&train_no);
      
      write(sd,&train_no,sizeof(int));
      int output;
      
      read(sd,&output,sizeof(int));
      if(!output)
      {
         printf("No such data exists\n");
         loginPage();
      }
      else
      {
      printf(" Press (1) to modify Train Name\n");
      printf(" Press (2) to modify Train Starting Location\n");
      printf(" Press (3) to modify Train Destination Location\n");
      printf(" Press (4) to modify Starting Time of Train\n");
      printf(" Press (5) to modify Reaching Time of Train\n");
      printf(" Press any other key to go back to Login Page\n");
      scanf("%d",&input);
      write(sd,&input,sizeof(int));
      switch(input)
        { 
           case 1:
                   {
                    char buff[80];
                    getchar();
                    printf("Enter new Train Name:\n");
                    scanf("%[^\n]s",buff);
                    write(sd,buff,sizeof(buff));
                    int output;
                    read(sd,&output,sizeof(int));
                    if(output)
                    printf("Data Modified Successfully!!!\n");
                    else
                    printf("Some error occurred during modification of data, please try again later\n");
                    break; 
                   }
           case 2:
                   {
                     char buff[80];
                     getchar();
                     printf("Enter new Train Starting Location:\n");
                     scanf("%[^\n]s",buff);
                     write(sd,buff,sizeof(buff));
                     int output;
                     read(sd,&output,sizeof(int));
                     if(output)
                     printf("Data Modified Successfully!!!\n");
                     else
                     printf("Some error occurred during modification of data, please try again later\n");
                     break; 
                   }
           case 3:
                    {
                     char buff[80];
                     getchar();
                     printf("Enter new Train Destination Location:\n");
                     scanf("%[^\n]s",buff);
                     write(sd,buff,sizeof(buff));
                     int output;
                     read(sd,&output,sizeof(int));
                     if(output)
                     printf("Data Modified Successfully!!!\n");
                     else
                     printf("Some error occurred during modification of data, please try again later\n");
                     break; 
                   }
           case 4:
                   {
                     char buff[80];
                     getchar();
                     printf("Enter new Train Start Time:\n");
                     scanf("%[^\n]s",buff);
                     write(sd,buff,sizeof(buff));
                     int output;
                     read(sd,&output,sizeof(int));
                     if(output)
                     printf("Data Modified Successfully!!!\n");
                     else
                     printf("Some error occurred during modification of data, please try again later\n");
                     break; 
                   }
           case 5:
                   {
                     char buff[80];
                     getchar();
                     printf("Enter new Train Reaching Time:\n");
                     scanf("%[^\n]s",buff);
                     write(sd,buff,sizeof(buff));
                     int output;
                     read(sd,&output,sizeof(int));
                     if(output)
                     printf("Data Modified Successfully!!!\n");
                     else
                     printf("Some error occurred during modification of data, please try again later\n");
                     break; 
                   }
           default:
                   loginPage();
                                                                    
                   
        }
        
        loginPage();
      }
    }
    
    
    void deleteTrain()
    {
          int train_no,output;
          printf("Enter Train No:\n");
          scanf("%d",&train_no);
          
          write(sd,&train_no,sizeof(int));
          
          read(sd,&output,sizeof(int));
          
          if(output)
          {
               printf("Data deleted successfully !!!\n");
               loginPage();
          }
          else
           {
               printf("No such data exits\n");
               loginPage();
           }
          
    }
    
    
    void searchTrain()
    {
        int train_no;
        struct train_info c;
        printf("Enter Train No\n");
        scanf("%d",&train_no);
        
        write(sd,&train_no,sizeof(int));
        
        int output;
        read(sd,&output,sizeof(int));
        
        if(output==1)
        {
           read(sd,&c,sizeof(struct train_info));
           printf("Train No\t\t Train Name\t\t Starting Location\t\t Destination Location\t\t Start Time\t\t Reaching Time\t\t No of Tickets Available\n");
printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
           printf("%d\t\t %s\t\t %s\t\t\t %s\t\t\t %s\t\t\t %s\t\t\t %d\n",c.train_no,c.train_name,c.from,c.destn,c.start_time,c.reaching_time,c.no_of_tickets);
           loginPage();
        }
        else
         {
           printf("No data exists for train no:%d\n",train_no);
           loginPage();
         }
    }
    
    
    void normalLogin()
    {
       int id;
       char pwd[80];
       printf("Enter user id:\n");
       scanf("%d",&id);
       printf("Enter password:\n");
       scanf("%s",pwd);
       write(sd,&id,sizeof(int));
       write(sd,pwd,sizeof(pwd));
       int response;
       read(sd,&response,sizeof(int));
       if(!response)
       {
          printf("Incorrect ID or Password\n");
          loginPage();
       }
       else
       {
          char buff[80];
          printf("================Welcome ");
          read(sd,buff,sizeof(buff));
          printf("%s==============\n",buff);
          normalUserOptionMenu(id);
       }
    }
    
    void normalUserOptionMenu(int id)
    {
          printf("Press (1) to Book Ticket\n");
          printf("Press (2) to View Previous Bookings\n");
          printf("Press (3) to Update Booking\n");
          printf("Press (4) to Cancel Booking\n");
          printf("Press any other key to go back to Login Page\n");
          int input;
          scanf("%d",&input);
          write(sd,&input,sizeof(int));
          
          switch(input)
          {
             case 1:
                   bookTicket(id);
                   break;
             
             case 2:
                   viewPreviousBooking(id);
                   break;
             
             case 3:
                   updateBooking(id);
                   break;
             
             case 4:
                   cancelBooking(id);
                   break;
             
             default:
                      loginPage();
                                                  
          }
          
    }
    
    void bookTicket(int id)
    {
         struct train_info c;
         int a,count=0;
         printf("Train No\t\t Train Name\t\t Starting Location\t\t Destination Location\t\t Start Time\t\t Reaching Time\t\t No of Tickets Available\n");
printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
         while( read(sd,&a,sizeof(int)) && a!=0 )
         {
           read(sd,&c,sizeof(struct train_info));
           
           if(c.train_no!=0 && c.train_no!=-1)
           { 
             count++;
           printf("%d\t\t %s\t\t %s\t\t\t %s\t\t\t %s\t\t\t %s\t\t\t %d\n",c.train_no,c.train_name,c.from,c.destn,c.start_time,c.reaching_time,c.no_of_tickets);   
         }
         }
         write(sd,&count,sizeof(int));
         if(count==0)
         {
          printf("No train exists\n");
          loginPage();
         }
         else
         {
         int train_no;
         printf("Enter Train No to book ticket\n");
         scanf("%d",&train_no);
         write(sd,&train_no,sizeof(int));
         int flag;
         read(sd,&flag,sizeof(int));
         if(flag==0)
         {
           printf("No such train exists\n");
           loginPage();
         }
         else
         {
         int output;
         read(sd,&output,sizeof(int));
         if(output==-2)
         {
          printf("No Tickets are available!!!\n");
          loginPage();
         }
         else if(output==-1)
         {
             printf("Some error occurred while booking ticket,please try again later\n");
             loginPage();
         }
         else
         {
             int seat_no;
             read(sd,&seat_no,sizeof(int));
             printf("Ticket Booked Successfully\n");
             printf("Seat No is : %d\n",seat_no);
             loginPage();
         }
    }
    }
    }
    
    void updateBooking(int id)
    {
      int train_no;
      printf("Enter Train No to update booking\n");
      scanf("%d",&train_no);
      write(sd,&train_no,sizeof(int));
      int output;
      read(sd,&output,sizeof(int));
      if(output==0)
      {
       printf("No booking exists in train no: %d\n",train_no);
       loginPage();
      }
      else
      {
        int old_seat,new_seat;
        read(sd,&old_seat,sizeof(int));
        read(sd,&new_seat,sizeof(int));
        printf("The seat No is updated from %d to %d\n",old_seat,new_seat);
        loginPage();
      }
    }
    
    
    void newNormalAccount()
    {
        int id;
        char username[80], password[80];
        struct normal_user cust;

        printf("\n Create New Normal User Account \n");
        printf("Enter User Id: \n");
        scanf("%d", &id);
        printf(" Enter User Name: \n");
        scanf("%s", username);
        printf(" Enter Password: \n");
        scanf("%s", password);
       
        cust.id = id;
        strcpy(cust.name, username);
        strcpy(cust.password, password);
        
        
        write(sd, &cust, sizeof(struct normal_user));
    
        int output;
        read(sd,&output,sizeof(int));
        if(output)
        printf("Account Created Successfully! Congratulations! \n");
        else
        printf("Some error occurred while creating account,please try again later\n");
        loginPage();
    }
    
    void searchNormalAccount()
    {
      int id;
      printf("Enter ID of account to be searched\n");
      scanf("%d",&id);
      write(sd,&id,sizeof(int));
      int output;
      
      read(sd,&output,sizeof(int));
      if(output)
      {
          struct normal_user c;
          read(sd,&c,sizeof(struct normal_user));
          printf("ID\t\t Name\t\t Password\n");
          printf("------------------------------------------------------------------------------------------------------------------------------\n");
          printf("%d\t\t %s\t\t %s\n",c.id,c.name,c.password);
          loginPage();
      }
      else
      {
        printf("No such record found!!\n");
        loginPage();
      }
    }
    
    void modifyNormalAccount()
    {
        int id;
        printf("Enter ID of account to be modified\n");
        scanf("%d",&id);
        
        write(sd,&id,sizeof(int));
        int output;
        read(sd,&output,sizeof(int));
        if(!output)
        {
         printf("No such entry exists\n");
         loginPage();
        }
        else
        {
            int input;
            
            printf(" Press (1) to modify Name\n");
            printf(" Press (2) to modify Password\n");
            printf(" Press any other key to go back to Login Page\n");
            scanf("%d",&input);
            write(sd,&input,sizeof(int));
            
            switch(input)
            {
               case 1:
                       {
                       char buff[80];
                       printf("Enter new Name for user\n");
                       scanf("%s",buff);
                       write(sd,buff,sizeof(buff));
                       int output;
                       read(sd,&output,sizeof(int));
                       if(output)
                       printf("Data Modified Successfully!!!\n");
                       else
                       printf("Some error occurred during modification of data, please try again later\n");
                       break;
                       }
               case 2:
                       {
                       char buff[80];
                       printf("Enter new Password for user\n");
                       scanf("%s",buff);
                       write(sd,buff,sizeof(buff));
                       int output;
                       read(sd,&output,sizeof(int));
                       if(output)
                       printf("Data Modified Successfully!!!\n");
                       else
                       printf("Some error occurred during modification of data, please try again later\n");
                       break;
                       }
               default: 
                       loginPage();                        
            }
            
            loginPage();
        }
    }
    
      void deleteNormalAccount()
      {
           int id;
           printf("Enter ID of account to be deleted\n");
           scanf("%d",&id);
           write(sd,&id,sizeof(int));
           int output;
           read(sd,&output,sizeof(int));
           if(!output)
           {
             printf("No such account exists\n");
             loginPage();
           }
           else
           {
             int output;
             read(sd,&output,sizeof(int));
             if(output)
             printf("Account deleted successfully !!\n");
             else
             printf("Some error occurred while deleting account, please try again later\n");
             
             loginPage();
           }
      }
     
     void viewPreviousBooking(int id)
     {
           int output;
           struct ticket_info c;
           int count=0;
           printf("Train No\t\t\t Train Name\t\t\t Seat No\t\t\t Status\n");
           printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
           while( read(sd,&output,sizeof(int)) && output!=0)
           {
                read(sd,&c,sizeof(struct ticket_info));
                if(c.id==id )
                {
                  count++;
                  printf("%d\t\t\t %s\t\t\t %d\t\t\t %s\n",c.train_no,c.trainName,c.seatNo,c.status);
                }
           }
           if(count==0)
           printf("====================== No Record Exists ==================\n");
           char h[5];
           printf("Press any key to return to Login Page\n");
           scanf("%s",h);
           loginPage();
     } 
     
     void cancelBooking(int id)
     {
          int train_no;
          printf("Enter Train No to cancel booked ticket\n");
          scanf("%d",&train_no);
          write(sd,&train_no,sizeof(int));
          int flag;
          read(sd,&flag,sizeof(int));
          if(flag==0)
          {
             printf("No booking exists in Train No: %d\n",train_no);
             loginPage();
          }
          else
          {
             
             char h[5];
             printf("Press Enter to cancel Ticket\n");
             scanf("%s",h);
             printf("Ticket Cancelled Successfully\n");
             loginPage();
          }
     }
     
     void newAgentAccount()
     {
         struct agent_account c;
         int id;
         char userName1[80],userName2[80],password1[80],password2[80];
         printf("Enter ID for new Agent Account:\n");
         scanf("%d",&id);
         printf("Enter First User's Name:\n");
         scanf("%s",userName1);
         printf("Enter First User's Password:\n");
         scanf("%s",password1);
         printf("Enter Second User's Name:\n");
         scanf("%s",userName2);
         printf("Enter Second User's Password:\n");
         scanf("%s",password2);
         
         c.id=id;
         strcpy(c.password1,password1);
         strcpy(c.password2,password2);
         strcpy(c.userName1,userName1);
         strcpy(c.userName2,userName2);
         
         write(sd,&c,sizeof(struct agent_account));
         int output;
         read(sd,&output,sizeof(int));
         if(output!=-1)
         printf("Account created successfully!!\n");
         else
         printf("Some error occurred,please try again later\n");
         loginPage();
         
     }
     
     void deleteAgentAccount()
     {
        int id;
           printf("Enter ID of account to be deleted\n");
           scanf("%d",&id);
           write(sd,&id,sizeof(int));
           int output;
           read(sd,&output,sizeof(int));
           if(!output)
           {
             printf("No such account exists\n");
             loginPage();
           }
           else
           {
             int output;
             read(sd,&output,sizeof(int));
             if(output)
             printf("Account deleted successfully !!\n");
             else
             printf("Some error occurred while deleting account, please try again later\n");
             
             loginPage();
           }
     }
      
      
      void modifyAgentAccount()
      {
          int id;
        printf("Enter ID of account to be modified\n");
        scanf("%d",&id);
        
        write(sd,&id,sizeof(int));
        int output;
        read(sd,&output,sizeof(int));
        if(!output)
        {
         printf("No such entry exists\n");
         loginPage();
        }
        else
        {
            int input;
            
            printf(" Press (1) to modify First User's Name\n");
            printf(" Press (2) to modify First User's Password\n");
            printf(" Press (3) to modify Second User's Name\n");
            printf(" Press (4) to modify Second User's Password\n");
            printf(" Press any other key to go back to Login Page\n");
            scanf("%d",&input);
            write(sd,&input,sizeof(int));
            
            switch(input)
            {
               case 1:
                       {
                       char buff[80];
                       printf("Enter new Name for First user\n");
                       scanf("%s",buff);
                       write(sd,buff,sizeof(buff));
                       int output;
                       read(sd,&output,sizeof(int));
                       if(output)
                       printf("Data Modified Successfully!!!\n");
                       else
                       printf("Some error occurred during modification of data, please try again later\n");
                       break;
                       }
               case 2:
                       {
                       char buff[80];
                       printf("Enter new Password for First user\n");
                       scanf("%s",buff);
                       write(sd,buff,sizeof(buff));
                       int output;
                       read(sd,&output,sizeof(int));
                       if(output)
                       printf("Data Modified Successfully!!!\n");
                       else
                       printf("Some error occurred during modification of data, please try again later\n");
                       break;
                       }
              case 3:
                       {
                       char buff[80];
                       printf("Enter new Name for Second user\n");
                       scanf("%s",buff);
                       write(sd,buff,sizeof(buff));
                       int output;
                       read(sd,&output,sizeof(int));
                       if(output)
                       printf("Data Modified Successfully!!!\n");
                       else
                       printf("Some error occurred during modification of data, please try again later\n");
                       break;
                       }
             
             case 4:
                       {
                       char buff[80];
                       printf("Enter new Password for Second user\n");
                       scanf("%s",buff);
                       write(sd,buff,sizeof(buff));
                       int output;
                       read(sd,&output,sizeof(int));
                       if(output)
                       printf("Data Modified Successfully!!!\n");
                       else
                       printf("Some error occurred during modification of data, please try again later\n");
                       break;
                       } 
                              
               default: 
                       loginPage();                        
            }
            
            loginPage();
        }
      }
      
      void searchAgentAccount()
      {
        int id;
      printf("Enter ID of account to be searched\n");
      scanf("%d",&id);
      write(sd,&id,sizeof(int));
      int output;
      
      read(sd,&output,sizeof(int));
      if(output)
      {
          struct agent_account c;
          read(sd,&c,sizeof(struct agent_account));
          printf("ID\t\t First User Name\t\t First User Password\t\t Second User Name\t\t Second User Password\n");
          printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
          printf("%d\t\t\t %s\t\t\t %s\t\t\t %s\t\t\t %s\n",c.id,c.userName1,c.password1,c.userName2,c.password2);
          loginPage();
      }
      else
      {
        printf("No such record found!!\n");
        loginPage();
      }
      }
      
      
    int main(int argc, char *argv[])
    {
   
          sd=socket(AF_INET,SOCK_STREAM,0);
          
          server.sin_family=AF_INET;
          server.sin_addr.s_addr=INADDR_ANY;
          server.sin_port=htons(3737);
          
          connect(sd,(void *) (&server),sizeof(server));
          
          
          loginPage();
          close(sd);
          return 0;
          
    }

