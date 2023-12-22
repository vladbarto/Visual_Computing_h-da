import numpy as np
import cv2

filepath_yoshi = './figures/yoshi.png'

if __name__ == '__main__':
    print(f"OpenCV-Version: {cv2.__version__}")
    img = cv2.imread(filepath_yoshi)
    cv2.imshow("image", img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()