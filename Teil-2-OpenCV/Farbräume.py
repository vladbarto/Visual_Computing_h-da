import numpy as np
import cv2

filepath_yoshi = './figures/yoshi.png'
save_filepath = './figures/yoshi3.png'
mask_filepath = './figures/mask.png'
def get_quadrat_corners(central_position_x: int, central_position_y: int, dimension_x: int, dimension_y: int):
    """
    :param central_position_x: The center of rectangle, x parameter
    :param central_position_y: The center of parameter, y parameter
    Suppose I want a picture of dimension 10x10 pixels. For that I have the following params:
    :param dimension_x: dimension of final Quadrat, x
    :param dimension_y: dimension of final Quadrat, y
    :return: tuple having (x,y) for top-left corner and (x,y) for bottom_right corner
    """
    return [central_position_x - dimension_x//2, central_position_y - dimension_y//2,
            central_position_x + dimension_x//2, central_position_y + dimension_y//2]


def every_5_lines_black(img, height: int):
    schwarz = [0, 0, 0]

    for y in range(0, height, 5):
        img[y, :] = schwarz  # Set the entire row to black
    return img


def mask_change_color(mask, img, hueWert: int):
    hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

    höhe = hsv.shape[0]
    breite = hsv.shape[1]
    weiß = [255, 255, 255]

    h = hsv[:, :, 0]
    s = hsv[:, :, 1]
    v = hsv[:, :, 2]

    # Shift the hue
    hueChange = hueWert
    for y in range(höhe):
        for x in range(breite):
            if np.array_equal(mask[y, x], weiß):
                h[y, x] += hueChange

    # Combine new hue with s and v
    hsvnew = cv2.merge([h, s, v])

    # Update the original image with the modified hue values
    img[:,:,:] = cv2.cvtColor(hsvnew, cv2.COLOR_HSV2BGR)


def nothing(Wert):
    pass


if __name__ == '__main__':
    print(f"OpenCV-Version: {cv2.__version__}")
    img = cv2.imread(filepath_yoshi)  # load the attached-to-the-Aufgabe image
    mask = cv2.imread(mask_filepath)

    dimensions = img.shape  # get the height, the width and the number of color channels
    höhe = dimensions[0]
    breite = dimensions[1]

    print(f"dimensions of the image are {dimensions}")

    _dst = img.astype(np.float32)  # change the data type of the image to Floating point numbers

    size_of_rectangle = [10, 10]
    corners = get_quadrat_corners(breite // 2, höhe // 2, size_of_rectangle[0], size_of_rectangle[1])
    cv2.rectangle(img, (corners[0], corners[1]), (corners[2], corners[3]), (0, 0, 255), 1)  # draw a rectangle 10x10 pixels in the center of image

    img = every_5_lines_black(img, höhe)
    cv2.imshow("image", img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

    cv2.imshow("image", _dst)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

    cv2.imwrite(filename=save_filepath, img=img, params=(cv2.IMWRITE_PNG_COMPRESSION, 1))  # 1 indicates compression, 0 - no compression

    # 4.3. Farbräume
    yoshi = cv2.imread('./figures/yoshi.png')

    # Create a window
    cv2.namedWindow('yoshi')

    # Create a trackbar for color change
    cv2.createTrackbar('H', 'yoshi', 0, 180, nothing)

    while True:
        cv2.imshow('yoshi', yoshi)

        k = cv2.waitKey(1) & 0xFF
        if k == 27:  # 'Esc' key
            break

        # Get current position of the trackbar
        h = cv2.getTrackbarPos('H', 'yoshi')

        # Update the image with the modified hue values
        mask_change_color(mask, yoshi, h)

    cv2.destroyAllWindows()

