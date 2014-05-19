#Exercise no. 2

##6

###a
´5 * ((3 \alpha),(4 + \beta),(\gamma)) = ((15 \alpha),(20 + 5 \beta),(5 \gamma))´

###b
´((3 \alpha),(4 + \beta),(\gamma)) + ((2 \beta),(4x),(\gamma^2)) = ((3 \alpha + 2 \beta ),(4 + \beta + 4x),(\gamma + \gamma^2))´

###c
´((3 \alpha),(4 + \beta),(\gamma)) - ((2 \alpha),(3),(6\alpha)) = ((\alpha),(\beta + 1),(\gamma - 6\alpha))´

###d
´|((3),(4),(5))| = sqrt(3^2 + 4^2 +5^2) = sqrt(9 + 16 + 25) = sqrt(50) = sqrt(2) * 5´

###e
norm´( ((3),(4),(5)) ) =  1 / |((3),(4),(5))| * ((3),(4),(5)) = 1/(5 sqrt(2))  ((3),(4),(5))´ 

###f
´<((3),(4),(5)),((3),(4),(5))> = 3 \* 2 + 4 \* 4 + 5 \* 6 = 6 + 16 + 30 = 52 ´

###g
´alpha = cos^-1( (<((3),(4),(5)),((3),(4),(5))>) / ( ((3),(4),(5)) * ((3),(4),(5)) ) ) =  cos^-1(52 / (sqrt(50)  sqrt(56))) = 10,67 °´

###h
´((3),(2),(5)) Xx ((1),(1),(8)) = ((2 \* 8 - 5 \* 1 ), (5 \* 1 - 3 \* 8), ( \3 * 1 - 2 \* 1)) = ((11), (-19), (1))´

##7

###a

######2 Richtungsvekotre der Ebene berechnen
´vec(a) = vec(P_1P_2) = ((0),(0),(5)) - ((5),(0),(0)) = ((-5),(0),(5))´

´vec(b) = vec(P_1P_3) = ((10),(0),(5)) - ((5),(0),(0)) = ((5),(0),(5))´ 
######Normalvektor
´vec(n) = vec(a) Xx vec(b) = ((-5),(0),(5)) Xx ((5),(0),(5)) = ((0),(50),(0))´
######Da der Vektor ein Richtungsvektor ist, kann man in normalisiert aufschreiben
´((0),(50),(0)) => ( (0),(1),(0) )´

###b
Da in allen drei Vektoren die y-Koordinate 0 ist kann man die Rechnung vereinfachen in den die Punkte nur als zwei dimensional betrachtet. Die Punkte wären dann: (5,0), (0,5) und (10,5).
Nach Laplacescher Entwicklungssatz ergibt sich:
´area(P_1,P_2,P_3) = 1/2 \* | (0 - 5) \* ( 5 - 0) - ( 10 - 5) \* ( 5 - 0 ) | = 1/2 | -25 -25 | = 25´
##8
###a
´a = ((6,5,3,4),(1,8,2,2),(4,9,3,2),(4,9,7,1)) \* ((4),(2),(3),(1)) = ((6 \* 4+5\*2+3\*3+4\*1),(1\*4+8\*2+2\*3+2\*1),(4\*4+9\*2+3\*3+2\*1),(4\*4+9\*2+7\*3+1\*1)) = ((47),(28),(45),(56))´ 

´b = ((2,0,0,0),(0,1,0,0),(0,0,3,0),(0,0,0,1)) \* ((x),(y),(z),(1)) = ((2x),(y),(3z),(1))´ 

´c = ((alpha,0,0,1),(0,0,beta,0),(gamma,0,1,delta),(0,zeta,0,eta)) \* ((x),(y),(z),(1)) = ((alpha \*x + 1),(beta \* z),(gamma \* x + z + \delta ),(zeta \* beta + eta))´
###b
´D \* E = ((1,5,3,4),(1,3,2,2),(4,5,-3,2),(4,2,7,1)) \* ((2,3,5,1),(2,1,4,2),(3,4,3,3),(1,3,0,1)) ´

´= ((2-10+9+4,3+5+12-12,5+20+9-0,1+10+0-4),(2-6+6-2,3+3+8+6,5+12+6+0,1+6+6+2),(8-10-9-2,12+5-12+6,20-20-9,4+10-9+2),(8-4+21-1,12+2+28+3,20+8+21,4+4+21+1)) ´

