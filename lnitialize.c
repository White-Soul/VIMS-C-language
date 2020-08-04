#include "user.h"
extern bool limit;
// home函数显示系统主界面。
void home()
{
    fflush(stdin);
    system("cls");
    printf("\t\t\t\t===========================================\n");
    printf("\t\t\t\t|               1.添加用户信息            |\n");
    printf("\t\t\t\t|               2.违规信息查询            |\n");
    printf("\t\t\t\t|               3.缴费充值管理            |\n");
    printf("\t\t\t\t|               4.帮助                    |\n");
    printf("\t\t\t\t|               q.退出系统                |\n");
    printf("\t\t\t\t===========================================\n");
    printf("\t\t\t\t|请选择：_\b");
    char n, ch;
    scanf("%c", &n);
    while (n == '\n') // 如果刚开始输入\n
    {
        printf("\t\t\t\t|");
        scanf("%c", &n);
    }
    while (ch = getchar() != '\n') // 将多余的输入读掉
        ;
    sleep_time();
    // 进行选择
    if (n == 'q')
    {
        limit = false;
        Start();
    }
    else if (n > '4' || n < '1')
    {
        printf("\t\t\t\t|Error: E.009...\n");
        printf("\t\t\t\t|");
        system("pause");
        home();
    }
    else
    {
        switch (n)
        {
        case '1':
            if (limit)
                install_dp();
            else
            {
                printf("\t\t\t\t|Error: E.014...\n");
                printf("\t\t\t\t|");
                system("pause");
                home();
            }
            break;
        case '2':
            Inquire();
            break;
        case '3':
            if (limit)
                Top_up();
            else
                Payment();
            break;
        case '4':
            Help();
            break;
        default:
            break;
        }
    }
}
// lnit函数进行系统初始化。
void lnit()
{
    struct vio_infor *s;
    struct user_passwd *us = list();

    while (us) // 如果用户存在
    {
        char N[20] = "user/";
        if (limit) // 如果是root用户则不用初始化
            break;
        else if (!strcmp(us->ID, User_Own))
        {
            strcat(N, us->ID);
            FILE *fp = fopen(N, "r");
            if (!fp) // 如果文件不存在
            {
                printf("\t\t\t\t|Error: E.010...\n");
                printf("\t\t\t\t|");
                system("pause");
                fclose(fp);
            }
            else
            {
                struct user *User = (struct user *)malloc(sizeof(struct user));
                User->head = NULL;
                fscanf(fp, "%s %s %lf %d %lf %s", User->id, User->name, &User->Amount, &User->score, &User->Fine, User->phone);
                User->Fine = 0;
                while (!feof(fp)) // 将用户信息读出来
                {
                    struct vio_infor *h = (struct vio_infor *)malloc(sizeof(struct vio_infor));
                    if (h == NULL)
                    {
                        printf("\t\t\t\t|Error: E.011...\n");
                        system("pause");
                        exit(0);
                    }
                    if (User->head == NULL)
                        User->head = h;
                    else
                    {
                        s->next = h;
                    }
                    h->next = NULL;
                    s = h;
                    fscanf(fp, "%d/%d/%d %d %lf %d %d", &s->year, &s->month, &s->day, &s->fraction, &s->fine, &s->flag, &s->days);
                    if (!s->flag)
                        User->Fine += s->fine;
                }
                struct vio_infor *vi = User->head;
                fclose(fp);
                FILE *fp = fopen(N, "w");
                fprintf(fp, "%s\t%s\t%lf\t%d\t%lf\t%s", User->id, User->name, User->Amount, User->score, User->Fine, User->phone);
                while (vi) // 将更新的用户信息输入进去
                {
                    fprintf(fp, "\n%d/%d/%d\t%d\t%lf\t%d\t%d", vi->year, vi->month, vi->day, vi->fraction, vi->fine, vi->flag, Days(vi));
                    vi = vi->next;
                }
                Free_U(User);
                fclose(fp);
            }
        }
        us = us->next;
    }
    system("cls");
    printf("\t\t\t\t===========================================\n");
    printf("\t\t\t\t|请稍等.");
    // 请稍等。。。代码
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 2; i++)
        {
            putchar(' ');
            putchar('.');
            Sleep(1000);
        }
        printf("\b\b\b\b    \b\b\b\b");
        Sleep(1000);
    }
    for (int i = 0; i < 2; i++)
    {
        putchar(' ');
        putchar('.');
        Sleep(1000);
    }
}
// install函数用来添加用户,
void install_dp()
{
    fflush(stdin);
    system("cls");
    printf("\t\t\t\t===========================================\n");
    printf("\t\t\t\t|                1.新建用户               |\n");
    printf("\t\t\t\t|                2.旧用户添加信息         |\n");
    printf("\t\t\t\t|                3.返回上一级             |\n");
    printf("\t\t\t\t===========================================\n");
    printf("\t\t\t\t|请选择：");
    char n, ch;
    scanf("%c", &n);
    // 直接输入回车
    while (n == '\n')
    {
        printf("\t\t\t\t|");
        scanf("%c", &n);
    }
    //选择
    while (n != '1' && n != '2' && n != '3')
    {
        printf("\t\t\t\t|错误，请重新输入：");
        scanf("%c", &n);
        while (n == '\n')
        {
            printf("\t\t\t\t|");
            scanf("%c", &n);
        }
    }
    // 读取多余的输入
    while (ch = getchar() != '\n')
        ;
    sleep_time();
    //选择
    if (n == '1')
    {
        install();
        install_dp();
    }
    else if (n == '2')
    {
        install_old();
        install_dp();
    }
    else
    {
        home();
    }
}
// 添加user的信息。新建用户。
void install()
{
    fflush(stdin);
    system("cls");
    char a[11] = "";
    char b1[20], b2[20];
    char ch1, ch;
    int i = 0;
    printf("\t\t\t\t===========================================\n");
    printf("\t\t\t\t|请输入用户ID(不超过10个字符):");
    while ((ch = getchar()) == '\n')
        printf("\t\t\t\t|");
    while ((ch) != '\n' && ch != ' ') // 用来输入ID
    {
        // 判断是否输入了非法字符
        if ((ch <= 'z' && ch >= 'a') || (ch >= 'A' && ch <= 'z') || (ch >= '0' && ch <= '9'))
            a[i++] = ch;
        else
        {
            printf("\t\t\t\t|错误：使用了非法字符！\n");
            printf("\t\t\t\t|请重新输入：");
            while ((ch = getchar()) == '\n')
                printf("\t\t\t\t|");
            while ((ch = getchar()) != '\n')
                ;
            i = 0;
            strcat(a, "");
            continue;
        }
        ch = getchar();
    }
    if (Find(a)) // 判断用户是否存在
    {
        printf("\t\t\t\t|错误：用户存在！\n");
        printf("\t\t\t\t|");
        system("pause");
        if (limit)
            install_dp();
        else
            Start();
    }
    else
    {
        i = 0;
        // 判断账号是否符合规则
        while (a[10] != '\0' || a[0] == '\0')
        {
            printf("\t\t\t\t|Error: 用户名不符合要求，请重新输入：");
            while ((ch = getchar()) != '\n')
                a[i++] = ch;
        }
        i = 0;
        printf("\t\t\t\t|请输入密码(6位数)：");
        // 输入密码
        while ((ch1 = getch()) != '\r')
        {
            if (i == 0 && ch1 == 8)
                ;
            else
            {
                if (ch1 == 8)
                {
                    putchar('\b');
                    putchar(' ');
                    putchar('\b');
                    if (i > 0)
                        i--;
                }
                else
                {
                    putchar('*');
                    b1[i++] = ch1;
                }
            }
        };
        putchar('\n');
        i = 0;
        printf("\t\t\t\t|请确认密码：");
        while ((ch1 = getch()) != '\r')
        {
            if (i == 0 && ch1 == 8)
                ;
            else
            {
                if (ch1 == 8)
                {
                    putchar('\b');
                    putchar(' ');
                    putchar('\b');
                    if (i > 0)
                        i--;
                }
                else
                {
                    putchar('*');
                    b2[i++] = ch1;
                }
            }
        }
        putchar('\n');
        if (strlen(b1) != 6) // 输入的密码不合要求
        {
            printf("\t\t\t\t|密码长度不符合要求！\n");
            printf("\t\t\t\t|");
            system("pause");
            install();
        }
        else // 如果输入的密码符合要求。
        {
            if (strcmp(b1, b2)) // 判断密码是否相同
            {
                printf("\t\t\t\t|Error: 两次密码不相同！\n");
                printf("\t\t\t\t|");
                system("pause");
                if (limit)
                    install_dp();
                else
                    Start();
            }
            else // 相同则将用户添加到user_password中
            {
                FILE *fp = fopen("user_password", "a+");
                if (fp == NULL)
                {
                    printf("\t\t\t\t|Error: E.010...\n");
                    printf("\t\t\t\t|");
                    system("pause");
                    fclose(fp);
                    install_dp();
                }
                else
                {
                    fprintf(fp, "\n%s\t%s\t%d", a, b1, 0);
                    printf("\t\t\t\t|用户创建成功！\n");
                    printf("\t\t\t\t|");
                    system("pause");
                    fclose(fp);
                }
            }
            if (limit) // 如果是管理员进行用户注册
            {
                int i = 0;
                system("cls");
                printf("\t\t\t\t===========================================\n");
                printf("\t\t\t\t|请输入该用户信息(包括姓名, 电话):\n");
                printf("\t\t\t\t|");
                struct user *U = (struct user *)malloc(sizeof(struct user));
                // 初始化用户信息
                scanf("%s %s", U->name, U->phone);
                U->Amount = 0;
                while (i <= 10 && U->phone[i] != '\0')
                {
                    if (U->phone[i] > '9' && U->phone[i] < '0')
                    {
                        printf("\t\t\t\t|错误：请重新输入电话：");
                        scanf("%s", U->phone);
                        i = 0;
                    }
                    i++;
                }
                strcpy(U->id, a);
                U->score = SCORE;
                U->Fine = 0;
                char n[30] = "user/";
                strcat(n, U->id);
                U->head = NULL;

                int c;
                printf("\t\t\t\t|请选择要添加的违规信息个数：");
                scanf("%d", &c);
                printf("\t\t\t\t|请输入违规信息(日期(y/m/d)，扣分，罚款，是否交完罚款(0/1)):\n");

                //创建一个链表来储存输入的数据
                struct vio_infor *in = NULL;
                for (int i = 0; i < c; i++)
                {
                    printf("\t\t\t\t|");
                    struct vio_infor *h = (struct vio_infor *)malloc(sizeof(struct vio_infor));
                    if (h == NULL)
                    {
                        printf("\t\t\t\t|Error: E.011...\n");
                        system("pause");
                        install_dp();
                        exit(0);
                    }
                    if (U->head == NULL)
                        U->head = h;
                    else
                        in->next = h;
                    h->next = NULL;
                    in = h;
                    scanf("%d/%d/%d %d %lf %d", &h->year, &h->month, &h->day, &h->fraction, &h->fine, &h->flag);
                    while (1)
                    {
                        fflush(stdin);
                        if (Day_t_or_f(h))
                            break;
                        else
                        {
                            printf("\t\t\t\t|错误：请重新输入日期：\n");
                            printf("\t\t\t\t|");
                            scanf("%d/%d/%d", &h->year, &h->month, &h->day);
                        }
                    }
                    h->days = Days(h);
                    if (U->score <= 0)
                    {
                        printf("\t\t\t\t|错误：违规超过分数限制！");
                        getchar();
                        install_dp();
                        exit(0);
                    }
                    else
                        U->score += h->fraction;
                }
                struct vio_infor *h = U->head;
                FILE *f = fopen(n, "w");
                // 将数据输入到文件
                fprintf(f, "%s\t%s\t%lf\t%d\t%lf\t%s", U->id, U->name, U->Amount, U->score, U->Fine, U->phone);
                while (h != NULL)
                {
                    fprintf(f, "\n%d/%d/%d\t%d\t%lf\t%d\t%d", h->year, h->month, h->day, h->fraction, h->fine, h->flag, h->days);
                    h = h->next;
                }
                printf("\t\t\t\t|Success: S.001...\n");
                printf("\t\t\t\t|");
                system("pause");
                Free_U(U);
                fclose(f);
            }
            else // 如果是普通用户注册
            {
                int i = 0;
                system("cls");
                printf("\t\t\t\t===========================================\n");
                printf("\t\t\t\t|请输入用户信息(姓名, 电话):\n");
                printf("\t\t\t\t|");
                struct user *U = (struct user *)malloc(sizeof(struct user));
                scanf("%s %s", U->name, U->phone);
                while (i <= 10 && U->phone[i] != '\0')
                {
                    if (U->phone[i] > '9' && U->phone[i] < '0')
                    {
                        printf("\t\t\t\t|错误：请重新输入电话：");
                        scanf("%s", U->phone);
                        i = 0;
                    }
                    i++;
                }
                strcpy(U->id, a);
                U->score = SCORE;
                U->Fine = 0;
                U->Amount = 0;
                char n[30] = "user/";
                strcat(n, U->id);
                FILE *f = fopen(n, "w");
                U->head = NULL;
                fprintf(f, "%s\t%s\t%lf\t%d\t%lf\t%s", U->id, U->name, U->Amount, U->score, U->Fine, U->phone);
                fclose(f);
                printf("\t\t\t\t|成功！\n");
                printf("\t\t\t\t|");
                system("pause");
            }
        }
    }
}
// 添加现有用户
void install_old()
{
    fflush(stdin);
    int i = 0;
    int fl = 0;
    system("cls");
    printf("\t\t\t\t===========================================\n");
    lnit_display();
    printf("\t\t\t\t|请输入用户id：");
    char n[20] = "user/";
    char N[20] = "", ch;
    // 直接输入回车
    while ((ch = getchar()) == '\n')
        printf("\t\t\t\t|");
    //读取输入
    while ((ch) != '\n' && ch != ' ')
    {
        if ((ch <= 'z' && ch >= 'a') || (ch >= 'A' && ch <= 'z') || (ch >= '0' && ch <= '9'))
            N[i++] = ch;
        else
        {
            printf("\t\t\t\t|错误：使用了非法字符！");
            printf("\t\t\t\t|请重新输入：");
            while ((ch = getchar()) == '\n')
                printf("\t\t\t\t|");
            while ((ch = getchar()) != '\n')
                ;
            i = 0;
            strcat(N, "");
            continue;
        }
        ch = getchar();
    }
    strcat(n, N);
    // 读写模式打开文件
    FILE *f = fopen(n, "r");
    if (f == NULL)
    {
        printf("\t\t\t\t|Error: E.010...\n");
        printf("\t\t\t\t|");
        system("pause");
    }
    else
    {
        printf("\t\t\t\t|请输入需要添加的信息个数：");
        int a;
        scanf("%d", &a);
        fflush(stdin);
        sleep_time();
        // 判断要添加的信息数
        if (a <= 0)
        {
            printf("\t\t\t\t|无法添加！");
        }
        else // 添加信息
        {
            struct user *vi = (struct user *)malloc(sizeof(struct user));
            fscanf(f, "%s %s %lf %d %lf %s", vi->id, vi->name, &vi->Amount, &vi->score, &vi->Fine, vi->phone);
            list_us(f, vi);
            struct vio_infor *h = vi->head;
            if (h == NULL)
                ;
            else
            {
                while (h->next != NULL)
                {
                    h = h->next;
                }
            }
            fclose(f);
            system("cls");
            if (f == NULL)
            {
                printf("\t\t\t\t|Error: E.010...\n");
                printf("\t\t\t\t|");
                system("pause");
                exit(1);
            }
            else
            {
                struct vio_infor *in = NULL;
                printf("\t\t\t\t===========================================\n");
                printf("\t\t\t\t|请输入要添加的信息\n\t\t\t\t|(日期(y/m/d)，扣分(负数)，罚款，是否交完罚款(0/1)):\n");
                for (int i = 0; i < a; i++)
                {
                    fflush(stdin);
                    struct vio_infor *p = (struct vio_infor *)malloc(sizeof(struct vio_infor));
                    if (vi->head == NULL)
                        vi->head = p;
                    else if (h != NULL)
                        if (h->next == NULL)
                            h->next = p;
                        else
                            in->next = p;
                    else
                        in->next = p;
                    p->next = NULL;
                    in = p;
                    printf("\t\t\t\t|");
                    scanf("%d/%d/%d %d %lf %d", &p->year, &p->month, &p->day, &p->fraction, &p->fine, &p->flag);
                    while (1)
                    {
                        if (Day_t_or_f(p))
                            break;
                        else
                        {
                            fflush(stdin);
                            printf("\t\t\t\t|日期错误，请重新输入日期：\n");
                            printf("\t\t\t\t|");
                            scanf("%d/%d/%d", &p->year, &p->month, &p->day);
                        }
                    }
                    while (p->fraction > 0)
                    {
                        printf("\t\t\t\t|分数错误：请重新输入:");
                        scanf("%d", &p->fraction);
                    }
                    if (vi->score <= 0)
                    {
                        Delete(vi);
                    }
                    else
                        vi->score += p->fraction;
                }
                FILE *f = fopen(n, "w");
                fprintf(f, "%s\t%s\t%lf\t%d\t%lf\t%s", vi->id, vi->name, vi->Amount, vi->score, vi->Fine, vi->phone);
                h = vi->head;
                while (h != NULL)
                {
                    fprintf(f, "\n%d/%d/%d %d %lf %d %d", h->year, h->month, h->day, h->fraction, h->fine, h->flag, Days(h));
                    h = h->next;
                }
                printf("\t\t\t\t|Success: S.001...\n");
                fclose(f);
            }
            Free_U(vi);
        }
        printf("\t\t\t\t|");
        system("pause");
    }
}
// 当用户分数为0时无法添加违规记录
void Delete(struct user *us)
{
    double m = 0.0;
    system("cls");
    printf("\t\t\t\t===========================================\n");
    printf("\t\t\t\t|错误，添加过后用户分数已经为0              |\n");
    struct vio_infor *vi;
    vi = us->head;
    // 计算总共需要的缴费
    while (vi)
    {
        if (vi->flag == 0)
        {
            m += vi->fine;
        }
        vi = vi->next;
    }
    printf("\t\t\t\t|需要缴纳的罚款总数为：%lf ", m);
    us->Fine = m;
}
// 查找用户
bool Find(char Id[])
{
    struct user_passwd *p = list();
    while (p != NULL)
    {
        if (!strcmp(p->ID, Id))
            return true;
        p = p->next;
    }
    return false;
}