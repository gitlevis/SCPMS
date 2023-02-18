#include <iostream>
using namespace std;
#include <vector>
#include <deque>
#include <algorithm>
#include <random>
#include <chrono>
#include <fstream>

class Player
{
    friend void getScore(vector<Player> &v);
    friend class MyCmp;

public:
    Player() {} // 结构体resize，必须有空构造函数
    Player(int id, float score)
    {
        this->m_Id = id;
        this->m_Score = score;
    }
    static void printPlayer(const Player &p)
    {
        cout << "ID: " << p.m_Id << "\tScore: " << p.m_Score << endl;
    }

public:
    int m_Id;
    float m_Score;
};

class MyCmp
{
public:
    bool operator()(const Player &p1, const Player &p2)
    {
        return p1.m_Score > p2.m_Score;
    }
};

void getScore(vector<Player> &v)
{
    for (vector<Player>::iterator iit = v.begin(); iit != v.end(); iit++)
    {
        deque<int> d;
        for (int i = 0; i < 10; i++)
        {
            int score = rand() % 41 + 60;
            d.push_back(score);
        }
        sort(d.begin(), d.end());
        d.pop_back();
        d.pop_front();
        int sum = 0;
        for (deque<int>::iterator it = d.begin(); it != d.end(); it++)
        {
            sum += *it;
        }
        float aveScore = (float)sum / d.size();
        iit->m_Score = aveScore;
    }
}

void getPlayer(vector<Player> &v)
{
    for (int i = 10001; i <= 10012; i++)
    {
        Player p(i, 0);
        v.push_back(p);
    }
}

void test01()
{
    srand((unsigned int)time(NULL));
    vector<Player> v;
    getPlayer(v);

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(v.begin(), v.end(), default_random_engine(seed));
    // for_each(v.begin(), v.end(), Player::printPlayer);

    // 分组： 一组
    vector<Player> group01;
    group01.resize(v.size() / 2); // 结构体resize，必须有空构造函数
    copy(v.begin(), v.begin() + v.size() / 2, group01.begin());
    // for_each(group01.begin(), group01.end(), Player::printPlayer);
    // cout << endl;

    //分组： 二组
    vector<Player> group02;
    group02.resize(v.size() / 2);
    copy(v.begin() + v.size() / 2, v.end(), group02.begin());
    // for_each(group02.begin(), group02.end(), Player::printPlayer);

    cout << "第一轮成绩: " << endl;
    cout << "第一组: " << endl;
    getScore(group01);
    for_each(group01.begin(), group01.end(), Player::printPlayer);
    cout << endl;
    cin.get();

    cout << "第二组：" << endl;
    getScore(group02);
    for_each(group02.begin(), group02.end(), Player::printPlayer);
    cout << endl;
    cin.get();

    // 两组成绩分别排序
    sort(group01.begin(), group01.end(), MyCmp());
    cout<<"第一组排序："<<endl;
    for_each(group01.begin(), group01.end(), Player::printPlayer);
    cout << endl;
    cin.get();

    sort(group02.begin(), group02.end(), MyCmp());
    cout<<"第二组排序："<<endl;
    for_each(group02.begin(), group02.end(), Player::printPlayer);
    cout << endl;
    cin.get();

    // 两组前三合并到三组
    vector<Player> groupFinal;
    groupFinal.resize(group01.size() / 2 + group02.size() / 2);
    copy(group01.begin(), group01.end() + group01.size() / 2, groupFinal.begin());
    copy(group02.begin(), group02.end() + group02.size() / 2, groupFinal.begin() + groupFinal.size() / 2);
    cout << "第三组: " << endl;
    for_each(groupFinal.begin(), groupFinal.end(), Player::printPlayer);
    cout << endl;

    getScore(groupFinal);
    cout << "第三组第二轮成绩: " << endl;
    for_each(groupFinal.begin(), groupFinal.end(), Player::printPlayer);
    cin.get();

    // 第三组排序
    sort(groupFinal.begin(), groupFinal.end(), MyCmp());
    cout << "第三组排序: " << endl;
    for_each(groupFinal.begin(), groupFinal.end(), Player::printPlayer);
    cin.get();

    // 成绩文件存储
    ofstream ofs;
    ofs.open("speechContest.txt", ios::app);
    ofs<<"一轮比赛: "<<endl;
    for(vector<Player>::iterator it=groupFinal.begin(); it!=groupFinal.begin()+groupFinal.size()/2; it++)
    {
        ofs<<(*it).m_Id<<"\t"<<(*it).m_Score<<endl;
    }
    ofs<<endl;
    ofs.close();
    cout<<"前三名成绩已保存。"<<endl;
}

int main()
{
    test01();
    return 0;
}