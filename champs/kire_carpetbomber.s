.name		"kire_carpetbomber"
.comment	"fine persian carpets!"

		ld %2863311530, r2#garbage value to bomb the core with
		ld %16, r3#incrementor; the size of jumps
		ld %16, r4
		fork %25

loop:	sti r1, %:live, %1
live:	live %0
		ld %0, r16
		zjmp %:live

bomber1:add r4, r3, r4
		sti r2, %:end, r4
		ld %0, r16
		zjmp %:bomber1
end:
