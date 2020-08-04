#include "user.h"
bool limit = false;

int main(void)
{

    Start();
    system("cls");
    printf("\t\t\t\t|系统已退出！\n");
    printf("\t\t\t\t|");
    system("pause");
    return 0;
}
//欢迎界面
void welcome()
{
    fflush(stdin);
    struct user_passwd *hd = NULL;
    hd = list();
    char user[20] = "";
    char password[20];
    char ch;
    int i = 0;
    system("cls");
    printf("\t\t\t\t===========================================\n");
    printf("\t\t\t\t|               欢迎使用本系统         \n");
    printf("\t\t\t\t|请输入用户名(id)：");
    while ((ch = getchar()) == '\n')
        printf("\t\t\t\t|");
    while (ch != '\n' && ch != ' ')
    {
        user[i++] = ch;
        ch = getchar();
    }
    i = 0;
    strcpy(User_Own, user);
    printf("\t\t\t\t|请输入密码(6位数)：");
    // 输入密码
    while ((ch = getch()) != '\r')
    {
        if (i == 0 && ch == 8)
            ;
        else
        {
            if (ch == 8)
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
                password[i++] = ch;
            }
        }
    }
    putchar('\n');
    sleep_time();
    // 判断密码格式是否正确
    if (strlen(password) != 6)
    {
        printf("\t\t\t\t|密码错误！\n");
        printf("\t\t\t\t|");
        system("pause");
        welcome();
    }
    else
    {
        struct user_passwd *a = hd;
        // while循环判断用户是否存在，且是否是管理员
        while (a != NULL)
        {
            if (strcmp(a->ID, user))
            {
                a = a->next;
            }
            else
            {
                // 用户是管理员，则将全局变量改为true，否则为false
                if (!strcmp(a->passwd, password))
                {
                    if (a->Authority == true)
                        limit = true;
                    lnit();
                    home();
                }
                else
                {
                    printf("\t\t\t\t|Error: E.012...\n");
                    printf("\t\t\t\t|");
                    system("pause");
                    welcome();
                }
                break;
            }
        }
        if (a == NULL)
        {
            Free_WD(hd);
            printf("\t\t\t\t|Error: E.013...\n");
            printf("\t\t\t\t|");
            system("pause");
            welcome();
        }
    }
}
// list函数将创建一个链表，用来储存用户名和密码
struct user_passwd *list()
{
    FILE *fi;
    fi = fopen("user_password", "r");
    // 文件不存在，则报错。
    if (fi == NULL)
    {
        printf("\t\t\t\t|Error: E.010...\n");
        printf("\t\t\t\t|");
        system("pause");
        exit(0);
    }
    struct user_passwd *z = NULL;
    struct user_passwd *s;
    struct user_passwd *hd = NULL;
    // do-while循环创建一个链表
    do
    {
        s = (struct user_passwd *)malloc(sizeof(struct user_passwd));
        if (s == NULL)
        {
            printf("\t\t\t\t|Error: E.011...\n");
            printf("\t\t\t\t|");
            system("pause");
            exit(1);
        }
        if (hd == NULL)
            hd = s;
        else
            z->next = s;
        s->next = NULL;
        z = s;
        fscanf(fi, "%s %s %d\n", s->ID, s->passwd, &s->Authority);
    } while (!feof(fi));
    fclose(fi);
    return hd;
}
// 登录界面
void Start()
{
    fflush(stdin);
    system("cls");
    printf("\t\t\t\t===========================================\n");
    printf("\t\t\t\t|                 1.登录                  |\n");
    printf("\t\t\t\t|                 2.注册                  |\n");
    printf("\t\t\t\t|                 3.帮助                  |\n");
    printf("\t\t\t\t|                 0.退出                  |\n");
    printf("\t\t\t\t===========================================\n");
    printf("\t\t\t\t|请输入:");
    char ch = 0, n;
    while ((ch = getchar()) == '\n')
    {
        printf("\t\t\t\t|");
    }
    while (n = getchar() != '\n')
        ;
    while (ch != '1' && ch != '2' && ch != '0' && ch != '3')
    {
        printf("\t\t\t\t|错误，请重新输入：");
        while ((ch = getchar()) == '\n')
        {
            printf("\t\t\t\t|");
        }
        while (n = getchar() != '\n')
            ;
    }
    sleep_time();
    switch (ch)
    {
    case '1':
        welcome();
        break;
    case '2':
        install();
        Start();
        break;
    case '0':
        break;
    case '3':
        Help();
        Start();
        break;
    }
}