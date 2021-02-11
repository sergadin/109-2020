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
 
if __name__ == '__main__':
    deck = Deck();
    hand = [None] * 11;
    for i in range(1, 11):
        t = int(input('Вы (введите число): '));
        card = deck.get(t-1);
        print(card, end='.\n');
        hand[i] = t;
    for i in range(1, 11):
        card = deck.get(hand[i]-1);
        print('Вы взяли карты', card, end='.\n');
    
    neurons = [[None] * 33] * 11;
    for i in range(1, 11):
         for j in range(1, 33):
             if j == hand[i]:
                 neurons[i][j] = 1;
             else:
                 neurons[i][j] = 0;
         print(neurons[i]);