.name "las"
.comment "just like zork but with long fork"


lfork %2048
sti r1,%4,%4
live %125
ld %0,r2
zjmp %-12
