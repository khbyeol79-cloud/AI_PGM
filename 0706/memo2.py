import tkinter as tk
from tkinter import font
from tkinter import ttk

root = tk.Tk()
root.title("파이썬 메모장")
root.geometry("800x600")

# 기본 폰트
current_font = tk.StringVar(value="맑은 고딕")
current_size = tk.IntVar(value=12)

# 텍스트 영역
text = tk.Text(root, undo=True,
               font=(current_font.get(), current_size.get()))
text.pack(fill="both", expand=True)

# 스크롤바
scroll = tk.Scrollbar(text)
scroll.pack(side="right", fill="y")
scroll.config(command=text.yview)
text.config(yscrollcommand=scroll.set)


# ---------------- 파일 기능 ----------------
def new_file():
    global filename
    text.delete("1.0", tk.END)
    filename = None
    root.title("제목 없음 - 메모장")


def open_file():
    global filename
    file = filedialog.askopenfilename(
        filetypes=[("텍스트 파일", "*.txt"),
                   ("모든 파일", "*.*")]
    )

    if file:
        filename = file
        with open(file, "r", encoding="utf-8") as f:
            text.delete("1.0", tk.END)
            text.insert("1.0", f.read())
        root.title(f"{filename} - 메모장")


def save_file():
    global filename

    # 한 번도 저장한 적이 없으면 다른 이름으로 저장
    if filename is None:
        save_as_file()
        return

    with open(filename, "w", encoding="utf-8") as f:
        f.write(text.get("1.0", tk.END))

    root.title(f"{filename} - 메모장")

def save_as_file():
    global filename

    file = filedialog.asksaveasfilename(
        defaultextension=".txt",
        filetypes=[("텍스트 파일", "*.txt"),
                   ("모든 파일", "*.*")]
    )

    if file:
        filename = file
        with open(file, "w", encoding="utf-8") as f:
            f.write(text.get("1.0", tk.END))

        root.title(f"{filename} - 메모장")


text = tk.Text(root)
text.pack(fill="both", expand=True)
# ---------------- 폰트 변경 ----------------
def change_font(event=None):
    text.config(
        font=(current_font.get(),
              current_size.get())
    )


# ---------------- 라인 수 표시 ----------------
status = tk.Label(root, text="라인 : 1", anchor="e")
status.pack(fill="x", side="bottom")


def update_line(event=None):
    lines = int(text.index('end-1c').split('.')[0])
    status.config(text=f"라인 : {lines}")


text.bind("<KeyRelease>", update_line)

# 폰트
def font_setting():
    window = tk.Toplevel(root)
    window.title("폰트 설정")
    window.geometry("300x150")
    window.resizable(False, False)

    tk.Label(window, text="폰트").pack(pady=5)

    font_box = ttk.Combobox(
        window,
        textvariable=current_font,
        values=sorted(font.families()),
        state="readonly"
    )
    font_box.pack()

    tk.Label(window, text="글자 크기").pack(pady=5)

    size_box = ttk.Combobox(
        window,
        textvariable=current_size,
        values=[8, 9, 10, 11, 12, 14, 16, 18, 20, 24, 28, 32],
        state="readonly"
    )
    size_box.pack()

    def apply_font():
        text.config(
            font=(
                current_font.get(),
                current_size.get()
            )
        )

    tk.Button(
        window,
        text="적용",
        command=apply_font
    ).pack(pady=10)


# ---------------- 메뉴 ----------------
menu_bar = tk.Menu(root)
root.config(menu=menu_bar)

file_menu = tk.Menu(menu_bar, tearoff=0)
menu_bar.add_cascade(label="파일", menu=file_menu)

file_menu.add_command(label="새로 만들기", command=new_file)
file_menu.add_command(label="열기", command=open_file)
file_menu.add_separator()
file_menu.add_command(label="저장", command=save_file)
file_menu.add_command(label="다른 이름으로 저장", command=save_as_file)
file_menu.add_separator()
file_menu.add_command(label="종료", command=root.quit)

font_menu = tk.Menu(menu_bar, tearoff=0)
menu_bar.add_cascade(label="서식", menu=font_menu)
font_menu.add_command(
    label="글꼴...",
    command=font_setting
)



size_box = ttk.Combobox(
    root,
    textvariable=current_size,
    values=[8, 9, 10, 11, 12, 14, 16,
            18, 20, 24, 28, 32],
    width=5
)


# ---------------- 단축키 ----------------
root.bind("<Control-n>", lambda e: new_file())
root.bind("<Control-o>", lambda e: open_file())
root.bind("<Control-s>", lambda e: save_file())

# 복사
root.bind("<Control-c>",
          lambda e: text.event_generate("<<Copy>>"))

# 붙여넣기
root.bind("<Control-v>",
          lambda e: text.event_generate("<<Paste>>"))

# 잘라내기
root.bind("<Control-x>",
          lambda e: text.event_generate("<<Cut>>"))

# 전체선택
root.bind("<Control-a>",
          lambda e: text.tag_add("sel", "1.0", "end"))

update_line()
root.mainloop()