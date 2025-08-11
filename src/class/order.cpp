#include "class/order.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

void load(std::vector<Order>& orders)
{
    std::ifstream file("order.csv");
    if (!file.is_open())
    {
        std::cout << "订单文件打开失败" << std::endl;
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
        Order order(v[0], v[1], std::stod(v[2]), v[3], v[4], v[5]);
        orders.push_back(order);
    }
}
void save(std::vector<Order>& orders)
{
    std::ofstream file("order.csv");
    if (!file.is_open())
    {
        std::cout << "订单文件打开失败" << std::endl;
        return;
    }
    file << "订单ID,商品ID,交易金额,交易时间,卖家ID,买家ID" << std::endl;
    for (auto order : orders)
    {
        file << order.id << "," << order.good_id << "," << order.price << "," << order.time << "," << order.sold_id << "," << order.buy_id << std::endl;
    }
}
