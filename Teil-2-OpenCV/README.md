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

Every time you access an image pixel at certain `[y][x]`, you will find in there a **color tuple** in BGR format.
```python
blue = (255, 0, 0)  # color blue, format BGR
img[315][220] = blue
```

### 7. Save an image on hard disk (die Festplatte)
For that we have the `imwrite` function with the following arguments:
- `filepath`: where do you want to save the image
- `img`: the image object you created earlier and edited
- (freiwillig) `params`: different flags for writing. It expects tuples
For more, look this up, under `ImWriteFlags`: 
> https://docs.opencv.org/4.x/d8/d6a/group__imgcodecs__flags.html#ga292d81be8d76901bff7988d18d2b42ac

and this:
> https://docs.opencv.org/4.x/d8/d6a/group__imgcodecs__flags.html