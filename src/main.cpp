#include "menu.h"
#include "class/admin.h"
#include "class/user.h"
#include "class/good.h"
#include "tools/clear_screen.h"
#include <iostream>
#include <cstdlib>


inline void inputError()
{
    std::cout << "输入错误" << std::endl;
    std::system("pause");
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
            user = loginUser(users);
            bool flag = true;

            // 登录失败
            if(user == nullptr)
            {
                flag=false;
                clear_screen();
                std::system("pause");
                break;
            }

            // 登录成功
            while (flag)
            {
                clear_screen();
                bool flag2 = true;
                int choice;
                userMenu();
                std::cin >> choice;
                switch (choice)
                {
                case 1:
                    flag = false;
                    std::cout << "注销成功" << std::endl;
                    std::system("pause");
                    break;
                case 2:
                    while (flag2)
                    {
                        clear_screen();
                        buyerMenu();
                        int buyer_choice;
                        std::cin >> buyer_choice;
                        switch (buyer_choice)
                        {
                        case 1:
                            viewAllGood(goods);
                            std::system("pause");
                            break;
                        case 2:
                            user->buy(goods);
                            std::system("pause");
                            break;
                        case 3:
                            searchGood(goods);
                            std::system("pause");
                            break;
                        case 4: 
                            user->buyerOrder();
                            std::system("pause");                           
                            break;
                        case 5:
                            viewGoodIfo(goods);
                            std::system("pause");
                            break;
                        case 6:
                            flag2 = false;
                            std::cout << "即将返回用户主界面" << std::endl;
                            std::system("pause");
                            break;
                        default:
                            inputError();
                            break;
                        }
                    }
                    break;
                case 3:
                    while (flag2)
                    {
                        clear_screen();
                        sellerMenu();
                        int seller_choice;
                        std::cin >> seller_choice;
                        switch (seller_choice)
                        {
                        case 1:
                            user->uploadGood(goods);
                            save(goods);
                            std::system("pause");
                            break;
                        case 2:
                            user->viewGood(goods);
                            std::system("pause");
                            break;
                        case 3:
                            user->modifyGood(goods);
                            save(goods);
                            std::system("pause");
                            break;
                        case 4:
                            user->deleteGood(goods);
                            std::system("pause");
                            break;
                        case 5:
                            user->sellerOrder();
                            std::system("pause");
                            break;
                        case 6:
                            flag2 = false;
                            std::cout << "即将返回用户主界面" << std::endl;
                            std::system("pause");
                            break;
                        default:
                            inputError();
                            break;
                        }
                    }
                    break;
                case 4:
                    while (flag2)
                    {
                        clear_screen();
                        userModifyMenu();
                        int modify_choice;
                        std::cin >> modify_choice;
                        switch (modify_choice)
                        {
                        case 1:
                            flag2 = false;
                            std::cout << "即将返回用户主界面" << std::endl;
                            std::system("pause");
                            break;
                        case 2:
                            user->modify();
                            save(users);
                            std::system("pause");
                            break;
                        case 3:
                            user->view();
                            std::system("pause");
                            break;
                        case 4:
                            user->charge();
                            save(users);
                            std::system("pause");
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
            std::system("pause");
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
                clear_screen();
                std::system("pause");
                break;
            }

            // 登录成功
            std::cout << "****************************  登录成功!  **************************" << std::endl;
            std::system("pause");
            while (flag)
            {
                clear_screen();
                adminMenu();
                int adminChoice;
                std::cin >> adminChoice;
                switch (adminChoice)
                {
                case 1:
                    admin.viewGoods();
                    std::system("pause");
                    break;
                case 2:
                    admin.searchGoods();
                    std::system("pause");
                    break;
                case 3:
                    admin.viewOrders();
                    std::system("pause");
                    break;
                case 4:
                    admin.viewUsers();
                    std::system("pause");
                    break;
                case 5:
                    admin.deleteUsersID();
                    std::system("pause");
                    break;
                case 6:
                    admin.deleteGoodsID();
                    std::system("pause");
                    break;
                case 7:
                    std::cout << "注销成功" << std::endl;
                    flag = false;
                    std::system("pause");
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
            std::system("pause");
            return 0;
            break;
        }

        default:
            inputError();
            break;
        }
    }
    std::system("pause");
    return 0;
}