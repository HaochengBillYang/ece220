;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming video lecture, we will discuss 
;  how to prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** Submit a working version to Gradescope  **



	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop

; Intro: the following is written on such premises and logic is based off such pseudocode:
; x3F00 # for @ (16 bit binary)
; x3F01-x3F1A  # for A-Z (16 bit binary)
; write a while loop starting from 40 to 5A (ASCII), 0ffset =40
; x4000 string start
; pseudo python: 
; def Binary to hex(SR):
;	counter = 16
;	DR = 0
;	get SR
; 	if SR < 0:
;	DR += 8
; 	counter - 1
; 	SR += SR
; 	if SR < 0:
;	DR += 4
; 	counter - 1
; 	SR += SR
; 	if SR < 0:
;	DR += 2
; 	counter - 1
; 	SR += SR
; 	if SR < 0:
;	DR += 1
; 	counter - 1
;	if DR - 10 < 0:
;	DR += 48 dec 30 hex
;	print DR
; 	if DR - 10 >= 0:
; 	DR += 65 dec 41 hex
;	print DR
; 	SR += SR
;	if counter > 0:
; 		branch back to start
; if name == main:
; 	while offset - 5A < 0: (BRn)
;   	print leading char (offset)
;		print space
; 		load memory addr (SR) = offset-40+x3F00
; 		BinaryToHex(SR)
;		print newline
; Resgister definition:	
;	print | counter | SR | DR | offset | x3F00 | temp | X  |
;   R0	  | R1      | R2 | R3 | R4     | R5    | R6   | R7 |
; This program uses labels like functions, but with input values being global variables. 

BIN_TO_HEX				; loop is pseudo function definition, intakes R2
	AND R1, R1, #0		; Init R1 to 16
	ADD R1, R1, #8		; R1 += 8
	ADD R1, R1, #8		; R1 += 8
BIN_TO_HEX_START		; Actual loop portion, skips initialization
	AND R3, R3, #0		; For each time, clear output register
	AND R2, R2, R2		; L shift and get CC for R2
	BRzp SKIP8			; Skips +8 if R2 starts with 0
	ADD R3, R3, #8		; output += 8 
SKIP8					;
	ADD R1, R1, #-1		; decrement counter
	ADD R2, R2, R2		; L shift and get CC
	BRzp SKIP4			; Skips +4 if R2 starts with 0
	ADD R3, R3, #4		; output += 4
SKIP4					; 
	ADD R1, R1, #-1		; decrement counter
	ADD R2, R2, R2		; L shift and get CC
	BRzp SKIP2			; Skips +2 if R2 starts with 0
	ADD R3, R3, #2		; output += 2
SKIP2					;
	ADD R1, R1, #-1		; decrement counter
	ADD R2, R2, R2		; L shift and get CC
	BRzp SKIP1			; Skips +1 if R2 starts with 0
	ADD R3, R3, #1		; output += 1
SKIP1					;
	ADD R1, R1, #-1		; decrement counter
    ADD R2, R2, R2		; L shift and get CC
	ADD R6, R3, #-10	; if R3 -10 is less than 0, R3 is higher case
	BRn SKIP65			; program for lower case
	LD R6, HEX41		; Load R6 with x41
    ADD R6, R6, #-10	; Turned out the drift (bug) was by 10, so -10.
	ADD R0, R3, R6 		; Add R3 to R6 and OUT
        OUT				;
        BRnzp NEXT		; Go to next line
SKIP65					;
	LD R6, HEX30		; Same of non skip but for high case letters
	ADD R0, R3, R6 		; Add R3 to R6 and OUT
	OUT
NEXT
	AND R1, R1, R1		 	; Gets R1's CC 
	BRp BIN_TO_HEX_START	; if still positive than do this again
	LD R0, ENTER			; Change lines
	OUT						; OUT	
	BRnzp RESUME			; Resume anyway
	
PRINT_HIST
	AND R0, R0, #0		; init and reset registers
	AND R1, R1, #0		; init and reset registers
	AND R2, R2, #0		; init and reset registers
	AND R3, R3, #0		; init and reset registers
	LD  R4, HEX41		; init register
	ADD R4, R4, #-1		; init register (bug fix--drift by 1)
	LD  R5, HIST_ADDR	; init register
	AND R6, R6, #0		; init and reset registers
	AND R7, R7, #0		; init and reset registers
LOOP_BACK
	AND R0, R0, #0		; init and reset
	AND R1, R1, #0		; init and reset
	AND R2, R2, #0		; init and reset
	AND R3, R3, #0		; init and reset
	; R4 NOT INCLUDED
	; R5 NOT INCLUDED
	AND R6, R6, #0		; init and reset
	AND R7, R7, #0		; init and reset
	ADD R0, R4, #0		; print first ascii
	OUT					; 
	LD R0, SPACE		; print the space
	OUT					; 
	LD R6, HEX3EC0		; load memory addr (SR) = offset-40+x3F00
	ADD R6, R4, R6		; finishes above comment
	LDR R2, R6, #0		; sr definition
	BRnzp BIN_TO_HEX	; function call: BinaryToHex(SR)

RESUME
	ADD R4, R4, #1		; WHILE mechenism
	LD  R6, HEXM5A		; R6 -= x5A
	ADD R6, R4, R6		; while offset - 5A < 0: (BRn)
	BRnz LOOP_BACK		; while offset - 5A < 0: (BRn)
	BRnzp DONE			; done





; you will need to insert your code to print the histogram here

; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments



DONE	HALT			; done


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00 ; histogram starting address
STR_START	.FILL x4000	; string starting address
HEX30		.FILL x0030 ; hex30

HEX41		.FILL x0041 ; hex41
HEXM40		.FILL xFFC0 ; -hex40
HEXM5A		.FILL xFFA6 ; -hex5A
ENTER		.FILL x000A ; SPACEBAR
LITTLEX		.FILL x0078	; x
HEX3EC0		.FILL x3EC0 ; x3F00-x40
SPACE		.FILL x0020	; space



; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
