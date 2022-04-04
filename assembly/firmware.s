  .org $8000

reset:
  lda #$ff
  sta $6002

  lda #$50
  sta $6000

loop:
  ror
  sta $6000

  jmp loop

.segment  "VECTORS"
  .word $0000 ;$FFFA
  .addr reset ;$FFFC ; ends up +1
  .word $0000 ;$FFFE
