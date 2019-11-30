
#include <iostream>
#include <ctime>
#include <array>
using namespace std;

array<int, 13> mon_days = {-1,31,28,31,30,31,30,31,31,30,31,30,31};

struct Date {
    int year, mon, day;
};

bool isleap(int);
bool isOK(int);
int cal_days(const Date &,const Date &);
void print(const Date &,const Date &, int &);

int main()
{
    Date btm, ntm;
    time_t now = time(0);
    tm *ltm = localtime(&now);

    // 开始的日期,年，月，日
    btm.year = 2018, btm.mon = 10, btm.day = 16;
    // 现在的日期
    ntm.year = 1900 + ltm->tm_year;
    ntm.mon = 1 + ltm->tm_mon;
    ntm.day = ltm->tm_mday;

    int ans = cal_days(btm, ntm);
    print(btm, ntm, ans);
    return 0;
}
// 计算天数的逻辑，先计算完整的年,完整的月
int cal_days(const Date & btm,const Date & ntm)
{
    int ans = 0;
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

    return ans;
}

bool isleap(int n)
{
    if (n%400==0 || (n%4==0&&n%100))
        return true;
    return false;
}

void print(const Date & btm,const Date & ntm, int & ans)
{
    cout << "begin time: " << btm.year << "." << btm.mon << "." << btm.day << endl;
    cout << "now time: " << ntm.year << "." << ntm.mon << "." << ntm.day << endl;
    cout << "how many days: " << ans << endl;
}
