;CQUEUE code
;queue has 10 element capicity

		PRESERVE8
		THUMB
		AREA Arm_ASM,CODE,READONLY
		ENTRY
		EXPORT __main
CAPACITY EQU 40				;40 BYTES
INIT EQU 0					;front = rear = INIT
ADDR  EQU 0x10000000		;first address of queue	
__main FUNCTION
		MOV R0, #CAPACITY		;R0 is used to check wether queue is full or empty
		MOV R1, #INIT			;rear pointer is indicated by R0
		MOV R3, #ADDR			;R3 stores starting address of queue, which is used to wrape around rear and front pointer
		MOV R4, #INIT			;front pointer is indicated by R4
loop		BLGT  enqueue			;then call enqueue routinue
		CMP R0,#0				;check if queue is not full
		BGT loop				;continue if queue is not empty
		BL dequeue				;dequeue
		BL dequeue				;dequeue
		BL enqueue				;enqueue
		BL dequeue				;dequeue
		BL dequeue				;dequeue
stop 	B stop

enqueue
		CMP R0,#0			;check if there is empty slot in queue or not
		BXEQ LR				;if not, then we can not insert element
		ADD R5, #2			;Take new value to be inserted into R5
		STR R5,[R3,R1]		;Store it in queue
		ADD R1,#4			;increment rear pointer
		CMP R1,#SIZE		
		MOVEQ R1,#START		;  for circular nature
		SUB R0,R0,#4		;decrement free slot available
		BX	LR		

dequeue
		CMP R0,#CAPACITY	;check for queue emptyness
		BXEQ LR 			;if empty then cannot dequeue
		LDR R6, [R3,R4]		;read from queue and store it into R6
		ADD R4, #0x04		;increment front pointer
		CMP R4,#SIZE		
		MOVEQ R4,#START		; for circular nature
		ADD R0,#4			;Increment queue availability
		BX  LR
		ENDFUNC
		END
