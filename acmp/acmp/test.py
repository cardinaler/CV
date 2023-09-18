class figure:
    def __init__(self, x, y, color):
        self.x = x
        self.y = y
        self.color = color
    def hello(self):
        print("Hello. I am %s figure and my coordinates are (%d, %d) "% (self.color, self.x, self.y))

class desk:
    def __init__(self):
        self.cell = [0] * 9
        for i in range(9):
            self.cell[i] = [None] * 9
    def add(self, shape:figure):
        self.cell[shape.y][shape.x] = shape
    def show(self):
        for i in range(1, 9):
            for j in range(1, 9):
                if self.cell[i ][j] != None:
                    print("[%c]" % self.cell[i ][j].color[0], end = '')
                else:
                    print("[]", end = '')
                
            print()

            
D = desk()
D.add(figure(1,1,"black"))
D.add(figure(2,5, "white"))
D.cell[1][1].hello()
D.show()
