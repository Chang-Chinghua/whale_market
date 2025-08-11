#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "class/good.h"

void load(std::vector<Good> &goods)
{
    std::ifstream file("good.csv");
    if (!file.is_open())
    {
        std::cout << "文件打开失败" << std::endl;
        return;
    }
    std::string line;
    getline(file, line);
    while (getline(file, line))
    {
        std::stringstream s(line);
        std::string item;
        std::vector<std::string> good;
        good.reserve(7);
        while (getline(s, item, ','))
        {
            good.push_back(item);
        }
        goods.push_back(Good(good[0], good[1], std::stod(good[2]), good[3], good[4], good[5], static_cast<GoodState>(std::stoi(good[6]))));
    }
}

void save(std::vector<Good> &goods)
{
    std::ofstream file("good.csv");
    if (!file.is_open())
    {
        std::cout << "文件打开失败" << std::endl;
        return;
    }
    file << "商品ID,名称,价格,描述,卖家ID,上架时间,商品状态" << std::endl;
    for (auto good : goods)
    {
        file << good.id << "," << good.name << "," << good.price << "," << good.description << "," << good.user_id << "," << good.time << "," << static_cast<int>(good.state) << std::endl;
    }
}

std::string_view transState(const Good &good)
{
    if (good.state == GoodState::Sold)
    {
        return "已售出";
    }
    else if (good.state == GoodState::Off)
    {
        return "已下架";
    }
    else
    {
        return "销售中";
    }
}

void viewAllGood(const std::vector<Good> &goods)
{
    std::cout << "***************************************************************" << std::endl;
    std::cout << "ID\t名称\t价格\t上架时间\t卖家ID" << std::endl;
    std::cout << "***************************************************************" << std::endl;
    for (const auto &good : goods)
    {
        if (good.state == GoodState::Selling)
        {
            std::cout << good.id << "\t" << good.name << "\t" << good.price << "\t" << good.time << "\t" << good.user_id << std::endl;
        }
    }
    std::cout << "***************************************************************" << std::endl;
}

void searchGood(const std::vector<Good> &goods)
{
    std::string name;
    std::cout << "请输入商品名称:";
    std::cin >> name;
    std::cout << "***************************************************************" << std::endl;
    std::cout << "ID\t名称\t价格\t上架时间\t卖家ID" << std::endl;
    for (const auto &good : goods)
    {
        if (good.name.find(name) != std::string::npos && good.state == GoodState::Selling)
        {
            std::cout << good.id << "\t" << good.name << "\t" << good.price << "\t" << good.time << "\t" << good.user_id << std::endl;
        }
    }
    std::cout << "***************************************************************" << std::endl;
}

void viewGoodIfo(const std::vector<Good> &goods)
{
    viewAllGood(goods);
    std::string id;
    std::cout << "请输入商品ID:";
    std::cin >> id;
    std::cout << "***************************************************************" << std::endl;
    for (const auto &good : goods)
    {
        if (good.id == id)
        {
            std::cout << "商品ID:" << good.id << std::endl;
            std::cout << "商品名称：" << good.name << std::endl;
            std::cout << "商品价格：" << good.price << std::endl;
            std::cout << "商品描述：" << good.description << std::endl;
            std::cout << "卖家ID:" << good.user_id << std::endl;
            std::cout << "上架时间：" << good.time << std::endl;
            std::cout << "商品状态：" << transState(good) << std::endl;
        }
    }
    std::cout << "***************************************************************" << std::endl;
}
