tmp = input().split(" ")
length = int(tmp[0])
median = int(tmp[1])
num_list = [int(num) for num in input().split(" ")]

median_index = num_list.index(median)

left_balance = {0: 1}
lesser_count = 0
greater_count = 0
for i in range(median_index - 1, -1, -1):
    if num_list[i] < median:
        lesser_count += 1
    else:
        greater_count += 1

    balance = greater_count - lesser_count
    if balance in left_balance:
        left_balance[balance] += 1
    else:
        left_balance[balance] = 1

subsequence_count = 0
lesser_count = 0
greater_count = 0
for i in range(median_index, length):
    if num_list[i] < median:
        lesser_count += 1
    elif num_list[i] > median:
        greater_count += 1

    balance = greater_count - lesser_count
    if -balance in left_balance:
        subsequence_count += left_balance[-balance]

print(subsequence_count)
