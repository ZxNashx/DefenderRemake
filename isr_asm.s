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


; below do not work
_disable_interrupts:
    movem.l  d0,-(sp)         
    move.w   sr,d0            
    ori.w    #$0700,sr      
    movem.l  (sp)+,d0         
    rts                       

_enable_interrupts:
    movem.l  d0,-(sp)         
    move.w   d0,sr            
    movem.l  (sp)+,d0         
    rts                       
