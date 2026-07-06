import tkinter as tk
from tkinter import filedialog, messagebox, font

class Notepad:
    def __init__(self, root):
        self.root = root
        self.root.title("메모장")
        self.root.geometry("900x600")

        self.current_file = None

        # 기본 폰트
        self.font_family = "Arial"
        self.font_size = 12

        # ===== 메뉴 =====
        self.menu = tk.Menu(root)
        root.config(menu=self.menu)

        file_menu = tk.Menu(self.menu, tearoff=0)
        self.menu.add_cascade(label="파일", menu=file_menu)
        file_menu.add_command(label="새 파일", command=self.new_file)
        file_menu.add_command(label="열기", command=self.open_file)
        file_menu.add_command(label="저장", command=self.save_file)
        file_menu.add_command(label="다른 이름으로 저장", command=self.save_as)
        file_menu.add_separator()
        file_menu.add_command(label="종료", command=self.exit_app)

        edit_menu = tk.Menu(self.menu, tearoff=0)
        self.menu.add_cascade(label="편집", menu=edit_menu)
        edit_menu.add_command(label="잘라내기", command=lambda: self.text.event_generate("<<Cut>>"))
        edit_menu.add_command(label="복사", command=lambda: self.text.event_generate("<<Copy>>"))
        edit_menu.add_command(label="붙여넣기", command=lambda: self.text.event_generate("<<Paste>>"))

        view_menu = tk.Menu(self.menu, tearoff=0)
        self.menu.add_cascade(label="보기", menu=view_menu)
        view_menu.add_command(label="글꼴 크게", command=self.font_bigger)
        view_menu.add_command(label="글꼴 작게", command=self.font_smaller)

        # ===== 프레임 =====
        self.frame = tk.Frame(root)
        self.frame.pack(fill=tk.BOTH, expand=1)

        # ===== 줄 번호 =====
        self.line_numbers = tk.Text(self.frame, width=4, padx=5, takefocus=0,
                                     border=0, background="#f0f0f0", state="disabled")
        self.line_numbers.pack(side=tk.LEFT, fill=tk.Y)

        # ===== 텍스트 영역 =====
        self.text = tk.Text(self.frame, undo=True, wrap="none")
        self.text.pack(fill=tk.BOTH, expand=1, side=tk.LEFT)

        self.scrollbar = tk.Scrollbar(self.frame, command=self.on_scroll)
        self.scrollbar.pack(side=tk.RIGHT, fill=tk.Y)

        self.text.config(yscrollcommand=self.scrollbar.set)

        # 폰트 적용
        self.update_font()

        # 이벤트 바인딩
        self.text.bind("<KeyRelease>", self.update_line_numbers)
        self.text.bind("<MouseWheel>", self.update_line_numbers)
        self.text.bind("<ButtonRelease>", self.update_line_numbers)

        self.update_line_numbers()

    # ===== 줄 번호 =====
    def update_line_numbers(self, event=None):
        self.line_numbers.config(state="normal")
        self.line_numbers.delete("1.0", tk.END)

        lines = self.text.get("1.0", tk.END).split("\n")
        for i in range(1, len(lines)):
            self.line_numbers.insert(tk.END, f"{i}\n")

        self.line_numbers.config(state="disabled")

    # ===== 스크롤 동기화 =====
    def on_scroll(self, *args):
        self.text.yview(*args)
        self.line_numbers.yview(*args)

    # ===== 파일 기능 =====
    def new_file(self):
        self.text.delete("1.0", tk.END)
        self.current_file = None

    def open_file(self):
        file = filedialog.askopenfilename()
        if file:
            with open(file, "r", encoding="utf-8") as f:
                self.text.delete("1.0", tk.END)
                self.text.insert(tk.END, f.read())
            self.current_file = file
            self.update_line_numbers()

    def save_file(self):
        if self.current_file:
            with open(self.current_file, "w", encoding="utf-8") as f:
                f.write(self.text.get("1.0", tk.END))
        else:
            self.save_as()

    def save_as(self):
        file = filedialog.asksaveasfilename(defaultextension=".txt")
        if file:
            self.current_file = file
            self.save_file()

    def exit_app(self):
        if messagebox.askokcancel("종료", "종료하시겠습니까?"):
            self.root.destroy()

    # ===== 폰트 =====
    def update_font(self):
        f = font.Font(family=self.font_family, size=self.font_size)
        self.text.config(font=f)
        self.line_numbers.config(font=f)

    def font_bigger(self):
        self.font_size += 1
        self.update_font()

    def font_smaller(self):
        if self.font_size > 6:
            self.font_size -= 1
            self.update_font()


if __name__ == "__main__":
    root = tk.Tk()
    app = Notepad(root)
    root.mainloop()