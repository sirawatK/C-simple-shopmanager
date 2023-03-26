#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
char fproduct[]={"product.dat"};
char ftransaction[]={"transaction.dat"};
struct product{
    char name[50];
    int quantity;
    int id;
    int price;
    int cost;
};
struct transaction{
    int id;
    char name[50];
    time_t time;
    char type[10];
    int quantity;
    int cost;
    int price;
    int profit;
};
void addproduct(){
    FILE *fp,*ft;
    struct product t1;
    struct transaction t2;
    fp=fopen(fproduct,"ab");
    ft=fopen(ftransaction,"ab");
        printf("\nEnter ID:");
        scanf("%d",&t1.id);
        printf("\nEnter name:");
        scanf("%s",t1.name);
        printf("\nEnter price:");
        scanf("%d",&t1.price);
        printf("\nEnter quantity:");
        scanf("%d",&t1.quantity);
        printf("\nEnter cost:");
        scanf("%d",&t1.cost);
        fwrite(&t1,sizeof(t1),1,fp);

        t2.id = t1.id;
        strcpy(t2.name, t1.name);
        time_t now = time(NULL);
        t2.time = now;
        strcpy(t2.type, "Add");
        t2.quantity = t1.quantity;
        t2.cost=t1.cost;
        t2.price=t1.price;
        t2.profit=0;
        fwrite(&t2,sizeof(t2),1,ft);
    fclose(ft);
    fclose(fp);
}
void displaytransac(){
    system("cls");
    FILE *ft;
    struct transaction t;
    int totalprofit=0;
    ft=fopen(ftransaction,"rb");
        if (ft == NULL) {
            printf("NO Product Transaction!!");
            return;
        }
        printf("\n========================================================\n\n");
        printf("\t\tProduct Trasaction Details\n\n");
        printf("========================================================\n\n");
        printf("ID\tName\t\tType\tQuantity\tPrice\tCost\tProfit\tDate\n\n");
        while(1){
            fread(&t,sizeof(t),1,ft);
            if(feof(ft)){
                break;
            }
            printf("%d\t", t.id);
            printf("%s\t\t", t.name);
            printf("%s\t", t.type);
            printf("%d\t\t", t.quantity);
            printf("%d\t", t.price);
            printf("%d\t", t.cost);
            printf("%d\t",t.profit);
            char *time_string = ctime(&t.time);
            char *final_time = strtok(time_string, "\n");
            printf("%s\t\n\n", final_time);
            totalprofit+=t.profit;
        }
        printf("Total profit : %d\n\n",totalprofit);
        printf("========================================================\n\n");
    fclose(ft); 
}
void displayproduct(){
    system("cls");
    FILE *fp;
    struct product t;
    fp=fopen(fproduct,"rb");
        if (fp == NULL) {
            printf("No Product!!");
            return;
        }
        printf("\n========================================================\n\n");
        printf("\t\tAll Product Details\n\n");
        printf("========================================================\n\n");
        printf("ID\tName\t\tPrice\tQuantity\tCost\n\n");
        while(1){
            fread(&t,sizeof(t),1,fp);
            if(feof(fp)){
                break;
            }
            printf("%d\t",t.id);
            printf("%s\t\t",t.name);
            printf("%d\t",t.price);
            printf("%d\t\t",t.quantity);
            printf("%d\t\n\n",t.cost);
        }
        printf("========================================================\n\n");
    fclose(fp);     
}
void modifyproduct(){
    FILE *fp,*fp1,*ft;
    struct product t;
    struct transaction t2;
    int id,found=0,count;
    fp=fopen(fproduct,"rb");
    fp1=fopen("temp.dat","wb");
    ft=fopen(ftransaction,"ab");
        printf("\nEnter The Product ID You Want To Modify:");
        scanf("%d",&id);
        while(1){
            fread(&t,sizeof(t),1,fp);
            if(feof(fp)){
                break;
            }
            if(t.id==id){
                found=1;
                printf("\nEnter ID:");
                scanf("%d",&t.id);
                fflush(stdin);
                printf("\nEnter name:");
                scanf("%s",t.name);
                printf("\nEnter price:");
                scanf("%d",&t.price);
                printf("\nEnter quantity:");
                scanf("%d",&t.quantity);
                printf("\nEnter cost:");
                scanf("%d",&t.cost);
                if(t.quantity==0){
                    count=0;
                }
                else{
                    fwrite(&t,sizeof(t),1,fp1);
                }
                t2.id = t.id;
                strcpy(t2.name, t.name);
                time_t now = time(NULL);
                t2.time = now;
                strcpy(t2.type,"Modify");
                t2.quantity=t.quantity;
                t2.cost=t.cost;
                t2.price=t.price;
                t2.profit=0;
                fwrite(&t2,sizeof(t2),1,ft);
            }
            else{
                fwrite(&t,sizeof(t),1,fp1);
            }
        }
        fclose(fp);
        fclose(fp1);
        fclose(ft);
        if(found==0){
            printf("No Product Found\n\n");
        }
        else{
            fp=fopen(fproduct,"wb");
            fp1=fopen("temp.dat","rb");
            while(1){
                fread(&t,sizeof(t),1,fp1);
                if(feof(fp1)){
                    break;
                }
                fwrite(&t,sizeof(t),1,fp);
            }
        }
        fclose(fp);
        fclose(fp1);
}
void deleteproduct(){
    FILE *fp,*fp1,*ft;
    struct product t;
    struct transaction t2;
    int count=0,id,a;
    char b;
    printf("\nEnter The Product ID You Want To Delete:");
    scanf("%d",&a);
    printf("\nAre You Sure To Delete ID:%d [y/n]:",a);
    scanf(" %c", &b);
    switch (b){
        case 'n':
            break;
        case 'y':{
            id=a;
            fp=fopen(fproduct,"rb");
            fp1=fopen("temp.dat","wb");
                while(1){
                    fread(&t,sizeof(t),1,fp);
                    if(feof(fp)){
                        break;
                    }
                    if(t.id==id){
                        count=1;
                        ft=fopen(ftransaction,"ab");
                            t2.id=id;
                            strcpy(t2.name,t.name);
                            time_t now = time(NULL);
                            t2.time = now;
                            strcpy(t2.type,"Delete");
                            t2.quantity = 0;
                            t2.cost = t.cost;
                            t2.price = t.price;
                            t2.profit=0;
                        fwrite(&t2,sizeof(t2),1,ft);
                        fclose(ft);
                    }
                    else{  
                        fwrite(&t,sizeof(t),1,fp1);        
                    }
                }
            fclose(fp);
            fclose(fp1);
            if(count==0){
                printf("No This Product");
                break;
            }
            fp=fopen(fproduct,"wb");
            fp1=fopen("temp.dat","rb");
                while(1){
                    fread(&t,sizeof(t),1,fp1);
                    if(feof(fp1)){
                        break;
                    }
                    fwrite(&t,sizeof(t),1,fp);
                }
            fclose(fp);
            fclose(fp1);
        }
            break;
        default:
            break;
    }
}
void manageproduct(){
    int n,back;
    while(1){
        system("cls");
        printf("========================================================\n");
        printf("\t\tProduct Management\n\n");
        printf("========================================================\n");
        printf("1. Add Product\n\n");
        printf("2. Display All Product\n\n");
        printf("3. Modify The Product\n\n");
        printf("4. Delete The Product\n\n");
        printf("0. Back\n\n");
        printf("Enter your choice:");
        scanf("%d",&n);
        switch(n){
            case 1:addproduct();
                    break; 
            case 2:displayproduct();
                    break;
            case 3:displayproduct();modifyproduct();
                    break;
            case 4:displayproduct();deleteproduct();
                    break;
            case 0:back=1;
                    break;
        }
        if(back==1){
            break;
        }
        else{
            getch();
        }
    }
}
void displayshop(){
    system("cls");
    FILE *fp;
    struct product t;
    fp=fopen(fproduct,"rb");
        if (fp == NULL) {
            return;
        }
        printf("\n========================================================\n\n");
        printf("\t\tWelcome To The Shop\n\n");
        printf("========================================================\n\n");
        printf("ID\tProduct Name\tPrice\tQuantity\n\n");
        while(1){
            fread(&t,sizeof(t),1,fp);
            if(feof(fp)){
                break;
            }
            printf("%d\t",t.id);
            printf("%s\t\t",t.name);
            printf("%d\t",t.price);
            printf("%d\t\t\n\n",t.quantity);
        }
        printf("========================================================\n\n");
    fclose(fp);     
}
void purchaseproduct(){
    char b;
    int id,a,quan,count=0;
    FILE *fp,*ft,*ftemp;
    struct product p;
    struct transaction t;
    system("cls");
    fp=fopen(fproduct,"rb");
    if (fp == NULL){
        printf("No Product In This Shop!!");
        return;
    }
    fclose(fp);
    displayshop();
    printf("Enter Product ID You Want to Buy :");
    scanf("%d",&a);
    printf("Are You Sure To buy ID:%d [y/n] :",a);
    scanf(" %c",&b);
    switch(b){
        case 'n':
            break;
        case 'y':{
            id=a;
            fp=fopen(fproduct,"rb");
            ftemp=fopen("temp.dat","wb");
            while(1){
                fread(&p,sizeof(p),1,fp);
                if(feof(fp)){
                    break;
                }
                if(p.id==id){
                    count=1;
                    printf("Enter Quantity You Want To Buy:");
                    scanf("%d",&quan);
                    p.quantity-=quan;
                    if(p.quantity==0){
                        count=1;
                    }
                    else if(p.quantity<0){
                        p.quantity+=quan;
                        fwrite(&p,sizeof(p),1,ftemp);
                        printf("Not Enough Product");
                        break;
                    }
                    else{
                        fwrite(&p,sizeof(p),1,ftemp);
                    }
                    ft=fopen(ftransaction,"ab");
                        t.id=id;
                        strcpy(t.name,p.name);
                        time_t now = time(NULL);
                        t.time = now;
                        strcpy(t.type,"Sales");
                        t.quantity = quan;
                        t.cost = p.cost;
                        t.price = p.price;
                        t.profit = (p.price-p.cost)*quan;
                        fwrite(&t,sizeof(t),1,ft);
                    fclose(ft);
                    printf("Total Amount: %d",quan*(p.price));
                }
                else{
                    fwrite(&p,sizeof(p),1,ftemp);
                }
            }
            if(count==0){
                printf("No Product In This Shop!!!");
            }
            fclose(fp);
            fclose(ftemp);

            fp=fopen(fproduct,"wb");
            ftemp=fopen("temp.dat","rb");
            while(1){
                fread(&p,sizeof(p),1,ftemp);
                if(feof(ftemp)){
                    break;
                }
                fwrite(&p,sizeof(p),1,fp);
            }
            fclose(fp);
            fclose(ftemp);
        }
            break;
        default:
            break;
    }
}
int main(){
    FILE *fp;
    int n;
    while(1){
        system("cls");
        printf("========================================================\n\n");
        printf("\t\tShop Management\n\n");
        printf("========================================================\n\n");
        printf("1. Manage Product\n\n");
        printf("2. Purchase Product\n\n");
        printf("3. Product Transaction\n\n");
        printf("0. Exit\n\n");
        printf("Enter your choice:");
        scanf("%d",&n);
        switch(n){
            case 1:manageproduct();
                    break;
            case 2:purchaseproduct();
                    break;
            case 3:displaytransac();
                    break;
            case 0:exit(0);
                    break;
        }
        getch();
    }
    return 0;   
}