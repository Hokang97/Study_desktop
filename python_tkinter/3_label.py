from tkinter import *
from tkinter import LabelFrame
root = Tk()
root.title("Test Title")

lable1 = Label(root, text="안녕")
lable1.pack()
photo = PhotoImage(file="image/img.png")

lable2 = Label(root, image=photo)
lable2.pack()

def change():
    lable1.config(text="또 만나요")

    global photo2
    photo2 = PhotoImage(file="image/img2.png")
    lable2.config(image=photo2)

btn = Button(root, text="클릭", command=change).pack()


root.mainloop()