import random

class Deck():
    deck = [None] * 32;
    def __init__(self):
        for i in range(1, 5):
            for j in range(7, 15):
                self.deck[(i - 1) * 8 + (j - 6) - 1] = Card(i, j);
    def get(self, i):
        try:
            answer = {
                11: "Валет",
                12: "Дама",
                13: "Король",
                14: "Туз",
            }[self.deck[i].Num];
        except:
            answer = str(self.deck[i].Num);
        answer += " ";
        answer += {
            1: "червы",
            2: "бубны",
            3: "крести",
            4: "пики",
        }[self.deck[i].Mastb];
        return answer;
class Card():
    def __init__(self, i, j):
        self.Mastb = i;
        self.Num   = j;
 
    
def pravila1(a, b, c, n1, n2, n3): #если 1 ходит первым
    s = int;
    s = 0;
    for i in range(1, 33):
        if (a[i] == 1):
            n1 = i;
            neurons1[i] = 0;
            break
    for i in range(1, 33):
        if (mast(i) == mast(n1)) & (b[i] == 1):
            n2 = i;
            neurons2[i] = 0;
            break
        s = s+1;
    if s == 32:
        for i in range(1, 33):
            if (b[i] == 1):
                n2 = i;
                neurons2[i] = 0;
                break
    s = 0;
    for i in range(1, 33):
        if (mast(i) == mast(n1)) & (c[i] == 1):
            n3 = i;
            neurons3[i] = 0;
            break
        s = s+1;
    if s == 32:
        for i in range(1, 33):
            if (c[i] == 1):
                n3 = i;
                neurons3[i] = 0;
                break
        
        
        
        

def pravila2(n1, n2, n3): #если 2 ходит первым
    print(n2)
    print(n3)
    if (n1 == n2) | (n1 == n3):
        print(n1)
        
        
        
        

def pravila3(n1, n2, n3): #если 3 ходит первым
    print(n3)
    if (n1 == n3) | (n1 != n3):
        print(n1)
    print(n2)
    
 
def mast(a):
    if (a>=1) & (a<=8):
        return(1);
    if (a>=9) & (a<=16):
        return(2);
    if (a>=17) & (a<=24):
        return(3);
    if (a>=25) & (a<=32):
        return(4);
        
        
        
def kinut(a, b, c): #что кинуть(правила)
    s = step(1);
    n1 = 0;
    n2 = 0;
    n3 = 0;
    if (s == 1):
        pravila1(a, b, c, n1, n2, n3);
        print(n1);
        print(n2);
        print(n3);
        sravnit1(n1, n2, n3);

def step(a): #чей ход и кто следующий
    s = random.randint(1, 3)
    s = 1;
    return s;
        
            
        
        
def sravnit1(a, b, c): #сравнивает карты 
    s1 = 0;
    s2 = 0;
    s3 = 0;
    if (mast(b) == mast(a)) & (mast(c) == mast(a)):
        if (a > b) & (a > c):
            s1 = s1+1;
        if (b > a) & (b > c):
            s2 = s2+1;
        if (c > a) & (c > b):
            s3 = s3+1;
    if (mast(b) != mast(a)) & (mast(c) == mast(a)):
        if (a > c):
            s1 = s1+1;
        else:
            s3 = s3+1;
    if (mast(b) == mast(a)) & (mast(c) != mast(a)):
        if (a > b):
            s1 = s1+1;
        else:
            s2 = s2+1;
    if (mast(b) != mast(a)) & (mast(c) != mast(a)):
        s1 = s1+1;
    
    if (s1 < s2) & (s1 < s3):
        print('');
    else:
        print('');
 
    
     
if __name__ == '__main__':
    deck = Deck();
    s = 1;
    t = [None] * 33;
    l = list(range(1, 33))
    random.shuffle(l)
    for j in l:
        t[s] = j;
        s = s+1;
    hand1 = [None] * 11;
    hand2 = [None] * 11;
    hand3 = [None] * 11;
    for i in range(1, 11):
        hand1[i] = t[i];
        print(hand1[i], end='.\n');
        card = deck.get(hand1[i]-1);
        print(card, end='.\n');
    global neurons1;
    neurons1 = [None] * 33;
    for i in range(1, 11):
         for j in range(1, 33):
             if (j == hand1[i]):
                 neurons1[j] = 1;
             if (j != hand1[i]) & (neurons1[j] != 1):
                 neurons1[j] = 0;
    print(neurons1);
    for i in range(11, 21):
        hand2[i-10] = t[i];
    global neurons2;
    neurons2 = [None] * 33;
    for i in range(1, 11):
         for j in range(1, 33):
             if (j == hand2[i]):
                 neurons2[j] = 1;
             if (j != hand2[i]) & (neurons2[j] != 1):
                 neurons2[j] = 0;
    for i in range(21, 31):
        hand3[i-20] = t[i];
    global neurons3;
    neurons3 = [None] * 33;
    for i in range(1, 11):
         for j in range(1, 33):
             if (j == hand3[i]):
                 neurons3[j] = 1;
             if (j != hand3[i]) & (neurons3[j] != 1):
                 neurons3[j] = 0;
    for i in range(1, 11):
        kinut (neurons1, neurons2, neurons3);