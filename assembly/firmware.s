  .org $8000 ; start at $8000

reset:
  lda #$ff  ; store $ff in A
  sta $6002 ; store A in $6002

  lda #$50  ; store $50 in A
  sta $6000 ; store A in $6000

loop:
  ror       ; rotate right
  sta $6000 ; store A in $6000

  jmp loop  ; jump to loop

nmi:
  jmp reset  ; jump to reset

irq:
  jmp reset  ; jump to reset

.segment  "VECTORS"
  .word nmi   ;$FFFA
  .addr reset ;$FFFC
  .word irq   ;$FFFE

; 8000 A9 lda
; 8001 FF $FF
; 8002 8D sta
; 8003 02
; 8004 60 $6002
; 8005 A9 lda
; 8006 50 $50
; 8007 8D sta
; 8008 00
; 8009 60 $6000
; 800A 6A ROR :loop
; 800B 8D sta
; 800C 00
; 800D 60 $6000
; 800E 4C JMP
; 800F 0A
; 8010 80 $800A -> loop