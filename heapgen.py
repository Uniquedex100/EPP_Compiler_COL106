import heapq
import random as r

h = []
heapq.heapify(h)

mx = 1000000
tc = 100000

testcases = []
ans = []
i = 0

def pushOp(tI):
    testcases.append("1 " + str(tI) + "\n")
    heapq.heappush(h, tI)

def minOp():
    testcases.append("2\n")
    ans.append(str(heapq.nsmallest(1, h)[0]) + "\n")

def popOp():
    testcases.append("3\n")
    heapq.heappop(h)
    
while i < tc:
    tI = r.randint(0, mx)
    if tI in h:
        tD = r.randint(2,3)
    else:
        tD = r.randint(1,3)
    if (tD == 1):
        pushOp(tI)
    if (tD == 2):
        if len(h) == 0: continue
        minOp()
    if (tD == 3):
        if len(h) == 0: continue
        popOp()

    i += 1

while len(h) > 0:
    minOp()
    popOp()

with open("testcase.txt", "w") as F:
    F.writelines(testcases)

with open("ans.txt", "w") as F:
    F.writelines(ans)
