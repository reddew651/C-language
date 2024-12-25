import re   # 导入正则表达式模块，用于密码评分

class Account:  # 定义账户类
    def __init__(self, username, name, student_id, password_score): #__init__方法用于初始化对象
        self.username = username    # self表示对象本身，username、name、student_id、password_score是对象的属性
        self.name = name
        self.student_id = student_id
        self.password_score = password_score
        self.password = None

# 存储账户信息的列表
accounts = []

# 密码评分函数
def score_password(password):
    score = 0
    # 密码长度评分
    if len(password) <= 4:
        score += 5
    elif 5 <= len(password) <= 7:
        score += 10
    else:
        score += 25

    # 字母评分
    if re.search("[a-z A-Z]", password): # re.search()用于在字符串中查找匹配项
        if re.search("[a-z]", password) and re.search("[A-Z]", password):   # 包含大小写字母
            score += 20
        else:
            score += 10

    # 数字评分
    digit_count = len(re.findall("[0-9]", password))
    if digit_count == 1:
        score += 10
    elif digit_count > 1:
        score += 20

    # 符号评分
    symbol_count = len(re.findall("[^a-z A-Z 0-9]", password))    # ^表示非
    if symbol_count == 1:
        score += 10
    elif symbol_count > 1:
        score += 25

    # 奖励评分
    if re.search("[a-z A-Z]", password) and re.search("[0-9]", password):
        if symbol_count > 0 and re.search("[a-z]", password) and re.search("[A-Z]", password):
            score += 5
        elif symbol_count > 0:
            score += 3
        else:
            score += 2

    return score

# 密码强度评级
def evaluate_password_strength(score):
    if score >= 90:
        return "非常安全"
    elif score >= 80:
        return "安全"
    elif score >= 70:
        return "非常强"
    elif score >= 60:
        return "强"
    elif score >= 50:
        return "一般"
    elif score >= 25:
        return "弱"
    else:
        return "非常弱"


# 注册新用户
def register():
    username = input("请输入用户名: ")
    if any(acc.username == username for acc in accounts):
        print("用户名已存在，请选择其他用户名。")
        return

    password = input("请输入密码: ")
    score = score_password(password)
    print(f"密码评分为 {score}，属于 {evaluate_password_strength(score)} 等级。")

    name = input("请输入姓名: ")
    student_id = input("请输入学号: ")
    new_account = Account(username, name, student_id, score)
    new_account.password = password
    accounts.append(new_account)
    print("注册成功！")

# 用户登录
def login():
    username = input("请输入用户名: ")
    password = input("请输入密码: ")
    account = next((acc for acc in accounts if acc.username == username and acc.password == password), None)
    
    if account:
        print("登录成功！")
        print(f"用户名: {account.username}, 姓名: {account.name}, 学号: {account.student_id}, 密码评分: {account.password_score}")
    else:
        print("用户名或密码错误。")

# 修改密码
def change_password():
    username = input("请输入用户名: ")
    old_password = input("请输入原密码: ")
    account = next((acc for acc in accounts if acc.username == username and acc.password == old_password), None)
    
    if account:
        new_password = input("请输入新密码: ")
        score = score_password(new_password)
        print(f"新密码评分为 {score}，属于 {evaluate_password_strength(score)} 等级。")
        
        account.password = new_password
        account.password_score = score
        print("密码修改成功！")
    else:
        print("用户名或原密码错误，无法修改密码。")

# 主函数
def main():
    while True:
        print("\n请选择操作：1. 注册 2. 登录 3. 修改密码 4. 退出")
        choice = input("输入选项编号: ")
        
        if choice == "1":
            register()
        elif choice == "2":
            login()
        elif choice == "3":
            change_password()
        elif choice == "4":
            print("退出系统。")
            break
        else:
            print("无效的选择，请重新输入。")

# 运行主程序
if __name__ == "__main__":
    main()


