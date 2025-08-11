项目教程:https://cui-jiacai.gitbook.io/whale-market

原项目地址:https://github.com/201220014/WhaleMarket

`TODO`: 

1. 
>  - 在全局命名空间中为不同实体定义重名的自由函数 `load/save`，并用“输出参数”`std::vector<T>&` 承载结果，这更偏 C 式过程化接口：
>  ```19:24:include/class/good.h
>  void load(std::vector<Good> &goods);
>  void save(std::vector<Good> &goods);
>  ```
>  ```18:20:include/class/order.h
>  void load(std::vector<Order> &orders);
>  void save(std::vector<Order> &orders);
>  ```
>  ```31:34:include/class/user.h
>  void load(std::vector<User> &users);
>  void save(std::vector<User> &users);
>  ```
>  - 修改建议（方向性）：
>    - 返回值承载数据，避免输出参数：例如 `std::vector<Good> loadGoods();`，并让编译器用返回值优化/移动构造。
>    - 为保存接口使用只读视图：例如 `void saveGoods(std::span<const Good> goods);` 或 `const std::vector<Good>&`。
>    - 将这些函数置于各自命名空间（如 `io::good::load`）或作为相关类型的静态成员，避免全局重名和 ADL 干扰。
>
>  回复“继续”我会给出下一处。
>
>  - 重点
>    - 指出全局 `load/save` + 输出参数是 C 风格；建议用返回值、只读视图和命名空间/静态成员来 C++ 化。

2.

>   - 文件 `include/class/user.h` 使用了“数据包”式的 `struct`，所有成员变量公开可写，偏 C 风格的数据暴露：
>   ```11:18:include/class/user.h
>   struct User
>   {
>       std::string id;
>       std::string name;
>       std::string password;
>       std::string phone;
>       std::string address;
>       double balance;
>       User(std::string id, std::string name, std::string password, std::string phone, std::string address, double balance) : id(id), name(name), password(password), phone(phone), address(address), balance(balance) {}
>       User() = default;
>       // ...
>   };
>   ```
>   - 修改建议（方向性）：
>     - 将敏感或需保持不变式的字段设为私有，提供必要的访问器和变更接口（如 `balance` 的充值/消费、`password` 的修改流程等）。
>     - 如需聚合初始化，可提供最小化且语义清晰的构造函数，避免随意改写字段导致不一致。
>     - 可将与 `User` 状态变更相关的逻辑（上传/下单等）限定对对象自身可见的数据修改，减少“外部直接改字段”的可能。
>
>   回复“继续”我会给出下一处。
>
>   - 本次要点
>     - 指出 `User` 的公开可写字段是 C 风格数据暴露；建议以私有成员 + 明确接口的方式封装不变式。


