import re
import tkinter as tk
from tkinter import messagebox


class Account:
    def __init__(self, username, name, student_id, password_score):
        self.username = username
        self.name = name
        self.student_id = student_id
        self.password_score = password_score
        self.password = None

accounts = []

def score_password(password):
    score = 0
    if len(password) <= 4:
        score += 5
    elif 5 <= len(password) <= 7:
        score += 10
    else:
        score += 25

    if re.search("[a-zA-Z]", password):
        if re.search("[a-z]", password) and re.search("[A-Z]", password):
            score += 20
        else:
            score += 10

    digit_count = len(re.findall("[0-9]", password))
    if digit_count == 1:
        score += 10
    elif digit_count > 1:
        score += 20

    symbol_count = len(re.findall("[^a-zA-Z0-9]", password))
    if symbol_count == 1:
        score += 10
    elif symbol_count > 1:
        score += 25

    if re.search("[a-zA-Z]", password) and re.search("[0-9]", password):
        if symbol_count > 0 and re.search("[a-z]", password) and re.search("[A-Z]", password):
            score += 5
        elif symbol_count > 0:
            score += 3
        else:
            score += 2

    return score

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

def clear_fields():
    entry_username.delete(0, tk.END)
    entry_password.delete(0, tk.END)
    entry_name.delete(0, tk.END)
    entry_student_id.delete(0, tk.END)
    entry_new_password.delete(0, tk.END)

def register():
    username = entry_username.get()
    password = entry_password.get()
    name = entry_name.get()
    student_id = entry_student_id.get()

    if not username or not password or not name or not student_id:
        messagebox.showerror("错误", "请填写所有字段。")
        return

    if any(acc.username == username for acc in accounts):
        messagebox.showerror("错误", "用户名已存在，请选择其他用户名。")
        return

    score = score_password(password)
    strength = evaluate_password_strength(score)
    messagebox.showinfo("密码评分", f"密码评分为 {score}，属于 {strength} 等级。")

    new_account = Account(username, name, student_id, score)
    new_account.password = password
    accounts.append(new_account)
    messagebox.showinfo("成功", "注册成功！")
    clear_fields()

def login():
    username = entry_username.get()
    password = entry_password.get()

    if not username or not password:
        messagebox.showerror("错误", "请填写用户名和密码。")
        return

    account = next((acc for acc in accounts if acc.username == username and acc.password == password), None)
    if account:
        messagebox.showinfo("成功", f"登录成功！\n用户名: {account.username}\n姓名: {account.name}\n学号: {account.student_id}\n密码评分: {account.password_score}")
    else:
        messagebox.showerror("错误", "用户名或密码错误。")
    clear_fields()

def change_password():
    username = entry_username.get()
    old_password = entry_password.get()
    new_password = entry_new_password.get()

    if not username or not old_password or not new_password:
        messagebox.showerror("错误", "请填写用户名、原密码和新密码。")
        return

    account = next((acc for acc in accounts if acc.username == username and acc.password == old_password), None)
    if account:
        score = score_password(new_password)
        strength = evaluate_password_strength(score)
        messagebox.showinfo("密码评分", f"新密码评分为 {score}，属于 {strength} 等级。")

        account.password = new_password
        account.password_score = score
        messagebox.showinfo("成功", "密码修改成功！")
    else:
        messagebox.showerror("错误", "用户名或原密码错误，无法修改密码。")
    clear_fields()

def show_register():
    clear_fields()
    frame_register.pack()
    frame_login.pack_forget()
    frame_change_password.pack_forget()

def show_login():
    clear_fields()
    frame_register.pack_forget()
    frame_login.pack()
    frame_change_password.pack_forget()

def show_change_password():
    clear_fields()
    frame_register.pack_forget()
    frame_login.pack_forget()
    frame_change_password.pack()

def main():
    global entry_username, entry_password, entry_name, entry_student_id, entry_new_password
    global frame_register, frame_login, frame_change_password

    root = tk.Tk()
    root.title("用户管理系统")

    menu = tk.Frame(root)
    menu.pack(pady=10)

    tk.Button(menu, text="注册", command=show_register).grid(row=0, column=0, padx=5)
    tk.Button(menu, text="登录", command=show_login).grid(row=0, column=1, padx=5)
    tk.Button(menu, text="修改密码", command=show_change_password).grid(row=0, column=2, padx=5)

    # Registration Frame
    frame_register = tk.Frame(root)
    tk.Label(frame_register, text="用户名:").grid(row=0, column=0)
    entry_username = tk.Entry(frame_register)
    entry_username.grid(row=0, column=1)

    tk.Label(frame_register, text="密码:").grid(row=1, column=0)
    entry_password = tk.Entry(frame_register, show="*")
    entry_password.grid(row=1, column=1)

    tk.Label(frame_register, text="姓名:").grid(row=2, column=0)
    entry_name = tk.Entry(frame_register)
    entry_name.grid(row=2, column=1)

    tk.Label(frame_register, text="学号:").grid(row=3, column=0)
    entry_student_id = tk.Entry(frame_register)
    entry_student_id.grid(row=3, column=1)

    tk.Button(frame_register, text="注册", command=register).grid(row=4, column=0, columnspan=2, pady=5)

    # Login Frame
    frame_login = tk.Frame(root)
    tk.Label(frame_login, text="用户名:").grid(row=0, column=0)
    entry_username = tk.Entry(frame_login)
    entry_username.grid(row=0, column=1)

    tk.Label(frame_login, text="密码:").grid(row=1, column=0)
    entry_password = tk.Entry(frame_login, show="*")
    entry_password.grid(row=1, column=1)

    tk.Button(frame_login, text="登录", command=login).grid(row=2, column=0, columnspan=2, pady=5)

    # Change Password Frame
    frame_change_password = tk.Frame(root)
    tk.Label(frame_change_password, text="用户名:").grid(row=0, column=0)
    entry_username = tk.Entry(frame_change_password)
    entry_username.grid(row=0, column=1)

    tk.Label(frame_change_password, text="原密码:").grid(row=1, column=0)
    entry_password = tk.Entry(frame_change_password, show="*")
    entry_password.grid(row=1, column=1)

    tk.Label(frame_change_password, text="新密码:").grid(row=2, column=0)
    entry_new_password = tk.Entry(frame_change_password, show="*")
    entry_new_password.grid(row=2, column=1)

    tk.Button(frame_change_password, text="修改密码", command=change_password).grid(row=3, column=0, columnspan=2, pady=5)

    # Start with Register Frame
    show_register()

    root.mainloop()

if __name__ == "__main__":
    main()