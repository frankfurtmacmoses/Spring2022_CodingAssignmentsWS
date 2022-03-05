
from math import log10



v1 = [2,
0,
0,
4,
0,
1,
2,
3,
0]

def doLogPlusone(mylist):
    for i in mylist:
        if i > 0 :
            h = (1+ log10(i))
            print(h)

if __name__ ==  "__main__":
    doLogPlusone(v1)