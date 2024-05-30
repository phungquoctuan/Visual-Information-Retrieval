import cv2
import numpy as np
import matplotlib.pyplot as plt

def show_histogram(frame):
    """Hiển thị histogram của khung hình."""
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    h, s, v = cv2.split(hsv)

    hist_h = cv2.calcHist([h], [0], None, [256], [0, 256])
    hist_s = cv2.calcHist([s], [0], None, [256], [0, 256])
    hist_v = cv2.calcHist([v], [0], None, [256], [0, 256])

    hist_h = np.array(hist_h)[:, 0]
    hist_s = np.array(hist_s)[:, 0]
    hist_v = np.array(hist_v)[:, 0]

    plt.plot(hist_h, color='b', label='Hue')
    plt.plot(hist_s, color='g', label='Saturation')
    plt.plot(hist_v, color='r', label='Value')
    plt.legend()
    plt.show()

# Chọn nguồn video là một video có sẵn trong PC
cap = cv2.VideoCapture('labs/lab01/2024-05-28 18-47-25.mp4')

while True:
  # Đọc khung hình tiếp theo
  ret, frame = cap.read()

  # Hiển thị khung hình
  cv2.imshow('Frame', frame)

  # Hiển thị histogram
  show_histogram(frame)

  # Nhấn 'q' để thoát
  if cv2.waitKey(1) & 0xFF == ord('q'):
    break

# Giải phóng nguồn
cap.release()
cv2.destroyAllWindows()
