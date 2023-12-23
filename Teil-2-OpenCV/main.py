import numpy as np
import cv2

filepath_yoshi = './figures/yoshi.png'
save_filepath = './figures/yoshi3.png'

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


def every_5_lines_black(img, height: int, width: int):
    schwarz = (0, 0, 0)

    for y in range(0, height, 5):
        img[y, :] = schwarz  # Set the entire row to black

    return img



if __name__ == '__main__':
    print(f"OpenCV-Version: {cv2.__version__}")
    img = cv2.imread(filepath_yoshi)  # load the attached-to-the-Aufgabe image

    dimensions = img.shape  # get the height, the width and the number of color channels
    höhe = dimensions[0]
    breite = dimensions[1]

    print(f"dimensions of the image are {dimensions}")

    _dst = img.astype(np.float32)  # change the data type of the image to Floating point numbers

    size_of_rectangle = [10, 10]
    corners = get_quadrat_corners(breite // 2, höhe // 2, size_of_rectangle[0], size_of_rectangle[1])
    cv2.rectangle(img, (corners[0], corners[1]), (corners[2], corners[3]), (0, 0, 255), 1)  # draw a rectangle 10x10 pixels in the center of image

    img = every_5_lines_black(img, höhe, breite)
    cv2.imshow("image", img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

    # cv2.imshow("image", _dst)
    # cv2.waitKey(0)
    # cv2.destroyAllWindows()

    cv2.imwrite(filename=save_filepath, img=img, params=(cv2.IMWRITE_PNG_COMPRESSION, 1))  # 1 indicates compression, 0 - no compression
