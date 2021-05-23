; your code goes here

(deffunction is-divides (?n ?divider)
    (if (eq (mod ?n ?divider) 0)
    then
        TRUE
    else
        FALSE
    )
)

(deffunction simple-dividing (?n)
	(bind ?printed 0)
	(bind ?i 1)
	(while (< ?printed ?n)
		(if (is-divides ?i 2)
        then
        	(if (is-divides ?i 3)
        	then (if (is-divides ?i 5)
	        	then
	        		(printout t ?i crlf)
	        		(bind ?printed (+ ?printed 1))
	        	)
        	)
    	)
    	
    	(bind ?i (+ ?i 1))
	)
)

(simple-dividing (read))

(exit)
; empty line at the end