from tkinter import *

root = Tk()
root.title("Test Title")
root.geometry("640x480+500+300") # 가로 * 세로 + x좌표 + y좌표

checkvar = IntVar()
checkbox = Checkbutton(root, text="오늘하루보지않기", variable=checkvar)
#checkbox.select()
#checkbox.deselect()
checkbox.pack()

checkvar2 = IntVar()
checkbox2 = Checkbutton(root, text="일주일동안 보지 않기", variable=checkvar2)
checkbox2.pack()

def btncmd():
    print(checkvar.get()) # 0 : 체크해제, 1 : 체크
    print(checkvar2.get())

btn = Button(root, text="클릭", command=btncmd)
btn.pack()





root.mainloop()