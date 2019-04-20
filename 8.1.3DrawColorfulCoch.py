import turtle
colorlist = ["red","orange","yellow","green","cyan","blue","purple"]
i=0

def koch(size, n):
    global i
    turtle.color(colorlist[i%7])
    if n==0:
        turtle.fd(size)
    else:
        for angle in [0,60,-120,60]:
            turtle.left(angle)
            koch(size/3,n-1)
    i=i+1


def main(startx,starty,size,level):
    turtle.setup(1000,800)
    turtle.speed(0)
    turtle.penup()
    turtle.goto(startx,starty)
    turtle.pendown()
    turtle.pensize(2)
    koch(size,level)
    turtle.right(120)
    koch(size,level)
    turtle.right(120)
    koch(size,level)
    turtle.right(120)
    turtle.hideturtle()

main(-200,80,200,3)
main(-300,140,400,4)
main(-400,200,600,5)
