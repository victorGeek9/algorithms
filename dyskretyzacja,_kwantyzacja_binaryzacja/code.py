import math as mt
import matplotlib.pyplot as plt
import numpy as np
from PIL import Image
from skimage import io
from scipy.signal import argrelextrema

#2
A = 1.0
fs = 4000
q = 8

def s(t, f):
    return A*np.sin(2*np.pi*f*t)

def probkowanie(i, f):
    arr = []
    for t in i:
        arr.append(s(t, f))
    return arr

x = np.arange(0, 1, 1/fs)
t = [20, 21, 30, 45, 50, 100, 150, 200, 250, 1000]


for czest in t:
    y = probkowanie(x, czest)
    plt.plot(x, y)
    plt.xlabel('t[s]')
    plt.ylabel('F(t)')
    plt.title(str(czest) + 'Hz')
    plt.show()

'''
4)
Twierdzenie o próbkowaniu, twierdzenie Nyquista–Shannona
Sygnał ciągły może być ponownie odtworzony z sygnału dyskretnego, 
jeśli był próbkowany z częstotliwością co najmniej dwa razy 
większą od granicznej częstotliwości swego widma.
5)
Aliasing – nieodwracalne zniekształcenie sygnału w procesie 
próbkowania wynikające z niespełnienia założeń twierdzenia o 
próbkowaniu. Zniekształcenie objawia się obecnością w wynikowym 
sygnale składowych o błędnych częstotliwościach (aliasów).

'''


#3
img = io.imread('./first.png')
chang = []
for i in range(3):
    chang.append(img.copy())


plt.imshow(img)
plt.show()
print(img.shape)
print(len(img[0,0,:]))
rows,cols = img.shape[0:2]

for i in range(rows):
    for j in range(cols):
        chang[0][i,j, 0:3] = ((max(chang[0][i,j,0:3]) + min(chang[0][i,j,0:3])) // 3)


for i in range(rows):
    for j in range(cols):
        chang[1][i,j, 0:3] = (sum(chang[1][i,j,0:3]) // 3)

for i in range(rows):
    for j in range(cols):
        chang[2][i,j, 0:3] = (0.21*chang[2][i,j,0]) + (0.72*chang[2][i,j,1]) + (0.07*chang[2][i,j,2])


fig, axs = plt.subplots(3)
fig.suptitle('Skala szarosci')
for i in range(3):
    axs[i].imshow(chang[i])
plt.show()


fig, axs = plt.subplots(3)
fig.suptitle('Histogramy')
for i in range(3):
    histogram, bin_edges = np.histogram(chang[i], bins=256)
    axs[i].plot(bin_edges[0:-1], histogram)

plt.show()

histogram, bin_edges = np.histogram(chang[1], bins=16)
plt.plot(bin_edges[0:-1], histogram)
plt.show()

new = bin_edges.mean()
img[:,:,0:3] = img[:,:,0:3] * new
plt.imshow(img)
plt.show()
histogram, bin_edges = np.histogram(img, bins=256)
plt.plot(bin_edges[0:-1], histogram)
plt.show()

#4
fig, axs = plt.subplots(3)

img = io.imread('./second.jpg')
axs[0].imshow(img)

rows,cols = img.shape[0:2]

cp=img.copy()
for i in range(rows):
    for j in range(cols):
        cp[i,j, 0:3] = (0.21*cp[i,j,0]) + (0.72*cp[i,j,1]) + (0.07*cp[i,j,2])
axs[1].imshow(cp)

_ = axs[2].hist(cp[:, :, 0:3].ravel(), bins = 256, color = 'red', alpha = 0.5)
_ = plt.xlabel('Intensity Value')
_ = plt.ylabel('Count')
_ = plt.legend(['Total', 'Red_Channel', 'Green_Channel', 'Blue_Channel'])
plt.show()

picture = Image.open("./second.jpg")

def prog(histogram):
    return sum(histogram[1]) // len(histogram[1])

histogram = np.histogram(picture)
pr = prog(histogram)


print(pr)
pr = pr * 3

for i in range(rows):
    for j in range(cols):
        if pr > sum(picture.getpixel( (i,j) )):
            picture.putpixel( (i,j), (0,0,0))
        else:
            picture.putpixel( (i,j), (256,256,256))
plt.imshow(picture)
plt.show()


picture = Image.open("./second.jpg")
for i in range(rows):
    for j in range(cols):
        if pr < sum(picture.getpixel( (i,j) )):
            picture.putpixel( (i,j), (256,256,256))
plt.imshow(picture)
plt.show()
