import csv
import random

random.seed(42)  # For reproducibility

rows = []
for _ in range(100):
    row_length = random.randint(5, 20)
    row = [(random.randint(0, 99), random.randint(10, 200)) for _ in range(row_length)]
    rows.append(row)

with open("Connections.txt", 'w') as my_csv:
    csvWriter = csv.writer(my_csv,delimiter=',')
    csvWriter.writerows(rows)