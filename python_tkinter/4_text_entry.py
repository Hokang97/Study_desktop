from tkinter import *

root = Tk()
root.title("Test Title")
root.geometry("640x480+500+300") # 가로 * 세로 + x좌표 + y좌표


txt = Text(root, width=30, height=5)
txt.pack()

txt.insert(END, "글자를 입력하세요")

e = Entry(root, width=30)
e.pack()
e.insert(0, "한줄만 입력")

def btncmd():
    print(txt.get("1.0", END)) # 1 : 첫번째 라인 0 : 0번째 column 위치
    print(e.get())

    txt.delete("1.0", END)
    e.delete(0, END)

btn = Button(root, text="클릭", command=btncmd)
btn.pack()

root.mainloop()