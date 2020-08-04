#ifndef USER
#define USER
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#define SCORE 25
char User_Own[20];
struct user
{
    int score;
    char phone[12];
    char name[20];
    double Amount; // 余额
    char id[11];
    double Fine; //应交多少
    struct vio_infor *head;
};
struct vio_infor
{
    struct data //日期
    {
        int year;
        int month;
        int day;
    };
    int days;
    bool flag;    //是否缴费
    int fraction; //扣分
    double fine;  //罚款
    struct vio_infor *next;
};
struct user_passwd
{
    char ID[11];
    char passwd[7];
    bool Authority;
    struct user_passwd *next;
};
#define TIME 22
void install();               //插入信息，
void lnit();                  //初始化系统并且分配空间。
void Inquire();               //查询用户违规信息查询界面
void Delete(struct user *us); //当对象的积分为0时，将会删除对象
void Time_limit();            //未在规定的时间之内进行缴费，将会额外扣分
void display_Am();            //显示当前余额。并且打印违规信息
void Payment();               //缴费操作.
void Help();                  //帮助
void home();                  //主界面
void Pay_face();              //缴费界面;
void welcome();               //欢迎界面，输入用户。
int Days(struct vio_infor *); // 计算日期。
void display(FILE *);         //显示违规信息
void install_old();           //给老用户添加信息
void Free_U(struct user *);   //释放内存
void Free_V(struct vio_infor *);
void Free_WD(struct user_passwd *);
struct user_passwd *list();              //创建链表
void install_dp();                       //添加用户界面
void sleep_time();                       // 加载进度条
void list_us(FILE *fp, struct user *us); //创建user链表
void lnit_display();                     //显示用户信息
void Start();                            // 开始界面
bool Find(char[]);                       // 查找用户
void Top_up();                           // 充值
bool Day_t_or_f(struct vio_infor *);
#endif