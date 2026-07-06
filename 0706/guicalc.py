import tkinter as tk
from tkinter import messagebox

window = tk.Tk()
window.title("계산기")
window.geometry("300x400")
window.resizable(False, False)

expression = ""


def press(value):
    global expression
    expression += str(value)
    display.delete(0, tk.END)
    display.insert(0, expression)


def clear():
    global expression
    expression = ""
    display.delete(0, tk.END)


def calculate():
    global expression
    try:
        result = str(eval(expression))
        display.delete(0, tk.END)
        display.insert(0, result)
        expression = result
    except ZeroDivisionError:
        messagebox.showerror("오류", "0으로 나눌 수 없습니다.")
        clear()
    except:
        messagebox.showerror("오류", "잘못된 수식입니다.")
        clear()


# 입력창
display = tk.Entry(window, font=("Arial", 20), justify="right")
display.grid(row=0, column=0, columnspan=4, padx=10, pady=10, sticky="nsew")

# 버튼 정보
buttons = [
    "7", "8", "9", "/",
    "4", "5", "6", "*",
    "1", "2", "3", "-",
    "C", "0", "=", "+"
]

row = 1
col = 0

for button in buttons:
    if button == "=":
        cmd = calculate
    elif button == "C":
        cmd = clear
    else:
        cmd = lambda x=button: press(x)

    tk.Button(
        window,
        text=button,
        width=5,
        height=2,
        font=("Arial", 16),
        command=cmd
    ).grid(row=row, column=col, padx=5, pady=5, sticky="nsew")

    col += 1
    if col > 3:
        col = 0
        row += 1

# 행/열 크기 자동 조절
for i in range(5):
    window.grid_rowconfigure(i, weight=1)

for i in range(4):
    window.grid_columnconfigure(i, weight=1)

window.mainloop()