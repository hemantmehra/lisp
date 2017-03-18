(define sqr
	(lambda (x)
		(* x x)))

(define sos
	(lambda (x y)
		(+ (sqr x) (sqr y))))

(sqr 3)
(sqr 4)
(sos 3 4)