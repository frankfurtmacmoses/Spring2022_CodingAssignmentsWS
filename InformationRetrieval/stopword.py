import io
import tarfile
from logging import exception

import nltk
from nltk.corpus import stopwords
from nltk.tokenize import word_tokenize
import pprint

nltk.download('stopwords')


# word_tokenize accepts
# a string as an input, not a file.
def filter(file):
    stop_words = set(stopwords.words('english'))
    with open(file) as f:

        # Use this to read file content as a stream:
        line = f.read()
        words = line.split()
        for r in words:
            if not r in stop_words:
                appendFile = open('filter_' + f.name, 'a')
                appendFile.write(" " + r)
                appendFile.close()


def or_postings(posting1, posting2):
    p1 = 0
    p2 = 0
    result = list()
    while p1 < len(posting1) and p2 < len(posting2):
        if posting1[p1] == posting2[p2]:
            result.append(posting1[p1])
            p1 += 1
            p2 += 1
        elif posting1[p1] > posting2[p2]:
            result.append(posting2[p2])
            p2 += 1
        else:
            result.append(posting1[p1])
            p1 += 1
    while p1 < len(posting1):
        result.append(posting1[p1])
        p1 += 1
    while p2 < len(posting2):
        result.append(posting2[p2])
        p2 += 1
    return result


def and_postings(posting1, posting2):
    p1 = 0
    p2 = 0
    result = list()
    while p1 < len(posting1) and p2 < len(posting2):
        if posting1[p1] == posting2[p2]:
            result.append(posting1[p1])
            p1 += 1
            p2 += 1
        elif posting1[p1] > posting2[p2]:
            p2 += 1
        else:
            p1 += 1
    return result


def doInverted_index():
    docs = ["doc1.txt", "doc2.txt", "doc3.txt"]
    inverted_index = {}
    for i, doc in enumerate(docs):

        with open(doc) as f:
            content = f.read()
            for term in content.split():
                if term in inverted_index:
                    inverted_index[term].add(i)
                else:
                    inverted_index[term] = {i}
    return inverted_index


def tokenized():
    #   Create tokenized term with corresponding document_ID
    docs = ["doc1.txt", "doc2.txt", "doc3.txt"]
    for doc in docs:
        with open(doc) as f:
            content = f.read()
            # print(content)
            for term in content.split():
                print(term, doc[3])


if __name__ == "__main__":
    print("------***********************--------")
    print("Documents are now been tokenized")
    tokenized()
    print(f"\n Done tokenizing")

    print("------***********************--------")
    print("Generating inverted index")
    postingList = doInverted_index()
    print(f"\n Done Generating Inverted Index")

    # create dictionary of inverted index with no frequency
    # Note:
    # You can get posting list for any item by replacing the string and uncomment try and exception block:
    # try:
    #     print("PostingList for a")
    #     print(postingList['a'])
    # except exception as ex:
    #     print("string not in the document")

    # Question i:
    doInverted_index()
    pos1 = doInverted_index()
    p1 = list(pos1['index'])
    pos2 = doInverted_index()
    p2 = list(pos2['query'])
    result_i = and_postings(p1,p2)
    print(result_i)

    # Question ii
    doInverted_index()
    pos1 = doInverted_index()
    p1 = list(pos1['index'])
    pos2 = doInverted_index()
    p2 = list(pos2['query'])
    result_ii = or_postings(p1, p2)
    print(result_ii)

    # Question iii
    doInverted_index()
    pos1 = doInverted_index()
    p1 = list(pos1['search'])
    pos2 = doInverted_index()
    p2 = list(pos2['query'])
    temp_result_a = and_postings(p1, p2)

    doInverted_index()
    pos1 = doInverted_index()
    p1 = list(pos1['search'])
    pos2 = doInverted_index()
    p2 = list(pos2['retrieve'])
    temp_result_b = and_postings(p1, p2)

    doInverted_index()
    pos1 = doInverted_index()
    p1 = list(pos1[temp_result_a])
    pos2 = doInverted_index()
    p2 = list(pos2[temp_result_b])
    result_iv = or_postings(p1, p2)
    print(result_iv)

     # Question iv 

    doInverted_index()
    pos1 = doInverted_index()
    p1 = list(pos1['index'])
    pos2 = doInverted_index()
    p2 = list(pos2['cluster'])
    temp_result_a = or_postings(p1, p2)

    doInverted_index()
    pos1 = doInverted_index()
    p1 = list(pos1['web'])
    pos2 = doInverted_index()
    p2 = list(pos2['system'])
    temp_result_b = or_postings(p1, p2)

    doInverted_index()
    pos1 = doInverted_index()
    p1 = list(pos1[temp_result_a])
    pos2 = doInverted_index()
    p2 = list(pos2[temp_result_b])
    result_v = and_postings(p1, p2)
    print(result_v)



