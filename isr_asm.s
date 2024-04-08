    xdef    _vbl_isr
    xdef    _ikbd_isr
    xref    _do_VBL_ISR
    xref    _do_IKBD_ISR
    xdef    _disable_interrupts
    xdef    _enable_interrupts

_vbl_isr:
    movem.l     d0-d2/a0-a2,-(sp)
    jsr         _do_VBL_ISR
    movem.l     (sp)+,d0-d2/a0-a2
    rte

_ikbd_isr:
    movem.l     d0-d2/a0-a2,-(sp)  
    jsr         _do_IKBD_ISR       
    movem.l     (sp)+,d0-d2/a0-a2  
    rte                            

_disable_interrupts:
    move.w #$2700,sr  
    rts               

_enable_interrupts:
    move.w #$2000,sr   
    rts             