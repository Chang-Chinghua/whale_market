#include "menu.h"
#include "class/admin.h"
#include "class/user.h"
#include "class/good.h"

#include <iostream>

inline void back()
{
    system("pause");
    system("cls");
}
inline void inputError()
{
    std::cout << "输入错误" << std::endl;
    back();
}

int main()
{
    welcomeMessage();
    Admin admin;
    int choice = 4;
    while (true)
    {
        initialMenu();
        std::cout << "输入操作：";
        std::cin >> choice;
        switch (choice)
        {
        case 1:
        {
            std::vector<User> users;
            load(users);
            User *user = nullptr;
            std::vector<Good> goods;
            load(goods);
            bool flag = loginUser(user, users);
            // 登录失败
            if (!flag)
            {
                system("cls");
                back();
                break;
            }

            // 登录成功
            while (flag)
            {
                system("cls");
                bool flag2 = true;
                int choice;
                userMenu();
                std::cin >> choice;
                switch (choice)
                {
                case 1:
                    flag = false;
                    std::cout << "注销成功" << std::endl;
                    back();
                    break;
                case 2:
                    system("cls");
                    while (flag2)
                    {
                        buyerMenu();
                        int buyer_choice;
                        std::cin >> buyer_choice;
                        switch (buyer_choice)
                        {
                        case 1:
                            viewGood(goods);
                            back();
                            break;
                        case 2:
                            break;
                        case 3:
                            searchGood(goods);
                            back();
                            break;
                        case 4:                            
                            break;
                        case 5:
                            viewGoodIfo(goods);
                            back();
                            break;
                        case 6:
                            flag2 = false;
                            std::cout << "即将返回用户主界面" << std::endl;
                            back();
                            break;
                        default:
                            inputError();
                            break;
                        }
                    }
                    break;
                case 3:
                    system("cls");
                    while (flag2)
                    {
                        sellerMenu();
                        int seller_choice;
                        std::cin >> seller_choice;
                        switch (seller_choice)
                        {
                        case 1:
                            user->uploadGood(goods);
                            save(goods);
                            back();
                            break;
                        case 2:
                            user->viewGood(goods);
                            back();
                            break;
                        case 3:
                            user->modifyGood(goods);
                            save(goods);
                            back();
                            break;
                        case 4:
                            user->deleteGood(goods);
                            back();
                            break;
                        case 5:
                            break;
                        case 6:
                            flag2 = false;
                            std::cout << "即将返回用户主界面" << std::endl;
                            back();
                            break;
                        default:
                            inputError();
                            break;
                        }
                    }
                    break;
                case 4:
                    system("cls");
                    while (flag2)
                    {
                        userModifyMenu();
                        int modify_choice;
                        std::cin >> modify_choice;
                        switch (modify_choice)
                        {
                        case 1:
                            flag2 = false;
                            std::cout << "即将返回用户主界面" << std::endl;
                            back();
                            break;
                        case 2:
                            user->modify();
                            save(users);
                            back();
                            break;
                        case 3:
                            user->view();
                            back();
                            break;
                        case 4:
                            user->charge();
                            save(users);
                            back();
                            break;
                        default:
                            inputError();
                            break;
                        }
                    }
                    break;
                default:
                {
                    inputError();
                    break;
                }
                }
            }
            break;
        }

        case 2:
        {
            registerUser();
            back();
            break;
        }

        case 3:
        {
            // 不断尝试登录
            bool flag = adminLogin(admin);

            // 取消登录
            if (!flag)
            {
                std::cout << "*****************   登录失败!即将返回主菜单...  **********************" << std::endl;
                back();
                break;
            }

            // 登录成功
            std::cout << "****************************  登录成功!  **************************" << std::endl;
            back();
            while (flag)
            {
                system("cls");
                adminMenu();
                int adminChoice;
                std::cin >> adminChoice;
                switch (adminChoice)
                {
                case 1:
                    admin.viewGoods();
                    back();
                    break;
                case 2:
                    admin.searchGoods();
                    back();
                    break;
                case 3:
                    admin.viewOrders();
                    back();
                    break;
                case 4:
                    admin.viewUsers();
                    back();
                    break;
                case 5:
                    admin.deleteUsersID();
                    back();
                    break;
                case 6:
                    admin.deleteGoodsID();
                    back();
                    break;
                case 7:
                    std::cout << "注销成功" << std::endl;
                    flag = false;
                    back();
                    break;
                default:
                    inputError();
                    break;
                }
            }
            break;
        }

        case 4:
        {

            std::cout << "欢迎下次再来" << std::endl;
            system("pause");
            return 0;
            break;
        }

        default:
            inputError();
            break;
        }
    }
    system("pause");
    return 0;
}