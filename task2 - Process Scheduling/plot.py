import matplotlib.pyplot as plt
import numpy as np
file = open('data1.txt', 'r')
x = file.readline()
y = file.readline()
xx = []
yy = []
file = open('data1.txt', 'r')
x = file.readline().split(' ')
y = file.readline().split(' ')
for i in x:
    if(i == '\n' or i == ' ' or i==''): continue
    xx.append(int(i))
for i in y:
    if(i == '\n' or i ==' ' or i ==''): continue
    yy.append(int(i))

print(xx)
print(yy)

plt.step(xx , yy , where='post')
plt.plot(xx, yy, 'C0o', alpha=0.5)
plt.show()
