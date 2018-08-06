#!/usr/bin/env python
# -*- coding: utf-8 -*-  

import random
import numpy as np
from PIL import Image, ImageDraw, ImageFont


SIZE=10
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

def randcolor():
	return (random.randint(0,255), random.randint(0,255), random.randint(0,255))

def randcolor_1(x, y):
	value = int((x + y) * 0.5)
	return (value, value, value)

src_image = Image.new('RGB', (SIZE, SIZE))
src_draw = ImageDraw.Draw(src_image)
for x in range(SIZE):
	for y in range(SIZE):
		src_draw.point((x,y), fill=randcolor_1(x,y))

image_list_array = []
#image_list_array.append(src_draw)

LEVEL=1
copy_number = 1
fnt = ImageFont.load_default()

for x in range(-1*LEVEL, LEVEL + 1, 1):
	line_array = []
	for y in range(-1*LEVEL, LEVEL + 1, 1):
		if x == 0 and y == 0:
			line_array.append(src_image)
		else:
			copy_image = src_image.copy()
			copy_draw = ImageDraw.Draw(copy_image)
			copy_draw.text((SIZE/2,SIZE/2), str(copy_number), font=fnt)
			copy_number += 1
			line_array.append(copy_image)
	image_list_array.append(line_array)


#拓展原始图片
NEW_SIZE = SIZE + SIZE * LEVEL * 2
extend_image = Image.new('RGB', (NEW_SIZE, NEW_SIZE))

for y in range(len(image_list_array)):
	for x in range(len(image_list_array[y])):
		extend_image.paste(image_list_array[y][x], box=(x * SIZE, y * SIZE, (x + 1) * SIZE, (y + 1) * SIZE))

extend_image.save("extend.jpg", "jpeg")

pos_array=list()
for x in range(-1 * SIZE/2, SIZE/2 + 1):
	pos_array.append([(y, x) for y in range(-1 * SIZE/2, SIZE/2 + 1)])

for x in range(len(pos_array)):
	print pos_array[x]

		
