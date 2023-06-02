def is_leap(year):
  if year % 400 == 0:
    return 1
  if year % 100 == 0:
    return 0
  if year % 4 != 0:
    return 0
  return 1

def join(lst):
  ret=0
  for b in lst:
    ret = ret * 2 + b
  return ret

A=[]
for i in range(1500, 2501):
  A.append(is_leap(i))

for i in range(0, 1000, 8):
  #print(i, A[i:i+8], join(A[i:i+8]))
  print(join(A[i:i+8]), end=", ")

#print(A)

#print(is_leap(1900))
#print(is_leap(2000))

