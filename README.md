# lisp
A simple lisp interpreter implementation in C.
About lisp: https://en.wikipedia.org/wiki/Lisp_(programming_language)

## Syntax
### Declaring variables
```lisp
(define x 10)
```

### Declaring function
```lisp
(define sqr        
	(lambda (x)     
		(* x x))) 
    
(define sos     
	(lambda (x y)  
		(+ (sqr x) (sqr y))))
 ```
    
### Function calling
```lisp
(sos 3 4)
```
Output: - 25

Here
sqr - square  </br>
sos - sum of squares

## Build
run command: - (needs gcc compilier and make tool)
```
make
```

## Start interpreter
on mac/linux - .\lisp.o </br>
on windows   - ./lisp.o
