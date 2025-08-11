#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "good.h"


struct User
{
    std::string id;
    std::string name;
    std::string password;
    std::string phone;
    std::string address;
    double balance;
    User(std::string id, std::string name, std::string password, std::string phone, std::string address, double balance) : id(id), name(name), password(password), phone(phone), address(address), balance(balance) {}
    User() = default;
    void charge();
    void view();
    void modify();
    void uploadGood(std::vector<Good> &goods);
    void viewGood(const std::vector<Good> &goods);
    void modifyGood(std::vector<Good> &goods);
    void deleteGood(std::vector<Good> &goods);
    void sellerOrder();
    void buyerOrder();
    void buy(std::vector<Good> &goods);
};

void load(std::vector<User> &users);
void save(std::vector<User> &users);
void registerUser();
User* loginUser(std::vector<User> &users);

#endif