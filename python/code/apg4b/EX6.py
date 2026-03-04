A, op, B = input().split()
A = int(A)
B = int(B)

if op=='?' or op=='=' or op=='!':
    print("error")
else:
    if op=='+':
        print(A+B)
    elif op=='-':
        print(A-B)
    elif op=='*':
        print(A*B)
    else:
        if B==0:
            print("error")
        else:
            print(A//B)