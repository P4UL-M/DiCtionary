import matplotlib.pylab as plt

file = open("experimentalRandom.out", "r")
lines = file.readlines()
file.close()

words = {}

for line in lines:
    line = line.strip()
    words[line] = words.get(line, 0) + 1

print("Total number of words: ", sum(words.values()))
print("Number of unique words: ", len(words))
print("Most common words: ")

sorted_words = sorted(words.items(), key=lambda x: x[1], reverse=True)

for i in range(min(10,len(sorted_words))):
    print(sorted_words[i][0], sorted_words[i][1])

print("Least common words: ")

for i in range(min(10,len(sorted_words))):
    print(sorted_words[-i][0], sorted_words[-i][1])

# plt.plot([x[1] for x in sorted_words])
# plt.show()

# stairs graph filled with color

mean_words = {}
# mean value of each 1000 words
for i in range(0, len(sorted_words), 100):
    mean_words[i] = sum([x[1] for x in sorted_words[i:i+100]])/100

plt.stairs([x for x in mean_words.values()], range(len(mean_words)+1) , fill=True)
plt.show()

import statistics

print("Mean: ", statistics.mean([x[1] for x in sorted_words]))
print("Median: ", statistics.median([x[1] for x in sorted_words]))
print("Standard deviation: ", statistics.stdev([x[1] for x in sorted_words]))