´= ((5,8,34,16),(0,20,23,15),(-13,11,31,7),(24,45,49,30))´ 

´E \* D =  ((2,3,5,1),(2,1,4,2),(3,4,3,3),(1,3,0,1)) \* ((1,5,3,4),(1,3,2,2),(4,5,-3,2),(4,2,7,1))´

´= ((2+3+20+4,10+9+25+2,6+6-15+7,-8+6+10+1),(-2+1+16+8,-10+3+20+4,-6+2-12+14,8+2+8+2),(3+4+12+12,15+12+15+6,9+8-9+21,-12+8+6+3),(-1+3-0+4,-5+9+10+2,-3+6+0+7,4+5+0+1)) ´

´= ((29,46,4,9),(23,17,-2,20),(31,48,29,5),(6,6,10,11))´

###c
´F^T=((6,5,3),(1,8,2),(4,9,7)) = ((6,1,4),(5,8,9),(3,2,7))´

###d
´det(G)=det( ((6,5),(1,8)) ) = 6 \*8 - 5 * 1 = 43´

´det(H)=det( ((2,3,5),(-1,4,2),(3,-2,2)) ) 
= 3 det( ((1,3),(-2,-5)) ) - 2 det( ((1,3),(-3,-5)) + 6 det( ((1,1),(-3,-2)) ) ´ 

´= 3 \* (-5+6) - 2 \* (-5+9) + 6 \* (-2+3) = 3 \* 1 - 2 \*  4 - 6 \* 1 = 3-8+6 = 1´

´det(J) = det( ((2,-3,1,4),(1,3,-2,2),(3,2,3,-3),(4,1,2,2)) )´

´= 2 det( ((3,-2,2),(2,3,-3),(1,2,2)) ) - det( ((-3,1,4),(2,3,-3),(1,2,2)) ) + 3 det( ((-3,1,4),(3,-2,2),(1,2,2)) ) - 4 det( ((-3,1,4),(3,-2,2),(2,3,-3)) )´

´= 2 \* 52 - (-39) + 3 \* 52 - 4 \* 65 = 39

###e

| K        | E        |  |
| :-------------: |:-------------:| :-----|
| ´((2,3),(-1,4))´ | ´((1,0),(0,1))´ | Zeilen vertauschen und dann zweite Zeile mal -1 |
| ´((1,-4),(2,3))´ | ´((0,-1),(1,0))´ | erste Zeile mal -2; die Addition als neue zweite Zeile | 
| ´((1,-4),(0,11))´ | ´((0,-1),(1,2))´ | zweite Zeile durch 11 |
| ´((1,-4),(0,1))´ | ´((0,-1),(1/11,2/11))´ | die erste Zeile mal 4; die Additon als neue erste Zeile
| ´((1,0),(0,1))´ | ´((4/11,-1/11),(1/11,2/11))´ | die Matrix die nun bei E steht ist die inverse Matrix von K |
´K^-1 = ((4/11,-1/11),(1/11,2/11))´

| L        | E        |  |
| :-------------: |:-------------:| :-----|
| ´((3,2,6),(1,1,3),(-3,-2,-5))´ | ´((1,0,0),(0,1,0),(0,0,1))´ | Zeilen 1 und 2 vertauschen |
| ´((1,1,3),(3,2,6),(-3,-2,-5))´ | ´((0,1,0),(1,0,0),(0,0,1))´ | Zeilen 1 (mal -2) und 2 werden addiert und die neue zweite Zeile; Zeilen 1 ( mal 2 ) und 2 werden addiert und die neue dritte Zeile; |
 |´((1,1,3),(0,-1,-3),(0,1,4))´ | ´((0,1,0),(1,-3,0),(0,3,1))´ | Zeilen 2 mal -1; Zeilen 2 und 3 werden addiert und die neue dritte Zeile; |
 |´((1,1,3),(0,1,3),(0,0,1))´ | ´((0,1,0),(-1,3,0),(1,0,1))´ | Zeilen 1 und 2 (mal -1) werden addiert und die neue erste Zeile; Zeilen 2 und 3 (mal -3) werden addiert und die neue dritte Zeile; |
 | ´((1,0,0),(0,1,0),(0,0,1))´ | ´((1,-2,0),(-4,3,-3),(1,0,1))´ | die Matrix die nun bei E steht ist die inverse Matrix von L |
´L^-1 = ((1,-2,0),(-4,3,-3),(1,0,1))´


| M        | E        |  |
| :-------------: |:-------------:| 
| ´((2,-1,3,4),(1,-2,0,2),(4,-1,3,2),(0,1,2,1))´ | ´((1,0,0,0),(0,1,0,0),(0,0,1,0),(0,0,0,1))´ | 
| ´((1,-2,0,2),(0,-1,3,4),(0,-1,3,2),(0,1,2,1))´ | ´((0,1,0,0),(0,1,0,3),(0,-2,1,0),(0,2/3,0,1))´ | 
| ´((1,-2,0,2),(0,-1,3,4),(0,0,3,2),(0,0,4,2))´ | ´((0,1,0,0),(0,1,4/3,3),(0,-2,1,-7/3),(0,2/3,11/6,1))´ | 
| ´((1,-2,0,2),(0,-1,3,4),(0,0,1,2/3),(0,0,0,1))´ | ´((-2,-1,-5,11),(3,1,7/3,-13),(-3,-1/2,-3,5/2),(-2,0,-5/3,4/3))´ | 
| ´((1,0,0,0),(0,1,0,0),(0,0,1,0),(0,0,0,1))´ | ´((-2,-1/2,-5/3,11/6),(3,1/2,7/3,-13/6),(-3,-1/2,-3,5/2),(-2,0,-5/3,4/3))´ | 

´J^-1 = ((-2,-1/2,-5/3,11/6),(3,1/2,7/3,-13/6),(-3,-1/2,-3,5/2),(-2,0,-5/3,4/3))´


###9

####a
´X_Q = u \* P1_x + v \* P2_x + w \* P3_x´
´Y_Q = u \* P1_y + v \* P2_y + w \* P3_y´

da ´u+v+w = 1´ folgt ´w = 1-u-v´

´X_Q = u \* (P3_x - P1_x) + v \* (P3_x - P2_x) + P3_x´
´Y_Q = u \* (P3_y - P1_y) + v \* (P3_y - P2_y) + P3_y´
´Q= u \* ((P3_x - P1_x),(P3_y - P1_y)) + v \* ((P3_x - P2_x),(P3_y - P2_y)) + P_3´
´Q= ((P3_x - P1_x, P3_x - P2_x),(P3_y - P1_y, P3_y - P2_y)) \* ((u),(v)) + P_3´
´vec(QP_3) = ((P3_x - P1_x, P3_x - P2_x),(P3_y - P1_y, P3_y - P2_y)) \* ((u),(v))´
´((u),(v)) = ((P3_x - P1_x, P3_x - P2_x),(P3_y - P1_y, P3_y - P2_y))^-1 \* vec(QP_3)´

###### Werte einsetzen

´A = ((P3_x - P1_x, P3_x - P2_x),(P3_y - P1_y, P3_y - P2_y)) = ((1-4,7-4),(1-5,2-5)) = ((-3,3),(-4,-3))´

´b = vec(QP_3) = ((3.5),(2.5)) - ((4),(5)) = ((-0.5),(-2.5))´

| A        | E        |  |
| :-------------: |:-------------:| :-----|
| ´((-3,3),(-4,3))´ | ´((1,0),(0,1))´ | erste Zeile durch -3 |
| ´((1,-1),(-4,-3))´ | ´((-1/3,0),(0,1))´ | erste Zeile (mal 4) und zweite Zeile addiert sind neue Zeile 2 |
| ´((1,-1),(0,-7))´ | ´((-1/3,0),(-4/3,1))´ | zweite Zeile durch -7 |
| ´((1,-1),(0,1))´ | ´((-1/3,0),(4/21,-1/7))´ | erste Zeile und zweite Zeile addiert sind neue Zeile 1 |
| ´((1,0),(0,1))´ | ´((-1/7,1/2),(4/21,-1/7))´ | DIe Matrix bei E ist die inverse Matrix von A |
´A^-1 = ((-1/7,1/2),(4/21,-1/7))´
´((u),(v)) = ((-1/7,1/2),(4/21,-1/7)) \* ((-0.5),(-2.5)) = ((1/14+5/14),(-2/21+5/14)) = ((6/14),(11/42))´

´u = 6/14´

´v = 11/42´

´w = 1 - 18/42 - 11/42 = 13/42´

´(6/14, 11/42, 13/42)´

####b
**Nach Laplacschen Bildungssatz gilt**

´area(Delta(P\_1,P\_2,P\_3)) = 1/2 det(A)´

**Die det(A) lässt sich aus Aufgabeteil auch darstellen als:**

´det(A) = ((x_Q-P3_x)(P2_y-P3_y)-(y_Q-P3_y)(P2_x-P3_x))/u´ 

**bei genauerer Betrachtung erkennt man, dass sich dies auch so darstellen lässt:**

´det(A) = det( ((x_Q-P3_x,P2_y-P3_y),(y_Q-P3_y,P2_x-P3_x)) )/u´ 

´<=> det(vec(P_3P_1),vec(P_3P_2)) = det(vec(P_3Q),vec(P_3P_2))/u´

´<=> area(Delta(P\_1,P\_2,P\_3)) = area(Delta(Q,P\_2,P\_3))/u´

´<=> area(Delta(P\_1,P\_2,P\_3)) \* u = area(Delta(Q,P\_2,P\_3))´

**u lässt sich (aus Aufgabeteil a) darstellen als**´ |((1,0),(0,0)) \* A^-1 \* b |;´**Mit der Matrix gewinnen wir den oberen Wert es Vektores, welcher beim Betrag dann allein ist** ´area(Delta(P\_1,P\_2,P\_3))´ **wissen wir von oben**

´=> area(Delta(Q,P\_2,P\_3)) = |((1,0),(0,0)) \* A^-1 \* b | \* 1/2 det(A)´

**analog dazu ist:**

´=> area(Delta(Q,P\_1,P\_3)) = |((0,1),(0,0)) \* A^-1 \* b | \* 1/2 det(A)´

**und**

´=> area(Delta(Q,P\_1,P\_2)) = (1 - |((0,1),(0,0)) \* A^-1 \* b |  - |((1,0),(0,0)) \* A^-1 \* b | )\* 1/2 det(A)´

####c

**Aus Aufgabeteil b** ´area(Delta(P\_1,P\_2,P\_3)) \* u = area(Delta(Q,P\_2,P\_3))´ ** ergeben sich dann folgende Verhältnisse**

´u=(area(Delta(Q,P\_2,P\_3)))/(area(Delta(P\_1,P\_2,P\_3)))´

´v=(area(Delta(Q,P\_1,P\_3)))/(area(Delta(P\_1,P\_2,P\_3)))´

´w=(area(Delta(Q,P\_2,P\_1)))/(area(Delta(P\_1,P\_2,P\_3)))´

###10

####V1-V4 beweisen, dass es eine abelische Gruppe ist. S1 - S4 garantieren die saubere Multiplikation mit einem Skalar

#####V1 Assozativ
´((f+g)+h)(x) = (g+(f+h)(x) da (f(x) + g(x)) + h(x) = g(x) + (f(x) + h(x))´ aus (1)

#####V2 Existenz eines neutralen Elements bezüglich Addtion
wenn ´g(x)=0´ dann ist g das neutralle Element für alle ´f(x)=f(x)+g(x)´

#####V3 Existens eines inversen Elements
´f(x)^-1 = -f(x)´

#####V4 Kommuntativ
´(f+g)(x) = (g+f)(x) da f(x) + g(x) = g(x) + f(x)´ aus (1)

#####S1 Distributiv mit einem Skalar
´(lambda(f+g)(x)) = lambda (f+g)(x) = lambda f (x) + lambda g (x)´ aus (1) & (2)

#####S2 Skalar distributiv mit Element des Vektorraums
´((lambda + eta) f(x)) = (lambda + eta) (f)(x) = lambda f(x) + eta f(x)´ aus (1) & (2)

#####S3 Assoziativ mit einem Skalar

#####S4 Existenz eines neutralen Elements bezüglich Multiplikation mit Skalar


