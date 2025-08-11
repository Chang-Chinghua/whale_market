#ifndef ADMIN_H
#define ADMIN_H

#include <string>

class Admin
{
private:
    const std::string username = "admin";
    const std::string password = "88888888";

public:
    bool login(std::string &username, std::string &password) const;
    void viewGoods() const;
    void searchGoods() const;
    void deleteGoodsID() const;
    void viewUsers() const;
    void deleteUsersID() const;
    void viewOrders() const;
};

bool adminLogin(Admin &admin);

#endif