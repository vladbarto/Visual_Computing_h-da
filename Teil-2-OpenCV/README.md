# Aufgabe 5: Dokumentation
## Notwendig, um der Code zu verstehen

### Prerequisites:
`import cv2`
### 1. Loading an image  
It's done with the method `imread` of `cv2`. A call would look like:
```python
import cv2
img = cv2.imread("filepath_of_image")

#If you need your image in Grayscale
img_grayscale = cv2.imread("filepath_of_image", cv2.IMREAD_GRAYSCALE)
```

### 2. Get the image Width, Height and Number of Color channels
For that there is the method `shape` of an image object-type.  
It will return a tuple with three parameters `(a, b, c)`:
- __a__: height
- __b__: width
- __c__: number of color channels.  

If the image is in *Grayscale*, then the returned tuple will not have the `c` parameter.

```python
dimensions = img.shape
height = dimensions[0]
width = dimensions[1]
number_of_color_channels = dimensions[2]
```
### 3. Change image type from 8UC1 to 32FC1:
Here it is used the constant `np.float32` from `numpy` package (np) and the method `astype` of the created image.  
So the code looks like this:
```python
import cv2
import numpy as np
dest_image = src_image.astype(np.float32)

# Display the new image:
cv2.imshow("image", dest_image)
cv2.waitKey(0)
cv2.destroyAllWindows()
```

### 4. Display a picture until a key is pressed
The code for that is already given in the Hinweis:
```python
import cv2

cv2.imshow("image", img)
cv2.waitKey(0)
cv2.destroyAllWindows()
```

### 5. Drawing a rectangle
> More about this here: https://docs.opencv.org/3.4/dc/da5/tutorial_py_drawing_functions.html

In all the above functions, you will see some common arguments as given below:

    img : The image where you want to draw the shapes
    color : Color of the shape. for BGR (Blau-Grün-Rot), pass it as a tuple, eg: (255,0,0) for blue. For grayscale, just pass the scalar value.
    thickness : Thickness of the line or circle etc. If -1 is passed for closed figures like circles, it will fill the shape. default thickness = 1
    lineType : Type of line, whether 8-connected, anti-aliased line etc. By default, it is 8-connected. cv.LINE_AA gives anti-aliased line which looks great for curves.

To draw a rectangle, you need __top-left corner__ and __bottom-right__ corner of rectangle. We will draw a red rectangle.
```python
import cv2
# a red rectangle, coming up!
cv2.rectangle(img,
              (384,0),  # Top-Left corner of rectangle (pixels)
              (510,128),  # Bottom-Right corner of rectangle (pixels)
              (0,0,255),  # Color in format BGR, values [0, 255]
              3  # Line thickness)  
```

### 6. Accessing and modifying pixel values
Img can be interpreted as a matrix of pixels:
- first argument refers to height, so y
- second argument refers to width, so x

Every time you access an image pixel at certain `[y][x]`, you will find in there a **color array** in BGR format.
```python
blue = [255, 0, 0]  # color blue, format BGR
img[315][220] = blue
```
```python
img[315, 220] = blue  # it's the same thing, but more often used
```
> More details here: https://docs.opencv.org/4.x/d3/df2/tutorial_py_basic_ops.html

### 7. Save an image on hard disk (die Festplatte)
For that we have the `imwrite` function with the following arguments:
- `filepath`: where do you want to save the image
- `img`: the image object you created earlier and edited
- (freiwillig) `params`: different flags for writing. It expects tuples
For more, look this up, under `ImWriteFlags`: 
> https://docs.opencv.org/4.x/d8/d6a/group__imgcodecs__flags.html#ga292d81be8d76901bff7988d18d2b42ac

and this:
> https://docs.opencv.org/4.x/d8/d6a/group__imgcodecs__flags.html

### 8. Changing Color-Space
For color conversion, we use the function `cv.cvtColor(input_image, flag)` where `flag` determines the type of conversion.
- Conversion BGR->HSV: `cv2.COLOR_BGR2HSV`

```python
    # Convert BGR to HSV
    hsv = cv2.cvtColor(src_image, cv.COLOR_BGR2HSV)
```
Once I have my image in HSV Color Space, I can extract all channels separately:
```python
h = hsv[:, :, 0]
s = hsv[:, :, 1]
v = hsv[:, :, 2]
```
In this code, `h` is an array with all pixels from the image containing only the `H Color Channel`. The same goes for `s` and `v`

Going further, we declare a constant and add it to the extracted `h` channel using `cv2.add(dest, src)` method:
```python
# Shift the hue
hueChange = 85
hnew = cv2.add(h, hueChange)

# Combine new hue with s and v
hsvnew = cv2.merge([hnew, s, v])
```
With `cv2.merge` we create a new image in HSV Color space with the modified channels.
> More details here: https://stackoverflow.com/questions/67448555/python-opencv-how-to-change-hue-in-hsv-channels

### 9. Schieberegler (Slider) as the Color Palette
> Excelent Doku here: https://docs.opencv.org/3.1.0/d9/dc8/tutorial_py_trackbar.html#gsc.tab=0

Used functions: `cv2.createTrackbar` and `cv2.getTrackbarPos`.
Start from an existing image:
```python
yoshi = cv2.imread('./figures/yoshi.png')
```
Then you have to create a window for reference:
```python
# Create a window
cv2.namedWindow('yoshi')
```
`createTrackbar` takes exactly 5 arguments:
- `name of the slider`: H
- `name of the window`: yoshi
- `min value`: 0
- `max value`: 180
- `callback function`: nothing, which in our case will be a function that has to take one argument and do nothing.
```python
def nothing(Wert):
    pass

# Create a trackbar for color change
cv2.createTrackbar('H', 'yoshi', 0, 180, nothing)
```
In an infinite loop, display the window and wait for a key to stop the program.
> Note: `cv2.destroyAllWindows()` must be called after the while loop.

Inside while loop, get current Trackbar position and store it in a variable, with `cv2.getTrackbarPos`, then modify your image:
```python
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
```