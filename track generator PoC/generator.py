from PIL import Image, ImageDraw
from random import random

#generates new point between two other point
def midpoint(a,b, coef = 0.5, misplacement = 0):
    diffX = (b[0]-a[0])
    diffY = (b[1]-a[1])

    #displacement occurs in pendicular direction, thus swapped axes
    displacementX = (-diffY-(diffY/2))*misplacement
    displacementY = (diffX-(diffX/2))*misplacement
    

    return (a[0]+coef*diffX+displacementX, a[1]+coef*(diffY)+displacementY)

####################################################################
#casteljau
####################################################################

#used in deCasteljau, computes position of actual point
def reduce(points, coef= 0.5):
    newPoints = []

    count = len(points)

    if count == 1 :
        return points[0]

    curPoint = points[0]
    for nextPoint in points[1:]:
        newPoints.append( midpoint(curPoint,nextPoint, coef) )
        curPoint = nextPoint

    return reduce(newPoints,coef)
    

#computes polybeziers spline by divede and conquer strategy
def deCasteljau(points, steps = 30):
    newPoints = []

    count = len(points)
    
    step = 1.0 / steps
    for i in range(steps+1):
        pos = step * i
        newPoints.append( reduce(points, pos) )

    return newPoints

#end of function for casteljau
####################################################################


####################################################################
#catmull
####################################################################

def catmull(points, steps = 30):
    newPoints = []

#    points.insert(0,points[0])
#    points.append(points[-1])

    count = len(points)

    for i in range(0,count):
        p0 = points[i];
        p1 = points[(i+1)%count];
        p2 = points[(i+2)%count];
        p3 = points[(i+3)%count];

        step = 1.0 / steps
        for i in range(steps):
            pos = step * i
            newPoints.append( spline_4p( pos, p0, p1, p2, p3 ) )
            
    return newPoints
    
#from http://pastebin.com/GzqNKW8Q
def spline_4p( t, p_1, p0, p1, p2 ):
    c1 = t*((2-t)*t - 1)
    c2 = (t*t*(3*t - 5) + 2)
    c3 = t*((4 - 3*t)*t + 1)
    c4 = (t-1)*t*t

    x = ( c1 * p_1[0] + c2 * p0[0] + c3 * p1[0] + c4 * p2[0] ) / 2
    y = ( c1 * p_1[1] + c2 * p0[1] + c3 * p1[1] + c4 * p2[1] ) / 2
    
    return (x,y)

#end of function for catmull
####################################################################


#splits lines into 2 with random misplacement
def fragment(points):
    newPoints = []

    curPoint = points[0]
    for nextPoint in points[1:]:
        newPoints.append(curPoint)

        #optionaly split
        coef = 0.5+(0.1-random()*0.2)
        misplacement = random()*0.2
        
        newPoints.append( midpoint(curPoint,nextPoint, coef,  misplacement) )
        curPoint = nextPoint
    #add last point
    newPoints.append(curPoint)

    return newPoints

#this is bridge
def drawLines(draw, point, color = 128, width=1):
    for i in range(len(point)-1):
        draw.line(point[i] + point[i+1], fill=color, width=width)

##### main code

#infinite track?
        
for x in range(10):
    im = Image.new("L", (500,500), 255)
    draw = ImageDraw.Draw(im)

    #box
    #toDraw=[ (50,50),(450,50),(450,450),(50,450),(50,50) ]

    #zigzag
    toDraw=[ (50,50),(450,50),(300,250),(150,300),(400,270),(450,450),(50,450) ]

    # deCasteljau / catmull
    function = deCasteljau

    #control line
    drawLines(draw, toDraw, color = 230, width=1)
    #processed line
    drawLines(draw, function(toDraw), color = 220, width=2)

    #make new fragments
    fragmentedDraw = fragment( fragment(toDraw) )
    #draw fragmented control line
    drawLines(draw, fragmentedDraw, color = 200, width=5)

    #processed fragmented line
    drawLines(draw, function(fragmentedDraw), color = 0, width=3)

    del draw

    im.save("out"+str(x)+".png")
