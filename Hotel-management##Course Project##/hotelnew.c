#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"hotel.h"
FILE* view;
FILE* view2;
FILE *fp;
FILE* br;
FILE* tmp1;
FILE* enter;
char admin_entry[20] = {'y'};
char user_entry[20] = {'y'};

int main(){
    
    int a, b, c, ab, cd;
    qwe:
    printf("\n\n\t\t***********************************************************\n");
    printf("\t\t*                                                         *\n");
    printf("\t\t*       ---------------------------------------           *\n");
    printf("\t\t*            WELCOME TO ROHITH'S ROYAL HEVAN              *\n");
    printf("\t\t*       ---------------------------------------           *\n");
    printf("\t\t*                                                         *\n");
    printf("\t\t***********************************************************\n\n\n");

    printf("\n>>>>>>>>>>>>\tFor ADMIN access enter --> 1 \t\t\t<<<<<<<<<<<<");
    printf("\n>>>>>>>>>>>>\tFor USER access enter --> 2 \t\t\t<<<<<<<<<<<<");
    printf("\n>>>>>>>>>>>>\tFor EXIT enter --> 3 \t\t\t       <<<<<<<<<<<<");
    printf("\n>> ");
    scanf("%d", &a);

    switch(a) {
        case 1: {
            char pass[10];
            char filepass[10];
            int i;

            FILE* passw;
            passw = fopen("pass.txt", "r");
            printf("\n Hello admin!\n Please enter the password to continue --> ");

            for(i = 0; i < 6; i++) {
                scanf("%s", pass);
                fscanf(passw, "%s", filepass);
                if(strcmp(filepass, pass) == 0) {
                    printf("\n\nAccess granted!\n");
                    fclose(passw);
                    break;
                } else {
                    printf("\nIncorrect password, please try again.");
                    printf("\nYou have %d tries left ", 5 - i - 1);
                    printf("\n\nEnter password >> ");
                }
                if(i == 4) {
                    fclose(passw);
                    return 0;
                }
            }
            while(admin_entry[0] == 'y') {
                printf("\n>>>>>>>>>>>>\tTo VIEW booking requests --> 1 \t\t\t<<<<<<<<<<<<");
                printf("\n>>>>>>>>>>>>\tTo VIEW booked guests details --> 2 \t\t\t<<<<<<<<<<<<");
                printf("\n>>>>>>>>>>>>\tTo ENTER new guest --> 3 \t\t\t<<<<<<<<<<<<");
                printf("\n>>>>>>>>>>>>\tTo FIND room number of existing guest --> 4 \t<<<<<<<<<<<<");
                printf("\n>>>>>>>>>>>>\tTo FIND guest of occupied room --> 5 \t<<<<<<<<<<<<");
                printf("\n>>>>>>>>>>>>\tTo CHECKOUT room number of existing guest --> 6 <<<<<<<<<<<<\n");
                printf(">> ");
                scanf("%d", &b);

                switch(b) {
                    case 1: {
                        view_bookings();
                        break;
                    }
                    case 2: {
                        FILE* fpi;
                        fpi = fopen("hotelnew.txt", "r");

                        while(fscanf(fpi, "%s %s %s %d %f", h.name, h.room, h.wifi, &h.nights,&h.payment) != -1) {
                            printf("\n\nName     : %s\n", h.name);
                            printf("Room no. : %s\n", h.room);
                            printf("Wifi     : %s\n", h.wifi);
                            printf("No. of nights stay : %d\n", h.nights);
                            printf("Billing details: %.2f\n", h.payment);
                            printf("--------------------------------------------------------------------");
                        }
                        fclose(fpi);
                        break;
                    }
                    case 3: {
                        enter_name();
                        break;
                    }
                    case 4: {
                        find_name();
                        break;
                    }
                    case 5: {
                        find_room();
                        break;
                    }
                    case 6: {
                        checkout_guest();
                        break;
                    }
                }
                printf("\n\nTo access the admin menu press --y/Y-- <*> To access Main Menu press --m/M-- <*> to exit press any other key >> ");
                scanf("%s", admin_entry);
                if(admin_entry[0]=='m'){
                	goto qwe;
				}
            }
            break;
        }
        case 2: {
            while(user_entry[0] == 'y') {
                printf("\n>>>>>>>>>>>>\tTo VIEW available rooms --> 1 \t\t\t<<<<<<<<<<<<");
                printf("\n>>>>>>>>>>>>\tTo Online Booking --> 2 \t\t\t<<<<<<<<<<<<");
                printf("\n>>>>>>>>>>>>\tTo VIEW hotel details --> 3 \t\t\t<<<<<<<<<<<<");
                printf("\n>>>>>>>>>>>>\tTo VIEW restrictions --> 4 \t\t\t<<<<<<<<<<<<");
                printf(">> ");
                scanf("%d", &c);

                switch(c) {
                    case 1: {
                        printf("\n\n\t\t***********************************************************\n");
                        printf("\t\t*                                                         *\n");
                        printf("\t\t*                  AVAILABLE ROOMS                        *\n");
                        printf("\t\t*                                                         *\n");
                        printf("\t\t*       ---------------------------------------           *\n");
                        printf("\t\t*        Twin-Bed(1-25) &&&&& King-Bed(26-50)             *\n");
                        printf("\t\t*             ROOMS (Rate - Rs.8000(special price))       *\n");

                        view = fopen("rooms.txt", "r");
                        while((ab = fgetc(view)) != EOF) {
                            printf("%c", ab);
                        }
                        fclose(view);
                        break;
                    }
                    case 2: {
                        char room1[10];
                        int nf;
                        float bill;
                        FILE* tmp1;
                        FILE* tmp2;
                        char same_room[20];
                        char room[20];
                        printf("\n\nPlease enter your name >> ");
                        scanf("%s", h.name);
                        printf("\nEnter the room no. you want to stay >> ");
                        scanf("%s", h.room);
                        strcpy(same_room,h.room);
                        printf("\nEnter the Wifi plan you prefer (Free/Limited/Unlimited) >> ");
                        scanf("%s", h.wifi);
                        printf("\nEnter the number of nights you want to stay >> ");
                        scanf("%d", &h.nights);
                        
						br=fopen("booked_rooms.txt","r");
						while(fscanf(br,"%s",room) != -1){
			            if(strcmp(room,same_room) == 0){
                        printf("\nSorry The room is already reserved");
                        goto abc;
                        }
       					}
       					fclose(br);

                        printf("\nYour billing details:\n");
                            bill = h.nights *8000;
                        

                        if (strcmp(h.wifi, "Free") == 0) {
                            bill += 0;
                        } else if (strcmp(h.wifi, "Limited") == 0) {
                            bill += 200;
                        } else if (strcmp(h.wifi, "Unlimited") == 0) {
                            bill += 500;
                        } else {
                            printf("\nInvalid WiFi plan.");
                            break;
                        }

                        h.payment = bill;

                        printf("\nName     : %s", h.name);
                        printf("\nRoom no. : %s", h.room);
                        printf("\nWifi     : %s", h.wifi);
                        printf("\nNo. of nights stay : %d", h.nights);
                        printf("\nBilling details: %.2f", h.payment);
                        printf("\n\nYour booking has been requested.");
						br=fopen("booked_rooms.txt","a");
						fprintf(br,"%s",h.room);
						fprintf(br,"\n");
						fclose(br);
                        fp = fopen("hotelnew.txt", "a+");
                        fprintf(fp, "%s %s %s %d %.2f\n", h.name, h.room, h.wifi, h.nights, h.payment);
                        char remove_guest[20];
    strcpy(remove_guest,h.name);
    char remove_room[20];
    strcpy(remove_room,h.room);

    //removing booking
    tmp1 = fopen("tmp1.txt","a");
    enter = fopen("bookings.txt","r");
 
    while(fscanf(enter,"%s %s %s %d %f",h.name,h.room,h.wifi,h.nights,h.payment) != -1){
			    if(strcmp(h.name,remove_guest) != 0){
                    fprintf(tmp1,"%s %s %s %d %f",h.name,h.room,h.wifi,h.nights,h.payment);
                }
        }
    fclose(enter);
    fclose(tmp1);
    remove("bookings.txt");
    rename("tmp1.txt","bookings.txt");
    fclose(fp);

    //removing room
    tmp2 = fopen("tmp2.txt","a");
    view = fopen("rooms.txt","r");

    
    while(fscanf(view,"%s",h.room) != -1){
			    if(strcmp(h.room,remove_room) != 0){
                    fprintf(tmp2,"%s",h.room);
                    fprintf(tmp2,"\n");
                }
        }
    fclose(view);
    fclose(tmp2);
    remove("rooms.txt");
    rename("tmp2.txt","rooms.txt");


    fclose(fp);
                        break;
                    }
                    case 3: {
                        printf("\n\n\t\t***********************************************************\n");
                        printf("\t\t*                                                         *\n");
                        printf("\t\t*                   HOTEL DETAILS                         *\n");
                        printf("\t\t*                                                         *\n");
                        printf("\t\t*       ---------------------------------------           *\n");
                        printf("\t\t*               ROHITH'S ROYAL HEVAN                      *\n");
                        printf("\t\t*       ---------------------------------------           *\n");
                        printf("\t\t*                                                         *\n");
                        printf("\t\t*       Address : Near Baga Beach, Goa, India, 403518     *\n");
                        printf("\t\t*       Phone   : 7780598470                              *\n");
                        printf("\t\t*       Email   : info@rohithsroyalhevan.com              *\n");
                        printf("\t\t*       Website : www.rohithsroyalhevan.com               *\n"); 
                        printf("\t\t*       -------------------------------------             *\n");
                        printf("\t\t*              KEY FEATURES(Included)                     *\n");
                        printf("\t\t*       -------------------------------------             *\n");
                        printf("\t\t*       \4 Hygiene Plus              	                  *\n");
                        printf("\t\t*       \4 Twin Bed(1-25 Rooms numbers)                    *\n"); 
                        printf("\t\t*       \4 King Bed(25-30 Rooms numbers)            	  *\n");
                        printf("\t\t*       \4 MAX 4 members per Room           	          *\n");
                        printf("\t\t*       \4 Free Parking                                    *\n");
                        printf("\t\t*       \4 Excellent Food & Dining(included)               *\n");
                        printf("\t\t*       \4 Excellent Breakfast                             *\n");
                        printf("\t\t*       \4 Fishing              	                          *\n");
                        printf("\t\t*       \4 Diving         		                  *\n");
                        printf("\t\t*       \4 Fitness Center              	                  *\n");
                        printf("\t\t*       \4 Game Room           			          *\n");
                        printf("\t\t***********************************************************\n");
                        break;
                    }
                    case 4: {
                        printf("\n\n\t\t***********************************************************\n");
                        printf("\t\t*                                                         *\n");
                        printf("\t\t*                    RESTRICTIONS                         *\n");
                        printf("\t\t*                                                         *\n");
                        printf("\t\t*       ---------------------------------------           *\n");
                        printf("\t\t*            - No pets allowed                            *\n");
                        printf("\t\t*            - No smoking in rooms                        *\n");
                        printf("\t\t*            - Check-in time: 2 PM                        *\n");
                        printf("\t\t*            - Check-out time: 12 PM                      *\n");
                        printf("\t\t*            - ID proof required during check-in          *\n");
                        printf("\t\t*            - Maximum 2 adults per room                  *\n");
                        printf("\t\t*                                                         *\n");
                        printf("\t\t***********************************************************\n");
                        break;
                    }
                }
                abc:
                printf("\n\nTo access the User menu press --y/Y-- <*> To access Main Menu press --m/M-- <*> to exit press any other key >> ");
                scanf("%s", user_entry);
                if(user_entry[0]=='m'){
                	goto qwe;
				}
            }
            break;
        }
        case 3:{
        	
        	printf(">>>>>EXICTED<<<<<");
        	exit(0);
			break;
		}
    }
    printf("\n\n");
    return 0;
}
