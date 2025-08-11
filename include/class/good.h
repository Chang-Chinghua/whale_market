#ifndef GOOD_H
#define GOOD_H

#include <string>
#include <vector>

enum class GoodState
{
    Sold=1,
    Off=2,
    Selling=3
};

struct Good
{
    std::string id;
    std::string name;
    double price;
    std::string description;
    std::string user_id;
    std::string time;
    GoodState state;
    Good(std::string id, std::string name, double price, std::string description, std::string user_id, std::string time, GoodState state) : id(id), name(name), price(price), description(description), user_id(user_id), time(time), state(state) {}
};

void load(std::vector<Good> &goods);
void save(std::vector<Good> &goods);
std::string_view transState(const Good &good);
void viewAllGood(const std::vector<Good> &goods);
void searchGood(const std::vector<Good> &goods);
void viewGoodIfo(const std::vector<Good> &goods);

#endif