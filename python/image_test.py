#!/usr/bin/env python
# -*- coding: utf-8 -*-  

import random
import numpy as np
from PIL import Image, ImageDraw, ImageFont


SIZE=250
'''
line_array = [ 0 for j in range(SIZE) ]
array = [ line_array for j in range(SIZE) ]
print len(array)
print len(array[0])

for i in range(len(array)):
	for j in range(len(array[i])):
		value = SIZE*0.5
		if i < value and j < value:
			array[i][j] = 0
		elif i < value and j >= value:
			array[i][j] = 60
		elif i >= value and j < value:
			array[i][j] = 120
		elif i >= value and j >= value:
			array[i][j] = 180

array = np.array(array)
array = np.array(array, dtype='uint8')

arr = Image.fromarray(array)
print arr.size
arr.save("test.bmp", 'bmp')
'''

#创建原始图片
image = Image.new('RGB', (SIZE, SIZE))
draw = ImageDraw.Draw(image)

def randcolor():
	return (random.randint(0,255), random.randint(0,255), random.randint(0,255))

def randcolor_1(x, y):
	value = int((x + y) * 0.5)
	return (value, value, value)

for x in range(SIZE):
	for y in range(SIZE):
		draw.point((x,y), fill=randcolor_1(x,y))

#image.save("white.jpg", "jpeg")

#拓展原始图片
LEVEL=1
NEW_SIZE = SIZE + SIZE * LEVEL * 2
extend_image = Image.new('RGB', (NEW_SIZE, NEW_SIZE))

fnt = ImageFont.load_default()

number=1
for x in range(NEW_SIZE/SIZE):
	for y in range(NEW_SIZE/SIZE):
		tmp_image = image.copy()
		tmp_draw = ImageDraw.Draw(tmp_image)
		tmp_draw.text((SIZE/2,SIZE/2), str(number), font=fnt)
		extend_image.paste(tmp_image, box=(y * SIZE, x * SIZE, (y + 1) * SIZE, (x + 1) * SIZE))
		number += 1

extend_image.save("extend.jpg", "jpeg")
