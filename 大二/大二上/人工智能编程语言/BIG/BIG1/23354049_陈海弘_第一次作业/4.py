#第四题（30分）
#请编写一个Python程序，要求该程序可以帮助用户管理他们的购物清单。用户可以添加、查看、删除和编辑购物清单中的商品，还可以查看购物清单的总价格。各功能形成菜单供用户选择，包括退出功能。
#提示：购物清单是一个字典，其中商品名称是键，商品价格是值。通过input来输入每次要执行的操作，用循环来实现多次执行操作。

def display_meun(): #显示菜单
    print("1. Add item")
    print("2. View item")
    print("3. Delete item")
    print("4. Edit item")
    print("5. View total price")
    print("6. Exit")
    choice = input("Enter your choice: ")
    return choice

def add_item(shopping_list):#添加商品
    item = input("Enter item name: ") #输入商品名称
    name, price=item.split()
    shopping_list[name]=float(price)    #利用创建的字典shopping_list，将商品名称作为键，商品价格作为值，添加到字典中

def view_item(shopping_list):   #查看商品
    for name, price in shopping_list.items():   #遍历字典shopping_list，输出商品名称和价格
        print(name, price)

def delete_item(shopping_list): #删除商品
    item = input("Enter item name: ")
    if item in shopping_list:   #如果商品在字典shopping_list中
        del shopping_list[item] #删除商品
    else:
        print("Item not found")

def edit_item(shopping_list):   #编辑商品
    item = input("Enter item name and price separated by a space: ")
    name, price = item.split()
    position = input("Enter 'beginning' to add to the beginning or 'end' to add to the end: ").strip().lower()
    if position == 'beginning': #如果输入的位置是'beginning'
        shopping_list.insert(0, (name, float(price)))   #在字典shopping_list的第一个位置添加商品，也就是在字典的开头添加商品
    elif position == 'end':
        shopping_list.append((name, float(price)))      #在字典shopping_list的最后一个位置添加商品，也就是在字典的末尾添加商品
    else:
        print("Invalid position. Item not added.")


def view_total_price(shopping_list):
    total_price = sum(shopping_list.values())   #通过sum函数计算字典shopping_list中所有商品价格的总和
    print("Total price: ", total_price)

def main(): #主函数
    shopping_list = {}      #创建一个空字典shopping_list
    while True: #True表示循环一直执行，除非遇到输入6退出
        choice = display_meun()
        if choice == '1':
            add_item(shopping_list)
        elif choice == '2':
            view_item(shopping_list)
        elif choice == '3':
            delete_item(shopping_list)
        elif choice == '4':
            edit_item(shopping_list)
        elif choice == '5':
            view_total_price(shopping_list)
        elif choice == '6':
            break
        else:
            print("Invalid choice")