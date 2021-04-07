import random

#глобальные переменные neurons1 neurons2 neurons3

class Deck():
    deck = [None] * 32
    def __init__(self):
        for i in range(1, 5):
            for j in range(7, 15):
                self.deck[(i - 1) * 8 + (j - 6) - 1] = Card(i, j)
    def get(self, i):
        try:
            answer = {
                11: "Валет",
                12: "Дама",
                13: "Король",
                14: "Туз",
            }[self.deck[i].Num]
        except:
            answer = str(self.deck[i].Num)
        answer += " "
        answer += {
            1: "червы",
            2: "бубны",
            3: "крести",
            4: "пики",
        }[self.deck[i].Mastb]
        return answer

class Card():
    def __init__(self, i, j):
        self.Mastb = i
        self.Num   = j
 
def pravila1(a, b, c, n): #если 1 ходит первым
    s = int
    s = 0
    for i in range(1, 33):
        if (a[i] == 1):
            n[1] = i
            neurons1[i] = 0
            break
    for i in range(1, 33):
        if (mast(i) == mast(n[1])) & (b[i] == 1):
            n[2] = i
            neurons2[i] = 0
            break
        s = s+1
    if s == 32:
        for i in range(1, 33):
            if (b[i] == 1):
                n[2] = i
                neurons2[i] = 0
                break
    s = 0
    for i in range(1, 33):
        if (mast(i) == mast(n[1])) & (c[i] == 1):
            n[3] = i
            neurons3[i] = 0
            break
        s = s+1
    if s == 32:
        for i in range(1, 33):
            if (c[i] == 1):
                n[3] = i
                neurons3[i] = 0
                break
    return n
        
def pravila2(a, b, c, n): #если 2 ходит первым
    s = int
    s = 0
    for i in range(1, 33):
        if (b[i] == 1):
            n[2] = i
            neurons2[i] = 0
            break
    for i in range(1, 33):
        if (mast(i) == mast(n[2])) & (c[i] == 1):
            n[3] = i
            neurons3[i] = 0
            break
        s = s+1
    if s == 32:
        for i in range(1, 33):
            if (c[i] == 1):
                n[3] = i
                neurons3[i] = 0
                break
    s = 0
    for i in range(1, 33):
        if (mast(i) == mast(n[2])) & (a[i] == 1):
            n[1] = i
            neurons1[i] = 0
            break
        s = s+1
    if s == 32:
        for i in range(1, 33):
            if (a[i] == 1):
                n[1] = i
                neurons1[i] = 0
                break
    return n
        
def pravila3(a, b, c, n): #если 3 ходит первым
    s = int
    s = 0
    for i in range(1, 33):
        if (c[i] == 1):
            n[3] = i
            neurons3[i] = 0
            break
    for i in range(1, 33):
        if (mast(i) == mast(n[3])) & (a[i] == 1):
            n[1] = i
            neurons1[i] = 0
            break
        s = s+1
    if s == 32:
        for i in range(1, 33):
            if (a[i] == 1):
                n[1] = i
                neurons1[i] = 0
                break
    s = 0
    for i in range(1, 33):
        if (mast(i) == mast(n[3])) & (b[i] == 1):
            n[2] = i
            neurons2[i] = 0
            break
        s = s+1
    if s == 32:
        for i in range(1, 33):
            if (b[i] == 1):
                n[2] = i
                neurons2[i] = 0
                break
    return n

def sravnit1(a, b, c, s): #сравнивает карты 1
    if (mast(b) == mast(a)) & (mast(c) == mast(a)):
        if (a > b) & (a > c):
            s[1] = s[1]+1
            s[4] = 1
        if (b > a) & (b > c):
            s[2] = s[2]+1
            s[4] = 2
        if (c > a) & (c > b):
            s[3] = s[3]+1
            s[4] = 3
    if (mast(b) != mast(a)) & (mast(c) == mast(a)):
        if (a > c):
            s[1] = s[1]+1
            s[4] = 1
        else:
            s[3] = s[3]+1
            s[4] = 3
    if (mast(b) == mast(a)) & (mast(c) != mast(a)):
        if (a > b):
            s[1] = s[1]+1
            s[4] = 1
        else:
            s[2] = s[2]+1
            s[4] = 2 
    if (mast(b) != mast(a)) & (mast(c) != mast(a)):
        s[1] = s[1]+1
        s[4] = 1
    print('\n')
    return s

