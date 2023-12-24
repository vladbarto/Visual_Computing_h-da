import cv2
import numpy as np

def init():
    input = cv2.imread('./figures/IMG_5871.png') / 255.0
    target = cv2.imread('./figures/jag.png') / 255.0

    # input = cv2.imread('./figures/FigSource.png') / 255.0
    # target = cv2.imread('./figures/FigTarget.png') / 255.0

    # Conversion to Floating point type, normalized to [0, 1] Bereich
    inputF = input.astype(np.float32)
    targetF = target.astype(np.float32)

    # Conversion to Lab-Farbraum
    input_lab = cv2.cvtColor(inputF, cv2.COLOR_BGR2Lab)
    target_lab = cv2.cvtColor(targetF, cv2.COLOR_BGR2Lab)

    return input_lab, target_lab


def color_transfer(input_lab, target_lab):
    for channel in range(3):  # 3 Kanäle: L, a, b
        input_mean = np.mean(input_lab[:, :, channel])
        input_standard_deviation = np.std(input_lab[:, :, channel])

        target_mean = np.mean(target_lab[:, :, channel])
        target_standard_deviation = np.std(target_lab[:, :, channel])

        input_lab[:, :, channel] -= input_mean  # i)
        input_lab[:, :, channel] /= input_standard_deviation  # ii)
        input_lab[:, :, channel] *= target_standard_deviation  # iii)
        input_lab[:, :, channel] += target_mean  # iv)

    return cv2.cvtColor(input_lab, cv2.COLOR_Lab2BGR)


def display_image(img):
    cv2.imshow("Ergebnis", img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


if __name__ == '__main__':
    input_lab, target_lab = init()
    ergebnis = color_transfer(input_lab, target_lab)
    display_image(ergebnis)
