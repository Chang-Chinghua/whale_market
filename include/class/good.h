#ifndef GOOD_H
#define GOOD_H

#include <string>
#include <vector>

struct Good
{
    std::string id;
    std::string name;
    double price;
    std::string description;
    std::string user_id;
    std::string time;
    int state; // 1:已售出 2:已下架 3:销售中
    Good(std::string id, std::string name, double price, std::string description, std::string user_id, std::string time, int state) : id(id), name(name), price(price), description(description), user_id(user_id), time(time), state(state) {}
};

void load(std::vector<Good> &goods);
void save(std::vector<Good> &goods);
const std::string transState(const Good &good);
void viewGood(const std::vector<Good> &goods);
void searchGood(const std::vector<Good> &goods);
void viewGoodIfo(const std::vector<Good> &goods);

#endif