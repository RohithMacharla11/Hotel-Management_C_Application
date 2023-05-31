#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void enter_name();
void find_name();
void find_room();
void checkout_guest();
void view_bookings();

FILE* view;
FILE* view2;
FILE *fp;
FILE* br;
FILE* tmp1;
FILE* enter;

struct hotel
{
    char name[20];
    char room[20];
    char wifi[20];
    int nights;
    float payment;
} h;

void enter_name() {
    FILE* tmp1;
    FILE* tmp2;
    char same_room[20];
    char room[20];
    printf("\n\nPlease enter Guest name >> ");
    scanf("%s", h.name);
    printf("\nEnter the room no. Guest want to stay >> ");
    scanf("%s", h.room);
    printf("\nEnter the Wifi plan Guest prefers (Free/Limited/Unlimited) >> ");
    scanf("%s", h.wifi);
    printf("\nEnter the number of nights Guest want to stay >> ");
    scanf("%d", &h.nights);
    strcpy(same_room,h.room);
    br=fopen("booked_rooms.txt","r");
						while(fscanf(br,"%s",room) != -1){
			            if(strcmp(room,same_room) == 0){
                        printf("\nSorry The room is already reserved");
                        goto xyz;
                        }
       					}
       				fclose(br);
       				br=fopen("booked_rooms.txt","a");
						fprintf(br,"%s",h.room);
						fprintf(br,"\n");
						fclose(br);
        float bill = h.nights * 8000;

    if (strcmp(h.wifi, "Free") == 0) {
        bill += 0;
    } else if (strcmp(h.wifi, "Limited") == 0) {
        bill += 200;
    } else if (strcmp(h.wifi, "Unlimited") == 0) {
        bill += 500;
    } else {
        printf("\nInvalid WiFi plan.");
        return;
    }

    h.payment = bill;

    printf("\nName     : %s", h.name);
    printf("\nRoom no. : %s", h.room);
    printf("\nWifi     : %s", h.wifi);
    printf("\nNo. of nights stay : %d", h.nights);
    printf("\nBilling details: %.2f", h.payment);
    printf("\n\nYour booking has been entered.");

    fp = fopen("hotelnew.txt", "a+");
    fprintf(fp, "%s %s %s %d %.2f\n", h.name, h.room, h.wifi, h.nights, h.payment);
    fprintf(fp,"\n");

    //
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

    xyz:
    fclose(fp);
}


void find_name() {
    char search_name[20];
    int found = 0;

    printf("\n\nEnter the Guest name to search >> ");
    scanf("%s", search_name);

    fp = fopen("hotelnew.txt", "r");
    while(fscanf(fp, "%s %s %s %d %f", h.name, h.room, h.wifi, &h.nights,&h.payment) != -1) {
        if(strcmp(h.name, search_name) == 0) {
            found = 1;
            printf("\n\nName     : %s\n", h.name);
            printf("Room no. : %s\n", h.room);
            printf("Wifi     : %s\n", h.wifi);
            printf("No. of nights stay : %d\n", h.nights);
            printf("Billing details: %.2f\n", h.payment);
            break;
        }
    }
    fclose(fp);
    if(found == 0) {
        printf("\n\nNo guest found with the name %s\n", search_name);
    }
}

void find_room() {
    char search_room[10];
    int found = 0;

    printf("\n\nEnter the room no. to search for Guest details >> ");
    scanf("%s", search_room);

    fp = fopen("hotelnew.txt", "r");
    while(fscanf(fp, "%s %s %s %d %f", h.name, h.room, h.wifi, &h.nights, &h.payment) != -1) {
        if(strcmp(h.room, search_room) == 0) {
            found = 1;
            printf("\n\nName     : %s\n", h.name);
            printf("Room no. : %s\n", h.room);
            printf("Wifi     : %s\n", h.wifi);
            printf("No. of nights stay : %d\n", h.nights);
            printf("Billing details: %.2f\n", h.payment);
            break;
        }
    }
    fclose(fp);
    if(found == 0) {
        printf("\n\nNo guest found in room %s\n", search_room);
    }
}

//method definition for guest checkout
void checkout_guest(){
    char buffer2[20];
    char checkout_room[20];
    char add_room[20];

    FILE *tmp;

    printf("Enter Room too checkout ");
    scanf("%s",checkout_room);

    fp = fopen("hotelnew.txt","r");
    tmp = fopen("tmp.txt","w");

    if(fp == NULL){
    printf("File not found");
    exit(1);
    }
	else{
        while(fscanf(fp,"%s %s %s %d %f",h.name,h.room,h.wifi,&h.nights,&h.payment) != -1){
			    if(strcmp(h.room,checkout_room) != 0){

                    fprintf(tmp,"%s %s %s %d %f",h.name,h.room,h.wifi,h.nights,h.payment);
                }
                else{
                   strcpy(add_room,h.room);
                }
                
        }
        
        printf("Room checked out!");
    }

    fclose(fp);
    fclose(tmp);
    remove("hotelnew.txt");
    rename("tmp.txt","hotelnew.txt");
    strcpy(add_room,checkout_room);
    //enter room back into available rooms list
    view = fopen("rooms.txt","a");
    printf(" add is %s",add_room);
    fprintf(view,"\n%s",add_room);
    fclose(view);
    char rem_room[20];
    strcpy(rem_room,add_room);
    br = fopen("booked_rooms.txt","r");
    tmp1 = fopen("tmp1.txt","w");
    while(fscanf(br,"%s",h.room) != -1){
			    if(strcmp(h.room,rem_room) != 0){
                    fprintf(tmp1,"%s\n",h.room);
                }
     }
    fclose(br);
    fclose(tmp1);
    remove("booked_rooms.txt");
    rename("tmp1.txt","booked_rooms.txt");
}

void view_bookings() {
    FILE* fpi;
    fpi = fopen("hotelnew.txt", "r");
    printf("\n\n>>>>>> BOOKING REQUESTS <<<<<<\n");
    while(fscanf(fpi, "\n%s %s %s %d %f", h.name, h.room, h.wifi, &h.nights,&h.payment) != -1) {
        printf("\n\nName     : %s\n", h.name);
        printf("Room no. : %s\n", h.room);
        printf("Wifi     : %s\n", h.wifi);
        printf("No. of nights stay : %d\n", h.nights);
    }
    fclose(fpi);
}
