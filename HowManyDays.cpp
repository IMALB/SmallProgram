
#include <iostream>
#include <ctime>
#include <array>
using namespace std;

array<int, 13> mon_days = {-1,31,28,31,30,31,30,31,31,30,31,30,31};

struct Date 
{
    int year, mon, day;
};

bool isleap(int);
bool isOK(int);
bool isLegal(const Date &,const Date &);
int cal_days(const Date &,const Date &);
void print(const Date &,const Date &, int &);
void getBeginTime(Date &); 
void getNowTime(Date &, tm *);

int main()
{
    Date btm, ntm;
    time_t now = time(0);
    tm *ltm = localtime(&now);

    getBeginTime(btm);
    getNowTime(ntm, ltm);

    int ans = cal_days(btm, ntm);
    print(btm, ntm, ans);
    return 0;
}
// 获取开始的时间
void getBeginTime(Date & btm)
{
    btm.year = 2019, btm.mon = 10, btm.day = 16;
}
// 获取结束的时间
void getNowTime(Date & ntm, tm *ltm)
{
    ntm.year = 1900 + ltm->tm_year;
    ntm.mon = 1 + ltm->tm_mon;
    ntm.day = ltm->tm_mday;
}
// 计算天数的逻辑，先计算完整的年,完整的月
int cal_days(const Date & btm,const Date & ntm)
{
    int ans = 0;
    if(btm.year == ntm.year && btm.mon == ntm.mon) {
        ans = ntm.day - btm.day;
    }
    else {
        for (int i = btm.year+1; i < ntm.year; i++) {
            if (isleap(i)) ans += 366;
            else           ans += 365;
        }
        if (isleap(btm.year))  mon_days[2] = 29;
        else                   mon_days[2] = 28;
        if (btm.year != ntm.year) 
            for (int i = btm.mon+1; i <= 12; i++)
                ans += mon_days[i];
        else for (int i = btm.mon+1; i < ntm.mon; i++)
                    ans += mon_days[i];
        ans += mon_days[btm.mon] - btm.day + 1;
        
        if (isleap(ntm.year)) mon_days[2] = 29;
        else                  mon_days[2] = 28;
        if (btm.year != ntm.year) 
            for (int i = 1; i < ntm.mon; i++)
                ans += mon_days[i];
        ans += ntm.day;
    }
    return ans;
}
// 判断是否是闰年
bool isleap(int n)
{
    if (n%400==0 || (n%4==0&&n%100))
        return true;
    return false;
}
// 打印结果
void print(const Date & btm,const Date & ntm, int & ans)
{
    if (isLegal(btm, ntm)) {
        cout << "begin time: " << btm.year << "." << btm.mon << "." << btm.day << endl;
        cout << "now time: " << ntm.year << "." << ntm.mon << "." << ntm.day << endl;
        cout << "how many days: " << ans << endl;   
    }
    else
        cout << "the date is error!" << endl;
}
// 判断两个日期是否合法
bool isLegal(const Date & btm,  const Date & ntm)
{
    if (btm.mon<1 || btm.mon>12 || ntm.mon<1 || ntm.mon>12)
        return false;
    else {
        if (btm.mon == 2)
            mon_days[2] = isleap(btm.year) ? 29 : 28;
        if (btm.day<1 || btm.day>mon_days[btm.mon] )
            return false;

        if (ntm.mon == 2)
            mon_days[2] = isleap(ntm.year) ? 29 : 28;    
        if (ntm.day<1 || ntm.day>mon_days[ntm.mon])
            return false;
    }

    if (btm.year < ntm.year)
        return true;
    else if(btm.year == ntm.year && btm.mon < ntm.mon)
        return true;
    else if(btm.year == ntm.year && btm.mon == ntm.mon && btm.day <= ntm.day)
        return true;
    return false;
}
