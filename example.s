        .org 0x100

label:  addb %es:test(%bx, %si),%al     ; does not make any sense
 test :         movb $label, %bx        ; as well as this thing


        
; there were some empty lines to generate nothing

; also some empty line

.section text

.section data
variable:       .db     123
string:         .asciiz "Hello world!"
