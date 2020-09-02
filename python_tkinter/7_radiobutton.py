from tkinter import *

root = Tk()
root.title("Test Title")
root.geometry("640x480+500+300") # 가로 * 세로 + x좌표 + y좌표

Label(root, text="메뉴를 선택하세요").pack()

burger_var = IntVar()
button1 = Radiobutton(root, text="햄버거", value=1, variable=burger_var)
button1.select()
button2 = Radiobutton(root, text="치즈버거", value=2, variable=burger_var)
button3 = Radiobutton(root, text="치킨버거", value=3, variable=burger_var)

button1.pack()
button2.pack()
button3.pack()

Label(root, text="음료를 선택하세요").pack()
drink_var = StringVar()
drink1 = Radiobutton(root, text="콜라", value="콜라", variable=drink_var)
drink1.select()
drink2 = Radiobutton(root, text="사이다", value="사이다", variable=drink_var)
drink3 = Radiobutton(root, text="환타", value="환타", variable=drink_var)

drink1.pack()
drink2.pack()
drink3.pack()


def btncmd():
    print(burger_var.get())
    print(drink_var.get())

btn = Button(root, text="주문", command=btncmd)
btn.pack()

root.mainloop()