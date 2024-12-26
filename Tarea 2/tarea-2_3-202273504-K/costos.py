LETTER_COUNT = 26

# Costos de insercion
costs = []
for i in range(LETTER_COUNT):
    costs.append(25)

archivo = open("cost_insert.txt", "w")

line = ""
for cost in costs:
    line += str(cost) + " "
line += "\n"
archivo.write(line)

archivo.close()

# Costos de eliminación
costs = []
for i in range(LETTER_COUNT):
    costs.append(25)

archivo = open("cost_delete.txt", "w")

line = ""
for cost in costs:
    line += str(cost) + " "
line += "\n"
archivo.write(line)

archivo.close()

# Costos de sustitución
costs = []
for i in range(LETTER_COUNT):
    row = []
    for j in range(LETTER_COUNT):
        row.append(2 * abs(i - j))
    costs.append(row)

archivo = open("cost_replace.txt", "w")

for row in costs:
    line = ""
    for cost in row:
        line += str(cost) + " "
    line += "\n"
    archivo.write(line)

archivo.close()

# Costos de transposición
costs = []
for i in range(LETTER_COUNT):
    row = []
    for j in range(LETTER_COUNT):
        row.append(abs(i - j))
    costs.append(row)

archivo = open("cost_transpose.txt", "w")

for row in costs:
    line = ""
    for cost in row:
        line += str(cost) + " "
    line += "\n"
    archivo.write(line)

archivo.close()

