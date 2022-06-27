; This is a program which allows the user to input values and get a arithmetic result
; give inputs after countinuing in the lc3sim, and results and inputs will be printed.
; invalid inputs will be ommit and a warning will appear, halting the program.

.ORIG x3000

;your code goes here
NEW_INPUT	; takes new input, echo to screen, and jumps into evaluate
GETC		; take keyboard input
OUT			; echo
JSR EVALUATE	; Jumps into evaluate

PRINT_RESULT
JSR PRINT_HEX 	; recycled from mp1, 0 changes

DONE
HALT			; Halt

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R1 - Bit counter
;R2 - Data in R5, R5 cannot to change so we shift R2 instead
;The portion is recycled from lab1, no changes
PRINT_HEX
ST R7, PRINT_R7	; Store R7 for further restoration
AND R2, R2, #0	; clear R2
ADD R2, R2, R5	; R2 equates to R5
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
    OUT					;
    BRnzp NEXT			; Go to next line
SKIP65					
	LD R6, HEX30		; Same of non skip but for high case letters
	ADD R0, R3, R6 		; Add R3 to R6 and OUT
	OUT
NEXT
	AND R1, R1, R1		 	; Gets R1's CC 
	BRp BIN_TO_HEX_START	; if still positive than do this again
	LD R7, PRINT_R7			; Restores R7
	RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; R0 - character input from keyboard
; R6 - ASCII value being tested
; R1 - temporary register to check input char
; R3, R4, operands
; R2 - check stack in OUTPUT
; R5 - Answer

EVALUATE

;your code goes here
ST R7, EVAL_R7	; Save R7
AND R3, R3, #0	; Clear Values in R3, R4 for operations
AND R4, R4, #0	; Clear R4
AND R1, R1, #0	; R1 will be used to check input char
AND R2, R2, #0	; R2 will be use to check stack

IF_EQUAL
LD R6, ASC_EQUAL	; tests if R0 is the equal sign
ADD R1, R0, R6		; if it is R1 will be zero
BRz OUTPUT			; jumps accordingly

IF_SPACE
LD R6, ASC_SPACE	; test if R0 is the space sign
ADD R1, R0, R6		; if it is R1 will be zero
BRz NEW_INPUT		; jumps accordingly

IF_NUMBER
LD R6, ASC_ZERO		; test if R0 is a number by seeing if it is larger than 0			
ADD R1, R0, R6
BRn IF_PLUS
LD R6, ASC_NINE		; test if R0 is a number by seeing if it is smaller than 9
ADD R1, R0, R6
BRp IF_PLUS
LD R6, ASC_ZERO 	; If value is indeed a number
ADD R0, R0, R6		; Remove ASCII of 0 from it so that only the number is stored
JSR PUSH			; Push number to stack
BRnzp NEW_INPUT		; jump back to input

IF_PLUS				; when it is a plus sign
LD R6, ASC_PLUS		; if value is a plus sign
ADD R1, R0, R6		; if it is R1 will be zero
BRnp IF_MINUS		; if not go to next test
JSR POP				; pop two numbers, store and calculate, if pop fails go and print invalid
ADD R5, R5, #0
BRp INVALID_OUTPUT
ADD R4, R4, R0
JSR POP
ADD R5, R5, #0
BRp INVALID_OUTPUT
ADD R3, R3, R0
JSR PLUS			; R4 and R3 checks out, R0 will be the result
JSR PUSH			; push result to stack
BRnzp NEW_INPUT		; wait for next input

IF_MINUS			; when it is a minus sign
LD R6, ASC_MIN		; if value is a minus sign
ADD R1, R0, R6		; if it is R1 will be zero
BRnp IF_MUL			; if not go next test
JSR POP				; pop two numbers, store and calculate, if pop fails go and print invalid
ADD R5, R5, #0
BRp INVALID_OUTPUT
ADD R4, R4, R0
JSR POP
ADD R5, R5, #0
BRp INVALID_OUTPUT
ADD R3, R3, R0
JSR MIN				; R4 and R3 checks out, R0 will be the result
JSR PUSH			; push result to stack
BRnzp NEW_INPUT		; wait for next input

IF_MUL				; same as IF_PLUS and IF_MIN
LD R6, ASC_MUL
ADD R1, R0, R6
BRnp IF_DIV
JSR POP
ADD R5, R5, #0
BRp INVALID_OUTPUT
ADD R4, R4, R0
JSR POP
ADD R5, R5, #0
BRp INVALID_OUTPUT
ADD R3, R3, R0
JSR MUL
JSR PUSH
BRnzp NEW_INPUT

