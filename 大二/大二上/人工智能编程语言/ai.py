for i in range(5):
    sentence = input("Enter a sentence: ")
    sentence = str.replace(sentence, "你", "我")
    sentence = str.replace(sentence, "吗", "")
    sentence = str.replace(sentence, "?", "!")
    sentence = str.replace(sentence, "？", "!")
    print(sentence)

