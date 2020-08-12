#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<ctype.h>
#define SPACE 5
struct library
{
    int id;
    char name[20] ;
    char gender[6];
    int age ;
    char bookname[20];
    char phoneNo[20];
    struct library *next;
} *head ;
struct idTreeNode
{
    int id;
    struct idTreeNode *left;
    struct idTreeNode *right;
};
//main functions
struct library *create(struct library *head);
void display (struct library *head);
struct library *sort (struct library *head);
void *search(struct library *head,char NAME[]);
struct library *insert(struct library *head);
struct library *del(struct library *head,char NAME[]);
struct library *modify(struct library *head,char NAME[]);
struct library *getNewNode();
struct library *reverse(struct library *head);
//validation functions
int getAgeInput();
void login();
int isIDunique(struct library* head, int id);
//tree functions
struct idTreeNode* idTreeID();
struct idTreeNode* sortedArrToBst(int*,int,int);
struct idTreeNode* getNewTreeNode(int);
void sortArray(int*,int);
void draw_tree_hor2(struct idTreeNode *tree,int depth,char *path,int right);
void draw_tree(struct idTreeNode *tree);
void printIDTree(struct library*);
//display functions
void headDisplay();
void mainDisplay();
void createDisplay();
void displayDislpay();
void info();
int n, j ;
//int a[20] ;
void main ()
{
    char NAME[50];
    int ch ;
    struct library *head=NULL;
    headDisplay();
    login();
    while(1)
    {
        mainDisplay();
        printf("\t\t\t\t\t\t");
        scanf ("%d",&ch ) ;
        switch (ch)
        {
        case 1:
            head =create(head);
            break;
        case 2 :
            display(head);
            break;
        case 3 :
            sort(head);
            display(head) ;
            break;
        case 4 :
            headDisplay();
            printf("\t\t\t\t\tENTER NAME OF PERSON TO SEARCH : ");
            scanf("%s",NAME);
            search (head,NAME) ;
            break ;
        case 5 :
            head=insert(head);
            break;
        case 6 :
            headDisplay();
            printf("\t\t\t\t\t\tENTER NAME OF PERSON WHOSE RECORD SHOULD BE DELETED : ");
            scanf("%s",NAME);
            head=del(head,NAME);
            break;
        case 7:
            headDisplay();
            printf("\t\t\t\t\t\tENTER NAME OF PERSON WHOSE RECORD SHOULD BE MODIFIED : ");
            scanf("%s",NAME);
            head=modify(head,NAME);
            break;
        case 8:
            head = reverse(head);
            headDisplay();
            display(head);
            break;
        case 9:
            printIDTree(head);
            break;
        case 10:
            info();
            break;
        case 11:
            exit(0);
            break;
        default :
            printf("\t\t\t\t\t\tWRONG CHOICE!!");
            break;
        }
    }
}
struct library *create(struct library* head)
{
    int ch;
    struct library *p, *temp;
    headDisplay();
    createDisplay();
    scanf("%d",&ch);
    headDisplay();
    switch(ch)
    {
    case 1:
        printf ("\t\t\t\t\t\tENTER HOW MANY RECORDS TO ENTER : ");
        scanf ("%d",&n) ;
        temp = head;
        for (int i=0 ; i<n ; i++)
        {
            headDisplay();
            temp = (struct library*)malloc(sizeof(struct library));
            printf("\t\t\t___________________________________________________________________________\n");
            int FLAG = 0;
            do
            {
                if(FLAG)
                    printf("\n\t\t\t\t\t\tID IS ALREADY PRESENT!\n");
                printf("\n\t\t\t\t\t\tENTER ID : ");
                scanf("%d",&(temp->id));
                FLAG = 1;
            }
            while(!isIDunique(head, temp->id));
            printf("\n\t\t\t\t\t\tENTER NAME : ") ;
            scanf ("%s",temp->name) ;
            temp->age=getAgeInput();
            printf("\n\t\t\t\t\t\tENTER gender [M/F] : ");
            scanf("%s",temp->gender);
            printf("\n\t\t\t\t\t\tENTER BOOK NAME : ");
            scanf("%s",temp->bookname);
            while(1)
            {
                printf("\n\t\t\t\t\t\tENTER PHONE NUMBER : ");
                scanf("%s",&(temp->phoneNo));
                if(strlen(temp->phoneNo)==10)
                    break;
                printf("\t\t\t\t\t\tINVALID PHONE NUMBER!!");
            }
            if(head == NULL)
            {
                head = temp;
                temp->next = NULL;
            }
            else
            {
                p=head;
                while(p->next!=NULL)
                    p=p->next;
                p->next=temp;
                temp->next=NULL;
            }
            printf("\n\t\t\t\t\t\tRECORD SUCESSFULLY ADDED!!\n");
            //sleep(1);
            printf("\n\t\t\t\t\t\tPRESS ANY KEY TO CONTINUE");
            getch();
            printf("\n\n");
        }
        return head;
        break;
    case 2:
        main();
        break;
    case 3:
        exit(0);
        break;
    default:
        printf("\t\t\t\t\tWRONG CHOICE");
        break;
    }
}
void display(struct library *head)
{
    int space;
    headDisplay();
    printf("\t\t\t\t  ID         NAME             AGE      GENDER           BOOK NAME           PHONE NUMBER       \n");
    printf("\t\t\t\t----------------------------------------------------------------------------------------\n");
    struct library *p;
    p = head;
    while(p!=NULL)
    {
        printf("\t\t\t\t");
        printf(" %d\t    ",p->id);
        space=18-strlen(p->name);
        printf("%s",p->name);
        while(space>0)
        {
            printf(" ");
            space--;
        }
        printf("%d  \t %s \t\t %s\t          %s\n",p->age,p->gender,p->bookname,p->phoneNo);
        p=p->next;
    }
    printf("\n");
}
struct library *sort(struct library *head)
{
    struct library *p, *q, *temp;
    temp=(struct library*)malloc(sizeof(struct library)*6);
    for(p=head; p->next!=NULL; p=p->next)
    {
        for(q=p->next; q!=NULL; q=q->next)
        {
            if(p->age > q->age)
            {
                temp->id=p->id;
                p->id=q->id;
                q->id=temp->id;
                temp->age=p->age;
                p->age=q->age;
                q->age=temp->age;
                strcpy(temp->name,p->name);
                strcpy(p->name,q->name);
                strcpy(q->name,temp->name);
                strcpy(temp->bookname,p->bookname);
                strcpy(p->bookname,q->bookname);
                strcpy(q->bookname,temp->bookname);
                strcpy(temp->phoneNo,p->phoneNo);
                strcpy(p->phoneNo,q->phoneNo);
                strcpy(q->phoneNo,temp->phoneNo);
                strcpy(temp->gender,p->gender);
                strcpy(p->gender,q->gender);
                strcpy(q->gender,temp->gender);
            }
        }
    }
}
void *search(struct library *head,char NAME[])
{
    int space1,space2;
    struct library *p;
    int flag=0;
    if(strcmp(head->name,NAME)==0)
    {
        printf("\t\t\t\t\t\t\tRECORD FOUND\n\n");
        printf("\t\t\t\t  ID         NAME             AGE      GENDER           BOOK NAME             PHONE NUMBER       \n");
        printf("\t\t\t\t----------------------------------------------------------------------------------------\n");
        printf("\t\t\t\t");
        printf(" %d\t    ",head->id);
        space1=18-strlen(head->name);
        printf("%s",head->name);
        while(space1>0)
        {
            printf(" ");
            space1--;
        }
        printf("%d  \t %s \t\t %s\t          %s\n",head->age,head->gender,head->bookname,head->phoneNo);
        flag++;
    }
    p=head;
    while(p->next!=NULL)
    {
        if(strcmp(p->next->name,NAME)==0)
        {
            printf("\n\t\t\t\t\t\tRECORD FOUND!!\n");
            printf("\t\t\t\t  ID         NAME             AGE      GENDER           BOOK NAME            PHONE NUMBER       \n");
            printf("\t\t\t\t----------------------------------------------------------------------------------------\n");
            printf("\t\t\t\t");
            printf(" %d\t    ",p->next->id);
            space2=18-strlen(p->next->name);
            printf("%s",p->next->name);
            while(space2>0)
            {

                printf(" ");
                space2--;
            }
            printf("%d  \t %s \t\t %s\t          %s\n",p->next->age,p->next->gender,p->next->bookname,p->next->phoneNo);
        }
        p=p->next;
        flag++;
    }
    if(flag==0)
        printf("\n\t\t\t\t\t\tRECORD DOES NOT EXIST!!!\n\n");
}
struct library *insert(struct library *head)
{
    int pos;
    struct library *p,*temp;
    temp=(struct library*)malloc(sizeof(struct library)*1);
    headDisplay();
    printf("\t\t\t\t\t\tENTER POSITION WHERE RECORD SHOULD BE ADDED : ");
    scanf("%d",&pos);
    if(pos==1)
    {
        int FLAG = 0;
            do
            {
                if(FLAG)
                    printf("\n\t\t\t\t\t\tID IS ALREADY PRESENT!\n");
                printf("\n\t\t\t\t\t\tENTER ID : ");
                scanf("%d",&(temp->id));
                FLAG = 1;
            }
            while(!isIDunique(head, temp->id));
        printf("\n\t\t\t\t\t\tENTER NAME : ");
        scanf("%s",(temp->name));
        temp->age=getAgeInput();
        while(1)
        {
            printf("\n\t\t\t\t\t\tENTER PHONE NUMBER : ");
            scanf("%s",&(temp->phoneNo));
            if(strlen(temp->phoneNo)==10)
                break;
            printf("\t\t\t\t\t\tINVALID PHONE NUMBER!!");
        }
        printf("\n\t\t\t\t\t\tENTER BOOK NAME : ");
        scanf("%s",(temp->bookname));
        printf("\n\t\t\t\t\t\t\tENTER GENDER[M/F] : ");
        scanf("%s",(temp->gender));
        temp->next=head;
        head=temp;
        return head;
    }
    p=head;
    for(int i=1; i<pos-1 && p!=NULL; i++)
        p=p->next;
    if(p==NULL)
        printf("\n\t\t\t\t\t\t*POSITION OUT OF RANGE*\n\n");
    else
    {
        int FLAG = 0;
            do
            {
                if(FLAG)
                    printf("\n\t\t\t\t\t\tID IS ALREADY PRESENT!\n");
                printf("\n\t\t\t\t\t\tENTER ID : ");
                scanf("%d",&(temp->id));
                FLAG = 1;
            }
            while(!isIDunique(head, temp->id));
        printf("\t\t\t\t\t\tENTER NAME : ");
        scanf("%s",(temp->name));
        temp->age=getAgeInput();
        while(1)
        {
            printf("\n\t\t\t\t\t\tENTER PHONE NUMBER : ");
            scanf("%s",&(temp->phoneNo));
            if(strlen(temp->phoneNo)==10)
                break;
            printf("\t\t\t\t\t\tINVALID PHONE NUMBER!!");
        }
        printf("\n\t\t\t\t\t\tENTER BOOK NAME : ");
        scanf("%s",(temp->bookname));
        printf("\n\t\t\t\t\tENTER GENDER[M/F] : ");
        scanf("%s",(temp->gender));
        temp->next=p->next;
        p->next=temp;
    }
    return head;
}
struct library *del(struct library *head,char NAME[])
{
    struct library *temp,*p;
    if(strcmp(head->name,NAME)==0)
    {
        temp=head;
        head=temp->next;
        free(temp);
        return head;
    }
    p=head;
    while(p->next!=NULL)
    {
        if(strcmp(p->next->name,NAME)==0)
        {
            temp=p->next;
            p->next=temp->next;
            free(temp);
            return head;
        }
        p=p->next;
    }

}
struct library *modify(struct library *head,char NAME[])
{
    struct library *p;
    int choice,space3,space4;
    char ans1,ans2;
    int flag=0,chs=0;
    int FLAG = 0;
    int FLAG1 = 0;
    if(strcmp(head->name,NAME)==0)
    {
        printf("\t\t\t\t\tRECORD FOUND\n");
        printf("\t\t\t\t  ID         NAME             AGE      GENDER           BOOK NAME          PHONE NUMBER       \n");
        printf("\t\t\t\t----------------------------------------------------------------------------------------\n");
        printf("\t\t\t\t");
        printf(" %d\t    ",head->id);
        space3=18-strlen(head->name);
        printf("%s",head->name);
        while(space3>0)
        {
            printf(" ");
            space3--;
        }
        printf("%d  \t %s \t\t %s\t          %s\n",head->age,head->gender,head->bookname,head->phoneNo);
        do
        {
            printf("\n\t\t\t\t\t\t1.MODIFY ID");
            printf("\n\t\t\t\t\t\t2.MODIFY NAME");
            printf("\n\t\t\t\t\t\t3.MODIFY AGE");
            printf("\n\t\t\t\t\t\t4.MODIFY PHONE NUMBER");
            printf("\n\t\t\t\t\t\t5.MODIFY BOOK NAME");
            printf("\n\t\t\t\t\t\t6.MODIFY GENDER\n");
            printf("\t\t\t\t\t\t");
            scanf("%d",&choice);
            switch (choice)
            {
            case 1:
            do
            {
                if(FLAG)
                    printf("\n\t\t\t\t\t\tID IS ALREADY PRESENT!\n");
                printf("\n\t\t\t\t\t\tENTER ID : ");
                scanf("%d",&(head->id));
                FLAG = 1;
            }
            while(!isIDunique(head, head->id));
                break;
            case 2:
                printf("\t\t\t\t\t\tENTER NEW NAME :\n");
                scanf("%s",(head->name));
                break;
            case 3:
                head->age=getAgeInput();
                break;
            case 4:
                while(1)
                {
                    printf("\n\t\t\t\t\t\tENTER PHONE NUMBER : ");
                    scanf("%s",&(head->phoneNo));
                    if(strlen(head->phoneNo)==10)
                        break;
                    printf("\t\t\t\t\t\tINVALID PHONE NUMBER!!");
                }
                break;
            case 5:
                printf("\t\t\t\t\t\tENTER NEW BOOK NAME : \n");
                scanf("%s",&(head->bookname));
                break;
            case 6:
                printf("\t\t\t\t\t\tENTER NEW GENDER : \n");
                scanf("%s",&(head->gender));
                break;
            default :
                printf("Please enter correct choice to proceed \n");
                break;
            }
            printf("\t\t\t\t\t\tPRESS 1 TO CONTINUE MODIFY:");
            scanf("%d",&chs);
        }
        while(chs==1);
        flag++;
        return head;
    }
    p=head;
    while(p->next!=NULL)
    {
        if(strcmp(p->next->name,NAME)==0)
        {
            printf("\t\t\t\t\tRECORD FOUND\n");
            printf("\t\t\t\t  ID         NAME             AGE      GENDER           BOOK NAME             PHONE NUMBER       \n");
            printf("\t\t\t\t--------------------------------------------------------------------------------------------------------------\n");
            printf("\t\t\t\t");
            printf(" %d\t    ",head->id);
            space4=18-strlen(head->name);
            printf("%s",head->name);
            while(space4>0)
            {
                printf(" ");
                space4--;
            }
            printf("%d  \t %s \t\t %s          %s\n",head->age,head->gender,head->bookname,head->phoneNo);
            do
            {
                printf("\n\t\t\t\t\t\t1.MODIFY ID");
                printf("\n\t\t\t\t\t\t2.MODIFY NAME");
                printf("\n\t\t\t\t\t\t3.MODIFY AGE");
                printf("\n\t\t\t\t\t\t4.MODIFY PHONE NUMBER");
                printf("\n\t\t\t\t\t\t5.MODIFY BOOK NAME");
                printf("\n\t\t\t\t\t\t7.MODIFY GENDER\n");
                scanf("%d",&choice);
                switch (choice)
                {
                case 1:
            do
            {
                if(FLAG1)
                    printf("\n\t\t\t\t\t\tID IS ALREADY PRESENT!\n");
                printf("\n\t\t\t\t\t\tENTER ID : ");
                scanf("%d",&(p->next->id));
                FLAG1 = 1;
            }
            while(!isIDunique(head,p->next->id));
                    break;
                case 2:
                    printf("\t\t\t\t\t\tENTER NEW NAME :\n");
                    scanf("%s",(p->next->name));
                    break;
                case 3:
                    p->next->age=getAgeInput();
                    break;
                case 4:
                    while(1)
                    {
                        printf("\n\t\t\t\t\t\tENTER PHONE NUMBER : ");
                        scanf("%s",&(p->next->phoneNo));
                        if(strlen(p->next->phoneNo)==10)
                            break;
                        printf("\t\t\t\t\t\tINVALID PHONE NUMBER!!");
                    }
                    break;
                case 5:
                    printf("\t\t\t\t\t\tENTER NEW BOOK NAME : ");
                    scanf("%s",&(p->next->bookname));
                    break;
                case 6:
                    printf("\t\t\t\t\t\tENTER NEW GENDER : ");
                    scanf("%s",&(p->next->gender));
                    break;
                default :
                    printf("\t\t\t\t\t\tPlease enter correct choice to proceed \n");
                    break;
                }
                printf("\t\t\t\t\t\tPRESS 1 TO CONTINUE MODIFICATION ELSE PRESS 0 TO GO BACK");
                scanf("%d",&chs);
            }
            while(chs==1);
        }
        p=p->next;
        flag++;
        return head;
    }
    if(flag==0)
        printf("\n\n\t\t\t\t\t\tNOT FOUND!!\n\n");
}
void headDisplay()
{
    system("cls");
    printf ("\n");
    printf ("\n");
    printf ("\n");
    printf ("\n");
    printf("\t\t\t\t\t\t$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
    printf("\t\t\t\t\t\t$$$$                                                    $$$$\n");
    printf("\t\t\t\t\t\t$$$$             LIBRARY MANAGEMENT SYSTEM              $$$$\n");
    printf("\t\t\t\t\t\t$$$$                                                    $$$$\n");
    printf("\t\t\t\t\t\t$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n\n");
}
void mainDisplay()
{
    printf("\t\t\t\t____________________________________________________________________________________________\n");
    printf("\t\t\t\t............................................................................................\n\n");
    printf("\t\t\t\t\t\t\t\t\t1.CREATE\n");
    printf("\t\t\t\t\t\t\t\t\t2.DISPLAY\n");
    printf("\t\t\t\t\t\t\t\t\t3.SORT\n");
    printf("\t\t\t\t\t\t\t\t\t4.SEARCH\n");
    printf("\t\t\t\t\t\t\t\t\t5.INSERT\n");
    printf("\t\t\t\t\t\t\t\t\t6.DELETE\n");
    printf("\t\t\t\t\t\t\t\t\t7.MODIFY\n");
    printf("\t\t\t\t\t\t\t\t\t8.REVERSE RECORD\n");
    printf("\t\t\t\t\t\t\t\t\t9.PRINT TREE OF ID'S\n");
    printf("\t\t\t\t\t\t\t\t\t10.INFO\n");
    printf("\t\t\t\t\t\t\t\t\t11.EXIT\n");
}
void createDisplay()
{
    printf("\t\t\t\t\t\t\t\t\t1.ADD NEW RECORD\n");
    printf("\t\t\t\t\t\t\t\t\t2.GO BACK\n");
    printf("\t\t\t\t\t\t\t\t\t3.EXIT\n");
}
void info()
{
    headDisplay();
    printf("LIBRARY MANAGEMENT SYSTEM\nVERSION_1.0\nDEVELOPER_DARSHAN JOGAD\n\n");
    printf("1.CREATE FUNCTION\nTHIS FUNCTION GIVES YOU FUNCTIONALITY TO CREATE COSTUMER RECORDS\n\n");
    printf("2.DISPLAY FUNCTION\nTHIS FUNCTION GIVES YOU FUNCTIONALITY TO DISPLAY ALL PRESENT DATA IN DATABASE\n\n");
    printf("3.SORT FUNCTION\nTHIS FUNCTION GIVES YOU FUNCTIONALITY TO SORT RECORD IN ACENDING ORDER BY AGE\n\n");
    printf("4.SEARCH FUNCTION\nTHIS FUNCTION GIVES YOU FUNCTIONALITY TO SEARCH RECORD BY PERSON NAME\n\n");
    printf("5.INSERT FUNCTION\nTHIS FUNCTION GIVES YOU FUNCTIONALITY TO INSERT RECORD AT ANY LOCATION IN PRESENT DATA BASE\n\n");
    printf("6.DELETE FUNCTION\nTHIS FUNCTION GIVES YOU FUNCTIONALITY TO DELETE ANY PERSONS RECORD\n\n");
    printf("7.MODIFY FUNCTION\nTHIS FUNCTION GIVES YOU FUNCTIONALITY TO MODIFY RECORD\n");
    printf("*YOU CAN MODIFY ANY PERSON RECORD BY SEARCHING HIS/HER RECORD BY HIS/HER NAME\n");
    printf("*YOU CAN MODIFY HIS/HER...\n1.NAME\n2.AGE\n3.GENDER\n4.ID\n5.PHONE NUMBER\n6.POLICY NUMBER\n\n");
    printf("8.REVERSE FUNCTION\nTHIS FUNCTION GIVES YOU FUNCTIONALITY TO ALTER ALL RECORDS UPSIDE DOWN\n\n");
    printf("9.TREE FUNCTION\nTHIS FUNCTION GIVES YOU FUNCTIONALITY TO DISPLAY ALL ID IN A GRAPHICAL SORTED HORIZONTAL TREE\n\n");
    printf("10.INFO FUNCTION\nTHIS FUNCTION GIVES YOU ALL INFORMATION CUM USERGUIDE FOR THIS SOFTWARE\n\n");
    printf("11.EXIT FUNCTION\nTHIS FUNCTION JUST EXIT YOU FROM THIS SOFTWARE\n\n");
}
struct library *reverse(struct library *head)
{
    struct library *rev = NULL;
    struct library *temp = head;
    struct library *temp1;
    while(temp!=NULL)
    {
        if (rev == NULL)
        {
            rev = temp;
            temp = temp->next;
            rev->next = NULL;
            continue;
        }
        temp1 = temp;
        temp = temp->next;
        temp1->next = rev;
        rev = temp1;
    }
    return rev;
}
struct idTreeNode* getTreeID(struct library *head,int n)
{
    int array[n];
    int point=0;
    struct library* temp=head;
    while(temp!=NULL)
    {
        array[point++]=temp->id;
        temp=temp->next;
    }
    sortArray(array,n);
    return sortedArrToBst(array, 0, n-1);
}
struct idTreeNode* sortedArrToBst(int A[], int start, int end)
{
    if(start > end)
        return NULL;
    int mid = (start+end)/2;
    struct idTreeNode* root = getNewTreeNode(A[mid]);
    root->left = sortedArrToBst(A, start, mid-1);
    root->right = sortedArrToBst(A, mid+1, end);
    return root;
}
struct idTreeNode*  getNewTreeNode (int x)
{
    struct idTreeNode*  temp = (struct idTreeNode*)malloc(sizeof(struct idTreeNode));
    temp->id = x;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}
void sortArray(int A[], int n)
{
    int flag = 0;
    int temp;
    for (int i = 0; i < n; ++i)
    {
        flag = 0;
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (A[j] > A[j+1])
            {
                flag = 1;
                temp = A[j];
                A[j] = A[j+1];
                A[j+1] = temp;
            }
        }
        if (!flag)
            break;
    }
}
//tree draw functions
void draw_tree_hor2(struct idTreeNode *tree, int depth, char *path, int right)
{
    if (tree== NULL)
        return;
    depth++;
    draw_tree_hor2(tree->right, depth, path, 1);
    path[depth-2] = 0;
    if(right)
        path[depth-2] = 1;
    if(tree->left)
        path[depth-1] = 1;
    printf("\n");
    for(int i=0; i<depth-1; i++)
    {
        if(i == depth-2)
            printf("+");
        else if(path[i])
            printf("|");
        else
            printf(" ");
        for(int j=1; j<SPACE; j++)
            if(i < depth-2)
                printf(" ");
            else
                printf("-");
    }
    printf("%d\n", tree->id);
    for(int i=0; i<depth; i++)
    {
        if(path[i])
            printf("|");
        else
            printf(" ");
        for(int j=1; j<SPACE; j++)
            printf(" ");
    }
    draw_tree_hor2(tree->left, depth, path, 0);
}
void draw_tree(struct idTreeNode *tree)
{
    char path[255] = {};
    draw_tree_hor2(tree, 0, path, 0);
}
void printIDTree(struct library* head)
{
    headDisplay();
    printf("\n\n\n");
    struct idTreeNode *root=getTreeID(head,n);
    if(root)
        {draw_tree(root);
        printf("\n\n\n");
        }
    else
    {
        printf("\t\t\t\t\t\tNO DATA AVAILABLE\n");
    }
}
void login()
{
    char dpassword[30]="GHRCEM";
    char password[30];
    char dusername[50]="ADMIN";
    char username[50];
    int p;
    do
    {
        printf("\t\t\t\t\t\t\t\tUSERNAME : ");
        scanf("%s",username);
        printf("\n\t\t\t\t\t\t\t\t(**please press \"CTRL ENTER\" after typying password)");
        printf("\n\t\t\t\t\t\t\t\tPASSWORD : ");
        p=0;
        do
        {
            password[p]=getch();
            if(password[p]!='\n')
                printf("*");
            p++;
        }
        while(password[p-1]!='\n');
        password[p-1]='\0';
        if(strcmp(dpassword,password)==0 && strcmp(dusername,username)==0)
        {
            headDisplay();
        }
        else
        {
            printf("\n\t\t\t\t\t\t\t\tWRONG USERNAME OR PASSWORD\n");
            printf("\n\t\t\t\t\t\t\t\t\"PRESS ANY KEY TO TRY AGAIN\" :");
            getch();
            headDisplay();
        }
    }
    while((strcmp(dpassword,password))!=0 || (strcmp(dusername,username))!=0);
}
int getAgeInput()
{
    int age,flag=0;
    while(1)
    {
        if(flag==1)
            printf("\t\t\t\t\t\tYOU ARE TOO OLD\n");
        else if(flag==2)
            printf("\t\t\t\t\t\tAGE CANT BE LESS THAN ONE\n");
        printf("\n\t\t\t\t\t\tENTER AGE : ");
        scanf("%d",&age);
        if(age<=0)
            flag=2;
        else if(age>101)
            flag=1;
        else
            break;
    }
    return age;
}
int isIDunique(struct library* head, int id)
{
    struct library* temp = head;
    while(temp!=NULL)
    {
        if(temp->id == id)
            return 0;
        temp = temp->next;
    }
    return 1;
}