IF_DIV				; same as IF_PLUS and IF_MIN
LD R6, ASC_DIV
ADD R1, R0, R6
BRnp IF_EXP
JSR POP
ADD R5, R5, #0
BRp INVALID_OUTPUT
ADD R4, R4, R0
JSR POP
ADD R5, R5, #0
BRp INVALID_OUTPUT
ADD R3, R3, R0
JSR DIV
JSR PUSH
BRnzp NEW_INPUT

IF_EXP				; same as IF_PLUS and IF_MIN
LD R6, ASC_EXP
ADD R1, R0, R6
BRnp IF_INVALID
JSR POP
ADD R5, R5, #0
BRp INVALID_OUTPUT
ADD R4, R4, R0
JSR POP
ADD R5, R5, #0
BRp INVALID_OUTPUT
ADD R3, R3, R0
JSR EXP
JSR PUSH
BRnzp NEW_INPUT

IF_INVALID			; invalid outputs end up here, will redirect to printing invalid expression string
BRnzp INVALID_OUTPUT

OUTPUT				; Check if there is only one answer in stack, if not, print invalid, if yes, print the entry
LD R1, STACK_TOP
ADD R1, R1, #1
LD R2, STACK_START
NOT R2, R2
ADD R2, R2, #1
ADD R1, R1, R2
BRz NORMAL_OUTPUT
BRnzp INVALID_OUTPUT

NORMAL_OUTPUT		; Normal output, pop, store in R5 and return
	JSR POP
	AND R5, R5, #0
	ADD R5, R5, R0
	BRnzp RET_EVAL

INVALID_OUTPUT		; Invalid output, just print the string
	LEA R0, INVALID_EXP
	PUTS
	BRnzp DONE

RET_EVAL			; restore R7 and ret
	LD R7, EVAL_R7
	RET



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS
AND R0, R0, #0
;your code goes here
	ADD R0, R3, R4 ; simply add R3 and R4 to R0
	RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
AND R0, R0, #0
;your code goes here
	NOT R4, R4
	ADD R4, R4, #1 ; invert R4
	ADD R0, R4, R3 ; R3 - R4, give to R0
	RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	
;your code goes here
AND R0, R0, #0
MUL_LOOP
	ADD R4, R4, #-1 ; decrement R4
	BRn DONE_MUL
	ADD R0, R0, R3	; Add R3 to R0
	BRnzp MUL_LOOP
DONE_MUL
	RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV	
;your code goes here
	AND R0, R0, #0	; 
	NOT R4, R4		;
	ADD R4, R4, #1	; invert R4
DIV_LOOP		
	ADD R3, R3, R4	; subtract R4 from R3
	ADD R0, R0, #1	; increment R0
	ADD R3, R3, #0	; get R3, if nz then stop
	BRzp DIV_LOOP
	ADD R0, R0, #-1	; there will be one time extra subtraction did, revert that here
	RET
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
ST R1, EXP_R1
ST R2, EXP_R2
ST R5, EXP_R5


AND R0, R0, #0
AND R1, R1, #0
AND R2, R2, #0
AND R5, R5, #0

ADD R4, R4, #-1 ; Test if R4 is one
BRz ONE			; Jump if it is
ADD R4, R4, #1	; Restores R4
ADD R0, R0, #1	; R0 starts at 1
ADD R1, R4, #0	; R1 is power


OUTER
AND R5, R5, #0 	; clear R5
ADD R5, R0, #0	; R5 stores most outloop recent R0
ADD R2, R3, #0	; R2 is original base
MULT_LOOP
ADD R2, R2, #-1
BRnz DONE_MULT
ADD R0, R0, R5
BRnzp MULT_LOOP
DONE_MULT
ADD R1, R1, #-1 ; Condition for outer loop
BRp	OUTER 
BRnzp EXP_DONE

ONE
ADD R0, R3, #0 ; if R4 is one just return R3

EXP_DONE
LD R1, EXP_R1
LD R2, EXP_R2
LD R5, EXP_R5
RET

;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACK_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;


ASC_PLUS	.FILL #-43 	; ASCII values for corresponding chars
ASC_MIN	.FILL #-45
ASC_MUL	.FILL #-42
ASC_DIV	.FILL #-47
ASC_EXP	.FILL #-94
ASC_EQUAL	.FILL #-61
ASC_ZERO	.FILL #-48
ASC_NINE	.FILL #-57
ASC_SPACE	.FILL #-32

HEX41		.FILL x0041 ; HEX for x41
HEX30		.FILL x0030 ; HEX for x30

EVAL_R7		.BLKW #1	; st and rst corresponding registers in corresponding srs
PRINT_R7	.BLKW #1
EXP_R1		.BLKW #1
EXP_R2		.BLKW #1
EXP_R5		.BLKW #1
EXP_R7		.BLKW #1

INVALID_EXP	.STRINGZ "Invalid Expression"

.END
