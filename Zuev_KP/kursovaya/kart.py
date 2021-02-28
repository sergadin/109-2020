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
 
    
 
    
 
    
 
def mast(a):
    for i in range(1, 33):
        if (a[i] == 1):
            if (i>=1) & (i<=8):
                return(1);
            if (i>=9) & (i<=16):
                return(2);
            if (i>=17) & (i<=24):
                return(3);
            if (i>=25) & (i<=32):
                return(4);
        
        
        
#def kinut(a): #что кинуть(правила)
    



#def step(a): #чей ход и кто следующий
            
        
        
def sravnit(a, b, c, m): #сравнивает карты 
    s1 = 0;
    s2 = 0;
    s3 = 0;
    if (mast(a) == m) & (mast(b) == m) & (mast(b) == m):    
        if (a > b) & (a > c):
            s1 = s1+1;
        if (b > a) & (b > c):
            s2 = s2+1;
        if (c > a) & (c > b):
            s3 = s3+1;
    
    if (s1 > s2) & (s1 > s3):
        print(s1);
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
    neurons2 = [None] * 33;
    for i in range(1, 11):
         for j in range(1, 33):
             if (j == hand2[i]):
                 neurons2[j] = 1;
             if (j != hand2[i]) & (neurons2[j] != 1):
                 neurons2[j] = 0;
    for i in range(21, 31):
        hand3[i-20] = t[i];
    neurons3 = [None] * 33;
    for i in range(1, 11):
         for j in range(1, 33):
             if (j == hand3[i]):
                 neurons3[j] = 1;
             if (j != hand3[i]) & (neurons3[j] != 1):
                 neurons3[j] = 0;
    
    sravnit(neurons1, neurons2, neurons3, 1);
    