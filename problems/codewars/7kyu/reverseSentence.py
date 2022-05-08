# usage, takes a sentence and reverses all the words that have a len of >= 5
def spin_words(sentence):
    return ' '.join(word[::-1] if len(word) >= 5 else word for word in sentence.split(' '))