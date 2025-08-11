#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "class/user.h"
#include "class/good.h"
#include <ctime>

std::string getTime()
{
    time_t now = time(nullptr);
    tm *localTime = localtime(&now);

    char buffer[11]; // yyyy-mm-dd + null terminator
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", localTime);

    return std::string(buffer);
}

void load(std::vector<User> &users)
{
    std::ifstream file("user.csv");
    if (!file.is_open())
    {
        std::cout << "文件打开失败" << std::endl;
        return;
    }
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string s;
        std::vector<std::string> v;
        while (std::getline(ss, s, ','))
        {
            v.push_back(s);
        }
        users.push_back(User(v[0], v[1], v[2], v[3], v[4], std::stod(v[5])));
    }
    file.close();
}

void save(std::vector<User> &users)
{
    std::ofstream file("user.csv");
    file << "用户ID,用户名,密码,联系方式,地址,钱包余额" << std::endl;
    for (auto &user : users)
    {
        file << user.id << "," << user.name << "," << user.password << "," << user.phone << "," << user.address << "," << user.balance << std::endl;
    }
    file.close();
}

void registerUser()
{
    std::vector<User> users;
    load(users);
    std::string name;
    while (true)
    {
        bool flag = true;
        std::cout << "请输入用户名:";
        std::cin >> name;
        for (auto user : users)
        {
            if (user.name == name)
            {
                std::cout << "用户名已存在" << std::endl;
                flag = false;
                break;
            }
        }
        if (flag)
        {
            break;
        }
    }
    std::cout << "请输入密码:";
    std::string password;
    std::cin >> password;
    std::cout << "请输入联系方式:";
    std::string phone;
    std::cin >> phone;
    std::cout << "请输入地址:";
    std::string address;
    std::cin >> address;
    char id[5] = {(users.end() - 1)->id[1], (users.end() - 1)->id[2], (users.end() - 1)->id[3], (users.end() - 1)->id[4], (users.end() - 1)->id[5]};
    int id2 = std::stoi(id) + 1;
    char id3[7];
    sprintf(id3, "U%05d", id2);
    users.push_back(User(id3, name, password, phone, address, 0));
    std::cout << "*****************  注册成功  ********************" << std::endl;
    save(users);
}

bool loginUser(User *&user_i, std::vector<User> &users)
{
    std::cout << "请输入用户名:";
    std::string name;
    std::cin >> name;
    std::cout << "请输入密码:";
    std::string password;
    std::cin >> password;
    for (auto &user : users)
    {
        if (user.name == name && user.password == password)
        {
            std::cout << "***************  登录成功  ********************" << std::endl;
            user_i = &user;
            return true;
        }
    }
    std::cout << "*****************   登录失败!即将返回主菜单...  **********************" << std::endl;
    return false;
}

void User::charge()
{
    double money;
    std::cout << "请输入充值金额:";
    std::cin >> money;
    balance += money;
    std::cout << "充值成功!" << std::endl;
    std::cout << "当前余额为:" << balance << std::endl;
}

void User::view()
{
    std::cout << "****************************************" << std::endl;
    std::cout << "用户名:" << name << std::endl;
    std::cout << "联系方式:" << phone << std::endl;
    std::cout << "地址:" << address << std::endl;
    std::cout << "钱包余额:" << balance << std::endl;
    std::cout << "****************************************" << std::endl;
}

void User::modify()
{
    std::cout << "请选择修改的属性(1.用户名 2.联系方式 3.地址):";
    int choice;
    std::cin >> choice;
    switch (choice)
    {
    case 1:
        std::cout << "请输入新的用户名:";
        std::cin >> name;
        break;
    case 2:
        std::cout << "请输入新的联系方式:";
        std::cin >> phone;
        break;
    case 3:
        std::cout << "请输入新的地址:";
        std::cin >> address;
        break;
    default:
        std::cout << "输入错误" << std::endl;
        break;
    }
}

