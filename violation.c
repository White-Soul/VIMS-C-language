#include "user.h"
//打印用户信息。
void Inquire()
{
    fflush(stdin);
    int i = 0;
    system("cls");
    printf("\t\t\t\t===========================================\n");
    lnit_display();
    printf("\t\t\t\t|q.退出！\n");
    printf("\t\t\t\t|请输入需要查询的用户id：");
    char N[20] = "", ch;
    char n[20] = "user/";
    while ((ch = getchar()) == '\n')
        printf("\t\t\t\t|");
    while (ch != '\n' && ch != ' ')
    {
        N[i++] = ch;
        ch = getchar();
    }
    if (N[0] == 'q')
    {
        sleep_time();
        home();
    }
    else
    {
        sleep_time();
        strcat(n, N);
        FILE *fp = fopen(n, "r");
        if (fp == NULL)
        {
            printf("\t\t\t\t|Error: E.013...\n");
            printf("\t\t\t\t|");
            system("pause");
            Inquire();
        }
        else
        {
            display(fp);
            fclose(fp);
            home();
        }
    }
}
//显示违规信息
void display(FILE *fp)
{
    struct user US;
    system("cls");
    fscanf(fp, "%s %s %lf %d %lf %s", US.id, US.name, &US.Amount, &US.score, &US.Fine, US.phone);
    printf("\t\t\t\t|\t\t%s\t%s\t分数：%d\n", US.name, US.id, US.score);
    printf("\t\t\t\t|\t电话：%s\n", US.phone);
    printf("\t\t\t\t|   日期\t扣分数 罚款 是否缴费 违规天数\n");
    printf("\t\t\t\t|___________________________________________\n");
    list_us(fp, &US);
    struct vio_infor *z = US.head;
    while (z)
    {
        z->days = Days(z);
        printf("\t\t\t\t|%d/%.2d/%.2d|\t%d\t%.1lf\t%d\t%d\n", z->year, z->month, z->day, z->fraction, z->fine, z->flag, z->days);
        z = z->next;
    }
    Free_V(US.head);
    printf("\t\t\t\t|");
    system("pause");
    sleep_time();
}
//显示所有用户
void lnit_display()
{
    struct user_passwd *W;
    W = list();
    W = W->next;
    while (W != NULL)
    {
        printf("\t\t\t\t|%s \n", W->ID);
        W = W->next;
    }
}
// 从文件中读取用户。
void list_us(FILE *fp, struct user *us)
{
    us->head = NULL;
    while (!feof(fp))
    {
        struct vio_infor *s, *z;
        z = (struct vio_infor *)malloc(sizeof(struct vio_infor));
        if (z == NULL)
        {
            printf("\t\t\t\t|Error: E.011...\n");
            printf("\t\t\t\t|");
            system("pause");
            home();
        }
        else
        {
            if (us->head == NULL)
                us->head = z;
            else
                s->next = z;
            z->next = NULL;
            s = z;
            fscanf(fp, "%d/%d/%d %d %lf %d %d", &z->year, &z->month, &z->day, &z->fraction, &z->fine, &z->flag, &z->days);
        }
    }
}
