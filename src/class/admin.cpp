#include "class/admin.h"
#include "class/good.h"
#include "class/user.h"
#include "class/order.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

bool adminLogin(Admin &admin)
{
    while (true)
    {
        std::cout << "请输入管理员姓名： ";
        std::string name;
        std::cin >> name;
        if (name == "q")
            return false;
        std::cout << "请输入管理员密码： ";
        std::string password;
        std::cin >> password;
        if (admin.login(name, password))
        {
            std::cout << "登录成功！" << std::endl;
            return true;
        }
        else
        {
            std::cout << "用户名或密码错误,请重新输入!(返回上一级菜单请在管理员姓名处输入q)" << std::endl;
        }
    }
}

bool Admin::login(std::string &username, std::string &password) const
{
    if (username == this->username && password == this->password)
        return true;
    else
        return false;
}
void Admin::viewGoods() const
{
    std::vector<Good> goods;
    load(goods);
    if (goods.empty())
    {
        std::cout << "没有商品" << std::endl;
        return;
    }

    std::cout << "**************************************************************************" << std::endl;
    std::cout << "ID\t名称\t价格\t卖家ID\t上架时间\t商品状态" << std::endl;
    for (auto good : goods)
    {
        std::cout << good.id << "\t" << good.name << "\t" << good.price << "\t";
        std::cout << good.user_id << "\t" << good.time << "\t" << transState(good) << std::endl;
    }

    std::cout << "**************************************************************************" << std::endl;
}
void Admin::searchGoods() const
{
    std::cout << "请输入商品名称:";
    std::string name;
    std::cin >> name;
    std::vector<Good> goods;
    load(goods);
    if (goods.empty())
    {
        std::cout << "没有商品" << std::endl;
        return;
    }

    std::cout << "**************************************************************************" << std::endl;

    bool flag = false;
    for (const auto &good : goods)
    {
        auto pos = good.name.find(name);
        if (pos != std::string::npos)
        {
            if (!flag)
            {
                flag = true;
                std::cout << "ID\t名称\t价格\t卖家ID\t上架时间\t商品状态" << std::endl;
            }

            std::cout << good.id << "\t" << good.name << "\t" << good.price << "\t";
            std::cout << good.user_id << "\t" << good.time << "\t" << transState(good) << std::endl;
        }
    }
    if (!flag)
    {
        std::cout << "没有找到你想搜索的商品，即将返回初始界面" << std::endl;
    }

    std::cout << "**************************************************************************" << std::endl;
}
void Admin::deleteGoodsID() const
{

    std::vector<Good> goods;
    load(goods);
    if (goods.empty())
    {
        std::cout << "没有商品" << std::endl;
        return;
    }
    std::cout << "请输入下架商品ID:";
    std::string id;
    std::cin >> id;
    bool flag = false;
    for (auto &good : goods)
    {
        if (good.id == id)
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
                flag = true;
                std::cout << "下架成功" << std::endl;
                break;
            }
            else
            {
                std::cout << "取消下架" << std::endl;
            }
        }
    }
    if (!flag)
    {
        std::cout << "该商品不存在，下架失败" << std::endl;
    }
    else
    {
        save(goods);
    }
}

void Admin::viewUsers() const
{
    std::vector<User> users;
    load(users);
    if (users.empty())
    {
        std::cout << "没有用户" << std::endl;
        return;
    }
    std::cout << "**************************************************************************" << std::endl;
    std::cout << "用户ID\t用户名\t联系方式\t地址\t余额" << std::endl;
    for (const auto &user : users)
    {
        std::cout << user.id << "\t" << user.name << "\t" << user.phone << "\t";
        std::cout << user.address << "\t" << user.balance << std::endl;
    }
    std::cout << "**************************************************************************" << std::endl;
}

void Admin::deleteUsersID() const
{
    std::vector<User> users;
    load(users);
    if (users.empty())
    {
        std::cout << "没有用户" << std::endl;
        return;
    }
    std::cout << "请输入删除用户ID:";
    std::string id;
    std::cin >> id;
    bool flag = false;
    for (auto user = users.begin(); user != users.end(); user++)
    {
        if (user->id == id)
        {
            std::cout << "确定要删除该用户吗:" << std::endl;
            std::cout << "***********************************************************" << std::endl;
            std::cout << "用户ID:" << user->id << std::endl;
            std::cout << "用户名:" << user->name << std::endl;
            std::cout << "联系方式:" << user->phone << std::endl;
            std::cout << "地址:" << user->address << std::endl;
            std::cout << "余额:" << user->balance << std::endl;
            std::cout << "***********************************************************" << std::endl;
            std::cout << "请选择(y/n):" << std::endl;
            char choice;
            std::cin >> choice;
            if (choice == 'y')
            {
                user = users.erase(user);
                flag = true;
                std::cout << "删除成功" << std::endl;
                break;
            }
            else
            {
                std::cout << "取消删除" << std::endl;
            }
        }
    }
    if (!flag)
    {
        std::cout << "该用户不存在，删除失败" << std::endl;
    }
    else
    {
        save(users);
    }
}

void Admin::viewOrders() const
{
    std::vector<Order> orders;
    load(orders);
    if (orders.empty())
    {
        std::cout << "没有订单" << std::endl;
        return;
    }
    std::cout << "**************************************************************************" << std::endl;
    std::cout << "ID\t商品ID\t交易金额\t交易时间\t卖家ID\t买家ID" << std::endl;
    for (const auto &order : orders)
    {
        std::cout << order.id << "\t" << order.good_id << "\t" << order.price << "\t";
        std::cout << order.time << "\t" << order.sold_id << "\t" << order.buy_id << std::endl;
    }
    std::cout << "**************************************************************************" << std::endl;
}
