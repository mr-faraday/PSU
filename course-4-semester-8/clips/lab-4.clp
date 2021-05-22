; your code goes here

(deffunction ask-question (?question $?allowed-values)
    (printout t ?question)
    (bind ?answer (read))
    (if (lexemep ?answer)
    then
        (bind ?answer (lowcase ?answer)))
        (while (not (member ?answer ?allowed-values)) do
        (printout t ?question)
        (bind ?answer (read))
        (if (lexemep ?answer)
        then
            (bind ?answer (lowcase ?answer))))
            ?answer
)

(deffunction yes-or-no-p (?question)
    (bind ?response (ask-question ?question yes no у n))
    (if (or (eq ?response yes) (eq ?response y))
    then
        TRUE
    else
        FALSE
    )
)

(defrule askIsHumans
    (not (infiltration-species ?))
    (not (spaceship-malfunctioning ?))
    (not (transmiter ?))
    =>
    (bind ?species (ask-question "Is it humas or alien species (human/alien)?" human alien))
    (assert (infiltration-species ?species))
    (printout t crlf)

    (if (yes-or-no-p "Can spaceship fly (yes/no)?")
    then
        (assert (spaceship-malfunctioning working))
    else
        (assert (spaceship-malfunctioning oops))
    )
    (printout t crlf)

    (if (yes-or-no-p "Is transmiter working (yes/no)?")
    then
        (assert (transmiter working))
    else
        (assert (transmiter oops))
    )
    (printout t crlf)
)

(defrule mayday
    (transmiter working) =>
    (assert (action "Call a help"))
)

(defrule maybe-another-day
    (transmiter oops) =>
    (assert (action "Try to fix transmiter"))
)

(defrule escape
    (spaceship-malfunctioning working) =>
    (assert (action "Fly away from this s**t"))
)

(defrule noway
    (spaceship-malfunctioning oops) =>
    (assert (action "Try to fix engines"))
)

(defrule say-hello
    (infiltration-species alien) =>
    (assert (action "Say hello to your new friends and drink a cup of tea"))
)

(defrule anyway
    (infiltration-species human) =>
    (assert (action "Give a sigarete and talk about life"))
)

(defrule print-suggestions
    (action ?message)
    =>
    (printout t ?message crlf)
)

(printout t "SPACESHIP INFILTRATION EMERGENCY" crlf)

(run)

(exit)
; empty line at the end
