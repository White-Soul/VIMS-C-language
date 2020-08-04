#include "user.h"
// 显示缴费界面
void Payment()
{
    fflush(stdin); // 刷新缓冲区
    char a;
    system("cls");
    printf("\t\t\t\t===========================================\n");
    printf("\t\t\t\t|            1.查询账户余额               |\n");
    printf("\t\t\t\t|            2.缴费                       |\n");
    printf("\t\t\t\t|            3.返回上一级                 |\n");
    printf("\t\t\t\t===========================================\n");
    printf("\t\t\t\t|请选择：_\b");
    char i;
    scanf("%c", &i);
    while (i == '\n')
    {
        printf("\t\t\t\t|");
        scanf("%c", &i);
    }
    while ((a = getchar()) != '\n')
        ;
    sleep_time();
    // 选择
    if (i < '1' || i > '3')
    {
        printf("\t\t\t\t|错误：请重试！\n");
        printf("\t\t\t\t|");
        system("pause");
        Payment();
    }
    else
    {
        switch (i)
        {
        case '1':
            display_Am();
            break;
        case '2':
            Pay_face();
            break;
        case '3':
            home();
            break;
        }
    }
}
// 显示余额。
void display_Am()
{
    system("cls");
    // 判断是否是root用户，root用户无法显示余额
    if (!strcmp(User_Own, "root"))
    {
        printf("\t\t\t\t===========================================\n");
        printf("\t\t\t\t|错误：无法查询root用户！\n");
        printf("\t\t\t\t|");
        system("pause");
        sleep_time();
        Payment();
    }
    else
    {
        char US[20] = "user/";
        strcat(US, User_Own);
        FILE *F = fopen(US, "r");
        if (F == NULL)
        {
            printf("\t\t\t\t|Error: E.010...\n");
            printf("\t\t\t\t|");
            system("pause");
            Payment();
        }
        else
        {
            struct user *u = (struct user *)malloc(sizeof(struct user));
            fscanf(F, "%s %s %lf %d", u->id, u->name, &u->Amount, &u->score);
            printf("\t\t\t\t|===========================================\n");
            printf("\t\t\t\t|余额为：%.1lf!\n", u->Amount);
            u->head = NULL;
            Free_U(u);
            fclose(F);
            printf("\t\t\t\t|");
            system("pause");
            sleep_time();
            Payment();
        }
    }
}
// 缴费管理。
void Pay_face()
{
    fflush(stdin);
    char a;
    int i = 0;
    system("cls");
    printf("\t\t\t\t|===========================================\n");
    char An[20] = "user/";
    strcat(An, User_Own);
    FILE *F = fopen(An, "r");
    if (F == NULL)
    {
        printf("\t\t\t\t|Error: E.010...\n");
        printf("\t\t\t\t|");
        system("pause");
        Payment();
    }
    else
    {
        struct user U;
        fscanf(F, "%s %s %lf %d %lf %s", U.id, U.name, &U.Amount, &U.score, &U.Fine, U.phone);
        U.head = NULL;
        while (!feof(F))
        {
            struct vio_infor *h;
            struct vio_infor *z = (struct vio_infor *)malloc(sizeof(struct vio_infor));
            if (z == NULL)
            {
                printf("\t\t\t\t|Error: E.011...");
                printf("\t\t\t\t|");
                system("pause");
                exit(0);
            }
            else
            {
                if (U.head == NULL)
                    U.head = z;
                else
                    h->next = z;
                z->next = NULL;
                h = z;
                fscanf(F, "%d/%d/%d %d %lf %d %d", &z->year, &z->month, &z->day, &z->fraction, &z->fine, &z->flag, &z->days);
                printf("\t\t\t\t|%d|%d/%.2d/%.2d|\t%d\t%.1lf\t%d\t%d\n", ++i, z->year, z->month, z->day, z->fraction, z->fine, z->flag, z->days);
            }
        }
        fclose(F);
        if (U.head == NULL)
        {
            printf("\t\t\t\t|错误：没有违规信息！\n");
            printf("\t\t\t\t|");
            system("pause");
            Payment();
        }
        else
        {

            printf("\t\t\t\t|请输入要缴费的序号：");
            char Sn;
            scanf("%c", &Sn);
            // 选择需要缴费的序号
            while (Sn == '\n')
            {
                printf("\t\t\t\t|");
                scanf("%c", &Sn);
            }
            while ((a = getchar()) != '\n')
                ;
            while (Sn <= '0' || Sn > (i + '0'))
            {
                printf("\t\t\t\t|错误：请重新输入");
                scanf("%c", &Sn);
                while ((a = getchar()) != '\n')
                    ;
            }
            struct vio_infor *in = U.head;
            // 用循环来找到需要缴费的违规信息
            for (int j = 0; j < (Sn - 1 - '0'); j++)
            {
                in = in->next;
            }
            printf("\t\t\t\t|请确认(y/n):");
            char ch;
            scanf("%c", &ch);
            //  判断是否需要缴费
            while (ch == '\n')
            {
                printf("\t\t\t\t|");
                scanf("%c", &ch);
            }
            while ((a = getchar()) != '\n')
                ;
            while (ch != 'y' && ch != 'Y' && ch != 'n' && ch != 'N')
            {
                printf("\t\t\t\t|错误：请重新输入：");
                scanf("%c", &ch);
                while ((a = getchar()) != '\n')
                    ;
            }
            if (ch == 'y' || ch == 'Y')
            {
                // 需要缴费则把用户信息更新
                if (in->flag == 1)
                {
                    printf("\t\t\t\t|错误：已经交过费用！\n");
                }
                else if (U.Amount >= in->fine)
                {
                    FILE *F = fopen(An, "w");
                    in->flag = true;
                    U.Amount -= in->fine;
                    U.Fine -= in->fine;
                    U.score -= in->fraction;
                    in = U.head;
                    fprintf(F, "%s\t%s\t%lf\t%d\t%lf\t%s", U.id, U.name, U.Amount, U.score, U.Fine, U.phone);
                    while (in != NULL)
                    {
                        in->days = Days(in);
                        fprintf(F, "\n%d/%d/%d %d %lf %d %d", in->year, in->month, in->day, in->fraction, in->fine, in->flag, in->days);
                        in = in->next;
                    }
                    printf("\t\t\t\t|缴费成功！！！\n");
                }
                else
                {
                    printf("\t\t\t\t|错误：余额不足！\n");
                }
                printf("\t\t\t\t|");
                system("pause");
                fclose(F);
                Free_V(U.head);
                sleep_time();
                Payment();
            }
            else
            {
                fclose(F);
                Free_V(U.head);
                sleep_time();
                Payment();
            }
        }
    }
}
// 充值操作
void Top_up()
{
    fflush(stdin);
    int i = 0;
    system("cls");
    printf("\t\t\t\t===========================================\n");
    lnit_display();
    printf("\t\t\t\t|请输入需要充值的用户名(ID)：");
    char Id[30] = "", ch;
    while ((ch = getchar()) == '\n')
        printf("\t\t\t\t|");
    while ((ch) != '\n' && ch != ' ')
    {
        if ((ch <= 'z' && ch >= 'a') || (ch >= 'A' && ch <= 'z') || (ch >= '0' && ch <= '9'))
            Id[i++] = ch;
        else
        {
            printf("\t\t\t\t|错误：使用了非法字符！");
            printf("\t\t\t\t|请重新输入：");
            while ((ch = getchar()) == '\n')
                printf("\t\t\t\t|");
            while ((ch = getchar()) != '\n')
                ;
            i = 0;
            strcat(Id, "");
            continue;
        }
        ch = getchar();
    }
    char N[30] = "user/";
    strcat(N, Id);
    FILE *F = fopen(N, "r");
    if (!F)
    {
        printf("\t\t\t\t|Error: E.010...\n");
        system("pause");
    }
    else
    {
        struct user U;
        fscanf(F, "%s %s %lf %d %lf %s", U.id, U.name, &U.Amount, &U.score, &U.Fine, U.phone);
        U.head = NULL;
        while (!feof(F))
        {
            struct vio_infor *h;
            struct vio_infor *z = (struct vio_infor *)malloc(sizeof(struct vio_infor));
            if (z == NULL)
            {
                printf("\t\t\t\t|Error: E.011...");
                printf("\t\t\t\t|");
                system("pause");
                exit(0);
            }
            else
            {
                if (U.head == NULL)
                    U.head = z;
                else
                    h->next = z;
                z->next = NULL;
                h = z;
                fscanf(F, "%d/%d/%d %d %lf %d %d", &z->year, &z->month, &z->day, &z->fraction, &z->fine, &z->flag, &z->days);
            }
        }
        fclose(F);
        printf("\t\t\t\t|请输入需要充值的数值:");
        double n = 0;
        while ((ch = getchar()) == '\n')
            printf("\t\t\t\t|");
        while (ch != '\n')
        {
            if (ch >= '0' && ch <= '9')
            {
                n = n * 10 + ch - '0';
            }
            else
            {
                printf("\t\t\t\t|错误：输入非法！");
                printf("\t\t\t\t|");
                system("pause");
                Top_up();
                return;
            }
            ch = getchar();
        }
        U.Amount += n;
        FILE *fp = fopen(N, "w");
        fprintf(F, "%s\t%s\t%lf\t%d\t%lf\t%s", U.id, U.name, U.Amount, U.score, U.Fine, U.phone);
        struct vio_infor *in = U.head;
        while (in != NULL)
        {
            in->days = Days(in);
            fprintf(F, "\n%d/%d/%d %d %lf %d %d", in->year, in->month, in->day, in->fraction, in->fine, in->flag, in->days);
            in = in->next;
        }
        fclose(F);
        printf("\t\t\t\t|充值成功！\n");
        printf("\t\t\t\t|");
        system("pause");
        Free_V(U.head);
    }
    sleep_time();
    home();
}