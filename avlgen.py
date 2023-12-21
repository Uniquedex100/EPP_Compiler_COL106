import random as r

D = {}

mx = 1000000
tc = 100000

testcases = []
ans = []
i = 0

def pushOp(tI):
    testcases.append("1 " + tI + "\n")
    D[tI] = -1

def searchOp(tS):
    testcases.append("2 " + tS + "\n")
    ans.append(str(D[tS]) + "\n")

def remOp(tD):
    testcases.append("3 " + tD + "\n")
    del D[tD]

def assignOp(tA, aV):
    testcases.append("4 " + tA + " " + str(aV) + "\n")
    D[tA] = aV
    
def sizeOp():
    testcases.append("5\n")
    ans.append(str(len(D.keys())) + "\n")

def orderOp():
    s = ""
    for i in sorted(D.keys()):
        s = s + str(i) + " "
    s.rstrip(" ")
    s = s + "\n"
    ans.append(s)

while i < tc:
    toDo = r.randint(1,5)
    tI = str(r.randint(0, mx))
    if (toDo == 1) and (tI in D.keys()):
        toDo = r.randint(2, 5)
    if (toDo == 1):
        pushOp(tI)
    if (toDo == 2):
        if len(D.keys()) == 0: continue
        searchOp(r.choice(list(D.keys())))
    if (toDo == 3):
        if len(D.keys()) == 0: continue
        remOp(r.choice(list(D.keys())))
    if (toDo == 4):
        if len(D.keys()) == 0: continue
        assignOp(r.choice(list(D.keys())), r.randint(0, mx))
    if (toDo == 5):
        sizeOp()
    if (toDo == 1 or toDo == 3):
        orderOp()
    i += 1

testcases[-1] = testcases[-1][:-1]
ans[-1] = ans[-1][:-1]
with open("AroyTest/testcase_avl.txt", "w") as F:
    F.writelines(testcases)

with open("AroyTest/ans_avl.txt", "w") as F:
    F.writelines(ans)