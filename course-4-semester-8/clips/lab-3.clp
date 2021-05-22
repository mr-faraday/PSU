; your code goes here

(defglobal
    ?*sun_mass* = (* 1.989 (** 10 30)) ; kg
    ?*gravity_constant* = (* 6.6742 (** 10 -11)) ; m^3 / kg * s^2
    ?*light_speed* = 299792458 ; m / s
)

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
    (Star (star_name VY_Canis_Major) (mass 30) (stellar_type M))
    (Star (star_name Deneb) (mass 19.0) (stellar_type A))
)


(deffunction calc-gravity-radius (?relative_mass) ; mass in kg
    (printout t (/ (* 2 ?relative_mass ?*sun_mass* ?*gravity_constant*) (** ?*light_speed* 2)))
)

(defgeneric print-mass)
(defmethod print-mass ( (?mass NUMBER (<= ?mass 0.3) ) )
    (printout t "very light")
)
(defmethod print-mass ( (?mass NUMBER (<= ?mass 0.7) ) )
    (printout t "light")
)
(defmethod print-mass ( (?mass NUMBER (<= ?mass 1.1) ) )
    (printout t "medium")
)
(defmethod print-mass ( (?mass NUMBER (<= ?mass 5) ) )
    (printout t "heavy")
)
(defmethod print-mass ( (?mass NUMBER (> ?mass 5)) )
    (printout t "huge")
)


(defrule print-vy-canis-major-gravity-radius
    (Star (star_name VY_Canis_Major) (mass ?mass))
    =>
    
    (printout t (calc-gravity-radius ?mass) crlf)
    (printout t (print-mass ?mass) crlf)
)

(run)

; (facts)

(exit)
; empty line at the end
