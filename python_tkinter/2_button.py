from tkinter import *

root = Tk()
root.title("Test Title")

btn1 = Button(root, text="버튼1").pack()

btn2 = Button(root, padx = 5, pady = 10, text="버튼2")
btn2.pack()

btn3 = Button(root, padx = 10, pady = 5, text="버튼3")
btn3.pack()

btn4 = Button(root, width=10, height=3,text="버튼4").pack()

btn5 = Button(root, fg="red", bg="yellow",text="test").pack()

photo = PhotoImage(file="image/img.png")
btn = Button(root, image=photo).pack()

def btncmd():
    print("버튼 클릭")

btn7 = Button(root, text="동작버튼", command=btncmd).pack()


root.mainloop()