void User::uploadGood(std::vector<Good> &goods)
{
    std::cout << "请输入商品名称:";
    std::string name;
    std::cin >> name;
    std::cout << "请输入商品价格:";
    double price;
    std::cin >> price;
    std::cout << "请输入商品描述:";
    std::string description;
    std::cin >> description;
    std::cout << std::endl
              << "请确定发布商品的信息无误！" << std::endl;
    std::cout << "商品名称:" << name << std::endl;
    std::cout << "商品价格:" << price << std::endl;
    std::cout << "商品描述:" << description << std::endl
              << std::endl;
    std::cout << "您确认要发布该商品吗(y/n)" << std::endl;
    char choice;
    std::cin >> choice;
    if (choice != 'y')
    {
        std::cout << "取消发布！" << std::endl;
        return;
    }
    char id1[5] = {(goods.end() - 1)->id[1], (goods.end() - 1)->id[2], (goods.end() - 1)->id[3], (goods.end() - 1)->id[4], (goods.end() - 1)->id[5]};
    int id2 = std::stoi(id1) + 1;
    char id3[7];
    sprintf(id3, "M%05d", id2);
    goods.push_back(Good(id3, name, price, description, id, getTime(), 3));
    std::cout << "发布成功！" << std::endl;
}

void User::viewGood(std::vector<Good> &goods)
{
    std::cout << "您发布的商品清单如下：" << std::endl;
    std::cout << "****************************************" << std::endl;
    std::cout << "ID\t名称\t价格\t上架时间\t商品状态" << std::endl;
    for (const auto &good : goods)
    {
        if (good.user_id == id)
        {
            std::cout << good.id << "\t" << good.name << "\t" << good.price << "\t" << good.time << "\t" << transState(good) << std::endl;
            std::cout << "****************************************" << std::endl;
        }
    }
}

void User::modifyGood(std::vector<Good> &goods)
{
    viewGood(goods);
    std::cout << "请输入要修改的商品ID:";
    std::string good_id;
    std::cin >> good_id;
    int choice;
    while (choice < 1 || choice > 3)
    {
        std::cout << "请输入要修改的商品属性(1.名称 2.价格 3.描述):";
        std::cin >> choice;
        if (choice < 1 || choice > 3)
        {
            std::cout << "输入错误" << std::endl;
        }
    }
    for (auto &good : goods)
    {
        if (good.id == good_id && good.user_id == id)
        {
            switch (choice)
            {
            case 1:
                std::cout << "请输入新的商品名称:";
                std::cin >> good.name;
                break;
            case 2:
                std::cout << "请输入新的商品价格:";
                std::cin >> good.price;
                break;
            case 3:
                std::cout << "请输入新的商品描述:";
                std::cin >> good.description;
                break;
            default:
                break;
            }
        }
    }
    std::cout << "未找到该商品!" << std::endl;
}

void User::deleteGood(std::vector<Good> &goods)
{
    if (goods.empty())
    {
        std::cout << "没有商品" << std::endl;
        return;
    }
    viewGood(goods);
    std::cout << "请输入下架商品ID:";
    std::string good_id;
    std::cin >> good_id;
    for (auto &good : goods)
    {
        if (good.id == good_id && good.user_id == id)
        {
            std::cout << "您确定要下架该商品吗！" << std::endl;
            std::cout << "***********************************************************" << std::endl;
            std::cout << "商品ID:" << good.id << std::endl;
            std::cout << "商品名称:" << good.name << std::endl;
            std::cout << "商品价格:" << good.price << std::endl;
            std::cout << "商品描述:" << good.description << std::endl;
            std::cout << "***********************************************************" << std::endl;
            std::cout << "请选择(y/n):" << std::endl;
            char choice;
            std::cin >> choice;
            if (choice == 'y')
            {
                good.state = 2;
                std::cout << "下架成功" << std::endl;
                save(goods);
                return;
            }
            else
            {
                std::cout << "取消下架" << std::endl;
                return;
            }
        }
    }
    std::cout << "该商品不存在，下架失败" << std::endl;
}