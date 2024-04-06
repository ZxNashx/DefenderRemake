; video_base.s
; Assembly routines for setting and getting the video base register on Atari ST

	xdef _set_video_base
	xdef _get_video_base

; Set video base address
_set_video_base:
	move.l	d0,a0				; Move base address to address register a0
	move.w	(a0),d0				; Move 16-bit base address to data register d0
	lea		$FFFF8200,a1			; Load base address of video hardware registers
	movep.w	d0,1(a1)			; Write high and middle bytes to video base registers
	rts							; Return from subroutine

; Get video base address
_get_video_base:
	lea		$FFFF8200,a1			; Load base address of video hardware registers
	movep.w	1(a1),d0				; Read high and middle bytes from video base register
	swap	d0					; Swap the bytes to form the correct 16-bit address
	clr.w	d0					; Clear lower word to ensure it's zero
	move.l	d0,a0				; Move result to address register a0
	rts							; Return from subroutine
