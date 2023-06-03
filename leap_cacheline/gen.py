#!/usr/bin/env python3

import random
NUM_YEARS=20_000_000

print("int years_to_check[%d] = {" % NUM_YEARS)
sep="  "
for i in range(NUM_YEARS):
  year = random.randint(1500, 2500)
  print("%s%d" % (sep, year), end="")
  sep=", "
  if i % 11 == 10:
    sep=",\n  "

print("\n };\n")

