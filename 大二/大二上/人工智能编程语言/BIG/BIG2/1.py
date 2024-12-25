# 第一题（20分）
# 文本文件“news.txt”中包含了一些英文单词，每个单词占据文件的一行。请编写一个Python程序，该程序读取文件并统计每个单词出现的次数，然后将单词及其出现次数按照字母顺序写入另一个文件。格式如下：
# Area: 1
# Bay: 1
# Greater: 1
# 提示：要注意文件中字母的大小写，排序时大写字母应在小写字母之前。

wordTotal = {}
with open("news.txt", "r") as f:
    for line in f:  # 逐行读取文件
        word = line.strip()
        wordTotal[word] = wordTotal.get(word,0) + 1 # 统计单词出现次数，如果单词不存在则默认为0
sortedwords = sorted(wordTotal.keys(), key = lambda x: (x[0].islower(),x))  # 按照字母顺序排序，lambda函数用于排序时区分大小写
with open("1.txt","w") as f:
    for word in sortedwords:
        f.write(f"{word}: {wordTotal[word]}\n")