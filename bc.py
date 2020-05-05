#4 digits guess the digits
#for every right digit -> 1 Cow
#for every right digit at wrongs place -> Bull
#game loops until player guesses right number -> at the end it'll show amount guesses


import random

def cowBull_loop():
    ask= str(input("enter a four digit number: "))
    cow=0
    bullCow=0  #total number of digit guessed perfectly. right place + wrong place
    for i in range(0,4):
        if num[i]==ask[i]:
            cow+=1
    for i in num:
        if i in ask:
            bullCow +=1
    bull=bullCow-cow
    print("you have {} cow and {} bulls".format(cow,bull))
    return cow


if __name__=='__main__':
    num= str(random.randrange(1000,9999)) # for testing use str(2727)
    cow= 0
    count=0
    while cow !=4:
        count+=1
        cow = cowBull_loop()

