# 11328241from PyQt6.QtWidgets import (
    QApplication, QLabel, QLineEdit,
    QPushButton, QVBoxLayout, QWidget, QMessageBox
)
import sys

class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("PyQt6 輸入與互動")
        self.resize(400, 300)

        # 元件：標籤、輸入框、按鈕
        self.label = QLabel("請輸入文字並點擊按鈕：", self)
        self.input_field = QLineEdit(self)
        self.input_field.setPlaceholderText("在這裡輸入...")
        self.display_button = QPushButton("顯示文字", self)
        self.clear_button = QPushButton("清除文字", self)

        # 設定佈局
        layout = QVBoxLayout()
        layout.addWidget(self.label)
        layout.addWidget(self.input_field)
        layout.addWidget(self.display_button)
        layout.addWidget(self.clear_button)
        self.setLayout(layout)

        # 事件連接
        self.display_button.clicked.connect(self.display_text)
        self.clear_button.clicked.connect(self.clear_text)

    def display_text(self):
        text = self.input_field.text()
        if text.strip():
            self.label.setText(f"您輸入了：{text}")
        else:
            QMessageBox.warning(self, "警告", "輸入欄位為空！")

    def clear_text(self):
        self.input_field.clear()
        self.label.setText("請輸入文字並點擊按鈕：")

# 主程式入口
if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())


    def add_task():
    print("Add task")

def show_tasks():
    print("Show tasks")

def main():
    while True:
        print("\n=== To-Do List 管理系統 ===")
        print("1. 顯示任務清單")
        print("2. 新增任務")
        print("3. 離開系統")
        
        choice = input("請選擇功能（輸入數字）：").strip()
        
        if choice == "1":
            show_tasks()
        elif choice == "2":
            add_task()
        elif choice == "3":
            print("感謝使用，再見！")
            break
        else:
            print("無效的選擇，請重新輸入。\n")

# 啟動主程式
main()



def complete_task():
    if not pending_tasks:
        print("\n目前沒有未完成的任務！\n")
        return

    show_tasks()
    try:
        task_idx = int(input("請輸入要完成的任務編號：")) - 1
        if 0 <= task_idx < len(pending_tasks):
            task = pending_tasks.pop(task_idx)
            completed_tasks.append(task)
            print(f"\n成功完成任務：{task['title']}\n")
        else:
            print("\n無效的編號！請重新選擇。\n")
    except ValueError:
        print("\n輸入無效！請輸入數字。\n")