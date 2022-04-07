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
  .word reset ;$FFFA
  .addr reset ;$FFFC
  .word reset ;$FFFE
