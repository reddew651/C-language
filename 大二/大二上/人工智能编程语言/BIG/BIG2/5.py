
from tkinter import *

top = Tk()

top.geometry("400x250")

uname = Label(top, text = "Username").place(x = 30,y = 50)

password = Label(top, text = "Password").place(x = 30, y = 90)

sbmitbtn = Button(top, text = "Submit",activebackground = "pink", activeforeground = "blue").place(x = 30, y = 120)

e1 = Entry(top,width = 20).place(x = 100, y = 50)


e2 = Entry(top, width = 20).place(x = 100, y = 90)

top.mainloop()
