#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct user{
     char phone[50];
     char ac[50];
     char password[50];
     float balance;
};

int main(){
      struct user usr;
      FILE *fp;
      char filename[50], phone[50], pword[50];
      int opt, choice;
      char cont = 'y';
      float amount;

      printf("\n What do you want to do");
      printf("\n\n1. Register an account");
      printf("\n2. Login to an account");

      printf("\n\n Your choice: ");
      scanf("%d",&opt);

      if(opt == 1){
           system("clear");
           printf("Enter your account number:\t");
           scanf("%s", usr.ac);

           printf("Enter your phone number:\t");
           scanf("%s", usr.phone);

           printf("Enter your new password:\t");
           scanf("%s", usr.password);

           usr.balance = 0;

           strcpy(filename, usr.phone);
           fp = fopen(strcat(filename,".dat"),"w");

           if(fp != NULL){
               fwrite(&usr, sizeof(struct user), 1, fp);
               printf("\n\n Account successfully registered");
               fclose(fp);
           } else {
               printf("\n Something went wrong please try again");
           }
      }

      if(opt == 2){
           system("clear");

           printf("\nPhone number: \t");
           scanf("%s", phone);

           printf("Password: \t");
           scanf("%s", pword);

           strcpy(filename, phone);
           fp = fopen(strcat(filename,".dat"), "r");

           if(fp == NULL){
                printf("\n Account not registered");
           }    
           else {
               fread(&usr, sizeof(struct user), 1, fp);
               fclose(fp);

               if(strcmp(pword, usr.password) == 0){

                   while(cont == 'y'){
                        system("clear");

                        printf("\n Press 1 for balance inquiry");
                        printf("\n Press 2 for depositing cash");
                        printf("\n Press 3 for cash withdrawal");
                        printf("\n Press 4 for online transfer");
                        printf("\n Press 5 for password change");
                        printf("\n\n Your choice: ");
                        scanf("%d",&choice);

                        switch(choice){

                             case 1:
                                 printf("\n Your current balance is: %.2f", usr.balance);
                                 break;

                             case 2:
                                 printf("\n Enter the amount: \t");
                                 scanf("%f", &amount);

                                 usr.balance += amount;

                                 fp = fopen(filename,"w");
                                 fwrite(&usr, sizeof(struct user), 1, fp);
                                 fclose(fp);

                                 printf("\n Deposit successful");
                                 break;

                             case 3:
                                 printf("\n Enter the amount:\t");  
                                 scanf("%f", &amount);

                                 if(amount > usr.balance){
                                     printf("\n Insufficient balance");
                                 } else {
                                     usr.balance -= amount;

                                     fp = fopen(filename,"w");
                                     fwrite(&usr, sizeof(struct user), 1, fp);
                                     fclose(fp);

                                     printf("\n Withdrawal successful");
                                 }
                                 break;

                             case 4:{
                                 char receiverFile[50];
                                 struct user receiver;

                                 printf("\n Please enter the receiver phone: ");
                                 scanf("%s", phone);

                                 printf("\n Please enter the amount: ");
                                 scanf("%f",&amount);

                                 if(amount > usr.balance){
                                     printf("\n Insufficient balance");
                                 } else {
                                     strcpy(receiverFile, phone);
                                     fp = fopen(strcat(receiverFile,".dat"),"r");

                                     if(fp == NULL){
                                         printf("\n Receiver not found");
                                     } else {
                                         fread(&receiver,sizeof(struct user),1,fp);
                                         fclose(fp);

                                         receiver.balance += amount;

                                         fp = fopen(receiverFile,"w");
                                         fwrite(&receiver,sizeof(struct user),1,fp);
                                         fclose(fp);

                                         usr.balance -= amount;

                                         fp = fopen(filename,"w");
                                         fwrite(&usr,sizeof(struct user),1,fp);
                                         fclose(fp);

                                         printf("\n You have successfully transferred");
                                     }
                                 }
                                 break;
                             }

                             case 5:
                                 printf("\n Please enter your new password: ");
                                 scanf("%s", usr.password);

                                 fp = fopen(filename,"w");
                                 fwrite(&usr,sizeof(struct user),1,fp);
                                 fclose(fp);

                                 printf("\n Password successfully changed");
                                 break;

                             default:
                                 printf("\n Invalid choice");
                        }

                        printf("\n\n Do you want to continue (y/n): ");
                        scanf(" %c",&cont);
                   }
               }
               else{
                   printf("\n Invalid password");
               }
           }
      }

      return 0;
}
