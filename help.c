#include "user.h"

void Help()
{
    system("cls");
    printf("\t\t\t\t===========================================\n");
    printf("\t\t\t\t|           违规信息管理系统帮助          |\n");
    printf("\t\t\t\t|成功提示：                               |\n");
    printf("\t\t\t\t|S.001: 插入信息成功！                    |\n");
    printf("\t\t\t\t|S.002: 查询成功！                        |\n");
    printf("\t\t\t\t|S.003: 缴费成功！                        |\n");
    printf("\t\t\t\t|                                         |\n");
    printf("\t\t\t\t|错误提示：                               |\n");
    printf("\t\t\t\t|E.004: 插入信息失败！                    |\n");
    printf("\t\t\t\t|E.005: 用户不存在！                      |\n");
    printf("\t\t\t\t|E.006: 余额不足！                        |\n");
    printf("\t\t\t\t|E.007: 进行了不必要的操作！              |\n");
    printf("\t\t\t\t|E.008: 违规信息未按时间顺序插入！        |\n");
    printf("\t\t\t\t|E.009: 请重新选择！                      |\n");
    printf("\t\t\t\t|E.010: 无法打开文件！                    |\n");
    printf("\t\t\t\t|E.011: 无法分配空间！                    |\n");
    printf("\t\t\t\t|E.012: 密码错误！                        |\n");
    printf("\t\t\t\t|E.013: 用户不存在,或用户没有违规信息!    |\n");
    printf("\t\t\t\t|E.014: 用户权限不足！                    |\n");
    printf("\t\t\t\t===========================================\n");
    printf("\t\t\t\t|");
    system("pause");
    sleep_time();
    home();
}
// 释放分配的user内存。
void Free_U(struct user *u)
{
    struct vio_infor *vio;
    vio = u->head;
    free(u);
    Free_V(vio);
}
// 释放分配的vio_infor内存。
void Free_V(struct vio_infor *vio)
{
    struct vio_infor *n;
    n = vio;
    while (vio != NULL)
    {
        vio = vio->next;
        free(n);
        n = vio;
    }
}
// 释放分配的user_passwd内存。
void Free_WD(struct user_passwd *wd)
{
    struct user_passwd *n;
    n = wd;
    while (wd != NULL)
    {
        wd = wd->next;
        free(n);
        n = wd;
    }
}
// 加载画面。
void sleep_time()
{
    for (int i = 0; i < 4; i++)
        putchar('\t');
    int ti = 0;
    for (; ti < TIME; ti++)
    {
        putchar('*');
        putchar(' ');
        Sleep(20);
    }
    putchar('\n');
}
// 计算日期
int Days(struct vio_infor *D)
{
    int Days = 0;
    time_t timep;
    struct tm *t;
    time(&timep);
    t = gmtime(&timep);
    int year = D->year;
    // 计算D的年份到今天的天数。
    while (year != (t->tm_year + 1900))
    {
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
            Days += 366;
        else
            Days += 365;
    }
    Days += t->tm_yday;
    int days_d = 0;
    int n = 1;
    // 计算D本年违规日期的天数
    while (n < D->month)
    {
        switch (n++)
        {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            days_d += 31;
            break;
        case 2:
            if ((D->year % 4 == 0 && D->year % 100 != 0) || D->year % 400 == 0)
                days_d += 29;
            else
                days_d += 28;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            days_d += 30;
            break;
        }
    }
    days_d += D->day;
    return Days - days_d + 1;
}
// 判断日期
bool Day_t_or_f(struct vio_infor *vio)
{
    time_t timep;
    struct tm *t;
    time(&timep);
    t = gmtime(&timep);
    if (vio->year < 1900 || vio->year > (t->tm_year + 1900))
        return false;
    else if (vio->year == (t->tm_year + 1900))
    {
        if (vio->month < 1 || vio->month > t->tm_mon + 1)
            return false;
        else if (vio->month == t->tm_mon + 1)
        {
            if (vio->day < 1 || vio->day > t->tm_mday)
                return false;
            else
                return true;
        }
        else
        {
            switch (vio->month + 1)
            {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                if (vio->day > 31 || vio->day < 1)
                    return false;
                else
                    return true;
                break;
            case 2:
                if ((vio->year % 4 == 0 && vio->year % 100 != 0) || vio->year % 400 == 0)
                    if (vio->day > 29 || vio->day < 1)
                        return false;
                    else
                        return true;
                else
                {
                    if (vio->day > 28 || vio->day < 1)
                        return false;
                    else
                        return true;
                }
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                if (vio->day > 30 || vio->day < 1)
                    return false;
                else
                    return true;
                break;
            }
        }
    }
    else
    {
        if (vio->month < 1 || vio->month > 12)
            return false;
        else
        {
            switch (vio->month)
            {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                if (vio->day > 31 || vio->day < 1)
                    return false;
                else
                    return true;
                break;
            case 2:
                if ((vio->year % 4 == 0 && vio->year % 100 != 0) || vio->year % 400 == 0)
                    if (vio->day > 29 || vio->day < 1)
                        return false;
                    else
                        return true;
                else
                {
                    if (vio->day > 28 || vio->day < 1)
                        return false;
                    else
                        return true;
                }
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                if (vio->day > 30 || vio->day < 1)
                    return false;
                else
                    return true;
                break;
            }
        }
    }
}