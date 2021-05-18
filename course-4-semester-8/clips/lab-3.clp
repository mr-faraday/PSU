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
    (Star (star_name Sun) (mass 1) (stellar_type G))
    (Star (star_name Alpha_Centauri) (mass 1.2) (stellar_type G))
    (Star (star_name Polar) (mass 2.2) (stellar_type B))
    (Star (star_name Betelgeuse) (mass 22.5) (stellar_type M))
    (Star (star_name Arcturus) (mass 1) (stellar_type K))
    (Star (star_name Procyon) (mass 0.6) (stellar_type F))
    (Star (star_name Sirius) (mass 0.7) (stellar_type A))
    (Star (star_name Rigel) (mass 0.5) (stellar_type B))
    (Star (star_name 10_Lacerta) (mass 0.4) (stellar_type O))
    (Star (star_name CY_Canis_Major) (mass 30) (stellar_type M))
    (Star (star_name Deneb) (mass 19.0) (stellar_type A))
)

(deffunction showStarsWithType (?type)
    (defrule show
        (Star (star_name ?name) (mass ?mass) (stellar_type ?s_type))
        (test (str-compare (?type ?s_type)))
        =>
        (printout t ?name "with mass" ?mass crlf)
    )

    (run)
)

(showStarsWithType M)

; (facts)

(exit)
; empty line at the end
