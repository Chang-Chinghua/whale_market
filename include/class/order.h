#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <vector>

struct Order
{
    const std::string id;
    const std::string good_id;
    const double price;
    const std::string time;
    const std::string sold_id;
    const std::string buy_id;
    Order(std::string id, std::string good_id, double price, std::string time, std::string sold_id, std::string buy_id) : id(id), good_id(good_id), price(price), time(time), sold_id(sold_id), buy_id(buy_id) {}
};

void load(std::vector<Order> &orders);
void save(std::vector<Order> &orders);

#endif