def sravnit2(a, b, c, s): #сравнивает карты 2
    if (mast(a) == mast(b)) & (mast(c) == mast(b)):
        if (a > b) & (a > c):
            s[1] = s[1]+1
            s[4] = 1
        if (b > a) & (b > c):
            s[2] = s[2]+1
            s[4] = 2
        if (c > a) & (c > b):
            s[3] = s[3]+1
            s[4] = 3
    if (mast(a) != mast(b)) & (mast(c) == mast(b)):
        if (b > c):
            s[2] = s[2]+1
            s[4] = 2
        else:
            s[3] = s[3]+1
            s[4] = 3
    if (mast(a) == mast(b)) & (mast(c) != mast(b)):
        if (a > b):
            s[1] = s[1]+1
            s[4] = 1
        else:
            s[2] = s[2]+1
            s[4] = 2
    if (mast(a) != mast(b)) & (mast(c) != mast(b)):
        s[2] = s[2]+1
        s[4] = 2
    print('\n')
    return s
    
def sravnit3(a, b, c, s): #сравнивает карты 3
    if (mast(b) == mast(c)) & (mast(a) == mast(c)):
        if (a > b) & (a > c):
            s[1] = s[1]+1
            s[4] = 1
        if (b > a) & (b > c):
            s[2] = s[2]+1
            s[4] = 2
        if (c > a) & (c > b):
            s[3] = s[3]+1
            s[4] = 3
    if (mast(b) != mast(c)) & (mast(a) == mast(c)):
        if (a > c):
            s[1] = s[1]+1
            s[4] = 1
        else:
            s[3] = s[3]+1
            s[4] = 3
    if (mast(b) == mast(c)) & (mast(a) != mast(c)):
        if (c > b):
            s[3] = s[3]+1
            s[4] = 3
        else:
            s[2] = s[2]+1
            s[4] = 2
    if (mast(b) != mast(c)) & (mast(a) != mast(c)):
        s[3] = s[3]+1
        s[4] = 3
    print('\n')
    return s
        
def mast(a):
    if (a>=1) & (a<=8):
        return(1)
    if (a>=9) & (a<=16):
        return(2)
    if (a>=17) & (a<=24):
        return(3)
    if (a>=25) & (a<=32):
        return(4)                        

def kinut(a, b, c, s): #что кинуть(правила)
    n = [None] * 4
    for i in range(1, 4):
        n[i] = 0
    if (s[4] == 1):
        n = pravila1(a, b, c, n)
        print(n)
        s = sravnit1(n[1], n[2], n[3], s)
        return s
    if (s[4] == 2):
        n = pravila2(a, b, c, n)
        print(n)
        s = sravnit2(n[1], n[2], n[3], s)
        return s
    if (s[4] == 3):
        n = pravila3(a, b, c, n)
        print(n)
        s = sravnit3(n[1], n[2], n[3], s)
        return s
    
if __name__ == '__main__':
    deck = Deck()
    otvet = [None] * 5
    for i in range(1, 4):
        otvet[i] = 0
    otvet[4] = random.randint(1, 3) #чей ход
    s = 1
    t = [None] * 33
    l = list(range(1, 33))
    random.shuffle(l)
    for j in l:
        t[s] = j
        s = s+1
    hand1 = [None] * 11
    hand2 = [None] * 11
    hand3 = [None] * 11
    for i in range(1, 11):
        hand1[i] = t[i]
        print(hand1[i], end='.\n')
        card = deck.get(hand1[i]-1)
        print(card, end='.\n')
    global neurons1
    neurons1 = [None] * 33
    for i in range(1, 11):
         for j in range(1, 33):
             if (j == hand1[i]):
                 neurons1[j] = 1
             if (j != hand1[i]) & (neurons1[j] != 1):
                 neurons1[j] = 0
    print(neurons1)
    for i in range(11, 21):
        hand2[i-10] = t[i]
    global neurons2
    neurons2 = [None] * 33
    for i in range(1, 11):
         for j in range(1, 33):
             if (j == hand2[i]):
                 neurons2[j] = 1
             if (j != hand2[i]) & (neurons2[j] != 1):
                 neurons2[j] = 0
    for i in range(21, 31):
        hand3[i-20] = t[i]
    global neurons3
    neurons3 = [None] * 33
    for i in range(1, 11):
         for j in range(1, 33):
             if (j == hand3[i]):
                 neurons3[j] = 1
             if (j != hand3[i]) & (neurons3[j] != 1):
                 neurons3[j] = 0
    for i in range(1, 11):
        print (otvet)
        otvet = kinut (neurons1, neurons2, neurons3, otvet)
    print('Ответ', otvet[1], otvet[2], otvet[3])