from tkinter import *

root = Tk()
root.title("Test Title")
root.geometry("640x480+500+300") # 가로 * 세로 + x좌표 + y좌표

listbox = Listbox(root, selectmode="extended", height=0)
listbox.insert(0, "사과")
listbox.insert(1, "딸기")
listbox.insert(2, "바나나")
listbox.insert(END, "수박")
listbox.insert(END, "포도")
listbox.pack()


def btncmd():
    #listbox.delete(0)
    #print(listbox.size())
    #print(listbox.get(0,3))
    #print(listbox.curselection())
    #print(listbox.get(listbox.curselection()))


btn = Button(root, text="클릭", command=btncmd)
btn.pack()





root.mainloop()