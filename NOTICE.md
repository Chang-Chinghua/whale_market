### NOTICE: 本项目 C++ 风格改进备忘与复习要点

本文件汇总本项目中曾出现的典型 C 风格用法与相应的现代 C++ 写法建议，便于后续复习与查漏补缺。未修改之处多为暂未掌握或改动较大，建议在有余力时逐步迭代。

---

### 输出与格式化
- 问题：使用 C 风格 `printf`/位置占位符进行格式化输出。
- 建议：统一使用 `std::cout` 流式输出；涉及格式化时优先 `std::format`（C++20），备选 `std::ostringstream` + `<iomanip>`。

### 时间与日期
- 问题：使用 `time_t`/`localtime`/`strftime` 搭配 `char buffer[]`。
- 建议：使用 `std::chrono::system_clock::now()` + `std::format("{:%Y-%m-%d}", tp)`；不具备 `std::format` 时用 `std::ostringstream` + `std::put_time`，避免手写缓冲区。

### 字符数组与 `sprintf`
- 问题：用 `char[]` + `sprintf` 生成 ID 或进行字符串拼接。
- 建议：使用 `std::string`/`std::string_view` 与 `std::format` 或流式拼接；消除手工缓冲区与可变参数带来的类型不安全。

### 颜色常量/全局常量的声明方式
- 问题：`extern const char*` 全局字符串常量定义在头/源文件，类型不安全且易发生 ODR/重复定义问题。
- 建议：在头文件使用 `inline constexpr std::string_view`，必要时置于命名空间。若已使用 `inline constexpr`，可移除对应 `.cpp` 中的重复定义。

### 清屏/暂停等外壳调用
- 问题：大量使用 `std::system("pause")`、`std::system("cls"/"clear")`。
- 建议：
  - 暂停：封装为可移植的“等待一次输入/回车”的小函数，避免 `system`。
  - 清屏：封装跨平台 `clear_screen()`；在支持 ANSI 的终端用转义序列复位光标与清屏，不支持时降级为打印多行换行。尽量把实现放到 `.cpp`，头文件只暴露接口或 `inline` 实现。

### 魔法数字与强类型
- 问题：用整型魔法值表示状态/菜单项等（如 `1/2/3` 表示商品状态）。
- 建议：
  - 状态使用 `enum class`（例如 `GoodState { Sold=1, Off=2, Selling=3 }`），比较与赋值均使用枚举常量。
  - 菜单分发可选用 `enum class` 提升可读性（若改动过大可暂缓）。

### 函数签名与 const-correctness
- 问题：
  - 仅输入的形参却声明为非常量左值引用（如 `std::string&`）。
  - 只读遍历函数参数声明为可写引用（如 `std::vector<T>&`）。
- 建议：
  - 仅输入参数改为 `std::string_view` 或 `const T&`。
  - 只读函数使用 `const T&`；仅在确需修改时使用非常量引用。

### 输出参数与过程式接口
- 问题：全局 `load/save` 使用“输出参数”`std::vector<T>&`，多个实体在全局命名空间重名，接口偏 C 风格。
- 建议（可逐步演进）：
  - 读取函数直接“按值返回容器”（依赖返回值优化/移动）；写入函数接收 `const&` 或 `std::span<const T>`。
  - 使用命名空间（如 `io::good::load`）或与类型关联，避免全局重名。

### 返回类型上的 `const`
- 问题：对按值返回类型加 `const`（如 `const std::string`）无意义且可能误导。
- 建议：去掉返回类型上的 `const`；若返回只读文本，考虑返回 `std::string_view`。

### RAII 与资源管理
- 问题：显式 `file.close()` 依赖手动关闭资源。
- 建议：依赖 RAII，作用域退出自动关闭；需要更小生存期时用局部作用域包裹。若需确保刷盘，使用 `flush()`（通常析构已会刷新）。

### 头/源一致性
- 问题：声明与实现签名不一致（例如将接口改为 `string_view` 后，源文件仍保留旧的非常量引用）。
- 建议：修改接口后，确保头文件与源文件一致，并复核所有调用点。

### 业务一致性（示例：ID 前缀）
- 提醒：统一 ID 前缀与格式（如订单 `Oxxxxx`/`Txxxxx` 的前缀一致性），避免数据文件中出现多种前缀混用。

---

### 已改进要点回顾（供对照）
- 将 `printf` 改为 `std::cout`，统一 C++ 输出风格。
- 使用 `std::chrono` + `std::format` 生成日期字符串，替代 `strftime`。
- ID 生成改用 `std::format`，消除 `char[]` + `sprintf`。
- 引入 `enum class GoodState`，并在多数处替换了魔法数字。
- `transState` 返回类型调整为 `std::string_view`。
- 只读函数（如 `viewGood`）参数改为 `const&`。
- `Admin::login` 形参改用 `std::string_view` 并与实现对齐。
- 颜色常量改为头文件 `inline constexpr std::string_view`。
- 新增清屏封装（但仍有 `std::system("pause")` 存在，后续可继续收敛）。

---

### 建议的后续行动清单（可择机逐步完成）
- 收敛所有 `std::system("pause")` 到统一的暂停函数，替换全工程调用。
- 若已用 `inline constexpr` 颜色常量，删除 `src/tools/color.cpp` 中的重复 C 风格定义，避免 ODR/重定义风险。
- 将全局 `load/save` 逐步演进为“返回值/只读视图 + 命名空间”的形式，减少过程式接口。
- 审视剩余只读函数的参数签名，确保 `const&` 一致性。
- 如需，逐步为菜单分发引入 `enum class`，并集中定义映射，提高可读性。

---

本清单旨在作为风格与实践的“复盘手册”。优先保证功能与稳定性，在不影响业务的前提下，逐步将 C 风格代码演进为现代 C++ 风格即可。


