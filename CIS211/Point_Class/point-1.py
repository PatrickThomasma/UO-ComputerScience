'''Mini Project 1,
Patrick Thomasma
April 5th 2019'''

class Point:
    def __init__(self, u, v):
        self.x = u
        self.y = v

    def move(self, dx: int, dy: int):
        self.x = self.x + dx
        self.y = self.y + dy

    def __str__(self):
        return f"({self.x}, {self.y})"

    def __eq__(self: "Point",other: "Point") -> bool:
        return self.x == other.x and self.y == other.y


pt1 = Point(4, 5)
print(pt1)