class Square:
    ranks = '12345678'
    files = 'abcdefgh'

    def __init__(self, name):
        if isinstance(name, int):
            self.sq = name
        elif isinstance(name, str):
            file = self.files.index(name[0])
            rank = self.ranks.index(name[1])
            self.sq = self.make_sq(file, rank)

    def make_sq(self, file, rank):
        if file in range(8) and rank in range(8):
            return int(8 * file + rank)
        raise ValueError

    def rank(self):
        return self.sq % 8

    def file(self):
        return int(self.sq / 8)

    def number(self):
        return self.sq

    def sq_name(self):
        return '{f}{r}'.format(f=self.files[self.file()], r=self.ranks[self.rank()])

    def offset(self, file_delta=0, rank_delta=0):
        try:
            sq = self.make_sq(file=self.file()+file_delta,
                              rank=self.rank()+rank_delta)
            return Square(sq)
        except ValueError:
            pass
        return None

    def __repr__(self):
        return self.sq_name()



def find(from_square: Square, to_square: Square, depth: int):
    """Найти траектории с поля from на to за depth шагов."""
    class Trajectory:
        def __init__(self, sample=None) -> None:
            self.squares = []  # Поля траектории
            if sample is not None:
                self.squares = [x for x in sample.squares]
        def last_square(self):
            return self.squares[-1]
        def push(self, square):
            self.squares.append(square)
        def __repr__(self):
            return str([square for square in self.squares])

    def possible_moves(square):
        """Список полей, на которые можно попасть из SQ за один ход."""
        res = []
        for rank_delta in [-2, -1, +1, +2]:
            for offset in [-1, +1]:
                file_delta = offset * (3 - abs(rank_delta))
                square_to = square.offset(file_delta, rank_delta)
                if square_to is not None:
                    res.append(square_to)
        return res

    def walk(trajectories, steps_to_go):
        if steps_to_go == 0:
            def non_repeating(traj):
                return len(traj.squares) == len(set([sq.number() for sq in traj.squares]))
            return [traj for traj in trajectories if traj.last_square().number() == to_square.number() and non_repeating(traj)]
        next_trajectories = []
        for traj in trajectories:
            square = traj.last_square()
            for next in possible_moves(square):
                # Создаем траекторию traj + next
                sequel = Trajectory(sample=traj)
                sequel.push(next)
                next_trajectories.append(sequel)
        return walk(next_trajectories, steps_to_go-1)

    initial_traj = Trajectory()
    initial_traj.push(from_square)
    return walk([initial_traj], depth)


print(len(find(Square('a1'), Square('h8'), 6)))


for f in 'abcdefgh':
    for r in range(1, 9, 1):
        sq = Square('{f}{r}'.format(f=f, r=r))
        num = sq.number()
        sq2 = Square(num)
        assert(num == sq2.number())
exit(0)

sq = Square('a1')
for delta in range(8):
    sq2 = sq.offset(file_delta=delta)
    if sq2 is not None:
        print(delta, sq2.rank(), sq2.file(), sq2)
