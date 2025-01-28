from calendar import isleap
import os

for i in range(1000,2101):
  print(i, int(isleap(i)))
