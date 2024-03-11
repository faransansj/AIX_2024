'''
##################################################
# Image Data type check GUI                      #
# upload image then print type and max, min      #
# user : midori_sour0216                         #
##################################################
'''

import tkinter as tk
from tkinter import filedialog
from PIL import Image
import numpy as np

def upload_image():
    file_path = filedialog.askopenfilename()
    if file_path:
        image = Image.open(file_path)
        image_array = np.array(image)

        # 데이터 타입, 최소값, 최대값 출력
        data_type_label.config(text=f"Data type: {image_array.dtype}")
        min_val_label.config(text=f"Min value: {image_array.min()}")
        max_val_label.config(text=f"Max value: {image_array.max()}")

# tkinter 윈도우 생성
root = tk.Tk()
root.title("Image Upload and Check")

# 버튼과 레이블 설정
upload_button = tk.Button(root, text="Upload Image", command=upload_image)
upload_button.pack()

data_type_label = tk.Label(root, text="Data type: ")
data_type_label.pack()

min_val_label = tk.Label(root, text="Min value: ")
min_val_label.pack()

max_val_label = tk.Label(root, text="Max value: ")
max_val_label.pack()

# GUI 실행
root.mainloop()
