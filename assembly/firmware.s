.org $8000 ; start at $8000

ACIA_DATA := $5000
ACIA_STATUS := $5001
ACIA_CMD := $5002
ACIA_CTRL := $5003

reset:
  ldx #$ff
  txs

  lda #$00
  sta ACIA_STATUS ; soft reset (value ignored)

  lda #$1f ; 8n1, 19200 baud
  sta ACIA_CTRL

  lda #$0b ; no parity, no echo, no interrupts
  sta ACIA_CMD

rx_wait:
  lda ACIA_STATUS
  and #$08 ; check rx status buffer flag
  beq rx_wait ; loop until we have data

  lda ACIA_DATA
  jsr rx_write ; write back (echo)
  jmp rx_wait

rx_write:
  sta ACIA_DATA
  pha
tx_wait:
  lda ACIA_STATUS
  and #$10 ; check tx buffer status flag
  beq tx_wait
  jsr tx_delay ; wait 100 cycles; hw bug
  pla
  rts

tx_delay: ; delay for tx, because of hardware bug with tx buffer status flag
  phx
  ldx #100 ; loop 100 times, gives us a total of about 520 cycles, which matches 1/19200 * 1mhz * 10 bits
tx_delay_1:
  dex
  bne tx_delay_1
  plx
  rts

nmi:
  jmp reset

irq:
  jmp reset

.segment  "VECTORS"
  .word nmi   ;$FFFA
  .addr reset ;$FFFC
  .word irq   ;$FFFE
