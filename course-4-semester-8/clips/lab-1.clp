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
	(slot name)
	(slot mass)
	(slot stellar_type)
)

(assert
    (Star (name Sun) (mass 1) (stellar_type G))
    (Star (name Alpha_Centauri) (mass 1.2) (stellar_type G))
    (Star (name Polar) (mass 2.2) (stellar_type B))
    (Star (name Betelgeuse) (mass 22.5) (stellar_type M))
    (Star (name Arcturus) (mass 1) (stellar_type K))
    (Star (name Procyon) (mass 0.6) (stellar_type F))
    (Star (name Sirius) (mass 0.7) (stellar_type A))
    (Star (name Rigel) (mass 0.5) (stellar_type B))
    (Star (name 10_Lacerta) (mass 0.4) (stellar_type O))
    (Star (name CY_Canis_Major) (mass 30) (stellar_type M))
)
	
(facts)

(exit)
; empty line at the end
