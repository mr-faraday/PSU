; your code goes here

(deffacts initial-facts
	(light speed is 299792458 meters per second)
    (there are 9 planets in our solar system)
    (planets are sphere shape)
    (you can not move faster than light)
    (stars are hot)
    (gas gigants are huge)
    (space are enourmous)
	(humans native planet are Earth)
    (thre are not green people)
    (you cant breathe in a space)
)

(reset)

(deftemplate Star
	(slot star_name)
	(slot mass)
	(slot stellar_type)
)

(assert
    (Star (star_name Sun) (mass 1.0) (stellar_type G))
    (Star (star_name Alpha_Centauri) (mass 1.2) (stellar_type G))
    (Star (star_name Polar) (mass 2.2) (stellar_type B))
    (Star (star_name Betelgeuse) (mass 22.5) (stellar_type M))
    (Star (star_name Arcturus) (mass 1.0) (stellar_type K))
    (Star (star_name Procyon) (mass 0.6) (stellar_type F))
    (Star (star_name Sirius) (mass 0.7) (stellar_type A))
    (Star (star_name Rigel) (mass 0.5) (stellar_type B))
    (Star (star_name 10_Lacerta) (mass 0.4) (stellar_type O))
    (Star (star_name CY_Canis_Major) (mass 30.0) (stellar_type M))
    (Star (star_name Deneb) (mass 19.0) (stellar_type A))
)

; 1

(printout t "1:" crlf)
(defrule showHeavyStars 
    (Star (star_name ?name) (mass ?mass))
    (test (> ?mass 1))
    =>
    (printout t ?name crlf)
)

(run)
(printout t crlf)

; 2

(printout t "2:" crlf)
(defrule showLightWeightStars 
    (Star (star_name ?name) (mass ?mass))
    (test (<= ?mass 1))
    =>
    (printout t ?name crlf)
)

(run)
(printout t crlf)

; 3

(printout t "3:" crlf)
(defrule showVeryLigthOrHeavyStars 
    (Star (star_name ?name) (mass ?mass))
    (or (test (<= ?mass 0.5)) (test (>= ?mass 20)))
    =>
    (printout t ?name crlf)
)

(run)
(printout t crlf)

; 4

(printout t "4:" crlf)
(defrule showHeavyStarsWithMType
    (Star (star_name ?name) (mass ?mass) (stellar_type ?type))
    (and (test (str-compare ?type "M")) (test (>= ?mass 20)))
    =>
    (printout t ?name crlf)
)

(run)
(printout t crlf)

; 5

(printout t "5:" crlf)
(defrule showHeavyStarsWithMType
    (Star (star_name ?name) (mass ?mass) (stellar_type ?type))
    (and (test (str-compare ?type "M")) (test (>= ?mass 20)))
    =>
    (printout t ?name crlf)
)

(run)
(printout t crlf)

;6

(printout t "6:" crlf)
(defrule isStarsGTypeExists
    (exists (Star (stellar_type G)))
    =>
    (printout t "There are stars with G type" crlf)
)

(run)
(printout t crlf)

;7

(printout t "7:" crlf)
(defrule areThereExtreamlyLightStars
    (forall
        (mass ?mass)
        (not (test (< ?mass 0.3)))
    )
    =>
    (printout t "There are no extreamly light stars" crlf)
)

(run)
(printout t crlf)

; 8

(defrule createSnippet
    (logical (Star (star_name ?name) (stellar_type ?type)))
    =>
    (assert (There are star with name ?name and type ?type))
)

(run)

; 9

(defrule removeHevyStars
    ?f <- (Star (mass ?mass))
    (test (> ?mass 2))
    =>
    (retract (fact-index ?f))
)

(run)

; 10

(printout t "10:" crlf)
(defrule showStarsWithOType
    (Star (star_name ?name) (stellar_type O))
    =>
    (printout t ?name)
)

(run)
(printout t crlf)

; (facts)

(exit)
; empty line at the end
