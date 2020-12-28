.name		"xor"
.comment	"xor"

ld	%1, r4
st	r4, :end

xor 12, %1, r2
aff r2
end:
